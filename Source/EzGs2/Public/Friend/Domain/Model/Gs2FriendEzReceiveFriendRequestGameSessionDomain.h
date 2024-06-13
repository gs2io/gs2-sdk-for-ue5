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
#include "Friend/Domain/Model/ReceiveFriendRequestAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzReceiveFriendRequestGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeReceiveRequestsIterator.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzReceiveFriendRequestGameSessionDomain final :
        public TSharedFromThis<FEzReceiveFriendRequestGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> FromUserId() const;

        FEzReceiveFriendRequestGameSessionDomain(
            Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FAcceptTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>,
            public TSharedFromThis<FAcceptTask>
        {
            TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self;

        public:
            explicit FAcceptTask(
                TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>> Result
            ) override;
        };
        friend FAcceptTask;

        TSharedPtr<FAsyncTask<FAcceptTask>> Accept(
        );

        class FRejectTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>,
            public TSharedFromThis<FRejectTask>
        {
            TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self;

        public:
            explicit FRejectTask(
                TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>> Result
            ) override;
        };
        friend FRejectTask;

        TSharedPtr<FAsyncTask<FRejectTask>> Reject(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzFriendRequest>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendRequestPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFriendRequestPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> FEzReceiveFriendRequestGameSessionDomainPtr;
}
