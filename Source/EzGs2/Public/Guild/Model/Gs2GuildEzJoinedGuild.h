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
#include "Guild/Model/JoinedGuild.h"

namespace Gs2::UE5::Guild::Model
{
	class EZGS2_API FEzJoinedGuild final : public TSharedFromThis<FEzJoinedGuild>
	{
        TOptional<FString> GuildModelNameValue;
        TOptional<FString> GuildNameValue;
        TOptional<FString> UserIdValue;
        TOptional<int64> CreatedAtValue;

	public:
        TSharedPtr<FEzJoinedGuild> WithGuildModelName(const TOptional<FString> GuildModelName);
        TSharedPtr<FEzJoinedGuild> WithGuildName(const TOptional<FString> GuildName);
        TSharedPtr<FEzJoinedGuild> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzJoinedGuild> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetGuildModelName() const;

        TOptional<FString> GetGuildName() const;

        TOptional<FString> GetUserId() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        Gs2::Guild::Model::FJoinedGuildPtr ToModel() const;
        static TSharedPtr<FEzJoinedGuild> FromModel(Gs2::Guild::Model::FJoinedGuildPtr Model);
    };
    typedef TSharedPtr<FEzJoinedGuild> FEzJoinedGuildPtr;
}