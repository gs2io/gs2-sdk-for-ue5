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
#include "Inventory/Model/Gs2InventorySimpleItem.h"
#include "Inventory/Model/Gs2InventoryConsumeCount.h"
#include "Inventory/Model/Gs2InventorySimpleInventory.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventoryActionConsumeSimpleItems.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryConsumeSimpleItemsSuccessDelegate, const TArray<FGs2InventoryOwnSimpleItem>&, SimpleItems, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryConsumeSimpleItemsErrorDelegate, const TArray<FGs2InventoryOwnSimpleItem>&, SimpleItems, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventoryConsumeSimpleItemsAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventoryOwnSimpleInventory SimpleInventory;
    TArray<FGs2InventoryConsumeCount> ConsumeCounts;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryConsumeSimpleItemsSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryConsumeSimpleItemsErrorDelegate OnError;

    UGs2InventoryConsumeSimpleItemsAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::SimpleItem::Action::ConsumeSimpleItems", Category="Game Server Services|GS2-Inventory|Namespace|User|SimpleInventory|SimpleItem|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventoryConsumeSimpleItemsAsyncFunction* ConsumeSimpleItems(
        UObject* WorldContextObject,
        FGs2InventoryOwnSimpleInventory SimpleInventory,
        TArray<FGs2InventoryConsumeCount> ConsumeCounts
    );

    virtual void Activate() override;
};