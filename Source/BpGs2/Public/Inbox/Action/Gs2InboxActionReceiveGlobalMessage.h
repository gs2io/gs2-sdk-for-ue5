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
#include "Gs2InboxActionReceiveGlobalMessage.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxReceiveGlobalMessageSuccessDelegate, const TArray<FGs2InboxOwnMessage>&, Messages, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxReceiveGlobalMessageErrorDelegate, const TArray<FGs2InboxOwnMessage>&, Messages, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InboxReceiveGlobalMessageAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InboxOwnUser User;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxReceiveGlobalMessageSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxReceiveGlobalMessageErrorDelegate OnError;

    UGs2InboxReceiveGlobalMessageAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::Message::Action::ReceiveGlobalMessage", Category="Game Server Services|GS2-Inbox|Namespace|User|Message|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InboxReceiveGlobalMessageAsyncFunction* ReceiveGlobalMessage(
        UObject* WorldContextObject,
        FGs2InboxOwnUser User
    );

    virtual void Activate() override;
};