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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2CHAT_API FMessageAccessTokenDomain:
        public TSharedFromThis<FMessageAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Chat::FGs2ChatRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> RoomName;
        TOptional<FString> Password;
        TOptional<FString> MessageName;
    private:

        FString ParentKey;

    public:

        FMessageAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> RoomName,
            const TOptional<FString> Password,
            const TOptional<FString> MessageName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FMessageAccessTokenDomain(
            const FMessageAccessTokenDomain& From
        );

        class GS2CHAT_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FMessage>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
            const Request::FGetMessageRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FMessageAccessTokenDomain> Self,
                const Request::FGetMessageRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetMessageRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> RoomName,
            TOptional<FString> MessageName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> MessageName
        );

        class GS2CHAT_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Model::FMessage>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FMessageAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FMessageAccessTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Model::FMessage>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Chat::Model::FMessagePtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FMessageAccessTokenDomain> FMessageAccessTokenDomainPtr;
}
