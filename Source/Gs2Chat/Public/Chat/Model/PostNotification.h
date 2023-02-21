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

namespace Gs2::Chat::Model
{
	class GS2CHAT_API FPostNotification : public TSharedFromThis<FPostNotification>
	{
	public:
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> RoomNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int32> CategoryValue;
        TOptional<int64> CreatedAtValue;

        TSharedPtr<FPostNotification> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        TSharedPtr<FPostNotification> WithRoomName(
            const TOptional<FString> RoomName
        );
        TOptional<FString> GetRoomName() const;

        TSharedPtr<FPostNotification> WithUserId(
            const TOptional<FString> UserId
        );
        TOptional<FString> GetUserId() const;

        TSharedPtr<FPostNotification> WithCategory(
            const TOptional<int32> Category
        );
        TOptional<int32> GetCategory() const;

        TSharedPtr<FPostNotification> WithCreatedAt(
            const TOptional<int64> CreatedAt
        );
        TOptional<int64> GetCreatedAt() const;

        static TSharedPtr<FPostNotification> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FPostNotification> FPostNotificationPtr;
}
