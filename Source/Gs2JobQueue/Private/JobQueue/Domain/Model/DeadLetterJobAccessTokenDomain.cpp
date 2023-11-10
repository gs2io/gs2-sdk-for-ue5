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

#include "JobQueue/Domain/Model/DeadLetterJobAccessToken.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/DeadLetterJobAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FDeadLetterJobAccessTokenDomain::FDeadLetterJobAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> DeadLetterJobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        DeadLetterJobName(DeadLetterJobName),
        ParentKey(Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "DeadLetterJob"
        ))
    {
    }

    FDeadLetterJobAccessTokenDomain::FDeadLetterJobAccessTokenDomain(
        const FDeadLetterJobAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        DeadLetterJobName(From.DeadLetterJobName),
        ParentKey(From.ParentKey)
    {

    }

    FString FDeadLetterJobAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> DeadLetterJobName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (DeadLetterJobName.IsSet() ? *DeadLetterJobName : "null") + ":" +
            ChildType;
    }

    FString FDeadLetterJobAccessTokenDomain::CreateCacheKey(
        TOptional<FString> DeadLetterJobName
    )
    {
        return FString("") +
            (DeadLetterJobName.IsSet() ? *DeadLetterJobName : "null");
    }

    FDeadLetterJobAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FDeadLetterJobAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FDeadLetterJobAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeadLetterJobAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FDeadLetterJob>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::JobQueue::Model::FDeadLetterJob> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FDeadLetterJob>(
            Self->ParentKey,
            Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                Self->DeadLetterJobName
            ),
            &Value
        );
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeadLetterJobAccessTokenDomain::FModelTask>> FDeadLetterJobAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDeadLetterJobAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDeadLetterJobAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FDeadLetterJobPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::JobQueue::Model::FDeadLetterJob::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                DeadLetterJobName
            ),
            [Callback](TSharedPtr<Gs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::JobQueue::Model::FDeadLetterJob>(obj));
            }
        );
    }

    void FDeadLetterJobAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::JobQueue::Model::FDeadLetterJob::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                DeadLetterJobName
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

