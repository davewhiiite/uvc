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
#ifndef _TEST_S009_ITS_DATA_TESTS_H_
#define _TEST_S009_ITS_DATA_TESTS_H_

#include "val_internal_trusted_storage.h"

#define SST_FUNCTION val->its_function
#define psa_sst_uid_t psa_its_uid_t

typedef struct {
    enum its_function_code  api;
    psa_its_status_t        status;
} test_data;

static struct psa_its_info_t info;
static const test_data s009_data[] = {
{
 0, 0 /* This is dummy for index0 */
},
{
 VAL_ITS_SET, PSA_ITS_SUCCESS /* Call set API with NULL write buffer and 0 length */
},
{
 VAL_ITS_GET_INFO, PSA_ITS_SUCCESS /* Verify UID is created */
},
{
 VAL_ITS_GET, PSA_ITS_SUCCESS /* Call get API with NULL write buffer and 0 length */
},
{
 VAL_ITS_REMOVE, PSA_ITS_SUCCESS /* Remove the storage entity */
},
{
 VAL_ITS_GET_INFO, PSA_ITS_ERROR_UID_NOT_FOUND /* Verify UID is removed */
},
{
 VAL_ITS_SET, PSA_ITS_SUCCESS /* Create storage of zero size and valid write buffer */
},
{
 VAL_ITS_GET_INFO, PSA_ITS_SUCCESS /* Call get_info API to check data size */
},
{
 0, 0 /* This is dummy for index8 */
},
{
 VAL_ITS_GET, PSA_ITS_SUCCESS /* Call get API with 0 length and NULL read buffer */
},
{
 VAL_ITS_SET, PSA_ITS_SUCCESS /* Increase the asset size */
},
{
 VAL_ITS_REMOVE, PSA_ITS_SUCCESS /* Remove the storage entity */
},
};
#endif /* _TEST_S009_ITS_DATA_TESTS_H_ */
