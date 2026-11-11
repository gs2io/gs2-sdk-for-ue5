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

#include "Enhance/Model/Gs2EnhanceEzUnleashMaterialSelection.h"
#include "Gs2EnhanceUnleashMaterialSelection.generated.h"

USTRUCT(BlueprintType)
struct FGs2EnhanceUnleashMaterialSelection
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FString> ItemSetIds = TArray<FString>();
};

inline FGs2EnhanceUnleashMaterialSelection EzUnleashMaterialSelectionToFGs2EnhanceUnleashMaterialSelection(
    const Gs2::UE5::Enhance::Model::FEzUnleashMaterialSelectionPtr Model
)
{
    FGs2EnhanceUnleashMaterialSelection Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.ItemSetIds = Model->GetItemSetIds() ? [&]
    {
        TArray<FString> r;
        for (auto v : *Model->GetItemSetIds())
        {
            r.Add(v);
        }
        return r;
    }() : TArray<FString>();
    return Value;
}

inline Gs2::UE5::Enhance::Model::FEzUnleashMaterialSelectionPtr FGs2EnhanceUnleashMaterialSelectionToEzUnleashMaterialSelection(
    const FGs2EnhanceUnleashMaterialSelection Model
)
{
    return MakeShared<Gs2::UE5::Enhance::Model::FEzUnleashMaterialSelection>()
        ->WithName(Model.Name)
        ->WithItemSetIds([&]{
            auto r = MakeShared<TArray<FString>>();
            for (auto v : Model.ItemSetIds) {
                r->Add(v);
            }
            return r;
        }());
}