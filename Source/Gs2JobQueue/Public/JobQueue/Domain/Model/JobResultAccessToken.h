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
#include "JobQueue/Gs2JobQueue.h"
#include "JobQueue/Domain/Iterator/DescribeNamespacesIterator.h"
#include "JobQueue/Domain/Iterator/DescribeJobsByUserIdIterator.h"

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
    class FUserDomain;
    class FUserAccessTokenDomain;

    class GS2JOBQUEUE_API FJobResultAccessTokenDomain:
        public TSharedFromThis<FJobResultAccessTokenDomain>
    {
        const Core::Domain::FGs2Ptr Gs2;
        const JobQueue::Domain::FGs2JobQueueDomainPtr Service;
        const Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

        public:
        TOptional<FString> NamespaceName;
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
        TOptional<FString> JobName;
        TOptional<int32> TryNumber;
    private:

        FString ParentKey;

    public:

        FJobResultAccessTokenDomain(
            const Core::Domain::FGs2Ptr& Gs2,
            const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
            const TOptional<FString> JobName,
            const TOptional<int32> TryNumber
            // ReSharper disable once CppMemberInitializersOrder
        );

        FJobResultAccessTokenDomain(
            const FJobResultAccessTokenDomain& From
        );

        class GS2JOBQUEUE_API FGetTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FJobResult>,
            public TSharedFromThis<FGetTask>
        {
            const TSharedPtr<FJobResultAccessTokenDomain> Self;
            const Request::FGetJobResultRequestPtr Request;
        public:
            explicit FGetTask(
                const TSharedPtr<FJobResultAccessTokenDomain>& Self,
                const Request::FGetJobResultRequestPtr Request
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
            Request::FGetJobResultRequestPtr Request
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
            const TSharedPtr<FJobResultAccessTokenDomain> Self;
        public:
            explicit FModelTask(
                const TSharedPtr<FJobResultAccessTokenDomain> Self
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

        class GS2JOBQUEUE_API FModelNoCacheTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Model::FJobResult>,
            public TSharedFromThis<FModelNoCacheTask>
        {
            const TSharedPtr<FJobResultAccessTokenDomain> Self;
        public:
            explicit FModelNoCacheTask(
                const TSharedPtr<FJobResultAccessTokenDomain> Self
            );

            FModelNoCacheTask(
                const FModelNoCacheTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
            ) override;
        };
        friend FModelNoCacheTask;

        TSharedPtr<FAsyncTask<FModelNoCacheTask>> ModelNoCache();

        Gs2::Core::Domain::CallbackID Subscribe(
            TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
        );

        void Unsubscribe(
            Gs2::Core::Domain::CallbackID CallbackID
        );

    };

    typedef TSharedPtr<FJobResultAccessTokenDomain> FJobResultAccessTokenDomainPtr;
}
