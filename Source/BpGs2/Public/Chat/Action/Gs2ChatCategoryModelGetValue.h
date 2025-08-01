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
#include "Chat/Model/Gs2ChatCategoryModel.h"
#include "Chat/Model/Gs2ChatCategoryModel.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ChatCategoryModelGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatCategoryModelGetValueSuccessDelegate, FGs2ChatCategoryModelValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatCategoryModelGetValueErrorDelegate, FGs2ChatCategoryModelValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ChatCategoryModelGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ChatCategoryModel CategoryModel;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ChatCategoryModelGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ChatCategoryModelGetValueErrorDelegate OnError;

    UGs2ChatCategoryModelGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Fetch::GetValueOfCategoryModel", Category="Game Server Services|GS2-Chat|Namespace|CategoryModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ChatCategoryModelGetValueAsyncFunction* CategoryModelGetValue(
        UObject* WorldContextObject,
        FGs2ChatCategoryModel CategoryModel
    );

    virtual void Activate() override;
};