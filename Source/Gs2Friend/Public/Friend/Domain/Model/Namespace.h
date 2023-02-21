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

    class GS2FRIEND_API FNamespaceDomain:
        public TSharedFromThis<FNamespaceDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
        TOptional<FString> Status;
        TOptional<FString> GetStatus() const
        {
            return Status;
        }
        TOptional<FString> NamespaceName;
    private:

        FString ParentKey;

    public:

        FNamespaceDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FNamespaceDomain(
            const FNamespaceDomain& From
        );

        class GS2FRIEND_API FGetStatusTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FGetStatusTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceStatusRequestPtr Request;
        public:
            explicit FGetStatusTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceStatusRequestPtr Request
            );

            FGetStatusTask(
                const FGetStatusTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FGetStatusTask;

        TSharedPtr<FAsyncTask<FGetStatusTask>> GetStatus(
            Request::FGetNamespaceStatusRequestPtr Request
        );

        class GS2FRIEND_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FNamespace>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FGetNamespaceRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FGetNamespaceRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FNamespace>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetNamespaceRequestPtr Request
        );

        class GS2FRIEND_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FUpdateNamespaceRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FUpdateNamespaceRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateNamespaceRequestPtr Request
        );

        class GS2FRIEND_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
            const Request::FDeleteNamespaceRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FNamespaceDomain> Self,
                const Request::FDeleteNamespaceRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteNamespaceRequestPtr Request
        );

        TSharedPtr<Gs2::Friend::Domain::Model::FUserDomain> User(
            const FString UserId
        ) const;

        TSharedPtr<Gs2::Friend::Domain::Model::FUserAccessTokenDomain> AccessToken(
            Gs2::Auth::Model::FAccessTokenPtr AccessToken
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> NamespaceName
        );

        class GS2FRIEND_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FNamespace>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FNamespaceDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FNamespaceDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FNamespace>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FNamespaceDomain> FNamespaceDomainPtr;
}
