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
#include "Account/Model/Gs2AccountNamespace.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2AccountActionPreviewTakeOver.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountPreviewTakeOverSuccessDelegate, FGs2AccountAccount, Account, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2AccountPreviewTakeOverErrorDelegate, FGs2AccountAccount, Account, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2AccountPreviewTakeOverAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2AccountNamespace Namespace;
    int32 Type;
    FString UserIdentifier;
    FString Password;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountPreviewTakeOverSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2AccountPreviewTakeOverErrorDelegate OnError;

    UGs2AccountPreviewTakeOverAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Account::Account::Action::PreviewTakeOver", Category="Game Server Services|GS2-Account|Namespace|Account|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2AccountPreviewTakeOverAsyncFunction* PreviewTakeOver(
        UObject* WorldContextObject,
        FGs2AccountNamespace Namespace,
        int32 Type,
        FString UserIdentifier,
        FString Password
    );

    virtual void Activate() override;
};