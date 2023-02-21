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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "BpGs2/Public/Chat/Model/Gs2ChatSubscribe.h"
#include "BpGs2/Public/Chat/Model/Gs2ChatSubscribe.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ChatActionSubscribe.generated.h"
  
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatSubscribeSuccessDelegate, FGs2ChatOwnSubscribe, Subscribe, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatSubscribeErrorDelegate, FGs2ChatOwnSubscribe, Subscribe, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ChatSubscribeAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    UPARAM(DisplayName="Subscribe") FGs2ChatOwnSubscribe SubscribeValue;

public:
    TArray<FGs2ChatNotificationType> NotificationTypes;

    UPROPERTY(BlueprintAssignable)
    FGs2ChatSubscribeSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ChatSubscribeErrorDelegate OnError;

    UGs2ChatSubscribeAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Subscribe::Action::Subscribe", Category="Game Server Services|GS2-Chat|Namespace|User|Subscribe|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ChatSubscribeAsyncFunction* Subscribe(
        UObject* WorldContextObject,
        FGs2ChatOwnSubscribe Subscribe
    );

    virtual void Activate() override;
};