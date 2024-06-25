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
#include "Money2/Model/Gs2Money2Wallet.h"
#include "Money2/Model/Gs2Money2Wallet.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2Money2WalletGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2Money2WalletGetValueSuccessDelegate, FGs2Money2WalletValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2Money2WalletGetValueErrorDelegate, FGs2Money2WalletValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2Money2WalletGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2Money2OwnWallet Wallet;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2Money2WalletGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2Money2WalletGetValueErrorDelegate OnError;

    UGs2Money2WalletGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Money2::Fetch::GetValueOfWallet", Category="Game Server Services|GS2-Money2|Namespace|User|Wallet|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2Money2WalletGetValueAsyncFunction* WalletGetValue(
        UObject* WorldContextObject,
        FGs2Money2OwnWallet Wallet
    );

    virtual void Activate() override;
};