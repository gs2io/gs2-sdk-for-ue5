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
#include "Inventory/Model/Gs2InventoryItemSet.h"
#include "Inventory/Model/Gs2InventoryItemSet.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventoryItemSetGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryItemSetGetValueSuccessDelegate, const TArray<FGs2InventoryItemSetValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryItemSetGetValueErrorDelegate, const TArray<FGs2InventoryItemSetValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventoryItemSetGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventoryOwnItemSet ItemSet;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryItemSetGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryItemSetGetValueErrorDelegate OnError;

    UGs2InventoryItemSetGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::GetValueOfItemSet", Category="Game Server Services|GS2-Inventory|Namespace|User|Inventory|ItemSet|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventoryItemSetGetValueAsyncFunction* ItemSetGetValue(
        UObject* WorldContextObject,
        FGs2InventoryOwnItemSet ItemSet
    );

    virtual void Activate() override;
};