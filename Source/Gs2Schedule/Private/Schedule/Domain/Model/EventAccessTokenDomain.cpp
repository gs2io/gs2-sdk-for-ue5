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

#include "Schedule/Domain/Model/EventAccessToken.h"

// deny overwrite

#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/RepeatScheduleAccessToken.h"
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
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FEventAccessTokenDomain::FEventAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> EventName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        EventName(EventName),
        ParentKey(Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            TOptional<bool>(true),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        ))
    {
    }

    FEventAccessTokenDomain::FEventAccessTokenDomain(
        const FEventAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        EventName(From.EventName),
        ParentKey(From.ParentKey)
    {

    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FRepeatScheduleAccessTokenDomain> FEventAccessTokenDomain::RepeatSchedule()
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FRepeatScheduleAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken,
            EventName,
            InSchedule
        );
    }

    FEventAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FEventAccessTokenDomain>& Self,
        const Request::FGetEventRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEvent>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithEventName(Self->EventName)
            ->WithIsInSchedule(Self->InSchedule)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetEvent(
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

        if (!((CacheOwnerSnapshotUserId)).IsSet())
            {
              const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
              }
            Gs2::Schedule::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            Request->GetEventName(),
            TOptional<bool>(Request->GetIsInSchedule().Get(true)),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
            );
            }
        if (ResultModel.IsValid() && ResultModel->GetRepeatSchedule().IsValid())
        {
            Gs2::Schedule::Model::Cache::FRepeatScheduleCache::Put(
                Self->Gs2->Cache,
                Self->NamespaceName,
                CacheOwnerSnapshotUserId,
                Self->InSchedule.Get(true),
                Self->EventName,
                CacheOwnerSnapshotTimeOffset,
                ResultModel->GetRepeatSchedule()
            );
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEventAccessTokenDomain::FGetTask>> FEventAccessTokenDomain::Get(
        Request::FGetEventRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FEventAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FEventAccessTokenDomain>& Self,
        const Request::FVerifyEventRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Domain::Model::FEventAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithEventName(Self->EventName);
        const auto CacheOwnerSnapshotUserId = Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>();
        const auto CacheOwnerSnapshotTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->VerifyEvent(
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

        if (!((CacheOwnerSnapshotUserId)).IsSet())
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
            (CacheOwnerSnapshotUserId),
            Request->GetEventName(),
            TOptional<bool>(false),
            CacheOwnerSnapshotTimeOffset,
            ResultModel->GetItem()
        );
        Gs2::Schedule::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,
            Request->GetNamespaceName(),
            (CacheOwnerSnapshotUserId),
            Request->GetEventName(),
            TOptional<bool>(true),
            CacheOwnerSnapshotTimeOffset,
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

    TSharedPtr<FAsyncTask<FEventAccessTokenDomain::FVerifyTask>> FEventAccessTokenDomain::Verify(
        Request::FVerifyEventRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FEventAccessTokenDomain::CreateCacheParentKey(
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

    FString FEventAccessTokenDomain::CreateCacheKey(
        TOptional<FString> EventName
    )
    {
        return FString("") +
            (EventName.IsSet() ? *EventName : "null");
    }

    FEventAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FEventAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FEventAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEventAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Schedule::Model::FEvent>> Result
    )
    {
        const auto CacheParentKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            TOptional<bool>(true),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
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
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->EventName,
                    TOptional<bool>(true),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
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
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->EventName,
                    TOptional<bool>(true),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self](Gs2::Schedule::Model::FEventPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Schedule::Request::FGetEventRequest>()
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

    TSharedPtr<FAsyncTask<FEventAccessTokenDomain::FModelTask>> FEventAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FEventAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    void FEventAccessTokenDomain::Invalidate()
    {
        Gs2::Schedule::Model::Cache::FEventCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            EventName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    FEventAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FEventAccessTokenDomain>& Self,
        TFunction<void(Gs2::Schedule::Model::FEventPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FEventAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FEventAccessTokenDomain::FSubscribeWithInitialCallTask>> FEventAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Schedule::Model::FEventPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FEventAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Schedule::Model::FEventPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            TOptional<bool>(true),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheKey(

            EventName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Schedule::Domain::FGs2ScheduleDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryEventName = EventName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        return Gs2->Cache->Subscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Schedule::Model::FEvent>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryEventName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FEventAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryEventName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FEventAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            TOptional<bool>(true),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
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
