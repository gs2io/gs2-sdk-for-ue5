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
    class FFriendRequestDomain;

    class GS2FRIEND_API FSendFriendRequestDomain:
        public TSharedFromThis<FSendFriendRequestDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Friend::Domain::FGs2FriendDomainPtr Service;
        const Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> TargetUserId;
    private:

        FString ParentKey;

    public:

        FSendFriendRequestDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Friend::Domain::FGs2FriendDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> TargetUserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSendFriendRequestDomain(
            const FSendFriendRequestDomain& From
        );

        class GS2FRIEND_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FFriendRequest>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSendFriendRequestDomain> Self;
            const Request::FGetSendRequestByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSendFriendRequestDomain>& Self,
                const Request::FGetSendRequestByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendRequest>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSendRequestByUserIdRequestPtr Request
        );

        class GS2FRIEND_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FSendFriendRequestDomain> Self;
            const Request::FDeleteRequestByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FSendFriendRequestDomain>& Self,
                const Request::FDeleteRequestByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRequestByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> TargetUserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> TargetUserId
        );

        class GS2FRIEND_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FFriendRequest>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSendFriendRequestDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSendFriendRequestDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FFriendRequest>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Friend::Model::FFriendRequestPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSendFriendRequestDomain> FSendFriendRequestDomainPtr;
}
