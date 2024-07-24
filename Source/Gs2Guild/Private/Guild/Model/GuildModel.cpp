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

#include "Guild/Model/GuildModel.h"

namespace Gs2::Guild::Model
{
    FGuildModel::FGuildModel():
        GuildModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        DefaultMaximumMemberCountValue(TOptional<int32>()),
        MaximumMemberCountValue(TOptional<int32>()),
        InactivityPeriodDaysValue(TOptional<int32>()),
        RolesValue(nullptr),
        GuildMasterRoleValue(TOptional<FString>()),
        GuildMemberDefaultRoleValue(TOptional<FString>()),
        RejoinCoolTimeMinutesValue(TOptional<int32>())
    {
    }

    FGuildModel::FGuildModel(
        const FGuildModel& From
    ):
        GuildModelIdValue(From.GuildModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        DefaultMaximumMemberCountValue(From.DefaultMaximumMemberCountValue),
        MaximumMemberCountValue(From.MaximumMemberCountValue),
        InactivityPeriodDaysValue(From.InactivityPeriodDaysValue),
        RolesValue(From.RolesValue),
        GuildMasterRoleValue(From.GuildMasterRoleValue),
        GuildMemberDefaultRoleValue(From.GuildMemberDefaultRoleValue),
        RejoinCoolTimeMinutesValue(From.RejoinCoolTimeMinutesValue)
    {
    }

    TSharedPtr<FGuildModel> FGuildModel::WithGuildModelId(
        const TOptional<FString> GuildModelId
    )
    {
        this->GuildModelIdValue = GuildModelId;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithDefaultMaximumMemberCount(
        const TOptional<int32> DefaultMaximumMemberCount
    )
    {
        this->DefaultMaximumMemberCountValue = DefaultMaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithMaximumMemberCount(
        const TOptional<int32> MaximumMemberCount
    )
    {
        this->MaximumMemberCountValue = MaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithInactivityPeriodDays(
        const TOptional<int32> InactivityPeriodDays
    )
    {
        this->InactivityPeriodDaysValue = InactivityPeriodDays;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> Roles
    )
    {
        this->RolesValue = Roles;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithGuildMasterRole(
        const TOptional<FString> GuildMasterRole
    )
    {
        this->GuildMasterRoleValue = GuildMasterRole;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithGuildMemberDefaultRole(
        const TOptional<FString> GuildMemberDefaultRole
    )
    {
        this->GuildMemberDefaultRoleValue = GuildMemberDefaultRole;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithRejoinCoolTimeMinutes(
        const TOptional<int32> RejoinCoolTimeMinutes
    )
    {
        this->RejoinCoolTimeMinutesValue = RejoinCoolTimeMinutes;
        return SharedThis(this);
    }
    TOptional<FString> FGuildModel::GetGuildModelId() const
    {
        return GuildModelIdValue;
    }
    TOptional<FString> FGuildModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FGuildModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int32> FGuildModel::GetDefaultMaximumMemberCount() const
    {
        return DefaultMaximumMemberCountValue;
    }

    FString FGuildModel::GetDefaultMaximumMemberCountString() const
    {
        if (!DefaultMaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumMemberCountValue.GetValue());
    }
    TOptional<int32> FGuildModel::GetMaximumMemberCount() const
    {
        return MaximumMemberCountValue;
    }

    FString FGuildModel::GetMaximumMemberCountString() const
    {
        if (!MaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumMemberCountValue.GetValue());
    }
    TOptional<int32> FGuildModel::GetInactivityPeriodDays() const
    {
        return InactivityPeriodDaysValue;
    }

    FString FGuildModel::GetInactivityPeriodDaysString() const
    {
        if (!InactivityPeriodDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InactivityPeriodDaysValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> FGuildModel::GetRoles() const
    {
        return RolesValue;
    }
    TOptional<FString> FGuildModel::GetGuildMasterRole() const
    {
        return GuildMasterRoleValue;
    }
    TOptional<FString> FGuildModel::GetGuildMemberDefaultRole() const
    {
        return GuildMemberDefaultRoleValue;
    }
    TOptional<int32> FGuildModel::GetRejoinCoolTimeMinutes() const
    {
        return RejoinCoolTimeMinutesValue;
    }

    FString FGuildModel::GetRejoinCoolTimeMinutesString() const
    {
        if (!RejoinCoolTimeMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RejoinCoolTimeMinutesValue.GetValue());
    }

    TOptional<FString> FGuildModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuildModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuildModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FGuildModel::GetGuildModelNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):guild:(?<namespaceName>.+):model:(?<guildModelName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FGuildModel> FGuildModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGuildModel>()
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
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FGuildModel::ToJson() const
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
        return JsonRootObject;
    }

    FString FGuildModel::TypeName = "GuildModel";
}