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
#include "JobQueue/Model/Cache/JobResult.h"

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
        ParentKey(FJobResultDomain::CreateResultCacheParentKey(NamespaceName, UserId, JobName))
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
        if (!Self->UserId.IsSet())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Request
            ->WithContextStack(Request->GetContextStack().IsSet() && !Request->GetContextStack()->IsEmpty() ? Request->GetContextStack() : Self->Gs2->DefaultContextStack)
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
                const auto ParentKey = FJobResultDomain::CreateResultCacheParentKey(Self->NamespaceName, Self->UserId, Self->JobName);
                const auto Key = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                    FString::FromInt(ResultModel->GetItem()->GetTryNumber().Get(0))
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
        *Result = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
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

    FString FJobResultDomain::CreateResultCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> JobName,
        TOptional<int32> TimeOffset
    )
    {
        return FString("jobQueue:") + NamespaceName.Get(FString()) + ":" + UserId.Get(FString()) + ":" + JobName.Get(FString()) + ":" + FString::FromInt(TimeOffset.Get(0)) + ":JobResult";
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
        if (!Self->UserId.IsSet())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const FString CacheParentKey = FJobResultDomain::CreateResultCacheParentKey(Self->NamespaceName, Self->UserId, Self->JobName);
        const FString CacheKey = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
            FString::FromInt(Self->TryNumber.Get(0))
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheKey, CacheParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::JobQueue::Model::FJobResult> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::JobQueue::Model::FJobResult>(
                    CacheParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::JobQueue::Request::FGetJobResultByUserIdRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::JobQueue::Model::FJobResult::TypeName,
                            CacheParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "jobResult")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::JobQueue::Model::FJobResult::TypeName,
                        CacheParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::JobQueue::Model::FJobResult::TypeName,
                            CacheParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
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
        if (!Self->UserId.IsSet())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const FString CacheParentKey = FJobResultDomain::CreateResultCacheParentKey(Self->NamespaceName, Self->UserId, Self->JobName);
        const auto Key = FJobResultDomain::CreateCacheKey(FString::FromInt(Self->TryNumber.Get(0)));
        const auto Future = Self->Get(MakeShared<Gs2::JobQueue::Request::FGetJobResultByUserIdRequest>());
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        TSharedPtr<Gs2::JobQueue::Model::FJobResult> Value;
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString) return Error;
            Self->Gs2->Cache->Put(Gs2::JobQueue::Model::FJobResult::TypeName, CacheParentKey, Key, nullptr,
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes));
            if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "jobResult") return Error;
        }
        else
        {
            Value = Future->GetTask().Result();
            FGs2ObjectPtr ExistingObject;
            const bool Existing = Value.IsValid() && Self->Gs2->Cache->TryGet(Gs2::JobQueue::Model::FJobResult::TypeName, CacheParentKey, Key, &ExistingObject);
            if (!Value.IsValid() || !Existing || ExistingObject != Value)
            {
                Self->Gs2->Cache->Put(Gs2::JobQueue::Model::FJobResult::TypeName, CacheParentKey, Key, Value,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes));
            }
        }
        *Result = Value;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobResultDomain::FModelNoCacheTask>> FJobResultDomain::ModelNoCache()
    {
        return Gs2::Core::Util::New<FAsyncTask<FJobResultDomain::FModelNoCacheTask>>(this->AsShared());
    }

    FJobResultDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FJobResultDomain> Self,
        const TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FJobResultDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FJobResultDomain::FSubscribeWithInitialCallTask>> FJobResultDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FJobResultDomain::Invalidate()
    {
        Gs2::JobQueue::Model::Cache::FJobResultCache::Delete(
            Gs2->Cache,
            NamespaceName,
            UserId,
            JobName,
            TOptional<int32>(TryNumber.Get(0)),
            TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FJobResultDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Gs2::JobQueue::Domain::FGs2JobQueueDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryJobName = JobName;
        const TOptional<int32> QueryTryNumber = TryNumber;
        const auto RegisteredParentKey = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateResultCacheParentKey(
            QueryNamespaceName,
            QueryUserId,
            QueryJobName,
            TOptional<int32>()
        );
        const auto RegisteredCacheKey = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
            FString::FromInt(QueryTryNumber.Get(0))
        );
        return Gs2->Cache->Subscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            RegisteredParentKey,
            RegisteredCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::JobQueue::Model::FJobResult>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryUserId, QueryJobName, QueryTryNumber]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !QueryUserId.IsSet())
                {
                    return;
                }
                const auto Domain = MakeShared<FJobResultDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryJobName,
                    QueryTryNumber
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FJobResultDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            FJobResultDomain::CreateResultCacheParentKey(NamespaceName, UserId, JobName),
            Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateCacheKey(
                FString::FromInt(TryNumber.Get(0))
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
