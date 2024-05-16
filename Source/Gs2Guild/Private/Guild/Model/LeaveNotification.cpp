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

#include "Guild/Model/LeaveNotification.h"

namespace Gs2::Guild::Model
{

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithGuildModelName(
        const TOptional<FString> GuildModelName
    ) {
        GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithGuildName(
        const TOptional<FString> GuildName
    ) {
        GuildNameValue = GuildName;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetGuildName() const
    {
        return GuildNameValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::WithLeavedUserId(
        const TOptional<FString> LeavedUserId
    ) {
        LeavedUserIdValue = LeavedUserId;
        return SharedThis(this);
    }
    TOptional<FString> FLeaveNotification::GetLeavedUserId() const
    {
        return LeavedUserIdValue;
    }

    TSharedPtr<FLeaveNotification> FLeaveNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FLeaveNotification>()
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildModelName(Data->HasField(ANSI_TO_TCHAR("guildModelName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildModelName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildName(Data->HasField(ANSI_TO_TCHAR("guildName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithLeavedUserId(Data->HasField(ANSI_TO_TCHAR("leavedUserId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("leavedUserId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
