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

#include "Showcase/Model/Gs2ShowcaseEzSalesItem.h"
#include "Showcase/Model/Gs2ShowcaseConsumeAction.h"
#include "Showcase/Model/Gs2ShowcaseAcquireAction.h"
#include "Gs2ShowcaseSalesItem.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseSalesItem
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Name = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString Metadata = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ShowcaseConsumeAction> ConsumeActions = TArray<FGs2ShowcaseConsumeAction>();
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    TArray<FGs2ShowcaseAcquireAction> AcquireActions = TArray<FGs2ShowcaseAcquireAction>();
};

inline FGs2ShowcaseSalesItem EzSalesItemToFGs2ShowcaseSalesItem(
    const Gs2::UE5::Showcase::Model::FEzSalesItemPtr Model
)
{
    FGs2ShowcaseSalesItem Value;
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ConsumeActions = Model->GetConsumeActions() ? [&]
    {
        TArray<FGs2ShowcaseConsumeAction> r;
        for (auto v : *Model->GetConsumeActions())
        {r.Add(EzConsumeActionToFGs2ShowcaseConsumeAction(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseConsumeAction>();
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2ShowcaseAcquireAction> r;
        for (auto v : *Model->GetAcquireActions())
        {r.Add(EzAcquireActionToFGs2ShowcaseAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseAcquireAction>();
    return Value;
}

inline Gs2::UE5::Showcase::Model::FEzSalesItemPtr FGs2ShowcaseSalesItemToEzSalesItem(
    const FGs2ShowcaseSalesItem Model
)
{
    return MakeShared<Gs2::UE5::Showcase::Model::FEzSalesItem>()
        ->WithName(Model.Name)
        ->WithMetadata(Model.Metadata)
        ->WithConsumeActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzConsumeActionPtr>>();
            for (auto v : Model.ConsumeActions) {
                r->Add(FGs2ShowcaseConsumeActionToEzConsumeAction(v));
            }
            return r;
        }())
        ->WithAcquireActions([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Showcase::Model::FEzAcquireActionPtr>>();
            for (auto v : Model.AcquireActions) {
                r->Add(FGs2ShowcaseAcquireActionToEzAcquireAction(v));
            }
            return r;
        }());
}