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

#include "Guild/Model/GuildModelMaster.h"

namespace Gs2::Guild::Model
{
    FGuildModelMaster::FGuildModelMaster():
        GuildModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        DescriptionValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultMaximumMemberCountValue(TOptional<int32>()),
        MaximumMemberCountValue(TOptional<int32>()),
        InactivityPeriodDaysValue(TOptional<int32>()),
        RolesValue(nullptr),
        GuildMasterRoleValue(TOptional<FString>()),
        GuildMemberDefaultRoleValue(TOptional<FString>()),
        RejoinCoolTimeMinutesValue(TOptional<int32>()),
        MaxConcurrentJoinGuildsValue(TOptional<int32>()),
        MaxConcurrentGuildMasterCountValue(TOptional<int32>()),
        CreatedAtValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FGuildModelMaster::FGuildModelMaster(
        const FGuildModelMaster& From
    ):
        GuildModelIdValue(From.GuildModelIdValue),
        NameValue(From.NameValue),
        DescriptionValue(From.DescriptionValue),
        MetadataValue(From.MetadataValue),
        DefaultMaximumMemberCountValue(From.DefaultMaximumMemberCountValue),
        MaximumMemberCountValue(From.MaximumMemberCountValue),
        InactivityPeriodDaysValue(From.InactivityPeriodDaysValue),
        RolesValue(From.RolesValue),
        GuildMasterRoleValue(From.GuildMasterRoleValue),
        GuildMemberDefaultRoleValue(From.GuildMemberDefaultRoleValue),
        RejoinCoolTimeMinutesValue(From.RejoinCoolTimeMinutesValue),
        MaxConcurrentJoinGuildsValue(From.MaxConcurrentJoinGuildsValue),
        MaxConcurrentGuildMasterCountValue(From.MaxConcurrentGuildMasterCountValue),
        CreatedAtValue(From.CreatedAtValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithGuildModelId(
        const TOptional<FString> GuildModelId
    )
    {
        this->GuildModelIdValue = GuildModelId;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithDefaultMaximumMemberCount(
        const TOptional<int32> DefaultMaximumMemberCount
    )
    {
        this->DefaultMaximumMemberCountValue = DefaultMaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithMaximumMemberCount(
        const TOptional<int32> MaximumMemberCount
    )
    {
        this->MaximumMemberCountValue = MaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithInactivityPeriodDays(
        const TOptional<int32> InactivityPeriodDays
    )
    {
        this->InactivityPeriodDaysValue = InactivityPeriodDays;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> Roles
    )
    {
        this->RolesValue = Roles;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithGuildMasterRole(
        const TOptional<FString> GuildMasterRole
    )
    {
        this->GuildMasterRoleValue = GuildMasterRole;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithGuildMemberDefaultRole(
        const TOptional<FString> GuildMemberDefaultRole
    )
    {
        this->GuildMemberDefaultRoleValue = GuildMemberDefaultRole;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithRejoinCoolTimeMinutes(
        const TOptional<int32> RejoinCoolTimeMinutes
    )
    {
        this->RejoinCoolTimeMinutesValue = RejoinCoolTimeMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithMaxConcurrentJoinGuilds(
        const TOptional<int32> MaxConcurrentJoinGuilds
    )
    {
        this->MaxConcurrentJoinGuildsValue = MaxConcurrentJoinGuilds;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithMaxConcurrentGuildMasterCount(
        const TOptional<int32> MaxConcurrentGuildMasterCount
    )
    {
        this->MaxConcurrentGuildMasterCountValue = MaxConcurrentGuildMasterCount;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FGuildModelMaster::GetGuildModelId() const
    {
        return GuildModelIdValue;
    }
    TOptional<FString> FGuildModelMaster::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGuildModelMaster::GetDescription() const
    {
        return DescriptionValue;
    }
    TOptional<FString> FGuildModelMaster::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FGuildModelMaster::GetDefaultMaximumMemberCount() const
    {
        return DefaultMaximumMemberCountValue;
    }

    FString FGuildModelMaster::GetDefaultMaximumMemberCountString() const
    {
        if (!DefaultMaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumMemberCountValue.GetValue());
    }
    TOptional<int32> FGuildModelMaster::GetMaximumMemberCount() const
    {
        return MaximumMemberCountValue;
    }

    FString FGuildModelMaster::GetMaximumMemberCountString() const
    {
        if (!MaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumMemberCountValue.GetValue());
    }
    TOptional<int32> FGuildModelMaster::GetInactivityPeriodDays() const
    {
        return InactivityPeriodDaysValue;
    }

    FString FGuildModelMaster::GetInactivityPeriodDaysString() const
    {
        if (!InactivityPeriodDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InactivityPeriodDaysValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> FGuildModelMaster::GetRoles() const
    {
        return RolesValue;
    }
    TOptional<FString> FGuildModelMaster::GetGuildMasterRole() const
    {
        return GuildMasterRoleValue;
    }
    TOptional<FString> FGuildModelMaster::GetGuildMemberDefaultRole() const
    {
        return GuildMemberDefaultRoleValue;
    }
    TOptional<int32> FGuildModelMaster::GetRejoinCoolTimeMinutes() const
    {
        return RejoinCoolTimeMinutesValue;
    }

    FString FGuildModelMaster::GetRejoinCoolTimeMinutesString() const
    {
        if (!RejoinCoolTimeMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RejoinCoolTimeMinutesValue.GetValue());
    }
    TOptional<int32> FGuildModelMaster::GetMaxConcurrentJoinGuilds() const
    {
        return MaxConcurrentJoinGuildsValue;
    }

    FString FGuildModelMaster::GetMaxConcurrentJoinGuildsString() const
    {
        if (!MaxConcurrentJoinGuildsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxConcurrentJoinGuildsValue.GetValue());
    }
    TOptional<int32> FGuildModelMaster::GetMaxConcurrentGuildMasterCount() const
    {
        return MaxConcurrentGuildMasterCountValue;
    }

    FString FGuildModelMaster::GetMaxConcurrentGuildMasterCountString() const
    {
        if (!MaxConcurrentGuildMasterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxConcurrentGuildMasterCountValue.GetValue());
    }
    TOptional<int64> FGuildModelMaster::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FGuildModelMaster::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }
    TOptional<int64> FGuildModelMaster::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FGuildModelMaster::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FGuildModelMaster::GetRevision() const
    {
        return RevisionValue;
    }

    FString FGuildModelMaster::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FGuildModelMaster::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuildModelMaster::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuildModelMaster::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuildModelMaster::GetGuildModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGuildModelMaster> FGuildModelMaster::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGuildModelMaster>()
            ->WithGuildModelId(Data->HasField(ANSI_TO_TCHAR("guildModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildModelId"), v))
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
            ->WithDescription(Data->HasField(ANSI_TO_TCHAR("description")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("description"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDefaultMaximumMemberCount(Data->HasField(ANSI_TO_TCHAR("defaultMaximumMemberCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("defaultMaximumMemberCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaximumMemberCount(Data->HasField(ANSI_TO_TCHAR("maximumMemberCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maximumMemberCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithInactivityPeriodDays(Data->HasField(ANSI_TO_TCHAR("inactivityPeriodDays")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("inactivityPeriodDays"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithRoles(Data->HasField(ANSI_TO_TCHAR("roles")) ? [Data]() -> TSharedPtr<TArray<Model::FRoleModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FRoleModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("roles")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("roles")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("roles")))
                        {
                            v->Add(Model::FRoleModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FRoleModelPtr>>())
            ->WithGuildMasterRole(Data->HasField(ANSI_TO_TCHAR("guildMasterRole")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildMasterRole"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildMemberDefaultRole(Data->HasField(ANSI_TO_TCHAR("guildMemberDefaultRole")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildMemberDefaultRole"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRejoinCoolTimeMinutes(Data->HasField(ANSI_TO_TCHAR("rejoinCoolTimeMinutes")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("rejoinCoolTimeMinutes"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxConcurrentJoinGuilds(Data->HasField(ANSI_TO_TCHAR("maxConcurrentJoinGuilds")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxConcurrentJoinGuilds"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithMaxConcurrentGuildMasterCount(Data->HasField(ANSI_TO_TCHAR("maxConcurrentGuildMasterCount")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("maxConcurrentGuildMasterCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
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

    TSharedPtr<FJsonObject> FGuildModelMaster::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GuildModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelId", GuildModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (DescriptionValue.IsSet())
        {
            JsonRootObject->SetStringField("description", DescriptionValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (DefaultMaximumMemberCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("defaultMaximumMemberCount", DefaultMaximumMemberCountValue.GetValue());
        }
        if (MaximumMemberCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maximumMemberCount", MaximumMemberCountValue.GetValue());
        }
        if (InactivityPeriodDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField("inactivityPeriodDays", InactivityPeriodDaysValue.GetValue());
        }
        if (RolesValue != nullptr && RolesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RolesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("roles", v);
        }
        if (GuildMasterRoleValue.IsSet())
        {
            JsonRootObject->SetStringField("guildMasterRole", GuildMasterRoleValue.GetValue());
        }
        if (GuildMemberDefaultRoleValue.IsSet())
        {
            JsonRootObject->SetStringField("guildMemberDefaultRole", GuildMemberDefaultRoleValue.GetValue());
        }
        if (RejoinCoolTimeMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField("rejoinCoolTimeMinutes", RejoinCoolTimeMinutesValue.GetValue());
        }
        if (MaxConcurrentJoinGuildsValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxConcurrentJoinGuilds", MaxConcurrentJoinGuildsValue.GetValue());
        }
        if (MaxConcurrentGuildMasterCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("maxConcurrentGuildMasterCount", MaxConcurrentGuildMasterCountValue.GetValue());
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

    FString FGuildModelMaster::TypeName = "GuildModelMaster";
}