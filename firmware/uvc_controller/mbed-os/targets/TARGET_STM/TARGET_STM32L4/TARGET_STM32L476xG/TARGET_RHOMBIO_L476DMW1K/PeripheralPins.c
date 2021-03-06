/* mbed Microcontroller Library
 *
 * SPDX-License-Identifier: BSD-3-Clause
 *******************************************************************************
 * Copyright (c) 2018, STMicroelectronics
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of STMicroelectronics nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
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
// - The pins which are other components present on the board have
//   the comment "Connected to xxx". The pin function may not work properly in this
//   case. These pins may not be displayed on the board pinout image on mbed.org.
//   Please read the board reference manual and schematic for more information.
//
// - Warning: pins the default STDIO_UART_TX and STDIO_UART_RX pins are commented
//   See https://os.mbed.com/teams/ST/wiki/STDIO for more information.
//
//==============================================================================


//*** ADC ***

MBED_WEAK const PinMap PinMap_ADC[] = {
    {PA_0,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 5, 0)},  // ADC1_IN5  // rhomb.io AD0
    {PA_0_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 5, 0)},  // ADC2_IN5  // rhomb.io AD0 
    {PA_1,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 6, 0)},  // ADC1_IN6  // rhomb.io AD1
    {PA_1_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 6, 0)},  // ADC2_IN6  // rhomb.io AD1
    {PA_2,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 7, 0)},  // ADC1_IN7  // rhomb.io UART-A_TXD
    {PA_2_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 7, 0)},  // ADC2_IN7  // rhomb.io UART-A_TXD
    {PA_3,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 8, 0)},  // ADC1_IN8  // rhomb.io UART-A_RXD
    {PA_3_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 8, 0)},  // ADC2_IN8  // rhomb.io UART-A_RXD
    {PA_4,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 9, 0)},  // ADC1_IN9  // rhomb.io AD2
    {PA_4_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 9, 0)},  // ADC2_IN9  // rhomb.io AD2
    {PA_5,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 10, 0)}, // ADC1_IN10 // rhomb.io SPIA_CLK
    {PA_5_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 10, 0)}, // ADC2_IN10 // rhomb.io SPIA_CLK 
    {PA_6,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 11, 0)}, // ADC1_IN11 // rhomb.io SPIA_MISO
    {PA_6_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 11, 0)}, // ADC2_IN11 // rhomb.io SPIA_MISO
    {PA_7,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 12, 0)}, // ADC1_IN12 // rhomb.io SPIA_MOSI
    {PA_7_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 12, 0)}, // ADC2_IN12 // rhomb.io SPIA_MOSI 
    {PB_0,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 15, 0)}, // ADC1_IN15 // rhomb.io AD3
    {PB_0_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 15, 0)}, // ADC2_IN15 // rhomb.io AD3
    {PB_1,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 16, 0)}, // ADC1_IN16 // rhomb.io NMI
    {PB_1_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 16, 0)}, // ADC2_IN16 // rhomb.io NMI
    {PC_0,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 1, 0)},  // ADC1_IN1  // rhomb.io AD5
    {PC_0_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 1, 0)},  // ADC2_IN1  // rhomb.io AD5 
    {PC_0_ALT1,  ADC_3, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 1, 0)},  // ADC3_IN1  // rhomb.io AD5
    {PC_1,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 2, 0)},  // ADC1_IN2  // rhomb.io AD4
    {PC_1_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 2, 0)},  // ADC2_IN2  // rhomb.io AD4 
    {PC_1_ALT1,  ADC_3, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 2, 0)},  // ADC3_IN2  // rhomb.io AD4 
    {PC_2,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 3, 0)},  // ADC1_IN3  // rhomb.io CAPT1 (R19 must be populated)
    {PC_2_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 3, 0)},  // ADC2_IN3  // rhomb.io CAPT1 (R19 must be populated) 
    {PC_2_ALT1,  ADC_3, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 3, 0)},  // ADC3_IN3  // rhomb.io CAPT1 (R19 must be populated) 
    {PC_3,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 4, 0)},  // ADC1_IN4  // rhomb.io CAPT0 (R18 must be populated)
    {PC_3_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 4, 0)},  // ADC2_IN4  // rhomb.io CAPT0 (R18 must be populated)
    {PC_3_ALT1,  ADC_3, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 4, 0)},  // ADC3_IN4  // rhomb.io CAPT0 (R18 must be populated) 
    {PC_4,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 13, 0)}, // ADC1_IN13 // rhomb.io AD8
    {PC_4_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 13, 0)}, // ADC2_IN13 // rhomb.io AD8 
    {PC_5,       ADC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 14, 0)}, // ADC1_IN14 // rhomb.io AD7
    {PC_5_ALT0,  ADC_2, STM_PIN_DATA_EXT(STM_MODE_ANALOG_ADC_CONTROL, GPIO_NOPULL, 0, 14, 0)}, // ADC2_IN14 // rhomb.io AD7 
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_ADC_Internal[] = {
    {ADC_TEMP,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 17, 0)},
    {ADC_VREF,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0,  0, 0)},
    {ADC_VBAT,   ADC_1,    STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 18, 0)},
    {NC, NC, 0}
};

//*** DAC ***

MBED_WEAK const PinMap PinMap_DAC[] = {
    {PA_4,       DAC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 1, 0)}, // DAC1_OUT1 // rhomb.io AD2
    {PA_5,       DAC_1, STM_PIN_DATA_EXT(STM_MODE_ANALOG, GPIO_NOPULL, 0, 2, 0)}, // DAC1_OUT2 // rhomb.io SPIA_CLK
    {NC, NC, 0}
};

//*** I2C ***

MBED_WEAK const PinMap PinMap_I2C_SDA[] = {
    {PB_7,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // rhomb.io INT1
    {PB_9,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // rhomb.io I2C-A_SDA // Connected to ATECC608A
    {PB_11,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // rhomb.io QSPI_CS0 /
    {PB_14,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // rhomb.io SPI-A_CS1
    {PC_1,       I2C_3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)}, // rhomb.io AD4
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_I2C_SCL[] = {
    {PB_6,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // rhomb.io SPI-A_CS0
    {PB_8,       I2C_1, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C1)}, // rhomb.io I2C-A_SCL // Connected to ATECC608A
    {PB_10,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // rhomb.io IO2
    {PB_13,      I2C_2, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C2)}, // rhomb.io SPI-A_CS2
    {PC_0,       I2C_3, STM_PIN_DATA(STM_MODE_AF_OD, GPIO_NOPULL, GPIO_AF4_I2C3)}, // rhomb.io AD5
    {NC, NC, 0}
};

//*** PWM ***

// TIM5 cannot be used because already used by the us_ticker
MBED_WEAK const PinMap PinMap_PWM[] = {
    {PA_0,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 1, 0)},   // TIM2_CH1   // rhomb.io AD0
//  {PA_0,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 1, 0)},   // TIM5_CH1   // rhomb.io AD0
    {PA_1,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 2, 0)},   // TIM2_CH2   // rhomb.io AD1
//  {PA_1,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 2, 0)},   // TIM5_CH2   // rhomb.io AD1
    {PA_1_ALT0,  PWM_15, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM15, 1, 1)}, // TIM15_CH1N // rhomb.io AD1
    {PA_2,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 3, 0)},   // TIM2_CH3   // rhomb.io UART-A_TXD
//  {PA_2,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 3, 0)},   // TIM5_CH3   // rhomb.io UART-A_TXD
    {PA_2_ALT0,  PWM_15, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM15, 1, 0)}, // TIM15_CH1  // rhomb.io UART-A_TXD
    {PA_3,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 4, 0)},   // TIM2_CH4   // rhomb.io UART-A_RXD
//  {PA_3,       PWM_5,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM5, 4, 0)},   // TIM5_CH4   // rhomb.io UART-A_RXD
    {PA_3_ALT0,  PWM_15, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM15, 2, 0)}, // TIM15_CH2  // rhomb.io UART-A_RXD
    {PA_5,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 1, 0)},   // TIM2_CH1   // rhomb.io SPI-A_CLK
    {PA_5_ALT0,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 1, 1)},   // TIM8_CH1N  // rhomb.io SPI-A_CLK
    {PA_6,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)},   // TIM3_CH1   // rhomb.io SPI-A_MISO 
    {PA_6_ALT0,  PWM_16, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM16, 1, 0)}, // TIM16_CH1  // rhomb.io SPI-A_MISO 
    {PA_7,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 1)},   // TIM1_CH1N  // rhomb.io SPI-A_MOSI 
    {PA_7_ALT0,  PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)},   // TIM3_CH2   // rhomb.io SPI-A_MOSI 
    {PA_7_ALT1,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 1, 1)},   // TIM8_CH1N  // rhomb.io SPI-A_MOSI 
    {PA_7_ALT2,  PWM_17, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM17, 1, 0)}, // TIM17_CH1  // rhomb.io SPI-A_MOSI 
    {PA_8,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 0)},   // TIM1_CH1   // rhomb.io IO3
    {PA_9,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 0)},   // TIM1_CH2   // rhomb.io IO4
    {PA_10,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 0)},   // TIM1_CH3   // rhomb.io OTG_ID
    {PA_11,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 4, 0)},   // TIM1_CH4   // rhomb.io OTG_N 
    {PA_15,      PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 1, 0)},   // TIM2_CH1   // rhomb.io INT2 
    {PB_0,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 1)},   // TIM1_CH2N  // rhomb.io AD3  
    {PB_0_ALT0,  PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 3, 0)},   // TIM3_CH3   // rhomb.io AD3 
    {PB_0_ALT1,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 2, 1)},   // TIM8_CH2N  // rhomb.io AD3 
    {PB_1,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 1)},   // TIM1_CH3N  // rhomb.io NMI
    {PB_1_ALT0,  PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 4, 0)},   // TIM3_CH4   // rhomb.io NMI
    {PB_1_ALT1,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 3, 1)},   // TIM8_CH3N  // rhomb.io NMI
    {PB_3,       PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 2, 0)},   // TIM2_CH2   // rhomb.io INT0
    {PB_4,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)},   // TIM3_CH1   // rhomb.io IO1
    {PB_5,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)},   // TIM3_CH2   // rhomb.io IO0
    {PB_6,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 1, 0)},   // TIM4_CH1   // rhomb.io SPI-A_CS0
    {PB_6_ALT0,  PWM_16, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM16, 1, 1)}, // TIM16_CH1N // rhomb.io SPI-A_CS0
    {PB_7,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 2, 0)},   // TIM4_CH2   // rhomb.io INT1
    {PB_7_ALT0,  PWM_17, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM17, 1, 1)}, // TIM17_CH1N // rhomb.io INT1
    {PB_8,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 3, 0)},   // TIM4_CH3   // rhomb.io I2C-A_SCL
    {PB_8_ALT0,  PWM_16, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM16, 1, 0)}, // TIM16_CH1  // rhomb.io I2C-A_SCL
    {PB_9,       PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 4, 0)},   // TIM4_CH4   // rhomb.io I2C-A_SDA
    {PB_9_ALT0,  PWM_17, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM17, 1, 0)}, // TIM17_CH1  // rhomb.io I2C-A_SDA
    {PB_10,      PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 3, 0)},   // TIM2_CH3   // rhomb.io IO2
    {PB_11,      PWM_2,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM2, 4, 0)},   // TIM2_CH4   // rhomb.io QSPI_CS0
    {PB_13,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 1)},   // TIM1_CH1N  // rhomb.io SPI-A_CS2
    {PB_13_ALT0, PWM_15, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM15, 1, 1)}, // TIM15_CH1N // rhomb.io SPI-A_CS2
    {PB_14,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 1)},   // TIM1_CH2N  // rhomb.io SPI-A_CS1
    {PB_14_ALT0, PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 2, 1)},   // TIM8_CH2N  // rhomb.io SPI-A_CS1
    {PB_14_ALT1, PWM_15, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM15, 1, 0)}, // TIM15_CH1  // rhomb.io SPI-A_CS1
    {PB_15,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 1)},   // TIM1_CH3N  // rhomb.io IO7
    {PB_15_ALT0, PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 3, 1)},   // TIM8_CH3N  // rhomb.io IO7
    {PB_15_ALT1, PWM_15, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM15, 2, 0)}, // TIM15_CH2  // rhomb.io IO7
    {PC_6,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)},   // TIM3_CH1  // rhomb.io PWM3
    {PC_6_ALT0,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 1, 0)},   // TIM8_CH1  // rhomb.io PWM3
    {PC_7,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)},   // TIM3_CH2  // rhomb.io PWM0
    {PC_7_ALT0,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 2, 0)},   // TIM8_CH2  // rhomb.io PWM0
    {PC_8,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 3, 0)},   // TIM3_CH3  // rhomb.io SDIO_DATA0
    {PC_8_ALT0,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 3, 0)},   // TIM8_CH3  // rhomb.io SDIO_DATA0
    {PC_9,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 4, 0)},   // TIM3_CH4  // rhomb.io SDIO_DATA1
    {PC_9_ALT0,  PWM_8,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF3_TIM8, 4, 0)},   // TIM8_CH4  // rhomb.io SDIO_DATA1
    {PD_12,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 1, 0)},   // TIM4_CH1  // rhomb.io IO12
    {PD_13,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 2, 0)},   // TIM4_CH2  // rhomb.io IO13
    {PD_14,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 3, 0)},   // TIM4_CH3  // rhomb.io PWM2
    {PD_15,      PWM_4,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM4, 4, 0)},   // TIM4_CH4  // rhomb.io SDIO_CDN
    {PE_0,       PWM_16, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM16, 1, 0)}, // TIM16_CH1 // rhomb.io RESET_OUT
    {PE_1,       PWM_17, STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF14_TIM17, 1, 0)}, // TIM17_CH1 // rhomb.io USB_SWITCH
    {PE_3,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 1, 0)},   // TIM3_CH1  // rhomb.io SAI-A_SDO
    {PE_4,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 2, 0)},   // TIM3_CH2  // rhomb.io SAI-A_LRCLK
    {PE_5,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 3, 0)},   // TIM3_CH3  // rhomb.io SAI-A_BCLK
    {PE_6,       PWM_3,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF2_TIM3, 4, 0)},   // TIM3_CH4  // rhomb.io SAI-A_SDI
    {PE_8,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 1)},   // TIM1_CH1N // rhomb.io IO5
    {PE_9,       PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 1, 0)},   // TIM1_CH1  // rhomb.io PWM1
    {PE_10,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 1)},   // TIM1_CH2N // rhomb.io QSPI_CLK
    {PE_11,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 2, 0)},   // TIM1_CH2  // rhomb.io QSPI_MEM_CS
    {PE_12,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 1)},   // TIM1_CH3N // rhomb.io QSPI_IO0
    {PE_13,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 3, 0)},   // TIM1_CH3  // rhomb.io QSPI_IO1
    {PE_14,      PWM_1,  STM_PIN_DATA_EXT(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF1_TIM1, 4, 0)},   // TIM1_CH4  // rhomb.io QSPI_IO2
    {NC, NC, 0}
};

//*** SERIAL ***

MBED_WEAK const PinMap PinMap_UART_TX[] = {
    {PA_0,       UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},    // rhomb.io AD0
    {PA_2,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io UART-A_TXD
    {PA_9,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io IO4
    {PB_6,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io SPI-A_CS0 
    {PB_10,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io IO2
    {PB_11,      LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // rhomb.io QSPI_CS0 
    {PC_1,       LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // rhomb.io AD4
    {PC_4,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io COMP-A_N
    {PC_10,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SDIO_DATA2
    {PC_10_ALT0, UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},    // rhomb.io SDIO_DATA2
    {PC_12,      UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},    // rhomb.io SDIO_CLK
    {PD_5,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io UART-B_TXD
    {PD_8,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io UART-C_TXD
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_UART_RX[] = {
    {PA_1,       UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},    // rhomb.io AD1
    {PA_3,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io UART-A_RXD
    {PA_10,      UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io OTG_ID
    {PB_7,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io INT1
    {PB_10,      LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // rhomb.io IO2
    {PB_11,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SPI_CS0
    {PC_0,       LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // rhomb.io AD5
    {PC_5,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io COMP-A_P
    {PC_11,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SDIO_DATA3
    {PC_11_ALT0, UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},    // rhomb.io SDIO_DATA3
    {PD_2,       UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},    // rhomb.io SDIO_CMD
    {PD_6,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io UART-B_RXD
    {PD_9,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io UART-C_RXD
    {NC, NC, 0}
};
 
MBED_WEAK const PinMap PinMap_UART_RTS[] = {
    {PA_1,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io AD1
    {PA_12,      UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io OTG_P
    {PA_15,      UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},    // rhomb.io INT2
    {PB_1,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io NMI
    {PB_3,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io INT0
    {PB_4,       UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},    // rhomb.io IO1
    {PB_12,      LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // rhomb.io 1WIRE // Connected to DS28E05X
    {PB_14,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SPI-A_CS1
    {PD_2,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SDIO_CMD
    {PD_4,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io UART-A_RTS
    {PD_12,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io IO12
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_UART_CTS[] = {
    {PA_0,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io AD0
    {PA_6,       UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SPI-A_MISO
    {PA_11,      UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io OTG_N
    {PB_4,       UART_1,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART1)},   // rhomb.io IO1
    {PB_5,       UART_5,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART5)},    // rhomb.io IO0
    {PB_7,       UART_4,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_UART4)},    // rhomb.io INT1
    {PB_13,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io SPI-A_CS2
    {PB_13_ALT0, LPUART_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF8_LPUART1)}, // rhomb.io SPI-A_CS2
    {PD_3,       UART_2,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART2)},   // rhomb.io UART-A_CTS
    {PD_11,      UART_3,  STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF7_USART3)},   // rhomb.io IO11
    {NC, NC, 0}
};

//*** SPI ***

MBED_WEAK const PinMap PinMap_SPI_MOSI[] = {
    {PA_7,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io SPI-A_MOSI
    {PB_5,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io IO0
    {PB_5_ALT0,  SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io IO0
    {PB_15,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io IO7
    {PC_3,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io IO14
    {PC_12,      SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io SDIO_CLK
    {PD_4,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io UART-A_RTS
    {PE_15,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io QSPI_IO3
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_SPI_MISO[] = {
    {PA_6,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io SPI-A_MISO
    {PB_4,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io IO1
    {PB_4_ALT0,  SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io IO1
    {PB_14,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io SPI-A_CS1
    {PC_2,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io IO15
    {PC_11,      SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io SDIO_DATA3
    {PD_3,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io UART-A_CTS
    {PE_14,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io QSPI_IO2
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_SPI_SCLK[] = {
    {PA_5,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io SPI-A_CLK
    {PB_3,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io INT0
    {PB_3_ALT0,  SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io INT0
    {PB_10,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io IO2
    {PB_13,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io SPI-A_CS2
    {PC_10,      SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io SDIO_DATA2
    {PD_1,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io CAN-A_TX
    {PE_13,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io QSPI_IO1
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_SPI_SSEL[] = {
    {PA_4,       SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io AD2
    {PA_4_ALT0,  SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io AD2
    {PA_15,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io INT2
    {PA_15_ALT0, SPI_3, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF6_SPI3)}, // rhomb.io INT2
    {PB_9,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io I2C-A_SDA
    {PB_12,      SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io 1WIRE // Connected to DS28E05X
    {PD_0,       SPI_2, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI2)}, // rhomb.io CAN-A_RX
    {PE_12,      SPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF5_SPI1)}, // rhomb.io QSPI_IO0
    {NC, NC, 0}
};

//*** CAN ***

MBED_WEAK const PinMap PinMap_CAN_RD[] = {
    {PA_11,      CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // rhomb.io OTG_N
    {PB_8,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // rhomb.io I2C-A_SCL
    {PD_0,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // rhomb.io CAN-A_RX
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_CAN_TD[] = {
    {PA_12,      CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // rhomb.io OTG_P 
    {PB_9,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // rhomb.io I2C-A_SDA
    {PD_1,       CAN_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_NOPULL, GPIO_AF9_CAN1)}, // rhomb.io CAN-A_TX
    {NC, NC, 0}
};

//*** QUADSPI ***

MBED_WEAK const PinMap PinMap_QSPI_DATA0[] = {
    {PB_1,      QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO0 // rhomb.io NMI 
    {PE_12,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO0 // rhomb.io QSPI_IO0 // Connected to MT25QL128ABA1EW7
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_QSPI_DATA1[] = {
    {PB_0,      QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO1 // rhomb.io AD3
    {PE_13,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO1 // rhomb.io QSPI_IO1 // Connected to MT25QL128ABA1EW7
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_QSPI_DATA2[] = {
    {PA_7,      QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO2 // rhomb.io SPI_A_MOSI 
    {PE_14,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO2 // rhomb.io QSPI_IO2 // Connected to MT25QL128ABA1EW7
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_QSPI_DATA3[] = {
    {PA_6,      QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO3 // rhomb.io SPI_A_MISO  
    {PE_15,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_BK1_IO3 // rhomb.io QSPI_IO3 // Connected to MT25QL128ABA1EW7
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_QSPI_SCLK[] = {
    {PB_10,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_CLK // rhomb.io IO2
    {PE_10,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_CLK // rhomb.io QSPI_CLK // Connected to MT25QL128ABA1EW7
    {NC, NC, 0}
};

MBED_WEAK const PinMap PinMap_QSPI_SSEL[] = {
    {PB_11,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_NCS // rhomb.io QSPI_CS0
    {PE_11,     QSPI_1, STM_PIN_DATA(STM_MODE_AF_PP, GPIO_PULLUP, GPIO_AF10_QUADSPI)},  // QUADSPI_NCS // rhomb.io QSPI_MEM_CS // Connected to MT25QL128ABA1EW7
    {NC, NC, 0}
};
