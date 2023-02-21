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
#include "BpGs2/Public/Inventory/Model/Gs2InventoryInventory.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventoryListOfItemSet.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryListOfItemSetSuccessDelegate, const TArray<FGs2InventoryItemSetValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryListOfItemSetErrorDelegate, const TArray<FGs2InventoryItemSetValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventoryListOfItemSetAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventoryOwnInventory Inventory;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2InventoryListOfItemSetSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2InventoryListOfItemSetErrorDelegate OnError;

    UGs2InventoryListOfItemSetAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::ListOfItemSet", Category="Game Server Services|GS2-Inventory|Namespace|User|Inventory|ItemSet|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventoryListOfItemSetAsyncFunction* ListOfItemSet(
        UObject* WorldContextObject,
        FGs2InventoryOwnInventory Inventory
    );

    virtual void Activate() override;
};