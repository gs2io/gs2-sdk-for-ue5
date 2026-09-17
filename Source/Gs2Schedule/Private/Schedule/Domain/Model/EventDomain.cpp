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

#include "Schedule/Domain/Model/Event.h"

// deny overwrite
#include "Schedule/Domain/Model/RepeatSchedule.h"
#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Model/Cache/Event.h"
#include "Schedule/Model/Cache/RepeatSchedule.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FEventDomain::FEventDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId,
        const TOptional<FString> EventName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        EventName(EventName),
        ParentKey(Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
            NamespaceName,
            UserId,
            TOptional<bool>(true),
            TOptional<int32>()
        ))
    {
    }

    FEventDomain::FEventDomain(
        const FEventDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        EventName(From.EventName),
        ParentKey(From.ParentKey)
    {

    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FRepeatScheduleDomain> FEventDomain::RepeatSchedule()
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FRepeatScheduleDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            EventName,
            InSchedule
        );
    }

    FEventDomain::FGetTask::FGetTask(
        const TSharedPtr<FEventDomain>& Self,
        const Request::FGetEventByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEvent>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithEventName(Self->EventName)
            ->WithUserId(Self->UserId)
            ->WithIsInSchedule(Self->InSchedule);
        const auto Future = Self->Client->GetEventByUserId(
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

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
            Gs2::Schedule::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetEventName(),
            TOptional<bool>(Request->GetIsInSchedule().Get(true)),
            TOptional<int32>(),
            ResultModel->GetItem()
            );
            }
        if (ResultModel.IsValid() && ResultModel->GetRepeatSchedule().IsValid())
        {
            Gs2::Schedule::Model::Cache::FRepeatScheduleCache::Put(
                Self->Gs2->Cache,
                Self->NamespaceName,
                Self->UserId,
                Self->InSchedule.Get(true),
                Self->EventName,
                TOptional<int32>(),
                ResultModel->GetRepeatSchedule()
            );
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEventDomain::FGetTask>> FEventDomain::Get(
        Request::FGetEventByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FEventDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FEventDomain>& Self,
        const Request::FVerifyEventByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FEventDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId)
            ->WithEventName(Self->EventName);
        const auto Future = Self->Client->VerifyEventByUserId(
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

        if (!(Request->GetUserId()).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
        if (ResultModel->GetInSchedule().IsSet())
        {
        Gs2::Schedule::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetEventName(),
            TOptional<bool>(false),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
        Gs2::Schedule::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            Request->GetUserId(),
            Request->GetEventName(),
            TOptional<bool>(true),
            TOptional<int32>(),
            *ResultModel->GetInSchedule() ? ResultModel->GetItem() : nullptr
        );
        }
            }
        auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetInSchedule().IsSet())
            {
                Domain->InSchedule = *ResultModel->GetInSchedule();
            }
            if (ResultModel->GetScheduleStartAt().IsSet())
            {
                Domain->ScheduleStartAt = *ResultModel->GetScheduleStartAt();
            }
            if (ResultModel->GetScheduleEndAt().IsSet())
            {
                Domain->ScheduleEndAt = *ResultModel->GetScheduleEndAt();
            }
            if (ResultModel->GetIsGlobalSchedule().IsSet())
            {
                Domain->IsGlobalSchedule = *ResultModel->GetIsGlobalSchedule();
            }
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEventDomain::FVerifyTask>> FEventDomain::Verify(
        Request::FVerifyEventByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FEventDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> EventName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (EventName.IsSet() ? *EventName : "null") + ":" +
            ChildType;
    }

    FString FEventDomain::CreateCacheKey(
        TOptional<FString> EventName
    )
    {
        return FString("") +
            (EventName.IsSet() ? *EventName : "null");
    }

    FEventDomain::FModelTask::FModelTask(
        const TSharedPtr<FEventDomain> Self
    ): Self(Self)
    {

    }

    FEventDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEventDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEvent>> Result
    )
    {
        const auto CacheParentKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->UserId,
            TOptional<bool>(true),
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheKey(

            Self->EventName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Schedule::Model::FEvent::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Schedule::Model::FEventPtr Value;
                const auto CacheHit = Gs2::Schedule::Model::Cache::FEventCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->EventName,
                    TOptional<bool>(true),
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Schedule::Model::Cache::FEventCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->UserId,
                    Self->EventName,
                    TOptional<bool>(true),
                    TOptional<int32>(),
                    [Self](Gs2::Schedule::Model::FEventPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Schedule::Request::FGetEventByUserIdRequest>()
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

    TSharedPtr<FAsyncTask<FEventDomain::FModelTask>> FEventDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEventDomain::FModelTask>>(this->AsShared());
    }

    void FEventDomain::Invalidate()
    {
        Gs2::Schedule::Model::Cache::FEventCache::Delete(
            Gs2->Cache,

            NamespaceName,
            UserId,
            EventName,
            TOptional<int32>()
        );
    }

    FEventDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FEventDomain>& Self,
        TFunction<void(Gs2::Schedule::Model::FEventPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FEventDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FEventDomain::FSubscribeWithInitialCallTask>> FEventDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Schedule::Model::FEventPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FEventDomain::Subscribe(
        TFunction<void(Gs2::Schedule::Model::FEventPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<bool>(true),
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheKey(

            EventName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Schedule::Domain::FGs2ScheduleDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryUserId = UserId;
        const TOptional<FString> QueryEventName = EventName;
        return Gs2->Cache->Subscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Schedule::Model::FEvent>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryUserId, QueryEventName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FEventDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryUserId,
                    QueryEventName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FEventDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(

            NamespaceName,
            UserId,
            TOptional<bool>(true),
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheKey(

            EventName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
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
