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

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Gateway/Gs2Gateway.h"

// Model
#include "Gateway/Domain/Model/Namespace.h"
#include "Gateway/Domain/Model/WebSocketSession.h"
#include "Gateway/Domain/Model/WebSocketSessionAccessToken.h"
#include "Gateway/Domain/Model/FirebaseToken.h"
#include "Gateway/Domain/Model/FirebaseTokenAccessToken.h"
#include "Gateway/Domain/Model/User.h"
#include "Gateway/Domain/Model/UserAccessToken.h"

// Iterator
#include "Gateway/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Gateway/Domain/Iterator/DescribeWebSocketSessionsIterator.h"
#include "Gateway/Domain/Iterator/DescribeWebSocketSessionsByUserIdIterator.h"

// Notification

namespace Gs2::Gateway::Domain
{

    class GS2GATEWAY_API FGs2GatewayDomain:
        public TSharedFromThis<FGs2GatewayDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Gateway::FGs2GatewayRestClientPtr Client;
        Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr Wssession;
        FGs2GatewayWebSocketClientPtr Wsclient;

        public:
        TOptional<FString> Url;
        TOptional<FString> GetUrl() const
        {
            return Url;
        }
    private:

        FString ParentKey;

    public:

        FGs2GatewayDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const Gs2::Core::Net::WebSocket::FGs2WebSocketSessionPtr Wssession
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2GatewayDomain(
            const FGs2GatewayDomain& From
        );

        class GS2GATEWAY_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Gateway::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2GatewayDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2GatewayDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Gateway::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        class GS2GATEWAY_API FDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GatewayDomain>,
            public TSharedFromThis<FDumpUserDataTask>
        {
            const TSharedPtr<FGs2GatewayDomain> Self;
            const Request::FDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FDumpUserDataTask(
                const TSharedPtr<FGs2GatewayDomain> Self,
                const Request::FDumpUserDataByUserIdRequestPtr Request
            );

            FDumpUserDataTask(
                const FDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GatewayDomain>> Result
            ) override;
        };
        friend FDumpUserDataTask;

        TSharedPtr<FAsyncTask<FDumpUserDataTask>> DumpUserData(
            Request::FDumpUserDataByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FCheckDumpUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GatewayDomain>,
            public TSharedFromThis<FCheckDumpUserDataTask>
        {
            const TSharedPtr<FGs2GatewayDomain> Self;
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckDumpUserDataTask(
                const TSharedPtr<FGs2GatewayDomain> Self,
                const Request::FCheckDumpUserDataByUserIdRequestPtr Request
            );

            FCheckDumpUserDataTask(
                const FCheckDumpUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GatewayDomain>> Result
            ) override;
        };
        friend FCheckDumpUserDataTask;

        TSharedPtr<FAsyncTask<FCheckDumpUserDataTask>> CheckDumpUserData(
            Request::FCheckDumpUserDataByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GatewayDomain>,
            public TSharedFromThis<FCleanUserDataTask>
        {
            const TSharedPtr<FGs2GatewayDomain> Self;
            const Request::FCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCleanUserDataTask(
                const TSharedPtr<FGs2GatewayDomain> Self,
                const Request::FCleanUserDataByUserIdRequestPtr Request
            );

            FCleanUserDataTask(
                const FCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GatewayDomain>> Result
            ) override;
        };
        friend FCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCleanUserDataTask>> CleanUserData(
            Request::FCleanUserDataByUserIdRequestPtr Request
        );

        class GS2GATEWAY_API FCheckCleanUserDataTask final :
            public Gs2::Core::Util::TGs2Future<FGs2GatewayDomain>,
            public TSharedFromThis<FCheckCleanUserDataTask>
        {
            const TSharedPtr<FGs2GatewayDomain> Self;
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request;
        public:
            explicit FCheckCleanUserDataTask(
                const TSharedPtr<FGs2GatewayDomain> Self,
                const Request::FCheckCleanUserDataByUserIdRequestPtr Request
            );

            FCheckCleanUserDataTask(
                const FCheckCleanUserDataTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<FGs2GatewayDomain>> Result
            ) override;
        };
        friend FCheckCleanUserDataTask;

        TSharedPtr<FAsyncTask<FCheckCleanUserDataTask>> CheckCleanUserData(
            Request::FCheckCleanUserDataByUserIdRequestPtr Request
        );

        Gs2::Gateway::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Gateway::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2GatewayDomain> FGs2GatewayDomainPtr;
}
