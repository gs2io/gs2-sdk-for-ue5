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
#include "Chat/Domain/Iterator/DescribeLatestMessagesIterator.h"
#include "Chat/Domain/Iterator/DescribeLatestMessagesByUserIdIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesByUserIdIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesByRoomNameIterator.h"
#include "Chat/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Chat/Domain/Iterator/DescribeCategoryModelMastersIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Chat::Domain
{
    class FGs2ChatDomain;
    typedef TSharedPtr<FGs2ChatDomain> FGs2ChatDomainPtr;
}

namespace Gs2::Chat::Domain::Model
{
    class FNamespaceDomain;
    class FRoomDomain;
    class FRoomAccessTokenDomain;
    class FMessageDomain;
    class FMessageAccessTokenDomain;
    class FSubscribeDomain;
    class FSubscribeAccessTokenDomain;
    class FCategoryModelDomain;
    class FCategoryModelMasterDomain;
    class FCurrentModelMasterDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2CHAT_API FRoomAccessTokenDomain:
        public TSharedFromThis<FRoomAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Chat::Domain::FGs2ChatDomainPtr Service;
        const Gs2::Chat::FGs2ChatRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> RoomName;
        TOptional<FString> Password;
    private:

        FString ParentKey;

    public:

        FRoomAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Chat::Domain::FGs2ChatDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> RoomName,
            const TOptional<FString> Password
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRoomAccessTokenDomain(
            const FRoomAccessTokenDomain& From
        );

        class GS2CHAT_API FUpdateTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>,
            public TSharedFromThis<FUpdateTask>
        {
            const TSharedPtr<FRoomAccessTokenDomain> Self;
            const Request::FUpdateRoomRequestPtr Request;
        public:
            explicit FUpdateTask(
                const TSharedPtr<FRoomAccessTokenDomain>& Self,
                const Request::FUpdateRoomRequestPtr Request
            );

            FUpdateTask(
                const FUpdateTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
            ) override;
        };
        friend FUpdateTask;

        TSharedPtr<FAsyncTask<FUpdateTask>> Update(
            Request::FUpdateRoomRequestPtr Request
        );

        class GS2CHAT_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FRoomAccessTokenDomain> Self;
            const Request::FDeleteRoomRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FRoomAccessTokenDomain>& Self,
                const Request::FDeleteRoomRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteRoomRequestPtr Request
        );

        class GS2CHAT_API FPostTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>,
            public TSharedFromThis<FPostTask>
        {
            const TSharedPtr<FRoomAccessTokenDomain> Self;
            const Request::FPostRequestPtr Request;
        public:
            explicit FPostTask(
                const TSharedPtr<FRoomAccessTokenDomain>& Self,
                const Request::FPostRequestPtr Request
            );

            FPostTask(
                const FPostTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain>> Result
            ) override;
        };
        friend FPostTask;

        TSharedPtr<FAsyncTask<FPostTask>> Post(
            Request::FPostRequestPtr Request
        );

        class GS2CHAT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FRoom>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRoomAccessTokenDomain> Self;
            const Request::FGetRoomRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRoomAccessTokenDomain>& Self,
                const Request::FGetRoomRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetRoomRequestPtr Request
        );

        Gs2::Chat::Domain::Iterator::FDescribeMessagesIteratorPtr Messages(
            const TOptional<int32> Category = TOptional<int32>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMessages(
            TFunction<void()> Callback
        );

        void UnsubscribeMessages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesIteratorPtr LatestMessages(
            const TOptional<int32> Category = TOptional<int32>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLatestMessages(
            TFunction<void()> Callback
        );

        void UnsubscribeLatestMessages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Chat::Domain::Model::FMessageAccessTokenDomain> Message(
            const FString MessageName
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
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FRoom>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FRoomAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRoomAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Model::FRoom>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Chat::Model::FRoomPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FRoomAccessTokenDomain> FRoomAccessTokenDomainPtr;
}
