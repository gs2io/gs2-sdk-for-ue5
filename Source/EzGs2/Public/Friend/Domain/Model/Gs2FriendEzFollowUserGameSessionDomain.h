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
#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzFollowUserGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeFollowsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzFollowUserGameSessionDomain final :
        public TSharedFromThis<FEzFollowUserGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> TargetUserId() const;

        FEzFollowUserGameSessionDomain(
            Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FFollowTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>,
            public TSharedFromThis<FFollowTask>
        {
            TSharedPtr<FEzFollowUserGameSessionDomain> Self;

        public:
            explicit FFollowTask(
                TSharedPtr<FEzFollowUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>> Result
            ) override;
        };
        friend FFollowTask;

        TSharedPtr<FAsyncTask<FFollowTask>> Follow(
        );

        class FUnfollowTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>,
            public TSharedFromThis<FUnfollowTask>
        {
            TSharedPtr<FEzFollowUserGameSessionDomain> Self;

        public:
            explicit FUnfollowTask(
                TSharedPtr<FEzFollowUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>> Result
            ) override;
        };
        friend FUnfollowTask;

        TSharedPtr<FAsyncTask<FUnfollowTask>> Unfollow(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzFollowUser>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzFollowUserGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzFollowUserGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Friend::Model::FEzFollowUserPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFollowUserPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzFollowUserGameSessionDomain> FEzFollowUserGameSessionDomainPtr;
}
