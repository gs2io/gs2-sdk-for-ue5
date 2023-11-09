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
#include "BpGs2/Public/Inbox/Model/Gs2InboxMessage.h"
#include "BpGs2/Public/Inbox/Model/Gs2InboxMessage.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InboxActionDelete.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxDeleteSuccessDelegate, FGs2InboxOwnMessage, Message, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxDeleteErrorDelegate, FGs2InboxOwnMessage, Message, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InboxDeleteAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InboxOwnMessage Message;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxDeleteSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxDeleteErrorDelegate OnError;

    UGs2InboxDeleteAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::Message::Action::Delete", Category="Game Server Services|GS2-Inbox|Namespace|User|Message|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InboxDeleteAsyncFunction* Delete(
        UObject* WorldContextObject,
        FGs2InboxOwnMessage Message
    );

    virtual void Activate() override;
};