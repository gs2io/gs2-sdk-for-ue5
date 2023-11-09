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
#include "Enchant/Domain/Model/Gs2EnchantEzBalanceParameterStatusGameSessionDomain.h"
#include "Enchant/Model/Gs2EnchantBalanceParameterValue.h"
#include "Core/BpGs2Constant.h"
#include "Gs2EnchantBalanceParameterStatus.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnchantOwnBalanceParameterStatus
{
    GENERATED_BODY()

    Gs2::UE5::Enchant::Domain::Model::FEzBalanceParameterStatusGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2EnchantBalanceParameterStatusValue
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString ParameterName = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    FString PropertyId = "";
    UPROPERTY(Category = Gs2, BlueprintReadOnly)
    TArray<FGs2EnchantBalanceParameterValue> ParameterValues = TArray<FGs2EnchantBalanceParameterValue>();
};

inline FGs2EnchantBalanceParameterStatusValue EzBalanceParameterStatusToFGs2EnchantBalanceParameterStatusValue(
    const Gs2::UE5::Enchant::Model::FEzBalanceParameterStatusPtr Model
)
{
    FGs2EnchantBalanceParameterStatusValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2EnchantBalanceParameterStatusFunctionLibrary::EzBalanceParameterStatusToFGs2EnchantBalanceParameterStatusValue] Model parameter specification is missing."))
        return Value;
    }
    Value.ParameterName = Model->GetParameterName() ? *Model->GetParameterName() : "";
    Value.PropertyId = Model->GetPropertyId() ? *Model->GetPropertyId() : "";
    Value.ParameterValues = Model->GetParameterValues() ? [&]
    {
        TArray<FGs2EnchantBalanceParameterValue> r;
        for (auto v : *Model->GetParameterValues())
        {
            r.Add(EzBalanceParameterValueToFGs2EnchantBalanceParameterValue(v));
        }
        return r;
    }() : TArray<FGs2EnchantBalanceParameterValue>();
    return Value;
}

inline Gs2::UE5::Enchant::Model::FEzBalanceParameterStatusPtr FGs2EnchantBalanceParameterStatusValueToEzBalanceParameterStatus(
    const FGs2EnchantBalanceParameterStatusValue Model
)
{
    return MakeShared<Gs2::UE5::Enchant::Model::FEzBalanceParameterStatus>()
        ->WithParameterName(Model.ParameterName)
        ->WithPropertyId(Model.PropertyId)
        ->WithParameterValues([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Enchant::Model::FEzBalanceParameterValuePtr>>();
            for (auto v : Model.ParameterValues) {
                r->Add(FGs2EnchantBalanceParameterValueToEzBalanceParameterValue(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2EnchantBalanceParameterStatusFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};