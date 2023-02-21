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
    class FFriendRequestDomain;

    class GS2FRIEND_API FBlackListDomain:
        public TSharedFromThis<FBlackListDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FBlackListDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FBlackListDomain(
            const FBlackListDomain& From
        );

        class GS2FRIEND_API FRegisterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FBlackListDomain>,
            public TSharedFromThis<FRegisterTask>
        {
            const TSharedPtr<FBlackListDomain> Self;
            const Request::FRegisterBlackListByUserIdRequestPtr Request;
        public:
            explicit FRegisterTask(
                const TSharedPtr<FBlackListDomain> Self,
                const Request::FRegisterBlackListByUserIdRequestPtr Request
            );

            FRegisterTask(
                const FRegisterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FBlackListDomain>> Result
            ) override;
        };
        friend FRegisterTask;

        TSharedPtr<FAsyncTask<FRegisterTask>> Register(
            Request::FRegisterBlackListByUserIdRequestPtr Request
        );

        class GS2FRIEND_API FUnregisterTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FBlackListDomain>,
            public TSharedFromThis<FUnregisterTask>
        {
            const TSharedPtr<FBlackListDomain> Self;
            const Request::FUnregisterBlackListByUserIdRequestPtr Request;
        public:
            explicit FUnregisterTask(
                const TSharedPtr<FBlackListDomain> Self,
                const Request::FUnregisterBlackListByUserIdRequestPtr Request
            );

            FUnregisterTask(
                const FUnregisterTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FBlackListDomain>> Result
            ) override;
        };
        friend FUnregisterTask;

        TSharedPtr<FAsyncTask<FUnregisterTask>> Unregister(
            Request::FUnregisterBlackListByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2FRIEND_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FBlackList>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FBlackListDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FBlackListDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FBlackList>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FBlackListDomain> FBlackListDomainPtr;
}
