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

#include "Schedule/Domain/Model/User.h"

// deny overwrite

#include "Schedule/Domain/Model/Namespace.h"
#include "Schedule/Domain/Model/EventMaster.h"
#include "Schedule/Domain/Model/Trigger.h"
#include "Schedule/Domain/Model/TriggerAccessToken.h"
#include "Schedule/Domain/Model/Event.h"
#include "Schedule/Domain/Model/EventAccessToken.h"
#include "Schedule/Domain/Model/User.h"
#include "Schedule/Domain/Model/UserAccessToken.h"
#include "Schedule/Domain/Model/CurrentEventMaster.h"
#include "Schedule/Model/Cache/Trigger.h"
#include "Schedule/Model/Cache/Event.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Schedule::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Schedule::FGs2ScheduleRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::Schedule::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    Gs2::Schedule::Domain::Iterator::FDescribeTriggersByUserIdIteratorPtr FUserDomain::Triggers(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Iterator::FDescribeTriggersByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeTriggers(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            Gs2::Schedule::Model::Cache::FTriggerCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeTriggers(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Schedule::Model::FTrigger::TypeName,
            Gs2::Schedule::Model::Cache::FTriggerCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectTriggersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Schedule::Model::FTriggerPtr>>, public TSharedFromThis<FCollectTriggersTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectTriggersTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectTriggersTask(const FCollectTriggersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Schedule::Model::FTriggerPtr>>> Result) override
        {
            TArray<Gs2::Schedule::Model::FTriggerPtr> Items;
            auto Iterator = Self->Triggers(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Schedule::Model::FTriggerPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeTriggers(
        TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Schedule::Domain::FGs2ScheduleDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Schedule::Model::Cache::FTriggerCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Schedule::Model::FTrigger::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Schedule::Model::FTriggerPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Schedule::Model::FTrigger>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTriggersTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateTriggers(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Schedule::Model::FTrigger::TypeName,
            Gs2::Schedule::Model::Cache::FTriggerCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeTriggersWithInitialCallTask::FSubscribeTriggersWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeTriggersWithInitialCallTask::FSubscribeTriggersWithInitialCallTask(const FSubscribeTriggersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeTriggersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectTriggersTask>>(Self, TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeTriggers(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeTriggersWithInitialCallTask>> FUserDomain::SubscribeTriggersWithInitialCall(TFunction<void(TArray<Gs2::Schedule::Model::FTriggerPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTriggersWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FTriggerDomain> FUserDomain::Trigger(
        const FString TriggerName
    )
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FTriggerDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            TriggerName == TEXT("") ? TOptional<FString>() : TOptional<FString>(TriggerName)
        );
    }

    Gs2::Schedule::Domain::Iterator::FDescribeEventsByUserIdIteratorPtr FUserDomain::Events(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::Schedule::Domain::Iterator::FDescribeEventsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeEvents(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<bool>(true),
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeEvents(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<bool>(true),
                TOptional<int32>()
            ),
            CallbackID
        );
        Gs2->Cache->ListUnsubscribe(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<bool>(false),
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectEventsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Schedule::Model::FEventPtr>>, public TSharedFromThis<FCollectEventsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectEventsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectEventsTask(const FCollectEventsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Schedule::Model::FEventPtr>>> Result) override
        {
            TArray<Gs2::Schedule::Model::FEventPtr> Items;
            auto Iterator = Self->Events(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Schedule::Model::FEventPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeEvents(
        TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Schedule::Domain::FGs2ScheduleDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<bool>(true),
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Schedule::Model::FEvent::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Schedule::Model::FEventPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Schedule::Model::FEvent>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectEventsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateEvents(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<bool>(true),
        TOptional<int32>()
    )
        );
        Gs2->Cache->ClearListCache(
            Gs2::Schedule::Model::FEvent::TypeName,
            Gs2::Schedule::Model::Cache::FEventCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<bool>(false),
                TOptional<int32>()
            )
        );
    }

    FUserDomain::FSubscribeEventsWithInitialCallTask::FSubscribeEventsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeEventsWithInitialCallTask::FSubscribeEventsWithInitialCallTask(const FSubscribeEventsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeEventsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectEventsTask>>(Self, TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeEvents(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeEventsWithInitialCallTask>> FUserDomain::SubscribeEventsWithInitialCall(TFunction<void(TArray<Gs2::Schedule::Model::FEventPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeEventsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::Schedule::Domain::Model::FEventDomain> FUserDomain::Event(
        const FString EventName
    )
    {
        return MakeShared<Gs2::Schedule::Domain::Model::FEventDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            EventName == TEXT("") ? TOptional<FString>() : TOptional<FString>(EventName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
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

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
