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
        RejoinCoolTimeMinutesValue(TOptional<int32>()),
        MaxConcurrentJoinGuildsValue(TOptional<int32>()),
        MaxConcurrentGuildMasterCountValue(TOptional<int32>())
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
        RejoinCoolTimeMinutesValue(From.RejoinCoolTimeMinutesValue),
        MaxConcurrentJoinGuildsValue(From.MaxConcurrentJoinGuildsValue),
        MaxConcurrentGuildMasterCountValue(From.MaxConcurrentGuildMasterCountValue)
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

    TSharedPtr<FGuildModel> FGuildModel::WithMaxConcurrentJoinGuilds(
        const TOptional<int32> MaxConcurrentJoinGuilds
    )
    {
        this->MaxConcurrentJoinGuildsValue = MaxConcurrentJoinGuilds;
        return SharedThis(this);
    }

    TSharedPtr<FGuildModel> FGuildModel::WithMaxConcurrentGuildMasterCount(
        const TOptional<int32> MaxConcurrentGuildMasterCount
    )
    {
        this->MaxConcurrentGuildMasterCountValue = MaxConcurrentGuildMasterCount;
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
    TOptional<int32> FGuildModel::GetMaxConcurrentJoinGuilds() const
    {
        return MaxConcurrentJoinGuildsValue;
    }

    FString FGuildModel::GetMaxConcurrentJoinGuildsString() const
    {
        if (!MaxConcurrentJoinGuildsValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxConcurrentJoinGuildsValue.GetValue());
    }
    TOptional<int32> FGuildModel::GetMaxConcurrentGuildMasterCount() const
    {
        return MaxConcurrentGuildMasterCountValue;
    }

    FString FGuildModel::GetMaxConcurrentGuildMasterCountString() const
    {
        if (!MaxConcurrentGuildMasterCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MaxConcurrentGuildMasterCountValue.GetValue());
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
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(v);
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
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("roles")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<Model::FRoleModelPtr>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("roles")))
                    {
                        v->Add(Model::FRoleModel::FromJson(JsonObjectValue->AsObject()));
                    }
                    return v;
                 }() : nullptr)
            ->WithGuildMasterRole(Data->HasField(ANSI_TO_TCHAR("guildMasterRole")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildMasterRole"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGuildMemberDefaultRole(Data->HasField(ANSI_TO_TCHAR("guildMemberDefaultRole")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("guildMemberDefaultRole"), v))
                    {
                        return TOptional(v);
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

    TSharedPtr<FJsonObject> FGuildModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GuildModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("guildModelId"), GuildModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("metadata"), MetadataValue.GetValue());
        }
        if (DefaultMaximumMemberCountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("defaultMaximumMemberCount"), DefaultMaximumMemberCountValue.GetValue());
        }
        if (MaximumMemberCountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maximumMemberCount"), MaximumMemberCountValue.GetValue());
        }
        if (InactivityPeriodDaysValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("inactivityPeriodDays"), InactivityPeriodDaysValue.GetValue());
        }
        if (RolesValue != nullptr && RolesValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *RolesValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField(TEXT("roles"), v);
        }
        if (GuildMasterRoleValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("guildMasterRole"), GuildMasterRoleValue.GetValue());
        }
        if (GuildMemberDefaultRoleValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("guildMemberDefaultRole"), GuildMemberDefaultRoleValue.GetValue());
        }
        if (RejoinCoolTimeMinutesValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("rejoinCoolTimeMinutes"), RejoinCoolTimeMinutesValue.GetValue());
        }
        if (MaxConcurrentJoinGuildsValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maxConcurrentJoinGuilds"), MaxConcurrentJoinGuildsValue.GetValue());
        }
        if (MaxConcurrentGuildMasterCountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("maxConcurrentGuildMasterCount"), MaxConcurrentGuildMasterCountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGuildModel::TypeName = "GuildModel";
}
#include "Guild/Model/Cache/GuildModel.h"

namespace Gs2::Guild::Model::Cache
{
    FString FGuildModelCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("guild:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":GuildModel");
    }

    FString FGuildModelCache::CreateCacheKey(
        TOptional<FString> CacheOwnerArgumentGuildModelName
    )
    {
        return
            FString()
            + CacheOwnerArgumentGuildModelName.Get(FString())
            ;
    }

    bool FGuildModelCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGuildModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Guild::Model::FGuildModelPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Guild::Model::FGuildModelPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Guild::Model::FGuildModel>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentGuildModelName
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FGuildModelCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGuildModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Guild::Model::FGuildModelPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentGuildModelName
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        CacheSnapshot->Put(Gs2::Guild::Model::FGuildModel::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    FString FGuildModelCache::PutUserData(
        const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> TimeOffset,
        const Gs2::Guild::Model::FGuildModelPtr& Item
    )
    {
        if (!Item.IsValid()) return FString();
        Put(
            Cache,
            NamespaceName,
            Item->GetName(),
            TimeOffset,
            Item
        );
        return CreateCacheParentKey(
            NamespaceName,
            TimeOffset
        );
    }

    void FGuildModelCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGuildModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Guild::Model::FGuildModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentGuildModelName
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FGuildModelCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<FString> CacheOwnerArgumentGuildModelName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Guild::Model::FGuildModelPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Guild::Model::FGuildModelPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Guild::Model::FGuildModelPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentGuildModelName,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentGuildModelName,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("guildModel"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FGuildModelCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Guild::Model::FGuildModelPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Guild::Model::FGuildModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Guild::Model::FGuildModelPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Guild::Model::FGuildModel>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FGuildModelCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Guild::Model::FGuildModel::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}