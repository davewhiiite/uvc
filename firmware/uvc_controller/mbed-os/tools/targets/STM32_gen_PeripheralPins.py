#!/usr/bin/env python

"""
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 *
 * Copyright (c) 2016-2020 STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
"""

import argparse
import datetime
import fnmatch
import json
import os
import re
import sys
import textwrap
from xml.dom.minidom import parse, Node
from argparse import RawTextHelpFormatter

GENPINMAP_VERSION = "1.12"

ADD_DEVICE_IF = 0
ADD_QSPI_FEATURE = 1
DEBUG_PRINT = 0

mcu_file=""
mcu_list = []       #'name'
io_list = []        #'PIN','name'
adclist = []        #'PIN','name','ADCSignal'
daclist = []        #'PIN','name','DACSignal'
i2cscl_list = []    #'PIN','name','I2CSCLSignal'
i2csda_list = []    #'PIN','name','I2CSDASignal'
pwm_list = []       #'PIN','name','PWM'
uarttx_list = []    #'PIN','name','UARTtx'
uartrx_list = []    #'PIN','name','UARTrx'
uartcts_list = []   #'PIN','name','UARTcts'
uartrts_list = []   #'PIN','name','UARTrts'
spimosi_list = []   #'PIN','name','SPIMOSI'
spimiso_list = []   #'PIN','name','SPIMISO'
spissel_list = []   #'PIN','name','SPISSEL'
spisclk_list = []   #'PIN','name','SPISCLK'
cantd_list = []     #'PIN','name','CANTD'
canrd_list = []     #'PIN','name','CANRD'
eth_list = []       #'PIN','name','ETH'
quadspidata0_list = []      #'PIN','name','QUADSPIDATA0'
quadspidata1_list = []      #'PIN','name','QUADSPIDATA1'
quadspidata2_list = []      #'PIN','name','QUADSPIDATA2'
quadspidata3_list = []      #'PIN','name','QUADSPIDATA3'
quadspisclk_list = []      #'PIN','name','QUADSPISCLK'
quadspissel_list = []      #'PIN','name','QUADSPISSEL'
usb_list = []        # 'PIN','name','USB'
usb_otgfs_list = []  # 'PIN','name','USB'
usb_otghs_list = []  # 'PIN','name','USB'
osc_list = []      #'PIN','name','OSC'
sys_list = []      #'PIN','name','SYS'

STDIO_list = ["", ""] # TX , RX
LED_list   = []
BUTTON_list   = []

TIM_MST_LIST = {
# Timer used for us ticker is hardcoded in this script
# Default is TIM5
"F0":"TIM2",
"F030":"TIM1",  # overwrite previous default F0
"F05":"TIM1",  # overwrite previous default F0
"F070":"TIM1", # overwrite previous default F0
"F1":"TIM4",
"F3":"TIM2",
"L0":"TIM21",
"G0":"TIM2",
"G070":"TIM3",
"G43":"TIM2",
"G471":"TIM2",
"G49":"TIM2",
"G4A":"TIM2",
"L10":"TIM2",
"L152R(6-8-B)":"TIM2",
"L41":"TIM2",
"L43":"TIM2",
"L45":"TIM2",

"WB":"TIM16"
}

TIM_DUALCORE_LIST = { # Timer used for us ticker is hardcoded in this script
"H745":"TIM2",
"H747":"TIM2",
"H750":"TIM2",
"H755":"TIM2"
}

VCP_UART_LIST = { # Used interface is HW option
"Nucleo_NUCLEO-L552ZE-Q":"LPUART1",
"Discovery_STM32L4R9I":"USART2",
"Discovery_STM32L496G":"USART2"
}

def print_debug(console_line):
    if DEBUG_PRINT == 1:
        print("DEBUG: %s" % console_line)

def find_gpio_file():
    res = "ERROR"
    itemlist = xml_mcu.getElementsByTagName("IP")
    for s in itemlist:
        a = s.attributes["Name"].value
        if "GPIO" in a:
            res = s.attributes["Version"].value
    return res


def get_gpio_af_num(pintofind, iptofind):
    if "STM32F10" in mcu_file:
        return get_gpio_af_numF1(pintofind, iptofind)
    i = 0
    mygpioaf = ""
    for n in xml_gpio.documentElement.childNodes:
        i += 1
        j = 0
        if n.nodeType == Node.ELEMENT_NODE:
            for firstlevel in n.attributes.items():
                # if 'PB7' in firstlevel:
                if pintofind == firstlevel[1]:
                    # n = pin node found
                    for m in n.childNodes:
                        j += 1
                        k = 0
                        if m.nodeType == Node.ELEMENT_NODE:
                            for secondlevel in m.attributes.items():
                                k += 1
                                # if 'I2C1_SDA' in secondlevel:
                                if iptofind in secondlevel:
                                    # m = IP node found
                                    for p in m.childNodes:
                                        if p.nodeType == Node.ELEMENT_NODE:
                                            # p node of 'Specific parameter'
                                            for myc in p.childNodes:
                                                if myc.nodeType == Node.ELEMENT_NODE:
                                                    # myc = node of ALTERNATE
                                                    for mygpioaflist in myc.childNodes:
                                                        if mygpioaflist.data not in mygpioaf:
                                                            if mygpioaf != "":
                                                                mygpioaf += " "
                                                            mygpioaf += mygpioaflist.data
    if mygpioaf == "":
        mygpioaf = "GPIO_AF_NONE"
    return mygpioaf


def get_gpio_af_numF1(pintofind, iptofind):
    print_debug('pin to find ' + pintofind + ' ip to find ' + iptofind)
    i = 0
    mygpioaf = ""
    for n in xml_gpio.documentElement.childNodes:
        i += 1
        j = 0
        if n.nodeType == Node.ELEMENT_NODE:
            for firstlevel in n.attributes.items():
                if pintofind == firstlevel[1]:
                    # n = pin node found
                    for m in n.childNodes:
                        j += 1
                        k = 0
                        if m.nodeType == Node.ELEMENT_NODE:
                            for secondlevel in m.attributes.items():
                                k += 1
                                # if 'I2C1_SDA' in secondlevel:
                                if iptofind in secondlevel:
                                    # m = IP node found
                                    for p in m.childNodes:
                                        # p node 'RemapBlock'
                                        if (
                                            p.nodeType == Node.ELEMENT_NODE
                                            and p.hasChildNodes() is False
                                        ):
                                            if mygpioaf != "":
                                                mygpioaf += " "
                                            mygpioaf += "AFIO_NONE"
                                        else:
                                            for s in p.childNodes:
                                                if s.nodeType == Node.ELEMENT_NODE:
                                                    # s node 'Specific parameter'
                                                    for myc in s.childNodes:
                                                        if (
                                                            myc.nodeType
                                                            == Node.ELEMENT_NODE
                                                        ):
                                                            # myc = AF value
                                                            for (
                                                                mygpioaflist
                                                            ) in myc.childNodes:
                                                                if mygpioaf != "":
                                                                    mygpioaf += " "
                                                                mygpioaf += mygpioaflist.data.replace(
                                                                    "__HAL_", ""
                                                                ).replace(
                                                                    "_REMAP", ""
                                                                )
    if mygpioaf == "":
        mygpioaf = "AFIO_NONE"
    return mygpioaf.replace("AFIO_NONE", "0")\
       .replace("AFIO_SPI1_ENABLE", "1")\
       .replace("AFIO_I2C1_ENABLE", "2")\
       .replace("AFIO_USART1_ENABLE", "3")\
       .replace("AFIO_USART3_PARTIAL", "5")\
       .replace("AFIO_TIM1_PARTIAL", "6")\
       .replace("AFIO_TIM3_PARTIAL", "7")\
       .replace("AFIO_TIM2_ENABLE", "8")\
       .replace("AFIO_TIM2_PARTIAL_1", "8")\
       .replace("AFIO_TIM2_PARTIAL_2", "8")\
       .replace("AFIO_TIM3_ENABLE", "9")\
       .replace("AFIO_CAN1_2", "10")

def store_pin(pin, name):
    # store pin I/O
    p = [pin, name]
    io_list.append(p)


# function to store ADC list
def store_adc(pin, name, signal):
    adclist.append([pin, name, signal])


# function to store DAC list
def store_dac(pin, name, signal):
    daclist.append([pin, name, signal])


# function to store I2C list
def store_i2c(pin, name, signal):
    # is it SDA or SCL ?
    if "_SCL" in signal:
        i2cscl_list.append([pin, name, signal])
    if "_SDA" in signal:
        i2csda_list.append([pin, name, signal])


# function to store timers
def store_pwm(pin, name, signal):
    if "_CH" in signal:
        pwm_list.append([pin, name, signal])


# function to store Uart pins
def store_uart(pin, name, signal):
    if "_TX" in signal:
        uarttx_list.append([pin, name, signal])
    if "_RX" in signal:
        uartrx_list.append([pin, name, signal])
    if "_CTS" in signal:
        uartcts_list.append([pin, name, signal])
    if "_RTS" in signal:
        uartrts_list.append([pin, name, signal])


# function to store SPI pins
def store_spi(pin, name, signal):
    if "_MISO" in signal:
        spimiso_list.append([pin, name, signal])
    if "_MOSI" in signal:
        spimosi_list.append([pin, name, signal])
    if "_SCK" in signal:
        spisclk_list.append([pin, name, signal])
    if "_NSS" in signal:
        spissel_list.append([pin, name, signal])


# function to store CAN pins
def store_can(pin, name, signal):
    if "_RX" in signal:
        canrd_list.append([pin, name, signal])
    if "_TX" in signal:
        cantd_list.append([pin, name, signal])


# function to store ETH list
def store_eth(pin, name, signal):
    eth_list.append([pin, name, signal])


# function to store QSPI pins
def store_qspi(pin, name, signal):
    if "_IO0" in signal:
        quadspidata0_list.append([pin, name, signal])
    if "_IO1" in signal:
        quadspidata1_list.append([pin, name, signal])
    if "_IO2" in signal:
        quadspidata2_list.append([pin, name, signal])
    if "_IO3" in signal:
        quadspidata3_list.append([pin, name, signal])
    if "_CLK" in signal:
        quadspisclk_list.append([pin, name, signal])
    if "_NCS" in signal:
        quadspissel_list.append([pin, name, signal])


# function to store USB pins
def store_usb(pin, name, signal):
    if "OTG" not in signal:
        usb_list.append([pin, name, signal])
    elif signal.startswith("USB_OTG_FS"):
        usb_otgfs_list.append([pin, name, signal])
    elif signal.startswith("USB_OTG_HS"):
        usb_otghs_list.append([pin, name, signal])


# function to store OSC pins
def store_osc(pin, name, signal):
    osc_list.append([pin, name, signal])


# function to store SYS pins
def store_sys(pin, name, signal):
    sys_list.append([pin, name, signal])


def print_header():
    DATE_YEAR = datetime.datetime.now().year

    s =  ("""/* mbed Microcontroller Library
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 *
 * Copyright (c) 2016-%i STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 *
 * Automatically generated from STM32CubeMX/db/mcu/%s
 */

#include "PeripheralPins.h"
#include "mbed_toolchain.h"

//==============================================================================
// Notes
//
// - The pins mentioned Px_y_ALTz are alternative possibilities which use other
//   HW peripheral instances. You can use them the same way as any other "normal"
//   pin (i.e. PwmOut pwm(PA_7_ALT0);). These pins are not displayed on the board
//   pinout image on mbed.org.
//
// - The pins which are connected to other components present on the board have
//   the comment "Connected to xxx". The pin function may not work properly in this
//   case. These pins may not be displayed on the board pinout image on mbed.org.
//   Please read the board reference manual and schematic for more information.
//
// - Warning: pins connected to the default STDIO_UART_TX and STDIO_UART_RX pins are commented
//   See https://os.mbed.com/teams/ST/wiki/STDIO for more information.
//
//==============================================================================

""" % (DATE_YEAR, os.path.basename(input_file_name)))
    out_c_file.write( s )

    s =  ("""/* mbed Microcontroller Library
 * SPDX-License-Identifier: BSD-3-Clause
 ******************************************************************************
 *
 * Copyright (c) 2016-%i STMicroelectronics.
 * All rights reserved.
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 *
 * Automatically generated from STM32CubeMX/db/mcu/%s
 */

#ifndef MBED_PINNAMES_H
#define MBED_PINNAMES_H

#include "cmsis.h"
#include "PinNamesTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ALT0  = 0x100,
    ALT1  = 0x200,
    ALT2  = 0x300,
    ALT3  = 0x400
} ALTx;

typedef enum {

""" % (DATE_YEAR, os.path.basename(input_file_name)))
    out_h_file.write( s )


def print_footer():
    s = ("""
    // Not connected
    NC = (int)0xFFFFFFFF
} PinName;

#ifdef __cplusplus
}
#endif

#endif
""")
    out_h_file.write(s)


def print_all_lists():
    if print_list_header("ADC", "ADC", adclist, "ANALOGIN"):
        print_adc()
    if print_list_header("DAC", "DAC", daclist, "ANALOGOUT"):
        print_dac()
    if print_list_header("I2C", "I2C_SDA", i2csda_list, "I2C"):
        print_i2c(i2csda_list)
    if print_list_header("", "I2C_SCL", i2cscl_list, "I2C"):
        print_i2c(i2cscl_list)
    if print_list_header("PWM", "PWM", pwm_list, "PWMOUT"):
        print_pwm()
    if print_list_header("SERIAL", "UART_TX", uarttx_list, "SERIAL"):
        print_uart(uarttx_list)
    if print_list_header("", "UART_RX", uartrx_list, "SERIAL"):
        print_uart(uartrx_list)
    if print_list_header("", "UART_RTS", uartrts_list, "SERIAL"):
        print_uart(uartrts_list)
    if print_list_header("", "UART_CTS", uartcts_list, "SERIAL"):
        print_uart(uartcts_list)
    if print_list_header("SPI", "SPI_MOSI", spimosi_list, "SPI"):
        print_spi(spimosi_list)
    if print_list_header("", "SPI_MISO", spimiso_list, "SPI"):
        print_spi(spimiso_list)
    if print_list_header("", "SPI_SCLK", spisclk_list, "SPI"):
        print_spi(spisclk_list)
    if print_list_header("", "SPI_SSEL", spissel_list, "SPI"):
        print_spi(spissel_list)
    if print_list_header("CAN", "CAN_RD", canrd_list, "CAN"):
        print_can(canrd_list)
    if print_list_header("", "CAN_TD", cantd_list, "CAN"):
        print_can(cantd_list)
    if ADD_QSPI_FEATURE:
        if print_list_header("QUADSPI", "QSPI_DATA0", quadspidata0_list, "QSPI"):
            print_qspi(quadspidata0_list)
        if print_list_header("", "QSPI_DATA1", quadspidata1_list, "QSPI"):
            print_qspi(quadspidata1_list)
        if print_list_header("", "QSPI_DATA2", quadspidata2_list, "QSPI"):
            print_qspi(quadspidata2_list)
        if print_list_header("", "QSPI_DATA3", quadspidata3_list, "QSPI"):
            print_qspi(quadspidata3_list)
        if print_list_header("", "QSPI_SCLK", quadspisclk_list, "QSPI"):
            print_qspi(quadspisclk_list)
        if print_list_header("", "QSPI_SSEL", quadspissel_list, "QSPI"):
            print_qspi(quadspissel_list)
    if print_list_header("USBDEVICE", "USB_FS", usb_list, "USBDEVICE"):
        print_usb(usb_list)
    if print_list_header("USBDEVICE", "USB_FS", usb_otgfs_list, "USBDEVICE"):
        print_usb(usb_otgfs_list)
    if print_list_header("USBDEVICE", "USB_HS", usb_otghs_list, "USBDEVICE"):
        print_usb(usb_otghs_list)
    print_PinList(io_list)
    print_h_file(usb_list, "USB")
    print_h_file(usb_otgfs_list, "USB FS")
    print_h_file(usb_otghs_list, "USB HS")
    print_h_file(eth_list, "ETHERNET")
    print_h_file(osc_list, "OSCILLATOR")
    print_h_file(sys_list, "DEBUG")


def print_list_header(comment, name, l, switch):
    s = ""
    if len(l)>0:
        if comment:
            s += "\n//*** %s ***\n" % comment

        s += "\n"

        if name == "PWM":
            DefaultTimerCore1 = "TIM5"
            for EachTarget in TIM_MST_LIST:
                if EachTarget in mcu_file:
                    DefaultTimerCore1 = TIM_MST_LIST[EachTarget]
            s += "// %s cannot be used because already used by the us_ticker\n" % DefaultTimerCore1

            DefaultTimerCore2 = ""
            for EachTarget in TIM_DUALCORE_LIST:
                if EachTarget in mcu_file:
                    DefaultTimerCore2 = TIM_DUALCORE_LIST[EachTarget]
            if DefaultTimerCore2 != "":
                s += "// %s cannot be used because already used by the us_ticker (DUAL_CORE)\n" % DefaultTimerCore2

        if ADD_DEVICE_IF:
            s += "#if DEVICE_%s\n" % switch

        s += "MBED_WEAK const PinMap PinMap_%s[] = {\n" % name

    # else:
    #     if comment:
    #         s += "\n//*** No %s ***\n" % comment

    out_c_file.write(s)
    return len(l)


def print_adc():
    # Check GPIO version (alternate or not)
    s_pin_data = "STM_PIN_DATA_EXT(STM_MODE_ANALOG"
    # For STM32L47xxx/48xxx, it is necessary to configure
    # the GPIOx_ASCR register
    if re.match("STM32L4[78]+", mcu_file):
        s_pin_data += "_ADC_CONTROL"
    s_pin_data += ", GPIO_NOPULL, 0, "

    prev_p = ''
    alt_index = 0
    for p in adclist:
        if "IN" in p[2]:
            CommentedLine = "  "
            if p[1] in PinLabel.keys():
                if "STDIO_UART" in PinLabel[p[1]]:
                    CommentedLine = "//"
                if "RCC_OSC" in PinLabel[p[1]]:
                    CommentedLine = "//"
            if CommentedLine != "//":
                if p[0] == prev_p:
                    if "STM32F1" in mcu_file:
                        continue
                    else:
                        prev_p = p[0]
                        p[0] += '_ALT%d' % alt_index
                        store_pin(p[0], p[0])
                        alt_index += 1
                else:
                    prev_p = p[0]
                    alt_index = 0
            s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
            a = p[2].split('_')
            inst = a[0].replace("ADC", "")
            if len(inst) == 0:
                inst = '1' #single ADC for this product
            s1 += "%-7s" % ('ADC_' + inst + ',')
            chan = re.sub('IN[N|P]?', '', a[1])
            s1 += s_pin_data + chan
            s1 += ', 0)}, // ' + p[2]
            if p[1] in PinLabel.keys():
                s1 += ' // Connected to ' + PinLabel[p[1]]
            s1 += '\n'
            out_c_file.write(s1)
    out_c_file.write( """    {NC, NC, 0}
};

// !!! SECTION TO BE CHECKED WITH DEVICE REFERENCE MANUAL
// MBED_WEAK const PinMap PinMap_ADC_Internal[] = {
//     {ADC_TEMP,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 16, 0)},
//     {ADC_VREF,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 17, 0)},
//     {ADC_VBAT,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 18, 0)},
//     {NC, NC, 0}
// };
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_dac():
    for p in daclist:
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "STDIO_UART" in PinLabel[p[1]]:
                CommentedLine = "//"
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
        #p[2] : DAC_OUT1 / DAC1_OUT1
        a = p[2].split('_')
        inst = a[0].replace("DAC", "")
        b = a[1].replace("OUT", "")
        if len(inst) == 0:
            inst = '1'  # single DAC for this product
        s1 += "%-7s" % ('DAC_' + inst + ',')
        s1 += 'STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, ' + b + ', 0)}, // ' + p[2]
        if p[1] in PinLabel.keys():
            s1 += ' // Connected to ' + PinLabel[p[1]]
        s1 += '\n'
        out_c_file.write(s1)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_i2c(l):
    prev_p = ''
    alt_index = 0
    for p in l:
        result = get_gpio_af_num(p[1], p[2])
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "STDIO_UART" in PinLabel[p[1]]:
                CommentedLine = "//"
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        if CommentedLine != "//":
            if p[0] == prev_p:
                prev_p = p[0]
                p[0] += '_ALT%d' % alt_index
                store_pin(p[0], p[0])
                alt_index += 1
            else:
                prev_p = p[0]
                alt_index = 0
        s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
        # p[2] : I2C1_SDA / FMPI2C1_SDA
        if "FMP" in p[2]:
            inst = p[2].split('_')[0].replace("FMPI2C", "")
            s1 += "%-10s" % ('FMPI2C_' + inst + ',')
        else:
            inst = p[2].split('_')[0].replace("I2C", "")
            s1 += "%-7s" % ('I2C_' + inst + ',')
        s1 += 'STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, '
        r = result.split(' ')
        for af in r:
            s2 = s1 + af  + ')},'
            if p[1] in PinLabel.keys():
                s2 += ' // Connected to ' + PinLabel[p[1]]
            s2 += '\n'
            out_c_file.write(s2)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_pwm():
    prev_p = ''
    alt_index = 0

    TIM_MST = "TIM5"
    OneLineCommented = False
    for EachTarget in TIM_MST_LIST:
        if EachTarget in mcu_file:
            TIM_MST = TIM_MST_LIST[EachTarget]

    TIM_DUALCORE = "NOT_KNOWN"
    for EachTarget in TIM_DUALCORE_LIST:
        if EachTarget in mcu_file:
            TIM_DUALCORE = TIM_DUALCORE_LIST[EachTarget]

    for p in pwm_list:
        result = get_gpio_af_num(p[1], p[2])
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "STDIO_UART" in PinLabel[p[1]]:
                CommentedLine = "//"
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        if "%s_" % TIM_MST in p[2]:
            CommentedLine = "//"
            OneLineCommented = True
        if "%s_" % TIM_DUALCORE in p[2]:
            CommentedLine = "//"
        if CommentedLine != "//":
            if p[0] == prev_p:
                prev_p = p[0]
                p[0] += '_ALT%d' % alt_index
                store_pin(p[0], p[0])
                alt_index += 1
            else:
                prev_p = p[0]
                alt_index = 0
        s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
        # p[2] : TIM2_CH1 / TIM15_CH1N
        a = p[2].split('_')
        inst = a[0].replace("TIM", "PWM_")
        # if len(inst) == 3:
        #     inst += '1'
        s1 += "%-8s" % (inst + ',')
        chan = a[1].replace("CH", "")
        if chan.endswith('N'):
            neg = ', 1'
            chan = chan.strip('N')
        else:
            neg = ', 0'
        s1 += 'STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, '
        r = result.split(' ')
        prev_s1 = ""
        for af in r:
            if s1 == prev_s1:
                continue
            else:
                prev_s1 = s1
                s2 = s1 + af + ', ' + chan + neg + ')}, // ' + p[2]
                if p[1] in PinLabel.keys():
                    s2 += ' // Connected to ' + PinLabel[p[1]]
                s2 += '\n'
                out_c_file.write(s2)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if OneLineCommented == False:
        print("error: TIMER %s NOT FOUND" % TIM_MST)
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_uart(l):
    prev_p = ''
    alt_index = 0
    for p in l:
        result = get_gpio_af_num(p[1], p[2])
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        if CommentedLine != "//":
            if p[0] == prev_p:
                prev_p = p[0]
                p[0] += '_ALT%d' % alt_index
                store_pin(p[0], p[0])
                alt_index += 1
            else:
                prev_p = p[0]
                alt_index = 0
        s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
        # p[2] : USART2_RX
        b=p[2].split('_')[0]
        b = b.replace("UART", "UART_")
        b = b.replace("USART", "UART_")
        s1 += "%-9s" % (b[:len(b)-1] +  b[len(b)-1:] + ',')
        if 'STM32F10' in mcu_file and l == uartrx_list:
            s1 += 'STM_PIN_DATA(STM_MODE_INPUT, GPIO_PULLUP, '
        else:
            s1 += 'STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, '
        r = result.split(' ')
        for af in r:
            s2 = s1 + af  + ')},'
            if p[1] in PinLabel.keys():
                s2 += ' // Connected to ' + PinLabel[p[1]]
            s2 += '\n'
            out_c_file.write(s2)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_spi(l):
    prev_p = ''
    alt_index = 0
    for p in l:
        result = get_gpio_af_num(p[1], p[2])
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "STDIO_UART" in PinLabel[p[1]]:
                CommentedLine = "//"
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        if CommentedLine != "//":
            if p[0] == prev_p:
                prev_p = p[0]
                p[0] += '_ALT%d' % alt_index
                store_pin(p[0], p[0])
                alt_index += 1
            else:
                prev_p = p[0]
                alt_index = 0
        s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
        # p[2] : SPI1_MISO
        instance=p[2].split('_')[0].replace("SPI", "")
        s1 += "%-7s" % ('SPI_' + instance + ',')
        s1 += 'STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, '
        r = result.split(' ')
        for af in r:
            s2 = s1 + af  + ')},'
            if p[1] in PinLabel.keys():
                s2 += ' // Connected to ' + PinLabel[p[1]]
            s2 += '\n'
            out_c_file.write(s2)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_can(l):
    for p in l:
        result = get_gpio_af_num(p[1], p[2])
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "STDIO_UART" in PinLabel[p[1]]:
                CommentedLine = "//"
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        s1 = "%-17s" % (CommentedLine + "  {" + p[0] + ',')
        # p[2] : CAN_RX / CAN1_RX
        p[2] = p[2].replace("FD", "")
        instance = p[2].split('_')[0].replace("CAN", "")
        if len(instance) == 0:
            instance = '1'
        s1 += "%-7s" % ('CAN_' + instance + ',')
        if 'STM32F10' in mcu_file and l == canrd_list:
            s1 += 'STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, '
        else:
            s1 += 'STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, '
        r = result.split(' ')
        for af in r:
            s2 = s1 + af  + ')},'
            if p[1] in PinLabel.keys():
                s2 += ' // Connected to ' + PinLabel[p[1]]
            s2 += '\n'
            out_c_file.write(s2)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_qspi(l):
    for p in l:
        result = get_gpio_af_num(p[1], p[2])
        if "BK2" in p[2]: # QSPI Bank 2 is not supported
            continue
        CommentedLine = "  "
        if p[1] in PinLabel.keys():
            if "STDIO_UART" in PinLabel[p[1]]:
                CommentedLine = "//"
            if "RCC_OSC" in PinLabel[p[1]]:
                CommentedLine = "//"
        s1 = "%-16s" % (CommentedLine + "  {" + p[0] + ',')
        # p[2] : QUADSPI_BK1_IO3 / QUADSPI_CLK / QUADSPI_NCS
        if "OCTOSPIM_P2" in p[2]:
            s1 += "%-8s" % ('QSPI_2,')
        else:
            s1 += "%-8s" % ('QSPI_1,')
        result = result.replace("GPIO_AF10_OTG_FS", "GPIO_AF10_QSPI")
        s1 += 'STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, ' + result +')},'
        s1 += '  // ' + p[2]
        if p[1] in PinLabel.keys():
            s1 += ' // Connected to ' + PinLabel[p[1]]
        s1 += '\n'
        out_c_file.write(s1)
    out_c_file.write( """    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )

def print_usb(lst):
    use_hs_in_fs = False
    nb_loop = 1
    inst = "USB_FS"
    if lst is usb_otgfs_list:
        inst = "USB_FS"
    elif lst is usb_otghs_list:
        inst = "USB_HS"
        nb_loop = 2

    for nb in range(nb_loop):
        for p in lst:
            result = get_gpio_af_num(p[1], p[2])

            CommentedLine = "  "

            if p[1] in PinLabel.keys():
                if "STDIO_UART" in PinLabel[p[1]]:
                    CommentedLine = "//"
                if "RCC_OSC" in PinLabel[p[1]]:
                    CommentedLine = "//"

            if "_SOF" in p[2] or "_NOE" in p[2]:
                CommentedLine = "//"

            if lst is usb_otghs_list:
                if nb == 0:
                    if "ULPI" in p[2]:
                        continue
                    elif not use_hs_in_fs:
                        out_c_file.write("#if (MBED_CONF_TARGET_USB_SPEED == USE_USB_HS_IN_FS)\n")
                        use_hs_in_fs = True
                else:
                    if "ULPI" not in p[2]:
                        continue
                    elif use_hs_in_fs:
                        out_c_file.write("#else /* MBED_CONF_TARGET_USB_SPEED */\n")
                        use_hs_in_fs = False

            s1 = "%-16s" % (CommentedLine + "  {" + p[0] + ',')

            # 2nd element is the USB_XXXX signal
            if not p[2].startswith("USB_D") and "VBUS" not in p[2]:
                if "ID" not in p[2]:
                    s1 += inst + ", STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, "
                else:
                    # ID pin: AF_PP + PULLUP
                    s1 += inst + ", STM_PIN_DATA(STM_MODE_AF_OD, GPIO_PULLUP, "
            else:
                # USB_DM/DP and VBUS: INPUT + NOPULL
                s1 += inst + ", STM_PIN_DATA(STM_MODE_INPUT, GPIO_NOPULL, "
            if result == "NOTFOUND":
                s1 += "0)},"
            else:
                r = result.split(" ")
                for af in r:
                    s1 += af + ")},"
            s1 += " // " + p[2]
            if p[1] in PinLabel.keys():
                s1 += ' // Connected to ' + PinLabel[p[1]]
            s1 += "\n"
            out_c_file.write(s1)
    if lst:
        if lst is usb_otghs_list:
            out_c_file.write("#endif /* MBED_CONF_TARGET_USB_SPEED */\n")
        out_c_file.write("""    {NC, NC, 0}
};
""")
    if ADD_DEVICE_IF:
        out_c_file.write( "#endif\n" )


def print_PinList(l):
    l.sort(key=natural_sortkey)
    previous_pin = ""
    for p in l:
        print_debug("pin %s => %s" % (p, p[0]))
        if p[0] == previous_pin:
            continue
        previous_pin = p[0]

        if "_ALT" in p[0]:
            s1 = "    %-10s = %s | %s, // same pin used for alternate HW\n" % (p[0], p[0].split('_A')[0], p[0].split('_')[2])
        else:
            if "PA" in p[0]:
                PinValue = 0
            elif "PB" in p[0]:
                PinValue = 0x10
            elif "PC" in p[0]:
                PinValue = 0x20
            elif "PD" in p[0]:
                PinValue = 0x30
            elif "PE" in p[0]:
                PinValue = 0x40
            elif "PF" in p[0]:
                PinValue = 0x50
            elif "PG" in p[0]:
                PinValue = 0x60
            elif "PH" in p[0]:
                PinValue = 0x70
            elif "PI" in p[0]:
                PinValue = 0x80
            elif "PJ" in p[0]:
                PinValue = 0x90
            elif "PK" in p[0]:
                PinValue = 0xA0
            elif "PZ" in p[0]:
                PinValue = 0x0 # to update
            else:
                print("error in print_PinList with pin %s" % p[0])
            PinValue += int(p[0].split('_')[1])
            s1 = "    %-10s = 0x%02X,\n" % (p[0], PinValue)

        out_h_file.write(s1)

    out_h_file.write("""\n    /**** ADC internal channels ****/

    ADC_TEMP = 0xF0, // Internal pin virtual value
    ADC_VREF = 0xF1, // Internal pin virtual value
    ADC_VBAT = 0xF2, // Internal pin virtual value

    // Arduino Uno(Rev3) Header pin connection naming
    A0 = Px_x,
    A1 = Px_x,
    A2 = Px_x,
    A3 = Px_x,
    A4 = Px_x,
    A5 = Px_x,
    D0 = Px_x,
    D1 = Px_x,
    D2 = Px_x,
    D3 = Px_x,
    D4 = Px_x,
    D5 = Px_x,
    D6 = Px_x,
    D7 = Px_x,
    D8 = Px_x,
    D9 = Px_x,
    D10= Px_x,
    D11= Px_x,
    D12= Px_x,
    D13= Px_x,
    D14= Px_x,
    D15= Px_x,
    """)

    s = ("""
    // STDIO for console print
#ifdef MBED_CONF_TARGET_STDIO_UART_TX
    STDIO_UART_TX = MBED_CONF_TARGET_STDIO_UART_TX,
#else
    STDIO_UART_TX = %s,
#endif
#ifdef MBED_CONF_TARGET_STDIO_UART_RX
    STDIO_UART_RX = MBED_CONF_TARGET_STDIO_UART_RX,
#else
    STDIO_UART_RX = %s,
#endif

    USBTX = STDIO_UART_TX, // used for greentea tests
    USBRX = STDIO_UART_RX, // used for greentea tests
""" % (re.sub(r'(P.)', r'\1_', STDIO_list[0]), re.sub(r'(P.)', r'\1_', STDIO_list[1])))
    out_h_file.write(s)

    out_h_file.write("""
    // I2C signals aliases
    I2C_SDA = D14,
    I2C_SCL = D15,

    // SPI signals aliases
    SPI_CS   = D10,
    SPI_MOSI = D11,
    SPI_MISO = D12,
    SPI_SCK  = D13,

    // Standardized LED and button names
""")

    NameCounter = 1
    if len(LED_list) == 0:
       LED_list.append("Pxx")
    for EachLED in LED_list:
        try:
            LED_LABEL = " // %s" % PinLabel[EachLED]
        except:
            LED_LABEL = ""
        out_h_file.write("    LED%i    = %s,%s\n" % (NameCounter, re.sub(r'(P.)', r'\1_', EachLED), LED_LABEL))
        NameCounter += 1

    NameCounter = 1
    if len(BUTTON_list) == 0:
       BUTTON_list.append("Pxx")
    for EachBUTTON in BUTTON_list:
        try:
            BUTTON_LABEL = " // %s" % PinLabel[EachBUTTON]
        except:
            BUTTON_LABEL = ""
        out_h_file.write("    BUTTON%i = %s,%s\n" % (NameCounter, re.sub(r'(P.)', r'\1_', EachBUTTON).split('/')[0].split('-')[0], BUTTON_LABEL))
        NameCounter += 1

    out_h_file.write("""
    // Backward legacy names
    USER_BUTTON = BUTTON1,
    PWM_OUT = D3,
    """)


def print_h_file(l, comment):
    l.sort(key=natural_sortkey2)
    if len(l) > 0:
        s = ("\n    /**** %s pins ****/\n" % comment)
        out_h_file.write(s)

        prev_s = ''
        alt_index = 0
        for p in l:
            if p[2] == prev_s:
                prev_s = p[2]
                p[2] += '_ALT%d' % alt_index
                store_pin(p[0], p[0])
                alt_index += 1
            else:
                prev_s = p[2]
                alt_index = 0
            s1 = "    %s = %s,\n" % (p[2].replace("-", "_"), p[0])
            out_h_file.write(s1)
    # else:
    #     s = ("\n/**** No %s pins ***/\n" % comment)
    #     out_h_file.write(s)


tokenize = re.compile(r"(\d+)|(\D+)").findall


def natural_sortkey(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[0]))

def natural_sortkey2(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[2]))

def natural_sortkey_uart(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[2].replace("USART", "UART").replace("LPUART", "ZUART")))

def natural_sortkey_i2c(list_2_elem):
    return tuple(int(num) if num else alpha for num, alpha in tokenize(list_2_elem[2].replace("FMPI2C", "ZFMPI2C")))

def sort_my_lists():
    adclist.sort(key=natural_sortkey)
    daclist.sort(key=natural_sortkey)
    i2cscl_list.sort(key=natural_sortkey_i2c) # first sort on name column
    i2csda_list.sort(key=natural_sortkey_i2c) # first sort on name column
    i2cscl_list.sort(key=natural_sortkey)
    i2csda_list.sort(key=natural_sortkey)
    pwm_list.sort(key=natural_sortkey2) # first sort on name column
    pwm_list.sort(key=natural_sortkey)
    uarttx_list.sort(key=natural_sortkey_uart) # first sort on name column
    uartrx_list.sort(key=natural_sortkey_uart) # first sort on name column
    uartcts_list.sort(key=natural_sortkey_uart) # first sort on name column
    uartrts_list.sort(key=natural_sortkey_uart) # first sort on name column
    uarttx_list.sort(key=natural_sortkey)
    uartrx_list.sort(key=natural_sortkey)
    uartcts_list.sort(key=natural_sortkey)
    uartrts_list.sort(key=natural_sortkey)
    spimosi_list.sort(key=natural_sortkey)
    spimiso_list.sort(key=natural_sortkey)
    spissel_list.sort(key=natural_sortkey)
    spisclk_list.sort(key=natural_sortkey)
    cantd_list.sort(key=natural_sortkey)
    canrd_list.sort(key=natural_sortkey)
    quadspidata0_list.sort(key=natural_sortkey)
    quadspidata1_list.sort(key=natural_sortkey)
    quadspidata2_list.sort(key=natural_sortkey)
    quadspidata3_list.sort(key=natural_sortkey)
    quadspisclk_list.sort(key=natural_sortkey)
    quadspissel_list.sort(key=natural_sortkey)
    usb_list.sort(key=natural_sortkey)
    usb_otgfs_list.sort(key=natural_sortkey)
    usb_otghs_list.sort(key=natural_sortkey)

def clean_all_lists():
    del io_list[:]
    del adclist[:]
    del daclist[:]
    del i2cscl_list[:]
    del i2csda_list[:]
    del pwm_list[:]
    del uarttx_list[:]
    del uartrx_list[:]
    del uartcts_list[:]
    del uartrts_list[:]
    del spimosi_list[:]
    del spimiso_list[:]
    del spissel_list[:]
    del spisclk_list[:]
    del cantd_list[:]
    del canrd_list[:]
    del eth_list[:]
    del quadspidata0_list[:]
    del quadspidata1_list[:]
    del quadspidata2_list[:]
    del quadspidata3_list[:]
    del quadspisclk_list[:]
    del quadspissel_list[:]
    del usb_list[:]
    del osc_list[:]
    del sys_list[:]


def parse_pins():
    pinregex = r"^(P[A-Z][0-9][0-5]?)"
    itemlist = xml_mcu.getElementsByTagName("Pin")
    for s in itemlist:
        m = re.match(pinregex, s.attributes["Name"].value)
        if m:
            pin = (
                m.group(0)[:2] + "_" + m.group(0)[2:]
            )  # pin formatted P<port>_<number>: PF_O
            name = s.attributes["Name"].value.strip()  # full name: "PF0 / OSC_IN"
            if s.attributes["Type"].value == "I/O":
                store_pin(pin, name)
            else:
                continue
            siglist = s.getElementsByTagName("Signal")
            for a in siglist:
                sig = a.attributes["Name"].value.strip()
                if "ADC" in sig:
                    store_adc(pin, name, sig)
                if all(["DAC" in sig, "_OUT" in sig]):
                    store_dac(pin, name, sig)
                if "I2C" in sig:
                    store_i2c(pin, name, sig)
                if re.match("^TIM", sig) is not None:  # ignore HRTIM
                    store_pwm(pin, name, sig)
                if re.match("^(LPU|US|U)ART", sig) is not None:
                    store_uart(pin, name, sig)
                if "SPI" in sig:
                    store_spi(pin, name, sig)
                if "CAN" in sig:
                    store_can(pin, name, sig)
                if "ETH" in sig:
                    store_eth(pin, name, sig)
                if "QUADSPI" in sig or "OCTOSPI" in sig:
                    store_qspi(pin, name, sig)
                if "USB" in sig:
                    store_usb(pin, name, sig)
                if "RCC_OSC" in sig:
                    store_osc(pin, name, sig)
                if "SYS_" in sig or "PWR_" in sig or "DEBUG_" in sig:
                    store_sys(pin, name, sig)


PinData = {}
PinLabel = {}


def parse_BoardFile(fileName):
    print(" * Board file: '%s'" % (fileName))
    board_file = open(fileName, "r")
    # IOC_PIN_pattern = re.compile(r'(P[A-I][\d]*).*\.([\w]*)=(.*)')
    IOC_PIN_pattern = re.compile(r'(.*)\.([\w]*)=(.*)')
    for line in board_file.readlines():
        IOC_PIN = re.match(IOC_PIN_pattern, line)
        if IOC_PIN:
            if IOC_PIN.groups()[0] in PinData.keys():
                PinData[IOC_PIN.groups()[0]][IOC_PIN.groups()[1]] = IOC_PIN.groups()[2]
            else:
                PinData[IOC_PIN.groups()[0]] = {}
                PinData[IOC_PIN.groups()[0]][IOC_PIN.groups()[1]] = IOC_PIN.groups()[2]
        # IOC_MCU = re.match(r'Mcu\.UserName=(.*)', line)
        IOC_MCU = re.match(r'Mcu\.Name=(.*)', line)
        if IOC_MCU:
            mcu_list.append("%s.xml" % IOC_MCU.groups()[0])

    board_file.close()

    for EachPin in PinData:
        PinLabel[EachPin] = ""
        if "Signal" in PinData[EachPin].keys():
            PinLabel[EachPin] = PinData[EachPin]["Signal"]
        if "GPIO_Label" in PinData[EachPin].keys():
            PinLabel[EachPin] = PinData[EachPin]["GPIO_Label"]
        if any(led in PinLabel[EachPin].upper() for led in
               ["LED", "LD1", "LD2", "LD3", "LD4", "LD5", "LD6", "LD7", "LD8", "LD9"]):
            LED_list.append(EachPin)
        elif any(button in PinLabel[EachPin].upper() for button in ["BUTTON", "B_USER", "BTN"]):
            BUTTON_list.append(EachPin)

        UART_HW_OPTION = "NO_NEED"
        for EachTarget in VCP_UART_LIST:
            if EachTarget in fileName:
                UART_HW_OPTION = VCP_UART_LIST[EachTarget]

        try:
            if "STLK_RX" in PinLabel[EachPin] or "STLK_TX" in PinLabel[EachPin]:
                # Patch waiting for CubeMX correction
                if "RX" in PinData[EachPin]["Signal"]:
                    PinLabel[EachPin] = "STDIO_UART_RX"
                    STDIO_list[1] = EachPin
                else:
                    PinLabel[EachPin] = "STDIO_UART_TX"
                    STDIO_list[0] = EachPin
            elif "USART_RX" in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_RX"
                STDIO_list[1] = EachPin
            elif "USART_TX" in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_TX"
                STDIO_list[0] = EachPin
            elif "VCP_RX" in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_RX"
                STDIO_list[1] = EachPin
            elif "VCP_TX" in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_TX"
                STDIO_list[0] = EachPin
            elif "ST_LINK_UART1_RX" in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_RX"
                STDIO_list[1] = EachPin
            elif "ST_LINK_UART1_TX" in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_TX"
                STDIO_list[0] = EachPin
            elif "STLINK_RX" in PinLabel[EachPin] or "STLINK_TX" in PinLabel[EachPin]:
                # Patch waiting for CubeMX correction
                if "RX" in PinData[EachPin]["Signal"]:
                    PinLabel[EachPin] = "STDIO_UART_RX"
                    STDIO_list[1] = EachPin
                else:
                    PinLabel[EachPin] = "STDIO_UART_TX"
                    STDIO_list[0] = EachPin
            elif "%s_RX" % UART_HW_OPTION in PinLabel[EachPin]:
                PinLabel[EachPin] = "STDIO_UART_RX"
                STDIO_list[1] = EachPin
            elif "%s_TX" % UART_HW_OPTION in PinLabel[EachPin]:
                STDIO_list[0] = EachPin
                PinLabel[EachPin] = "STDIO_UART_TX"
            elif "_RESERVED" in PinLabel[EachPin]:
                PinLabel[EachPin] = "RESERVED_RADIO"
        except:
            pass


# main
print ("\nScript version %s" % GENPINMAP_VERSION)
cur_dir = os.getcwd()
PeripheralPins_c_filename = "PeripheralPins.c"
PinNames_h_filename = "PinNames.h"
config_filename = "cube_path.json"

try:
    config_file = open(config_filename, "r")
except IOError:
    print("Please set your configuration in '%s' file" % config_filename)
    config_file = open(config_filename, "w")
    if sys.platform.startswith("win32"):
        print_debug("Platform is Windows")
        cubemxdir = "C:\\Program Files\\STMicroelectronics\\STM32Cube\\STM32CubeMX"
    elif sys.platform.startswith("linux"):
        print_debug("Platform is Linux")
        cubemxdir = os.getenv("HOME")+"/STM32CubeMX"
    elif sys.platform.startswith("darwin"):
        print_debug("Platform is Mac OSX")
        cubemxdir = "/Applications/STMicroelectronics/STM32CubeMX.app/Contents/Resources"
    else:
        print_debug("Platform unknown")
        cubemxdir = "<Set CubeMX install directory>"
    config_file.write(json.dumps({"CUBEMX_DIRECTORY":cubemxdir}))
    config_file.close()
    print("Default path set: %s\n" % cubemxdir)
    config_file = open(config_filename, "r")

config = json.load(config_file)
config_file.close()
cubemxdir = config["CUBEMX_DIRECTORY"]


parser = argparse.ArgumentParser(
    description=textwrap.dedent('''\
Script will generate %s thanks to the xml files description available in
STM32CubeMX directory defined in '%s':
\t%s\n
More information in targets/TARGET_STM/README.md''' % (PeripheralPins_c_filename, config_filename, cubemxdir)),
    epilog=textwrap.dedent('''\
Once generated, you have to check and comment pins that can not be used (specific HW, internal ADC channels, remove PWM using us ticker timer, ...)
'''),
    formatter_class=RawTextHelpFormatter)

group = parser.add_mutually_exclusive_group(required = True)

group.add_argument("-l", "--list", help="list available mcu xml files description in STM32CubeMX", action="store_true")

group.add_argument("-b", "--boards", help="list available boards description in STM32CubeMX", action="store_true")

group.add_argument("-m", "--mcu", metavar='xml', help=textwrap.dedent('''\
specify the mcu xml file description in STM32CubeMX to use (use double quotes).
   Parameter can be a filter like L496 if you want to parse all L496 chips (-m STM32 to parse all).
'''))

group.add_argument("-t", "--target", metavar='HW', help=textwrap.dedent('''\
specify the board file description in STM32CubeMX to use (use double quotes).
   Parameter can be a filter like L496 (only the first file found will be parsed).
'''))

group.add_argument("-c", "--custom", help=textwrap.dedent('''\
specify a custom board .ioc file description to use (use double quotes).
'''))

args = parser.parse_args()

if not(os.path.isdir(cubemxdir)):
    print ("\n ! ! ! Cube Mx seems not to be installed or not at the requested location")
    print ("\n ! ! ! please check the value you set for 'CUBEMX_DIRECTORY' in '%s' file" % config_filename)
    sys.exit(1)

cubemxdirMCU = os.path.join(cubemxdir, "db", "mcu")
cubemxdirIP = os.path.join(cubemxdir, "db", "mcu", "IP")
cubemxdirBOARDS = os.path.join(cubemxdir, "db", "plugins", "boardmanager", "boards")

version_file = os.path.join(cubemxdir, "db", "package.xml")
try:
    xml_file = parse(version_file)
    PackDescription_item = xml_file.getElementsByTagName("PackDescription")
    for item in PackDescription_item:
        CUBEMX_DB_VERSION = item.attributes["Release"].value
except:
    CUBEMX_DB_VERSION = "NOT_FOUND"
print ("CubeMX DB version %s\n" % CUBEMX_DB_VERSION)

if args.list:
    FileCount = 0
    for f in fnmatch.filter(os.listdir(cubemxdirMCU), "STM32*.xml"):
        print(f)
        FileCount += 1
    print()
    print("%i available xml files description" % FileCount)
    sys.exit(0)

if args.boards:
    NucleoFileCount = 0
    DiscoFileCount = 0
    for f in fnmatch.filter(os.listdir(cubemxdirBOARDS), '*AllConfig.ioc'):
        print(f)
        if "Nucleo" in f:
            NucleoFileCount += 1
        elif "Discovery" in f:
            DiscoFileCount += 1
    print()
    print("%2i available Nucleo files description" % NucleoFileCount)
    print("%2i available Disco  files description" % DiscoFileCount)
    sys.exit(0)

if args.mcu:
    #check input file exists
    if os.path.isfile(os.path.join(cubemxdirMCU, args.mcu)):
        mcu_list.append(args.mcu)
    else:
        mcu_list = fnmatch.filter(os.listdir(cubemxdirMCU), '*%s*' % args.mcu)
        if len(mcu_list) == 0:
            print (" ! ! ! " + args.mcu + " file not found")
            print (" ! ! ! Check in " + cubemxdirMCU + " the correct name of this file")
            print (" ! ! ! You may use double quotes for this file if it contains special characters")
            sys.exit(1)

if args.target:
    board_file_name = os.path.join(cubemxdirBOARDS, args.target)
    if not(os.path.isfile(board_file_name)):
        board_list = fnmatch.filter(os.listdir(cubemxdirBOARDS), '*%s*AllConfig.ioc' % args.target)
        if len(board_list) == 0:
            print (" ! ! ! No file contains " + args.target)
            print (" ! ! ! Check in " + cubemxdirBOARDS + " the correct filter to apply")
            sys.exit(1)
        elif len(board_list) > 1:
            print (" ! ! ! Multiple files contains " + args.target)
            for board_elem in board_list: print (board_elem)
            print (" ! ! ! Only the first one will be parsed\n")
        board_file_name = os.path.join(cubemxdirBOARDS,board_list[0])
        if not (os.path.isfile(board_file_name)):
            print (" ! ! ! " + args.target + " file not found")
            print (" ! ! ! Check in " + cubemxdirBOARDS + " the correct name of this file")
            print (" ! ! ! You may use double quotes for this file if it contains special characters")
            sys.exit(1)

    # Add some hardcoded check
    if "J01_" in board_file_name:
        print("J01_Discovery_STM32F4-DISCO-AudioPack_STM32F407V_Board not parsed")
        sys.exit(0)
    elif "G00_" in board_file_name:
        print("G00_Nucleo_NUCLEO-WB52VGY_STM32WB52VGY_Board not parsed")
        sys.exit(0)
    elif "C40_" in board_file_name:
        print("C40_Discovery_STM32F4DISCOVERY_STM32F407VG_Board replaced by C47_Discovery_STM32F407G-DISC1_STM32F407VG_Board")
        sys.exit(0)
    elif "TrustZoneEnabled" in board_file_name:
        print("TrustZoneEnabled boards not parsed")
        sys.exit(0)

    parse_BoardFile(board_file_name)
    TargetName = ""
    if "Nucleo" in board_file_name:
        TargetName += "NUCLEO_"
    elif "Discovery" in board_file_name:
        TargetName += "DISCO_"
    elif "Evaluation" in board_file_name:
        TargetName += "EVAL_"
    m = re.search(r'STM32([MFLGWH][\w]*)_Board', board_file_name)
    if m:
        TargetName += "%s" % m.group(1)
        # specific case
        if "-P" in board_file_name:
            TargetName += "_P"
        elif "-Q" in board_file_name:
            TargetName += "_Q"

        target_rename = {  # manual renaming for some boards
            "DISCO_L072C": "DISCO_L072CZ_LRWAN1",
            "DISCO_L475V": "DISCO_L475VG_IOT01A",
            "DISCO_G071RBT": "DISCO_G071RB",
            "DISCO_L4R9A": "DISCO_L4R9I",
            "NUCLEO_WB55R": "NUCLEO_WB55RG",
            "NUCLEO_H743ZIT": "NUCLEO_H743ZI2",
            "NUCLEO_H7A3ZIT_Q": "NUCLEO_H7A3ZI_Q",
            "DISCO_F0DISCOVERY_STM32F051R8": "DISCO_F051R8",
            "DISCO_F3DISCOVERY_STM32F303VC": "DISCO_F303VC",
            "DISCO_F469NIH": "DISCO_F469NI",
            "DISCO_F412ZGT": "DISCO_F412ZG",
            "DISCO_F746NGH": "DISCO_F746NG",
            "DISCO_F769NIH": "DISCO_F769NI",
            "DISCO_H747XIH": "DISCO_H747I"
        }

        if TargetName in target_rename.keys():
            TargetName = target_rename[TargetName]

        if "DISC1" in board_file_name:
            TargetName += "_DISC1"

    else:
        sys.exit(1)

# Parse the user's custom board .ioc file
if args.custom:
    parse_BoardFile(args.custom)
    TargetName = ""

for mcu_file in mcu_list:
    if args.mcu:
        TargetName = os.path.splitext(mcu_file)[0]
    out_path = os.path.join(cur_dir, 'targets_custom', 'TARGET_STM', 'TARGET_%s' % TargetName)
    print(" * Output directory: %s" % (out_path))
    input_file_name = os.path.join(cubemxdirMCU, mcu_file)
    print(" * Generating %s and %s with '%s'" % (PeripheralPins_c_filename, PinNames_h_filename, input_file_name))
    output_cfilename = os.path.join(out_path, PeripheralPins_c_filename)
    output_hfilename = os.path.join(out_path, PinNames_h_filename)
    if not(os.path.isdir(out_path)):
        os.makedirs(out_path)

    if (os.path.isfile(output_cfilename)):
        print_debug(" * Requested %s file already exists and will be overwritten" % PeripheralPins_c_filename)
        os.remove(output_cfilename)
    out_c_file = open(output_cfilename, 'w')
    out_h_file = open(output_hfilename, 'w')

    #open input file
    try:
        xml_mcu = parse(input_file_name)
    except:
        # Patch waiting for CubeMX correction
        if "STM32F042K6Tx" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32F042K(4-6)Tx.xml")
            xml_mcu = parse(input_file_name)
        elif "STM32F429Z" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32F429ZITx.xml")
            xml_mcu = parse(input_file_name)
        elif "STM32F746Z" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32F746ZGTx.xml")
            xml_mcu = parse(input_file_name)
        elif "STM32F767Z" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32F767ZGTx.xml")
            xml_mcu = parse(input_file_name)

        elif "STM32L011K4Tx" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32L011K(3-4)Tx.xml")
            xml_mcu = parse(input_file_name)
        elif "STM32L432KCUx" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32L432K(B-C)Ux.xml")
            xml_mcu = parse(input_file_name)
        elif "STM32F746N" in input_file_name:
            input_file_name = os.path.join(cubemxdirMCU, "STM32F746NGHx.xml")
            xml_mcu = parse(input_file_name)
        else:
            print ("\n ! ! ! Error in CubeMX file. File " + input_file_name + " doesn't exist")
            print (" ! ! ! Check in " + cubemxdirMCU)
            sys.exit(1)
    gpiofile = find_gpio_file()
    if gpiofile == "ERROR":
        print("error: Could not find GPIO file")
        sys.exit(1)
    xml_gpio = parse(os.path.join(cubemxdirIP, "GPIO-" + gpiofile + "_Modes.xml"))
    print (" * GPIO file: " + os.path.join(cubemxdirIP, "GPIO-" + gpiofile + "_Modes.xml"))

    parse_pins()
    sort_my_lists()
    print_header()
    print_all_lists()
    print_footer()

    nb_pin = (len(io_list))
    nb_connected_pin = len(PinLabel)
    print (" * I/O pins found: %i connected: %i\n" % (nb_pin, nb_connected_pin))
    clean_all_lists()

    out_c_file.close()
    out_h_file.close()
