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
#include "Chat/Model/Gs2ChatMessage.h"
#include "Chat/Model/Gs2ChatRoom.h"
#include "../../Core/Model/Gs2Error.h"
#include "Core/Model/Gs2CoreTransaction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ChatActionPost.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatPostSuccessDelegate, FGs2ChatOwnMessage, Message, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatPostErrorDelegate, FGs2ChatOwnMessage, Message, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ChatPostAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ChatOwnRoom Room;
    FString Metadata;
    int32 Category;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ChatPostSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ChatPostErrorDelegate OnError;

    UGs2ChatPostAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Message::Action::Post", Category="Game Server Services|GS2-Chat|Namespace|User|Room|Message|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ChatPostAsyncFunction* Post(
        UObject* WorldContextObject,
        FGs2ChatOwnRoom Room,
        FString Metadata,
        int32 Category
    );

    virtual void Activate() override;
};