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
#include "BpGs2/Public/Chat/Model/Gs2ChatUser.h"
#include "BpGs2/Public/Core/Model/Gs2Error.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Gs2ChatActionCreateRoom.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatCreateRoomSuccessDelegate, FGs2ChatOwnRoom, Room, const FGs2Error, Error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGs2ChatCreateRoomErrorDelegate, FGs2ChatOwnRoom, Room, const FGs2Error, Error);

UCLASS()
class BPGS2_API UGs2ChatCreateRoomAsyncFunction : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

    FGs2ChatOwnUser User;
    FString Name;
    FString Metadata;
    FString Password;
    TArray<FString> WhiteListUserIds;

public:

    UPROPERTY(BlueprintAssignable)
    FGs2ChatCreateRoomSuccessDelegate OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FGs2ChatCreateRoomErrorDelegate OnError;

    UGs2ChatCreateRoomAsyncFunction(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(BlueprintCallable, DisplayName="Gs2::Chat::Room::Action::CreateRoom", Category="Game Server Services|GS2-Chat|Namespace|User|Room|Action", meta=(WorldContext="WorldContextObject", BlueprintInternalUseOnly="true"))
    static UGs2ChatCreateRoomAsyncFunction* CreateRoom(
        UObject* WorldContextObject,
        FGs2ChatOwnUser User,
        FString Name,
        FString Metadata,
        FString Password,
        TArray<FString> WhiteListUserIds
    );

    virtual void Activate() override;
};