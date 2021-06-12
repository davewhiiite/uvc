/***************************************************************************//**
* \file cyhal_spi.c
*
* \brief
* Provides a high level interface for interacting with the Cypress SPI. This is
* a wrapper around the lower level PDL API.
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

#include <stdlib.h>
#include <string.h>
#include "cyhal_spi.h"
#include "cyhal_scb_common.h"
#include "cyhal_gpio.h"
#include "cyhal_system_impl.h"
#include "cyhal_hwmgr.h"
#include "cyhal_system.h"
#include "cyhal_syspm.h"

#ifdef CY_IP_MXSCB

#if defined(__cplusplus)
extern "C"
{
#endif

#define SPI_DEFAULT_SPEED               100000
#define NUM_SPI_PORTS                   8

#define SPI_OVERSAMPLE_MIN              4
#define SPI_OVERSAMPLE_MAX              16

#define FRAC_DVDR_MAX_VAL               32

#define SPI_SLAVE_FREQ_MUL              8
/* Default timeout in milliseconds */
#define SPI_DEFAULT_TIMEOUT             1000

#define PENDING_NONE                    0
#define PENDING_RX                      1
#define PENDING_TX                      2
#define PENDING_TX_RX                   3

/* Default SPI configuration */
static const cy_stc_scb_spi_config_t default_spi_config =
{
    .spiMode                  = CY_SCB_SPI_MASTER,
    .subMode                  = CY_SCB_SPI_MOTOROLA,
    .sclkMode                 = CY_SCB_SPI_CPHA0_CPOL0,
    .oversample               = SPI_OVERSAMPLE_MIN,
    .rxDataWidth              = 8,
    .txDataWidth              = 8,
    .enableMsbFirst           = true,
    .enableFreeRunSclk        = false,
    .enableInputFilter        = false,
    .enableMisoLateSample     = true,
    .enableTransferSeperation = false,
    .enableWakeFromSleep      = false,
    .ssPolarity               = CY_SCB_SPI_ACTIVE_LOW,
    .rxFifoTriggerLevel       = 0,
    .rxFifoIntEnableMask      = 0,
    .txFifoTriggerLevel       = 0,
    .txFifoIntEnableMask      = 0,
    .masterSlaveIntEnableMask = 0
};

static cyhal_spi_event_t cyhal_convert_interrupt_cause(uint32_t pdl_cause);

static cy_rslt_t cyhal_int_spi_frequency(cyhal_spi_t *obj, uint32_t hz, uint8_t *ovr_smpl_val);
static void cyhal_set_ssel(cyhal_spi_t *obj);
static void cyhal_reset_ssel(cyhal_spi_t *obj);

static cyhal_spi_event_t cyhal_convert_interrupt_cause(uint32_t pdl_cause)
{
    cyhal_spi_event_t cause;
    switch (pdl_cause)
    {
        case CY_SCB_SPI_TRANSFER_IN_FIFO_EVENT:
            cause = CYHAL_SPI_IRQ_DATA_IN_FIFO;
            break;
        case CY_SCB_SPI_TRANSFER_CMPLT_EVENT:
            cause = CYHAL_SPI_IRQ_DONE;
            break;
        case CY_SCB_SPI_TRANSFER_ERR_EVENT:
            cause = CYHAL_SPI_IRQ_ERROR;
            break;
        default:
            cause = CYHAL_SPI_IRQ_ERROR;
            break;
    }
    return cause;
}

static void cyhal_spi_irq_handler(void)
{
    cyhal_spi_t *obj = (cyhal_spi_t*) cyhal_scb_get_irq_obj();
    if (NULL == obj)
    {
        return;
    }

    Cy_SCB_SPI_Interrupt(obj->base, &(obj->context));

    if (!obj->is_async)
    {
        return;
    }

    if (0 == (Cy_SCB_SPI_GetTransferStatus(obj->base,  &obj->context) & CY_SCB_SPI_TRANSFER_ACTIVE))
    {
        if (obj->tx_buffer)
        {
            /* Start TX Transfer */
            obj->pending = PENDING_TX;
            const uint8_t *buf = obj->tx_buffer;
            obj->tx_buffer = NULL;

            Cy_SCB_SPI_Transfer(obj->base, (uint8_t *)buf, NULL, obj->tx_buffer_size, &obj->context);
        }
        else if (obj->rx_buffer)
        {
            /* Start RX Transfer */
            obj->pending = PENDING_RX;
            uint8_t *rx_buf = obj->rx_buffer;
            uint8_t *tx_buf;
            size_t trx_size = obj->rx_buffer_size;

            if (obj->rx_buffer_size > 1)
            {
                trx_size -= 1; // Transfer everything left except for the last byte

                uint8_t **rx_buffer_p = (uint8_t **) &obj->rx_buffer;

                tx_buf = *rx_buffer_p + 1; // Start at second byte to avoid trying to transmit and receive the same byte
                memset(tx_buf, obj->write_fill, trx_size);

                *rx_buffer_p += trx_size; // Move to 1 byte before end
                obj->rx_buffer_size = 1; // Transfer the last byte on the next interrupt
            }
            else
            {
                tx_buf = &obj->write_fill;

                obj->rx_buffer = NULL;
            }

            Cy_SCB_SPI_Transfer(obj->base, tx_buf, rx_buf, trx_size, &obj->context);
        }
        else
        {
            /* Finish Async Transfer */
            obj->pending = PENDING_NONE;
            obj->is_async = false;
            cyhal_reset_ssel(obj);
        }
    }
}

static void cyhal_spi_cb_wrapper(uint32_t event)
{
    cyhal_spi_t *obj = (cyhal_spi_t*) cyhal_scb_get_irq_obj();
    cyhal_spi_irq_event_t anded_events = (cyhal_spi_irq_event_t) (obj->irq_cause & (uint32_t) cyhal_convert_interrupt_cause(event));

    // Don't call the callback until the final transfer has put everything in the FIFO/completed
    if ((anded_events & (CYHAL_SPI_IRQ_DATA_IN_FIFO | CYHAL_SPI_IRQ_DONE)) && !(obj->rx_buffer == NULL && obj->tx_buffer == NULL))
    {
        return;
    }

    if (anded_events)
    {
        cyhal_spi_event_callback_t callback = (cyhal_spi_event_callback_t) obj->callback_data.callback;
        callback(obj->callback_data.callback_arg, anded_events);
    }
}

static cy_en_scb_spi_sclk_mode_t cyhal_convert_mode_sclk(cyhal_spi_mode_t mode)
{
    uint8_t sclk_mode = (mode & (CYHAL_SPI_MODE_FLAG_CPOL | CYHAL_SPI_MODE_FLAG_CPHA));

    switch (sclk_mode)
    {
        case CYHAL_SPI_MODE_FLAG_CPOL | CYHAL_SPI_MODE_FLAG_CPHA:
            return (CY_SCB_SPI_CPHA1_CPOL1);
        case CYHAL_SPI_MODE_FLAG_CPOL:
            return (CY_SCB_SPI_CPHA0_CPOL1);
        case CYHAL_SPI_MODE_FLAG_CPHA:
            return (CY_SCB_SPI_CPHA1_CPOL0);
        default:
            return (CY_SCB_SPI_CPHA0_CPOL0);
    }
}

static bool is_cyhal_mode_msb(cyhal_spi_mode_t mode)
{
    return ((mode & CYHAL_SPI_MODE_FLAG_LSB) != CYHAL_SPI_MODE_FLAG_LSB);
}

static bool cyhal_spi_pm_callback_instance(void *obj_ptr, cyhal_syspm_callback_state_t state, cy_en_syspm_callback_mode_t pdl_mode)
{
    cyhal_spi_t *obj = (cyhal_spi_t *)obj_ptr;
    bool allow = true;
    cy_stc_syspm_callback_params_t spi_callback_params = {
        .base = (void *) (obj->base),
        .context = (void *) &(obj->context)
    };

    if (CYHAL_SYSPM_CB_CPU_DEEPSLEEP == state)
        allow = (CY_SYSPM_SUCCESS == Cy_SCB_SPI_DeepSleepCallback(&spi_callback_params, pdl_mode));
    else if (CYHAL_SYSPM_CB_SYSTEM_HIBERNATE == state)
        allow = (CY_SYSPM_SUCCESS == Cy_SCB_SPI_HibernateCallback(&spi_callback_params, pdl_mode));

    return allow;
}

cy_rslt_t cyhal_spi_init(cyhal_spi_t *obj, cyhal_gpio_t mosi, cyhal_gpio_t miso, cyhal_gpio_t sclk, cyhal_gpio_t ssel, const cyhal_clock_divider_t *clk,
                        uint8_t bits, cyhal_spi_mode_t mode, bool is_slave)
{
    CY_ASSERT(NULL != obj);
    memset(obj, 0, sizeof(cyhal_spi_t));

    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint8_t ovr_sample_val = SPI_OVERSAMPLE_MIN;

    // Explicitly marked not allocated resources as invalid to prevent freeing them.
    obj->resource.type = CYHAL_RSC_INVALID;
    obj->pin_miso = CYHAL_NC_PIN_VALUE;
    obj->pin_mosi = CYHAL_NC_PIN_VALUE;
    obj->pin_sclk = CYHAL_NC_PIN_VALUE;
    obj->pin_ssel = CYHAL_NC_PIN_VALUE;

    obj->write_fill = (uint8_t) CY_SCB_SPI_DEFAULT_TX;

    /* Validate pins configuration. Mandatory pins:*/
    /* Master mode: MOSI pin used, MISO unused:     SCLK, SSEL are optional */
    /* Master mode: MISO pin used, MOSI unused:     SCLK is mandatory, MOSI, SSEL are optional */
    /* Slave  mode: MOSI or MISO are used:          SCLK is mandatory, SSEL is optional */

    /* Slave */
    if (is_slave)
    {
        if ((NC == sclk) || ((NC == mosi) && (NC == miso)))
        {
            return CYHAL_SPI_RSLT_PIN_CONFIG_NOT_SUPPORTED;
        }
    }
    /* Master */
    else
    {
        if ((NC != miso && NC == sclk) || (NC == mosi && NC == miso))
        {
            return CYHAL_SPI_RSLT_PIN_CONFIG_NOT_SUPPORTED;
        }
    }

    /* Get pin configurations */
    const cyhal_resource_pin_mapping_t *mosi_map;
    const cyhal_resource_pin_mapping_t *miso_map;
    const cyhal_resource_pin_mapping_t *sclk_map;
    const cyhal_resource_pin_mapping_t *ssel_map;
    if (is_slave)
    {
        mosi_map = CYHAL_FIND_SCB_MAP(mosi, cyhal_pin_map_scb_spi_s_mosi);
        miso_map = CYHAL_FIND_SCB_MAP(miso, cyhal_pin_map_scb_spi_s_miso);
        sclk_map = CYHAL_FIND_SCB_MAP(sclk, cyhal_pin_map_scb_spi_s_clk);
        ssel_map = CYHAL_FIND_SCB_MAP(ssel, cyhal_pin_map_scb_spi_s_select0);
    }
    else
    {
        mosi_map = CYHAL_FIND_SCB_MAP(mosi, cyhal_pin_map_scb_spi_m_mosi);
        miso_map = CYHAL_FIND_SCB_MAP(miso, cyhal_pin_map_scb_spi_m_miso);
        sclk_map = CYHAL_FIND_SCB_MAP(sclk, cyhal_pin_map_scb_spi_m_clk);
        ssel_map = CYHAL_FIND_SCB_MAP(ssel, cyhal_pin_map_scb_spi_m_select0);
    }

    const cyhal_resource_inst_t *spi_inst = (NC != mosi)
        ? mosi_map->inst
        : miso_map->inst;

    /* Validate pins mapping */
    if (((NC != mosi) && ((NULL == mosi_map) || !cyhal_utils_resources_equal(spi_inst, mosi_map->inst))) ||
        ((NC != miso) && ((NULL == miso_map) || !cyhal_utils_resources_equal(spi_inst, miso_map->inst))) ||
        ((NC != sclk) && ((NULL == sclk_map) || !cyhal_utils_resources_equal(spi_inst, sclk_map->inst))) ||
        ((NC != ssel) && ((NULL == ssel_map) || !cyhal_utils_resources_equal(spi_inst, ssel_map->inst))))
    {
        return CYHAL_SPI_RSLT_ERR_INVALID_PIN;
    }

    if (CY_RSLT_SUCCESS != (result = cyhal_hwmgr_reserve(spi_inst)))
    {
        return result;
    }

    obj->resource = *spi_inst;

    // reserve the MOSI pin
    if ((result == CY_RSLT_SUCCESS) && (NC != mosi))
    {
        result = cyhal_utils_reserve_and_connect(mosi, mosi_map);
        if (result == CY_RSLT_SUCCESS)
        {
            obj->pin_mosi = mosi;
        }
    }

    // reserve the MISO pin
    if ((result == CY_RSLT_SUCCESS) && (NC != miso))
    {
        result = cyhal_utils_reserve_and_connect(miso, miso_map);
        if (result == CY_RSLT_SUCCESS)
        {
            obj->pin_miso = miso;
        }
    }

    // reserve the SCLK pin
    if (result == CY_RSLT_SUCCESS && (NC != sclk))
    {
        result = cyhal_utils_reserve_and_connect(sclk, sclk_map);
        if (result == CY_RSLT_SUCCESS)
        {
            obj->pin_sclk = sclk;
        }
    }

    // reserve the SSEL pin
    if ((result == CY_RSLT_SUCCESS) && (NC != ssel))
    {
        result = (is_slave)
            ? cyhal_utils_reserve_and_connect(ssel, ssel_map)
            : cyhal_gpio_init(ssel, CYHAL_GPIO_DIR_OUTPUT, CYHAL_GPIO_DRIVE_STRONG, true);

        if (result == CY_RSLT_SUCCESS)
        {
            obj->is_slave = is_slave;
            obj->pin_ssel = ssel;
        }
    }

    obj->base = CYHAL_SCB_BASE_ADDRESSES[obj->resource.block_num];

    if (result == CY_RSLT_SUCCESS)
    {
        if (clk == NULL)
        {
            result = cyhal_hwmgr_allocate_clock(&(obj->clock), CY_SYSCLK_DIV_16_BIT, true);
            obj->alloc_clock = true;
        }
        else
        {
            /* Per CDT 315848 and 002-20730 Rev. *E:
             * For SPI, an integer clock divider must be used for both master and slave. */
            if ((clk->div_type == CY_SYSCLK_DIV_16_5_BIT) || (clk->div_type == CY_SYSCLK_DIV_24_5_BIT))
            {
                result = CYHAL_SPI_RSLT_CLOCK_NOT_SUPPORTED;
            }
            else
            {
                obj->clock = *clk;
                obj->alloc_clock = false;
            }
        }
    }
    if (result == CY_RSLT_SUCCESS)
    {
        result = (cy_rslt_t)Cy_SysClk_PeriphAssignDivider(
                (en_clk_dst_t)((uint32_t)PCLK_SCB0_CLOCK + obj->resource.block_num), obj->clock.div_type, obj->clock.div_num);
        if (result == CY_RSLT_SUCCESS)
        {
            result = cyhal_int_spi_frequency(obj, SPI_DEFAULT_SPEED, &ovr_sample_val);
        }
    }

    if (result == CY_RSLT_SUCCESS)
    {
        cyhal_scb_update_instance_data(obj->resource.block_num, (void*)obj, &cyhal_spi_pm_callback_instance);
        cy_stc_scb_spi_config_t config_structure = default_spi_config;
        config_structure.spiMode = is_slave == 0
            ? CY_SCB_SPI_MASTER
            : CY_SCB_SPI_SLAVE;
        obj->msb_first = is_cyhal_mode_msb(mode);
        config_structure.enableMsbFirst = obj->msb_first;
        obj->clk_mode = cyhal_convert_mode_sclk(mode);
        config_structure.sclkMode = obj->clk_mode;
        config_structure.rxDataWidth = bits;
        config_structure.txDataWidth = bits;
        config_structure.oversample = ovr_sample_val;
        obj->data_bits = bits;
        obj->mode = (uint8_t) mode;
        obj->oversample_value = ovr_sample_val;
        Cy_SCB_SPI_Init(obj->base, &config_structure, &(obj->context));

        obj->callback_data.callback = NULL;
        obj->callback_data.callback_arg = NULL;
        obj->irq_cause = 0;

        cy_stc_sysint_t irqCfg = { CYHAL_SCB_IRQ_N[obj->resource.block_num], CYHAL_ISR_PRIORITY_DEFAULT };
        Cy_SysInt_Init(&irqCfg, cyhal_spi_irq_handler);
        NVIC_EnableIRQ(CYHAL_SCB_IRQ_N[obj->resource.block_num]);

        Cy_SCB_SPI_Enable(obj->base);
    }
    else
    {
        cyhal_spi_free(obj);
    }
    return result;
}

void cyhal_spi_free(cyhal_spi_t *obj)
{
    if (NULL != obj->base)
    {
        cyhal_scb_update_instance_data(obj->resource.block_num, NULL, NULL);
        Cy_SCB_SPI_Disable(obj->base, NULL);
        Cy_SCB_SPI_DeInit(obj->base);
        obj->base = NULL;
    }

    if (obj->resource.type != CYHAL_RSC_INVALID)
    {
        IRQn_Type irqn = CYHAL_SCB_IRQ_N[obj->resource.block_num];
        NVIC_DisableIRQ(irqn);

        cyhal_hwmgr_free(&(obj->resource));
        obj->resource.type = CYHAL_RSC_INVALID;
    }

    cyhal_utils_release_if_used(&(obj->pin_miso));
    cyhal_utils_release_if_used(&(obj->pin_mosi));
    cyhal_utils_release_if_used(&(obj->pin_sclk));
    cyhal_utils_release_if_used(&(obj->pin_ssel));

    if (obj->alloc_clock)
    {
       cyhal_hwmgr_free_clock(&(obj->clock));
       obj->alloc_clock = false;
    }
}

static inline uint32_t min(uint32_t lhs, uint32_t rhs)
{
    return lhs > rhs ? rhs : lhs;
}

static inline uint32_t max(uint32_t lhs, uint32_t rhs)
{
    return lhs < rhs ? rhs : lhs;
}

static cy_rslt_t cyhal_int_spi_frequency(cyhal_spi_t *obj, uint32_t hz, uint8_t *over_sample_val)
{
    CY_ASSERT(NULL != obj);
    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint8_t oversample_value;
    uint32_t divider_value;
    uint32_t last_diff = 0xFFFFFFFFU;
    uint8_t last_ovrsmpl_val = 0;
    uint32_t last_dvdr_val = 0;
    uint32_t oversampled_freq = 0;
    uint32_t divided_freq = 0;
    uint32_t diff = 0;

    Cy_SysClk_PeriphDisableDivider(obj->clock.div_type, obj->clock.div_num);

    if (!obj->is_slave)
    {
        for (oversample_value = SPI_OVERSAMPLE_MIN; oversample_value <= SPI_OVERSAMPLE_MAX; oversample_value++)
        {
            oversampled_freq = hz * oversample_value;
            if ((hz * oversample_value > Cy_SysClk_ClkPeriGetFrequency()) && (SPI_OVERSAMPLE_MIN == oversample_value))
            {
                return CYHAL_SPI_RSLT_CLOCK_ERROR;
            }
            else if (hz * oversample_value > Cy_SysClk_ClkPeriGetFrequency())
            {
                continue;
            }

            divider_value = cyhal_divider_value(hz * oversample_value, 0);
            divided_freq = Cy_SysClk_ClkPeriGetFrequency() /(divider_value + 1);
            diff = max(oversampled_freq, divided_freq) - min(oversampled_freq, divided_freq);

            if (diff < last_diff)
            {
                last_diff = diff;
                last_ovrsmpl_val = oversample_value;
                last_dvdr_val = divider_value;
                if (0 == diff)
                {
                    break;
                }
            }
        }
        *over_sample_val = last_ovrsmpl_val;
    }
    else
    {
        /* Slave requires such frequency: required_frequency = N / ((0.5 * desired_period) – 20 nsec - tDSI,
        *   N is 3 when "Enable Input Glitch Filter" is false and 4 when true.
        *   tDSI Is external master delay which is assumed to be 16.66 nsec */

        /* Divided by 2 desired period to avoid dividing in required_frequency formula */
        float desired_period_us_divided = 5e5f * (1 / (float)hz);
        uint32_t required_frequency = (uint32_t)(3e6f / (desired_period_us_divided - 36.66f / 1e3f));

        if (required_frequency > Cy_SysClk_ClkPeriGetFrequency())
        {
            return CYHAL_SPI_RSLT_CLOCK_ERROR;
        }

        /* Use maximum available clock for slave to make it able to work with any master environment */
        last_dvdr_val = 1;
    }

    result = Cy_SysClk_PeriphSetDivider(obj->clock.div_type, obj->clock.div_num, last_dvdr_val);

    if (CY_RSLT_SUCCESS == result)
    {
        Cy_SysClk_PeriphEnableDivider(obj->clock.div_type, obj->clock.div_num);
    }

    return result;
}

#define SSEL_ACTIVE      ( 0 )
#define SSEL_INACTIVE    ( 1 )
static void cyhal_set_ssel(cyhal_spi_t *obj)
{
    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE != obj->pin_ssel))
    {
       cyhal_gpio_write(obj->pin_ssel, SSEL_ACTIVE);
    }
}

static void cyhal_reset_ssel(cyhal_spi_t *obj)
{
    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE != obj->pin_ssel))
    {
       cyhal_gpio_write(obj->pin_ssel, SSEL_INACTIVE);
    }
}

cy_rslt_t cyhal_spi_set_frequency(cyhal_spi_t *obj, uint32_t hz)
{
    cy_rslt_t result = CY_RSLT_SUCCESS;
    uint8_t   ovr_sample_val;

    if (NULL == obj)
    {
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;
    }

    Cy_SCB_SPI_Disable(obj->base, &obj->context);
    result = cyhal_int_spi_frequency(obj, hz, &ovr_sample_val);

    /* No need to reconfigure slave since oversample value, that was changed in cyhal_int_spi_frequency, in slave is ignored */
    if ((CY_RSLT_SUCCESS == result) && !obj->is_slave && (obj->oversample_value != ovr_sample_val))
    {
       cy_stc_scb_spi_config_t config_structure = default_spi_config;
       Cy_SCB_SPI_DeInit(obj->base);
       config_structure.spiMode = obj->is_slave == false
           ? CY_SCB_SPI_MASTER
           : CY_SCB_SPI_SLAVE;
       config_structure.enableMsbFirst = obj->msb_first;
       config_structure.sclkMode = obj->clk_mode;
       config_structure.rxDataWidth = obj->data_bits;
       config_structure.txDataWidth = obj->data_bits;
       config_structure.oversample = ovr_sample_val;
       obj->oversample_value = ovr_sample_val;
       Cy_SCB_SPI_Init(obj->base, &config_structure, &(obj->context));
    }

    Cy_SCB_SPI_Enable(obj->base);

    return result;
}

cy_rslt_t cyhal_spi_recv(cyhal_spi_t *obj, uint32_t *value)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t read_value = CY_SCB_SPI_RX_NO_DATA;
    const uint32_t fill_in = 0x0000ffffUL; /* PDL Fill in value */
    uint32_t count = 0;

    if ((obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_mosi))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_miso))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if (!obj->is_slave)
    {
        cyhal_set_ssel(obj);

        /* Clear FIFOs */
        Cy_SCB_SPI_ClearTxFifo(obj->base);
        Cy_SCB_SPI_ClearRxFifo(obj->base);

        while (count == 0)
        {
            count = Cy_SCB_SPI_Write(obj->base, fill_in);
        }

        while (Cy_SCB_SPI_IsTxComplete(obj->base) == false) { }
        while (Cy_SCB_SPI_GetNumInRxFifo(obj->base) == 0) { } /* Wait for RX FIFO not empty */
        cyhal_reset_ssel(obj);
    }

    while (read_value == CY_SCB_SPI_RX_NO_DATA)
    {
        read_value = Cy_SCB_SPI_Read(obj->base);
    }
    *value = read_value;
    return CY_RSLT_SUCCESS;
}

cy_rslt_t cyhal_spi_send(cyhal_spi_t *obj, uint32_t value)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    uint32_t count = 0;
    cy_rslt_t result = CY_RSLT_SUCCESS;

    if ((obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_miso))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if ((!obj->is_slave) && (CYHAL_NC_PIN_VALUE == obj->pin_mosi))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    if (!obj->is_slave)
    {
        cyhal_set_ssel(obj);

        /* Clear FIFOs */
        Cy_SCB_SPI_ClearTxFifo(obj->base);
        Cy_SCB_SPI_ClearRxFifo(obj->base);
    }

    while (count == 0)
    {
        count = Cy_SCB_SPI_Write(obj->base, value);
    }

    if (!obj->is_slave)
    {
        while (Cy_SCB_SPI_IsTxComplete(obj->base) == false) { }
        while (Cy_SCB_SPI_GetNumInRxFifo(obj->base) == 0) { } /* Wait for RX FIFO not empty */
        cyhal_reset_ssel(obj);
        (void)Cy_SCB_SPI_Read(obj->base);
    }

    return result;
}

#define MAX_DUMMY_SIZE    ( 128 )

cy_rslt_t cyhal_spi_transfer(cyhal_spi_t *obj, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length, uint8_t write_fill)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    obj->write_fill = write_fill;
    cy_rslt_t rslt = cyhal_spi_transfer_async(obj, tx, tx_length, rx, rx_length);
    if (rslt == CY_RSLT_SUCCESS)
    {
        while (obj->pending != PENDING_NONE) { } /* Wait for async transfer to complete */
    }
    obj->write_fill = (uint8_t) CY_SCB_SPI_DEFAULT_TX;
    return rslt;
}

cy_rslt_t cyhal_spi_transfer_async(cyhal_spi_t *obj, const uint8_t *tx, size_t tx_length, uint8_t *rx, size_t rx_length)
{
    if (NULL == obj)
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;

    if (cyhal_scb_pm_transition_pending())
        return CYHAL_SYSPM_RSLT_ERR_PM_PENDING;

    cy_en_scb_spi_status_t spi_status;

    if ((CYHAL_NC_PIN_VALUE == obj->pin_mosi) || (CYHAL_NC_PIN_VALUE == obj->pin_miso))
    {
        return CYHAL_SPI_RSLT_INVALID_PIN_API_NOT_SUPPORTED;
    }

    cyhal_set_ssel(obj);
    obj->is_async = true;

    /* Setup transfer */
    if (tx_length > rx_length)
    {
        if (rx_length > 0)
        {
            /* I) write + read, II) write only */
            obj->pending = PENDING_TX_RX;
            obj->rx_buffer = NULL;

            obj->tx_buffer = tx + (obj->data_bits <= 8 ? rx_length : (rx_length * 2));
            obj->tx_buffer_size = tx_length - rx_length;

            tx_length = rx_length; // Use tx_length to store entire transfer length
        }
        else
        {
            /*  I) write only */
            obj->pending = PENDING_TX;
            obj->rx_buffer = NULL;
            obj->tx_buffer = NULL;

            rx = NULL;
        }
    }
    else if (rx_length > tx_length)
    {
        if (tx_length > 0)
        {
            /*  I) write + read, II) read only */
            obj->pending = PENDING_TX_RX;
            obj->tx_buffer = NULL;

            obj->rx_buffer = rx + (obj->data_bits <= 8 ? tx_length : (tx_length * 2));
            obj->rx_buffer_size = rx_length - tx_length;
        }
        else
        {
            /*  I) read only. */
            obj->pending = PENDING_RX;
            obj->tx_buffer = NULL;

            obj->rx_buffer = rx_length > 1 ? rx + 1 : NULL;
            obj->rx_buffer_size = rx_length - 1;
            tx = &obj->write_fill;
            tx_length = 1;
        }
    }
    else
    {
        /* RX and TX of the same size: I) write + read. */
        obj->pending = PENDING_TX_RX;
        obj->rx_buffer = NULL;
        obj->tx_buffer = NULL;
    }
    spi_status = Cy_SCB_SPI_Transfer(obj->base, (void *)tx, rx, tx_length, &obj->context);
    return spi_status == CY_SCB_SPI_SUCCESS
        ? CY_RSLT_SUCCESS
        : CYHAL_SPI_RSLT_TRANSFER_ERROR;
}

bool cyhal_spi_is_busy(cyhal_spi_t *obj)
{
    return Cy_SCB_SPI_IsBusBusy(obj->base);
}

cy_rslt_t cyhal_spi_abort_async(cyhal_spi_t *obj)
{
    if (NULL == obj)
    {
        return CYHAL_SPI_RSLT_BAD_ARGUMENT;
    }

    Cy_SCB_SPI_AbortTransfer(obj->base, &(obj->context));
    obj->pending = PENDING_NONE;
    return CY_RSLT_SUCCESS;
}

void cyhal_spi_register_callback(cyhal_spi_t *obj, cyhal_spi_event_callback_t callback, void *callback_arg)
{
    uint32_t savedIntrStatus = cyhal_system_critical_section_enter();
    obj->callback_data.callback = (cy_israddress) callback;
    obj->callback_data.callback_arg = callback_arg;
    cyhal_system_critical_section_exit(savedIntrStatus);
    Cy_SCB_SPI_RegisterCallback(obj->base, cyhal_spi_cb_wrapper, &(obj->context));

    obj->irq_cause = 0;
}

void cyhal_spi_enable_event(cyhal_spi_t *obj, cyhal_spi_event_t event, uint8_t intr_priority, bool enable)
{
    if (enable)
    {
        obj->irq_cause |= event;
    }
    else
    {
        obj->irq_cause &= ~event;
    }

    IRQn_Type irqn = CYHAL_SCB_IRQ_N[obj->resource.block_num];
    NVIC_SetPriority(irqn, intr_priority);
}

#if defined(__cplusplus)
}
#endif

#endif /* CY_IP_MXSCB */
