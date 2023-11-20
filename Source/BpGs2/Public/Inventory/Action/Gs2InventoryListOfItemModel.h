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
#include "Inventory/Model/Gs2InventoryInventoryModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventoryListOfItemModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryListOfItemModelSuccessDelegate, const TArray<FGs2InventoryItemModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryListOfItemModelErrorDelegate, const TArray<FGs2InventoryItemModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventoryListOfItemModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventoryInventoryModel InventoryModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryListOfItemModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryListOfItemModelErrorDelegate OnError;

    UGs2InventoryListOfItemModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::ListOfItemModel", Category="Game Server Services|GS2-Inventory|Namespace|InventoryModel|ItemModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventoryListOfItemModelAsyncFunction* ListOfItemModel(
        UObject* WorldContextObject,
        FGs2InventoryInventoryModel InventoryModel
    );

    virtual void Activate() override;
};