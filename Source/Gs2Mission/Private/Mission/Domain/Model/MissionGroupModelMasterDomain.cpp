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

#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Complete.h"
#include "Mission/Domain/Model/CompleteAccessToken.h"
#include "Mission/Domain/Model/CounterModelMaster.h"
#include "Mission/Domain/Model/MissionGroupModelMaster.h"
#include "Mission/Domain/Model/Namespace.h"
#include "Mission/Domain/Model/Counter.h"
#include "Mission/Domain/Model/CounterAccessToken.h"
#include "Mission/Domain/Model/CurrentMissionMaster.h"
#include "Mission/Domain/Model/CounterModel.h"
#include "Mission/Domain/Model/MissionGroupModel.h"
#include "Mission/Domain/Model/MissionTaskModel.h"
#include "Mission/Domain/Model/MissionTaskModelMaster.h"
#include "Mission/Domain/Model/User.h"
#include "Mission/Domain/Model/UserAccessToken.h"
#include "Mission/Model/Cache/MissionGroupModelMaster.h"
#include "Mission/Model/Cache/MissionTaskModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FMissionGroupModelMasterDomain::FMissionGroupModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Mission::Domain::FGs2MissionDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> MissionGroupName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Mission::FGs2MissionRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        MissionGroupName(MissionGroupName),
        ParentKey(Gs2::Mission::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "MissionGroupModelMaster"
        ))
    {
    }

    FMissionGroupModelMasterDomain::FMissionGroupModelMasterDomain(
        const FMissionGroupModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MissionGroupName(From.MissionGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FMissionGroupModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FGetMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->GetMissionGroupModelMaster(
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


        Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FGetTask>> FMissionGroupModelMasterDomain::Get(
        Request::FGetMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FMissionGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FUpdateMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->UpdateMissionGroupModelMaster(
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


        Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FUpdateTask>> FMissionGroupModelMasterDomain::Update(
        Request::FUpdateMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FMissionGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FDeleteMissionGroupModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionGroupModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->DeleteMissionGroupModelMaster(
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


              Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FDeleteTask>> FMissionGroupModelMasterDomain::Delete(
        Request::FDeleteMissionGroupModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask::FCreateMissionTaskModelMasterTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        const Request::FCreateMissionTaskModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask::FCreateMissionTaskModelMasterTask(
        const FCreateMissionTaskModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->CreateMissionTaskModelMaster(
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


        Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetMissionGroupName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FCreateMissionTaskModelMasterTask>> FMissionGroupModelMasterDomain::CreateMissionTaskModelMaster(
        Request::FCreateMissionTaskModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateMissionTaskModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelMastersIteratorPtr FMissionGroupModelMasterDomain::MissionTaskModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            MissionGroupName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FMissionGroupModelMasterDomain::SubscribeMissionTaskModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                MissionGroupName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FMissionGroupModelMasterDomain::UnsubscribeMissionTaskModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                MissionGroupName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FMissionGroupModelMasterDomain::FCollectMissionTaskModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>>, public TSharedFromThis<FCollectMissionTaskModelMastersTask>
    {
        const TSharedPtr<FMissionGroupModelMasterDomain> Self;
        const TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectMissionTaskModelMastersTask(const TSharedPtr<FMissionGroupModelMasterDomain>& Self, TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectMissionTaskModelMastersTask(const FCollectMissionTaskModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr> Items;
            auto Iterator = Self->MissionTaskModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FMissionGroupModelMasterDomain::SubscribeMissionTaskModelMasters(
        TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Mission::Domain::FGs2MissionDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryMissionGroupName = MissionGroupName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        MissionGroupName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Mission::Model::FMissionTaskModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryMissionGroupName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FMissionGroupModelMasterDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryMissionGroupName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMissionTaskModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FMissionGroupModelMasterDomain::InvalidateMissionTaskModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Mission::Model::FMissionTaskModelMaster::TypeName,
            Gs2::Mission::Model::Cache::FMissionTaskModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        MissionGroupName,
        TOptional<int32>()
    )
        );
    }

    FMissionGroupModelMasterDomain::FSubscribeMissionTaskModelMastersWithInitialCallTask::FSubscribeMissionTaskModelMastersWithInitialCallTask(const TSharedPtr<FMissionGroupModelMasterDomain>& Self, TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FMissionGroupModelMasterDomain::FSubscribeMissionTaskModelMastersWithInitialCallTask::FSubscribeMissionTaskModelMastersWithInitialCallTask(const FSubscribeMissionTaskModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FSubscribeMissionTaskModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMissionTaskModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMissionTaskModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FSubscribeMissionTaskModelMastersWithInitialCallTask>> FMissionGroupModelMasterDomain::SubscribeMissionTaskModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMissionTaskModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain> FMissionGroupModelMasterDomain::MissionTaskModelMaster(
        const FString MissionTaskName
    )
    {
        return MakeShared<Gs2::Mission::Domain::Model::FMissionTaskModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            MissionGroupName,
            MissionTaskName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MissionTaskName)
        );
    }

    FString FMissionGroupModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> MissionGroupName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null") + ":" +
            ChildType;
    }

    FString FMissionGroupModelMasterDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString("") +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FMissionGroupModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionGroupModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FMissionGroupModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::CreateCacheKey(

            Self->MissionGroupName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Mission::Model::FMissionGroupModelMasterPtr Value;
                const auto CacheHit = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    TOptional<int32>(),
                    [Self](Gs2::Mission::Model::FMissionGroupModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Mission::Request::FGetMissionGroupModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FModelTask>> FMissionGroupModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionGroupModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FMissionGroupModelMasterDomain::Invalidate()
    {
        Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            MissionGroupName,
            TOptional<int32>()
        );
    }

    FMissionGroupModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMissionGroupModelMasterDomain>& Self,
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMissionGroupModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMissionGroupModelMasterDomain::FSubscribeWithInitialCallTask>> FMissionGroupModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMissionGroupModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::CreateCacheKey(

            MissionGroupName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Mission::Domain::FGs2MissionDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryMissionGroupName = MissionGroupName;
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FMissionGroupModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryMissionGroupName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMissionGroupModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryMissionGroupName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FMissionGroupModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionGroupModelMasterCache::CreateCacheKey(

            MissionGroupName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FMissionGroupModelMaster::TypeName,
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
