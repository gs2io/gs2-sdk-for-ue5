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

#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Stack.h"
#include "Deploy/Domain/Model/Resource.h"
#include "Deploy/Domain/Model/Event.h"
#include "Deploy/Domain/Model/Output.h"
#include "Deploy/Model/Cache/Event.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Deploy::Domain::Model
{

    FEventDomain::FEventDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Deploy::Domain::FGs2DeployDomainPtr& Service,
        const TOptional<FString> StackName,
        const TOptional<FString> EventName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Deploy::FGs2DeployRestClient>(Gs2->RestSession)),
        StackName(StackName),
        EventName(EventName),
        ParentKey(Gs2::Deploy::Domain::Model::FStackDomain::CreateCacheParentKey(
            StackName,
            "Event"
        ))
    {
    }

    FEventDomain::FEventDomain(
        const FEventDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        StackName(From.StackName),
        EventName(From.EventName),
        ParentKey(From.ParentKey)
    {

    }

    FEventDomain::FGetTask::FGetTask(
        const TSharedPtr<FEventDomain>& Self,
        const Request::FGetEventRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FEventDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEventDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FEvent>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithStackName(Self->StackName)
            ->WithEventName(Self->EventName);
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


        Gs2::Deploy::Model::Cache::FEventCache::Put(
            Self->Gs2->Cache,

            Request->GetStackName(),
            Request->GetEventName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEventDomain::FGetTask>> FEventDomain::Get(
        Request::FGetEventRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FEventDomain::CreateCacheParentKey(
        TOptional<FString> StackName,
        TOptional<FString> EventName,
        FString ChildType
    )
    {
        return FString("") +
            (StackName.IsSet() ? *StackName : "null") + ":" +
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
        TSharedPtr<TSharedPtr<Gs2::Deploy::Model::FEvent>> Result
    )
    {
        const auto CacheParentKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheParentKey(

            Self->StackName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheKey(

            Self->EventName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Deploy::Model::FEvent::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Deploy::Model::FEventPtr Value;
                const auto CacheHit = Gs2::Deploy::Model::Cache::FEventCache::TryGet(
                    Self->Gs2->Cache,

                    Self->StackName,
                    Self->EventName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Deploy::Model::Cache::FEventCache::Fetch(
                    Self->Gs2->Cache,

                    Self->StackName,
                    Self->EventName,
                    TOptional<int32>(),
                    [Self](Gs2::Deploy::Model::FEventPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Deploy::Request::FGetEventRequest>()
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
        Gs2::Deploy::Model::Cache::FEventCache::Delete(
            Gs2->Cache,

            StackName,
            EventName,
            TOptional<int32>()
        );
    }

    FEventDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FEventDomain>& Self,
        TFunction<void(Gs2::Deploy::Model::FEventPtr)> Callback
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
        TFunction<void(Gs2::Deploy::Model::FEventPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FEventDomain::Subscribe(
        TFunction<void(Gs2::Deploy::Model::FEventPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheParentKey(

            StackName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheKey(

            EventName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Deploy::Domain::FGs2DeployDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryStackName = StackName;
        const TOptional<FString> QueryEventName = EventName;
        return Gs2->Cache->Subscribe(
            Gs2::Deploy::Model::FEvent::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Deploy::Model::FEvent>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryStackName, QueryEventName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FEventDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryStackName,
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
        const auto SubscriptionParentKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheParentKey(

            StackName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Deploy::Model::Cache::FEventCache::CreateCacheKey(

            EventName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Deploy::Model::FEvent::TypeName,
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
