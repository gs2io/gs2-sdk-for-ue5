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

#include "Friend/Model/Gs2FriendEzFollowUser.h"

namespace Gs2::UE5::Friend::Model
{

    TSharedPtr<FEzFollowUser> FEzFollowUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzFollowUser> FEzFollowUser::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }

    TSharedPtr<FEzFollowUser> FEzFollowUser::WithFollowerProfile(
        const TOptional<FString> FollowerProfile
    )
    {
        this->FollowerProfileValue = FollowerProfile;
        return SharedThis(this);
    }
    TOptional<FString> FEzFollowUser::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzFollowUser::GetPublicProfile() const
    {
        return PublicProfileValue;
    }
    TOptional<FString> FEzFollowUser::GetFollowerProfile() const
    {
        return FollowerProfileValue;
    }

    Gs2::Friend::Model::FFollowUserPtr FEzFollowUser::ToModel() const
    {
        return MakeShared<Gs2::Friend::Model::FFollowUser>()
            ->WithUserId(UserIdValue)
            ->WithPublicProfile(PublicProfileValue)
            ->WithFollowerProfile(FollowerProfileValue);
    }

    TSharedPtr<FEzFollowUser> FEzFollowUser::FromModel(const Gs2::Friend::Model::FFollowUserPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzFollowUser>()
            ->WithUserId(Model->GetUserId())
            ->WithPublicProfile(Model->GetPublicProfile())
            ->WithFollowerProfile(Model->GetFollowerProfile());
    }
}