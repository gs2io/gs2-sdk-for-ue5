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
#include "BpGs2/Public/Idle/Model/Gs2IdleCategoryModel.h"
#include "BpGs2/Public/Idle/Model/Gs2IdleCategoryModel.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2IdleCategoryModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2IdleCategoryModelGetValueSuccessDelegate, FGs2IdleCategoryModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2IdleCategoryModelGetValueErrorDelegate, FGs2IdleCategoryModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2IdleCategoryModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2IdleCategoryModel CategoryModel;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2IdleCategoryModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2IdleCategoryModelGetValueErrorDelegate OnError;

    UGs2IdleCategoryModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Idle::Fetch::GetValueOfCategoryModel", Category="Game Server Services|GS2-Idle|Namespace|CategoryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2IdleCategoryModelGetValueAsyncFunction* CategoryModelGetValue(
        UObject* WorldContextObject,
        FGs2IdleCategoryModel CategoryModel
    );

    virtual void Activate() override;
};