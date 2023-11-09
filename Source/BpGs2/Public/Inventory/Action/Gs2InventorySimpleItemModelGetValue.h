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
#include "BpGs2/Public/Inventory/Model/Gs2InventorySimpleItemModel.h"
#include "BpGs2/Public/Inventory/Model/Gs2InventorySimpleItemModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventorySimpleItemModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventorySimpleItemModelGetValueSuccessDelegate, FGs2InventorySimpleItemModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventorySimpleItemModelGetValueErrorDelegate, FGs2InventorySimpleItemModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventorySimpleItemModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventorySimpleItemModel SimpleItemModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventorySimpleItemModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventorySimpleItemModelGetValueErrorDelegate OnError;

    UGs2InventorySimpleItemModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::GetValueOfSimpleItemModel", Category="Game Server Services|GS2-Inventory|Namespace|SimpleInventoryModel|SimpleItemModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventorySimpleItemModelGetValueAsyncFunction* SimpleItemModelGetValue(
        UObject* WorldContextObject,
        FGs2InventorySimpleItemModel SimpleItemModel
    );

    virtual void Activate() override;
};