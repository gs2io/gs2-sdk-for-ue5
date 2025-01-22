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

#pragma once

#include "CoreMinimal.h"
#include "Core/Gs2Object.h"
#include "RoleModel.h"

namespace Gs2::Guild::Model
{
    class GS2GUILD_API FGuildModelMaster final : public Gs2Object, public TSharedFromThis<FGuildModelMaster>
    {
        TOptional<FString> GuildModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> DefaultMaximumMemberCountValue;
        TOptional<int32> MaximumMemberCountValue;
        TOptional<int32> InactivityPeriodDaysValue;
        TSharedPtr<TArray<TSharedPtr<FRoleModel>>> RolesValue;
        TOptional<FString> GuildMasterRoleValue;
        TOptional<FString> GuildMemberDefaultRoleValue;
        TOptional<int32> RejoinCoolTimeMinutesValue;
        TOptional<int32> MaxConcurrentJoinGuildsValue;
        TOptional<int32> MaxConcurrentGuildMasterCountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FGuildModelMaster();
        FGuildModelMaster(
            const FGuildModelMaster& From
        );
        virtual ~FGuildModelMaster() override = default;

        TSharedPtr<FGuildModelMaster> WithGuildModelId(const TOptional<FString> GuildModelId);
        TSharedPtr<FGuildModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FGuildModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FGuildModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGuildModelMaster> WithDefaultMaximumMemberCount(const TOptional<int32> DefaultMaximumMemberCount);
        TSharedPtr<FGuildModelMaster> WithMaximumMemberCount(const TOptional<int32> MaximumMemberCount);
        TSharedPtr<FGuildModelMaster> WithInactivityPeriodDays(const TOptional<int32> InactivityPeriodDays);
        TSharedPtr<FGuildModelMaster> WithRoles(const TSharedPtr<TArray<TSharedPtr<FRoleModel>>> Roles);
        TSharedPtr<FGuildModelMaster> WithGuildMasterRole(const TOptional<FString> GuildMasterRole);
        TSharedPtr<FGuildModelMaster> WithGuildMemberDefaultRole(const TOptional<FString> GuildMemberDefaultRole);
        TSharedPtr<FGuildModelMaster> WithRejoinCoolTimeMinutes(const TOptional<int32> RejoinCoolTimeMinutes);
        TSharedPtr<FGuildModelMaster> WithMaxConcurrentJoinGuilds(const TOptional<int32> MaxConcurrentJoinGuilds);
        TSharedPtr<FGuildModelMaster> WithMaxConcurrentGuildMasterCount(const TOptional<int32> MaxConcurrentGuildMasterCount);
        TSharedPtr<FGuildModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGuildModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FGuildModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetGuildModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetDefaultMaximumMemberCount() const;
        FString GetDefaultMaximumMemberCountString() const;
        TOptional<int32> GetMaximumMemberCount() const;
        FString GetMaximumMemberCountString() const;
        TOptional<int32> GetInactivityPeriodDays() const;
        FString GetInactivityPeriodDaysString() const;
        TSharedPtr<TArray<TSharedPtr<FRoleModel>>> GetRoles() const;
        TOptional<FString> GetGuildMasterRole() const;
        TOptional<FString> GetGuildMemberDefaultRole() const;
        TOptional<int32> GetRejoinCoolTimeMinutes() const;
        FString GetRejoinCoolTimeMinutesString() const;
        TOptional<int32> GetMaxConcurrentJoinGuilds() const;
        FString GetMaxConcurrentJoinGuildsString() const;
        TOptional<int32> GetMaxConcurrentGuildMasterCount() const;
        FString GetMaxConcurrentGuildMasterCountString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);

        static TSharedPtr<FGuildModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGuildModelMaster, ESPMode::ThreadSafe> FGuildModelMasterPtr;
}