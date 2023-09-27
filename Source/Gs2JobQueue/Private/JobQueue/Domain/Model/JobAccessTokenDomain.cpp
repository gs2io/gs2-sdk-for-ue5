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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/DeadLetterJobAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FJobAccessTokenDomain::FJobAccessTokenDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken,
        const TOptional<FString> JobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Session)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        JobName(JobName),
        ParentKey(Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "Job"
        ))
    {
    }

    FJobAccessTokenDomain::FJobAccessTokenDomain(
        const FJobAccessTokenDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        JobName(From.JobName),
        ParentKey(From.ParentKey)
    {

    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FJobResultAccessTokenDomain> FJobAccessTokenDomain::JobResult(
        const int32 TryNumber
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FJobResultAccessTokenDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            AccessToken,
            JobName,
            TryNumber
        );
    }

    FString FJobAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> JobName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (JobName.IsSet() ? *JobName : "null") + ":" +
            ChildType;
    }

    FString FJobAccessTokenDomain::CreateCacheKey(
        TOptional<FString> JobName
    )
    {
        return FString("") +
            (JobName.IsSet() ? *JobName : "null");
    }

    FJobAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FJobAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FJobAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJobAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJob>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::JobQueue::Model::FJob> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::JobQueue::Model::FJob>(
            Self->ParentKey,
            Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                Self->JobName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobAccessTokenDomain::FModelTask>> FJobAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJobAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FJobAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FJobPtr)> Callback
    )
    {
        return Cache->Subscribe(
            Gs2::JobQueue::Model::FJob::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                JobName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::JobQueue::Model::FJob>(obj));
            }
        );
    }

    void FJobAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->Unsubscribe(
            Gs2::JobQueue::Model::FJob::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                JobName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

