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
#include "Enchant/Domain/Model/Gs2EnchantEzRarityParameterModelDomain.h"
#include "Enchant/Model/Gs2EnchantRarityParameterCountModel.h"
#include "Enchant/Model/Gs2EnchantRarityParameterValueModel.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnchantRarityParameterModel.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantRarityParameterModel
{
    GENERATED_BODY()

    Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterModelDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnchantRarityParameterModelValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    int32 MaximumParameterCount = 0;
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2EnchantRarityParameterCountModel> ParameterCounts = TArray<FGs2EnchantRarityParameterCountModel>();
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2EnchantRarityParameterValueModel> Parameters = TArray<FGs2EnchantRarityParameterValueModel>();
};

inline FGs2EnchantRarityParameterModelValue EzRarityParameterModelToFGs2EnchantRarityParameterModelValue(
    const Gs2::UE5::Enchant::Model::FEzRarityParameterModelPtr Model
)
{
    FGs2EnchantRarityParameterModelValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantRarityParameterModelFunctionLibrary::EzRarityParameterModelToFGs2EnchantRarityParameterModelValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.MaximumParameterCount = Model->GetMaximumParameterCount() ? *Model->GetMaximumParameterCount() : 0;
    Value.ParameterCounts = Model->GetParameterCounts() ? [&]
    {
        TArray<FGs2EnchantRarityParameterCountModel> r;
        for (auto v : *Model->GetParameterCounts())
        {
            r.Add(EzRarityParameterCountModelToFGs2EnchantRarityParameterCountModel(v));
        }
        return r;
    }() : TArray<FGs2EnchantRarityParameterCountModel>();
    Value.Parameters = Model->GetParameters() ? [&]
    {
        TArray<FGs2EnchantRarityParameterValueModel> r;
        for (auto v : *Model->GetParameters())
        {
            r.Add(EzRarityParameterValueModelToFGs2EnchantRarityParameterValueModel(v));
        }
        return r;
    }() : TArray<FGs2EnchantRarityParameterValueModel>();
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzRarityParameterModelPtr FGs2EnchantRarityParameterModelValueToEzRarityParameterModel(
    const FGs2EnchantRarityParameterModelValue Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzRarityParameterModel>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithMaximumParameterCount(Model.MaximumParameterCount)
        ->WithParameterCounts([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzRarityParameterCountModelPtr>>();
            for (auto v : Model.ParameterCounts) {
                r->Add(FGs2EnchantRarityParameterCountModelToEzRarityParameterCountModel(v));
            }
            return r;
        }())
        ->WithParameters([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzRarityParameterValueModelPtr>>();
            for (auto v : Model.Parameters) {
                r->Add(FGs2EnchantRarityParameterValueModelToEzRarityParameterValueModel(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2EnchantRarityParameterModelFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};