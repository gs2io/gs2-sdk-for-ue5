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

namespace Gs2::Friend::Model
{
	class GS2FRIEND_API FFollowNotification : public TSharedFromThis<FFollowNotification>
	{
	public:
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> UserIdValue;
        TOptional<FString> FromUserIdValue;

        TSharedPtr<FFollowNotification> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        TSharedPtr<FFollowNotification> WithUserId(
            const TOptional<FString> UserId
        );
        TOptional<FString> GetUserId() const;

        TSharedPtr<FFollowNotification> WithFromUserId(
            const TOptional<FString> FromUserId
        );
        TOptional<FString> GetFromUserId() const;

        static TSharedPtr<FFollowNotification> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FFollowNotification> FFollowNotificationPtr;
}
