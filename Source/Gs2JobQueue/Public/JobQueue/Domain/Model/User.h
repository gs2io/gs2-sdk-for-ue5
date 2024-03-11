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
#include "JobQueue/Domain/Iterator/DescribeNamespacesIterator.h"
#include "JobQueue/Domain/Iterator/DescribeJobsByUserIdIterator.h"
#include "JobQueue/Domain/Iterator/DescribeDeadLetterJobsByUserIdIterator.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::JobQueue::Domain
{
    class FGs2JobQueueDomain;
    typedef TSharedPtr<FGs2JobQueueDomain> FGs2JobQueueDomainPtr;
}

namespace Gs2::JobQueue::Domain::Model
{
    class FNamespaceDomain;
    class FJobDomain;
    class FJobAccessTokenDomain;
    class FJobResultDomain;
    class FJobResultAccessTokenDomain;
    class FDeadLetterJobDomain;
    class FDeadLetterJobAccessTokenDomain;
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2JOBQUEUE_API FUserDomain:
        public TSharedFromThis<FUserDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const JobQueue::Domain::FGs2JobQueueDomainPtr Service;
        const Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

        public:
        TOptional<bool> AutoRun;
        TOptional<bool> IsLastJob;
        TOptional<FString> NextPageToken;
        TOptional<bool> GetAutoRun() const
        {
            return AutoRun;
        }
        TOptional<bool> GetIsLastJob() const
        {
            return IsLastJob;
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
            const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserDomain(
            const FUserDomain& From
        );

        class GS2JOBQUEUE_API FPushTask final :
            public Gs2::Core::Util::TGs2Future<TArray<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>>>,
            public TSharedFromThis<FPushTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FPushByUserIdRequestPtr Request;
        public:
            explicit FPushTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FPushByUserIdRequestPtr Request
            );

            FPushTask(
                const FPushTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>>>> Result
            ) override;
        };
        friend FPushTask;

        TSharedPtr<FAsyncTask<FPushTask>> Push(
            Request::FPushByUserIdRequestPtr Request
        );

        class GS2JOBQUEUE_API FRunTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Domain::Model::FJobDomain>,
            public TSharedFromThis<FRunTask>
        {
            const TSharedPtr<FUserDomain> Self;
            const Request::FRunByUserIdRequestPtr Request;
        public:
            explicit FRunTask(
                const TSharedPtr<FUserDomain>& Self,
                const Request::FRunByUserIdRequestPtr Request
            );

            FRunTask(
                const FRunTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>> Result
            ) override;
        };
        friend FRunTask;

        TSharedPtr<FAsyncTask<FRunTask>> Run(
            Request::FRunByUserIdRequestPtr Request
        );

        Gs2::JobQueue::Domain::Iterator::FDescribeJobsByUserIdIteratorPtr Jobs(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeJobs(
            TFunction<void()> Callback
        );

        void UnsubscribeJobs(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain> Job(
            const FString JobName
        );

        Gs2::JobQueue::Domain::Iterator::FDescribeDeadLetterJobsByUserIdIteratorPtr DeadLetterJobs(
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeDeadLetterJobs(
            TFunction<void()> Callback
        );

        void UnsubscribeDeadLetterJobs(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain> DeadLetterJob(
            const FString DeadLetterJobName
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
