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

#include "mbed.h"
#include "s5js100_pwr.h"
#include "modem_link_device_shmem.h"
#include "modem_io_device.h"


extern "C" {

    void s5js100_modem_start(void)
    {
        pShmemLinkDevice = new ShmemLinkDevice();
        pShmemLinkDevice->ShmemLinkDevice_start();
    }

    void s5js100_modem_stop(void)
    {
        delete pShmemLinkDevice;
    }

}

