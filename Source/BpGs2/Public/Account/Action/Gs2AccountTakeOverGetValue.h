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
#include "Account/Model/Gs2AccountTakeOver.h"
#include "Account/Model/Gs2AccountTakeOver.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountTakeOverGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountTakeOverGetValueSuccessDelegate, FGs2AccountTakeOverValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountTakeOverGetValueErrorDelegate, FGs2AccountTakeOverValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountTakeOverGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountOwnTakeOver TakeOver;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountTakeOverGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountTakeOverGetValueErrorDelegate OnError;

    UGs2AccountTakeOverGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::Fetch::GetValueOfTakeOver", Category="Game Server Services|GS2-Account|Namespace|Account|TakeOver|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountTakeOverGetValueAsyncFunction* TakeOverGetValue(
        UObject* WorldContextObject,
        FGs2AccountOwnTakeOver TakeOver
    );

    virtual void Activate() override;
};