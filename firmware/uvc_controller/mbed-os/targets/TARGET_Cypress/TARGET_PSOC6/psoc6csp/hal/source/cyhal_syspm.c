/***************************************************************************//**
* \file cyhal_syspm.c
*
* \brief
* Provides a high level interface for interacting with the Cypress power
* management and system clock configuration. This interface abstracts out the
* chip specific details. If any chip specific functionality is necessary, or
* performance is critical the low level functions can be used directly.
*
********************************************************************************
* \copyright
* Copyright 2018-2020 Cypress Semiconductor Corporation
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/
#include <limits.h>
#include "cyhal_system.h"
#include "cyhal_syspm.h"
#include "cy_syspm.h"
#include "cy_utils.h"
#include "cyhal_utils.h"
#include "cyhal_lptimer.h"

/** Disable the systick */
#define cyhal_syspm_disable_systick() (SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk)

/* Enable the systick */
#define cyhal_syspm_enable_systick()  (SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk)

/* Hz to KHz */
#define CYHAL_HZ_TO_KHZ_CONVERSION_FACTOR         1000

/** The common PM callback parameters set, that are used internally for different peripherals */
static cy_stc_syspm_callback_params_t internal_cb_params_sleep     = {NULL, (uint32_t *)CYHAL_SYSPM_CB_CPU_SLEEP};
static cy_stc_syspm_callback_params_t internal_cb_params_deepsleep = {NULL, (uint32_t *)CYHAL_SYSPM_CB_CPU_DEEPSLEEP};
static cy_stc_syspm_callback_params_t internal_cb_params_hibernate = {NULL, (uint32_t *)CYHAL_SYSPM_CB_SYSTEM_HIBERNATE};
static cy_stc_syspm_callback_params_t internal_cb_params_lp = {NULL, (uint32_t *)CYHAL_SYSPM_CB_SYSTEM_NORMAL};
static cy_stc_syspm_callback_params_t internal_cb_params_ulp = {NULL, (uint32_t *)CYHAL_SYSPM_CB_SYSTEM_LOW};

/* The first entry in the callback chain is always reserved for the user set
 * cyhal_syspm_register_callback callback. This may be set to a sentinel value
 * indicating it is the end of the list. All subsequent slots are where
 * peripheral drivers are tracked. This makes it very easy to determine whether
 * the user registered a callback and to make sure we run that first. */
static cyhal_syspm_callback_data_t* pm_callback_ptr = CYHAL_SYSPM_END_OF_LIST;
static cyhal_syspm_callback_data_t* peripheral_pm_callback_ptr = CYHAL_SYSPM_END_OF_LIST;

static uint16_t deep_sleep_lock = 0;

#define SYSPM_CALLBACK_ORDER    (10u)

static cy_en_syspm_status_t common_cb(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode);
static cy_stc_syspm_callback_t internal_pm_cb_sleep =
{
    .callback = common_cb,
    .type = CY_SYSPM_SLEEP,
    .skipMode = 0,
    .callbackParams = &internal_cb_params_sleep,
    .prevItm = NULL,
    .nextItm = NULL,
    .order = SYSPM_CALLBACK_ORDER,
};
static cy_stc_syspm_callback_t internal_pm_cb_deepsleep =
{
    .callback = common_cb,
    .type = CY_SYSPM_DEEPSLEEP,
    .skipMode = 0,
    .callbackParams = &internal_cb_params_deepsleep,
    .prevItm = NULL,
    .nextItm = NULL,
    .order = SYSPM_CALLBACK_ORDER,
};
static cy_stc_syspm_callback_t internal_pm_cb_hibernate =
{
    .callback = common_cb,
    .type = CY_SYSPM_HIBERNATE,
    .skipMode = 0,
    .callbackParams = &internal_cb_params_hibernate,
    .prevItm = NULL,
    .nextItm = NULL,
    .order = SYSPM_CALLBACK_ORDER,
};
static cy_stc_syspm_callback_t internal_pm_cb_lp =
{
    .callback = common_cb,
    .type = CY_SYSPM_LP,
    .skipMode = 0,
    .callbackParams = &internal_cb_params_lp,
    .prevItm = NULL,
    .nextItm = NULL,
    .order = SYSPM_CALLBACK_ORDER,
};
static cy_stc_syspm_callback_t internal_pm_cb_ulp =
{
    .callback = common_cb,
    .type = CY_SYSPM_ULP,
    .skipMode = 0,
    .callbackParams = &internal_cb_params_ulp,
    .prevItm = NULL,
    .nextItm = NULL,
    .order = SYSPM_CALLBACK_ORDER,
};

/* Defines for mapping hal hibernate sources to pdl */
#define HIB_SRC_COUNT               (10U)
#define HIB_SRC_HAL                 (0U)
#define HIB_SRC_PDL                 (1U)

static const uint32_t hib_source_map[HIB_SRC_COUNT][CYHAL_MAP_COLUMNS] =
{
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_LPCOMP0_LOW,  (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP0_LOW  },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_LPCOMP0_HIGH, (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP0_HIGH },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_LPCOMP1_LOW,  (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP1_LOW  },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_LPCOMP1_HIGH, (uint32_t)CY_SYSPM_HIBERNATE_LPCOMP1_HIGH },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_RTC_ALARM,    (uint32_t)CY_SYSPM_HIBERNATE_RTC_ALARM    },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_WDT,          (uint32_t)CY_SYSPM_HIBERNATE_WDT          },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_PINA_LOW,     (uint32_t)CY_SYSPM_HIBERNATE_PIN0_LOW     },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_PINA_HIGH,    (uint32_t)CY_SYSPM_HIBERNATE_PIN0_HIGH    },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_PINB_LOW,     (uint32_t)CY_SYSPM_HIBERNATE_PIN1_LOW     },
    { (uint32_t)CYHAL_SYSPM_HIBERNATE_PINB_HIGH,    (uint32_t)CY_SYSPM_HIBERNATE_PIN1_HIGH    }
};

static cyhal_syspm_callback_data_t* call_all_pm_callbacks(cyhal_syspm_callback_data_t* entry, bool* allow, cyhal_syspm_callback_state_t state, cyhal_syspm_callback_mode_t mode)
{
    while(entry != CYHAL_SYSPM_END_OF_LIST)
    {
        if (entry->callback != NULL &&
            (entry->states & state) == state &&
            (entry->ignore_modes & mode) != mode)
        {
            *allow = entry->callback(state, mode, entry->args) || mode != CYHAL_SYSPM_CHECK_READY;
            if (!(*allow))
            {
                // Do not increment pointer so that backtracking stop at the correct location
                break;
            }
        }
        entry = entry->next;
    }
    return entry;
}

static void backtrack_all_pm_callbacks(cyhal_syspm_callback_data_t* start, cyhal_syspm_callback_data_t* end, cyhal_syspm_callback_state_t state)
{
    while(start != end)
    {
        if (start->callback != NULL &&
            (start->states & state) == state &&
            (start->ignore_modes & CYHAL_SYSPM_CHECK_FAIL) != CYHAL_SYSPM_CHECK_FAIL)
        {
            start->callback(state, CYHAL_SYSPM_CHECK_FAIL, start->args);
        }
        start = start->next;
    }
}

static cy_en_syspm_status_t common_cb(cy_stc_syspm_callback_params_t *callbackParams, cy_en_syspm_callback_mode_t mode)
{
    // The PDL function that wrap around this callback enters critical section, this function does not need to enter critical section.
    cyhal_syspm_callback_state_t state = (cyhal_syspm_callback_state_t)(uintptr_t)callbackParams->context;
    if ((state == CYHAL_SYSPM_CB_CPU_DEEPSLEEP) && (mode == CY_SYSPM_CHECK_READY) && (deep_sleep_lock != 0))
    {
        return CY_SYSPM_FAIL;
    }
    else
    {
        cyhal_syspm_callback_mode_t hal_mode = cyhal_utils_convert_pdltohal_pm_mode(mode);
        bool allow = true;

        cyhal_syspm_callback_data_t *first, *second;
        if (hal_mode == CYHAL_SYSPM_CHECK_FAIL || hal_mode == CYHAL_SYSPM_AFTER_TRANSITION)
        {
            first = peripheral_pm_callback_ptr;
            second = pm_callback_ptr;
        }
        else
        {
            second = peripheral_pm_callback_ptr;
            first = pm_callback_ptr;
        }

        cyhal_syspm_callback_data_t* first_current = call_all_pm_callbacks(first, &allow, state, hal_mode);
        cyhal_syspm_callback_data_t* second_current = allow
            ? call_all_pm_callbacks(second, &allow, state, hal_mode)
            : second;

        if (!allow && (CYHAL_SYSPM_CHECK_READY == hal_mode))
        {
            backtrack_all_pm_callbacks(second, second_current, state);
            backtrack_all_pm_callbacks(first, first_current, state);
        }

        if (state == CYHAL_SYSPM_CB_SYSTEM_LOW && hal_mode == CYHAL_SYSPM_BEFORE_TRANSITION)
        {
            uint32_t hfclk_freq_mhz = Cy_SysClk_ClkHfGetFrequency(0) / 1000000;
            Cy_SysLib_SetWaitStates(true, hfclk_freq_mhz);
        }

        if (state == CYHAL_SYSPM_CB_SYSTEM_NORMAL && hal_mode == CYHAL_SYSPM_AFTER_TRANSITION)
        {
            uint32_t hfclk_freq_mhz = Cy_SysClk_ClkHfGetFrequency(0) / 1000000;
            Cy_SysLib_SetWaitStates(false, hfclk_freq_mhz);
        }

        return allow ? CY_SYSPM_SUCCESS : CY_SYSPM_FAIL;
    }
}

static void cyhal_syspm_remove_callback_from_list(cyhal_syspm_callback_data_t **list, cyhal_syspm_callback_data_t *remove)
{
    uint32_t intr_status = cyhal_system_critical_section_enter();
    while(*list != CYHAL_SYSPM_END_OF_LIST)
    {
        if (*list == remove)
        {
            *list = remove->next;
            remove->next = NULL;
            break;
        }
        list = &((*list)->next);
    }
    cyhal_system_critical_section_exit(intr_status);
}

static bool cyhal_syspm_is_registered(cyhal_syspm_callback_data_t *list, cyhal_syspm_callback_data_t *callback)
{
    // If callback->next is NULL it must not be registered since all registered
    // next ptrs in the list must point to the next callback or be equal to
    // CYHAL_SYSPM_END_OF_LIST
    if(callback->next == NULL)
        return false;
    else
        return true;
}

void cyhal_syspm_register_peripheral_callback(cyhal_syspm_callback_data_t *callback_data)
{
    CY_ASSERT(callback_data != NULL);
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if(!cyhal_syspm_is_registered(peripheral_pm_callback_ptr, callback_data))
    {
        callback_data->next = peripheral_pm_callback_ptr;
        peripheral_pm_callback_ptr = callback_data;
    }
    cyhal_system_critical_section_exit(intr_status);
}

void cyhal_syspm_unregister_peripheral_callback(cyhal_syspm_callback_data_t *callback_data)
{
    cyhal_syspm_remove_callback_from_list(&peripheral_pm_callback_ptr, callback_data);
}

cy_rslt_t cyhal_syspm_init(void)
{
    /* Check the IO status. If current status is frozen, unfreeze the system. */
    if (Cy_SysPm_GetIoFreezeStatus())
    {
        /* Unfreeze the system */
        Cy_SysPm_IoUnfreeze();
    }

    cy_rslt_t rslt = CY_RSLT_SUCCESS;
    if (!Cy_SysPm_RegisterCallback(&internal_pm_cb_sleep) ||
        !Cy_SysPm_RegisterCallback(&internal_pm_cb_deepsleep) ||
        !Cy_SysPm_RegisterCallback(&internal_pm_cb_hibernate) ||
        !Cy_SysPm_RegisterCallback(&internal_pm_cb_lp) ||
        !Cy_SysPm_RegisterCallback(&internal_pm_cb_ulp))
        {
            rslt = CYHAL_SYSPM_RSLT_INIT_ERROR;
        }
    return rslt;
}

cy_rslt_t cyhal_syspm_hibernate(cyhal_syspm_hibernate_source_t source)
{
    Cy_SysPm_SetHibernateWakeupSource(cyhal_utils_convert_flags(hib_source_map, HIB_SRC_HAL, HIB_SRC_PDL, HIB_SRC_COUNT, (uint32_t)source));
    return Cy_SysPm_SystemEnterHibernate();
}

cy_rslt_t cyhal_syspm_set_system_state(cyhal_syspm_system_state_t state)
{
    cy_rslt_t rslt;

    /* The wait states are changed in the common syspm handler after
     * state change is allowed and all handlers are called to take into
     * account any frequency change that might happen as a part of the
     * power management handlers
     */
    switch (state)
    {
        case CYHAL_SYSPM_SYSTEM_NORMAL:
            rslt = Cy_SysPm_SystemEnterLp();
            break;
        case CYHAL_SYSPM_SYSTEM_LOW:
            rslt = Cy_SysPm_SystemEnterUlp();
            break;
        default:
            /* Should never get here */
            CY_ASSERT(false);
            rslt = CYHAL_SYSPM_RSLT_BAD_ARGUMENT;
            break;
    }
    return rslt;
}

void cyhal_syspm_register_callback(cyhal_syspm_callback_data_t *callback_data)
{
    CY_ASSERT(callback_data != NULL);
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if(!cyhal_syspm_is_registered(pm_callback_ptr, callback_data))
    {
        callback_data->next = pm_callback_ptr;
        pm_callback_ptr = callback_data;
    }
    cyhal_system_critical_section_exit(intr_status);
}

void cyhal_syspm_unregister_callback(cyhal_syspm_callback_data_t *callback_data)
{
    cyhal_syspm_remove_callback_from_list(&pm_callback_ptr, callback_data);
}

void cyhal_syspm_lock_deepsleep(void)
{
    CY_ASSERT(deep_sleep_lock != USHRT_MAX);
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if (deep_sleep_lock < USHRT_MAX)
    {
        deep_sleep_lock++;
    }
    cyhal_system_critical_section_exit(intr_status);
}

void cyhal_syspm_unlock_deepsleep(void)
{
    CY_ASSERT(deep_sleep_lock != 0U);
    uint32_t intr_status = cyhal_system_critical_section_enter();
    if (deep_sleep_lock > 0U)
    {
        deep_sleep_lock--;
    }
    cyhal_system_critical_section_exit(intr_status);
}

cy_rslt_t cyhal_syspm_tickless_sleep_deepsleep(cyhal_lptimer_t *obj, uint32_t desired_ms, uint32_t *actual_ms, bool deep_sleep)
{
    CY_ASSERT(obj != NULL);
    uint32_t initial_ticks;
    uint32_t sleep_ticks;
    cyhal_lptimer_info_t timer_info;

    *actual_ms = 0;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if(desired_ms > 0)
    {
        cyhal_lptimer_get_info(obj, &timer_info);

        //lp_ticks = ms * lp_rate_khz
        sleep_ticks = ((desired_ms - 1) * timer_info.frequency_hz) / CYHAL_HZ_TO_KHZ_CONVERSION_FACTOR;
        initial_ticks = cyhal_lptimer_read(obj);

        result = cyhal_lptimer_set_delay(obj, sleep_ticks);
        if(result == CY_RSLT_SUCCESS)
        {
            /* Stop the timer that is generating the tick interrupt. */
            cyhal_syspm_disable_systick();

            cyhal_lptimer_enable_event(obj, CYHAL_LPTIMER_COMPARE_MATCH, CYHAL_ISR_PRIORITY_DEFAULT, true);

            result = deep_sleep ? cyhal_syspm_deepsleep() : cyhal_syspm_sleep();
            if(result == CY_RSLT_SUCCESS)
            {
                uint32_t final_ticks = cyhal_lptimer_read(obj);
                uint32_t ticks = (final_ticks < initial_ticks)
                                ? (timer_info.max_counter_value - initial_ticks) + final_ticks
                                : final_ticks - initial_ticks;
                *actual_ms = (ticks * CYHAL_HZ_TO_KHZ_CONVERSION_FACTOR) / timer_info.frequency_hz;
            }

            cyhal_lptimer_enable_event(obj, CYHAL_LPTIMER_COMPARE_MATCH, CYHAL_ISR_PRIORITY_DEFAULT, false);

            /* Restart the systick timer. */
            cyhal_syspm_enable_systick();
        }
    }

    return result;
}
