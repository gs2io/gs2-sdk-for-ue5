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
#include "Exchange/Domain/Model/Gs2ExchangeEzRateModelDomain.h"
#include "Exchange/Model/Gs2ExchangeVerifyAction.h"
#include "Exchange/Model/Gs2ExchangeConsumeAction.h"
#include "Exchange/Model/Gs2ExchangeAcquireAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ExchangeRateModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeRateModel
{
    GENERATED_BODY()

    Gs2::UE5::Exchange::Domain::Model::FEzRateModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ExchangeRateModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString TimingType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 LockTime = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2ExchangeVerifyAction> VerifyActions = TArray<FGs2ExchangeVerifyAction>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2ExchangeConsumeAction> ConsumeActions = TArray<FGs2ExchangeConsumeAction>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2ExchangeAcquireAction> AcquireActions = TArray<FGs2ExchangeAcquireAction>();
};

inline FGs2ExchangeRateModelValue EzRateModelToFGs2ExchangeRateModelValue(
    const Gs2::UE5::Exchange::Model::FEzRateModelPtr Model
)
{
    FGs2ExchangeRateModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeRateModelFunctionLibrary::EzRateModelToFGs2ExchangeRateModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.TimingType = Model->GetTimingType() ? *Model->GetTimingType() : "";
    Value.LockTime = Model->GetLockTime() ? *Model->GetLockTime() : 0;
    Value.VerifyActions = Model->GetVerifyActions() ? [&]
    {
        TArray<FGs2ExchangeVerifyAction> r;
        for (auto v : *Model->GetVerifyActions())
        {
            r.Add(EzVerifyActionToFGs2ExchangeVerifyAction(v));
        }
        return r;
    }() : TArray<FGs2ExchangeVerifyAction>();
    Value.ConsumeActions = Model->GetConsumeActions() ? [&]
    {
        TArray<FGs2ExchangeConsumeAction> r;
        for (auto v : *Model->GetConsumeActions())
        {
            r.Add(EzConsumeActionToFGs2ExchangeConsumeAction(v));
        }
        return r;
    }() : TArray<FGs2ExchangeConsumeAction>();
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2ExchangeAcquireAction> r;
        for (auto v : *Model->GetAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2ExchangeAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2ExchangeAcquireAction>();
    return Value;
}

inline Gs2::UE5::Exchange::Model::FEzRateModelPtr FGs2ExchangeRateModelValueToEzRateModel(
    const FGs2ExchangeRateModelValue Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzRateModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTimingType(Model.TimingType)
        ->WithLockTime(Model.LockTime)
        ->WithVerifyActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzVerifyActionPtr>>();
            for (auto v : Model.VerifyActions) {
                r->Add(FGs2ExchangeVerifyActionToEzVerifyAction(v));
            }
            return r;
        }())
        ->WithConsumeActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzConsumeActionPtr>>();
            for (auto v : Model.ConsumeActions) {
                r->Add(FGs2ExchangeConsumeActionToEzConsumeAction(v));
            }
            return r;
        }())
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2ExchangeAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2ExchangeRateModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};