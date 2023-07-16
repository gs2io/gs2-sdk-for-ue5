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
#include "Showcase/Domain/Model/Gs2ShowcaseEzRandomDisplayItemGameSessionDomain.h"
#include "Showcase/Model/Gs2ShowcaseConsumeAction.h"
#include "Showcase/Model/Gs2ShowcaseAcquireAction.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ShowcaseRandomDisplayItem.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseOwnRandomDisplayItem
{
    GENERATED_BODY()

    Gs2::UE5::Showcase::Domain::Model::FEzRandomDisplayItemGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ShowcaseRandomDisplayItemValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString Name = "";
    UPROPERTY(BlueprintReadOnly)
    FString Metadata = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2ShowcaseConsumeAction> ConsumeActions = TArray<FGs2ShowcaseConsumeAction>();
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2ShowcaseAcquireAction> AcquireActions = TArray<FGs2ShowcaseAcquireAction>();
    UPROPERTY(BlueprintReadOnly)
    int32 CurrentPurchaseCount = 0;
    UPROPERTY(BlueprintReadOnly)
    int32 MaximumPurchaseCount = 0;
};

inline FGs2ShowcaseRandomDisplayItemValue EzRandomDisplayItemToFGs2ShowcaseRandomDisplayItemValue(
    const Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr Model
)
{
    FGs2ShowcaseRandomDisplayItemValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseRandomDisplayItemFunctionLibrary::EzRandomDisplayItemToFGs2ShowcaseRandomDisplayItemValue] Model parameter specification is missing."))
        return Value;
    }
    Value.Name = Model->GetName() ? *Model->GetName() : "";
    Value.Metadata = Model->GetMetadata() ? *Model->GetMetadata() : "";
    Value.ConsumeActions = Model->GetConsumeActions() ? [&]
    {
        TArray<FGs2ShowcaseConsumeAction> r;
        for (auto v : *Model->GetConsumeActions())
        {
            r.Add(EzConsumeActionToFGs2ShowcaseConsumeAction(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseConsumeAction>();
    Value.AcquireActions = Model->GetAcquireActions() ? [&]
    {
        TArray<FGs2ShowcaseAcquireAction> r;
        for (auto v : *Model->GetAcquireActions())
        {
            r.Add(EzAcquireActionToFGs2ShowcaseAcquireAction(v));
        }
        return r;
    }() : TArray<FGs2ShowcaseAcquireAction>();
    Value.CurrentPurchaseCount = Model->GetCurrentPurchaseCount() ? *Model->GetCurrentPurchaseCount() : 0;
    Value.MaximumPurchaseCount = Model->GetMaximumPurchaseCount() ? *Model->GetMaximumPurchaseCount() : 0;
    return Value;
}

inline Gs2::UE5::Showcase::Model::FEzRandomDisplayItemPtr FGs2ShowcaseRandomDisplayItemValueToEzRandomDisplayItem(
    const FGs2ShowcaseRandomDisplayItemValue Model
)
{
    return MakeShared<Gs2::UE5::Showcase::Model::FEzRandomDisplayItem>()
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
        }())
        ->WithCurrentPurchaseCount(Model.CurrentPurchaseCount)
        ->WithMaximumPurchaseCount(Model.MaximumPurchaseCount);
}

UCLASS()
class BPGS2_API UGs2ShowcaseRandomDisplayItemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};