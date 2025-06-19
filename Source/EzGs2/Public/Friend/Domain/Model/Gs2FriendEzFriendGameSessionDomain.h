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
#include "Friend/Domain/Model/FriendAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzFriendUserGameSessionDomain.h"
#include "Gs2FriendEzFriendGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeFriendsIterator.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzFriendGameSessionDomain final :
        public TSharedFromThis<FEzFriendGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FFriendAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<bool> WithProfile() const;

        FEzFriendGameSessionDomain(
            Gs2::Friend::Domain::Model::FFriendAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FDeleteFriendTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomain>,
            public TSharedFromThis<FDeleteFriendTask>
        {
            TSharedPtr<FEzFriendGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FDeleteFriendTask(
                TSharedPtr<FEzFriendGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteFriendTask;

        TSharedPtr<FAsyncTask<FDeleteFriendTask>> DeleteFriend(
            FString TargetUserId
        );

        Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomainPtr FriendUser(
            const FString TargetUserId
        ) const;

    };
    typedef TSharedPtr<FEzFriendGameSessionDomain> FEzFriendGameSessionDomainPtr;
}
