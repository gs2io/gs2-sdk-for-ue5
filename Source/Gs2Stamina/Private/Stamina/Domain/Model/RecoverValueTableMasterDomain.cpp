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

#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
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
#include "Stamina/Model/Cache/RecoverValueTableMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverValueTableMasterDomain::FRecoverValueTableMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RecoverValueTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RecoverValueTableName(RecoverValueTableName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RecoverValueTableMaster"
        ))
    {
    }

    FRecoverValueTableMasterDomain::FRecoverValueTableMasterDomain(
        const FRecoverValueTableMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RecoverValueTableName(From.RecoverValueTableName),
        ParentKey(From.ParentKey)
    {

    }

    FRecoverValueTableMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FRecoverValueTableMasterDomain>& Self,
        const Request::FGetRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverValueTableMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverValueTableName(Self->RecoverValueTableName);
        const auto Future = Self->Client->GetRecoverValueTableMaster(
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
            Request->GetRecoverValueTableName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FGetTask>> FRecoverValueTableMasterDomain::Get(
        Request::FGetRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRecoverValueTableMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRecoverValueTableMasterDomain>& Self,
        const Request::FUpdateRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverValueTableMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverValueTableName(Self->RecoverValueTableName);
        const auto Future = Self->Client->UpdateRecoverValueTableMaster(
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
            Request->GetRecoverValueTableName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FUpdateTask>> FRecoverValueTableMasterDomain::Update(
        Request::FUpdateRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRecoverValueTableMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRecoverValueTableMasterDomain>& Self,
        const Request::FDeleteRecoverValueTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverValueTableMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverValueTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverValueTableName(Self->RecoverValueTableName);
        const auto Future = Self->Client->DeleteRecoverValueTableMaster(
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


              Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRecoverValueTableName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FDeleteTask>> FRecoverValueTableMasterDomain::Delete(
        Request::FDeleteRecoverValueTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRecoverValueTableMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RecoverValueTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RecoverValueTableName.IsSet() ? *RecoverValueTableName : "null") + ":" +
            ChildType;
    }

    FString FRecoverValueTableMasterDomain::CreateCacheKey(
        TOptional<FString> RecoverValueTableName
    )
    {
        return FString("") +
            (RecoverValueTableName.IsSet() ? *RecoverValueTableName : "null");
    }

    FRecoverValueTableMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverValueTableMasterDomain> Self
    ): Self(Self)
    {

    }

    FRecoverValueTableMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheKey(

            Self->RecoverValueTableName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Stamina::Model::FRecoverValueTableMasterPtr Value;
                const auto CacheHit = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RecoverValueTableName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RecoverValueTableName,
                    TOptional<int32>(),
                    [Self](Gs2::Stamina::Model::FRecoverValueTableMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Stamina::Request::FGetRecoverValueTableMasterRequest>()
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

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FModelTask>> FRecoverValueTableMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverValueTableMasterDomain::FModelTask>>(this->AsShared());
    }

    void FRecoverValueTableMasterDomain::Invalidate()
    {
        Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RecoverValueTableName,
            TOptional<int32>()
        );
    }

    FRecoverValueTableMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRecoverValueTableMasterDomain>& Self,
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTableMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRecoverValueTableMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverValueTableMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRecoverValueTableMasterDomain::FSubscribeWithInitialCallTask>> FRecoverValueTableMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTableMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRecoverValueTableMasterDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FRecoverValueTableMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheKey(

            RecoverValueTableName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRecoverValueTableName = RecoverValueTableName;
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverValueTableMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRecoverValueTableName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRecoverValueTableMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRecoverValueTableName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRecoverValueTableMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FRecoverValueTableMasterCache::CreateCacheKey(

            RecoverValueTableName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FRecoverValueTableMaster::TypeName,
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
