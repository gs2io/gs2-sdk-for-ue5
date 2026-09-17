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

#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/Namespace.h"
#include "Enhance/Domain/Model/RateModel.h"
#include "Enhance/Domain/Model/RateModelMaster.h"
#include "Enhance/Domain/Model/UnleashRateModel.h"
#include "Enhance/Domain/Model/UnleashRateModelMaster.h"
#include "Enhance/Domain/Model/Enhance.h"
#include "Enhance/Domain/Model/EnhanceAccessToken.h"
#include "Enhance/Domain/Model/Progress.h"
#include "Enhance/Domain/Model/ProgressAccessToken.h"
#include "Enhance/Domain/Model/CurrentRateMaster.h"
#include "Enhance/Domain/Model/User.h"
#include "Enhance/Domain/Model/UserAccessToken.h"
#include "Enhance/Model/Cache/Namespace.h"
#include "Enhance/Model/Cache/UnleashRateModelMaster.h"
#include "Enhance/Model/Cache/RateModelMaster.h"
#include "Enhance/Model/Cache/CurrentRateMaster.h"
#include "Enhance/Model/Cache/UnleashRateModel.h"
#include "Enhance/Model/Cache/RateModel.h"
#include "Enhance/Model/Cache/Progress.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Enhance::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enhance::FGs2EnhanceRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("enhance:Namespace")
    {
    }

    FNamespaceDomain::FNamespaceDomain(
        const FNamespaceDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceStatusRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetStatusTask::FGetStatusTask(
        const FGetStatusTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetStatusTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespaceStatus(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetStatus().IsSet())
            {
                Self->Status = Domain->Status = ResultModel->GetStatus();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetStatusTask>> FNamespaceDomain::GetStatus(
        Request::FGetNamespaceStatusRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetStatusTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FGetTask::FGetTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FGetNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->GetNamespace(
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


        Gs2::Enhance::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FGetTask>> FNamespaceDomain::Get(
        Request::FGetNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FUpdateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateNamespace(
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


        Gs2::Enhance::Model::Cache::FNamespaceCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FUpdateTask>> FNamespaceDomain::Update(
        Request::FUpdateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FDeleteNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
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


              Gs2::Enhance::Model::Cache::FNamespaceCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateUnleashRateModelMasterTask::FCreateUnleashRateModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateUnleashRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateUnleashRateModelMasterTask::FCreateUnleashRateModelMasterTask(
        const FCreateUnleashRateModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateUnleashRateModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateUnleashRateModelMaster(
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


        Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateUnleashRateModelMasterTask>> FNamespaceDomain::CreateUnleashRateModelMaster(
        Request::FCreateUnleashRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateUnleashRateModelMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRateModelMasterTask::FCreateRateModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateRateModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRateModelMasterTask::FCreateRateModelMasterTask(
        const FCreateRateModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRateModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateRateModelMaster(
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


        Gs2::Enhance::Model::Cache::FRateModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRateModelMasterTask>> FNamespaceDomain::CreateRateModelMaster(
        Request::FCreateRateModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRateModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FCurrentRateMasterDomain> FNamespaceDomain::CurrentRateMaster(
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FCurrentRateMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Enhance::Domain::Iterator::FDescribeUnleashRateModelsIteratorPtr FNamespaceDomain::UnleashRateModels(
    ) const
    {
        return MakeShared<Gs2::Enhance::Domain::Iterator::FDescribeUnleashRateModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnleashRateModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Enhance::Model::FUnleashRateModel::TypeName,
            Gs2::Enhance::Model::Cache::FUnleashRateModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeUnleashRateModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Enhance::Model::FUnleashRateModel::TypeName,
            Gs2::Enhance::Model::Cache::FUnleashRateModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectUnleashRateModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>>, public TSharedFromThis<FCollectUnleashRateModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> OnCollected;

    public:
        explicit FCollectUnleashRateModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectUnleashRateModelsTask(const FCollectUnleashRateModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>>> Result) override
        {
            TArray<Gs2::Enhance::Model::FUnleashRateModelPtr> Items;
            auto Iterator = Self->UnleashRateModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnleashRateModels(
        TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Enhance::Domain::FGs2EnhanceDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Enhance::Model::Cache::FUnleashRateModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Enhance::Model::FUnleashRateModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Enhance::Model::FUnleashRateModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Enhance::Model::FUnleashRateModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectUnleashRateModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateUnleashRateModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Enhance::Model::FUnleashRateModel::TypeName,
            Gs2::Enhance::Model::Cache::FUnleashRateModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeUnleashRateModelsWithInitialCallTask::FSubscribeUnleashRateModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeUnleashRateModelsWithInitialCallTask::FSubscribeUnleashRateModelsWithInitialCallTask(const FSubscribeUnleashRateModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeUnleashRateModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectUnleashRateModelsTask>>(Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeUnleashRateModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeUnleashRateModelsWithInitialCallTask>> FNamespaceDomain::SubscribeUnleashRateModelsWithInitialCall(TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeUnleashRateModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelDomain> FNamespaceDomain::UnleashRateModel(
        const FString RateName
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FUnleashRateModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            RateName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RateName)
        );
    }

    Gs2::Enhance::Domain::Iterator::FDescribeUnleashRateModelMastersIteratorPtr FNamespaceDomain::UnleashRateModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Enhance::Domain::Iterator::FDescribeUnleashRateModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnleashRateModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
            Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeUnleashRateModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
            Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectUnleashRateModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>>, public TSharedFromThis<FCollectUnleashRateModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectUnleashRateModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectUnleashRateModelMastersTask(const FCollectUnleashRateModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr> Items;
            auto Iterator = Self->UnleashRateModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeUnleashRateModelMasters(
        TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Enhance::Domain::FGs2EnhanceDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Enhance::Model::FUnleashRateModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectUnleashRateModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateUnleashRateModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Enhance::Model::FUnleashRateModelMaster::TypeName,
            Gs2::Enhance::Model::Cache::FUnleashRateModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeUnleashRateModelMastersWithInitialCallTask::FSubscribeUnleashRateModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeUnleashRateModelMastersWithInitialCallTask::FSubscribeUnleashRateModelMastersWithInitialCallTask(const FSubscribeUnleashRateModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeUnleashRateModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectUnleashRateModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeUnleashRateModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeUnleashRateModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeUnleashRateModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Enhance::Model::FUnleashRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeUnleashRateModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain> FNamespaceDomain::UnleashRateModelMaster(
        const FString RateName
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FUnleashRateModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RateName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RateName)
        );
    }

    Gs2::Enhance::Domain::Iterator::FDescribeRateModelsIteratorPtr FNamespaceDomain::RateModels(
    ) const
    {
        return MakeShared<Gs2::Enhance::Domain::Iterator::FDescribeRateModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRateModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Enhance::Model::FRateModel::TypeName,
            Gs2::Enhance::Model::Cache::FRateModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeRateModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Enhance::Model::FRateModel::TypeName,
            Gs2::Enhance::Model::Cache::FRateModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectRateModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Enhance::Model::FRateModelPtr>>, public TSharedFromThis<FCollectRateModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> OnCollected;

    public:
        explicit FCollectRateModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectRateModelsTask(const FCollectRateModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Enhance::Model::FRateModelPtr>>> Result) override
        {
            TArray<Gs2::Enhance::Model::FRateModelPtr> Items;
            auto Iterator = Self->RateModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Enhance::Model::FRateModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRateModels(
        TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Enhance::Domain::FGs2EnhanceDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Enhance::Model::Cache::FRateModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Enhance::Model::FRateModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Enhance::Model::FRateModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Enhance::Model::FRateModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRateModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateRateModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Enhance::Model::FRateModel::TypeName,
            Gs2::Enhance::Model::Cache::FRateModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeRateModelsWithInitialCallTask::FSubscribeRateModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeRateModelsWithInitialCallTask::FSubscribeRateModelsWithInitialCallTask(const FSubscribeRateModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeRateModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRateModelsTask>>(Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRateModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeRateModelsWithInitialCallTask>> FNamespaceDomain::SubscribeRateModelsWithInitialCall(TFunction<void(TArray<Gs2::Enhance::Model::FRateModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRateModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelDomain> FNamespaceDomain::RateModel(
        const FString RateName
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FRateModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            RateName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RateName)
        );
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Enhance::Domain::Iterator::FDescribeRateModelMastersIteratorPtr FNamespaceDomain::RateModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Enhance::Domain::Iterator::FDescribeRateModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRateModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Enhance::Model::FRateModelMaster::TypeName,
            Gs2::Enhance::Model::Cache::FRateModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeRateModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Enhance::Model::FRateModelMaster::TypeName,
            Gs2::Enhance::Model::Cache::FRateModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectRateModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Enhance::Model::FRateModelMasterPtr>>, public TSharedFromThis<FCollectRateModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectRateModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectRateModelMastersTask(const FCollectRateModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Enhance::Model::FRateModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Enhance::Model::FRateModelMasterPtr> Items;
            auto Iterator = Self->RateModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Enhance::Model::FRateModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRateModelMasters(
        TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Enhance::Domain::FGs2EnhanceDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Enhance::Model::Cache::FRateModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Enhance::Model::FRateModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Enhance::Model::FRateModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Enhance::Model::FRateModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRateModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateRateModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Enhance::Model::FRateModelMaster::TypeName,
            Gs2::Enhance::Model::Cache::FRateModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeRateModelMastersWithInitialCallTask::FSubscribeRateModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeRateModelMastersWithInitialCallTask::FSubscribeRateModelMastersWithInitialCallTask(const FSubscribeRateModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeRateModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRateModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRateModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeRateModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeRateModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Enhance::Model::FRateModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRateModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Enhance::Domain::Model::FRateModelMasterDomain> FNamespaceDomain::RateModelMaster(
        const FString RateName
    )
    {
        return MakeShared<Gs2::Enhance::Domain::Model::FRateModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RateName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RateName)
        );
    }

    FString FNamespaceDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FNamespaceDomain::CreateCacheKey(
        TOptional<FString> NamespaceName
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null");
    }

    FNamespaceDomain::FModelTask::FModelTask(
        const TSharedPtr<FNamespaceDomain> Self
    ): Self(Self)
    {

    }

    FNamespaceDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enhance::Model::FNamespace>> Result
    )
    {
        const auto CacheParentKey = Gs2::Enhance::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Enhance::Model::Cache::FNamespaceCache::CreateCacheKey(

            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Enhance::Model::FNamespace::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Enhance::Model::FNamespacePtr Value;
                const auto CacheHit = Gs2::Enhance::Model::Cache::FNamespaceCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Enhance::Model::Cache::FNamespaceCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    [Self](Gs2::Enhance::Model::FNamespacePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Enhance::Request::FGetNamespaceRequest>()
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    void FNamespaceDomain::Invalidate()
    {
        Gs2::Enhance::Model::Cache::FNamespaceCache::Delete(
            Gs2->Cache,

            NamespaceName,
            TOptional<int32>()
        );
    }

    FNamespaceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FNamespaceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeWithInitialCallTask>> FNamespaceDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Enhance::Model::FNamespacePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Enhance::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Enhance::Model::Cache::FNamespaceCache::CreateCacheKey(

            NamespaceName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Enhance::Domain::FGs2EnhanceDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        return Gs2->Cache->Subscribe(
            Gs2::Enhance::Model::FNamespace::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enhance::Model::FNamespace>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FNamespaceDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Enhance::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Enhance::Model::Cache::FNamespaceCache::CreateCacheKey(

            NamespaceName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Enhance::Model::FNamespace::TypeName,
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
