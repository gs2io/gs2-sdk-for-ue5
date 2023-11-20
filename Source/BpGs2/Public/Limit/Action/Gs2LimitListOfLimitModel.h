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
#include "Limit/Model/Gs2LimitNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2LimitListOfLimitModel.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitListOfLimitModelSuccessDelegate, const TArray<FGs2LimitLimitModelValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2LimitListOfLimitModelErrorDelegate, const TArray<FGs2LimitLimitModelValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2LimitListOfLimitModelAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2LimitNamespace Namespace;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LimitListOfLimitModelSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2LimitListOfLimitModelErrorDelegate OnError;

    UGs2LimitListOfLimitModelAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Limit::Fetch::ListOfLimitModel", Category="Game Server Services|GS2-Limit|Namespace|LimitModel|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2LimitListOfLimitModelAsyncFunction* ListOfLimitModel(
        UObject* WorldContextObject,
        FGs2LimitNamespace Namespace
    );

    virtual void Activate() override;
};