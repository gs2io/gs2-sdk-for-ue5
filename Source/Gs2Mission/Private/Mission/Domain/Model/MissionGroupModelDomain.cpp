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

#include "Mission/Domain/Model/MissionGroupModel.h"
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
#include "Mission/Model/Cache/MissionGroupModel.h"
#include "Mission/Model/Cache/MissionTaskModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Mission::Domain::Model
{

    FMissionGroupModelDomain::FMissionGroupModelDomain(
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
            "MissionGroupModel"
        ))
    {
    }

    FMissionGroupModelDomain::FMissionGroupModelDomain(
        const FMissionGroupModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        MissionGroupName(From.MissionGroupName),
        ParentKey(From.ParentKey)
    {

    }

    FMissionGroupModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FMissionGroupModelDomain>& Self,
        const Request::FGetMissionGroupModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FMissionGroupModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithMissionGroupName(Self->MissionGroupName);
        const auto Future = Self->Client->GetMissionGroupModel(
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


        Gs2::Mission::Model::Cache::FMissionGroupModelCache::Put(
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

    TSharedPtr<FAsyncTask<FMissionGroupModelDomain::FGetTask>> FMissionGroupModelDomain::Get(
        Request::FGetMissionGroupModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIteratorPtr FMissionGroupModelDomain::MissionTaskModels(
    ) const
    {
        return MakeShared<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            MissionGroupName
        );
    }

    Gs2::Core::Domain::CallbackID FMissionGroupModelDomain::SubscribeMissionTaskModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(
                NamespaceName,
                MissionGroupName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FMissionGroupModelDomain::UnsubscribeMissionTaskModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(
                NamespaceName,
                MissionGroupName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FMissionGroupModelDomain::FCollectMissionTaskModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Mission::Model::FMissionTaskModelPtr>>, public TSharedFromThis<FCollectMissionTaskModelsTask>
    {
        const TSharedPtr<FMissionGroupModelDomain> Self;
        const TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)> OnCollected;

    public:
        explicit FCollectMissionTaskModelsTask(const TSharedPtr<FMissionGroupModelDomain>& Self, TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectMissionTaskModelsTask(const FCollectMissionTaskModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Mission::Model::FMissionTaskModelPtr>>> Result) override
        {
            TArray<Gs2::Mission::Model::FMissionTaskModelPtr> Items;
            auto Iterator = Self->MissionTaskModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Mission::Model::FMissionTaskModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FMissionGroupModelDomain::SubscribeMissionTaskModels(
        TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Mission::Domain::FGs2MissionDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryMissionGroupName = MissionGroupName;
        const auto Parent = Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(
        NamespaceName,
        MissionGroupName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Mission::Model::FMissionTaskModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Mission::Model::FMissionTaskModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryMissionGroupName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FMissionGroupModelDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryMissionGroupName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMissionTaskModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FMissionGroupModelDomain::InvalidateMissionTaskModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Mission::Model::FMissionTaskModel::TypeName,
            Gs2::Mission::Model::Cache::FMissionTaskModelCache::CreateCacheParentKey(
        NamespaceName,
        MissionGroupName,
        TOptional<int32>()
    )
        );
    }

    FMissionGroupModelDomain::FSubscribeMissionTaskModelsWithInitialCallTask::FSubscribeMissionTaskModelsWithInitialCallTask(const TSharedPtr<FMissionGroupModelDomain>& Self, TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FMissionGroupModelDomain::FSubscribeMissionTaskModelsWithInitialCallTask::FSubscribeMissionTaskModelsWithInitialCallTask(const FSubscribeMissionTaskModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelDomain::FSubscribeMissionTaskModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMissionTaskModelsTask>>(Self, TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMissionTaskModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FMissionGroupModelDomain::FSubscribeMissionTaskModelsWithInitialCallTask>> FMissionGroupModelDomain::SubscribeMissionTaskModelsWithInitialCall(TFunction<void(TArray<Gs2::Mission::Model::FMissionTaskModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMissionTaskModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Mission::Domain::Model::FMissionTaskModelDomain> FMissionGroupModelDomain::MissionTaskModel(
        const FString MissionTaskName
    )
    {
        return MakeShared<Gs2::Mission::Domain::Model::FMissionTaskModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            MissionGroupName,
            MissionTaskName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MissionTaskName)
        );
    }

    FString FMissionGroupModelDomain::CreateCacheParentKey(
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

    FString FMissionGroupModelDomain::CreateCacheKey(
        TOptional<FString> MissionGroupName
    )
    {
        return FString("") +
            (MissionGroupName.IsSet() ? *MissionGroupName : "null");
    }

    FMissionGroupModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FMissionGroupModelDomain> Self
    ): Self(Self)
    {

    }

    FMissionGroupModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Mission::Model::FMissionGroupModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Mission::Model::Cache::FMissionGroupModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Mission::Model::Cache::FMissionGroupModelCache::CreateCacheKey(

            Self->MissionGroupName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Mission::Model::FMissionGroupModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Mission::Model::FMissionGroupModelPtr Value;
                const auto CacheHit = Gs2::Mission::Model::Cache::FMissionGroupModelCache::TryGet(
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
                const auto Error = Gs2::Mission::Model::Cache::FMissionGroupModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->MissionGroupName,
                    TOptional<int32>(),
                    [Self](Gs2::Mission::Model::FMissionGroupModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Mission::Request::FGetMissionGroupModelRequest>()
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

    TSharedPtr<FAsyncTask<FMissionGroupModelDomain::FModelTask>> FMissionGroupModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FMissionGroupModelDomain::FModelTask>>(this->AsShared());
    }

    void FMissionGroupModelDomain::Invalidate()
    {
        Gs2::Mission::Model::Cache::FMissionGroupModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            MissionGroupName,
            TOptional<int32>()
        );
    }

    FMissionGroupModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FMissionGroupModelDomain>& Self,
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FMissionGroupModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FMissionGroupModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FMissionGroupModelDomain::FSubscribeWithInitialCallTask>> FMissionGroupModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FMissionGroupModelDomain::Subscribe(
        TFunction<void(Gs2::Mission::Model::FMissionGroupModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionGroupModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionGroupModelCache::CreateCacheKey(

            MissionGroupName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Mission::Domain::FGs2MissionDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryMissionGroupName = MissionGroupName;
        return Gs2->Cache->Subscribe(
            Gs2::Mission::Model::FMissionGroupModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Mission::Model::FMissionGroupModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryMissionGroupName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FMissionGroupModelDomain>(
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

    void FMissionGroupModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Mission::Model::Cache::FMissionGroupModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Mission::Model::Cache::FMissionGroupModelCache::CreateCacheKey(

            MissionGroupName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Mission::Model::FMissionGroupModel::TypeName,
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
