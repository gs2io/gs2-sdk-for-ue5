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
#include "Showcase/Domain/Model/Gs2ShowcaseEzDisplayItemGameSessionDomain.h"
#include "Showcase/Model/Gs2ShowcaseSalesItem.h"
#include "Showcase/Model/Gs2ShowcaseSalesItemGroup.h"
#include "Core/BpGs2Constant.h"
#include "Gs2ShowcaseDisplayItem.generated.h"

USTRUCT(BlueprintType)
struct FGs2ShowcaseOwnDisplayItem
{
    GENERATED_BODY()

    Gs2::UE5::Showcase::Domain::Model::FEzDisplayItemGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ShowcaseDisplayItemValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString DisplayItemId = "";
    UPROPERTY(BlueprintReadOnly)
    FString Type = "";
    UPROPERTY(BlueprintReadOnly)
    FGs2ShowcaseSalesItem SalesItem = FGs2ShowcaseSalesItem();
    UPROPERTY(BlueprintReadOnly)
    FGs2ShowcaseSalesItemGroup SalesItemGroup = FGs2ShowcaseSalesItemGroup();
};

inline FGs2ShowcaseDisplayItemValue EzDisplayItemToFGs2ShowcaseDisplayItemValue(
    const Gs2::UE5::Showcase::Model::FEzDisplayItemPtr Model
)
{
    FGs2ShowcaseDisplayItemValue Value;
    if (Model == nullptr) {
        UE_LOG(BpGs2Log, Error, TEXT("[UGs2ShowcaseDisplayItemFunctionLibrary::EzDisplayItemToFGs2ShowcaseDisplayItemValue] Model parameter specification is missing."))
        return Value;
    }
    Value.DisplayItemId = Model->GetDisplayItemId() ? *Model->GetDisplayItemId() : "";
    Value.Type = Model->GetType() ? *Model->GetType() : "";
    Value.SalesItem = Model->GetSalesItem() ? EzSalesItemToFGs2ShowcaseSalesItem(Model->GetSalesItem()) : FGs2ShowcaseSalesItem();
    Value.SalesItemGroup = Model->GetSalesItemGroup() ? EzSalesItemGroupToFGs2ShowcaseSalesItemGroup(Model->GetSalesItemGroup()) : FGs2ShowcaseSalesItemGroup();
    return Value;
}

inline Gs2::UE5::Showcase::Model::FEzDisplayItemPtr FGs2ShowcaseDisplayItemValueToEzDisplayItem(
    const FGs2ShowcaseDisplayItemValue Model
)
{
    return MakeShared<Gs2::UE5::Showcase::Model::FEzDisplayItem>()
        ->WithDisplayItemId(Model.DisplayItemId)
        ->WithType(Model.Type)
        ->WithSalesItem(FGs2ShowcaseSalesItemToEzSalesItem(Model.SalesItem))
        ->WithSalesItemGroup(FGs2ShowcaseSalesItemGroupToEzSalesItemGroup(Model.SalesItemGroup));
}

UCLASS()
class BPGS2_API UGs2ShowcaseDisplayItemFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};