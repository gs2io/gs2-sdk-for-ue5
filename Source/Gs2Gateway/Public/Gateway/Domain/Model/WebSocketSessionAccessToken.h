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
#include "Gateway/Gs2Gateway.h"
#include "Gateway/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Gateway/Domain/Iterator/DescribeWebSocketSessionsIterator.h"
#include "Gateway/Domain/Iterator/DescribeWebSocketSessionsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2GATEWAY_API FWebSocketSessionAccessTokenDomain:
        public TSharedFromThis<FWebSocketSessionAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::Gateway::FGs2GatewayRestClientPtr Client;
        FGs2GatewayWebSocketClientPtr Wsclient;

        public:
        TOptional<FString> Protocol;
        TOptional<FString> GetProtocol() const
        {
            return Protocol;
        }
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> ConnectionId;
    private:

        FString ParentKey;

    public:

        FWebSocketSessionAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FWebSocketSessionAccessTokenDomain(
            const FWebSocketSessionAccessTokenDomain& From
        );

        class GS2GATEWAY_API FSetUserIdTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FWebSocketSessionAccessTokenDomain>,
            public TSharedFromThis<FSetUserIdTask>
        {
            const TSharedPtr<FWebSocketSessionAccessTokenDomain> Self;
            const Request::FSetUserIdRequestPtr Request;
        public:
            explicit FSetUserIdTask(
                const TSharedPtr<FWebSocketSessionAccessTokenDomain> Self,
                const Request::FSetUserIdRequestPtr Request
            );

            FSetUserIdTask(
                const FSetUserIdTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FWebSocketSessionAccessTokenDomain>> Result
            ) override;
        };
        friend FSetUserIdTask;

        TSharedPtr<FAsyncTask<FSetUserIdTask>> SetUserId(
            Request::FSetUserIdRequestPtr Request
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
            const TSharedPtr<FWebSocketSessionAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FWebSocketSessionAccessTokenDomain> Self
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

    typedef TSharedPtr<FWebSocketSessionAccessTokenDomain> FWebSocketSessionAccessTokenDomainPtr;
}
