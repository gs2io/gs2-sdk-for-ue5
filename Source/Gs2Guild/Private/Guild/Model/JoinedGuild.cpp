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

#include "Guild/Model/JoinedGuild.h"

namespace Gs2::Guild::Model
{
    FJoinedGuild::FJoinedGuild():
        JoinedGuildIdValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
        GuildNameValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        CreatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FJoinedGuild::FJoinedGuild(
        const FJoinedGuild& From
    ):
        JoinedGuildIdValue(From.JoinedGuildIdValue),
        GuildModelNameValue(From.GuildModelNameValue),
        GuildNameValue(From.GuildNameValue),
        UserIdValue(From.UserIdValue),
        CreatedAtValue(From.CreatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::WithJoinedGuildId(
        const TOptional<FString> JoinedGuildId
    )
    {
        this->JoinedGuildIdValue = JoinedGuildId;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::WithGuildName(
        const TOptional<FString> GuildName
    )
    {
        this->GuildNameValue = GuildName;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FJoinedGuild::GetJoinedGuildId() const
    {
        return JoinedGuildIdValue;
    }
    TOptional<FString> FJoinedGuild::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }
    TOptional<FString> FJoinedGuild::GetGuildName() const
    {
        return GuildNameValue;
    }
    TOptional<FString> FJoinedGuild::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FJoinedGuild::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FJoinedGuild::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FJoinedGuild::GetRevision() const
    {
        return RevisionValue;
    }

    FString FJoinedGuild::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FJoinedGuild::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):user:(?<userId>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedGuild::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):user:(?<userId>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedGuild::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):user:(?<userId>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedGuild::GetUserIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):user:(?<userId>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedGuild::GetGuildModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):user:(?<userId>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FJoinedGuild::GetGuildNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):user:(?<userId>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FJoinedGuild> FJoinedGuild::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FJoinedGuild>()
            ->WithJoinedGuildId(Data->HasField(ANSI_TO_TCHAR("joinedGuildId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("joinedGuildId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildModelName(Data->HasField(ANSI_TO_TCHAR("guildModelName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildModelName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildName(Data->HasField(ANSI_TO_TCHAR("guildName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildName"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FJoinedGuild::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (JoinedGuildIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("joinedGuildId"), JoinedGuildIdValue.GetValue());
        }
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("guildModelName"), GuildModelNameValue.GetValue());
        }
        if (GuildNameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("guildName"), GuildNameValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("userId"), UserIdValue.GetValue());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("createdAt"), FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FJoinedGuild::TypeName = "JoinedGuild";
}