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

    class GS2CHAT_API FUserDomain:
        public TSharedFromThis<FUserDomain>
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
    private:

        FString ParentKey;

    public:

        FUserDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Chat::Domain::FGs2ChatDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        Gs2::Chat::Domain::Iterator::FDescribeRoomsIteratorPtr Rooms(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeRooms(
            TFunction<void()> Callback

        );

        class FCollectRoomsTask;

        Gs2::Core::Domain::CallbackID SubscribeRooms(
            TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );

        void InvalidateRooms(const TOptional<FString> NamePrefix = TOptional<FString>());

        class GS2CHAT_API FSubscribeRoomsWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeRoomsWithInitialCallTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback;
        const TOptional<FString> QueryNamePrefix;
        public:
            FSubscribeRoomsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback,const TOptional<FString> NamePrefix);
            FSubscribeRoomsWithInitialCallTask(const FSubscribeRoomsWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeRoomsWithInitialCallTask>> SubscribeRoomsWithInitialCall(
            TFunction<void(TArray<Gs2::Chat::Model::FRoomPtr>)> Callback,const TOptional<FString> NamePrefix = TOptional<FString>()
        );
        void UnsubscribeRooms(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain> Room(
            const FString RoomName,
            const TOptional<FString> Password = TOptional<FString>()
        );

        Gs2::Chat::Domain::Iterator::FDescribeSubscribesByUserIdIteratorPtr Subscribes(
            const TOptional<FString> RoomNamePrefix = TOptional<FString>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribes(
            TFunction<void()> Callback

        );

        class FCollectSubscribesTask;

        Gs2::Core::Domain::CallbackID SubscribeSubscribes(
            TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix = TOptional<FString>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        void InvalidateSubscribes(const TOptional<FString> RoomNamePrefix = TOptional<FString>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>());

        class GS2CHAT_API FSubscribeSubscribesWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeSubscribesWithInitialCallTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback;
        const TOptional<FString> QueryRoomNamePrefix;const TOptional<FString> QueryTimeOffsetToken;
        public:
            FSubscribeSubscribesWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix,const TOptional<FString> TimeOffsetToken);
            FSubscribeSubscribesWithInitialCallTask(const FSubscribeSubscribesWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeSubscribesWithInitialCallTask>> SubscribeSubscribesWithInitialCall(
            TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const TOptional<FString> RoomNamePrefix = TOptional<FString>(),const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );
        void UnsubscribeSubscribes(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        Gs2::Chat::Domain::Iterator::FDescribeSubscribesByRoomNameIteratorPtr SubscribesByRoomName(
            const FString RoomName
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeSubscribesByRoomName(
            TFunction<void()> Callback

        );

        class FCollectSubscribesByRoomNameTask;

        Gs2::Core::Domain::CallbackID SubscribeSubscribesByRoomName(
            TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const FString RoomName
        );

        void InvalidateSubscribesByRoomName(const FString RoomName);

        class GS2CHAT_API FSubscribeSubscribesByRoomNameWithInitialCallTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Core::Domain::CallbackID>,
            public TSharedFromThis<FSubscribeSubscribesByRoomNameWithInitialCallTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback;
        const FString QueryRoomName;
        public:
            FSubscribeSubscribesByRoomNameWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const FString RoomName);
            FSubscribeSubscribesByRoomNameWithInitialCallTask(const FSubscribeSubscribesByRoomNameWithInitialCallTask& From);
            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result) override;
        };

        TSharedPtr<FAsyncTask<FSubscribeSubscribesByRoomNameWithInitialCallTask>> SubscribeSubscribesByRoomNameWithInitialCall(
            TFunction<void(TArray<Gs2::Chat::Model::FSubscribePtr>)> Callback,const FString RoomName
        );
        void UnsubscribeSubscribesByRoomName(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain> Subscribe(
            const FString RoomName
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserDomain> FUserDomainPtr;
}
