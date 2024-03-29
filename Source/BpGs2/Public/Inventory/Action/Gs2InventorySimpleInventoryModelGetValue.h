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
#include "Inventory/Model/Gs2InventorySimpleInventoryModel.h"
#include "Inventory/Model/Gs2InventorySimpleInventoryModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InventorySimpleInventoryModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventorySimpleInventoryModelGetValueSuccessDelegate, FGs2InventorySimpleInventoryModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InventorySimpleInventoryModelGetValueErrorDelegate, FGs2InventorySimpleInventoryModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InventorySimpleInventoryModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InventorySimpleInventoryModel SimpleInventoryModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventorySimpleInventoryModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InventorySimpleInventoryModelGetValueErrorDelegate OnError;

    UGs2InventorySimpleInventoryModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inventory::Fetch::GetValueOfSimpleInventoryModel", Category="Game Server Services|GS2-Inventory|Namespace|SimpleInventoryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InventorySimpleInventoryModelGetValueAsyncFunction* SimpleInventoryModelGetValue(
        UObject* WorldContextObject,
        FGs2InventorySimpleInventoryModel SimpleInventoryModel
    );

    virtual void Activate() override;
};