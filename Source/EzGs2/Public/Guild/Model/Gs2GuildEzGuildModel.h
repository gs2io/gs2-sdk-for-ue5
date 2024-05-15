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
#include "Guild/Model/GuildModel.h"
#include "Gs2GuildEzRoleModel.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzGuildModel final : public TSharedFromThis<FEzGuildModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> DefaultMaximumMemberCountValue;
        TOptional<int32> MaximumMemberCountValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> RolesValue;
        TOptional<int32> RejoinCoolTimeMinutesValue;

	public:
        TSharedPtr<FEzGuildModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzGuildModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzGuildModel> WithDefaultMaximumMemberCount(const TOptional<int32> DefaultMaximumMemberCount);
        TSharedPtr<FEzGuildModel> WithMaximumMemberCount(const TOptional<int32> MaximumMemberCount);
        TSharedPtr<FEzGuildModel> WithRoles(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> Roles);
        TSharedPtr<FEzGuildModel> WithRejoinCoolTimeMinutes(const TOptional<int32> RejoinCoolTimeMinutes);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int32> GetDefaultMaximumMemberCount() const;
        FString GetDefaultMaximumMemberCountString() const;

        TOptional<int32> GetMaximumMemberCount() const;
        FString GetMaximumMemberCountString() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Guild::Model::FEzRoleModel>>> GetRoles() const;

        TOptional<int32> GetRejoinCoolTimeMinutes() const;
        FString GetRejoinCoolTimeMinutesString() const;

        Gs2::Guild::Model::FGuildModelPtr ToModel() const;
        static TSharedPtr<FEzGuildModel> FromModel(Gs2::Guild::Model::FGuildModelPtr Model);
    };
    typedef TSharedPtr<FEzGuildModel> FEzGuildModelPtr;
}