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

#include "Guild/Model/Guild.h"

namespace Gs2::Guild::Model
{
    FGuild::FGuild():
        GuildIdValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DisplayNameValue(TOptional<FString>()),
        Attribute1Value(TOptional<int32>()),
        Attribute2Value(TOptional<int32>()),
        Attribute3Value(TOptional<int32>()),
        Attribute4Value(TOptional<int32>()),
        Attribute5Value(TOptional<int32>()),
        MetadataValue(TOptional<FString>()),
        JoinPolicyValue(TOptional<FString>()),
        CustomRolesValue(nullptr),
        GuildMemberDefaultRoleValue(TOptional<FString>()),
        CurrentMaximumMemberCountValue(TOptional<int32>()),
        MembersValue(nullptr),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FGuild::FGuild(
        const FGuild& From
    ):
        GuildIdValue(From.GuildIdValue),
        GuildModelNameValue(From.GuildModelNameValue),
        NameValue(From.NameValue),
        DisplayNameValue(From.DisplayNameValue),
        Attribute1Value(From.Attribute1Value),
        Attribute2Value(From.Attribute2Value),
        Attribute3Value(From.Attribute3Value),
        Attribute4Value(From.Attribute4Value),
        Attribute5Value(From.Attribute5Value),
        MetadataValue(From.MetadataValue),
        JoinPolicyValue(From.JoinPolicyValue),
        CustomRolesValue(From.CustomRolesValue),
        GuildMemberDefaultRoleValue(From.GuildMemberDefaultRoleValue),
        CurrentMaximumMemberCountValue(From.CurrentMaximumMemberCountValue),
        MembersValue(From.MembersValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FGuild> FGuild::WithGuildId(
        const TOptional<FString> GuildId
    )
    {
        this->GuildIdValue = GuildId;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithDisplayName(
        const TOptional<FString> DisplayName
    )
    {
        this->DisplayNameValue = DisplayName;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithAttribute1(
        const TOptional<int32> Attribute1
    )
    {
        this->Attribute1Value = Attribute1;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithAttribute2(
        const TOptional<int32> Attribute2
    )
    {
        this->Attribute2Value = Attribute2;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithAttribute3(
        const TOptional<int32> Attribute3
    )
    {
        this->Attribute3Value = Attribute3;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithAttribute4(
        const TOptional<int32> Attribute4
    )
    {
        this->Attribute4Value = Attribute4;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithAttribute5(
        const TOptional<int32> Attribute5
    )
    {
        this->Attribute5Value = Attribute5;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithJoinPolicy(
        const TOptional<FString> JoinPolicy
    )
    {
        this->JoinPolicyValue = JoinPolicy;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithCustomRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> CustomRoles
    )
    {
        this->CustomRolesValue = CustomRoles;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithGuildMemberDefaultRole(
        const TOptional<FString> GuildMemberDefaultRole
    )
    {
        this->GuildMemberDefaultRoleValue = GuildMemberDefaultRole;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithCurrentMaximumMemberCount(
        const TOptional<int32> CurrentMaximumMemberCount
    )
    {
        this->CurrentMaximumMemberCountValue = CurrentMaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithMembers(
        const TSharedPtr<TArray<TSharedPtr<Model::FMember>>> Members
    )
    {
        this->MembersValue = Members;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGuild> FGuild::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FGuild::GetGuildId() const
    {
        return GuildIdValue;
    }
    TOptional<FString> FGuild::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }
    TOptional<FString> FGuild::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGuild::GetDisplayName() const
    {
        return DisplayNameValue;
    }
    TOptional<int32> FGuild::GetAttribute1() const
    {
        return Attribute1Value;
    }

    FString FGuild::GetAttribute1String() const
    {
        if (!Attribute1Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute1Value.GetValue());
    }
    TOptional<int32> FGuild::GetAttribute2() const
    {
        return Attribute2Value;
    }

    FString FGuild::GetAttribute2String() const
    {
        if (!Attribute2Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute2Value.GetValue());
    }
    TOptional<int32> FGuild::GetAttribute3() const
    {
        return Attribute3Value;
    }

    FString FGuild::GetAttribute3String() const
    {
        if (!Attribute3Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute3Value.GetValue());
    }
    TOptional<int32> FGuild::GetAttribute4() const
    {
        return Attribute4Value;
    }

    FString FGuild::GetAttribute4String() const
    {
        if (!Attribute4Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute4Value.GetValue());
    }
    TOptional<int32> FGuild::GetAttribute5() const
    {
        return Attribute5Value;
    }

    FString FGuild::GetAttribute5String() const
    {
        if (!Attribute5Value.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), Attribute5Value.GetValue());
    }
    TOptional<FString> FGuild::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FGuild::GetJoinPolicy() const
    {
        return JoinPolicyValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> FGuild::GetCustomRoles() const
    {
        return CustomRolesValue;
    }
    TOptional<FString> FGuild::GetGuildMemberDefaultRole() const
    {
        return GuildMemberDefaultRoleValue;
    }
    TOptional<int32> FGuild::GetCurrentMaximumMemberCount() const
    {
        return CurrentMaximumMemberCountValue;
    }

    FString FGuild::GetCurrentMaximumMemberCountString() const
    {
        if (!CurrentMaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CurrentMaximumMemberCountValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FMember>>> FGuild::GetMembers() const
    {
        return MembersValue;
    }
    TOptional<int64> FGuild::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FGuild::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FGuild::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FGuild::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FGuild::GetRevision() const
    {
        return RevisionValue;
    }

    FString FGuild::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FGuild::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuild::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuild::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuild::GetGuildModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuild::GetGuildNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):guild:(?<guildModelName>.+):(?<guildName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGuild> FGuild::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGuild>()
            ->WithGuildId(Data->HasField(ANSI_TO_TCHAR("guildId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildId"), v))
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
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDisplayName(Data->HasField(ANSI_TO_TCHAR("displayName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("displayName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithAttribute1(Data->HasField(ANSI_TO_TCHAR("attribute1")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute1"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAttribute2(Data->HasField(ANSI_TO_TCHAR("attribute2")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute2"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAttribute3(Data->HasField(ANSI_TO_TCHAR("attribute3")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute3"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAttribute4(Data->HasField(ANSI_TO_TCHAR("attribute4")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute4"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithAttribute5(Data->HasField(ANSI_TO_TCHAR("attribute5")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("attribute5"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithJoinPolicy(Data->HasField(ANSI_TO_TCHAR("joinPolicy")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("joinPolicy"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCustomRoles(Data->HasField(ANSI_TO_TCHAR("customRoles")) ? [Data]() -> TSharedPtr<TArray<Model::FRoleModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRoleModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("customRoles")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("customRoles")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("customRoles")))
                        {
                            v->Add(Model::FRoleModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRoleModelPtr>>())
            ->WithGuildMemberDefaultRole(Data->HasField(ANSI_TO_TCHAR("guildMemberDefaultRole")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildMemberDefaultRole"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithCurrentMaximumMemberCount(Data->HasField(ANSI_TO_TCHAR("currentMaximumMemberCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("currentMaximumMemberCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMembers(Data->HasField(ANSI_TO_TCHAR("members")) ? [Data]() -> TSharedPtr<TArray<Model::FMemberPtr>>
                {
                    auto v = MakeShared<TArray<Model::FMemberPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("members")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("members")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("members")))
                        {
                            v->Add(Model::FMember::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FMemberPtr>>())
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
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

    TSharedPtr<FJsonObject> FGuild::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GuildIdValue.IsSet())
        {
            JsonRootObject->SetStringField("guildId", GuildIdValue.GetValue());
        }
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelName", GuildModelNameValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DisplayNameValue.IsSet())
        {
            JsonRootObject->SetStringField("displayName", DisplayNameValue.GetValue());
        }
        if (Attribute1Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute1", Attribute1Value.GetValue());
        }
        if (Attribute2Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute2", Attribute2Value.GetValue());
        }
        if (Attribute3Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute3", Attribute3Value.GetValue());
        }
        if (Attribute4Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute4", Attribute4Value.GetValue());
        }
        if (Attribute5Value.IsSet())
        {
            JsonRootObject->SetNumberField("attribute5", Attribute5Value.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (JoinPolicyValue.IsSet())
        {
            JsonRootObject->SetStringField("joinPolicy", JoinPolicyValue.GetValue());
        }
        if (CustomRolesValue != nullptr && CustomRolesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *CustomRolesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("customRoles", v);
        }
        if (GuildMemberDefaultRoleValue.IsSet())
        {
            JsonRootObject->SetStringField("guildMemberDefaultRole", GuildMemberDefaultRoleValue.GetValue());
        }
        if (CurrentMaximumMemberCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("currentMaximumMemberCount", CurrentMaximumMemberCountValue.GetValue());
        }
        if (MembersValue != nullptr && MembersValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *MembersValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("members", v);
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("updatedAt", FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField("revision", FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FGuild::TypeName = "Guild";
}