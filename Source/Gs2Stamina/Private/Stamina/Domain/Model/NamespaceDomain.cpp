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

#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/StaminaAccessToken.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"
#include "Stamina/Model/Cache/Namespace.h"
#include "Stamina/Model/Cache/MaxStaminaTableMaster.h"
#include "Stamina/Model/Cache/RecoverIntervalTableMaster.h"
#include "Stamina/Model/Cache/RecoverValueTableMaster.h"
#include "Stamina/Model/Cache/StaminaModelMaster.h"
#include "Stamina/Model/Cache/CurrentStaminaMaster.h"
#include "Stamina/Model/Cache/StaminaModel.h"
#include "Stamina/Model/Cache/Stamina.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FNamespaceDomain::FNamespaceDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey("stamina:Namespace")
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
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
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
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FNamespace>> Result
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


        Gs2::Stamina::Model::Cache::FNamespaceCache::Put(
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
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
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


        Gs2::Stamina::Model::Cache::FNamespaceCache::Put(
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
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
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


              Gs2::Stamina::Model::Cache::FNamespaceCache::Delete(
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

    FNamespaceDomain::FCreateMaxStaminaTableMasterTask::FCreateMaxStaminaTableMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateMaxStaminaTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateMaxStaminaTableMasterTask::FCreateMaxStaminaTableMasterTask(
        const FCreateMaxStaminaTableMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateMaxStaminaTableMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateMaxStaminaTableMaster(
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


        Gs2::Stamina::Model::Cache::FMaxStaminaTableMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateMaxStaminaTableMasterTask>> FNamespaceDomain::CreateMaxStaminaTableMaster(
        Request::FCreateMaxStaminaTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateMaxStaminaTableMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRecoverIntervalTableMasterTask::FCreateRecoverIntervalTableMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRecoverIntervalTableMasterTask::FCreateRecoverIntervalTableMasterTask(
        const FCreateRecoverIntervalTableMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRecoverIntervalTableMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateRecoverIntervalTableMaster(
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


        Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRecoverIntervalTableMasterTask>> FNamespaceDomain::CreateRecoverIntervalTableMaster(
        Request::FCreateRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRecoverIntervalTableMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateRecoverValueTableMasterTask::FCreateRecoverValueTableMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateRecoverValueTableMasterTask::FCreateRecoverValueTableMasterTask(
        const FCreateRecoverValueTableMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateRecoverValueTableMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateRecoverValueTableMaster(
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


        Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateRecoverValueTableMasterTask>> FNamespaceDomain::CreateRecoverValueTableMaster(
        Request::FCreateRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRecoverValueTableMasterTask>>(this->AsShared(), Request);
    }

    FNamespaceDomain::FCreateStaminaModelMasterTask::FCreateStaminaModelMasterTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        const Request::FCreateStaminaModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FNamespaceDomain::FCreateStaminaModelMasterTask::FCreateStaminaModelMasterTask(
        const FCreateStaminaModelMasterTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FCreateStaminaModelMasterTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->CreateStaminaModelMaster(
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


        Gs2::Stamina::Model::Cache::FStaminaModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            ResultModel->GetItem()->GetName()
        );

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FNamespaceDomain::FCreateStaminaModelMasterTask>> FNamespaceDomain::CreateStaminaModelMaster(
        Request::FCreateStaminaModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateStaminaModelMasterTask>>(this->AsShared(), Request);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain> FNamespaceDomain::CurrentStaminaMaster(
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FCurrentStaminaMasterDomain>(
            Gs2,
            Service,
            NamespaceName
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeMaxStaminaTableMastersIteratorPtr FNamespaceDomain::MaxStaminaTableMasters(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeMaxStaminaTableMastersIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeMaxStaminaTableMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FMaxStaminaTableMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeMaxStaminaTableMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FMaxStaminaTableMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectMaxStaminaTableMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>>, public TSharedFromThis<FCollectMaxStaminaTableMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>)> OnCollected;

    public:
        explicit FCollectMaxStaminaTableMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectMaxStaminaTableMastersTask(const FCollectMaxStaminaTableMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>>> Result) override
        {
            TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr> Items;
            auto Iterator = Self->MaxStaminaTableMasters()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeMaxStaminaTableMasters(
        TFunction<void(TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Stamina::Model::Cache::FMaxStaminaTableMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FMaxStaminaTableMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMaxStaminaTableMastersTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateMaxStaminaTableMasters()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Stamina::Model::FMaxStaminaTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FMaxStaminaTableMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeMaxStaminaTableMastersWithInitialCallTask::FSubscribeMaxStaminaTableMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeMaxStaminaTableMastersWithInitialCallTask::FSubscribeMaxStaminaTableMastersWithInitialCallTask(const FSubscribeMaxStaminaTableMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeMaxStaminaTableMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectMaxStaminaTableMastersTask>>(Self, TFunction<void(TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeMaxStaminaTableMasters(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeMaxStaminaTableMastersWithInitialCallTask>> FNamespaceDomain::SubscribeMaxStaminaTableMastersWithInitialCall(TFunction<void(TArray<Gs2::Stamina::Model::FMaxStaminaTableMasterPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeMaxStaminaTableMastersWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain> FNamespaceDomain::MaxStaminaTableMaster(
        const FString MaxStaminaTableName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FMaxStaminaTableMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            MaxStaminaTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(MaxStaminaTableName)
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIteratorPtr FNamespaceDomain::StaminaModels(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator>(
            Gs2,
            Client,
            NamespaceName
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStaminaModels(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FStaminaModel::TypeName,
            Gs2::Stamina::Model::Cache::FStaminaModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeStaminaModels(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FStaminaModel::TypeName,
            Gs2::Stamina::Model::Cache::FStaminaModelCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectStaminaModelsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Stamina::Model::FStaminaModelPtr>>, public TSharedFromThis<FCollectStaminaModelsTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)> OnCollected;

    public:
        explicit FCollectStaminaModelsTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)> OnCollected) : Self(Self), OnCollected(OnCollected) {}
        FCollectStaminaModelsTask(const FCollectStaminaModelsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Stamina::Model::FStaminaModelPtr>>> Result) override
        {
            TArray<Gs2::Stamina::Model::FStaminaModelPtr> Items;
            auto Iterator = Self->StaminaModels()->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Stamina::Model::FStaminaModelPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStaminaModels(
        TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto Parent = Gs2::Stamina::Model::Cache::FStaminaModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Stamina::Model::FStaminaModel::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Stamina::Model::FStaminaModelPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FStaminaModel>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStaminaModelsTask>>(Domain, Callback);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateStaminaModels()
    {
        Gs2->Cache->ClearListCache(
            Gs2::Stamina::Model::FStaminaModel::TypeName,
            Gs2::Stamina::Model::Cache::FStaminaModelCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeStaminaModelsWithInitialCallTask::FSubscribeStaminaModelsWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)> Callback) : Self(Self), Callback(Callback) {}
    FNamespaceDomain::FSubscribeStaminaModelsWithInitialCallTask::FSubscribeStaminaModelsWithInitialCallTask(const FSubscribeStaminaModelsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeStaminaModelsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStaminaModelsTask>>(Self, TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)>());
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStaminaModels(Callback);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeStaminaModelsWithInitialCallTask>> FNamespaceDomain::SubscribeStaminaModelsWithInitialCall(TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelPtr>)> Callback)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStaminaModelsWithInitialCallTask>>(this->AsShared(), Callback);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelDomain> FNamespaceDomain::StaminaModel(
        const FString StaminaName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FStaminaModelDomain>(
            Gs2,
            Service,
            NamespaceName,
            StaminaName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StaminaName)
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FUserDomain> FNamespaceDomain::User(
        const FString UserId
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FUserDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId == TEXT("") ? TOptional<FString>() : TOptional<FString>(UserId)
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FUserAccessTokenDomain> FNamespaceDomain::AccessToken(
        Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FUserAccessTokenDomain>(
            Gs2,
            Service,
            NamespaceName,
            AccessToken
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeRecoverIntervalTableMastersIteratorPtr FNamespaceDomain::RecoverIntervalTableMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeRecoverIntervalTableMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRecoverIntervalTableMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeRecoverIntervalTableMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectRecoverIntervalTableMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>>, public TSharedFromThis<FCollectRecoverIntervalTableMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectRecoverIntervalTableMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectRecoverIntervalTableMastersTask(const FCollectRecoverIntervalTableMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>>> Result) override
        {
            TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr> Items;
            auto Iterator = Self->RecoverIntervalTableMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRecoverIntervalTableMasters(
        TFunction<void(TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRecoverIntervalTableMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateRecoverIntervalTableMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeRecoverIntervalTableMastersWithInitialCallTask::FSubscribeRecoverIntervalTableMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeRecoverIntervalTableMastersWithInitialCallTask::FSubscribeRecoverIntervalTableMastersWithInitialCallTask(const FSubscribeRecoverIntervalTableMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeRecoverIntervalTableMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRecoverIntervalTableMastersTask>>(Self, TFunction<void(TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRecoverIntervalTableMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeRecoverIntervalTableMastersWithInitialCallTask>> FNamespaceDomain::SubscribeRecoverIntervalTableMastersWithInitialCall(TFunction<void(TArray<Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRecoverIntervalTableMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain> FNamespaceDomain::RecoverIntervalTableMaster(
        const FString RecoverIntervalTableName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RecoverIntervalTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RecoverIntervalTableName)
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeRecoverValueTableMastersIteratorPtr FNamespaceDomain::RecoverValueTableMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeRecoverValueTableMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRecoverValueTableMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeRecoverValueTableMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectRecoverValueTableMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>>, public TSharedFromThis<FCollectRecoverValueTableMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectRecoverValueTableMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectRecoverValueTableMastersTask(const FCollectRecoverValueTableMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>>> Result) override
        {
            TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr> Items;
            auto Iterator = Self->RecoverValueTableMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeRecoverValueTableMasters(
        TFunction<void(TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRecoverValueTableMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateRecoverValueTableMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeRecoverValueTableMastersWithInitialCallTask::FSubscribeRecoverValueTableMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeRecoverValueTableMastersWithInitialCallTask::FSubscribeRecoverValueTableMastersWithInitialCallTask(const FSubscribeRecoverValueTableMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeRecoverValueTableMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectRecoverValueTableMastersTask>>(Self, TFunction<void(TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeRecoverValueTableMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeRecoverValueTableMastersWithInitialCallTask>> FNamespaceDomain::SubscribeRecoverValueTableMastersWithInitialCall(TFunction<void(TArray<Gs2::Stamina::Model::FRecoverValueTableMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeRecoverValueTableMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain> FNamespaceDomain::RecoverValueTableMaster(
        const FString RecoverValueTableName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            RecoverValueTableName == TEXT("") ? TOptional<FString>() : TOptional<FString>(RecoverValueTableName)
        );
    }

    Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelMastersIteratorPtr FNamespaceDomain::StaminaModelMasters(
        const TOptional<FString> NamePrefix
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelMastersIterator>(
            Gs2,
            Client,
            NamespaceName,
            NamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStaminaModelMasters(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
            Gs2::Stamina::Model::Cache::FStaminaModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FNamespaceDomain::UnsubscribeStaminaModelMasters(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
            Gs2::Stamina::Model::Cache::FStaminaModelMasterCache::CreateCacheParentKey(
                NamespaceName,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FNamespaceDomain::FCollectStaminaModelMastersTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>>, public TSharedFromThis<FCollectStaminaModelMastersTask>
    {
        const TSharedPtr<FNamespaceDomain> Self;
        const TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>)> OnCollected;
    const TOptional<FString> QueryNamePrefix;
    public:
        explicit FCollectStaminaModelMastersTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>)> OnCollected,const TOptional<FString> NamePrefix) : Self(Self), OnCollected(OnCollected), QueryNamePrefix(NamePrefix) {}
        FCollectStaminaModelMastersTask(const FCollectStaminaModelMastersTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryNamePrefix(From.QueryNamePrefix) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>>> Result) override
        {
            TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr> Items;
            auto Iterator = Self->StaminaModelMasters(QueryNamePrefix)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FNamespaceDomain::SubscribeStaminaModelMasters(
        TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryNamePrefix = NamePrefix;
        const auto Parent = Gs2::Stamina::Model::Cache::FStaminaModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::Stamina::Model::FStaminaModelMaster>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryNamePrefix]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FNamespaceDomain>(Owner, WeakService.Pin(), QueryNamespaceName);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStaminaModelMastersTask>>(Domain, Callback, QueryNamePrefix);
                Task->StartBackgroundTask();
            }
        );
    }

    void FNamespaceDomain::InvalidateStaminaModelMasters(const TOptional<FString> NamePrefix)
    {
        Gs2->Cache->ClearListCache(
            Gs2::Stamina::Model::FStaminaModelMaster::TypeName,
            Gs2::Stamina::Model::Cache::FStaminaModelMasterCache::CreateCacheParentKey(
        NamespaceName,
        TOptional<int32>()
    )
        );
    }

    FNamespaceDomain::FSubscribeStaminaModelMastersWithInitialCallTask::FSubscribeStaminaModelMastersWithInitialCallTask(const TSharedPtr<FNamespaceDomain>& Self, TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix) : Self(Self), Callback(Callback), QueryNamePrefix(NamePrefix) {}
    FNamespaceDomain::FSubscribeStaminaModelMastersWithInitialCallTask::FSubscribeStaminaModelMastersWithInitialCallTask(const FSubscribeStaminaModelMastersWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryNamePrefix(From.QueryNamePrefix) {}
    Gs2::Core::Model::FGs2ErrorPtr FNamespaceDomain::FSubscribeStaminaModelMastersWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectStaminaModelMastersTask>>(Self, TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>)>(), QueryNamePrefix);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeStaminaModelMasters(Callback, QueryNamePrefix);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FNamespaceDomain::FSubscribeStaminaModelMastersWithInitialCallTask>> FNamespaceDomain::SubscribeStaminaModelMastersWithInitialCall(TFunction<void(TArray<Gs2::Stamina::Model::FStaminaModelMasterPtr>)> Callback,const TOptional<FString> NamePrefix)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeStaminaModelMastersWithInitialCallTask>>(this->AsShared(), Callback, NamePrefix);
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain> FNamespaceDomain::StaminaModelMaster(
        const FString StaminaName
    )
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FStaminaModelMasterDomain>(
            Gs2,
            Service,
            NamespaceName,
            StaminaName == TEXT("") ? TOptional<FString>() : TOptional<FString>(StaminaName)
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
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FNamespace>> Result
    )
    {
        const auto CacheParentKey = Gs2::Stamina::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Stamina::Model::Cache::FNamespaceCache::CreateCacheKey(

            Self->NamespaceName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Stamina::Model::FNamespace::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Stamina::Model::FNamespacePtr Value;
                const auto CacheHit = Gs2::Stamina::Model::Cache::FNamespaceCache::TryGet(
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
                const auto Error = Gs2::Stamina::Model::Cache::FNamespaceCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    TOptional<int32>(),
                    [Self](Gs2::Stamina::Model::FNamespacePtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Stamina::Request::FGetNamespaceRequest>()
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
        Gs2::Stamina::Model::Cache::FNamespaceCache::Delete(
            Gs2->Cache,

            NamespaceName,
            TOptional<int32>()
        );
    }

    FNamespaceDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FNamespaceDomain>& Self,
        TFunction<void(Gs2::Stamina::Model::FNamespacePtr)> Callback
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
        TFunction<void(Gs2::Stamina::Model::FNamespacePtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FNamespaceDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FNamespacePtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FNamespaceCache::CreateCacheKey(

            NamespaceName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FNamespace::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FNamespace>(obj));
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
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FNamespaceCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FNamespaceCache::CreateCacheKey(

            NamespaceName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FNamespace::TypeName,
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
