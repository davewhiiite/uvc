/** @file
 * Copyright (c) 2019, Arm Limited or its affiliates. All rights reserved.
 * SPDX-License-Identifier : Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
**/
#ifndef _TEST_S006_ITS_DATA_TESTS_H_
#define _TEST_S006_ITS_DATA_TESTS_H_

#include "val_internal_trusted_storage.h"

#define SST_FUNCTION            val->its_function
#define PSA_SST_FLAG_WRITE_ONCE PSA_ITS_FLAG_WRITE_ONCE
#define psa_sst_uid_t           psa_its_uid_t
#define psa_sst_create_flags_t  psa_its_create_flags_t

typedef struct {
    enum its_function_code  api;
    psa_its_status_t        status;
} test_data;

static struct psa_its_info_t info;
static const test_data s006_data[] = {
{
 0, PSA_ITS_ERROR_FLAGS_NOT_SUPPORTED /* This is dummy for index0 */
},
{
 VAL_ITS_SET, PSA_ITS_SUCCESS /* Create a valid storage entity with different flag values */
},
{
 VAL_ITS_GET_INFO, PSA_ITS_SUCCESS /* Validate the flag value get_info API */
},
{
 0, 0 /* Index not used */
},
{
 VAL_ITS_REMOVE, PSA_ITS_SUCCESS /* Remove the storage entity */
},
{
 VAL_ITS_REMOVE, PSA_ITS_ERROR_UID_NOT_FOUND /* Storage entity remove fails */
},
};
#endif /* _TEST_S006_ITS_DATA_TESTS_H_ */
