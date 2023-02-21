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

#include "EzGs2/Public/Friend/Model/Gs2FriendEzPublicProfile.h"

namespace Gs2::UE5::Friend::Model
{

    TSharedPtr<FEzPublicProfile> FEzPublicProfile::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzPublicProfile> FEzPublicProfile::WithPublicProfile(
        const TOptional<FString> PublicProfile
    )
    {
        this->PublicProfileValue = PublicProfile;
        return SharedThis(this);
    }
    TOptional<FString> FEzPublicProfile::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzPublicProfile::GetPublicProfile() const
    {
        return PublicProfileValue;
    }

    Gs2::Friend::Model::FPublicProfilePtr FEzPublicProfile::ToModel() const
    {
        return MakeShared<Gs2::Friend::Model::FPublicProfile>()
            ->WithUserId(UserIdValue)
            ->WithPublicProfile(PublicProfileValue);
    }

    TSharedPtr<FEzPublicProfile> FEzPublicProfile::FromModel(const Gs2::Friend::Model::FPublicProfilePtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzPublicProfile>()
            ->WithUserId(Model->GetUserId())
            ->WithPublicProfile(Model->GetPublicProfile());
    }
}