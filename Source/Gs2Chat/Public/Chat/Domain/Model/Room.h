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

    class GS2CHAT_API FRoomDomain:
        public TSharedFromThis<FRoomDomain>
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
        TOptional<FString> UserId;
        TOptional<FString> RoomName;
        TOptional<FString> Password;
    private:

        FString ParentKey;

    public:

        FRoomDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Chat::Domain::FGs2ChatDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> RoomName,
            const TOptional<FString> Password
            // ReSharper disable once CppMemberInitializersOrder
        );

        FRoomDomain(
            const FRoomDomain& From
        );

        class GS2CHAT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FRoom>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FRoomDomain> Self;
            const Request::FGetRoomRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FRoomDomain>& Self,
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

        class GS2CHAT_API FUpdateFromBackendTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FRoomDomain>,
            public TSharedFromThis<FUpdateFromBackendTask>
        {
            const TSharedPtr<FRoomDomain> Self;
            const Request::FUpdateRoomFromBackendRequestPtr Request;
        public:
            explicit FUpdateFromBackendTask(
                const TSharedPtr<FRoomDomain>& Self,
                const Request::FUpdateRoomFromBackendRequestPtr Request
            );

            FUpdateFromBackendTask(
                const FUpdateFromBackendTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
            ) override;
        };
        friend FUpdateFromBackendTask;

        TSharedPtr<FAsyncTask<FUpdateFromBackendTask>> UpdateFromBackend(
            Request::FUpdateRoomFromBackendRequestPtr Request
        );

        class GS2CHAT_API FDeleteFromBackendTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FRoomDomain>,
            public TSharedFromThis<FDeleteFromBackendTask>
        {
            const TSharedPtr<FRoomDomain> Self;
            const Request::FDeleteRoomFromBackendRequestPtr Request;
        public:
            explicit FDeleteFromBackendTask(
                const TSharedPtr<FRoomDomain>& Self,
                const Request::FDeleteRoomFromBackendRequestPtr Request
            );

            FDeleteFromBackendTask(
                const FDeleteFromBackendTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain>> Result
            ) override;
        };
        friend FDeleteFromBackendTask;

        TSharedPtr<FAsyncTask<FDeleteFromBackendTask>> DeleteFromBackend(
            Request::FDeleteRoomFromBackendRequestPtr Request
        );

        class GS2CHAT_API FPostTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FMessageDomain>,
            public TSharedFromThis<FPostTask>
        {
            const TSharedPtr<FRoomDomain> Self;
            const Request::FPostByUserIdRequestPtr Request;
        public:
            explicit FPostTask(
                const TSharedPtr<FRoomDomain>& Self,
                const Request::FPostByUserIdRequestPtr Request
            );

            FPostTask(
                const FPostTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain>> Result
            ) override;
        };
        friend FPostTask;

        TSharedPtr<FAsyncTask<FPostTask>> Post(
            Request::FPostByUserIdRequestPtr Request
        );

        Gs2::Chat::Domain::Iterator::FDescribeMessagesByUserIdIteratorPtr Messages(
            const TOptional<int32> Category = TOptional<int32>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMessages(
            TFunction<void()> Callback
        );

        void UnsubscribeMessages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Chat::Domain::Iterator::FDescribeLatestMessagesByUserIdIteratorPtr LatestMessages(
            const TOptional<int32> Category = TOptional<int32>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLatestMessages(
            TFunction<void()> Callback
        );

        void UnsubscribeLatestMessages(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Chat::Domain::Model::FMessageDomain> Message(
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
            const TSharedPtr<FRoomDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FRoomDomain> Self
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

    typedef TSharedPtr<FRoomDomain> FRoomDomainPtr;
}
