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
#include "Money/Model/Gs2MoneyWallet.h"
#include "Money/Model/Gs2MoneyWallet.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2MoneyWalletGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MoneyWalletGetValueSuccessDelegate, FGs2MoneyWalletValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2MoneyWalletGetValueErrorDelegate, FGs2MoneyWalletValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2MoneyWalletGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2MoneyOwnWallet Wallet;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MoneyWalletGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2MoneyWalletGetValueErrorDelegate OnError;

    UGs2MoneyWalletGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money::Fetch::GetValueOfWallet", Category="Game Server Services|GS2-Money|Namespace|User|Wallet|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2MoneyWalletGetValueAsyncFunction* WalletGetValue(
        UObject* WorldContextObject,
        FGs2MoneyOwnWallet Wallet
    );

    virtual void Activate() override;
};