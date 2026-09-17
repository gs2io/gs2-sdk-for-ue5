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

#include "MegaField/Domain/Model/AreaModel.h"
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
#include "MegaField/Model/Cache/AreaModel.h"
#include "MegaField/Model/Cache/LayerModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::MegaField::Domain::Model
{

    FAreaModelDomain::FAreaModelDomain(
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
            "AreaModel"
        ))
    {
    }

    FAreaModelDomain::FAreaModelDomain(
        const FAreaModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AreaModelName(From.AreaModelName),
        ParentKey(From.ParentKey)
    {

    }

    FAreaModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FAreaModelDomain>& Self,
        const Request::FGetAreaModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAreaModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAreaModelName(Self->AreaModelName);
        const auto Future = Self->Client->GetAreaModel(
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


        Gs2::MegaField::Model::Cache::FAreaModelCache::Put(
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

    TSharedPtr<FAsyncTask<FAreaModelDomain::FGetTask>> FAreaModelDomain::Get(
        Request::FGetAreaModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIteratorPtr FAreaModelDomain::LayerModels(
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator>(
            Gs2,
            Client,
            NamespaceName,
            AreaModelName
        );
    }

    Gs2::Core::Domain::CallbackID FAreaModelDomain::SubscribeLayerModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::MegaField::Model::FLayerModel::TypeName,
            Gs2::MegaField::Model::Cache::FLayerModelCache::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FAreaModelDomain::UnsubscribeLayerModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::MegaField::Model::FLayerModel::TypeName,
            Gs2::MegaField::Model::Cache::FLayerModelCache::CreateCacheParentKey(
                NamespaceName,
                AreaModelName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FAreaModelDomain::FCollectLayerModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::MegaField::Model::FLayerModelPtr>>, public TSharedFromThis<FCollectLayerModelsTask>
    {
        const TSharedPtr<FAreaModelDomain> Self;
        const TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)> OnCollected;

    public:
        explicit FCollectLayerModelsTask(const TSharedPtr<FAreaModelDomain>& Self, TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectLayerModelsTask(const FCollectLayerModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::MegaField::Model::FLayerModelPtr>>> Result) override
        {
            TArray<Gs2::MegaField::Model::FLayerModelPtr> Items;
            auto Iterator = Self->LayerModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::MegaField::Model::FLayerModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FAreaModelDomain::SubscribeLayerModels(
        TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<MegaField::Domain::FGs2MegaFieldDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryAreaModelName = AreaModelName;
        const auto Parent = Gs2::MegaField::Model::Cache::FLayerModelCache::CreateCacheParentKey(
        NamespaceName,
        AreaModelName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::MegaField::Model::FLayerModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::MegaField::Model::FLayerModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::MegaField::Model::FLayerModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryAreaModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FAreaModelDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryAreaModelName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLayerModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FAreaModelDomain::InvalidateLayerModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::MegaField::Model::FLayerModel::TypeName,
            Gs2::MegaField::Model::Cache::FLayerModelCache::CreateCacheParentKey(
        NamespaceName,
        AreaModelName,
        TOptional<int32>()
    )
        );
    }

    FAreaModelDomain::FSubscribeLayerModelsWithInitialCallTask::FSubscribeLayerModelsWithInitialCallTask(const TSharedPtr<FAreaModelDomain>& Self, TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FAreaModelDomain::FSubscribeLayerModelsWithInitialCallTask::FSubscribeLayerModelsWithInitialCallTask(const FSubscribeLayerModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FSubscribeLayerModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectLayerModelsTask>>(Self, TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeLayerModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FAreaModelDomain::FSubscribeLayerModelsWithInitialCallTask>> FAreaModelDomain::SubscribeLayerModelsWithInitialCall(TFunction<void(TArray<Gs2::MegaField::Model::FLayerModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeLayerModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FLayerModelDomain> FAreaModelDomain::LayerModel(
        const FString LayerModelName
    )
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FLayerModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            AreaModelName,
            LayerModelName == TEXT("") ? TOptional<FString>() : TOptional<FString>(LayerModelName)
        );
    }

    FString FAreaModelDomain::CreateCacheParentKey(
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

    FString FAreaModelDomain::CreateCacheKey(
        TOptional<FString> AreaModelName
    )
    {
        return FString("") +
            (AreaModelName.IsSet() ? *AreaModelName : "null");
    }

    FAreaModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FAreaModelDomain> Self
    ): Self(Self)
    {

    }

    FAreaModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Model::FAreaModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::MegaField::Model::Cache::FAreaModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::MegaField::Model::Cache::FAreaModelCache::CreateCacheKey(

            Self->AreaModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::MegaField::Model::FAreaModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::MegaField::Model::FAreaModelPtr Value;
                const auto CacheHit = Gs2::MegaField::Model::Cache::FAreaModelCache::TryGet(
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
                const auto Error = Gs2::MegaField::Model::Cache::FAreaModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AreaModelName,
                    TOptional<int32>(),
                    [Self](Gs2::MegaField::Model::FAreaModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::MegaField::Request::FGetAreaModelRequest>()
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

    TSharedPtr<FAsyncTask<FAreaModelDomain::FModelTask>> FAreaModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAreaModelDomain::FModelTask>>(this->AsShared());
    }

    void FAreaModelDomain::Invalidate()
    {
        Gs2::MegaField::Model::Cache::FAreaModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            AreaModelName,
            TOptional<int32>()
        );
    }

    FAreaModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FAreaModelDomain>& Self,
        TFunction<void(Gs2::MegaField::Model::FAreaModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FAreaModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAreaModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FAreaModelDomain::FSubscribeWithInitialCallTask>> FAreaModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::MegaField::Model::FAreaModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FAreaModelDomain::Subscribe(
        TFunction<void(Gs2::MegaField::Model::FAreaModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::MegaField::Model::Cache::FAreaModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::MegaField::Model::Cache::FAreaModelCache::CreateCacheKey(

            AreaModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<MegaField::Domain::FGs2MegaFieldDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryAreaModelName = AreaModelName;
        return Gs2->Cache->Subscribe(
            Gs2::MegaField::Model::FAreaModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::MegaField::Model::FAreaModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryAreaModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FAreaModelDomain>(
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

    void FAreaModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::MegaField::Model::Cache::FAreaModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::MegaField::Model::Cache::FAreaModelCache::CreateCacheKey(

            AreaModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::MegaField::Model::FAreaModel::TypeName,
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
