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

    class GS2JOBQUEUE_API FJobAccessTokenDomain:
        public TSharedFromThis<FJobAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> JobName;
    private:

        FString ParentKey;

    public:

        FJobAccessTokenDomain(
            const Core::Domain::FGs2Ptr Gs2,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
            const TOptional<FString> JobName
            // ReSharper disable once CppMemberInitializersOrder
        );

        FJobAccessTokenDomain(
            const FJobAccessTokenDomain& From
        );

        TSharedPtr<Gs2::JobQueue::Domain::Model::FJobResultAccessTokenDomain> JobResult(
            const int32 TryNumber
        ) const;

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
            const TSharedPtr<FJobAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FJobAccessTokenDomain> Self
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

    typedef TSharedPtr<FJobAccessTokenDomain> FJobAccessTokenDomainPtr;
}
