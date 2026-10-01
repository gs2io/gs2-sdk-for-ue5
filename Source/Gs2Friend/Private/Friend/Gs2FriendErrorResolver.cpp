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

#include "Friend/Gs2FriendErrorResolver.h"

#include "Core/Model/Gs2ErrorResolver.h"
#include "Friend/Error/AlreadyInBlackListError.h"
#include "Friend/Error/AlreadyFollowingError.h"
#include "Friend/Error/AlreadyFriendError.h"
#include "Friend/Error/SendRequestToSelfError.h"
#include "Friend/Error/SendRequestCapacityFullError.h"
#include "Friend/Error/DuplicateFriendRequestError.h"

namespace Gs2::Friend
{
    namespace
    {
        [[maybe_unused]] const bool GRegistered = Core::Model::FGs2ErrorResolver::Register(
            TEXT("Gs2Friend"),
            &FGs2FriendErrorResolver::Resolve
        );
    }

    Core::Model::FGs2ErrorPtr FGs2FriendErrorResolver::Resolve(const FString& Method, Core::Model::FGs2ErrorPtr Source)
    {
        if (!Source.IsValid())
        {
            return Source;
        }
        Core::Model::FGs2ErrorPtr Resolved;
        if (Method == TEXT("RegisterBlackList") || Method == TEXT("RegisterBlackListByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("friend.blackList.targetUserId.duplicate")))
            {
                Resolved = MakeShared<Gs2::Friend::Error::FAlreadyInBlackListError>(Source);
            }
        }
        else if (Method == TEXT("Follow") || Method == TEXT("FollowByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("friend.followUser.targetUserId.duplicate")))
            {
                Resolved = MakeShared<Gs2::Friend::Error::FAlreadyFollowingError>(Source);
            }
        }
        else if (Method == TEXT("AddFriend") || Method == TEXT("AddFriendByUserId") || Method == TEXT("AcceptRequest") || Method == TEXT("AcceptRequestByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("friend.friend.targetUserId.duplicate")))
            {
                Resolved = MakeShared<Gs2::Friend::Error::FAlreadyFriendError>(Source);
            }
        }
        else if (Method == TEXT("SendRequest") || Method == TEXT("SendRequestByUserId"))
        {
            if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("friend.sendFriendRequest.targetUserId.self")))
            {
                Resolved = MakeShared<Gs2::Friend::Error::FSendRequestToSelfError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("friend.sendFriendRequest.capacity.full")))
            {
                Resolved = MakeShared<Gs2::Friend::Error::FSendRequestCapacityFullError>(Source);
            }
            else if (Core::Model::FGs2ErrorResolver::HasCode(Source, TEXT("friend.sendFriendRequest.targetUserId.duplicate")))
            {
                Resolved = MakeShared<Gs2::Friend::Error::FDuplicateFriendRequestError>(Source);
            }
        }
        if (!Resolved.IsValid())
        {
            return Source;
        }
        Resolved->SetMetadata(Source->GetMetadata());
        return Resolved;
    }
}