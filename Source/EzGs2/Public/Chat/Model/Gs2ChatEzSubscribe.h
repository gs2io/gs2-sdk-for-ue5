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
#include "Chat/Model/Subscribe.h"
#include "Gs2ChatEzNotificationType.h"

namespace Gs2::UE5::Chat::Model
{
	class EZGS2_API FEzSubscribe final : public TSharedFromThis<FEzSubscribe>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> RoomNameValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypesValue;

	public:
        TSharedPtr<FEzSubscribe> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzSubscribe> WithRoomName(const TOptional<FString> RoomName);
        TSharedPtr<FEzSubscribe> WithNotificationTypes(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetRoomName() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> GetNotificationTypes() const;

        Gs2::Chat::Model::FSubscribePtr ToModel() const;
        static TSharedPtr<FEzSubscribe> FromModel(Gs2::Chat::Model::FSubscribePtr Model);
    };
    typedef TSharedPtr<FEzSubscribe> FEzSubscribePtr;
}