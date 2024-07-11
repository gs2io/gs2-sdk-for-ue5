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
#include "Account/Model/Gs2AccountAccount.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountListOfPlatformId.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountListOfPlatformIdSuccessDelegate, const TArray<FGs2AccountPlatformIdValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountListOfPlatformIdErrorDelegate, const TArray<FGs2AccountPlatformIdValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountListOfPlatformIdAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountOwnAccount Account;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountListOfPlatformIdSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountListOfPlatformIdErrorDelegate OnError;

    UGs2AccountListOfPlatformIdAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::Fetch::ListOfPlatformId", Category="Game Server Services|GS2-Account|Namespace|Account|PlatformId|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountListOfPlatformIdAsyncFunction* ListOfPlatformId(
        UObject* WorldContextObject,
        FGs2AccountOwnAccount Account
    );

    virtual void Activate() override;
};