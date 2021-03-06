/*
 * Copyright (c) 2014-2018, ARM Limited, All Rights Reserved
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License"); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
/**
 * \file pn512_timer.h
 * \copyright Copyright (c) ARM Ltd 2014
 * \author Donatien Garnier
 */

#ifndef PN512_TIMER_H_
#define PN512_TIMER_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "stack/nfc_common.h"
#include "pn512_types.h"

void pn512_timer_config(pn512_t *pPN512, bool autostart, uint16_t prescaler, uint16_t countdown_value);

void pn512_timer_start(pn512_t *pPN512);
void pn512_timer_stop(pn512_t *pPN512);

#ifdef __cplusplus
}
#endif

#endif /* PN512_TIMER_H_ */
