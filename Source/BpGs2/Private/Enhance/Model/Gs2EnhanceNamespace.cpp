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

#include "Enhance/Model/Gs2EnhanceNamespace.h"
#include "Enhance/Domain/EzGs2Enhance.h"
#include "Enhance/Model/Gs2EnhanceRateModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Enhance/Model/Gs2EnhanceRateModel.h"
#include "Enhance/Model/Gs2EnhanceUser.h"
#include "Core/BpGs2Constant.h"

FGs2EnhanceRateModel UGs2EnhanceNamespaceFunctionLibrary::RateModel(
    FGs2EnhanceNamespace Namespace,
    FString RateName
)
{
    FGs2EnhanceRateModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceNamespaceFunctionLibrary::RateModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (RateName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceNamespaceFunctionLibrary::RateModel] RateName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->RateModel(
        RateName
    );
    return Return;
}

FGs2EnhanceOwnUser UGs2EnhanceNamespaceFunctionLibrary::Me(
    FGs2EnhanceNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2EnhanceOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnhanceNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}