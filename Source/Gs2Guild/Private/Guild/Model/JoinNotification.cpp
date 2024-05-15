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

#include "Guild/Model/JoinNotification.h"

namespace Gs2::Guild::Model
{

    TSharedPtr<FJoinNotification> FJoinNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FJoinNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FJoinNotification> FJoinNotification::WithGuildModelName(
        const TOptional<FString> GuildModelName
    ) {
        GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }
    TOptional<FString> FJoinNotification::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TSharedPtr<FJoinNotification> FJoinNotification::WithGuildName(
        const TOptional<FString> GuildName
    ) {
        GuildNameValue = GuildName;
        return SharedThis(this);
    }
    TOptional<FString> FJoinNotification::GetGuildName() const
    {
        return GuildNameValue;
    }

    TSharedPtr<FJoinNotification> FJoinNotification::WithJoinedUserId(
        const TOptional<FString> JoinedUserId
    ) {
        JoinedUserIdValue = JoinedUserId;
        return SharedThis(this);
    }
    TOptional<FString> FJoinNotification::GetJoinedUserId() const
    {
        return JoinedUserIdValue;
    }

    TSharedPtr<FJoinNotification> FJoinNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJoinNotification>()
            ->WithNamespaceName(Data->HasField("namespaceName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("namespaceName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildModelName(Data->HasField("guildModelName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("guildModelName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildName(Data->HasField("guildName") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("guildName", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithJoinedUserId(Data->HasField("joinedUserId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("joinedUserId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
