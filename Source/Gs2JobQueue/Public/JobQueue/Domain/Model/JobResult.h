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

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
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

    class GS2JOBQUEUE_API FJobResultDomain:
        public TSharedFromThis<FJobResultDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        TOptional<FString> UserId;
        TOptional<FString> JobName;
        TOptional<int32> TryNumber;
    private:

        FString ParentKey;

    public:

        FJobResultDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> JobName,
            const TOptional<int32> TryNumber
            // ReSharper disable once CppMemberInitializersOrder
        );

        FJobResultDomain(
            const FJobResultDomain& From
        );

        class GS2JOBQUEUE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FJobResult>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FJobResultDomain> Self;
            const Request::FGetJobResultByUserIdRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FJobResultDomain> Self,
                const Request::FGetJobResultByUserIdRequestPtr Request
            );

            FGetTask(
                const FGetTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
            ) override;
        };
        friend FGetTask;

        TSharedPtr<FAsyncTask<FGetTask>> Get(
            Request::FGetJobResultByUserIdRequestPtr Request
        );

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            TOptional<FString> JobName,
            TOptional<FString> TryNumber,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> TryNumber
        );

        class GS2JOBQUEUE_API FModelTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FJobResult>,
            public TSharedFromThis<FModelTask>
        {
            const TSharedPtr<FJobResultDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FJobResultDomain> Self
            );

            FModelTask(
                const FModelTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
            ) override;
        };
        friend FModelTask;

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FJobResultDomain> FJobResultDomainPtr;
}
