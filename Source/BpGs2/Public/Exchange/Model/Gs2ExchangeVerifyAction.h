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

#pragma once

#include "CoreMinimal.h"

#include "Exchange/Model/Gs2ExchangeEzVerifyAction.h"
#include "Gs2ExchangeVerifyAction.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeVerifyAction
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Action = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Request = "";
};

inline FGs2ExchangeVerifyAction EzVerifyActionToFGs2ExchangeVerifyAction(
    const Gs2::UE5::Exchange::Model::FEzVerifyActionPtr Model
)
{
    FGs2ExchangeVerifyAction Value;
    Value.Action = Model->GetAction() ? *Model->GetAction() : "";
    Value.Request = Model->GetRequest() ? *Model->GetRequest() : "";
    return Value;
}

inline Gs2::UE5::Exchange::Model::FEzVerifyActionPtr FGs2ExchangeVerifyActionToEzVerifyAction(
    const FGs2ExchangeVerifyAction Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzVerifyAction>()
        ->WithAction(Model.Action)
        ->WithRequest(Model.Request);
}