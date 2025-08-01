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
#include "Friend/Domain/Model/FollowAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzFollowUserGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeFollowsIterator.h"
#include "Gs2FriendEzFollowGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzFollowGameSessionDomain final :
        public TSharedFromThis<FEzFollowGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FFollowAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<bool> WithProfile() const;

        FEzFollowGameSessionDomain(
            Gs2::Friend::Domain::Model::FFollowAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FFollowTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>,
            public TSharedFromThis<FFollowTask>
        {
            TSharedPtr<FEzFollowGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FFollowTask(
                TSharedPtr<FEzFollowGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>> Result
            ) override;
        };
        friend FFollowTask;

        TSharedPtr<FAsyncTask<FFollowTask>> Follow(
            FString TargetUserId
        );

        Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFollowsIteratorPtr Follows(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeFollows(TFunction<void()> Callback);

        void UnsubscribeFollows(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomainPtr FollowUser(
            const FString TargetUserId
        ) const;

    };
    typedef TSharedPtr<FEzFollowGameSessionDomain> FEzFollowGameSessionDomainPtr;
}
