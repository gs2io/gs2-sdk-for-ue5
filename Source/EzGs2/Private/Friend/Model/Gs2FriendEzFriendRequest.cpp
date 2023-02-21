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

#include "EzGs2/Public/Friend/Model/Gs2FriendEzFriendRequest.h"

namespace Gs2::UE5::Friend::Model
{

    TSharedPtr<FEzFriendRequest> FEzFriendRequest::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FEzFriendRequest> FEzFriendRequest::WithTargetUserId(
        const TOptional<FString> TargetUserId
    )
    {
        this->TargetUserIdValue = TargetUserId;
        return SharedThis(this);
    }
    TOptional<FString> FEzFriendRequest::GetUserId() const
    {
        return UserIdValue;
    }
    TOptional<FString> FEzFriendRequest::GetTargetUserId() const
    {
        return TargetUserIdValue;
    }

    Gs2::Friend::Model::FFriendRequestPtr FEzFriendRequest::ToModel() const
    {
        return MakeShared<Gs2::Friend::Model::FFriendRequest>()
            ->WithUserId(UserIdValue)
            ->WithTargetUserId(TargetUserIdValue);
    }

    TSharedPtr<FEzFriendRequest> FEzFriendRequest::FromModel(const Gs2::Friend::Model::FFriendRequestPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzFriendRequest>()
            ->WithUserId(Model->GetUserId())
            ->WithTargetUserId(Model->GetTargetUserId());
    }
}