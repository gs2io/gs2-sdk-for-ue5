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

    class GS2FRIEND_API FFriendAccessTokenDomain:
        public TSharedFromThis<FFriendAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Friend::Domain::FGs2FriendDomainPtr Service;
        const Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<bool> WithProfile;
    private:

        FString ParentKey;

    public:

        FFriendAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Friend::Domain::FGs2FriendDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<bool> WithProfile
            // ReSharper disable once CppMemberInitializersOrder
        );

        FFriendAccessTokenDomain(
            const FFriendAccessTokenDomain& From
        );

        class GS2FRIEND_API FAddFriendTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain>,
            public TSharedFromThis<FAddFriendTask>
        {
            const TSharedPtr<FFriendAccessTokenDomain> Self;
            const Request::FAddFriendRequestPtr Request;
        public:
            explicit FAddFriendTask(
                const TSharedPtr<FFriendAccessTokenDomain>& Self,
                const Request::FAddFriendRequestPtr Request
            );

            FAddFriendTask(
                const FAddFriendTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain>> Result
            ) override;
        };
        friend FAddFriendTask;

        TSharedPtr<FAsyncTask<FAddFriendTask>> AddFriend(
            Request::FAddFriendRequestPtr Request
        );

        class GS2FRIEND_API FDeleteFriendTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain>,
            public TSharedFromThis<FDeleteFriendTask>
        {
            const TSharedPtr<FFriendAccessTokenDomain> Self;
            const Request::FDeleteFriendRequestPtr Request;
        public:
            explicit FDeleteFriendTask(
                const TSharedPtr<FFriendAccessTokenDomain>& Self,
                const Request::FDeleteFriendRequestPtr Request
            );

            FDeleteFriendTask(
                const FDeleteFriendTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteFriendTask;

        TSharedPtr<FAsyncTask<FDeleteFriendTask>> DeleteFriend(
            Request::FDeleteFriendRequestPtr Request
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomain> FriendUser(
            const FString TargetUserId
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> WithProfile,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> WithProfile
        );

        class GS2FRIEND_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FFriend>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FFriendAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FFriendAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriend>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Friend::Model::FFriendPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FFriendAccessTokenDomain> FFriendAccessTokenDomainPtr;
}
