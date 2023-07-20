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
#include "Enchant/Domain/Model/Gs2EnchantEzBalanceParameterModelDomain.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterValueModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnchantBalanceParameterModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantBalanceParameterModel
{
    GENERATED_BODY()

    Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnchantBalanceParameterModelValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    int64 TotalValue = 0;
    UPROPERTY(BlueprintReadOnly)
    FString InitialValueStrategy = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2EnchantBalanceParameterValueModel> Parameters = TArray<FGs2EnchantBalanceParameterValueModel>();
};

inline FGs2EnchantBalanceParameterModelValue EzBalanceParameterModelToFGs2EnchantBalanceParameterModelValue(
    const Gs2::UE5::Enchant::Model::FEzBalanceParameterModelPtr Model
)
{
    FGs2EnchantBalanceParameterModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantBalanceParameterModelFunctionLibrary::EzBalanceParameterModelToFGs2EnchantBalanceParameterModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.TotalValue = Model->GetTotalValue() ? *Model->GetTotalValue() : 0;
    Value.InitialValueStrategy = Model->GetInitialValueStrategy() ? *Model->GetInitialValueStrategy() : "";
    Value.Parameters = Model->GetParameters() ? [&]
    {
        TArray<FGs2EnchantBalanceParameterValueModel> r;
        for (auto v : *Model->GetParameters())
        {
            r.Add(EzBalanceParameterValueModelToFGs2EnchantBalanceParameterValueModel(v));
        }
        return r;
    }() : TArray<FGs2EnchantBalanceParameterValueModel>();
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzBalanceParameterModelPtr FGs2EnchantBalanceParameterModelValueToEzBalanceParameterModel(
    const FGs2EnchantBalanceParameterModelValue Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzBalanceParameterModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithTotalValue(Model.TotalValue)
        ->WithInitialValueStrategy(Model.InitialValueStrategy)
        ->WithParameters([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzBalanceParameterValueModelPtr>>();
            for (auto v : Model.Parameters) {
                r->Add(FGs2EnchantBalanceParameterValueModelToEzBalanceParameterValueModel(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2EnchantBalanceParameterModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};