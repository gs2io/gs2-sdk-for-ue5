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

#include "BpGs2/Public/SerialKey/Model/Gs2SerialKeyUser.h"
#include "BpGs2/Public/SerialKey/Model/Gs2SerialKeySerialKey.h"
#include "Core/Model/Gs2AccessToken.h"
#include "SerialKey/Model/Gs2SerialKeySerialKey.h"
#include "Core/BpGs2Constant.h"

FGs2SerialKeySerialKey UGs2SerialKeyUserFunctionLibrary::SerialKey(
    FGs2SerialKeyUser User,
    FString SerialKeyCode
)
{
    FGs2SerialKeySerialKey Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyUserFunctionLibrary::SerialKey] User parameter specification is missing."))
        return Return;
    }
    if (SerialKeyCode == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyUserFunctionLibrary::SerialKey] SerialKeyCode parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->SerialKey(
        SerialKeyCode
    );
    return Return;
}

FGs2SerialKeyOwnSerialKey UGs2SerialKeyUserFunctionLibrary::OwnSerialKey(
    FGs2SerialKeyOwnUser User,
    FString SerialKeyCode
)
{
    FGs2SerialKeyOwnSerialKey Return;
    if (User.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyUserFunctionLibrary::OwnSerialKey] User parameter specification is missing."))
        return Return;
    }
    if (SerialKeyCode == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2SerialKeyUserFunctionLibrary::OwnSerialKey] SerialKeyCode parameter specification is missing."))
        return Return;
    }
    Return.Value = User.Value->SerialKey(
        SerialKeyCode
    );
    return Return;
}