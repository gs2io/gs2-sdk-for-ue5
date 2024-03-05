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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Friend/Gs2Friend.h"
#include "Friend/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Friend/Domain/Iterator/DescribeFriendsIterator.h"
#include "Friend/Domain/Iterator/DescribeFriendsByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeBlackListIterator.h"
#include "Friend/Domain/Iterator/DescribeBlackListByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeFollowsIterator.h"
#include "Friend/Domain/Iterator/DescribeFollowsByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeSendRequestsIterator.h"
#include "Friend/Domain/Iterator/DescribeSendRequestsByUserIdIterator.h"
#include "Friend/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Friend/Domain/Iterator/DescribeReceiveRequestsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Friend::Domain
{
    class FGs2FriendDomain;
    typedef TSharedPtr<FGs2FriendDomain> FGs2FriendDomainPtr;
}

namespace Gs2::Friend::Domain::Model
{
    class FNamespaceDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;
    class FProfileDomain;
    class FProfileAccessTokenDomain;
    class FFollowDomain;
    class FFollowAccessTokenDomain;
    class FFriendDomain;
    class FFriendAccessTokenDomain;
    class FBlackListDomain;
    class FBlackListAccessTokenDomain;
    class FFollowUserDomain;
    class FFollowUserAccessTokenDomain;
    class FFriendUserDomain;
    class FFriendUserAccessTokenDomain;
    class FSendFriendRequestDomain;
    class FSendFriendRequestAccessTokenDomain;
    class FReceiveFriendRequestDomain;
    class FReceiveFriendRequestAccessTokenDomain;
    class FPublicProfileDomain;
    class FPublicProfileAccessTokenDomain;
    class FFriendRequestAccessTokenDomain;

    class GS2FRIEND_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Friend::Domain::FGs2FriendDomainPtr Service;
        const Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Friend::Domain::FGs2FriendDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2FRIEND_API FSendRequestTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>,
            public TSharedFromThis<FSendRequestTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FSendRequestRequestPtr Request;
        public:
            explicit FSendRequestTask(
                const TSharedPtr<FUserAccessTokenDomain>& Self,
                const Request::FSendRequestRequestPtr Request
            );

            FSendRequestTask(
                const FSendRequestTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>> Result
            ) override;
        };
        friend FSendRequestTask;

        TSharedPtr<FAsyncTask<FSendRequestTask>> SendRequest(
            Request::FSendRequestRequestPtr Request
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FProfileAccessTokenDomain> Profile(
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FPublicProfileAccessTokenDomain> PublicProfile(
        );

        Gs2::Friend::Domain::Iterator::FDescribeBlackListIteratorPtr BlackListUsers(
        ) const;

        TSharedPtr<Gs2::Friend::Domain::Model::FBlackListAccessTokenDomain> BlackList(
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FFollowAccessTokenDomain> Follow(
            const bool WithProfile
        );

        Gs2::Friend::Domain::Iterator::FDescribeFriendsIteratorPtr Friends(
            const TOptional<bool> WithProfile
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeFriends(
            TFunction<void()> Callback,
            const TOptional<bool> WithProfile
        );

        void UnsubscribeFriends(
            Gs2::Core::Domain::CallbackID CallbackID,
            const TOptional<bool> WithProfile
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FFriendAccessTokenDomain> Friend(
            const bool WithProfile
        );

        Gs2::Friend::Domain::Iterator::FDescribeSendRequestsIteratorPtr SendRequests(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSendRequests(
            TFunction<void()> Callback
        );

        void UnsubscribeSendRequests(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain> SendFriendRequest(
            const FString TargetUserId
        );

        Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr ReceiveRequests(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeReceiveRequests(
            TFunction<void()> Callback
        );

        void UnsubscribeReceiveRequests(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomain> ReceiveFriendRequest(
            const FString FromUserId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
