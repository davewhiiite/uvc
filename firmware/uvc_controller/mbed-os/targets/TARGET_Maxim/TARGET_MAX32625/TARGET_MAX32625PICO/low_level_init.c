/*******************************************************************************
 * Copyright (C) 2017 Maxim Integrated Products, Inc., All Rights Reserved.
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
 *******************************************************************************
 */

#include "cmsis.h"
#include "ioman_regs.h"
#include "gpio_regs.h"

//******************************************************************************
// This function will get called early in system initialization
void low_level_init(void)
{
    /* The MAX32625PICO board utilizes a bootloader that can leave some
     * peripherals in a partially configured state.  This function resets
     * those to allow proper initialization.
     */
    MXC_IOMAN->uart0_req = 0x0;         // Clear any requests
    MXC_IOMAN->uart1_req = 0x0;         // Clear any requests

    MXC_GPIO->inten[2] = 0x0;           // Clear interrupt enable
    MXC_GPIO->int_mode[2] = 0x0;        // Clear interrupt mode
    MXC_GPIO->in_mode[2] = 0x22222222;  // Clear input mode
    MXC_GPIO->out_val[2] = 0x0;         // Clear output value
    MXC_GPIO->out_mode[2] = 0xFFFFFFFF; // Clear output mode
}
