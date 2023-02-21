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
#include "BpGs2/Public/Chat/Model/Gs2ChatRoom.h"
#include "BpGs2/Public/Chat/Model/Gs2ChatRoom.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ChatRoomGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatRoomGetValueSuccessDelegate, FGs2ChatRoomValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatRoomGetValueErrorDelegate, FGs2ChatRoomValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ChatRoomGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ChatRoom Room;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2ChatRoomGetValueSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ChatRoomGetValueErrorDelegate OnError;

    UGs2ChatRoomGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Fetch::GetValueOfRoom", Category="Game Server Services|GS2-Chat|Namespace|User|Room|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ChatRoomGetValueAsyncFunction* RoomGetValue(
        UObject* WorldContextObject,
        FGs2ChatRoom Room
    );

    virtual void Activate() override;
};