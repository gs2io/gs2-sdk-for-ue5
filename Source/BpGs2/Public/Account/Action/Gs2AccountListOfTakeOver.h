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
#include "BpGs2/Public/Account/Model/Gs2AccountAccount.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountListOfTakeOver.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountListOfTakeOverSuccessDelegate, const TArray<FGs2AccountTakeOverValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountListOfTakeOverErrorDelegate, const TArray<FGs2AccountTakeOverValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountListOfTakeOverAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountOwnAccount Account;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2AccountListOfTakeOverSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2AccountListOfTakeOverErrorDelegate OnError;

    UGs2AccountListOfTakeOverAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::Fetch::ListOfTakeOver", Category="Game Server Services|GS2-Account|Namespace|Account|TakeOver|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountListOfTakeOverAsyncFunction* ListOfTakeOver(
        UObject* WorldContextObject,
        FGs2AccountOwnAccount Account
    );

    virtual void Activate() override;
};