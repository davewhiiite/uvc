/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
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
#ifndef MBED_PORTNAMES_H
#define MBED_PORTNAMES_H

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    Port0 = 0,
    Port1 = 1
} PortName;

typedef enum {
    Flexcomm0 = 0,
    Flexcomm1 = 1,
    Flexcomm2 = 2,
    Flexcomm3 = 3,
    Flexcomm4 = 4,
    Flexcomm5 = 5,
    Flexcomm6 = 6,
    Flexcomm7 = 7,
    Flexcomm8 = 8,
    Flexcomm9 = 9
} FlexcommName;

#ifdef __cplusplus
}
#endif

#endif
