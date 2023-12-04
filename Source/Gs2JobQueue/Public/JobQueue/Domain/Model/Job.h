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
 *
 * deny overwrite
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

    class GS2JOBQUEUE_API FJobDomain:
        public TSharedFromThis<FJobDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const JobQueue::Domain::FGs2JobQueueDomainPtr Service;
        const Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

        public:
        TOptional<bool> AutoRun;
        TOptional<bool> IsLastJob;
        TOptional<bool> NeedRetry;
        TOptional<bool> GetAutoRun() const
        {
            return AutoRun;
        }
        TOptional<bool> GetIsLastJob() const
        {
            return IsLastJob;
        }
        TOptional<bool> GetNeedRetry() const
        {
            return NeedRetry;
        }
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> JobName;
    private:

        FString ParentKey;

    public:

        FJobDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> JobName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FJobDomain(
            const FJobDomain& From
        );

        class GS2JOBQUEUE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FJob>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FJobDomain> Self;
            const Request::FGetJobByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FJobDomain>& Self,
                const Request::FGetJobByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJob>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetJobByUserIdRequestPtr Request
        );

        class GS2JOBQUEUE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Domain::Model::FJobDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FJobDomain> Self;
            const Request::FDeleteJobByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FJobDomain>& Self,
                const Request::FDeleteJobByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteJobByUserIdRequestPtr Request
        );

        TSharedPtr<Gs2::JobQueue::Domain::Model::FJobResultDomain> JobResult(
            const int32 TryNumber = 0
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> JobName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> JobName
        );

        class GS2JOBQUEUE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FJob>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FJobDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FJobDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJob>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::JobQueue::Model::FJobPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FJobDomain> FJobDomainPtr;
}
