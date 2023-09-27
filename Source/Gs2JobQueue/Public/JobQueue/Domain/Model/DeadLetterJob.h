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
#include "JobQueue/Gs2JobQueue.h"
#include "JobQueue/Domain/Iterator/DescribeNamespacesIterator.h"
#include "JobQueue/Domain/Iterator/DescribeJobsByUserIdIterator.h"
#include "JobQueue/Domain/Iterator/DescribeDeadLetterJobsByUserIdIterator.h"

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

    class GS2JOBQUEUE_API FDeadLetterJobDomain:
        public TSharedFromThis<FDeadLetterJobDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> DeadLetterJobName;
    private:

        FString ParentKey;

    public:

        FDeadLetterJobDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> DeadLetterJobName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FDeadLetterJobDomain(
            const FDeadLetterJobDomain& From
        );

        class GS2JOBQUEUE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FDeadLetterJob>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FDeadLetterJobDomain> Self;
            const Request::FGetDeadLetterJobByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FDeadLetterJobDomain> Self,
                const Request::FGetDeadLetterJobByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FDeadLetterJob>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetDeadLetterJobByUserIdRequestPtr Request
        );

        class GS2JOBQUEUE_API FDeleteTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain>,
            public TSharedFromThis<FDeleteTask>
        {
            const TSharedPtr<FDeadLetterJobDomain> Self;
            const Request::FDeleteDeadLetterJobByUserIdRequestPtr Request;
        public:
            explicit FDeleteTask(
                const TSharedPtr<FDeadLetterJobDomain> Self,
                const Request::FDeleteDeadLetterJobByUserIdRequestPtr Request
            );

            FDeleteTask(
                const FDeleteTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain>> Result
            ) override;
        };
        friend FDeleteTask;

        TSharedPtr<FAsyncTask<FDeleteTask>> Delete(
            Request::FDeleteDeadLetterJobByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> DeadLetterJobName,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> DeadLetterJobName
        );

        class GS2JOBQUEUE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FDeadLetterJob>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FDeadLetterJobDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FDeadLetterJobDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FDeadLetterJob>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::JobQueue::Model::FDeadLetterJobPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FDeadLetterJobDomain> FDeadLetterJobDomainPtr;
}
