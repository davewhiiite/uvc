/*
 * The Clear BSD License
 * Copyright (c) 2016, Freescale Semiconductor, Inc.
 * Copyright (c) 2016, NXP
 * All rights reserved.
 *
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted (subject to the limitations in the disclaimer below) provided
 * that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of copyright holder nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE GRANTED BY THIS LICENSE.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "fsl_common.h"
#include "fsl_reset.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/

/*******************************************************************************
 * Variables
 ******************************************************************************/

/*******************************************************************************
 * Prototypes
 ******************************************************************************/

/*******************************************************************************
 * Code
 ******************************************************************************/

#if ((defined(FSL_FEATURE_SOC_SYSCON_COUNT) && (FSL_FEATURE_SOC_SYSCON_COUNT > 0)) || \
     (defined(FSL_FEATURE_SOC_ASYNC_SYSCON_COUNT) && (FSL_FEATURE_SOC_ASYNC_SYSCON_COUNT > 0)))

void RESET_SetPeripheralReset(reset_ip_name_t peripheral)
{
    const uint32_t regIndex = ((uint32_t)peripheral & 0xFFFF0000u) >> 16;
    const uint32_t bitPos = ((uint32_t)peripheral & 0x0000FFFFu);
    const uint32_t bitMask = 1u << bitPos;

    assert(bitPos < 32u);

    /* ASYNC_SYSCON registers have offset 1024 */
    if (regIndex >= SYSCON_PRESETCTRL_COUNT)
    {
        /* reset register is in ASYNC_SYSCON */

        /* set bit */
        ASYNC_SYSCON->ASYNCPRESETCTRLSET = bitMask;
        /* wait until it reads 0b1 */
        while (0u == (ASYNC_SYSCON->ASYNCPRESETCTRL & bitMask))
        {
        }
    }
    else
    {
        /* reset register is in SYSCON */

        /* set bit */
        SYSCON->PRESETCTRLSET[regIndex] = bitMask;
        /* wait until it reads 0b1 */
        while (0u == (SYSCON->PRESETCTRL[regIndex] & bitMask))
        {
        }
    }
}

void RESET_ClearPeripheralReset(reset_ip_name_t peripheral)
{
    const uint32_t regIndex = ((uint32_t)peripheral & 0xFFFF0000u) >> 16;
    const uint32_t bitPos = ((uint32_t)peripheral & 0x0000FFFFu);
    const uint32_t bitMask = 1u << bitPos;

    assert(bitPos < 32u);

    /* ASYNC_SYSCON registers have offset 1024 */
    if (regIndex >= SYSCON_PRESETCTRL_COUNT)
    {
        /* reset register is in ASYNC_SYSCON */

        /* clear bit */
        ASYNC_SYSCON->ASYNCPRESETCTRLCLR = bitMask;
        /* wait until it reads 0b0 */
        while (bitMask == (ASYNC_SYSCON->ASYNCPRESETCTRL & bitMask))
        {
        }
    }
    else
    {
        /* reset register is in SYSCON */

        /* clear bit */
        SYSCON->PRESETCTRLCLR[regIndex] = bitMask;
        /* wait until it reads 0b0 */
        while (bitMask == (SYSCON->PRESETCTRL[regIndex] & bitMask))
        {
        }
    }
}

void RESET_PeripheralReset(reset_ip_name_t peripheral)
{
    RESET_SetPeripheralReset(peripheral);
    RESET_ClearPeripheralReset(peripheral);
}

#endif /* FSL_FEATURE_SOC_SYSCON_COUNT || FSL_FEATURE_SOC_ASYNC_SYSCON_COUNT */
