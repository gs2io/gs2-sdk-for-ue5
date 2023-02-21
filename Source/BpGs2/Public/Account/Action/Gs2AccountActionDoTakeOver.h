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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "BpGs2/Public/Account/Model/Gs2AccountAccount.h"
#include "BpGs2/Public/Account/Model/Gs2AccountNamespace.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountActionDoTakeOver.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountDoTakeOverSuccessDelegate, FGs2AccountAccount, Account, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountDoTakeOverErrorDelegate, FGs2AccountAccount, Account, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountDoTakeOverAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountNamespace Namespace;

public:
    int32 Type;
    FString UserIdentifier;
    FString Password;

    UPROPERTY(BlueprintAssignable)
    FGs2AccountDoTakeOverSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2AccountDoTakeOverErrorDelegate OnError;

    UGs2AccountDoTakeOverAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::TakeOver::Action::DoTakeOver", Category="Game Server Services|GS2-Account|Namespace|Account|TakeOver|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountDoTakeOverAsyncFunction* DoTakeOver(
        UObject* WorldContextObject,
        FGs2AccountNamespace Namespace
    );

    virtual void Activate() override;
};