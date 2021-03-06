/**
 * @file icc.c
 * @brief      This file contains the function implementations for the
 *             Instruction Cache Controller.
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
 * $Date: 2016-08-15 11:26:49 -0500 (Mon, 15 Aug 2016) $
 * $Revision: 24063 $
 *
 *************************************************************************** */


/* **** Includes **** */
#include "mxc_config.h"
#include "icc.h"
/**
 * @ingroup icc
 * @{
 */

/* **** Definitions **** */

/* **** Globals **** */

/* **** Functions **** */

/* ************************************************************************* */
void ICC_Enable(void)
{
    /* Invalidate cache and wait until ready */
    MXC_ICC->invdt_all = 1;
    while (!(MXC_ICC->ctrl_stat & MXC_F_ICC_CTRL_STAT_READY));

    /* Enable cache */
    MXC_ICC->ctrl_stat |= MXC_F_ICC_CTRL_STAT_ENABLE;

    /* Must invalidate a second time for proper use */
    MXC_ICC->invdt_all = 1;
}

/* ************************************************************************* */
void ICC_Disable(void)
{
    MXC_ICC->ctrl_stat &= ~MXC_F_ICC_CTRL_STAT_ENABLE;
}
/**@} end of group icc */
