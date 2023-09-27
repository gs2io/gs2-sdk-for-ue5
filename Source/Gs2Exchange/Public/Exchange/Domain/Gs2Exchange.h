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
#include "Exchange/Gs2Exchange.h"

// Model
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/ExchangeAccessToken.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/AwaitAccessToken.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

// Iterator
#include "Exchange/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Exchange/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Exchange/Domain/Iterator/DescribeRateModelMastersIterator.h"
#include "Exchange/Domain/Iterator/DescribeIncrementalRateModelsIterator.h"
#include "Exchange/Domain/Iterator/DescribeIncrementalRateModelMastersIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsIterator.h"
#include "Exchange/Domain/Iterator/DescribeAwaitsByUserIdIterator.h"

// Notification

namespace Gs2::Exchange::Domain
{

    class GS2EXCHANGE_API FGs2ExchangeDomain:
        public TSharedFromThis<FGs2ExchangeDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Exchange::FGs2ExchangeRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2ExchangeDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2ExchangeDomain(
            const FGs2ExchangeDomain& From
        );

        class GS2EXCHANGE_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Exchange::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2ExchangeDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2ExchangeDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Exchange::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Exchange::Domain::Model::FNamespaceDomain> Namespace(
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
    typedef TSharedPtr<FGs2ExchangeDomain> FGs2ExchangeDomainPtr;
}
