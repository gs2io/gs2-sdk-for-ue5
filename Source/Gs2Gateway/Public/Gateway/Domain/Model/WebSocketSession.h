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

    class GS2GATEWAY_API FWebSocketSessionDomain:
        public TSharedFromThis<FWebSocketSessionDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const Gateway::Domain::FGs2GatewayDomainPtr Service;
        const Gs2::Gateway::FGs2GatewayRestClientPtr Client;
        const FGs2GatewayWebSocketClientPtr Wsclient;

        public:
        TOptional<FString> Protocol;
        TOptional<FString> GetProtocol() const
        {
            return Protocol;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> ConnectionId;
    private:

        FString ParentKey;

    public:

        FWebSocketSessionDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const Gateway::Domain::FGs2GatewayDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FWebSocketSessionDomain(
            const FWebSocketSessionDomain& From
        );

        class GS2GATEWAY_API FSetUserIdTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>,
            public TSharedFromThis<FSetUserIdTask>
        {
            const TSharedPtr<FWebSocketSessionDomain> Self;
            const Request::FSetUserIdByUserIdRequestPtr Request;
        public:
            explicit FSetUserIdTask(
                const TSharedPtr<FWebSocketSessionDomain>& Self,
                const Request::FSetUserIdByUserIdRequestPtr Request
            );

            FSetUserIdTask(
                const FSetUserIdTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionDomain>> Result
            ) override;
        };
        friend FSetUserIdTask;

        TSharedPtr<FAsyncTask<FSetUserIdTask>> SetUserId(
            Request::FSetUserIdByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2GATEWAY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Model::FWebSocketSession>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FWebSocketSessionDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FWebSocketSessionDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FWebSocketSession>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::Gateway::Model::FWebSocketSessionPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FWebSocketSessionDomain> FWebSocketSessionDomainPtr;
}
