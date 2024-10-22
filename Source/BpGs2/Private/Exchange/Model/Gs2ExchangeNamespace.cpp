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

#include "Exchange/Model/Gs2ExchangeNamespace.h"
#include "Exchange/Domain/EzGs2Exchange.h"
#include "Exchange/Model/Gs2ExchangeRateModel.h"
#include "Exchange/Model/Gs2ExchangeIncrementalRateModel.h"
#include "Core/Model/Gs2AccessToken.h"
#include "Exchange/Model/Gs2ExchangeRateModel.h"
#include "Exchange/Model/Gs2ExchangeUser.h"
#include "Exchange/Model/Gs2ExchangeIncrementalRateModel.h"
#include "Core/BpGs2Constant.h"

FGs2ExchangeRateModel UGs2ExchangeNamespaceFunctionLibrary::RateModel(
    FGs2ExchangeNamespace Namespace,
    FString RateName
)
{
    FGs2ExchangeRateModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeNamespaceFunctionLibrary::RateModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (RateName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeNamespaceFunctionLibrary::RateModel] RateName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->RateModel(
        RateName
    );
    return Return;
}

FGs2ExchangeOwnUser UGs2ExchangeNamespaceFunctionLibrary::Me(
    FGs2ExchangeNamespace Namespace,
    FGs2AccessToken AccessToken
)
{
    FGs2ExchangeOwnUser Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeNamespaceFunctionLibrary::Me] Namespace parameter specification is missing."))
        return Return;
    }
    if (AccessToken.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeNamespaceFunctionLibrary::Me] AccessToken parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->Me(AccessToken.Value);
    return Return;
}

FGs2ExchangeIncrementalRateModel UGs2ExchangeNamespaceFunctionLibrary::IncrementalRateModel(
    FGs2ExchangeNamespace Namespace,
    FString RateName
)
{
    FGs2ExchangeIncrementalRateModel Return;
    if (Namespace.Value == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeNamespaceFunctionLibrary::IncrementalRateModel] Namespace parameter specification is missing."))
        return Return;
    }
    if (RateName == "") {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeNamespaceFunctionLibrary::IncrementalRateModel] RateName parameter specification is missing."))
        return Return;
    }
    Return.Value = Namespace.Value->IncrementalRateModel(
        RateName
    );
    return Return;
}