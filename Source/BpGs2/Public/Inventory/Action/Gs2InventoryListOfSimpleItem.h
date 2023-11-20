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
#include "Inventory/Model/Gs2InventorySimpleInventory.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventoryListOfSimpleItem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryListOfSimpleItemSuccessDelegate, const TArray<FGs2InventorySimpleItemValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryListOfSimpleItemErrorDelegate, const TArray<FGs2InventorySimpleItemValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventoryListOfSimpleItemAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventoryOwnSimpleInventory SimpleInventory;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryListOfSimpleItemSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryListOfSimpleItemErrorDelegate OnError;

    UGs2InventoryListOfSimpleItemAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::ListOfSimpleItem", Category="Game Server Services|GS2-Inventory|Namespace|User|SimpleInventory|SimpleItem|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventoryListOfSimpleItemAsyncFunction* ListOfSimpleItem(
        UObject* WorldContextObject,
        FGs2InventoryOwnSimpleInventory SimpleInventory
    );

    virtual void Activate() override;
};