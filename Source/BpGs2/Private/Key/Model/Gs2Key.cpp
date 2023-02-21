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
 *
 * deny overwrite
 */

#include "Key/Model/Gs2Key.h"
#include "BpGs2/Public/Key/Model/Gs2KeyNamespace.h"
#include "Core/BpGs2Constant.h"

FGs2Key UGs2KeyFunctionLibrary::Service(
    FGs2Client Client
)
{
    FGs2Key Return;
    if (Client.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2KeyFunctionLibrary::Service] Client parameter specification is missing."))
        return Return;
    }
    return Return;
}
FGs2KeyNamespace UGs2KeyFunctionLibrary::Namespace(
    FGs2Key Service,
    FString NamespaceName
)
{
    FGs2KeyNamespace Return;
    if (NamespaceName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2KeyFunctionLibrary::Namespace] NamespaceName parameter specification is missing."))
        return Return;
    }
    Return.NamespaceName = NamespaceName;
    return Return;
}