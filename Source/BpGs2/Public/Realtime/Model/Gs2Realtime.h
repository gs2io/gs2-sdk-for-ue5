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

#include "Core/Model/Gs2Client.h"
#include "Gs2Realtime.generated.h"

USTRUCT(BlueprintType)
struct FGs2Realtime
{
    GENERATED_BODY()

    Gs2::UE5::Realtime::Domain::FEzGs2RealtimePtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2RealtimeCreateNotification
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString NamespaceName = "";
    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FString RoomName = "";
};

inline FGs2RealtimeCreateNotification EzCreateNotificationToFGs2RealtimeCreateNotification(
    const Gs2::Realtime::Model::FCreateNotificationPtr Model
)
{
    FGs2RealtimeCreateNotification Value;
    Value.NamespaceName = Model->GetNamespaceName() ? *Model->GetNamespaceName() : "";
    Value.RoomName = Model->GetRoomName() ? *Model->GetRoomName() : "";
    return Value;
}

UDELEGATE(BlueprintAuthorityOnly)
DECLARE_DYNAMIC_DELEGATE_OneParam(FEzRealtimeCreateNotificationEvent, FGs2RealtimeCreateNotification, Notification);

USTRUCT(BlueprintType)
struct FBpRealtimeCreateNotificationEvent
{
    GENERATED_BODY()

    UPROPERTY(Category = Gs2, BlueprintReadWrite)
    FEzRealtimeCreateNotificationEvent Value;
};

UCLASS()
class BPGS2_API UGs2RealtimeFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Realtime::Service", Category="Game Server Services|GS2-Realtime", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Service") FGs2Realtime Service(
        FGs2Client Client,
        FBpRealtimeCreateNotificationEvent CreateNotification
    );

    UFUNCTION(BlueprintCallable, DisplayName="Gs2::Realtime::Namespace", Category="Game Server Services|GS2-Realtime|Namespace", meta=(WorldContext="WorldContextObject"))
    static UPARAM(DisplayName="Namespace") FGs2RealtimeNamespace Namespace(
        FGs2Realtime Service,
        FString NamespaceName
    );

};