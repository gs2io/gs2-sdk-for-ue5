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
#include "Inventory/Model/Gs2InventoryBigItemModel.h"
#include "Inventory/Model/Gs2InventoryBigItemModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventoryBigItemModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryBigItemModelGetValueSuccessDelegate, FGs2InventoryBigItemModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventoryBigItemModelGetValueErrorDelegate, FGs2InventoryBigItemModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventoryBigItemModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventoryBigItemModel BigItemModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryBigItemModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventoryBigItemModelGetValueErrorDelegate OnError;

    UGs2InventoryBigItemModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::GetValueOfBigItemModel", Category="Game Server Services|GS2-Inventory|Namespace|BigInventoryModel|BigItemModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventoryBigItemModelGetValueAsyncFunction* BigItemModelGetValue(
        UObject* WorldContextObject,
        FGs2InventoryBigItemModel BigItemModel
    );

    virtual void Activate() override;
};