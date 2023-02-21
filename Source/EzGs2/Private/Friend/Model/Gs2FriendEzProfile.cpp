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

#include "EzGs2/Public/Friend/Model/Gs2FriendEzProfile.h"

namespace Gs2::UE5::Friend::Model
{

    TSharedPtr<FEzProfile> FEzProfile::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzProfile> FEzProfile::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }

    TSharedPtr<FEzProfile> FEzProfile::WithFollowerProfile(
        const TOptional<FString> FollowerProfile
    )
    {
        this->FollowerProfileValue = FollowerProfile;
        return SharedThis(this);
    }

    TSharedPtr<FEzProfile> FEzProfile::WithFriendProfile(
        const TOptional<FString> FriendProfile
    )
    {
        this->FriendProfileValue = FriendProfile;
        return SharedThis(this);
    }
    TOptional<FString> FEzProfile::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzProfile::GetPublicProfile() const
    {
        return PublicProfileValue;
    }
    TOptional<FString> FEzProfile::GetFollowerProfile() const
    {
        return FollowerProfileValue;
    }
    TOptional<FString> FEzProfile::GetFriendProfile() const
    {
        return FriendProfileValue;
    }

    Gs2::Friend::Model::FProfilePtr FEzProfile::ToModel() const
    {
        return MakeShared<Gs2::Friend::Model::FProfile>()
            ->WithUserId(UserIdValue)
            ->WithPublicProfile(PublicProfileValue)
            ->WithFollowerProfile(FollowerProfileValue)
            ->WithFriendProfile(FriendProfileValue);
    }

    TSharedPtr<FEzProfile> FEzProfile::FromModel(const Gs2::Friend::Model::FProfilePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzProfile>()
            ->WithUserId(Model->GetUserId())
            ->WithPublicProfile(Model->GetPublicProfile())
            ->WithFollowerProfile(Model->GetFollowerProfile())
            ->WithFriendProfile(Model->GetFriendProfile());
    }
}