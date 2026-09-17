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

#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"
#include "MegaField/Domain/Model/SpatialAccessToken.h"
#include "MegaField/Model/Cache/AreaModelMaster.h"
#include "MegaField/Model/Cache/LayerModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FAreaModelMasterDomain::FAreaModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const MegaField::Domain::FGs2MegaFieldDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> AreaModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AreaModelName(AreaModelName),
        ParentKey(Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "AreaModelMaster"
        ))
    {
    }

    FAreaModelMasterDomain::FAreaModelMasterDomain(
        const FAreaModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AreaModelName(From.AreaModelName),
        ParentKey(From.ParentKey)
    {

    }

    FAreaModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FGetAreaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->GetAreaModelMaster(
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


        Gs2::MegaField::Model::Cache::FAreaModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FGetTask>> FAreaModelMasterDomain::Get(
        Request::FGetAreaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FAreaModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FUpdateAreaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FAreaModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->UpdateAreaModelMaster(
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


        Gs2::MegaField::Model::Cache::FAreaModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FUpdateTask>> FAreaModelMasterDomain::Update(
        Request::FUpdateAreaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FAreaModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FDeleteAreaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FAreaModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->DeleteAreaModelMaster(
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


              Gs2::MegaField::Model::Cache::FAreaModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FDeleteTask>> FAreaModelMasterDomain::Delete(
        Request::FDeleteAreaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FAreaModelMasterDomain::FCreateLayerModelMasterTask::FCreateLayerModelMasterTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        const Request::FCreateLayerModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelMasterDomain::FCreateLayerModelMasterTask::FCreateLayerModelMasterTask(
        const FCreateLayerModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FCreateLayerModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->CreateLayerModelMaster(
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


        Gs2::MegaField::Model::Cache::FLayerModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Request->GetAreaModelName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FCreateLayerModelMasterTask>> FAreaModelMasterDomain::CreateLayerModelMaster(
        Request::FCreateLayerModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateLayerModelMasterTask>>(this->AsShared(), Request);
    }

    Gs2::MegaField::Domain::Iterator::FDescribeLayerModelMastersIteratorPtr FAreaModelMasterDomain::LayerModelMasters(
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            AreaModelName
        );
    }

    Gs2::Core::Domain::CallbackID FAreaModelMasterDomain::SubscribeLayerModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FAreaModelMasterDomain::UnsubscribeLayerModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FAreaModelMasterDomain::FCollectLayerModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>>, public TSharedFromThis<FCollectLayerModelMastersTask>
    {
        const TSharedPtr<FAreaModelMasterDomain> Self;
        const TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>)> OnCollected;

    public:
        explicit FCollectLayerModelMastersTask(const TSharedPtr<FAreaModelMasterDomain>& Self, TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectLayerModelMastersTask(const FCollectLayerModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>>> Result) override
        {
            TArray<Gs2::MegaField::Model::FLayerModelMasterPtr> Items;
            auto Iterator = Self->LayerModelMasters()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FAreaModelMasterDomain::SubscribeLayerModelMasters(
        TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<MegaField::Domain::FGs2MegaFieldDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryAreaModelName = AreaModelName;
        const auto Parent = Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        AreaModelName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::MegaField::Model::FLayerModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::MegaField::Model::FLayerModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryAreaModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FAreaModelMasterDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryAreaModelName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLayerModelMastersTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FAreaModelMasterDomain::InvalidateLayerModelMasters()
    {
        Gs2->Cache->ClearListCache(
            Gs2::MegaField::Model::FLayerModelMaster::TypeName,
            Gs2::MegaField::Model::Cache::FLayerModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        AreaModelName,
        TOptional<int32>()
    )
        );
    }

    FAreaModelMasterDomain::FSubscribeLayerModelMastersWithInitialCallTask::FSubscribeLayerModelMastersWithInitialCallTask(const TSharedPtr<FAreaModelMasterDomain>& Self, TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FAreaModelMasterDomain::FSubscribeLayerModelMastersWithInitialCallTask::FSubscribeLayerModelMastersWithInitialCallTask(const FSubscribeLayerModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FSubscribeLayerModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLayerModelMastersTask>>(Self, TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLayerModelMasters(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FSubscribeLayerModelMastersWithInitialCallTask>> FAreaModelMasterDomain::SubscribeLayerModelMastersWithInitialCall(TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelMasterPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLayerModelMastersWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain> FAreaModelMasterDomain::LayerModelMaster(
        const FString LayerModelName
    )
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FLayerModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            AreaModelName,
            LayerModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LayerModelName)
        );
    }

    FString FAreaModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> AreaModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (AreaModelName.IsSet() ? *AreaModelName : "null") + ":" +
            ChildType;
    }

    FString FAreaModelMasterDomain::CreateCacheKey(
        TOptional<FString> AreaModelName
    )
    {
        return FString("") +
            (AreaModelName.IsSet() ? *AreaModelName : "null");
    }

    FAreaModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FAreaModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FAreaModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::CreateCacheKey(

            Self->AreaModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::MegaField::Model::FAreaModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::MegaField::Model::FAreaModelMasterPtr Value;
                const auto CacheHit = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AreaModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AreaModelName,
                    TOptional<int32>(),
                    [Self](Gs2::MegaField::Model::FAreaModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::MegaField::Request::FGetAreaModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FModelTask>> FAreaModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAreaModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FAreaModelMasterDomain::Invalidate()
    {
        Gs2::MegaField::Model::Cache::FAreaModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AreaModelName,
            TOptional<int32>()
        );
    }

    FAreaModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FAreaModelMasterDomain>& Self,
        TFunction<void(Gs2::MegaField::Model::FAreaModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FAreaModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FAreaModelMasterDomain::FSubscribeWithInitialCallTask>> FAreaModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::MegaField::Model::FAreaModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FAreaModelMasterDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FAreaModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::CreateCacheKey(

            AreaModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<MegaField::Domain::FGs2MegaFieldDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryAreaModelName = AreaModelName;
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FAreaModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FAreaModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryAreaModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FAreaModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryAreaModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FAreaModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::MegaField::Model::Cache::FAreaModelMasterCache::CreateCacheKey(

            AreaModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FAreaModelMaster::TypeName,
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
