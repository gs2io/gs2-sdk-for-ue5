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
    class FUpdateGuildModelMasterRequest;

    class GS2GUILD_API FUpdateGuildModelMasterRequest final : public TSharedFromThis<FUpdateGuildModelMasterRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> GuildModelNameValue;
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
        
        FUpdateGuildModelMasterRequest();
        FUpdateGuildModelMasterRequest(
            const FUpdateGuildModelMasterRequest& From
        );
        ~FUpdateGuildModelMasterRequest() = default;

        TSharedPtr<FUpdateGuildModelMasterRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithDefaultMaximumMemberCount(const TOptional<int32> DefaultMaximumMemberCount);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithMaximumMemberCount(const TOptional<int32> MaximumMemberCount);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithInactivityPeriodDays(const TOptional<int32> InactivityPeriodDays);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithRoles(const TSharedPtr<TArray<TSharedPtr<Model::FRoleModel>>> Roles);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithGuildMasterRole(const TOptional<FString> GuildMasterRole);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithGuildMemberDefaultRole(const TOptional<FString> GuildMemberDefaultRole);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithRejoinCoolTimeMinutes(const TOptional<int32> RejoinCoolTimeMinutes);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithMaxConcurrentJoinGuilds(const TOptional<int32> MaxConcurrentJoinGuilds);
        TSharedPtr<FUpdateGuildModelMasterRequest> WithMaxConcurrentGuildMasterCount(const TOptional<int32> MaxConcurrentGuildMasterCount);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetGuildModelName() const;
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

        static TSharedPtr<FUpdateGuildModelMasterRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FUpdateGuildModelMasterRequest> FUpdateGuildModelMasterRequestPtr;
}