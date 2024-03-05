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
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Model/Gs2FriendEzProfile.h"
#include "Friend/Model/Gs2FriendEzBlackList.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"
#include "Friend/Model/Gs2FriendEzFriendUser.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"
#include "Friend/Model/Gs2FriendEzPublicProfile.h"
#include "Gs2FriendEzProfileGameSessionDomain.h"
#include "Gs2FriendEzBlackListGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeBlackListIterator.h"
#include "Gs2FriendEzFollowGameSessionDomain.h"
#include "Gs2FriendEzFriendGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeFriendsIterator.h"
#include "Gs2FriendEzSendFriendRequestGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeSendRequestsIterator.h"
#include "Gs2FriendEzReceiveFriendRequestGameSessionDomain.h"
#include "Friend/Domain/Iterator/Gs2FriendEzDescribeReceiveRequestsIterator.h"
#include "Gs2FriendEzUserGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Friend::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Friend::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class FSendRequestTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>,
            public TSharedFromThis<FSendRequestTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            FString TargetUserId;

        public:
            explicit FSendRequestTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                FString TargetUserId
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>> Result
            ) override;
        };
        friend FSendRequestTask;

        TSharedPtr<FAsyncTask<FSendRequestTask>> SendRequest(
            FString TargetUserId
        );

        Gs2::UE5::Friend::Domain::Model::FEzProfileGameSessionDomainPtr Profile(
        ) const;

        Gs2::UE5::Friend::Domain::Iterator::FEzDescribeBlackListIteratorPtr BlackListUsers(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeBlackListUsers(TFunction<void()> Callback);

        void UnsubscribeBlackListUsers(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Friend::Domain::Model::FEzBlackListGameSessionDomainPtr BlackList(
        ) const;

        Gs2::UE5::Friend::Domain::Model::FEzFollowGameSessionDomainPtr Follow(
            const bool WithProfile
        ) const;

        Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFriendsIteratorPtr Friends(
            const bool WithProfile
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeFriends(TFunction<void()> Callback);

        void UnsubscribeFriends(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Friend::Domain::Model::FEzFriendGameSessionDomainPtr Friend(
            const bool WithProfile
        ) const;

        Gs2::UE5::Friend::Domain::Iterator::FEzDescribeSendRequestsIteratorPtr SendRequests(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSendRequests(TFunction<void()> Callback);

        void UnsubscribeSendRequests(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomainPtr SendFriendRequest(
            const FString TargetUserId
        ) const;

        Gs2::UE5::Friend::Domain::Iterator::FEzDescribeReceiveRequestsIteratorPtr ReceiveRequests(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveRequests(TFunction<void()> Callback);

        void UnsubscribeReceiveRequests(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomainPtr ReceiveFriendRequest(
            const FString FromUserId
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
