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
#include "Exchange/Model/Gs2ExchangeConfig.h"
#include "Core/BpGs2Constant.h"
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

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString RateName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 SkipSeconds = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2ExchangeConfig> Config = TArray<FGs2ExchangeConfig>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 ExchangedAt = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 AcquirableAt = 0;
};

inline FGs2ExchangeAwaitValue EzAwaitToFGs2ExchangeAwaitValue(
    const Gs2::UE5::Exchange::Model::FEzAwaitPtr Model
)
{
    FGs2ExchangeAwaitValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeAwaitFunctionLibrary::EzAwaitToFGs2ExchangeAwaitValue] Model parameter specification is missing."))
        return Value;
    }
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.RateName = Model->GetRateName() ? *Model->GetRateName() : "";
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.SkipSeconds = Model->GetSkipSeconds() ? *Model->GetSkipSeconds() : 0;
    Value.Config = Model->GetConfig() ? [&]
    {
        TArray<FGs2ExchangeConfig> r;
        for (auto v : *Model->GetConfig())
        {
            r.Add(EzConfigToFGs2ExchangeConfig(v));
        }
        return r;
    }() : TArray<FGs2ExchangeConfig>();
    Value.ExchangedAt = Model->GetExchangedAt() ? *Model->GetExchangedAt() : 0;
    Value.AcquirableAt = Model->GetAcquirableAt() ? *Model->GetAcquirableAt() : 0;
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
        ->WithSkipSeconds(Model.SkipSeconds)
        ->WithConfig([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzConfigPtr>>();
            for (auto v : Model.Config) {
                r->Add(FGs2ExchangeConfigToEzConfig(v));
            }
            return r;
        }())
        ->WithExchangedAt(Model.ExchangedAt)
        ->WithAcquirableAt(Model.AcquirableAt);
}

UCLASS()
class BPGS2_API UGs2ExchangeAwaitFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};