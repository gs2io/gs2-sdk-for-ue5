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
#include "Enchant/Domain/Model/Gs2EnchantEzRarityParameterStatusGameSessionDomain.h"
#include "Enchant/Model/Gs2EnchantRarityParameterValue.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnchantRarityParameterStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantOwnRarityParameterStatus
{
    GENERATED_BODY()

    Gs2::UE5::Enchant::Domain::Model::FEzRarityParameterStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnchantRarityParameterStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ParameterName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PropertyId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2EnchantRarityParameterValue> ParameterValues = TArray<FGs2EnchantRarityParameterValue>();
};

inline FGs2EnchantRarityParameterStatusValue EzRarityParameterStatusToFGs2EnchantRarityParameterStatusValue(
    const Gs2::UE5::Enchant::Model::FEzRarityParameterStatusPtr Model
)
{
    FGs2EnchantRarityParameterStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantRarityParameterStatusFunctionLibrary::EzRarityParameterStatusToFGs2EnchantRarityParameterStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ParameterName = Model->GetParameterName() ? *Model->GetParameterName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.ParameterValues = Model->GetParameterValues() ? [&]
    {
        TArray<FGs2EnchantRarityParameterValue> r;
        for (auto v : *Model->GetParameterValues())
        {
            r.Add(EzRarityParameterValueToFGs2EnchantRarityParameterValue(v));
        }
        return r;
    }() : TArray<FGs2EnchantRarityParameterValue>();
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzRarityParameterStatusPtr FGs2EnchantRarityParameterStatusValueToEzRarityParameterStatus(
    const FGs2EnchantRarityParameterStatusValue Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzRarityParameterStatus>()
        ->WithParameterName(Model.ParameterName)
        ->WithPropertyId(Model.PropertyId)
        ->WithParameterValues([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzRarityParameterValuePtr>>();
            for (auto v : Model.ParameterValues) {
                r->Add(FGs2EnchantRarityParameterValueToEzRarityParameterValue(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2EnchantRarityParameterStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};