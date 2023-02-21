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
#include "Friend/Model/Profile.h"

namespace Gs2::UE5::Friend::Model
{
	class EZGS2_API FEzProfile final : public TSharedFromThis<FEzProfile>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FollowerProfileValue;
        TOptional<FString> FriendProfileValue;

	public:
        TSharedPtr<FEzProfile> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzProfile> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FEzProfile> WithFollowerProfile(const TOptional<FString> FollowerProfile);
        TSharedPtr<FEzProfile> WithFriendProfile(const TOptional<FString> FriendProfile);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetPublicProfile() const;

        TOptional<FString> GetFollowerProfile() const;

        TOptional<FString> GetFriendProfile() const;

        Gs2::Friend::Model::FProfilePtr ToModel() const;
        static TSharedPtr<FEzProfile> FromModel(Gs2::Friend::Model::FProfilePtr Model);
    };
    typedef TSharedPtr<FEzProfile> FEzProfilePtr;
}