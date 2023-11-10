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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FJobDomain::FJobDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> JobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        JobName(JobName),
        ParentKey(Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Job"
        ))
    {
    }

    FJobDomain::FJobDomain(
        const FJobDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        JobName(From.JobName),
        ParentKey(From.ParentKey)
    {

    }

    FJobDomain::FGetTask::FGetTask(
        const TSharedPtr<FJobDomain>& Self,
        const Request::FGetJobByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJobDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJob>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithJobName(Self->JobName);
        const auto Future = Self->Client->GetJobByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Job"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FJob::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobDomain::FGetTask>> FJobDomain::Get(
        Request::FGetJobByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FJobDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FJobDomain>& Self,
        const Request::FDeleteJobByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJobDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithJobName(Self->JobName);
        const auto Future = Self->Client->DeleteJobByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Job"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::JobQueue::Model::FJob::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobDomain::FDeleteTask>> FJobDomain::Delete(
        Request::FDeleteJobByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FJobResultDomain> FJobDomain::JobResult(
        const int32 TryNumber
    )
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FJobResultDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            JobName,
            TryNumber
        );
    }

    FString FJobDomain::CreateCacheParentKey(
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

    FString FJobDomain::CreateCacheKey(
        TOptional<FString> JobName
    )
    {
        return FString("") +
            (JobName.IsSet() ? *JobName : "null");
    }

    FJobDomain::FModelTask::FModelTask(
        const TSharedPtr<FJobDomain> Self
    ): Self(Self)
    {

    }

    FJobDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJobDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJob>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::JobQueue::Model::FJob> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FJob>(
            Self->ParentKey,
            Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                Self->JobName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::JobQueue::Request::FGetJobByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                    Self->JobName
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FJob::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "job")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FJob>(
                Self->ParentKey,
                Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                    Self->JobName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobDomain::FModelTask>> FJobDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJobDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FJobDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FJobPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
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

    void FJobDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
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

