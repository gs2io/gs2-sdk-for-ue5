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
#include "BpGs2/Public/Money/Model/Gs2MoneyWallet.h"
#include "BpGs2/Public/Money/Model/Gs2MoneyWallet.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MoneyActionWithdraw.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MoneyWithdrawSuccessDelegate, FGs2MoneyOwnWallet, Wallet, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MoneyWithdrawErrorDelegate, FGs2MoneyOwnWallet, Wallet, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MoneyWithdrawAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MoneyOwnWallet Wallet;
    int32 Count;
    bool PaidOnly;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2MoneyWithdrawSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2MoneyWithdrawErrorDelegate OnError;

    UGs2MoneyWithdrawAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money::Wallet::Action::Withdraw", Category="Game Server Services|GS2-Money|Namespace|User|Wallet|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MoneyWithdrawAsyncFunction* Withdraw(
        UObject* WorldContextObject,
        FGs2MoneyOwnWallet Wallet,
        int32 Count,
        bool PaidOnly
    );

    virtual void Activate() override;
};