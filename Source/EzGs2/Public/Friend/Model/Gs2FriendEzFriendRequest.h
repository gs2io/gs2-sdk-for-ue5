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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Friend/Model/FriendRequest.h"
#include "Friend/Model/ReceiveFriendRequest.h"
#include "Friend/Model/SendFriendRequest.h"

namespace Gs2::UE5::Friend::Model
{
	class EZGS2_API FEzFriendRequest final : public TSharedFromThis<FEzFriendRequest>
	{
        TOptional<FString> UserIdValue;
        TOptional<FString> TargetUserIdValue;

	public:
        TSharedPtr<FEzFriendRequest> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FEzFriendRequest> WithTargetUserId(const TOptional<FString> TargetUserId);

        TOptional<FString> GetUserId() const;

        TOptional<FString> GetTargetUserId() const;

        Gs2::Friend::Model::FFriendRequestPtr ToModel() const;
        static TSharedPtr<FEzFriendRequest> FromModel(Gs2::Friend::Model::FFriendRequestPtr Model);
        static TSharedPtr<FEzFriendRequest> FromModel(Gs2::Friend::Model::FSendFriendRequestPtr Model);
        static TSharedPtr<FEzFriendRequest> FromModel(Gs2::Friend::Model::FReceiveFriendRequestPtr Model);
    };
    typedef TSharedPtr<FEzFriendRequest> FEzFriendRequestPtr;
}