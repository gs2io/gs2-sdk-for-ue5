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

#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/Namespace.h"
#include "AdReward/Domain/Model/User.h"
#include "AdReward/Domain/Model/UserAccessToken.h"
#include "AdReward/Domain/Model/Point.h"
#include "AdReward/Domain/Model/PointAccessToken.h"
#include "AdReward/Model/Cache/Point.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::AdReward::Domain::Model
{

    FPointDomain::FPointDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::AdReward::FGs2AdRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::AdReward::Domain::Model::FUserDomain::CreateCacheParentKey(
            NamespaceName,
            UserId,
            "Point"
        ))
    {
    }

    FPointDomain::FPointDomain(
        const FPointDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FPointDomain::FGetTask::FGetTask(
        const TSharedPtr<FPointDomain>& Self,
        const Request::FGetPointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->GetPointByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::AdReward::Model::Cache::FPointCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FGetTask>> FPointDomain::Get(
        Request::FGetPointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPointDomain::FAcquireTask::FAcquireTask(
        const TSharedPtr<FPointDomain>& Self,
        const Request::FAcquirePointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FAcquireTask::FAcquireTask(
        const FAcquireTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FAcquireTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->AcquirePointByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::AdReward::Model::Cache::FPointCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FAcquireTask>> FPointDomain::Acquire(
        Request::FAcquirePointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAcquireTask>>(this->AsShared(), Request);
    }

    FPointDomain::FConsumeTask::FConsumeTask(
        const TSharedPtr<FPointDomain>& Self,
        const Request::FConsumePointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FConsumeTask::FConsumeTask(
        const FConsumeTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FConsumeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->ConsumePointByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

            if (ResultModel.IsValid() && ResultModel->GetItem() != nullptr)
            {

        if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        Gs2::AdReward::Model::Cache::FPointCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FConsumeTask>> FPointDomain::Consume(
        Request::FConsumePointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FConsumeTask>>(this->AsShared(), Request);
    }

    FPointDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPointDomain>& Self,
        const Request::FDeletePointByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPointDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Domain::Model::FPointDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->DeletePointByUserId(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            const auto Error = Future->GetTask().Error();
            if (Error.IsValid() && Error->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
            {
                *Result = Self;
                return nullptr;
            }
            return Error;
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

              if (!ResultModel.IsValid() || !((ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>())).IsSet())
                  {
                    const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                      Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                      return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
                    }
              Gs2::AdReward::Model::Cache::FPointCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (ResultModel.IsValid() && ResultModel->GetItem().IsValid() ? ResultModel->GetItem()->GetUserId() : TOptional<FString>()),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FDeleteTask>> FPointDomain::Delete(
        Request::FDeletePointByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPointDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FPointDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FPointDomain::FModelTask::FModelTask(
        const TSharedPtr<FPointDomain> Self
    ): Self(Self)
    {

    }

    FPointDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::AdReward::Model::FPoint>> Result
    )
    {
        const auto CacheParentKey = Gs2::AdReward::Model::Cache::FPointCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::AdReward::Model::Cache::FPointCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::AdReward::Model::FPoint::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::AdReward::Model::FPointPtr Value;
                const auto CacheHit = Gs2::AdReward::Model::Cache::FPointCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::AdReward::Model::Cache::FPointCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    TOptional<int32>(),
                    [Self](Gs2::AdReward::Model::FPointPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::AdReward::Request::FGetPointByUserIdRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError()) return Future->GetTask().Error();
                        *OutItem = Future->GetTask().Result();
                        Future->EnsureCompletion();
                        return nullptr;
                    },
                    &Value
                );
                if (Error.IsValid()) return Error;
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FPointDomain::FModelTask>> FPointDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPointDomain::FModelTask>>(this->AsShared());
    }

    void FPointDomain::Invalidate()
    {
        Gs2::AdReward::Model::Cache::FPointCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
    }

    FPointDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FPointDomain>& Self,
        TFunction<void(Gs2::AdReward::Model::FPointPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FPointDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPointDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Task = Self->Model();
        Task->StartSynchronousTask();
        Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Item = Task->GetTask().Result();
        const auto CallbackId = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPointDomain::FSubscribeWithInitialCallTask>> FPointDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::AdReward::Model::FPointPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FPointDomain::Subscribe(
        TFunction<void(Gs2::AdReward::Model::FPointPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::AdReward::Model::Cache::FPointCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::AdReward::Model::Cache::FPointCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<AdReward::Domain::FGs2AdRewardDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        return Gs2->Cache->Subscribe(
            Gs2::AdReward::Model::FPoint::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::AdReward::Model::FPoint>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FPointDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FPointDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::AdReward::Model::Cache::FPointCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::AdReward::Model::Cache::FPointCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::AdReward::Model::FPoint::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
