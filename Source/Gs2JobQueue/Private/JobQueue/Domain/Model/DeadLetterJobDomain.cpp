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

    FDeadLetterJobDomain::FDeadLetterJobDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> DeadLetterJobName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        DeadLetterJobName(DeadLetterJobName),
        ParentKey(Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "DeadLetterJob"
        ))
    {
    }

    FDeadLetterJobDomain::FDeadLetterJobDomain(
        const FDeadLetterJobDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        DeadLetterJobName(From.DeadLetterJobName),
        ParentKey(From.ParentKey)
    {

    }

    FDeadLetterJobDomain::FGetTask::FGetTask(
        const TSharedPtr<FDeadLetterJobDomain>& Self,
        const Request::FGetDeadLetterJobByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDeadLetterJobDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeadLetterJobDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FDeadLetterJob>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDeadLetterJobName(Self->DeadLetterJobName);
        const auto Future = Self->Client->GetDeadLetterJobByUserId(
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
                    "DeadLetterJob"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FDeadLetterJob::TypeName,
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

    TSharedPtr<FAsyncTask<FDeadLetterJobDomain::FGetTask>> FDeadLetterJobDomain::Get(
        Request::FGetDeadLetterJobByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FDeadLetterJobDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FDeadLetterJobDomain>& Self,
        const Request::FDeleteDeadLetterJobByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDeadLetterJobDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeadLetterJobDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithDeadLetterJobName(Self->DeadLetterJobName);
        const auto Future = Self->Client->DeleteDeadLetterJobByUserId(
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
                    "DeadLetterJob"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Delete(Gs2::JobQueue::Model::FDeadLetterJob::TypeName, ParentKey, Key);
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeadLetterJobDomain::FDeleteTask>> FDeadLetterJobDomain::Delete(
        Request::FDeleteDeadLetterJobByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FDeadLetterJobDomain::CreateCacheParentKey(
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

    FString FDeadLetterJobDomain::CreateCacheKey(
        TOptional<FString> DeadLetterJobName
    )
    {
        return FString("") +
            (DeadLetterJobName.IsSet() ? *DeadLetterJobName : "null");
    }

    FDeadLetterJobDomain::FModelTask::FModelTask(
        const TSharedPtr<FDeadLetterJobDomain> Self
    ): Self(Self)
    {

    }

    FDeadLetterJobDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeadLetterJobDomain::FModelTask::Action(
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
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::JobQueue::Request::FGetDeadLetterJobByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                    Self->DeadLetterJobName
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FDeadLetterJob::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "deadLetterJob")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FDeadLetterJob>(
                Self->ParentKey,
                Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain::CreateCacheKey(
                    Self->DeadLetterJobName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeadLetterJobDomain::FModelTask>> FDeadLetterJobDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDeadLetterJobDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FDeadLetterJobDomain::Subscribe(
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

    void FDeadLetterJobDomain::Unsubscribe(
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

