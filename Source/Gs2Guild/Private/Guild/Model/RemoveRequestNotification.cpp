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

#include "Guild/Model/RemoveRequestNotification.h"

namespace Gs2::Guild::Model
{

    TSharedPtr<FRemoveRequestNotification> FRemoveRequestNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FRemoveRequestNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FRemoveRequestNotification> FRemoveRequestNotification::WithGuildModelName(
        const TOptional<FString> GuildModelName
    ) {
        GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }
    TOptional<FString> FRemoveRequestNotification::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TSharedPtr<FRemoveRequestNotification> FRemoveRequestNotification::WithGuildName(
        const TOptional<FString> GuildName
    ) {
        GuildNameValue = GuildName;
        return SharedThis(this);
    }
    TOptional<FString> FRemoveRequestNotification::GetGuildName() const
    {
        return GuildNameValue;
    }

    TSharedPtr<FRemoveRequestNotification> FRemoveRequestNotification::WithFromUserId(
        const TOptional<FString> FromUserId
    ) {
        FromUserIdValue = FromUserId;
        return SharedThis(this);
    }
    TOptional<FString> FRemoveRequestNotification::GetFromUserId() const
    {
        return FromUserIdValue;
    }

    TSharedPtr<FRemoveRequestNotification> FRemoveRequestNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRemoveRequestNotification>()
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
            ->WithFromUserId(Data->HasField("fromUserId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("fromUserId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
