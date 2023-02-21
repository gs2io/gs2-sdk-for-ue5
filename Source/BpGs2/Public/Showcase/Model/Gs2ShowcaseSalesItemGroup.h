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

#include "Showcase/Model/Gs2ShowcaseEzSalesItemGroup.h"
#include "Showcase/Model/Gs2ShowcaseSalesItem.h"
#include "Gs2ShowcaseSalesItemGroup.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseSalesItemGroup
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(BlueprintReadWrite)
    TArray<FGs2ShowcaseSalesItem> SalesItems = TArray<FGs2ShowcaseSalesItem>();
};

inline FGs2ShowcaseSalesItemGroup EzSalesItemGroupToFGs2ShowcaseSalesItemGroup(
    const Gs2::UE5::Showcase::Model::FEzSalesItemGroupPtr Model
)
{
    FGs2ShowcaseSalesItemGroup Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.SalesItems = Model->GetSalesItems() ? [&]
    {
        TArray<FGs2ShowcaseSalesItem> r;
        for (auto v : *Model->GetSalesItems())
        {r.Add(EzSalesItemToFGs2ShowcaseSalesItem(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseSalesItem>();
    return Value;
}

inline Gs2::UE5::Showcase::Model::FEzSalesItemGroupPtr FGs2ShowcaseSalesItemGroupToEzSalesItemGroup(
    const FGs2ShowcaseSalesItemGroup Model
)
{
    return MakeShared<Gs2::UE5::Showcase::Model::FEzSalesItemGroup>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithSalesItems([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzSalesItemPtr>>();
            for (auto v : Model.SalesItems) {
                r->Add(FGs2ShowcaseSalesItemToEzSalesItem(v));
            }
            return r;
        }());
}