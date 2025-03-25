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
#include "Chat/Model/Gs2ChatMessage.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ChatMessageGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatMessageGetValueSuccessDelegate, FGs2ChatMessageValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatMessageGetValueErrorDelegate, FGs2ChatMessageValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ChatMessageGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ChatOwnMessage Message;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ChatMessageGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2ChatMessageGetValueErrorDelegate OnError;

    UGs2ChatMessageGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Fetch::GetValueOfMessage", Category="Game Server Services|GS2-Chat|Namespace|User|Room|Message|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ChatMessageGetValueAsyncFunction* MessageGetValue(
        UObject* WorldContextObject,
        FGs2ChatOwnMessage Message
    );

    virtual void Activate() override;
};