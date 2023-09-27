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

    class GS2CHAT_API FSubscribeAccessTokenDomain:
        public TSharedFromThis<FSubscribeAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Chat::FGs2ChatRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> RoomName;
    private:

        FString ParentKey;

    public:

        FSubscribeAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> RoomName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FSubscribeAccessTokenDomain(
            const FSubscribeAccessTokenDomain& From
        );

        class GS2CHAT_API FSubscribeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>,
            public TSharedFromThis<FSubscribeTask>
        {
            const TSharedPtr<FSubscribeAccessTokenDomain> Self;
            const Request::FSubscribeRequestPtr Request;
        public:
            explicit FSubscribeTask(
                const TSharedPtr<FSubscribeAccessTokenDomain> Self,
                const Request::FSubscribeRequestPtr Request
            );

            FSubscribeTask(
                const FSubscribeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>> Result
            ) override;
        };
        friend FSubscribeTask;

        TSharedPtr<FAsyncTask<FSubscribeTask>> Subscribe(
            Request::FSubscribeRequestPtr Request
        );

        class GS2CHAT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FSubscribe>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FSubscribeAccessTokenDomain> Self;
            const Request::FGetSubscribeRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FSubscribeAccessTokenDomain> Self,
                const Request::FGetSubscribeRequestPtr Request
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
            Request::FGetSubscribeRequestPtr Request
        );

        class GS2CHAT_API FUpdateNotificationTypeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>,
            public TSharedFromThis<FUpdateNotificationTypeTask>
        {
            const TSharedPtr<FSubscribeAccessTokenDomain> Self;
            const Request::FUpdateNotificationTypeRequestPtr Request;
        public:
            explicit FUpdateNotificationTypeTask(
                const TSharedPtr<FSubscribeAccessTokenDomain> Self,
                const Request::FUpdateNotificationTypeRequestPtr Request
            );

            FUpdateNotificationTypeTask(
                const FUpdateNotificationTypeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateNotificationTypeTask;

        TSharedPtr<FAsyncTask<FUpdateNotificationTypeTask>> UpdateNotificationType(
            Request::FUpdateNotificationTypeRequestPtr Request
        );

        class GS2CHAT_API FUnsubscribeTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>,
            public TSharedFromThis<FUnsubscribeTask>
        {
            const TSharedPtr<FSubscribeAccessTokenDomain> Self;
            const Request::FUnsubscribeRequestPtr Request;
        public:
            explicit FUnsubscribeTask(
                const TSharedPtr<FSubscribeAccessTokenDomain> Self,
                const Request::FUnsubscribeRequestPtr Request
            );

            FUnsubscribeTask(
                const FUnsubscribeTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain>> Result
            ) override;
        };
        friend FUnsubscribeTask;

        TSharedPtr<FAsyncTask<FUnsubscribeTask>> Unsubscribe(
            Request::FUnsubscribeRequestPtr Request
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
            const TSharedPtr<FSubscribeAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FSubscribeAccessTokenDomain> Self
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

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Chat::Model::FSubscribePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FSubscribeAccessTokenDomain> FSubscribeAccessTokenDomainPtr;
}
