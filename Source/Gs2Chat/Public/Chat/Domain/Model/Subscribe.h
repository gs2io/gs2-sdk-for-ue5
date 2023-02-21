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
#include "Chat/Gs2Chat.h"
#include "Chat/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Chat/Domain/Iterator/DescribeRoomsIterator.h"
#include "Chat/Domain/Iterator/DescribeMessagesIterator.h"
#include "Chat/Domain/Iterator/DescribeMessagesByUserIdIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesByUserIdIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesByRoomNameIterator.h"

namespace Gs2::Chat::Domain::Model
{
    class FNamespaceDomain;
    class FRoomDomain;
    class FRoomAccessTokenDomain;
    class FMessageDomain;
    class FMessageAccessTokenDomain;
    class FSubscribeDomain;
    class FSubscribeAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2CHAT_API FSubscribeDomain:
        public TSharedFromThis<FSubscribeDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Chat::FGs2ChatRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> RoomName;
    private:

        FString ParentKey;

    public:

        FSubscribeDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> RoomName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSubscribeDomain(
            const FSubscribeDomain& From
        );

        class GS2CHAT_API FSubscribeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FSubscribeDomain>,
            public TSharedFromThis<FSubscribeTask>
        {
            const TSharedPtr<FSubscribeDomain> Self;
            const Request::FSubscribeByUserIdRequestPtr Request;
        public:
            explicit FSubscribeTask(
                const TSharedPtr<FSubscribeDomain> Self,
                const Request::FSubscribeByUserIdRequestPtr Request
            );

            FSubscribeTask(
                const FSubscribeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain>> Result
            ) override;
        };
        friend FSubscribeTask;

        TSharedPtr<FAsyncTask<FSubscribeTask>> Subscribe(
            Request::FSubscribeByUserIdRequestPtr Request
        );

        class GS2CHAT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FSubscribe>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSubscribeDomain> Self;
            const Request::FGetSubscribeByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSubscribeDomain> Self,
                const Request::FGetSubscribeByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Model::FSubscribe>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetSubscribeByUserIdRequestPtr Request
        );

        class GS2CHAT_API FUpdateNotificationTypeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FSubscribeDomain>,
            public TSharedFromThis<FUpdateNotificationTypeTask>
        {
            const TSharedPtr<FSubscribeDomain> Self;
            const Request::FUpdateNotificationTypeByUserIdRequestPtr Request;
        public:
            explicit FUpdateNotificationTypeTask(
                const TSharedPtr<FSubscribeDomain> Self,
                const Request::FUpdateNotificationTypeByUserIdRequestPtr Request
            );

            FUpdateNotificationTypeTask(
                const FUpdateNotificationTypeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain>> Result
            ) override;
        };
        friend FUpdateNotificationTypeTask;

        TSharedPtr<FAsyncTask<FUpdateNotificationTypeTask>> UpdateNotificationType(
            Request::FUpdateNotificationTypeByUserIdRequestPtr Request
        );

        class GS2CHAT_API FUnsubscribeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FSubscribeDomain>,
            public TSharedFromThis<FUnsubscribeTask>
        {
            const TSharedPtr<FSubscribeDomain> Self;
            const Request::FUnsubscribeByUserIdRequestPtr Request;
        public:
            explicit FUnsubscribeTask(
                const TSharedPtr<FSubscribeDomain> Self,
                const Request::FUnsubscribeByUserIdRequestPtr Request
            );

            FUnsubscribeTask(
                const FUnsubscribeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain>> Result
            ) override;
        };
        friend FUnsubscribeTask;

        TSharedPtr<FAsyncTask<FUnsubscribeTask>> Unsubscribe(
            Request::FUnsubscribeByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> RoomName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> RoomName
        );

        class GS2CHAT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FSubscribe>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FSubscribeDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSubscribeDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Model::FSubscribe>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FSubscribeDomain> FSubscribeDomainPtr;
}
