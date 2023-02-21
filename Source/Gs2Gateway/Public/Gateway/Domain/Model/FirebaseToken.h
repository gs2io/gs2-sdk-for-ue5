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

namespace Gs2::Gateway::Domain::Model
{
    class FNamespaceDomain;
    class FWebSocketSessionDomain;
    class FWebSocketSessionAccessTokenDomain;
    class FFirebaseTokenDomain;
    class FFirebaseTokenAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2GATEWAY_API FFirebaseTokenDomain:
        public TSharedFromThis<FFirebaseTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Gateway::FGs2GatewayRestClientPtr Client;
        Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr Wssession;
        FGs2GatewayWebSocketClientPtr Wsclient;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
    private:

        FString ParentKey;

    public:

        FFirebaseTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr Wssession,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FFirebaseTokenDomain(
            const FFirebaseTokenDomain& From
        );

        class GS2GATEWAY_API FSetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>,
            public TSharedFromThis<FSetTask>
        {
            const TSharedPtr<FFirebaseTokenDomain> Self;
            const Request::FSetFirebaseTokenByUserIdRequestPtr Request;
        public:
            explicit FSetTask(
                const TSharedPtr<FFirebaseTokenDomain> Self,
                const Request::FSetFirebaseTokenByUserIdRequestPtr Request
            );

            FSetTask(
                const FSetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>> Result
            ) override;
        };
        friend FSetTask;

        TSharedPtr<FAsyncTask<FSetTask>> Set(
            Request::FSetFirebaseTokenByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Model::FFirebaseToken>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FFirebaseTokenDomain> Self;
            const Request::FGetFirebaseTokenByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FFirebaseTokenDomain> Self,
                const Request::FGetFirebaseTokenByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FFirebaseToken>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetFirebaseTokenByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FFirebaseTokenDomain> Self;
            const Request::FDeleteFirebaseTokenByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FFirebaseTokenDomain> Self,
                const Request::FDeleteFirebaseTokenByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteFirebaseTokenByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FSendMobileNotificationTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>,
            public TSharedFromThis<FSendMobileNotificationTask>
        {
            const TSharedPtr<FFirebaseTokenDomain> Self;
            const Request::FSendMobileNotificationByUserIdRequestPtr Request;
        public:
            explicit FSendMobileNotificationTask(
                const TSharedPtr<FFirebaseTokenDomain> Self,
                const Request::FSendMobileNotificationByUserIdRequestPtr Request
            );

            FSendMobileNotificationTask(
                const FSendMobileNotificationTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FFirebaseTokenDomain>> Result
            ) override;
        };
        friend FSendMobileNotificationTask;

        TSharedPtr<FAsyncTask<FSendMobileNotificationTask>> SendMobileNotification(
            Request::FSendMobileNotificationByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
        );

        class GS2GATEWAY_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Model::FFirebaseToken>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FFirebaseTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FFirebaseTokenDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Model::FFirebaseToken>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

    };

    typedef TSharedPtr<FFirebaseTokenDomain> FFirebaseTokenDomainPtr;
}
