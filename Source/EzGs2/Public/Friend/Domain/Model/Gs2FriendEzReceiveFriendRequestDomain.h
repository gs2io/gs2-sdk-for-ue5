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
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzReceiveFriendRequestDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzReceiveFriendRequestDomain final :
        public TSharedFromThis<FEzReceiveFriendRequestDomain>
    {
        Gs2::Friend::Domain::Model::FReceiveFriendRequestDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> FromUserId() const;

        FEzReceiveFriendRequestDomain(
            Gs2::Friend::Domain::Model::FReceiveFriendRequestDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

    };
    typedef TSharedPtr<FEzReceiveFriendRequestDomain> FEzReceiveFriendRequestDomainPtr;
}
