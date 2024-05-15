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

#include "Guild/Model/ChangeMemberNotification.h"

namespace Gs2::Guild::Model
{

    TSharedPtr<FChangeMemberNotification> FChangeMemberNotification::WithNamespaceName(
        const TOptional<FString> NamespaceName
    ) {
        NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }
    TOptional<FString> FChangeMemberNotification::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TSharedPtr<FChangeMemberNotification> FChangeMemberNotification::WithGuildModelName(
        const TOptional<FString> GuildModelName
    ) {
        GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }
    TOptional<FString> FChangeMemberNotification::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TSharedPtr<FChangeMemberNotification> FChangeMemberNotification::WithGuildName(
        const TOptional<FString> GuildName
    ) {
        GuildNameValue = GuildName;
        return SharedThis(this);
    }
    TOptional<FString> FChangeMemberNotification::GetGuildName() const
    {
        return GuildNameValue;
    }

    TSharedPtr<FChangeMemberNotification> FChangeMemberNotification::WithChangedUserId(
        const TOptional<FString> ChangedUserId
    ) {
        ChangedUserIdValue = ChangedUserId;
        return SharedThis(this);
    }
    TOptional<FString> FChangeMemberNotification::GetChangedUserId() const
    {
        return ChangedUserIdValue;
    }

    TSharedPtr<FChangeMemberNotification> FChangeMemberNotification::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FChangeMemberNotification>()
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
            ->WithChangedUserId(Data->HasField("changedUserId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("changedUserId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }
}
