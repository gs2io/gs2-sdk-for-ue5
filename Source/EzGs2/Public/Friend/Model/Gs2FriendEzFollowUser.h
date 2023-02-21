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
#include "Friend/Model/FollowUser.h"

namespace Gs2::UE5::Friend::Model
{
	class EZGS2_API FEzFollowUser final : public TSharedFromThis<FEzFollowUser>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FollowerProfileValue;

	public:
        TSharedPtr<FEzFollowUser> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzFollowUser> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FEzFollowUser> WithFollowerProfile(const TOptional<FString> FollowerProfile);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetPublicProfile() const;

        TOptional<FString> GetFollowerProfile() const;

        Gs2::Friend::Model::FFollowUserPtr ToModel() const;
        static TSharedPtr<FEzFollowUser> FromModel(Gs2::Friend::Model::FFollowUserPtr Model);
    };
    typedef TSharedPtr<FEzFollowUser> FEzFollowUserPtr;
}