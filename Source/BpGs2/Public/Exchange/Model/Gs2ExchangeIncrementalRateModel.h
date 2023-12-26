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
#include "Exchange/Domain/Model/Gs2ExchangeEzIncrementalRateModelDomain.h"
#include "Exchange/Model/Gs2ExchangeConsumeAction.h"
#include "Exchange/Model/Gs2ExchangeAcquireAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ExchangeIncrementalRateModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2ExchangeIncrementalRateModel
{
    GENERATED_BODY()

    Gs2::UE5::Exchange::Domain::Model::FEzIncrementalRateModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ExchangeIncrementalRateModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString CalculateType = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FGs2ExchangeConsumeAction ConsumeAction = FGs2ExchangeConsumeAction();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 BaseValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int64 CoefficientValue = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ExchangeCountId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaximumExchangeCount = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2ExchangeAcquireAction> AcquireActions = TArray<FGs2ExchangeAcquireAction>();
};

inline FGs2ExchangeIncrementalRateModelValue EzIncrementalRateModelToFGs2ExchangeIncrementalRateModelValue(
    const Gs2::UE5::Exchange::Model::FEzIncrementalRateModelPtr Model
)
{
    FGs2ExchangeIncrementalRateModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ExchangeIncrementalRateModelFunctionLibrary::EzIncrementalRateModelToFGs2ExchangeIncrementalRateModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.CalculateType = Model->GetCalculateType() ? *Model->GetCalculateType() : "";
    Value.ConsumeAction = Model->GetConsumeAction() ? EzConsumeActionToFGs2ExchangeConsumeAction(Model->GetConsumeAction()) : FGs2ExchangeConsumeAction();
    Value.BaseValue = Model->GetBaseValue() ? *Model->GetBaseValue() : 0;
    Value.CoefficientValue = Model->GetCoefficientValue() ? *Model->GetCoefficientValue() : 0;
    Value.ExchangeCountId = Model->GetExchangeCountId() ? *Model->GetExchangeCountId() : "";
    Value.MaximumExchangeCount = Model->GetMaximumExchangeCount() ? *Model->GetMaximumExchangeCount() : 0;
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

inline Gs2::UE5::Exchange::Model::FEzIncrementalRateModelPtr FGs2ExchangeIncrementalRateModelValueToEzIncrementalRateModel(
    const FGs2ExchangeIncrementalRateModelValue Model
)
{
    return MakeShared<Gs2::UE5::Exchange::Model::FEzIncrementalRateModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithCalculateType(Model.CalculateType)
        ->WithConsumeAction(FGs2ExchangeConsumeActionToEzConsumeAction(Model.ConsumeAction))
        ->WithBaseValue(Model.BaseValue)
        ->WithCoefficientValue(Model.CoefficientValue)
        ->WithExchangeCountId(Model.ExchangeCountId)
        ->WithMaximumExchangeCount(Model.MaximumExchangeCount)
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Exchange::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2ExchangeAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2ExchangeIncrementalRateModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};