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

namespace Gs2::Guild::Model
{
	class GS2GUILD_API FLeaveNotification : public TSharedFromThis<FLeaveNotification>
	{
	public:
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> LeavedUserIdValue;

        TSharedPtr<FLeaveNotification> WithNamespaceName(
            const TOptional<FString> NamespaceName
        );
        TOptional<FString> GetNamespaceName() const;

        TSharedPtr<FLeaveNotification> WithGuildModelName(
            const TOptional<FString> GuildModelName
        );
        TOptional<FString> GetGuildModelName() const;

        TSharedPtr<FLeaveNotification> WithGuildName(
            const TOptional<FString> GuildName
        );
        TOptional<FString> GetGuildName() const;

        TSharedPtr<FLeaveNotification> WithLeavedUserId(
            const TOptional<FString> LeavedUserId
        );
        TOptional<FString> GetLeavedUserId() const;

        static TSharedPtr<FLeaveNotification> FromJson(const TSharedPtr<FJsonObject> Data);
    };

    typedef TSharedPtr<FLeaveNotification> FLeaveNotificationPtr;
}
