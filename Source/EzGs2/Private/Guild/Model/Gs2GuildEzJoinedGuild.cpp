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

#include "Guild/Model/Gs2GuildEzJoinedGuild.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzJoinedGuild> FEzJoinedGuild::WithGuildModelName(
        const TOptional<FString> GuildModelName
    )
    {
        this->GuildModelNameValue = GuildModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzJoinedGuild> FEzJoinedGuild::WithGuildName(
        const TOptional<FString> GuildName
    )
    {
        this->GuildNameValue = GuildName;
        return SharedThis(this);
    }

    TSharedPtr<FEzJoinedGuild> FEzJoinedGuild::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzJoinedGuild> FEzJoinedGuild::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzJoinedGuild::GetGuildModelName() const
    {
        return GuildModelNameValue;
    }
    TOptional<FString> FEzJoinedGuild::GetGuildName() const
    {
        return GuildNameValue;
    }
    TOptional<FString> FEzJoinedGuild::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<int64> FEzJoinedGuild::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FEzJoinedGuild::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    Gs2::Guild::Model::FJoinedGuildPtr FEzJoinedGuild::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FJoinedGuild>()
            ->WithGuildModelName(GuildModelNameValue)
            ->WithGuildName(GuildNameValue)
            ->WithUserId(UserIdValue)
            ->WithCreatedAt(CreatedAtValue);
    }

    TSharedPtr<FEzJoinedGuild> FEzJoinedGuild::FromModel(const Gs2::Guild::Model::FJoinedGuildPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzJoinedGuild>()
            ->WithGuildModelName(Model->GetGuildModelName())
            ->WithGuildName(Model->GetGuildName())
            ->WithUserId(Model->GetUserId())
            ->WithCreatedAt(Model->GetCreatedAt());
    }
}