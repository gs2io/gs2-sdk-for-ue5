/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "Limit/Model/Gs2LimitUser.h"
#include "Limit/Model/Gs2LimitCounter.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Limit/Model/Gs2LimitCounter.h"
#include "Core/BpGs2Constant.h"

FGs2LimitOwnCounter UGs2LimitUserFunctionLibrary::OwnCounter(
    FGs2LimitOwnUser User,
    FString LimitName,
    FString CounterName
)
{
    FGs2LimitOwnCounter Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitUserFunctionLibrary::OwnCounter] User parameter specification is missing."))
        return Return;
    }
    if (LimitName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitUserFunctionLibrary::OwnCounter] LimitName parameter specification is missing."))
        return Return;
    }
    if (CounterName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2LimitUserFunctionLibrary::OwnCounter] CounterName parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->Counter(
        LimitName,
        CounterName
    );
    return Return;
}