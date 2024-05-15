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

#include "Guild/Model/Gs2GuildEzMember.h"

namespace Gs2::UE5::Guild::Model
{

    TSharedPtr<FEzMember> FEzMember::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMember> FEzMember::WithRoleName(
        const TOptional<FString> RoleName
    )
    {
        this->RoleNameValue = RoleName;
        return SharedThis(this);
    }

    TSharedPtr<FEzMember> FEzMember::WithJoinedAt(
        const TOptional<int64> JoinedAt
    )
    {
        this->JoinedAtValue = JoinedAt;
        return SharedThis(this);
    }
    TOptional<FString> FEzMember::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzMember::GetRoleName() const
    {
        return RoleNameValue;
    }
    TOptional<int64> FEzMember::GetJoinedAt() const
    {
        return JoinedAtValue;
    }

    FString FEzMember::GetJoinedAtString() const
    {
        if (!JoinedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), JoinedAtValue.GetValue());
    }

    Gs2::Guild::Model::FMemberPtr FEzMember::ToModel() const
    {
        return MakeShared<Gs2::Guild::Model::FMember>()
            ->WithUserId(UserIdValue)
            ->WithRoleName(RoleNameValue)
            ->WithJoinedAt(JoinedAtValue);
    }

    TSharedPtr<FEzMember> FEzMember::FromModel(const Gs2::Guild::Model::FMemberPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMember>()
            ->WithUserId(Model->GetUserId())
            ->WithRoleName(Model->GetRoleName())
            ->WithJoinedAt(Model->GetJoinedAt());
    }
}