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
    class GS2GUILD_API FGuildModel final : public Gs2Object, public TSharedFromThis<FGuildModel>
    {
        TOptional<FString> GuildModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> DefaultMaximumMemberCountValue;
        TOptional<int32> MaximumMemberCountValue;
        TSharedPtr<TArray<TSharedPtr<FRoleModel>>> RolesValue;
        TOptional<FString> GuildMasterRoleValue;
        TOptional<FString> GuildMemberDefaultRoleValue;
        TOptional<int32> RejoinCoolTimeMinutesValue;

    public:
        FGuildModel();
        FGuildModel(
            const FGuildModel& From
        );
        virtual ~FGuildModel() override = default;

        TSharedPtr<FGuildModel> WithGuildModelId(const TOptional<FString> GuildModelId);
        TSharedPtr<FGuildModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FGuildModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGuildModel> WithDefaultMaximumMemberCount(const TOptional<int32> DefaultMaximumMemberCount);
        TSharedPtr<FGuildModel> WithMaximumMemberCount(const TOptional<int32> MaximumMemberCount);
        TSharedPtr<FGuildModel> WithRoles(const TSharedPtr<TArray<TSharedPtr<FRoleModel>>> Roles);
        TSharedPtr<FGuildModel> WithGuildMasterRole(const TOptional<FString> GuildMasterRole);
        TSharedPtr<FGuildModel> WithGuildMemberDefaultRole(const TOptional<FString> GuildMemberDefaultRole);
        TSharedPtr<FGuildModel> WithRejoinCoolTimeMinutes(const TOptional<int32> RejoinCoolTimeMinutes);

        TOptional<FString> GetGuildModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetDefaultMaximumMemberCount() const;
        FString GetDefaultMaximumMemberCountString() const;
        TOptional<int32> GetMaximumMemberCount() const;
        FString GetMaximumMemberCountString() const;
        TSharedPtr<TArray<TSharedPtr<FRoleModel>>> GetRoles() const;
        TOptional<FString> GetGuildMasterRole() const;
        TOptional<FString> GetGuildMemberDefaultRole() const;
        TOptional<int32> GetRejoinCoolTimeMinutes() const;
        FString GetRejoinCoolTimeMinutesString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGuildModelNameFromGrn(const FString Grn);

        static TSharedPtr<FGuildModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGuildModel, ESPMode::ThreadSafe> FGuildModelPtr;
}