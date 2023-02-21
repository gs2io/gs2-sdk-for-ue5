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
#include "Friend/Model/FriendUser.h"

namespace Gs2::UE5::Friend::Model
{
	class EZGS2_API FEzFriendUser final : public TSharedFromThis<FEzFriendUser>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> PublicProfileValue;
        TOptional<FString> FriendProfileValue;

	public:
        TSharedPtr<FEzFriendUser> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzFriendUser> WithPublicProfile(const TOptional<FString> PublicProfile);
        TSharedPtr<FEzFriendUser> WithFriendProfile(const TOptional<FString> FriendProfile);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetPublicProfile() const;

        TOptional<FString> GetFriendProfile() const;

        Gs2::Friend::Model::FFriendUserPtr ToModel() const;
        static TSharedPtr<FEzFriendUser> FromModel(Gs2::Friend::Model::FFriendUserPtr Model);
    };
    typedef TSharedPtr<FEzFriendUser> FEzFriendUserPtr;
}