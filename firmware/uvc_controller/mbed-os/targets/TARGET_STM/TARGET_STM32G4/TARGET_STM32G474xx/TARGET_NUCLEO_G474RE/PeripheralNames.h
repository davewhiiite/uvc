/* mbed Microcontroller Library
 * Copyright (c) 2016 ARM Limited
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
 */
#ifndef MBED_PERIPHERALNAMES_H
#define MBED_PERIPHERALNAMES_H

#include "cmsis.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    ADC_1 = (int)ADC1_BASE,
    ADC_2 = (int)ADC2_BASE,
    ADC_3 = (int)ADC3_BASE,
    ADC_4 = (int)ADC4_BASE,
    ADC_5 = (int)ADC5_BASE
} ADCName;

typedef enum {
    DAC_1 = (int)DAC1_BASE,
    DAC_2 = (int)DAC2_BASE,
    DAC_3 = (int)DAC3_BASE,
    DAC_4 = (int)DAC4_BASE,

} DACName;

typedef enum {
    UART_1   = (int)USART1_BASE,
    UART_2   = (int)USART2_BASE,
    UART_3   = (int)USART3_BASE,
    UART_4   = (int)UART4_BASE,
    UART_5   = (int)UART5_BASE,
    LPUART_1 = (int)LPUART1_BASE
} UARTName;

#define DEVICE_SPI_COUNT 5
typedef enum {
    SPI_1 = (int)SPI1_BASE,
    SPI_2 = (int)SPI2_BASE,
    SPI_3 = (int)SPI3_BASE,
    SPI_4 = (int)SPI4_BASE,
} SPIName;

typedef enum {
    I2C_1 = (int)I2C1_BASE,
    I2C_2 = (int)I2C2_BASE,
    I2C_3 = (int)I2C3_BASE,
    I2C_4 = (int)I2C4_BASE
} I2CName;

typedef enum {
    PWM_1  = (int)TIM1_BASE,
    PWM_2  = (int)TIM2_BASE,
    PWM_3  = (int)TIM3_BASE,
    PWM_4  = (int)TIM4_BASE,
    PWM_5  = (int)TIM5_BASE,
    PWM_6  = (int)TIM6_BASE,
    PWM_7  = (int)TIM7_BASE,
    PWM_8  = (int)TIM8_BASE,
    PWM_15 = (int)TIM15_BASE,
    PWM_16 = (int)TIM16_BASE,
    PWM_17 = (int)TIM17_BASE,
    PWM_20 = (int)TIM20_BASE
} PWMName;

typedef enum {
    CAN_1 = (int)FDCAN1_BASE,
    CAN_2 = (int)FDCAN2_BASE,
    CAN_3 = (int)FDCAN3_BASE
} CANName;

typedef enum {
    QSPI_1 = (int)QSPI_R_BASE,
} QSPIName;

typedef enum {
    USB_FS = (int)USB_BASE
} USBName;

#ifdef __cplusplus
}
#endif

#endif
