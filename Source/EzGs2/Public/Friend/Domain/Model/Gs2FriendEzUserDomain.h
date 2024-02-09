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
#include "Friend/Domain/Model/User.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzProfileDomain.h"
#include "Gs2FriendEzPublicProfileDomain.h"
#include "Gs2FriendEzBlackListDomain.h"
#include "Gs2FriendEzFollowDomain.h"
#include "Gs2FriendEzFriendDomain.h"
#include "Gs2FriendEzUserDomain.h"
#include "Gs2FriendEzUserDomain.h"
#include "Gs2FriendEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzUserDomain final :
        public TSharedFromThis<FEzUserDomain>
    {
        Gs2::Friend::Domain::Model::FUserDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserDomain(
            Gs2::Friend::Domain::Model::FUserDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        Gs2::UE5::Friend::Domain::Model::FEzProfileDomainPtr Profile(
        ) const;

        Gs2::UE5::Friend::Domain::Model::FEzPublicProfileDomainPtr PublicProfile(
        ) const;

        Gs2::UE5::Friend::Domain::Model::FEzBlackListDomainPtr BlackList(
        ) const;

        Gs2::UE5::Friend::Domain::Model::FEzFollowDomainPtr Follow(
            const bool WithProfile
        ) const;

        Gs2::UE5::Friend::Domain::Model::FEzFriendDomainPtr Friend(
            const bool WithProfile
        ) const;

    };
    typedef TSharedPtr<FEzUserDomain> FEzUserDomainPtr;
}
