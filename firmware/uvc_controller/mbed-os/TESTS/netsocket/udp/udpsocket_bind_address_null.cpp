/*
 * Copyright (c) 2018, ARM Limited, All Rights Reserved
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

#include "greentea-client/test_env.h"
#include "mbed.h"
#include "udp_tests.h"
#include "UDPSocket.h"
#include "unity/unity.h"
#include "utest.h"

using namespace utest::v1;

void UDPSOCKET_BIND_ADDRESS_NULL()
{
    UDPSocket *sock = new UDPSocket;
    if (!sock) {
        TEST_FAIL();
    }
    TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, sock->open(NetworkInterface::get_default_instance()));
    nsapi_error_t bind_result = sock->bind(nullptr);
    if (bind_result == NSAPI_ERROR_UNSUPPORTED) {
        TEST_IGNORE_MESSAGE("bind() not supported");
    } else {
        TEST_ASSERT_EQUAL(NSAPI_ERROR_OK, bind_result);
    }

    delete sock;
}
