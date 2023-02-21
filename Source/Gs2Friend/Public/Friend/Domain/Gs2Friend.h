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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Friend/Gs2Friend.h"

// Model
#include "Friend/Domain/Model/Namespace.h"
#include "Friend/Domain/Model/User.h"
#include "Friend/Domain/Model/UserAccessToken.h"
#include "Friend/Domain/Model/Profile.h"
#include "Friend/Domain/Model/ProfileAccessToken.h"
#include "Friend/Domain/Model/Friend.h"
#include "Friend/Domain/Model/FriendAccessToken.h"
#include "Friend/Domain/Model/BlackList.h"
#include "Friend/Domain/Model/BlackListAccessToken.h"
#include "Friend/Domain/Model/FollowUser.h"
#include "Friend/Domain/Model/FollowUserAccessToken.h"
#include "Friend/Domain/Model/FriendUser.h"
#include "Friend/Domain/Model/FriendUserAccessToken.h"
#include "Friend/Domain/Model/SendFriendRequest.h"
#include "Friend/Domain/Model/SendFriendRequestAccessToken.h"
#include "Friend/Domain/Model/ReceiveFriendRequest.h"
#include "Friend/Domain/Model/ReceiveFriendRequestAccessToken.h"
#include "Friend/Domain/Model/PublicProfile.h"
#include "Friend/Domain/Model/PublicProfileAccessToken.h"
#include "Friend/Domain/Model/FriendRequest.h"
#include "Friend/Domain/Model/FriendRequestAccessToken.h"

// Iterator
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

// Notification
#include "Friend/Model/FollowNotification.h"
#include "Friend/Model/AcceptRequestNotification.h"
#include "Friend/Model/ReceiveRequestNotification.h"

namespace Gs2::Friend::Domain
{
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FFollowNotificationEvent, Gs2::Friend::Model::FFollowNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FAcceptRequestNotificationEvent, Gs2::Friend::Model::FAcceptRequestNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2FriendDomain, FReceiveRequestNotificationEvent, Gs2::Friend::Model::FReceiveRequestNotificationPtr);

    class GS2FRIEND_API FGs2FriendDomain:
        public TSharedFromThis<FGs2FriendDomain>
    {
        FFollowNotificationEvent FollowNotificationEvent;
        FAcceptRequestNotificationEvent AcceptRequestNotificationEvent;
        FReceiveRequestNotificationEvent ReceiveRequestNotificationEvent;
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Friend::FGs2FriendRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2FriendDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2FriendDomain(
            const FGs2FriendDomain& From
        );

        class GS2FRIEND_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2FriendDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2FriendDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Friend::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Friend::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );
        FFollowNotificationEvent& OnFollowNotification();
        FAcceptRequestNotificationEvent& OnAcceptRequestNotification();
        FReceiveRequestNotificationEvent& OnReceiveRequestNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2FriendDomain> FGs2FriendDomainPtr;
}
