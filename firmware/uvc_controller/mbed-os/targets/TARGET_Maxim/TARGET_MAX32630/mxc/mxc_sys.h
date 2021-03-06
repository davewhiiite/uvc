/**
 * @file  mxc_sys.h
 * @brief Registers, Bit Masks and Bit Positions for the System Clock Management module.
 */
 /* ****************************************************************************
 * Copyright (C) 2016 Maxim Integrated Products, Inc., All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL MAXIM INTEGRATED BE LIABLE FOR ANY CLAIM, DAMAGES
 * OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Except as contained in this notice, the name of Maxim Integrated
 * Products, Inc. shall not be used except as stated in the Maxim Integrated
 * Products, Inc. Branding Policy.
 *
 * The mere transfer of this software does not imply any licenses
 * of trade secrets, proprietary technology, copyrights, patents,
 * trademarks, maskwork rights, or any other form of intellectual
 * property whatsoever. Maxim Integrated Products, Inc. retains all
 * ownership rights.
 *
 * $Date: 2016-08-24 18:33:23 -0500 (Wed, 24 Aug 2016) $
 * $Revision: 24159 $
 *
 **************************************************************************** */

/* Define to prevent redundant inclusion */
#ifndef _MXC_SYS_H_
#define _MXC_SYS_H_

/* **** Includes **** */
#include "mxc_config.h"
#include "clkman.h"
#include "ioman.h"
#include "gpio.h"
#include "i2cm_regs.h"
#include "i2cs_regs.h"
#include "tmr_regs.h"
#include "pt_regs.h"
#include "wdt_regs.h"
#include "owm_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @defgroup sys_cfg System Configuration
 * @ingroup sysconfig
 * @brief Configuration objects and functions for configuration of the system and peripherals.
 * @{
 */

/* **** Definitions **** */

/**
 * Structure type for System Configuration.
 */
typedef struct {
    clkman_scale_t clk_scale;   /**< Desired clock scale value for the peripheral */
    ioman_cfg_t io_cfg;         /**< IOMAN configuration object */
} sys_cfg_t;

/**
 * Structure type for Watchdog System Configuration.
 * @ingroup    wdt
 * @{
 */
typedef struct {
    clkman_wdt_clk_select_t clk; /**< Select the clock source for the watchdog */
    clkman_scale_t clk_scale;    /**< Desired clock scale value for the peripheral. @note clk_scale is only applied if the system clock is used as the clk. */
} sys_cfg_wdt_t;
/**@}*/

/**
 * Structure type for UART System Configuration.
 * @ingroup     uart
 */
typedef sys_cfg_t sys_cfg_uart_t;

/**
 * Structure type for I2CM System Configuration.
 * @ingroup  i2cm
 */
typedef sys_cfg_t sys_cfg_i2cm_t;

/**
 * Structure type for I2CS System Configuration.
 * @ingroup i2cs
 */
typedef sys_cfg_t sys_cfg_i2cs_t;

/**
 * Structure type for SPIM System Configuration.
 * @ingroup spim
 */
typedef sys_cfg_t sys_cfg_spim_t;

/**
 * Structure type for SPIX System Configuration.
 * @ingroup spix
 */
typedef sys_cfg_t sys_cfg_spix_t;

/**
 * Structure type for OWM System Configuration.
 * @ingroup owm
 */
typedef sys_cfg_t sys_cfg_owm_t;

/**
 * Structure type for Timer System Configuration.
 * @ingroup timer
 */
typedef gpio_cfg_t sys_cfg_tmr_t;

/**
 * Structure type for Pulse Train System Configuration.
 * @ingroup pulsetrain
 */
typedef gpio_cfg_t sys_cfg_pt_t;

/**
 * Structure type for Pulse Train Clock Scale Configuration.
 * @ingroup clkman
 * @ingroup pulsetrain
 */
typedef clkman_scale_t sys_pt_clk_scale;

/* **** Include Files **** */
/* These includes require the above types to be defined first */
#include "uart.h"
#include "spim.h"


/* **** Function Prototypes **** */

/**
 * @brief      Get the frequency of a clock scaler
 * @param      clk_scale  value of SYSTEM_SOURCE_SELECT field of \ref clkman_clk_ctrl register
 * @return     frequency in Hz
 */
uint32_t SYS_GetFreq(uint32_t clk_scale);

/**
 * @brief      Get the frequency of the CPU
 * @return     frequency in Hz
 */
uint32_t SYS_CPU_GetFreq(void);

/**
 * @brief      System level initialization for the ADC module.
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    adc
 */
int SYS_ADC_Init(void);

/**
 * @brief      System level initialization for the AES module.
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    aes
 */
int SYS_AES_Init(void);

/**
 * @brief      System level initialization for the GPIO module.
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    gpio
 */
int SYS_GPIO_Init(void);

/**
 * @brief      System level initialization for the UART module.
 * @param      uart      Pointer to UART module registers
 * @param      uart_cfg  UART configuration object
 * @param      sys_cfg   System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    uart
 */
int SYS_UART_Init(mxc_uart_regs_t *uart, const uart_cfg_t *uart_cfg, const sys_cfg_uart_t *sys_cfg);

/**
 * @brief      System level shutdown for UART module
 * @param      uart  Pointer to UART module registers
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    uart
 */
int SYS_UART_Shutdown(mxc_uart_regs_t *uart);

/**
 * @brief      Get the frequency of the UART module source clock
 * @param      uart  Pointer to UART module registers
 * @return     frequency in Hz
 * @ingroup    uart
 */
uint32_t SYS_UART_GetFreq(mxc_uart_regs_t *uart);

/**
 * @brief      System level initialization for I2CM module.
 * @param      i2cm  Pointer to I2CM module registers
 * @param      cfg   System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    i2cm
 */
int SYS_I2CM_Init(mxc_i2cm_regs_t *i2cm, const sys_cfg_i2cm_t *cfg);

/**
 * @brief      System level shutdown for I2CM module
 * @param      i2cm  Pointer to I2CM module registers
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    i2cm
 */
int SYS_I2CM_Shutdown(mxc_i2cm_regs_t *i2cm);

/**
 * @brief      Get the frequency of the I2CM module source clock
 * @param      i2cm  Pointer to I2CM module registers
 * @return     frequency in Hz
 * @ingroup    i2cm
 */
uint32_t SYS_I2CM_GetFreq(mxc_i2cm_regs_t *i2cm);

/**
 * @brief      System level initialization for I2CS module.
 * @param      i2cs  Pointer to I2CS module registers
 * @param      cfg   System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    i2cs
 */
int SYS_I2CS_Init(mxc_i2cs_regs_t *i2cs, const sys_cfg_i2cs_t *cfg);

/**
 * @brief      System level shutdown for I2CS module
 * @param      i2cs  Pointer to I2CS module registers
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    i2cs
 */
int SYS_I2CS_Shutdown(mxc_i2cs_regs_t *i2cs);

/**
 * @brief      Get the frequency of the I2CS module source clock
 * @param      i2cs  Pointer to I2CS module registers
 * @return     frequency in Hz
 * @ingroup    i2cs
 */
uint32_t SYS_I2CS_GetFreq(mxc_i2cs_regs_t *i2cs);

/**
 * @brief      System level initialization for SPIM module.
 * @param      spim      Pointer to SPIM module registers
 * @param      spim_cfg  SPIM configuration object
 * @param      sys_cfg   System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    spim
 */
int SYS_SPIM_Init(mxc_spim_regs_t *spim, const spim_cfg_t *spim_cfg, const sys_cfg_spim_t *sys_cfg);

/**
 * @brief      System level shutdown for SPIM module
 * @param      spim  Pointer to SPIM module registers
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    spim
 */
int SYS_SPIM_Shutdown(mxc_spim_regs_t *spim);

/**
 * @brief      Get the frequency of the SPIM module source clock
 * @param      spim  Pointer to SPIM module registers
 * @return     frequency in Hz
 * @ingroup    spim
 */
uint32_t SYS_SPIM_GetFreq(mxc_spim_regs_t *spim);

/**
 * @brief      System level initialization for SPIX module.
 * @param      sys_cfg  System configuration object
 * @param      baud     Baud rate for clock divider configuration
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    spix
 */
int SYS_SPIX_Init(const sys_cfg_spix_t *sys_cfg, uint32_t baud);

/**
 * @brief      System level shutdown for SPIX module
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    spix
 */
int SYS_SPIX_Shutdown(void);

/**
 * @brief      Get the frequency of the SPIX module source clock
 * @return     frequency in Hz
 * @ingroup    spix
 */
uint32_t SYS_SPIX_GetFreq(void);

/**
 * @brief      System level initialization for OWM module.
 * @param      owm      Pointer to OWM module registers
 * @param      sys_cfg  System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    owm
 */
int SYS_OWM_Init(mxc_owm_regs_t *owm, const sys_cfg_owm_t *sys_cfg);

/**
 * @brief      System level shutdown for OWM module
 * @param      owm   Pointer to OWM module registers
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    owm
 */
int SYS_OWM_Shutdown(mxc_owm_regs_t *owm);

/**
 * @brief      Get the frequency of the OWM module source clock
 * @param      owm   Pointer to OWM module registers
 * @return     frequency in Hz
 * @ingroup    owm
 */
uint32_t SYS_OWM_GetFreq(mxc_owm_regs_t *owm);

/**
 * @brief      System level initialization for TMR module.
 * @param      tmr   Pointer to TMR module registers
 * @param      cfg   System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    timer
 */
int SYS_TMR_Init(mxc_tmr_regs_t *tmr, const sys_cfg_tmr_t *cfg);

/**
 * @brief      Get the frequency of the TMR module source clock
 * @param      tmr  Pointer to TMR module registers
 * @return     frequency in Hz
 * @ingroup    timer
 */
uint32_t SYS_TMR_GetFreq(mxc_tmr_regs_t *tmr);

/**
 * @brief      Get the frequency of the Pulse Train module source clock
 * @return     frequency in Hz
 * @ingroup    pulsetrain
 */
uint32_t SYS_PT_GetFreq(void);

/**
 * @brief      Initialize the global pulse train clock scale
 * @param      clk_scale  scale the system clock for the PT clock
 * @ingroup    pulsetrain
 */
void SYS_PT_Init(sys_pt_clk_scale clk_scale);

/**
 * @brief      System level initialization for Pulse Train module.
 * @param      pt    Pointer to PT module registers
 * @param      cfg   System configuration object
 * @return     #E_NO_ERROR if everything is successful
 * @ingroup    pulsetrain
 */
int SYS_PT_Config(mxc_pt_regs_t *pt, const sys_cfg_pt_t *cfg);

/**
 * @brief      System level initialization for USB device.
 * @param      enable  1 to enable the peripheral, 0 to disable.
 * @ingroup    usb
 */
void SYS_USB_Enable(uint8_t enable);

/**
 * @brief      System Tick Configuration Helper
 *
 *             The function enables selection of the external clock source for
 *             the System Tick Timer. It initializes the System Timer and its
 *             interrupt, and starts the System Tick Timer. Counter is in free
 *             running mode to generate periodic interrupts.
 *
 * @param      ticks    Number of ticks between two interrupts.
 * @param      clk_src  Selects between default SystemClock or External Clock.
 *                      - 0 Use external clock source
 *                      - 1 SystemClock
 * @return     #E_NO_ERROR  Function succeeded.
 * @return     #E_INVALID   Invalid reload value requested.
 *
 *             See CLKMAN_SetRTOSMode(uint8_t enable) if using the external
 *             clock source to drive the System Tick Timer
 */
int SYS_SysTick_Config(uint32_t ticks, int clk_src);

/**
 * @brief      Disable System Tick timer
 */
__STATIC_INLINE void SYS_SysTick_Disable(void)
{
	SysTick->CTRL = 0;
}

/**
 * @brief      Delay a requested number of SysTick Timer Ticks.
 * @param      ticks  Number of System Ticks to delay.
 * @note       This delay function is based on the clock used for the SysTick
 *             timer if the SysTick timer is enabled. If the SysTick timer is
 *             not enabled, the current SysTick registers are saved and the
 *             timer will use the SystemClock as the source for the delay. The
 *             delay is measured in clock ticks and is not based on the SysTick
 *             interval.
 * @return     #E_NO_ERROR if everything is successful
 */
int SYS_SysTick_Delay(uint32_t ticks);

/**
 * @brief      Get the frequency of the SysTick Timer
 * @return     frequency in Hz
 */
uint32_t SYS_SysTick_GetFreq(void);

/**
 * @brief      Delay a requested number of microseconds.
 * @param      us    Number of microseconds to delay.
 * @note       Calls SYS_SysTick_Delay().
 */
__STATIC_INLINE void SYS_SysTick_DelayUs(uint32_t us)
{
    SYS_SysTick_Delay((uint32_t)(((uint64_t)SYS_SysTick_GetFreq() * us) / 1000000));
}

/**
 * @brief      System level initialization for RTC module.
 * @return     #E_NO_ERROR if everything is successful
 */
int SYS_RTC_Init(void);

/**
 * @brief      Select VDDIO for the specified GPIO pin.
 * @ingroup    gpio
 */
void SYS_IOMAN_UseVDDIO(const gpio_cfg_t *cfg);

/**
 * @brief      Select VDDIOH for the specified GPIO pin.
 */
void SYS_IOMAN_UseVDDIOH(const gpio_cfg_t *cfg);

/**
 * @brief      System level initialization for Watchdog module.
 * @param      wdt   Pointer to Watchdog module registers
 * @param      cfg   Watchdog System configuration object
 * @ingroup    wdt
 */
void SYS_WDT_Init(mxc_wdt_regs_t *wdt, const sys_cfg_wdt_t *cfg);

/**
 * @brief      System level initialization for PRNG module. Enable crypto clock
 *             and set divisors to 1 if disabled
 */
void SYS_PRNG_Init(void);

/**
 * @brief      System level initialization for MAA module. Enable crypto clock
 *             and set divisors to 1 if disabled
 * @ingroup    maa
 */
void SYS_MAA_Init(void);

/**
 * @brief      Gets the size of the SRAM
 * @return     size of SRAM in bytes
 */
uint32_t SYS_SRAM_GetSize(void);

/**
 * @brief      Gets the size of the Flash
 * @return     size of Flash in bytes
 */
uint32_t SYS_FLASH_GetSize(void);

/**@} end of group sys_cfg */

#ifdef __cplusplus
}
#endif

#endif /* _MXC_SYS_H_*/
