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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/Expression.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Domain/Model/TransactionResult.h"
#include "Distributor/Domain/Model/TransactionResultAccessToken.h"

#include "Distributor/Model/Cache/DistributorModelMaster.h"
#include "Distributor/Model/Cache/DistributorModel.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("distributor:Namespace")
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
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FNamespace>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
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
        if (ResultModel->GetItem() != nullptr)
        {
            const auto Key = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheKey(
                ResultModel->GetItem()->GetName()
            );
            Self->Gs2->Cache->Put(
                Gs2::Distributor::Model::FNamespace::TypeName,
                "distributor:Namespace",
                Key,
                ResultModel->GetItem(),
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
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
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->DeleteNamespace(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FDeleteTask>> FNamespaceDomain::Delete(
        Request::FDeleteNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FSetTransactionDefaultConfigTask::FSetTransactionDefaultConfigTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FSetTransactionDefaultConfigRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FSetTransactionDefaultConfigTask::FSetTransactionDefaultConfigTask(
        const FSetTransactionDefaultConfigTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSetTransactionDefaultConfigTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack);
        const auto Future = Self->Client->SetTransactionDefaultConfig(
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
        *Result = Domain;
        Domain->NewContextStack = ResultModel->GetNewContextStack();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FSetTransactionDefaultConfigTask>> FNamespaceDomain::SetTransactionDefaultConfig(
        Request::FSetTransactionDefaultConfigRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FSetTransactionDefaultConfigTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FBatchExecuteApiTask::FBatchExecuteApiTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FBatchExecuteApiRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FBatchExecuteApiTask::FBatchExecuteApiTask(
        const FBatchExecuteApiTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FBatchExecuteApiTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->BatchExecuteApi(
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
            Self->Results = Domain->Results = ResultModel->GetResults();
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FBatchExecuteApiTask>> FNamespaceDomain::BatchExecuteApi(
        Request::FBatchExecuteApiRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FBatchExecuteApiTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateDistributorModelMasterTask::FCreateDistributorModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateDistributorModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateDistributorModelMasterTask::FCreateDistributorModelMasterTask(
        const FCreateDistributorModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateDistributorModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateDistributorModelMaster(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        auto Domain = MakeShared<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateDistributorModelMasterTask>> FNamespaceDomain::CreateDistributorModelMaster(
        Request::FCreateDistributorModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateDistributorModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain> FNamespaceDomain::CurrentDistributorMaster(
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FCurrentDistributorMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIteratorPtr FNamespaceDomain::DistributorModels(
    ) const
    {
        return MakeShared<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDistributorModels(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
            Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeDistributorModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
            Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectDistributorModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Distributor::Model::FDistributorModelPtr>>, public TSharedFromThis<FCollectDistributorModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelPtr>)> OnCollected;

    public:
        explicit FCollectDistributorModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectDistributorModelsTask(const FCollectDistributorModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Distributor::Model::FDistributorModelPtr>>> Result) override
        {
            TArray<Gs2::Distributor::Model::FDistributorModelPtr> Items;
            auto Iterator = Self->DistributorModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Distributor::Model::FDistributorModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDistributorModels(
        TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Distributor::Domain::FGs2DistributorDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Distributor::Model::FDistributorModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Distributor::Model::FDistributorModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDistributorModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateDistributorModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
            Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeDistributorModelsWithInitialCallTask::FSubscribeDistributorModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeDistributorModelsWithInitialCallTask::FSubscribeDistributorModelsWithInitialCallTask(const FSubscribeDistributorModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeDistributorModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDistributorModelsTask>>(Self, TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeDistributorModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeDistributorModelsWithInitialCallTask>> FNamespaceDomain::SubscribeDistributorModelsWithInitialCall(TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDistributorModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelDomain> FNamespaceDomain::DistributorModel(
        const FString DistributorName
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FDistributorModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            DistributorName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DistributorName)
        );
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FDistributeDomain> FNamespaceDomain::Distribute(
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FDistributeDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelMastersIteratorPtr FNamespaceDomain::DistributorModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDistributorModelMasters(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
            Gs2::Distributor::Model::Cache::FDistributorModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeDistributorModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
            Gs2::Distributor::Model::Cache::FDistributorModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectDistributorModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>>, public TSharedFromThis<FCollectDistributorModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectDistributorModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectDistributorModelMastersTask(const FCollectDistributorModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr> Items;
            auto Iterator = Self->DistributorModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeDistributorModelMasters(
        TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Distributor::Domain::FGs2DistributorDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Distributor::Model::Cache::FDistributorModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Distributor::Model::FDistributorModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDistributorModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateDistributorModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Distributor::Model::FDistributorModelMaster::TypeName,
            Gs2::Distributor::Model::Cache::FDistributorModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeDistributorModelMastersWithInitialCallTask::FSubscribeDistributorModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeDistributorModelMastersWithInitialCallTask::FSubscribeDistributorModelMastersWithInitialCallTask(const FSubscribeDistributorModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeDistributorModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectDistributorModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeDistributorModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeDistributorModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeDistributorModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Distributor::Model::FDistributorModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeDistributorModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain> FNamespaceDomain::DistributorModelMaster(
        const FString DistributorName
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FDistributorModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            DistributorName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DistributorName)
        );
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    TSharedPtr<Gs2::Distributor::Domain::Model::FExpressionDomain> FNamespaceDomain::Expression(
    )
    {
        return MakeShared<Gs2::Distributor::Domain::Model::FExpressionDomain>(
            Gs2,
            Service,
            NamespaceName
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
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FNamespace>> Result
    )
    {
        const auto ParentKey = FString("distributor:Namespace");
        const FString CacheKey = Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheKey(
            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Distributor::Model::FNamespace::TypeName,
            ParentKey,
            CacheKey,
            [this, Result, CacheKey, ParentKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                // ReSharper disable once CppLocalVariableMayBeConst
                TSharedPtr<Gs2::Distributor::Model::FNamespace> Value;
                auto bCacheHit = Self->Gs2->Cache->TryGet<Gs2::Distributor::Model::FNamespace>(
                    ParentKey,
                    CacheKey,
                    &Value
                );
                if (!bCacheHit) {
                    const auto Future = Self->Get(
                        MakeShared<Gs2::Distributor::Request::FGetNamespaceRequest>()
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        const auto Error = Future->GetTask().Error();
                        if (!Error.IsValid() || Error->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                        {
                            return Error;
                        }
                        Self->Gs2->Cache->Put(
                            Gs2::Distributor::Model::FNamespace::TypeName,
                            ParentKey,
                            CacheKey,
                            nullptr,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );

                        if (!Error->GetErrors().IsValid() || Error->Count() == 0 || !Error->Detail(0).IsValid() || Error->Detail(0)->GetComponent() != "namespace")
                        {
                            return Error;
                        }
                    }
                    else
                    {
                        Value = Future->GetTask().Result();
                    }
                    Future->EnsureCompletion();
                }
                if (!bCacheHit)
                {
                    FGs2ObjectPtr ExistingObject;
                    const bool Existing = Self->Gs2->Cache->TryGet(
                        Gs2::Distributor::Model::FNamespace::TypeName,
                        ParentKey,
                        CacheKey,
                        &ExistingObject
                    );
                    if (!Existing || ExistingObject != Value)
                    {
                        Self->Gs2->Cache->Put(
                            Gs2::Distributor::Model::FNamespace::TypeName,
                            ParentKey,
                            CacheKey,
                            Value,
                            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                        );
                    }
                }

                *Result = Value;

                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FModelTask>> FNamespaceDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FNamespaceDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Distributor::Model::FNamespacePtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Distributor::Domain::FGs2DistributorDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;

        return Gs2->Cache->Subscribe(
            Gs2::Distributor::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Distributor::Model::FNamespace>(obj));
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
        Gs2->Cache->Unsubscribe(
            Gs2::Distributor::Model::FNamespace::TypeName,
            ParentKey,
            Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheKey(
                NamespaceName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

