/****************************************************************************
 *
 * Copyright 2020 Samsung Electronics All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the License.
 *
 ****************************************************************************/

#ifndef __ARCH_ARM_SRC_S5JS100_S5JS100_CMU_H__
#define __ARCH_ARM_SRC_S5JS100_S5JS100_CMU_H__

#define OSCCLK ((unsigned long) 26000000)
#define SLPCLK_CP ((unsigned long) 32000)

#define S5JS100_SCMU_BASE   0x82000000
#define S5JS100_ACMU_BASE   0x83000000
#define S5JS100_MIFCMU_BASE 0x85000000

#define ACMU_AP_ACMU_CONTROLLER_OPTION  ((S5JS100_ACMU_BASE + 0x800))
#define ACMU_SPARE0 ((S5JS100_ACMU_BASE + 0x880))
#define ACMU_VER    ((S5JS100_ACMU_BASE + 0x890))
#define ACMU_ACMU_CONFIG0   ((S5JS100_ACMU_BASE + 0x904))
#define ACMU_ACMU_CONFIG1   ((S5JS100_ACMU_BASE + 0x908))
#define ACMU_ACMU_DFSC_CFG0 ((S5JS100_ACMU_BASE + 0x910))
#define ACMU_ACMU_DFSC_CFG1 ((S5JS100_ACMU_BASE + 0x914))
#define ACMU_ACMU_DFSC_CTL  ((S5JS100_ACMU_BASE + 0x920))
#define ACMU_ACMU_BUS_ACT_MSK   ((S5JS100_ACMU_BASE + 0x950))
#define ACMU_ACMU_MON_CLK   ((S5JS100_ACMU_BASE + 0x9e0))
#define ACMU_MR_REGISTER_A00    ((S5JS100_ACMU_BASE + 0xa00))
#define ACMU_MR_REGISTER_A04    ((S5JS100_ACMU_BASE + 0xa04))
#define ACMU_MR_REGISTER_C00    ((S5JS100_ACMU_BASE + 0xc00))
#define ACMU_CLK_CON_MUX_CKMUXA_TIMER0_CLK  ((S5JS100_ACMU_BASE + 0x1000))
#define ACMU_CLK_CON_MUX_CKMUXA_TIMER1_CLK  ((S5JS100_ACMU_BASE + 0x1004))
#define ACMU_CLK_CON_MUX_CKMUXA_TIMER2_CLK  ((S5JS100_ACMU_BASE + 0x1008))
#define ACMU_CLK_CON_MUX_CKMUXA_TIMER3_CLK  ((S5JS100_ACMU_BASE + 0x100c))
#define ACMU_CLK_CON_MUX_CKMUXA_TIMER4_CLK  ((S5JS100_ACMU_BASE + 0x1010))
#define ACMU_CLK_CON_MUX_CKMUXA_TIMER5_CLK  ((S5JS100_ACMU_BASE + 0x1014))
#define ACMU_CLK_CON_DIV_CKDIVA_SDIO_CLK    ((S5JS100_ACMU_BASE + 0x1804))
#define ACMU_CLK_CON_DIV_CKDIVA_SPI0_CLK    ((S5JS100_ACMU_BASE + 0x1808))
#define ACMU_CLK_CON_DIV_CKDIVA_USI0_CLK    ((S5JS100_ACMU_BASE + 0x1810))
#define ACMU_CLK_CON_DIV_CKDIVA_USI1_CLK    ((S5JS100_ACMU_BASE + 0x1814))
#define ACMU_CLK_CON_DIV_MULTI3_CKDIVA_ACPU_CLK ((S5JS100_ACMU_BASE + 0x1818))
#define ACMU_CLK_CON_BUF_BUF_AP_SRC_CLK ((S5JS100_ACMU_BASE + 0x2000))
#define ACMU_CLK_CON_GAT_CKCGA_AP_PERI_CLK  ((S5JS100_ACMU_BASE + 0x2004))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_AP_CMU_IPCLKPORT_PCLK   ((S5JS100_ACMU_BASE + 0x2008))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_ATIMER0_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x200c))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_ATIMER1_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x2010))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_ATIMER2_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x2014))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_ATIMER3_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x2018))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_ATIMER4_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x201c))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_ATIMER5_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x2020))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_AWDOG_IPCLKPORT_SLPCLK  ((S5JS100_ACMU_BASE + 0x2024))
#define ACMU_CLK_CON_GAT_CLK_AP_UID_PWM_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x2028))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ABUS_IPCLKPORT_ACPU2MCPU_LH_SI_L2CLK   ((S5JS100_ACMU_BASE + 0x202c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ABUS_IPCLKPORT_ACPU2MIF_LH_SI_L2CLK    ((S5JS100_ACMU_BASE + 0x2030))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ABUS_IPCLKPORT_L2CLK   ((S5JS100_ACMU_BASE + 0x2034))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ABUS_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x2038))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ABUS_IPCLKPORT_PPMU_L2CLK  ((S5JS100_ACMU_BASE + 0x203c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ABUS_IPCLKPORT_PPMU_L3CLK  ((S5JS100_ACMU_BASE + 0x2040))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_APMEM_IPCLKPORT_L2CLK  ((S5JS100_ACMU_BASE + 0x2044))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ATIMER0_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2048))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ATIMER1_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x204c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ATIMER2_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2050))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ATIMER3_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2054))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ATIMER4_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2058))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_ATIMER5_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x205c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_AWDOG_IPCLKPORT_L3CLK  ((S5JS100_ACMU_BASE + 0x2060))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_BS_IPCLKPORT_L2CLK ((S5JS100_ACMU_BASE + 0x2064))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_BS_MEM_IPCLKPORT_L2CLK ((S5JS100_ACMU_BASE + 0x2068))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_CM7_IPCLKPORT_L1CLK    ((S5JS100_ACMU_BASE + 0x206c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_CM7_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2070))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_CS_IPCLKPORT_L2CLK ((S5JS100_ACMU_BASE + 0x2074))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_CS_IPCLKPORT_L3CLK ((S5JS100_ACMU_BASE + 0x2078))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_I2C0_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x207c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_PDMA_IPCLKPORT_L2CLK   ((S5JS100_ACMU_BASE + 0x2080))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_PUF_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2084))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_PWM_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x2088))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SDIO_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x208c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SDIO_IPCLKPORT_L2CLK   ((S5JS100_ACMU_BASE + 0x2090))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SDIO_IPCLKPORT_SDIO_HCLK   ((S5JS100_ACMU_BASE + 0x2094))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SPI0_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x2098))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SPI0_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x209c))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SSS_IPCLKPORT_L2CLK    ((S5JS100_ACMU_BASE + 0x20a0))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SSS_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x20a4))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_SSS_IPCLKPORT_SLVHCLK  ((S5JS100_ACMU_BASE + 0x20a8))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_USI0_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x20ac))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_USI0_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x20b0))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_USI1_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x20b4))
#define ACMU_CLK_CON_GAT_GOUT_AP_UID_USI1_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x20b8))
#define ACMU_DMYQCH_CON_ABUS_QCH_PPMU_CLK   ((S5JS100_ACMU_BASE + 0x3000))
#define ACMU_DMYQCH_CON_ATIMER0_QCH ((S5JS100_ACMU_BASE + 0x3004))
#define ACMU_DMYQCH_CON_ATIMER1_QCH ((S5JS100_ACMU_BASE + 0x3008))
#define ACMU_DMYQCH_CON_ATIMER2_QCH ((S5JS100_ACMU_BASE + 0x300c))
#define ACMU_DMYQCH_CON_ATIMER3_QCH ((S5JS100_ACMU_BASE + 0x3010))
#define ACMU_DMYQCH_CON_ATIMER4_QCH ((S5JS100_ACMU_BASE + 0x3014))
#define ACMU_DMYQCH_CON_ATIMER5_QCH ((S5JS100_ACMU_BASE + 0x3018))
#define ACMU_DMYQCH_CON_AWDOG_QCH   ((S5JS100_ACMU_BASE + 0x301c))
#define ACMU_DMYQCH_CON_CS_QCH  ((S5JS100_ACMU_BASE + 0x3020))
#define ACMU_DMYQCH_CON_PUF_QCH ((S5JS100_ACMU_BASE + 0x3024))
#define ACMU_DMYQCH_CON_PWM_QCH_CLK ((S5JS100_ACMU_BASE + 0x3028))
#define ACMU_DMYQCH_CON_SDIO_QCH_HCLK   ((S5JS100_ACMU_BASE + 0x302c))
#define ACMU_DMYQCH_CON_SPI0_QCH    ((S5JS100_ACMU_BASE + 0x3030))
#define ACMU_DMYQCH_CON_SSS_QCH_DEBUG   ((S5JS100_ACMU_BASE + 0x3034))
#define ACMU_QCH_CON_ABUS_QCH_ACPU2MCPU_LH_SI_L2CLK ((S5JS100_ACMU_BASE + 0x3038))
#define ACMU_QCH_CON_ABUS_QCH_ACPU2MIF_LH_SI_L2CLK  ((S5JS100_ACMU_BASE + 0x303c))
#define ACMU_QCH_CON_ABUS_QCH_L2CLK ((S5JS100_ACMU_BASE + 0x3040))
#define ACMU_QCH_CON_APMEM_QCH  ((S5JS100_ACMU_BASE + 0x3044))
#define ACMU_QCH_CON_AP_CMU_QCH ((S5JS100_ACMU_BASE + 0x3048))
#define ACMU_QCH_CON_BS_MEM_QCH ((S5JS100_ACMU_BASE + 0x304c))
#define ACMU_QCH_CON_BS_QCH ((S5JS100_ACMU_BASE + 0x3050))
#define ACMU_QCH_CON_CM7_QCH    ((S5JS100_ACMU_BASE + 0x3054))
#define ACMU_QCH_CON_I2C0_QCH   ((S5JS100_ACMU_BASE + 0x3058))
#define ACMU_QCH_CON_PDMA_QCH   ((S5JS100_ACMU_BASE + 0x305c))
#define ACMU_QCH_CON_PWM_QCH_L3CLK  ((S5JS100_ACMU_BASE + 0x3060))
#define ACMU_QCH_CON_SDIO_QCH   ((S5JS100_ACMU_BASE + 0x3064))
#define ACMU_QCH_CON_SSS_QCH    ((S5JS100_ACMU_BASE + 0x3068))
#define ACMU_QCH_CON_USI0_QCH   ((S5JS100_ACMU_BASE + 0x306c))
#define ACMU_QCH_CON_USI1_QCH   ((S5JS100_ACMU_BASE + 0x3070))
#define ACMU_QUEUE_CTRL_REG_AP_CMU  ((S5JS100_ACMU_BASE + 0x3c00))
#define ACMU_DBG_NFO_CKMUXA_TIMER0_CLK  ((S5JS100_ACMU_BASE + 0x5000))
#define ACMU_DBG_NFO_CKMUXA_TIMER1_CLK  ((S5JS100_ACMU_BASE + 0x5004))
#define ACMU_DBG_NFO_CKMUXA_TIMER2_CLK  ((S5JS100_ACMU_BASE + 0x5008))
#define ACMU_DBG_NFO_CKMUXA_TIMER3_CLK  ((S5JS100_ACMU_BASE + 0x500c))
#define ACMU_DBG_NFO_CKMUXA_TIMER4_CLK  ((S5JS100_ACMU_BASE + 0x5010))
#define ACMU_DBG_NFO_CKMUXA_TIMER5_CLK  ((S5JS100_ACMU_BASE + 0x5014))
#define ACMU_DBG_NFO_CKDIVA_ACPU_CLK    ((S5JS100_ACMU_BASE + 0x5800))
#define ACMU_DBG_NFO_CKDIVA_SDIO_CLK    ((S5JS100_ACMU_BASE + 0x5808))
#define ACMU_DBG_NFO_CKDIVA_SPI0_CLK    ((S5JS100_ACMU_BASE + 0x580c))
#define ACMU_DBG_NFO_CKDIVA_USI0_CLK    ((S5JS100_ACMU_BASE + 0x5814))
#define ACMU_DBG_NFO_CKDIVA_USI1_CLK    ((S5JS100_ACMU_BASE + 0x5818))
#define ACMU_DBG_NFO_BUF_AP_SRC_CLK ((S5JS100_ACMU_BASE + 0x6000))
#define ACMU_DBG_NFO_CKCGA_AP_PERI_CLK  ((S5JS100_ACMU_BASE + 0x6004))
#define ACMU_DBG_NFO_CLK_AP_UID_AP_CMU_IPCLKPORT_PCLK   ((S5JS100_ACMU_BASE + 0x6008))
#define ACMU_DBG_NFO_CLK_AP_UID_ATIMER0_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x600c))
#define ACMU_DBG_NFO_CLK_AP_UID_ATIMER1_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x6010))
#define ACMU_DBG_NFO_CLK_AP_UID_ATIMER2_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x6014))
#define ACMU_DBG_NFO_CLK_AP_UID_ATIMER3_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x6018))
#define ACMU_DBG_NFO_CLK_AP_UID_ATIMER4_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x601c))
#define ACMU_DBG_NFO_CLK_AP_UID_ATIMER5_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x6020))
#define ACMU_DBG_NFO_CLK_AP_UID_AWDOG_IPCLKPORT_SLPCLK  ((S5JS100_ACMU_BASE + 0x6024))
#define ACMU_DBG_NFO_CLK_AP_UID_PWM_IPCLKPORT_CLK   ((S5JS100_ACMU_BASE + 0x6028))
#define ACMU_DBG_NFO_GOUT_AP_UID_ABUS_IPCLKPORT_ACPU2MCPU_LH_SI_L2CLK   ((S5JS100_ACMU_BASE + 0x602c))
#define ACMU_DBG_NFO_GOUT_AP_UID_ABUS_IPCLKPORT_ACPU2MIF_LH_SI_L2CLK    ((S5JS100_ACMU_BASE + 0x6030))
#define ACMU_DBG_NFO_GOUT_AP_UID_ABUS_IPCLKPORT_L2CLK   ((S5JS100_ACMU_BASE + 0x6034))
#define ACMU_DBG_NFO_GOUT_AP_UID_ABUS_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x6038))
#define ACMU_DBG_NFO_GOUT_AP_UID_ABUS_IPCLKPORT_PPMU_L2CLK  ((S5JS100_ACMU_BASE + 0x603c))
#define ACMU_DBG_NFO_GOUT_AP_UID_ABUS_IPCLKPORT_PPMU_L3CLK  ((S5JS100_ACMU_BASE + 0x6040))
#define ACMU_DBG_NFO_GOUT_AP_UID_APMEM_IPCLKPORT_L2CLK  ((S5JS100_ACMU_BASE + 0x6044))
#define ACMU_DBG_NFO_GOUT_AP_UID_ATIMER0_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6048))
#define ACMU_DBG_NFO_GOUT_AP_UID_ATIMER1_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x604c))
#define ACMU_DBG_NFO_GOUT_AP_UID_ATIMER2_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6050))
#define ACMU_DBG_NFO_GOUT_AP_UID_ATIMER3_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6054))
#define ACMU_DBG_NFO_GOUT_AP_UID_ATIMER4_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6058))
#define ACMU_DBG_NFO_GOUT_AP_UID_ATIMER5_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x605c))
#define ACMU_DBG_NFO_GOUT_AP_UID_AWDOG_IPCLKPORT_L3CLK  ((S5JS100_ACMU_BASE + 0x6060))
#define ACMU_DBG_NFO_GOUT_AP_UID_BS_IPCLKPORT_L2CLK ((S5JS100_ACMU_BASE + 0x6064))
#define ACMU_DBG_NFO_GOUT_AP_UID_BS_MEM_IPCLKPORT_L2CLK ((S5JS100_ACMU_BASE + 0x6068))
#define ACMU_DBG_NFO_GOUT_AP_UID_CM7_IPCLKPORT_L1CLK    ((S5JS100_ACMU_BASE + 0x606c))
#define ACMU_DBG_NFO_GOUT_AP_UID_CM7_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6070))
#define ACMU_DBG_NFO_GOUT_AP_UID_CS_IPCLKPORT_L2CLK ((S5JS100_ACMU_BASE + 0x6074))
#define ACMU_DBG_NFO_GOUT_AP_UID_CS_IPCLKPORT_L3CLK ((S5JS100_ACMU_BASE + 0x6078))
#define ACMU_DBG_NFO_GOUT_AP_UID_I2C0_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x607c))
#define ACMU_DBG_NFO_GOUT_AP_UID_PDMA_IPCLKPORT_L2CLK   ((S5JS100_ACMU_BASE + 0x6080))
#define ACMU_DBG_NFO_GOUT_AP_UID_PUF_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6084))
#define ACMU_DBG_NFO_GOUT_AP_UID_PWM_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x6088))
#define ACMU_DBG_NFO_GOUT_AP_UID_SDIO_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x608c))
#define ACMU_DBG_NFO_GOUT_AP_UID_SDIO_IPCLKPORT_L2CLK   ((S5JS100_ACMU_BASE + 0x6090))
#define ACMU_DBG_NFO_GOUT_AP_UID_SDIO_IPCLKPORT_SDIO_HCLK   ((S5JS100_ACMU_BASE + 0x6094))
#define ACMU_DBG_NFO_GOUT_AP_UID_SPI0_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x6098))
#define ACMU_DBG_NFO_GOUT_AP_UID_SPI0_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x609c))
#define ACMU_DBG_NFO_GOUT_AP_UID_SSS_IPCLKPORT_L2CLK    ((S5JS100_ACMU_BASE + 0x60a0))
#define ACMU_DBG_NFO_GOUT_AP_UID_SSS_IPCLKPORT_L3CLK    ((S5JS100_ACMU_BASE + 0x60a4))
#define ACMU_DBG_NFO_GOUT_AP_UID_SSS_IPCLKPORT_SLVHCLK  ((S5JS100_ACMU_BASE + 0x60a8))
#define ACMU_DBG_NFO_GOUT_AP_UID_USI0_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x60ac))
#define ACMU_DBG_NFO_GOUT_AP_UID_USI0_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x60b0))
#define ACMU_DBG_NFO_GOUT_AP_UID_USI1_IPCLKPORT_CLK ((S5JS100_ACMU_BASE + 0x60b4))
#define ACMU_DBG_NFO_GOUT_AP_UID_USI1_IPCLKPORT_L3CLK   ((S5JS100_ACMU_BASE + 0x60b8))
#define ACMU_DBG_NFO_DMYQCH_CON_ABUS_QCH_PPMU_CLK   ((S5JS100_ACMU_BASE + 0x7000))
#define ACMU_DBG_NFO_DMYQCH_CON_ATIMER0_QCH ((S5JS100_ACMU_BASE + 0x7004))
#define ACMU_DBG_NFO_DMYQCH_CON_ATIMER1_QCH ((S5JS100_ACMU_BASE + 0x7008))
#define ACMU_DBG_NFO_DMYQCH_CON_ATIMER2_QCH ((S5JS100_ACMU_BASE + 0x700c))
#define ACMU_DBG_NFO_DMYQCH_CON_ATIMER3_QCH ((S5JS100_ACMU_BASE + 0x7010))
#define ACMU_DBG_NFO_DMYQCH_CON_ATIMER4_QCH ((S5JS100_ACMU_BASE + 0x7014))
#define ACMU_DBG_NFO_DMYQCH_CON_ATIMER5_QCH ((S5JS100_ACMU_BASE + 0x7018))
#define ACMU_DBG_NFO_DMYQCH_CON_AWDOG_QCH   ((S5JS100_ACMU_BASE + 0x701c))
#define ACMU_DBG_NFO_DMYQCH_CON_CS_QCH  ((S5JS100_ACMU_BASE + 0x7020))
#define ACMU_DBG_NFO_DMYQCH_CON_PUF_QCH ((S5JS100_ACMU_BASE + 0x7024))
#define ACMU_DBG_NFO_DMYQCH_CON_PWM_QCH_CLK ((S5JS100_ACMU_BASE + 0x7028))
#define ACMU_DBG_NFO_DMYQCH_CON_SDIO_QCH_HCLK   ((S5JS100_ACMU_BASE + 0x702c))
#define ACMU_DBG_NFO_DMYQCH_CON_SPI0_QCH    ((S5JS100_ACMU_BASE + 0x7030))
#define ACMU_DBG_NFO_DMYQCH_CON_SSS_QCH_DEBUG   ((S5JS100_ACMU_BASE + 0x7034))
#define ACMU_DBG_NFO_QCH_CON_ABUS_QCH_ACPU2MCPU_LH_SI_L2CLK ((S5JS100_ACMU_BASE + 0x7038))
#define ACMU_DBG_NFO_QCH_CON_ABUS_QCH_ACPU2MIF_LH_SI_L2CLK  ((S5JS100_ACMU_BASE + 0x703c))
#define ACMU_DBG_NFO_QCH_CON_ABUS_QCH_L2CLK ((S5JS100_ACMU_BASE + 0x7040))
#define ACMU_DBG_NFO_QCH_CON_APMEM_QCH  ((S5JS100_ACMU_BASE + 0x7044))
#define ACMU_DBG_NFO_QCH_CON_AP_CMU_QCH ((S5JS100_ACMU_BASE + 0x7048))
#define ACMU_DBG_NFO_QCH_CON_BS_MEM_QCH ((S5JS100_ACMU_BASE + 0x704c))
#define ACMU_DBG_NFO_QCH_CON_BS_QCH ((S5JS100_ACMU_BASE + 0x7050))
#define ACMU_DBG_NFO_QCH_CON_CM7_QCH    ((S5JS100_ACMU_BASE + 0x7054))
#define ACMU_DBG_NFO_QCH_CON_I2C0_QCH   ((S5JS100_ACMU_BASE + 0x7058))
#define ACMU_DBG_NFO_QCH_CON_PDMA_QCH   ((S5JS100_ACMU_BASE + 0x705c))
#define ACMU_DBG_NFO_QCH_CON_PWM_QCH_L3CLK  ((S5JS100_ACMU_BASE + 0x7060))
#define ACMU_DBG_NFO_QCH_CON_SDIO_QCH   ((S5JS100_ACMU_BASE + 0x7064))
#define ACMU_DBG_NFO_QCH_CON_SSS_QCH    ((S5JS100_ACMU_BASE + 0x7068))
#define ACMU_DBG_NFO_QCH_CON_USI0_QCH   ((S5JS100_ACMU_BASE + 0x706c))
#define ACMU_DBG_NFO_QCH_CON_USI1_QCH   ((S5JS100_ACMU_BASE + 0x7070))

#define SCMU_PLL_LOCKTIME_UPLL  ((S5JS100_SCMU_BASE + 0x0))
#define SCMU_PLL_CON0_UPLL  ((S5JS100_SCMU_BASE + 0x100))
#define SCMU_PLL_CON1_UPLL  ((S5JS100_SCMU_BASE + 0x104))
#define SCMU_PLL_CON2_UPLL  ((S5JS100_SCMU_BASE + 0x108))
#define SCMU_PLL_CON4_UPLL  ((S5JS100_SCMU_BASE + 0x110))
#define SCMU_SYS_SCMU_CONTROLLER_OPTION ((S5JS100_SCMU_BASE + 0x800))
#define SCMU_SPARE0 ((S5JS100_SCMU_BASE + 0x880))
#define SCMU_VER    ((S5JS100_SCMU_BASE + 0x890))
#define SCMU_SCMU_MON_CLK   ((S5JS100_SCMU_BASE + 0x9e0))
#define SCMU_MR_REGISTER_A04    ((S5JS100_SCMU_BASE + 0xa04))
#define SCMU_CLK_CON_DIV_CKDIVS_UPLL_CLK_AP ((S5JS100_SCMU_BASE + 0x1800))
#define SCMU_CLK_CON_DIV_CKDIVS_UPLL_CLK_CP ((S5JS100_SCMU_BASE + 0x1804))
#define SCMU_CLK_CON_DIV_CKDIVS_UPLL_CLK_GNSS   ((S5JS100_SCMU_BASE + 0x1808))
#define SCMU_CLK_CON_DIV_CKDIVS_UPLL_CLK_MIF    ((S5JS100_SCMU_BASE + 0x180c))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_EFUSE_IPCLKPORT_CLK    ((S5JS100_SCMU_BASE + 0x2000))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_EFUSE_IPCLKPORT_PCLK   ((S5JS100_SCMU_BASE + 0x2004))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_GNSS_IPCLKPORT_CLK ((S5JS100_SCMU_BASE + 0x2008))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_PADCON_IPCLKPORT_PCLK  ((S5JS100_SCMU_BASE + 0x200c))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_PMU_SYS_IPCLKPORT_PCLK ((S5JS100_SCMU_BASE + 0x2010))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_SYSBUS_IPCLKPORT_PCLK  ((S5JS100_SCMU_BASE + 0x2014))
#define SCMU_CLK_CON_GAT_CLK_SYS_UID_SYS_CMU_IPCLKPORT_PCLK ((S5JS100_SCMU_BASE + 0x2018))
#define SCMU_CLK_CON_GAT_CP_SRC_CLK ((S5JS100_SCMU_BASE + 0x201c))
#define SCMU_CLK_CON_GAT_GNSS_SRC_CLK   ((S5JS100_SCMU_BASE + 0x2020))
#define SCMU_CLK_CON_GAT_MIF_SRC_CLK    ((S5JS100_SCMU_BASE + 0x2024))
#define SCMU_DMYQCH_CON_EFUSE_QCH_CLK   ((S5JS100_SCMU_BASE + 0x3000))
#define SCMU_DMYQCH_CON_GNSS_QCH    ((S5JS100_SCMU_BASE + 0x3004))
#define SCMU_DMYQCH_CON_PADCON_QCH  ((S5JS100_SCMU_BASE + 0x3008))
#define SCMU_DMYQCH_CON_PMU_SYS_QCH ((S5JS100_SCMU_BASE + 0x300c))
#define SCMU_DMYQCH_CON_SYSBUS_QCH  ((S5JS100_SCMU_BASE + 0x3010))
#define SCMU_QCH_CON_EFUSE_QCH_PCLK ((S5JS100_SCMU_BASE + 0x3014))
#define SCMU_QCH_CON_SYS_CMU_QCH    ((S5JS100_SCMU_BASE + 0x3018))
#define SCMU_QUEUE_CTRL_REG_SYS_CMU ((S5JS100_SCMU_BASE + 0x3c00))
#define SCMU_DBG_NFO_UPLL   ((S5JS100_SCMU_BASE + 0x4100))
#define SCMU_DBG_NFO_CKDIVS_UPLL_CLK_AP ((S5JS100_SCMU_BASE + 0x5800))
#define SCMU_DBG_NFO_CKDIVS_UPLL_CLK_CP ((S5JS100_SCMU_BASE + 0x5804))
#define SCMU_DBG_NFO_CKDIVS_UPLL_CLK_GNSS   ((S5JS100_SCMU_BASE + 0x5808))
#define SCMU_DBG_NFO_CKDIVS_UPLL_CLK_MIF    ((S5JS100_SCMU_BASE + 0x580c))
#define SCMU_DBG_NFO_CLK_SYS_UID_EFUSE_IPCLKPORT_CLK    ((S5JS100_SCMU_BASE + 0x6000))
#define SCMU_DBG_NFO_CLK_SYS_UID_EFUSE_IPCLKPORT_PCLK   ((S5JS100_SCMU_BASE + 0x6004))
#define SCMU_DBG_NFO_CLK_SYS_UID_GNSS_IPCLKPORT_CLK ((S5JS100_SCMU_BASE + 0x6008))
#define SCMU_DBG_NFO_CLK_SYS_UID_PADCON_IPCLKPORT_PCLK  ((S5JS100_SCMU_BASE + 0x600c))
#define SCMU_DBG_NFO_CLK_SYS_UID_PMU_SYS_IPCLKPORT_PCLK ((S5JS100_SCMU_BASE + 0x6010))
#define SCMU_DBG_NFO_CLK_SYS_UID_SYSBUS_IPCLKPORT_PCLK  ((S5JS100_SCMU_BASE + 0x6014))
#define SCMU_DBG_NFO_CLK_SYS_UID_SYS_CMU_IPCLKPORT_PCLK ((S5JS100_SCMU_BASE + 0x6018))
#define SCMU_DBG_NFO_CP_SRC_CLK ((S5JS100_SCMU_BASE + 0x601c))
#define SCMU_DBG_NFO_GNSS_SRC_CLK   ((S5JS100_SCMU_BASE + 0x6020))
#define SCMU_DBG_NFO_MIF_SRC_CLK    ((S5JS100_SCMU_BASE + 0x6024))
#define SCMU_DBG_NFO_DMYQCH_CON_EFUSE_QCH_CLK   ((S5JS100_SCMU_BASE + 0x7000))
#define SCMU_DBG_NFO_DMYQCH_CON_GNSS_QCH    ((S5JS100_SCMU_BASE + 0x7004))
#define SCMU_DBG_NFO_DMYQCH_CON_PADCON_QCH  ((S5JS100_SCMU_BASE + 0x7008))
#define SCMU_DBG_NFO_DMYQCH_CON_PMU_SYS_QCH ((S5JS100_SCMU_BASE + 0x700c))
#define SCMU_DBG_NFO_DMYQCH_CON_SYSBUS_QCH  ((S5JS100_SCMU_BASE + 0x7010))
#define SCMU_DBG_NFO_QCH_CON_EFUSE_QCH_PCLK ((S5JS100_SCMU_BASE + 0x7014))
#define SCMU_DBG_NFO_QCH_CON_SYS_CMU_QCH    ((S5JS100_SCMU_BASE + 0x7018))

#define MIFCMU_MIF_MIFCMU_CONTROLLER_OPTION ((S5JS100_MIFCMU_BASE + 0x800))
#define MIFCMU_SPARE0   ((S5JS100_MIFCMU_BASE + 0x880))
#define MIFCMU_VER  ((S5JS100_MIFCMU_BASE + 0x890))
#define MIFCMU_MIFCMU_MON_CLK   ((S5JS100_MIFCMU_BASE + 0x9e0))
#define MIFCMU_MR_REGISTER_A00  ((S5JS100_MIFCMU_BASE + 0xa00))
#define MIFCMU_MR_REGISTER_A04  ((S5JS100_MIFCMU_BASE + 0xa04))
#define MIFCMU_CLK_CON_DIV_CKDIVF_QSPI_CLK  ((S5JS100_MIFCMU_BASE + 0x1800))
#define MIFCMU_CLK_CON_DIV_CKDIVF_SMC_CLK   ((S5JS100_MIFCMU_BASE + 0x1804))
#define MIFCMU_CLK_CON_DIV_CKDIVF_UART0_CLK ((S5JS100_MIFCMU_BASE + 0x1808))
#define MIFCMU_CLK_CON_DIV_CKDIVF_UART1_CLK ((S5JS100_MIFCMU_BASE + 0x180c))
#define MIFCMU_CLK_CON_DIV_MULTI2_CKDIVF_MIF_SRC_CLK    ((S5JS100_MIFCMU_BASE + 0x1810))
#define MIFCMU_CLK_CON_BUF_CKBUF_MIF_SRC_CLK    ((S5JS100_MIFCMU_BASE + 0x2000))
#define MIFCMU_CLK_CON_GAT_CLK_MIF_UID_GPADCIF_IPCLKPORT_CLK    ((S5JS100_MIFCMU_BASE + 0x2004))
#define MIFCMU_CLK_CON_GAT_CLK_MIF_UID_MIF_CMU_IPCLKPORT_PCLK   ((S5JS100_MIFCMU_BASE + 0x2008))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_GPADCIF_IPCLKPORT_S0_L3CLK  ((S5JS100_MIFCMU_BASE + 0x200c))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_GPADCIF_IPCLKPORT_S1_L3CLK  ((S5JS100_MIFCMU_BASE + 0x2010))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_GPIO_IPCLKPORT_L3CLK    ((S5JS100_MIFCMU_BASE + 0x2014))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_IPCMEM_IPCLKPORT_L2CLK  ((S5JS100_MIFCMU_BASE + 0x2018))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MBOX_IPCLKPORT_L3CLK    ((S5JS100_MIFCMU_BASE + 0x201c))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_ACPU2MIF_LH_MI_L2CLK   ((S5JS100_MIFCMU_BASE + 0x2020))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_BAAW_SFR_L3CLK ((S5JS100_MIFCMU_BASE + 0x2024))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_L2CLK  ((S5JS100_MIFCMU_BASE + 0x2028))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_MCPU2MIF_LH_MI_L2CLK   ((S5JS100_MIFCMU_BASE + 0x202c))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_ACPU2MIF_L2CLK    ((S5JS100_MIFCMU_BASE + 0x2030))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_ACPU2MIF_L3CLK    ((S5JS100_MIFCMU_BASE + 0x2034))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_MCPU2MIF_L2CLK    ((S5JS100_MIFCMU_BASE + 0x2038))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_MCPU2MIF_L3CLK    ((S5JS100_MIFCMU_BASE + 0x203c))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_QSPI_IPCLKPORT_CLK  ((S5JS100_MIFCMU_BASE + 0x2040))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_QSPI_IPCLKPORT_L2CLK    ((S5JS100_MIFCMU_BASE + 0x2044))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_SMC_IPCLKPORT_CLK   ((S5JS100_MIFCMU_BASE + 0x2048))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_SMC_IPCLKPORT_L2CLK ((S5JS100_MIFCMU_BASE + 0x204c))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_SYSCFG_IPCLKPORT_L3CLK  ((S5JS100_MIFCMU_BASE + 0x2050))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_UART0_IPCLKPORT_CLK ((S5JS100_MIFCMU_BASE + 0x2054))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_UART0_IPCLKPORT_L3CLK   ((S5JS100_MIFCMU_BASE + 0x2058))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_UART1_IPCLKPORT_CLK ((S5JS100_MIFCMU_BASE + 0x205c))
#define MIFCMU_CLK_CON_GAT_GOUT_MIF_UID_UART1_IPCLKPORT_L3CLK   ((S5JS100_MIFCMU_BASE + 0x2060))
#define MIFCMU_DMYQCH_CON_GPADCIF_QCH_CLK   ((S5JS100_MIFCMU_BASE + 0x3000))
#define MIFCMU_DMYQCH_CON_GPIO_QCH  ((S5JS100_MIFCMU_BASE + 0x3004))
#define MIFCMU_DMYQCH_CON_MIFBUS_QCH_PPMU_ACPU2MIF_CLK  ((S5JS100_MIFCMU_BASE + 0x3008))
#define MIFCMU_DMYQCH_CON_MIFBUS_QCH_PPMU_MCPU2MIF_CLK  ((S5JS100_MIFCMU_BASE + 0x300c))
#define MIFCMU_DMYQCH_CON_QSPI_QCH  ((S5JS100_MIFCMU_BASE + 0x3010))
#define MIFCMU_DMYQCH_CON_SMC_QCH   ((S5JS100_MIFCMU_BASE + 0x3014))
#define MIFCMU_DMYQCH_CON_SYSCFG_QCH    ((S5JS100_MIFCMU_BASE + 0x3018))
#define MIFCMU_DMYQCH_CON_UART0_QCH ((S5JS100_MIFCMU_BASE + 0x301c))
#define MIFCMU_DMYQCH_CON_UART1_QCH ((S5JS100_MIFCMU_BASE + 0x3020))
#define MIFCMU_QCH_CON_GPADCIF_QCH_S0_L3CLK ((S5JS100_MIFCMU_BASE + 0x3024))
#define MIFCMU_QCH_CON_GPADCIF_QCH_S1_L3CLK ((S5JS100_MIFCMU_BASE + 0x3028))
#define MIFCMU_QCH_CON_IPCMEM_QCH   ((S5JS100_MIFCMU_BASE + 0x302c))
#define MIFCMU_QCH_CON_MBOX_QCH ((S5JS100_MIFCMU_BASE + 0x3030))
#define MIFCMU_QCH_CON_MIFBUS_QCH_ACPU2MIF_LH_MI_L2CLK  ((S5JS100_MIFCMU_BASE + 0x3034))
#define MIFCMU_QCH_CON_MIFBUS_QCH_BAAW_SFR_L3CLK    ((S5JS100_MIFCMU_BASE + 0x3038))
#define MIFCMU_QCH_CON_MIFBUS_QCH_L2CLK ((S5JS100_MIFCMU_BASE + 0x303c))
#define MIFCMU_QCH_CON_MIFBUS_QCH_MCPU2MIF_LH_MI_L2CLK  ((S5JS100_MIFCMU_BASE + 0x3040))
#define MIFCMU_QCH_CON_MIF_CMU_QCH  ((S5JS100_MIFCMU_BASE + 0x3044))
#define MIFCMU_QUEUE_CTRL_REG_MIF_CMU   ((S5JS100_MIFCMU_BASE + 0x3c00))
#define MIFCMU_DBG_NFO_CKDIVF_MIF_SRC_CLK   ((S5JS100_MIFCMU_BASE + 0x5800))
#define MIFCMU_DBG_NFO_CKDIVF_QSPI_CLK  ((S5JS100_MIFCMU_BASE + 0x5804))
#define MIFCMU_DBG_NFO_CKDIVF_SMC_CLK   ((S5JS100_MIFCMU_BASE + 0x5808))
#define MIFCMU_DBG_NFO_CKDIVF_UART0_CLK ((S5JS100_MIFCMU_BASE + 0x580c))
#define MIFCMU_DBG_NFO_CKDIVF_UART1_CLK ((S5JS100_MIFCMU_BASE + 0x5810))
#define MIFCMU_DBG_NFO_CKBUF_MIF_SRC_CLK    ((S5JS100_MIFCMU_BASE + 0x6000))
#define MIFCMU_DBG_NFO_CLK_MIF_UID_GPADCIF_IPCLKPORT_CLK    ((S5JS100_MIFCMU_BASE + 0x6004))
#define MIFCMU_DBG_NFO_CLK_MIF_UID_MIF_CMU_IPCLKPORT_PCLK   ((S5JS100_MIFCMU_BASE + 0x6008))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_GPADCIF_IPCLKPORT_S0_L3CLK  ((S5JS100_MIFCMU_BASE + 0x600c))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_GPADCIF_IPCLKPORT_S1_L3CLK  ((S5JS100_MIFCMU_BASE + 0x6010))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_GPIO_IPCLKPORT_L3CLK    ((S5JS100_MIFCMU_BASE + 0x6014))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_IPCMEM_IPCLKPORT_L2CLK  ((S5JS100_MIFCMU_BASE + 0x6018))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MBOX_IPCLKPORT_L3CLK    ((S5JS100_MIFCMU_BASE + 0x601c))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_ACPU2MIF_LH_MI_L2CLK   ((S5JS100_MIFCMU_BASE + 0x6020))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_BAAW_SFR_L3CLK ((S5JS100_MIFCMU_BASE + 0x6024))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_L2CLK  ((S5JS100_MIFCMU_BASE + 0x6028))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_MCPU2MIF_LH_MI_L2CLK   ((S5JS100_MIFCMU_BASE + 0x602c))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_ACPU2MIF_L2CLK    ((S5JS100_MIFCMU_BASE + 0x6030))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_ACPU2MIF_L3CLK    ((S5JS100_MIFCMU_BASE + 0x6034))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_MCPU2MIF_L2CLK    ((S5JS100_MIFCMU_BASE + 0x6038))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_MIFBUS_IPCLKPORT_PPMU_MCPU2MIF_L3CLK    ((S5JS100_MIFCMU_BASE + 0x603c))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_QSPI_IPCLKPORT_CLK  ((S5JS100_MIFCMU_BASE + 0x6040))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_QSPI_IPCLKPORT_L2CLK    ((S5JS100_MIFCMU_BASE + 0x6044))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_SMC_IPCLKPORT_CLK   ((S5JS100_MIFCMU_BASE + 0x6048))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_SMC_IPCLKPORT_L2CLK ((S5JS100_MIFCMU_BASE + 0x604c))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_SYSCFG_IPCLKPORT_L3CLK  ((S5JS100_MIFCMU_BASE + 0x6050))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_UART0_IPCLKPORT_CLK ((S5JS100_MIFCMU_BASE + 0x6054))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_UART0_IPCLKPORT_L3CLK   ((S5JS100_MIFCMU_BASE + 0x6058))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_UART1_IPCLKPORT_CLK ((S5JS100_MIFCMU_BASE + 0x605c))
#define MIFCMU_DBG_NFO_GOUT_MIF_UID_UART1_IPCLKPORT_L3CLK   ((S5JS100_MIFCMU_BASE + 0x6060))
#define MIFCMU_DBG_NFO_DMYQCH_CON_GPADCIF_QCH_CLK   ((S5JS100_MIFCMU_BASE + 0x7000))
#define MIFCMU_DBG_NFO_DMYQCH_CON_GPIO_QCH  ((S5JS100_MIFCMU_BASE + 0x7004))
#define MIFCMU_DBG_NFO_DMYQCH_CON_MIFBUS_QCH_PPMU_ACPU2MIF_CLK  ((S5JS100_MIFCMU_BASE + 0x7008))
#define MIFCMU_DBG_NFO_DMYQCH_CON_MIFBUS_QCH_PPMU_MCPU2MIF_CLK  ((S5JS100_MIFCMU_BASE + 0x700c))
#define MIFCMU_DBG_NFO_DMYQCH_CON_QSPI_QCH  ((S5JS100_MIFCMU_BASE + 0x7010))
#define MIFCMU_DBG_NFO_DMYQCH_CON_SMC_QCH   ((S5JS100_MIFCMU_BASE + 0x7014))
#define MIFCMU_DBG_NFO_DMYQCH_CON_SYSCFG_QCH    ((S5JS100_MIFCMU_BASE + 0x7018))
#define MIFCMU_DBG_NFO_DMYQCH_CON_UART0_QCH ((S5JS100_MIFCMU_BASE + 0x701c))
#define MIFCMU_DBG_NFO_DMYQCH_CON_UART1_QCH ((S5JS100_MIFCMU_BASE + 0x7020))
#define MIFCMU_DBG_NFO_QCH_CON_GPADCIF_QCH_S0_L3CLK ((S5JS100_MIFCMU_BASE + 0x7024))
#define MIFCMU_DBG_NFO_QCH_CON_GPADCIF_QCH_S1_L3CLK ((S5JS100_MIFCMU_BASE + 0x7028))
#define MIFCMU_DBG_NFO_QCH_CON_IPCMEM_QCH   ((S5JS100_MIFCMU_BASE + 0x702c))
#define MIFCMU_DBG_NFO_QCH_CON_MBOX_QCH ((S5JS100_MIFCMU_BASE + 0x7030))
#define MIFCMU_DBG_NFO_QCH_CON_MIFBUS_QCH_ACPU2MIF_LH_MI_L2CLK  ((S5JS100_MIFCMU_BASE + 0x7034))
#define MIFCMU_DBG_NFO_QCH_CON_MIFBUS_QCH_BAAW_SFR_L3CLK    ((S5JS100_MIFCMU_BASE + 0x7038))
#define MIFCMU_DBG_NFO_QCH_CON_MIFBUS_QCH_L2CLK ((S5JS100_MIFCMU_BASE + 0x703c))
#define MIFCMU_DBG_NFO_QCH_CON_MIFBUS_QCH_MCPU2MIF_LH_MI_L2CLK  ((S5JS100_MIFCMU_BASE + 0x7040))
#define MIFCMU_DBG_NFO_QCH_CON_MIF_CMU_QCH  ((S5JS100_MIFCMU_BASE + 0x7044))

#endif                          /* __ARCH_ARM_SRC_S5JS100_S5JS100_CMU_H__ */
