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
#include "Dom/JsonObject.h"
#include "../Model/RoleModel.h"

namespace Gs2::Guild::Request
{
    class FCreateGuildModelMasterRequest;

    class GS2GUILD_API FCreateGuildModelMasterRequest final : public TSharedFromThis<FCreateGuildModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> DefaultMaximumMemberCountValue;
        TOptional<int32> MaximumMemberCountValue;
        TOptional<int32> InactivityPeriodDaysValue;
        TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> RolesValue;
        TOptional<FString> GuildMasterRoleValue;
        TOptional<FString> GuildMemberDefaultRoleValue;
        TOptional<int32> RejoinCoolTimeMinutesValue;
        TOptional<int32> MaxConcurrentJoinGuildsValue;
        TOptional<int32> MaxConcurrentGuildMasterCountValue;
        
    public:
        
        FCreateGuildModelMasterRequest();
        FCreateGuildModelMasterRequest(
            const FCreateGuildModelMasterRequest& From
        );
        ~FCreateGuildModelMasterRequest() = default;

        TSharedPtr<FCreateGuildModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FCreateGuildModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FCreateGuildModelMasterRequest> WithName(const TOptional<FString> Name);
        TSharedPtr<FCreateGuildModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCreateGuildModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCreateGuildModelMasterRequest> WithDefaultMaximumMemberCount(const TOptional<int32> DefaultMaximumMemberCount);
        TSharedPtr<FCreateGuildModelMasterRequest> WithMaximumMemberCount(const TOptional<int32> MaximumMemberCount);
        TSharedPtr<FCreateGuildModelMasterRequest> WithInactivityPeriodDays(const TOptional<int32> InactivityPeriodDays);
        TSharedPtr<FCreateGuildModelMasterRequest> WithRoles(const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> Roles);
        TSharedPtr<FCreateGuildModelMasterRequest> WithGuildMasterRole(const TOptional<FString> GuildMasterRole);
        TSharedPtr<FCreateGuildModelMasterRequest> WithGuildMemberDefaultRole(const TOptional<FString> GuildMemberDefaultRole);
        TSharedPtr<FCreateGuildModelMasterRequest> WithRejoinCoolTimeMinutes(const TOptional<int32> RejoinCoolTimeMinutes);
        TSharedPtr<FCreateGuildModelMasterRequest> WithMaxConcurrentJoinGuilds(const TOptional<int32> MaxConcurrentJoinGuilds);
        TSharedPtr<FCreateGuildModelMasterRequest> WithMaxConcurrentGuildMasterCount(const TOptional<int32> MaxConcurrentGuildMasterCount);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetDefaultMaximumMemberCount() const;
        FString GetDefaultMaximumMemberCountString() const;
        TOptional<int32> GetMaximumMemberCount() const;
        FString GetMaximumMemberCountString() const;
        TOptional<int32> GetInactivityPeriodDays() const;
        FString GetInactivityPeriodDaysString() const;TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> GetRoles() const;
        TOptional<FString> GetGuildMasterRole() const;
        TOptional<FString> GetGuildMemberDefaultRole() const;
        TOptional<int32> GetRejoinCoolTimeMinutes() const;
        FString GetRejoinCoolTimeMinutesString() const;
        TOptional<int32> GetMaxConcurrentJoinGuilds() const;
        FString GetMaxConcurrentJoinGuildsString() const;
        TOptional<int32> GetMaxConcurrentGuildMasterCount() const;
        FString GetMaxConcurrentGuildMasterCountString() const;

        static TSharedPtr<FCreateGuildModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FCreateGuildModelMasterRequest> FCreateGuildModelMasterRequestPtr;
}