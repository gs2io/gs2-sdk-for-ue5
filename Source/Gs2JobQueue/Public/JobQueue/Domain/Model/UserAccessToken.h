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

    class GS2JOBQUEUE_API FUserAccessTokenDomain:
        public TSharedFromThis<FUserAccessTokenDomain>
    {
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::JobQueue::FGs2JobQueueRestClientPtr Client;

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
        Gs2::Auth::Model::FAccessTokenPtr AccessToken;
        TOptional<FString> UserId() const { return AccessToken->GetUserId(); }
    private:

        FString ParentKey;

    public:

        FUserAccessTokenDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
            const TOptional<FString> NamespaceName,
            const Gs2::Auth::Model::FAccessTokenPtr AccessToken
            // ReSharper disable once CppMemberInitializersOrder
        );

        FUserAccessTokenDomain(
            const FUserAccessTokenDomain& From
        );

        class GS2JOBQUEUE_API FRunTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::JobQueue::Domain::Model::FJobAccessTokenDomain>,
            public TSharedFromThis<FRunTask>
        {
            const TSharedPtr<FUserAccessTokenDomain> Self;
            const Request::FRunRequestPtr Request;
        public:
            explicit FRunTask(
                const TSharedPtr<FUserAccessTokenDomain> Self,
                const Request::FRunRequestPtr Request
            );

            FRunTask(
                const FRunTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobAccessTokenDomain>> Result
            ) override;
        };
        friend FRunTask;

        TSharedPtr<FAsyncTask<FRunTask>> Run(
            Request::FRunRequestPtr Request
        );

        TSharedPtr<Gs2::JobQueue::Domain::Model::FJobAccessTokenDomain> Job(
            const FString JobName
        ) const;

        TSharedPtr<Gs2::JobQueue::Domain::Model::FDeadLetterJobAccessTokenDomain> DeadLetterJob(
            const FString DeadLetterJobName
        ) const;

        static FString CreateCacheParentKey(
            TOptional<FString> NamespaceName,
            TOptional<FString> UserId,
            FString ChildType
        );

        static FString CreateCacheKey(
            TOptional<FString> UserId
        );

    };

    typedef TSharedPtr<FUserAccessTokenDomain> FUserAccessTokenDomainPtr;
}
