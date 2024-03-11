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
#include "Gateway/Gs2Gateway.h"
#include "Gateway/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Gateway/Domain/Iterator/DescribeWebSocketSessionsIterator.h"
#include "Gateway/Domain/Iterator/DescribeWebSocketSessionsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Gateway::Domain
{
    class FGs2GatewayDomain;
    typedef TSharedPtr<FGs2GatewayDomain> FGs2GatewayDomainPtr;
}

namespace Gs2::Gateway::Domain::Model
{
    class FNamespaceDomain;
    class FWebSocketSessionDomain;
    class FWebSocketSessionAccessTokenDomain;
    class FFirebaseTokenDomain;
    class FFirebaseTokenAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2GATEWAY_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gateway::Domain::FGs2GatewayDomainPtr Service;
        const Gs2::Gateway::FGs2GatewayRestClientPtr Client;
        const FGs2GatewayWebSocketClientPtr Wsclient;

        public:
        TOptional<FString> Protocol;
        TOptional<FString> NextPageToken;
        TOptional<FString> GetProtocol() const
        {
            return Protocol;
        }
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
            const Gateway::Domain::FGs2GatewayDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2GATEWAY_API FSendNotificationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FUserDomain>,
            public TSharedFromThis<FSendNotificationTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FSendNotificationRequestPtr Request;
        public:
            explicit FSendNotificationTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FSendNotificationRequestPtr Request
            );

            FSendNotificationTask(
                const FSendNotificationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FSendNotificationTask;

        TSharedPtr<FAsyncTask<FSendNotificationTask>> SendNotification(
            Request::FSendNotificationRequestPtr Request
        );

        class GS2GATEWAY_API FDisconnectTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>>>,
            public TSharedFromThis<FDisconnectTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDisconnectByUserIdRequestPtr Request;
        public:
            explicit FDisconnectTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FDisconnectByUserIdRequestPtr Request
            );

            FDisconnectTask(
                const FDisconnectTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>>>> Result
            ) override;
        };
        friend FDisconnectTask;

        TSharedPtr<FAsyncTask<FDisconnectTask>> Disconnect(
            Request::FDisconnectByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FDisconnectAllTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FUserDomain>,
            public TSharedFromThis<FDisconnectAllTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FDisconnectAllRequestPtr Request;
        public:
            explicit FDisconnectAllTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FDisconnectAllRequestPtr Request
            );

            FDisconnectAllTask(
                const FDisconnectAllTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FUserDomain>> Result
            ) override;
        };
        friend FDisconnectAllTask;

        TSharedPtr<FAsyncTask<FDisconnectAllTask>> DisconnectAll(
            Request::FDisconnectAllRequestPtr Request
        );

        Gs2::Gateway::Domain::Iterator::FDescribeWebSocketSessionsByUserIdIteratorPtr WebSocketSessions(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeWebSocketSessions(
            TFunction<void()> Callback
        );

        void UnsubscribeWebSocketSessions(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain> WebSocketSession(
        );

        TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain> FirebaseToken(
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
