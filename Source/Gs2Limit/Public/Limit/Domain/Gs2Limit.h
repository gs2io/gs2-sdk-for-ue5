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
#include "Limit/Gs2Limit.h"

// Model
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"

// Iterator
#include "Limit/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersIterator.h"
#include "Limit/Domain/Iterator/DescribeCountersByUserIdIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelMastersIterator.h"
#include "Limit/Domain/Iterator/DescribeLimitModelsIterator.h"

// Notification

namespace Gs2::Limit::Domain
{

    class GS2LIMIT_API FGs2LimitDomain:
        public TSharedFromThis<FGs2LimitDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Limit::FGs2LimitRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2LimitDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2LimitDomain(
            const FGs2LimitDomain& From
        );

        class GS2LIMIT_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Limit::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2LimitDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2LimitDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Limit::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Limit::Domain::Model::FNamespaceDomain> Namespace(
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
    typedef TSharedPtr<FGs2LimitDomain> FGs2LimitDomainPtr;
}
