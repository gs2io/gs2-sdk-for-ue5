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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::JobQueue::Domain::Model
{

    FJobResultDomain::FJobResultDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> JobName,
        const TOptional<int32> TryNumber
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        JobName(JobName),
        TryNumber(TryNumber),
        ParentKey(Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            JobName,
            "JobResult"
        ))
    {
    }

    FJobResultDomain::FJobResultDomain(
        const FJobResultDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        JobName(From.JobName),
        TryNumber(From.TryNumber),
        ParentKey(From.ParentKey)
    {

    }

    FJobResultDomain::FGetTask::FGetTask(
        const TSharedPtr<FJobResultDomain>& Self,
        const Request::FGetJobResultByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJobResultDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithJobName(Self->JobName)
            ->WithTryNumber(Self->TryNumber);
        const auto Future = Self->Client->GetJobResultByUserId(
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
                const auto ParentKey = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    Self->JobName,
                    "JobResult"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetTryNumber().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetTryNumber()) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FJobResult::TypeName,
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

    TSharedPtr<FAsyncTask<FJobResultDomain::FGetTask>> FJobResultDomain::Get(
        Request::FGetJobResultByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FJobResultDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> JobName,
        TOptional<FString> TryNumber,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (JobName.IsSet() ? *JobName : "null") + ":" +
            (TryNumber.IsSet() ? *TryNumber : "null") + ":" +
            ChildType;
    }

    FString FJobResultDomain::CreateCacheKey(
        TOptional<FString> TryNumber
    )
    {
        return FString("") +
            (TryNumber.IsSet() ? *TryNumber : "null");
    }

    FJobResultDomain::FModelTask::FModelTask(
        const TSharedPtr<FJobResultDomain> Self
    ): Self(Self)
    {

    }

    FJobResultDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::JobQueue::Model::FJobResult> Value;
        auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FJobResult>(
            Self->ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::JobQueue::Request::FGetJobResultByUserIdRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FJobResult::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "jobResult")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FJobResult>(
                Self->ParentKey,
                Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobResultDomain::FModelTask>> FJobResultDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJobResultDomain::FModelTask>>(this->AsShared());
    }

    FJobResultDomain::FModelNoCacheTask::FModelNoCacheTask(
        const TSharedPtr<FJobResultDomain> Self
    ):
        Self(Self)
    {
    }

    FJobResultDomain::FModelNoCacheTask::FModelNoCacheTask(
        const FModelNoCacheTask& From
    ):
        Self(From.Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultDomain::FModelNoCacheTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        TSharedPtr<Gs2::JobQueue::Model::FJobResult> Value;
        const auto Future = Self->Get(
            MakeShared<Gs2::JobQueue::Request::FGetJobResultByUserIdRequest>()
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
            {
                return Future->GetTask().Error();
            }

            const auto Key = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
            );
            Self->Gs2->Cache->Put(
                Gs2::JobQueue::Model::FJobResult::TypeName,
                Self->ParentKey,
                Key,
                nullptr,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );

            if (Future->GetTask().Error()->Detail(0)->GetComponent() != "jobResult")
            {
                return Future->GetTask().Error();
            }
        }
        Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FJobResult>(
            Self->ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                Self->TryNumber.IsSet() ? FString::FromInt(*Self->TryNumber) : TOptional<FString>()
            ),
            &Value
        );
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobResultDomain::FModelNoCacheTask>> FJobResultDomain::ModelNoCache()
    {
        return Gs2::Core::Util::New<FAsyncTask<FJobResultDomain::FModelNoCacheTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FJobResultDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
    )
    {
        return Gs2->Cache->Subscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                TryNumber.IsSet() ? FString::FromInt(*TryNumber) : TOptional<FString>()
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::JobQueue::Model::FJobResult>(obj));
            }
        );
    }

    void FJobResultDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            ParentKey,
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                TryNumber.IsSet() ? FString::FromInt(*TryNumber) : TOptional<FString>()
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

