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
#include "Realtime/Model/Gs2RealtimeRoom.h"
#include "Realtime/Model/Gs2RealtimeRoom.h"
#include "../../Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2RealtimeRoomGetValue.generated.h"
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RealtimeRoomGetValueSuccessDelegate, FGs2RealtimeRoomValue, Value, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2RealtimeRoomGetValueErrorDelegate, FGs2RealtimeRoomValue, Value, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2RealtimeRoomGetValueAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2RealtimeRoom Room;

public:

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RealtimeRoomGetValueSuccessDelegate OnSuccess;

    UPROPERTY(Category = Gs2, BlueprintAssignable)
    FGs2RealtimeRoomGetValueErrorDelegate OnError;

    UGs2RealtimeRoomGetValueAsyncFunction(const FObjectInitializer& ObjectInitializer);

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Realtime::Fetch::GetValueOfRoom", Category="Game Server Services|GS2-Realtime|Namespace|Room|Fetch", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2RealtimeRoomGetValueAsyncFunction* RoomGetValue(
        UObject* WorldContextObject,
        FGs2RealtimeRoom Room
    );

    virtual void Activate() override;
};