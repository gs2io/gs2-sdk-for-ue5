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

    class GS2CHAT_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Chat::FGs2ChatRestClientPtr Client;

        public:
        TOptional<FString> NextPageToken;
        TOptional<FString> GetNextPageToken() const
        {
            return NextPageToken;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2CHAT_API FCreateRoomTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>,
            public TSharedFromThis<FCreateRoomTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FCreateRoomRequestPtr Request;
        public:
            explicit FCreateRoomTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FCreateRoomRequestPtr Request
            );

            FCreateRoomTask(
                const FCreateRoomTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain>> Result
            ) override;
        };
        friend FCreateRoomTask;

        TSharedPtr<FAsyncTask<FCreateRoomTask>> CreateRoom(
            Request::FCreateRoomRequestPtr Request
        );

        TSharedPtr<Gs2::Chat::Domain::Model::FRoomAccessTokenDomain> Room(
            const FString RoomName,
            const TOptional<FString> Password = TOptional<FString>()
        ) const;

        Gs2::Chat::Domain::Iterator::FDescribeSubscribesIteratorPtr Subscribes(
        ) const;

        TSharedPtr<Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomain> Subscribe(
            const FString RoomName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
