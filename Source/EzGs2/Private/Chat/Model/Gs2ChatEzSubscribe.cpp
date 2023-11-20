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

#include "Chat/Model/Gs2ChatEzSubscribe.h"

namespace Gs2::UE5::Chat::Model
{

    TSharedPtr<FEzSubscribe> FEzSubscribe::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribe> FEzSubscribe::WithRoomName(
        const TOptional<FString> RoomName
    )
    {
        this->RoomNameValue = RoomName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSubscribe> FEzSubscribe::WithNotificationTypes(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes
    )
    {
        this->NotificationTypesValue = NotificationTypes;
        return SharedThis(this);
    }
    TOptional<FString> FEzSubscribe::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzSubscribe::GetRoomName() const
    {
        return RoomNameValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> FEzSubscribe::GetNotificationTypes() const
    {
        return NotificationTypesValue;
    }

    Gs2::Chat::Model::FSubscribePtr FEzSubscribe::ToModel() const
    {
        return MakeShared<Gs2::Chat::Model::FSubscribe>()
            ->WithUserId(UserIdValue)
            ->WithRoomName(RoomNameValue)
            ->WithNotificationTypes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Chat::Model::FNotificationType>>>();
                    if (NotificationTypesValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *NotificationTypesValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            );
    }

    TSharedPtr<FEzSubscribe> FEzSubscribe::FromModel(const Gs2::Chat::Model::FSubscribePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSubscribe>()
            ->WithUserId(Model->GetUserId())
            ->WithRoomName(Model->GetRoomName())
            ->WithNotificationTypes([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzNotificationType>>>();
                    if (Model->GetNotificationTypes() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetNotificationTypes())
                    {
                        v->Add(FEzNotificationType::FromModel(v2));
                    }
                    return v;
                }()
            );
    }
}