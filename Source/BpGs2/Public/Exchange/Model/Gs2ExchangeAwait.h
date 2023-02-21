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
#include "Exchange/Domain/Model/Gs2ExchangeEzAwaitGameSessionDomain.h"
#include "Gs2ExchangeAwait.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeOwnAwait
{
    GENERATED_BODY()

    Gs2::UE5::Exchange::Domain::Model::FEzAwaitGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ExchangeAwaitValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString RateName = "";
    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    int64 ExchangedAt = 0;
};

inline FGs2ExchangeAwaitValue EzAwaitToFGs2ExchangeAwaitValue(
    const Gs2::UE5::Exchange::Model::FEzAwaitPtr Model
)
{
    FGs2ExchangeAwaitValue Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.RateName = Model->GetRateName() ? *Model->GetRateName() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.ExchangedAt = Model->GetExchangedAt() ? *Model->GetExchangedAt() : 0;
    return Value;
}

inline Gs2::UE5::Exchange::Model::FEzAwaitPtr FGs2ExchangeAwaitValueToEzAwait(
    const FGs2ExchangeAwaitValue Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzAwait>()
        ->WithUserId(Model.UserId)
        ->WithRateName(Model.RateName)
        ->WithName(Model.Name)
        ->WithExchangedAt(Model.ExchangedAt);
}

UCLASS()
class BPGS2_API UGs2ExchangeAwaitFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};