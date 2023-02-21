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
#include "Chat/Domain/Model/Gs2ChatEzSubscribeGameSessionDomain.h"
#include "Chat/Model/Gs2ChatNotificationType.h"
#include "Gs2ChatSubscribe.generated.h"

USTRUCT(BlueprintType)
struct FGs2ChatOwnSubscribe
{
    GENERATED_BODY()

    Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomainPtr Value = nullptr;
};

USTRUCT(BlueprintType)
struct FGs2ChatSubscribeValue
{
    GENERATED_BODY()

    UPROPERTY(BlueprintReadOnly)
    FString UserId = "";
    UPROPERTY(BlueprintReadOnly)
    FString RoomName = "";
    UPROPERTY(BlueprintReadOnly)
    TArray<FGs2ChatNotificationType> NotificationTypes = TArray<FGs2ChatNotificationType>();
};

inline FGs2ChatSubscribeValue EzSubscribeToFGs2ChatSubscribeValue(
    const Gs2::UE5::Chat::Model::FEzSubscribePtr Model
)
{
    FGs2ChatSubscribeValue Value;
    Value.UserId = Model->GetUserId() ? *Model->GetUserId() : "";
    Value.RoomName = Model->GetRoomName() ? *Model->GetRoomName() : "";
    Value.NotificationTypes = Model->GetNotificationTypes() ? [&]
    {
        TArray<FGs2ChatNotificationType> r;
        for (auto v : *Model->GetNotificationTypes())
        {
            r.Add(EzNotificationTypeToFGs2ChatNotificationType(v));
        }
        return r;
    }() : TArray<FGs2ChatNotificationType>();
    return Value;
}

inline Gs2::UE5::Chat::Model::FEzSubscribePtr FGs2ChatSubscribeValueToEzSubscribe(
    const FGs2ChatSubscribeValue Model
)
{
    return MakeShared<Gs2::UE5::Chat::Model::FEzSubscribe>()
        ->WithUserId(Model.UserId)
        ->WithRoomName(Model.RoomName)
        ->WithNotificationTypes([&]{
            auto r = MakeShared<TArray<Gs2::UE5::Chat::Model::FEzNotificationTypePtr>>();
            for (auto v : Model.NotificationTypes) {
                r->Add(FGs2ChatNotificationTypeToEzNotificationType(v));
            }
            return r;
        }());
}

UCLASS()
class BPGS2_API UGs2ChatSubscribeFunctionLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()
};