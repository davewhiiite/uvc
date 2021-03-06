/***************************************************************************//**
* \file cyhal_triggers_psoc6_03.c
*
* \brief
* PSoC6_03 family HAL triggers header
*
* \note
* Generator version: 1.5.7254.19579
*
********************************************************************************
* \copyright
* Copyright 2016-2020 Cypress Semiconductor Corporation
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

#include "cy_device_headers.h"
#include "cyhal_hw_types.h"

#ifdef CY_DEVICE_PSOC6A512K
#include "triggers/cyhal_triggers_psoc6_03.h"

const uint8_t cyhal_dest_to_mux[108] =
{
    135, /* TRIGGER_CANFD0_TR_DBG_DMA_ACK0 */
    10, /* TRIGGER_CANFD0_TR_EVT_SWT_IN0 */
    5, /* TRIGGER_CPUSS_CTI_TR_IN0 */
    5, /* TRIGGER_CPUSS_CTI_TR_IN1 */
    6, /* TRIGGER_CPUSS_DMAC_TR_IN0 */
    6, /* TRIGGER_CPUSS_DMAC_TR_IN1 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN0 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN1 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN2 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN3 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN4 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN5 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN6 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN7 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN8 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN9 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN10 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN11 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN12 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN13 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN14 */
    133, /* TRIGGER_CPUSS_DW0_TR_IN15 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN16 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN17 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN18 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN19 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN20 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN21 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN22 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN23 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN24 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN25 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN26 */
    128, /* TRIGGER_CPUSS_DW0_TR_IN27 */
    130, /* TRIGGER_CPUSS_DW0_TR_IN28 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN0 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN1 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN2 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN3 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN4 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN5 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN6 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN7 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN8 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN9 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN10 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN11 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN12 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN13 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN14 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN15 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN16 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN17 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN18 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN19 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN20 */
    129, /* TRIGGER_CPUSS_DW1_TR_IN21 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN22 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN23 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN24 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN25 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN26 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN27 */
    131, /* TRIGGER_CPUSS_DW1_TR_IN28 */
    132, /* TRIGGER_CPUSS_DW1_TR_IN29 */
    132, /* TRIGGER_CPUSS_DW1_TR_IN30 */
    132, /* TRIGGER_CPUSS_DW1_TR_IN31 */
    8, /* TRIGGER_CSD_DSI_START */
    9, /* TRIGGER_PASS_TR_SAR_IN */
    7, /* TRIGGER_PERI_TR_DBG_FREEZE */
    4, /* TRIGGER_PERI_TR_IO_OUTPUT0 */
    4, /* TRIGGER_PERI_TR_IO_OUTPUT1 */
    2, /* TRIGGER_TCPWM0_TR_IN0 */
    2, /* TRIGGER_TCPWM0_TR_IN1 */
    2, /* TRIGGER_TCPWM0_TR_IN2 */
    2, /* TRIGGER_TCPWM0_TR_IN3 */
    2, /* TRIGGER_TCPWM0_TR_IN4 */
    2, /* TRIGGER_TCPWM0_TR_IN5 */
    2, /* TRIGGER_TCPWM0_TR_IN6 */
    2, /* TRIGGER_TCPWM0_TR_IN7 */
    2, /* TRIGGER_TCPWM0_TR_IN8 */
    2, /* TRIGGER_TCPWM0_TR_IN9 */
    2, /* TRIGGER_TCPWM0_TR_IN10 */
    2, /* TRIGGER_TCPWM0_TR_IN11 */
    2, /* TRIGGER_TCPWM0_TR_IN12 */
    2, /* TRIGGER_TCPWM0_TR_IN13 */
    3, /* TRIGGER_TCPWM1_TR_IN0 */
    3, /* TRIGGER_TCPWM1_TR_IN1 */
    3, /* TRIGGER_TCPWM1_TR_IN2 */
    3, /* TRIGGER_TCPWM1_TR_IN3 */
    3, /* TRIGGER_TCPWM1_TR_IN4 */
    3, /* TRIGGER_TCPWM1_TR_IN5 */
    3, /* TRIGGER_TCPWM1_TR_IN6 */
    3, /* TRIGGER_TCPWM1_TR_IN7 */
    3, /* TRIGGER_TCPWM1_TR_IN8 */
    3, /* TRIGGER_TCPWM1_TR_IN9 */
    3, /* TRIGGER_TCPWM1_TR_IN10 */
    3, /* TRIGGER_TCPWM1_TR_IN11 */
    3, /* TRIGGER_TCPWM1_TR_IN12 */
    3, /* TRIGGER_TCPWM1_TR_IN13 */
    134, /* TRIGGER_USB_DMA_BURSTEND0 */
    134, /* TRIGGER_USB_DMA_BURSTEND1 */
    134, /* TRIGGER_USB_DMA_BURSTEND2 */
    134, /* TRIGGER_USB_DMA_BURSTEND3 */
    134, /* TRIGGER_USB_DMA_BURSTEND4 */
    134, /* TRIGGER_USB_DMA_BURSTEND5 */
    134, /* TRIGGER_USB_DMA_BURSTEND6 */
    134, /* TRIGGER_USB_DMA_BURSTEND7 */
};

const uint8_t cyhal_mux_dest_index[108] =
{
    0, /* TRIGGER_CANFD0_TR_DBG_DMA_ACK0 */
    0, /* TRIGGER_CANFD0_TR_EVT_SWT_IN0 */
    0, /* TRIGGER_CPUSS_CTI_TR_IN0 */
    1, /* TRIGGER_CPUSS_CTI_TR_IN1 */
    0, /* TRIGGER_CPUSS_DMAC_TR_IN0 */
    1, /* TRIGGER_CPUSS_DMAC_TR_IN1 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN0 */
    1, /* TRIGGER_CPUSS_DW0_TR_IN1 */
    2, /* TRIGGER_CPUSS_DW0_TR_IN2 */
    3, /* TRIGGER_CPUSS_DW0_TR_IN3 */
    4, /* TRIGGER_CPUSS_DW0_TR_IN4 */
    5, /* TRIGGER_CPUSS_DW0_TR_IN5 */
    6, /* TRIGGER_CPUSS_DW0_TR_IN6 */
    7, /* TRIGGER_CPUSS_DW0_TR_IN7 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN8 */
    1, /* TRIGGER_CPUSS_DW0_TR_IN9 */
    2, /* TRIGGER_CPUSS_DW0_TR_IN10 */
    3, /* TRIGGER_CPUSS_DW0_TR_IN11 */
    4, /* TRIGGER_CPUSS_DW0_TR_IN12 */
    5, /* TRIGGER_CPUSS_DW0_TR_IN13 */
    6, /* TRIGGER_CPUSS_DW0_TR_IN14 */
    7, /* TRIGGER_CPUSS_DW0_TR_IN15 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN16 */
    1, /* TRIGGER_CPUSS_DW0_TR_IN17 */
    2, /* TRIGGER_CPUSS_DW0_TR_IN18 */
    3, /* TRIGGER_CPUSS_DW0_TR_IN19 */
    4, /* TRIGGER_CPUSS_DW0_TR_IN20 */
    5, /* TRIGGER_CPUSS_DW0_TR_IN21 */
    6, /* TRIGGER_CPUSS_DW0_TR_IN22 */
    7, /* TRIGGER_CPUSS_DW0_TR_IN23 */
    8, /* TRIGGER_CPUSS_DW0_TR_IN24 */
    9, /* TRIGGER_CPUSS_DW0_TR_IN25 */
    10, /* TRIGGER_CPUSS_DW0_TR_IN26 */
    11, /* TRIGGER_CPUSS_DW0_TR_IN27 */
    0, /* TRIGGER_CPUSS_DW0_TR_IN28 */
    0, /* TRIGGER_CPUSS_DW1_TR_IN0 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN1 */
    2, /* TRIGGER_CPUSS_DW1_TR_IN2 */
    3, /* TRIGGER_CPUSS_DW1_TR_IN3 */
    4, /* TRIGGER_CPUSS_DW1_TR_IN4 */
    5, /* TRIGGER_CPUSS_DW1_TR_IN5 */
    6, /* TRIGGER_CPUSS_DW1_TR_IN6 */
    7, /* TRIGGER_CPUSS_DW1_TR_IN7 */
    0, /* TRIGGER_CPUSS_DW1_TR_IN8 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN9 */
    2, /* TRIGGER_CPUSS_DW1_TR_IN10 */
    3, /* TRIGGER_CPUSS_DW1_TR_IN11 */
    4, /* TRIGGER_CPUSS_DW1_TR_IN12 */
    5, /* TRIGGER_CPUSS_DW1_TR_IN13 */
    6, /* TRIGGER_CPUSS_DW1_TR_IN14 */
    7, /* TRIGGER_CPUSS_DW1_TR_IN15 */
    8, /* TRIGGER_CPUSS_DW1_TR_IN16 */
    9, /* TRIGGER_CPUSS_DW1_TR_IN17 */
    10, /* TRIGGER_CPUSS_DW1_TR_IN18 */
    11, /* TRIGGER_CPUSS_DW1_TR_IN19 */
    12, /* TRIGGER_CPUSS_DW1_TR_IN20 */
    13, /* TRIGGER_CPUSS_DW1_TR_IN21 */
    0, /* TRIGGER_CPUSS_DW1_TR_IN22 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN23 */
    2, /* TRIGGER_CPUSS_DW1_TR_IN24 */
    3, /* TRIGGER_CPUSS_DW1_TR_IN25 */
    4, /* TRIGGER_CPUSS_DW1_TR_IN26 */
    5, /* TRIGGER_CPUSS_DW1_TR_IN27 */
    6, /* TRIGGER_CPUSS_DW1_TR_IN28 */
    0, /* TRIGGER_CPUSS_DW1_TR_IN29 */
    1, /* TRIGGER_CPUSS_DW1_TR_IN30 */
    2, /* TRIGGER_CPUSS_DW1_TR_IN31 */
    0, /* TRIGGER_CSD_DSI_START */
    0, /* TRIGGER_PASS_TR_SAR_IN */
    0, /* TRIGGER_PERI_TR_DBG_FREEZE */
    0, /* TRIGGER_PERI_TR_IO_OUTPUT0 */
    1, /* TRIGGER_PERI_TR_IO_OUTPUT1 */
    0, /* TRIGGER_TCPWM0_TR_IN0 */
    1, /* TRIGGER_TCPWM0_TR_IN1 */
    2, /* TRIGGER_TCPWM0_TR_IN2 */
    3, /* TRIGGER_TCPWM0_TR_IN3 */
    4, /* TRIGGER_TCPWM0_TR_IN4 */
    5, /* TRIGGER_TCPWM0_TR_IN5 */
    6, /* TRIGGER_TCPWM0_TR_IN6 */
    7, /* TRIGGER_TCPWM0_TR_IN7 */
    8, /* TRIGGER_TCPWM0_TR_IN8 */
    9, /* TRIGGER_TCPWM0_TR_IN9 */
    10, /* TRIGGER_TCPWM0_TR_IN10 */
    11, /* TRIGGER_TCPWM0_TR_IN11 */
    12, /* TRIGGER_TCPWM0_TR_IN12 */
    13, /* TRIGGER_TCPWM0_TR_IN13 */
    0, /* TRIGGER_TCPWM1_TR_IN0 */
    1, /* TRIGGER_TCPWM1_TR_IN1 */
    2, /* TRIGGER_TCPWM1_TR_IN2 */
    3, /* TRIGGER_TCPWM1_TR_IN3 */
    4, /* TRIGGER_TCPWM1_TR_IN4 */
    5, /* TRIGGER_TCPWM1_TR_IN5 */
    6, /* TRIGGER_TCPWM1_TR_IN6 */
    7, /* TRIGGER_TCPWM1_TR_IN7 */
    8, /* TRIGGER_TCPWM1_TR_IN8 */
    9, /* TRIGGER_TCPWM1_TR_IN9 */
    10, /* TRIGGER_TCPWM1_TR_IN10 */
    11, /* TRIGGER_TCPWM1_TR_IN11 */
    12, /* TRIGGER_TCPWM1_TR_IN12 */
    13, /* TRIGGER_TCPWM1_TR_IN13 */
    0, /* TRIGGER_USB_DMA_BURSTEND0 */
    1, /* TRIGGER_USB_DMA_BURSTEND1 */
    2, /* TRIGGER_USB_DMA_BURSTEND2 */
    3, /* TRIGGER_USB_DMA_BURSTEND3 */
    4, /* TRIGGER_USB_DMA_BURSTEND4 */
    5, /* TRIGGER_USB_DMA_BURSTEND5 */
    6, /* TRIGGER_USB_DMA_BURSTEND6 */
    7, /* TRIGGER_USB_DMA_BURSTEND7 */
};
#endif /* CY_DEVICE_PSOC6A512K */
