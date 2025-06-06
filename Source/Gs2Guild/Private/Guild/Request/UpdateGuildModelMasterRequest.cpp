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

#include "Guild/Request/UpdateGuildModelMasterRequest.h"

namespace Gs2::Guild::Request
{
    FUpdateGuildModelMasterRequest::FUpdateGuildModelMasterRequest():
        NamespaceNameValue(TOptional<FString>()),
        GuildModelNameValue(TOptional<FString>()),
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
        MaxConcurrentGuildMasterCountValue(TOptional<int32>())
    {
    }

    FUpdateGuildModelMasterRequest::FUpdateGuildModelMasterRequest(
        const FUpdateGuildModelMasterRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        GuildModelNameValue(From.GuildModelNameValue),
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
        MaxConcurrentGuildMasterCountValue(From.MaxConcurrentGuildMasterCountValue)
    {
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithDescription(
        const TOptional<FString> Description
    )
    {
        this->DescriptionValue = Description;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithDefaultMaximumMemberCount(
        const TOptional<int32> DefaultMaximumMemberCount
    )
    {
        this->DefaultMaximumMemberCountValue = DefaultMaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithMaximumMemberCount(
        const TOptional<int32> MaximumMemberCount
    )
    {
        this->MaximumMemberCountValue = MaximumMemberCount;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithInactivityPeriodDays(
        const TOptional<int32> InactivityPeriodDays
    )
    {
        this->InactivityPeriodDaysValue = InactivityPeriodDays;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithRoles(
        const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> Roles
    )
    {
        this->RolesValue = Roles;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithGuildMasterRole(
        const TOptional<FString> GuildMasterRole
    )
    {
        this->GuildMasterRoleValue = GuildMasterRole;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithGuildMemberDefaultRole(
        const TOptional<FString> GuildMemberDefaultRole
    )
    {
        this->GuildMemberDefaultRoleValue = GuildMemberDefaultRole;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithRejoinCoolTimeMinutes(
        const TOptional<int32> RejoinCoolTimeMinutes
    )
    {
        this->RejoinCoolTimeMinutesValue = RejoinCoolTimeMinutes;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithMaxConcurrentJoinGuilds(
        const TOptional<int32> MaxConcurrentJoinGuilds
    )
    {
        this->MaxConcurrentJoinGuildsValue = MaxConcurrentJoinGuilds;
        return SharedThis(this);
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::WithMaxConcurrentGuildMasterCount(
        const TOptional<int32> MaxConcurrentGuildMasterCount
    )
    {
        this->MaxConcurrentGuildMasterCountValue = MaxConcurrentGuildMasterCount;
        return SharedThis(this);
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetDescription() const
    {
        return DescriptionValue;
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetMetadata() const
    {
        return MetadataValue;
    }

    TOptional<int32> FUpdateGuildModelMasterRequest::GetDefaultMaximumMemberCount() const
    {
        return DefaultMaximumMemberCountValue;
    }

    FString FUpdateGuildModelMasterRequest::GetDefaultMaximumMemberCountString() const
    {
        if (!DefaultMaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DefaultMaximumMemberCountValue.GetValue());
    }

    TOptional<int32> FUpdateGuildModelMasterRequest::GetMaximumMemberCount() const
    {
        return MaximumMemberCountValue;
    }

    FString FUpdateGuildModelMasterRequest::GetMaximumMemberCountString() const
    {
        if (!MaximumMemberCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaximumMemberCountValue.GetValue());
    }

    TOptional<int32> FUpdateGuildModelMasterRequest::GetInactivityPeriodDays() const
    {
        return InactivityPeriodDaysValue;
    }

    FString FUpdateGuildModelMasterRequest::GetInactivityPeriodDaysString() const
    {
        if (!InactivityPeriodDaysValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), InactivityPeriodDaysValue.GetValue());
    }

    TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> FUpdateGuildModelMasterRequest::GetRoles() const
    {
        if (!RolesValue.IsValid())
        {
            return nullptr;
        }
        return RolesValue;
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetGuildMasterRole() const
    {
        return GuildMasterRoleValue;
    }

    TOptional<FString> FUpdateGuildModelMasterRequest::GetGuildMemberDefaultRole() const
    {
        return GuildMemberDefaultRoleValue;
    }

    TOptional<int32> FUpdateGuildModelMasterRequest::GetRejoinCoolTimeMinutes() const
    {
        return RejoinCoolTimeMinutesValue;
    }

    FString FUpdateGuildModelMasterRequest::GetRejoinCoolTimeMinutesString() const
    {
        if (!RejoinCoolTimeMinutesValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), RejoinCoolTimeMinutesValue.GetValue());
    }

    TOptional<int32> FUpdateGuildModelMasterRequest::GetMaxConcurrentJoinGuilds() const
    {
        return MaxConcurrentJoinGuildsValue;
    }

    FString FUpdateGuildModelMasterRequest::GetMaxConcurrentJoinGuildsString() const
    {
        if (!MaxConcurrentJoinGuildsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxConcurrentJoinGuildsValue.GetValue());
    }

    TOptional<int32> FUpdateGuildModelMasterRequest::GetMaxConcurrentGuildMasterCount() const
    {
        return MaxConcurrentGuildMasterCountValue;
    }

    FString FUpdateGuildModelMasterRequest::GetMaxConcurrentGuildMasterCountString() const
    {
        if (!MaxConcurrentGuildMasterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxConcurrentGuildMasterCountValue.GetValue());
    }

    TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUpdateGuildModelMasterRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
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
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUpdateGuildModelMasterRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (GuildModelNameValue.IsSet())
        {
            JsonRootObject->SetStringField("guildModelName", GuildModelNameValue.GetValue());
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
        return JsonRootObject;
    }
}