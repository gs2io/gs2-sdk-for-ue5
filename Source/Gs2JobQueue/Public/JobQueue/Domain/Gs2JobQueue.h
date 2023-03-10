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
#include "JobQueue/Gs2JobQueue.h"

// Model
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/DeadLetterJobAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"

// Iterator
#include "JobQueue/Domain/Iterator/DescribeNamespacesIterator.h"
#include "JobQueue/Domain/Iterator/DescribeJobsByUserIdIterator.h"
#include "JobQueue/Domain/Iterator/DescribeDeadLetterJobsByUserIdIterator.h"

// Notification
#include "JobQueue/Model/PushNotification.h"
#include "JobQueue/Model/RunNotification.h"

namespace Gs2::JobQueue::Domain
{
    DECLARE_EVENT_OneParam(FGs2JobQueueDomain, FPushNotificationEvent, Gs2::JobQueue::Model::FPushNotificationPtr);
    DECLARE_EVENT_OneParam(FGs2JobQueueDomain, FRunNotificationEvent, Gs2::JobQueue::Model::FRunNotificationPtr);

    class GS2JOBQUEUE_API FGs2JobQueueDomain:
        public TSharedFromThis<FGs2JobQueueDomain>
    {

        TSharedPtr<TArray<Gs2::JobQueue::Model::FRunNotificationPtr>> CopiedCompletedJobs;
        TSharedPtr<FCriticalSection> CopiedCompletedJobsMutex;
        FPushNotificationEvent PushNotificationEvent;
        FRunNotificationEvent RunNotificationEvent;
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2JobQueueDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2JobQueueDomain(
            const FGs2JobQueueDomain& From
        );

        class GS2JOBQUEUE_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2JobQueueDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2JobQueueDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::JobQueue::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::JobQueue::Domain::Model::FNamespaceDomain> Namespace(
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
        FPushNotificationEvent& OnPushNotification();
        FRunNotificationEvent& OnRunNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        class GS2JOBQUEUE_API FDispatchTask final :
            public Gs2::Core::Util::TGs2Future<void*>,
            public TSharedFromThis<FDispatchTask>
        {
            const TSharedPtr<FGs2JobQueueDomain> Self;
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        public:
            explicit FDispatchTask(
                const TSharedPtr<FGs2JobQueueDomain> Self,
                const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<void*>> Result
            ) override;
        };
        friend FDispatchTask;

        TSharedPtr<FAsyncTask<FDispatchTask>> Dispatch(
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
        );
    };
    typedef TSharedPtr<FGs2JobQueueDomain> FGs2JobQueueDomainPtr;
}
