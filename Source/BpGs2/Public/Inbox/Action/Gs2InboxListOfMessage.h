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
#include "Inbox/Model/Gs2InboxUser.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2InboxListOfMessage.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxListOfMessageSuccessDelegate, const TArray<FGs2InboxMessageValue>&, Values, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2InboxListOfMessageErrorDelegate, const TArray<FGs2InboxMessageValue>&, Values, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2InboxListOfMessageAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2InboxOwnUser User;

public:
    bool IsRead;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxListOfMessageSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2InboxListOfMessageErrorDelegate OnError;

    UGs2InboxListOfMessageAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Inbox::Fetch::ListOfMessage", Category="Game Server Services|GS2-Inbox|Namespace|User|Message|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2InboxListOfMessageAsyncFunction* ListOfMessage(
        UObject* WorldContextObject,
        FGs2InboxOwnUser User,
        bool IsRead
    );

    virtual void Activate() override;
};