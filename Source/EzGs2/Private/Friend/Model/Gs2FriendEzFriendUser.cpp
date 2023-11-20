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

#include "Friend/Model/Gs2FriendEzFriendUser.h"

namespace Gs2::UE5::Friend::Model
{

    TSharedPtr<FEzFriendUser> FEzFriendUser::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzFriendUser> FEzFriendUser::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }

    TSharedPtr<FEzFriendUser> FEzFriendUser::WithFriendProfile(
        const TOptional<FString> FriendProfile
    )
    {
        this->FriendProfileValue = FriendProfile;
        return SharedThis(this);
    }
    TOptional<FString> FEzFriendUser::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzFriendUser::GetPublicProfile() const
    {
        return PublicProfileValue;
    }
    TOptional<FString> FEzFriendUser::GetFriendProfile() const
    {
        return FriendProfileValue;
    }

    Gs2::Friend::Model::FFriendUserPtr FEzFriendUser::ToModel() const
    {
        return MakeShared<Gs2::Friend::Model::FFriendUser>()
            ->WithUserId(UserIdValue)
            ->WithPublicProfile(PublicProfileValue)
            ->WithFriendProfile(FriendProfileValue);
    }

    TSharedPtr<FEzFriendUser> FEzFriendUser::FromModel(const Gs2::Friend::Model::FFriendUserPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzFriendUser>()
            ->WithUserId(Model->GetUserId())
            ->WithPublicProfile(Model->GetPublicProfile())
            ->WithFriendProfile(Model->GetFriendProfile());
    }
}