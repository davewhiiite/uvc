/**
 * Copyright (c) 2017 - 2017, Nordic Semiconductor ASA
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 * 
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 * 
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 * 
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 * 
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 * 
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef NRF_DRV_USBD_ERRATA_H__
#define NRF_DRV_USBD_ERRATA_H__

#include <stdbool.h>
/**
 * @defgroup nrf_drv_usbd_errata Functions to check if selected PAN is present in current chip
 * @{
 * @ingroup nrf_drv_usbd
 *
 * Functions here are checking the presence of an error in current chip.
 * The checking is done at runtime based on the microcontroller version.
 * This file is subject to removal when nRF51840 prototype support is removed.
 */

#ifndef NRF_DRV_USBD_ERRATA_ENABLE
/**
 * @brief The constant that informs if errata should be enabled at all
 *
 * If this constant is set to 0, all the Errata bug fixes will be automatically disabled.
 */
#define NRF_DRV_USBD_ERRATA_ENABLE 1
#endif

static inline bool nrf_drv_usbd_errata_type_52840(void)
{
    return (*(uint32_t *)0x10000130UL == 0x8UL);
}

static inline bool nrf_drv_usbd_errata_type_52840_eng_a(void)
{
    return nrf_drv_usbd_errata_type_52840();
}

static inline bool nrf_drv_usbd_errata_type_52840_eng_b(void)
{
    return (nrf_drv_usbd_errata_type_52840() && (*(uint32_t *)0x10000134UL >= 0x1UL));
}

static inline bool nrf_drv_usbd_errata_type_52840_eng_c(void)
{
    return (nrf_drv_usbd_errata_type_52840() && (*(uint32_t *)0x10000134UL >= 0x2UL));
}

static inline bool nrf_drv_usbd_errata_type_52840_eng_d(void)
{
    return (nrf_drv_usbd_errata_type_52840() && (*(uint32_t *)0x10000134UL >= 0x3UL));
}

/* Errata: USBD: EPDATA event is not always generated. */
static inline bool nrf_drv_usbd_errata_104(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && (!nrf_drv_usbd_errata_type_52840_eng_b()));
}

/* Errata: During setup read/write transfer USBD acknowledges setup stage without SETUP task. */
static inline bool nrf_drv_usbd_errata_154(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && (!nrf_drv_usbd_errata_type_52840_eng_b()));
}

/* Errata: ISO double buffering not functional. */
static inline bool nrf_drv_usbd_errata_166(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && true);
}

/* Errata: USBD might not reach its active state. */
static inline bool nrf_drv_usbd_errata_171(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && true);
}

/* Errata: USB cannot be enabled. */
static inline bool nrf_drv_usbd_errata_187(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && nrf_drv_usbd_errata_type_52840_eng_b());
}

/* Errata: USBD cannot receive tasks during DMA. */
static inline bool nrf_drv_usbd_errata_199(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && true);
}

/* Errata: SIZE.EPOUT not writable. */
static inline bool nrf_drv_usbd_errata_200(void)
{
    return (NRF_DRV_USBD_ERRATA_ENABLE && (!nrf_drv_usbd_errata_type_52840_eng_b()));
}

/** @} */
#endif /* NRF_DRV_USBD_ERRATA_H__ */
