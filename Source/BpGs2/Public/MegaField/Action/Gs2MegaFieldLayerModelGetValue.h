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
#include "MegaField/Model/Gs2MegaFieldLayerModel.h"
#include "MegaField/Model/Gs2MegaFieldLayerModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MegaFieldLayerModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MegaFieldLayerModelGetValueSuccessDelegate, FGs2MegaFieldLayerModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MegaFieldLayerModelGetValueErrorDelegate, FGs2MegaFieldLayerModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MegaFieldLayerModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MegaFieldLayerModel LayerModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MegaFieldLayerModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MegaFieldLayerModelGetValueErrorDelegate OnError;

    UGs2MegaFieldLayerModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::MegaField::Fetch::GetValueOfLayerModel", Category="Game Server Services|GS2-MegaField|Namespace|AreaModel|LayerModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MegaFieldLayerModelGetValueAsyncFunction* LayerModelGetValue(
        UObject* WorldContextObject,
        FGs2MegaFieldLayerModel LayerModel
    );

    virtual void Activate() override;
};