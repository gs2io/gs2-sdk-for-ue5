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
    class FFriendRequestAccessTokenDomain;

    class GS2FRIEND_API FSendFriendRequestAccessTokenDomain:
        public TSharedFromThis<FSendFriendRequestAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> TargetUserId;
    private:

        FString ParentKey;

    public:

        FSendFriendRequestAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> TargetUserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSendFriendRequestAccessTokenDomain(
            const FSendFriendRequestAccessTokenDomain& From
        );

        class GS2FRIEND_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FFriendRequest>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSendFriendRequestAccessTokenDomain> Self;
            const Request::FGetSendRequestRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSendFriendRequestAccessTokenDomain> Self,
                const Request::FGetSendRequestRequestPtr Request
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
            Request::FGetSendRequestRequestPtr Request
        );

        class GS2FRIEND_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FSendFriendRequestAccessTokenDomain> Self;
            const Request::FDeleteRequestRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FSendFriendRequestAccessTokenDomain> Self,
                const Request::FDeleteRequestRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRequestRequestPtr Request
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
            const TSharedPtr<FSendFriendRequestAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSendFriendRequestAccessTokenDomain> Self
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

    };

    typedef TSharedPtr<FSendFriendRequestAccessTokenDomain> FSendFriendRequestAccessTokenDomainPtr;
}
