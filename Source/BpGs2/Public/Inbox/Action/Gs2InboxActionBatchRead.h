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
#include "Inbox/Model/Gs2InboxMessage.h"
#include "Inbox/Model/Gs2InboxUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InboxActionBatchRead.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxBatchReadSuccessDelegate, FGs2CoreOwnTransaction, Transaction, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxBatchReadErrorDelegate, FGs2CoreOwnTransaction, Transaction, const FGs2Error, Error);


UCLASS()
class BPGS2_API UGs2InboxBatchReadAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InboxOwnUser User;
    TArray<FString> MessageNames;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxBatchReadSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxBatchReadErrorDelegate OnError;

    UGs2InboxBatchReadAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::Message::Action::BatchRead", Category="Game Server Services|GS2-Inbox|Namespace|User|Message|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InboxBatchReadAsyncFunction* BatchRead(
        UObject* WorldContextObject,
        FGs2InboxOwnUser User,
        TArray<FString> MessageNames
    );

    virtual void Activate() override;
};