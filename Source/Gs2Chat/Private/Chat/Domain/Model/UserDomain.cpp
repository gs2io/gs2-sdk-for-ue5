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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Chat::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Chat::Domain::FGs2ChatDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Chat::FGs2ChatRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Chat::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Chat::Domain::Iterator::FDescribeRoomsIteratorPtr FUserDomain::Rooms(
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeRoomsIterator>(
            Gs2->Cache,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeRooms(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                "Room"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeRooms(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FRoom::TypeName,
            Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                TOptional<FString>("Singleton"),
                "Room"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FRoomDomain> FUserDomain::Room(
        const FString RoomName,
        const TOptional<FString> Password
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FRoomDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RoomName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RoomName),
            Password
        );
    }

    Gs2::Chat::Domain::Iterator::FDescribeSubscribesByUserIdIteratorPtr FUserDomain::Subscribes(
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeSubscribesByUserIdIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribes(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Subscribe"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeSubscribes(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Subscribe"
            ),
            CallbackID
        );
    }

    Gs2::Chat::Domain::Iterator::FDescribeSubscribesByRoomNameIteratorPtr FUserDomain::SubscribesByRoomName(
        const FString RoomName
    ) const
    {
        return MakeShared<Gs2::Chat::Domain::Iterator::FDescribeSubscribesByRoomNameIterator>(
            Gs2->Cache,
            Client,
            NamespaceName,
            RoomName
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeSubscribesByRoomName(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Subscribe"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeSubscribesByRoomName(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Chat::Model::FSubscribe::TypeName,
            Gs2::Chat::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Subscribe"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeDomain> FUserDomain::Subscribe(
        const FString RoomName
    )
    {
        return MakeShared<Gs2::Chat::Domain::Model::FSubscribeDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            RoomName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RoomName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

