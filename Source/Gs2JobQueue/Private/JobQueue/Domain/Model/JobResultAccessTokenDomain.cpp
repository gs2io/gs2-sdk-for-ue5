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

#include "JobQueue/Domain/Model/JobResultAccessToken.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FJobResultAccessTokenDomain::FJobResultAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> JobName,
        const TOptional<int32> TryNumber
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        JobName(JobName),
        TryNumber(TryNumber),
        ParentKey(FJobResultDomain::CreateResultCacheParentKey(NamespaceName, UserId(), JobName, AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()))
    {
    }

    FJobResultAccessTokenDomain::FJobResultAccessTokenDomain(
        const FJobResultAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        JobName(From.JobName),
        TryNumber(From.TryNumber),
        ParentKey(From.ParentKey)
    {

    }

    FJobResultAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FJobResultAccessTokenDomain>& Self,
        const Request::FGetJobResultRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FJobResultAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        if (!Self->AccessToken.IsValid() || !Self->AccessToken->GetUserId().IsSet())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Request
            ->WithContextStack(Request->GetContextStack().IsSet() && !Request->GetContextStack()->IsEmpty() ? Request->GetContextStack() : Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithJobName(Self->JobName)
            ->WithTryNumber(Self->TryNumber);
        const auto Future = Self->Client->GetJobResult(
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
                const auto ParentKey = FJobResultDomain::CreateResultCacheParentKey(Self->NamespaceName, Self->UserId(), Self->JobName, Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>());
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

    TSharedPtr<FAsyncTask<FJobResultAccessTokenDomain::FGetTask>> FJobResultAccessTokenDomain::Get(
        Request::FGetJobResultRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FJobResultAccessTokenDomain::CreateCacheParentKey(
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

    FString FJobResultAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TryNumber
    )
    {
        return FString("") +
            (TryNumber.IsSet() ? *TryNumber : "null");
    }

    FJobResultAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FJobResultAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FJobResultAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        if (!Self->AccessToken.IsValid() || !Self->AccessToken->GetUserId().IsSet())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const FString CacheParentKey = FJobResultDomain::CreateResultCacheParentKey(Self->NamespaceName, Self->UserId(), Self->JobName, Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>());
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
                        MakeShared<Gs2::JobQueue::Request::FGetJobResultRequest>()
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

    TSharedPtr<FAsyncTask<FJobResultAccessTokenDomain::FModelTask>> FJobResultAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FJobResultAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FJobResultAccessTokenDomain::FModelNoCacheTask::FModelNoCacheTask(
        const TSharedPtr<FJobResultAccessTokenDomain> Self
    ): Self(Self)
    {
    }

    FJobResultAccessTokenDomain::FModelNoCacheTask::FModelNoCacheTask(
        const FModelNoCacheTask& From
    ): TGs2Future(From), Self(From.Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultAccessTokenDomain::FModelNoCacheTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Model::FJobResult>> Result
    )
    {
        if (!Self->AccessToken.IsValid() || !Self->AccessToken->GetUserId().IsSet())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const FString CacheParentKey = FJobResultDomain::CreateResultCacheParentKey(Self->NamespaceName, Self->UserId(), Self->JobName, Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>());
        const auto Key = FJobResultDomain::CreateCacheKey(FString::FromInt(Self->TryNumber.Get(0)));
        const auto Future = Self->Get(MakeShared<Gs2::JobQueue::Request::FGetJobResultRequest>());
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

    TSharedPtr<FAsyncTask<FJobResultAccessTokenDomain::FModelNoCacheTask>> FJobResultAccessTokenDomain::ModelNoCache()
    {
        return Gs2::Core::Util::New<FAsyncTask<FJobResultAccessTokenDomain::FModelNoCacheTask>>(this->AsShared());
    }

    FJobResultAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FJobResultAccessTokenDomain> Self,
        const TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FJobResultAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FJobResultAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FJobResultAccessTokenDomain::FSubscribeWithInitialCallTask>> FJobResultAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FJobResultAccessTokenDomain::Invalidate()
    {
        const auto SourceToken = AccessToken;
        Gs2::JobQueue::Model::Cache::FJobResultCache::Delete(
            Gs2->Cache,
            NamespaceName,
            SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
            JobName,
            TOptional<int32>(TryNumber.Get(0)),
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FJobResultAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::JobQueue::Model::FJobResultPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Gs2::JobQueue::Domain::FGs2JobQueueDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryJobName = JobName;
        const TOptional<int32> QueryTryNumber = TryNumber;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto RegisteredParentKey = Gs2::JobQueue::Domain::Model::FJobResultDomain::CreateResultCacheParentKey(
            QueryNamespaceName,
            RegisteredUserId,
            QueryJobName,
            RegisteredTimeOffset
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
            [WeakGs2, WeakService, QueryNamespaceName, QueryJobName, QueryTryNumber, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FJobResultAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryJobName,
                    QueryTryNumber
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FJobResultAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::JobQueue::Model::FJobResult::TypeName,
            FJobResultDomain::CreateResultCacheParentKey(NamespaceName, UserId(), JobName, AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()),
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

