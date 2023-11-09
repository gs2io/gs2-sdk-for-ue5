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
#include "BpGs2/Public/MegaField/Model/Gs2MegaFieldAreaModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MegaFieldListOfLayerModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MegaFieldListOfLayerModelSuccessDelegate, const TArray<FGs2MegaFieldLayerModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MegaFieldListOfLayerModelErrorDelegate, const TArray<FGs2MegaFieldLayerModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MegaFieldListOfLayerModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MegaFieldAreaModel AreaModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MegaFieldListOfLayerModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MegaFieldListOfLayerModelErrorDelegate OnError;

    UGs2MegaFieldListOfLayerModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::MegaField::Fetch::ListOfLayerModel", Category="Game Server Services|GS2-MegaField|Namespace|AreaModel|LayerModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MegaFieldListOfLayerModelAsyncFunction* ListOfLayerModel(
        UObject* WorldContextObject,
        FGs2MegaFieldAreaModel AreaModel
    );

    virtual void Activate() override;
};