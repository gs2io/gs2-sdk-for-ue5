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

#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
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
#include "Stamina/Model/Cache/RecoverIntervalTableMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Stamina::Domain::Model
{

    FRecoverIntervalTableMasterDomain::FRecoverIntervalTableMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> RecoverIntervalTableName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        RecoverIntervalTableName(RecoverIntervalTableName),
        ParentKey(Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RecoverIntervalTableMaster"
        ))
    {
    }

    FRecoverIntervalTableMasterDomain::FRecoverIntervalTableMasterDomain(
        const FRecoverIntervalTableMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        RecoverIntervalTableName(From.RecoverIntervalTableName),
        ParentKey(From.ParentKey)
    {

    }

    FRecoverIntervalTableMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        const Request::FGetRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverIntervalTableMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverIntervalTableName(Self->RecoverIntervalTableName);
        const auto Future = Self->Client->GetRecoverIntervalTableMaster(
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
            Request->GetRecoverIntervalTableName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FGetTask>> FRecoverIntervalTableMasterDomain::Get(
        Request::FGetRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FRecoverIntervalTableMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverIntervalTableMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverIntervalTableName(Self->RecoverIntervalTableName);
        const auto Future = Self->Client->UpdateRecoverIntervalTableMaster(
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
            Request->GetRecoverIntervalTableName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FUpdateTask>> FRecoverIntervalTableMasterDomain::Update(
        Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FRecoverIntervalTableMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRecoverIntervalTableMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FRecoverIntervalTableMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithRecoverIntervalTableName(Self->RecoverIntervalTableName);
        const auto Future = Self->Client->DeleteRecoverIntervalTableMaster(
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


              Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetRecoverIntervalTableName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FDeleteTask>> FRecoverIntervalTableMasterDomain::Delete(
        Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FRecoverIntervalTableMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> RecoverIntervalTableName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (RecoverIntervalTableName.IsSet() ? *RecoverIntervalTableName : "null") + ":" +
            ChildType;
    }

    FString FRecoverIntervalTableMasterDomain::CreateCacheKey(
        TOptional<FString> RecoverIntervalTableName
    )
    {
        return FString("") +
            (RecoverIntervalTableName.IsSet() ? *RecoverIntervalTableName : "null");
    }

    FRecoverIntervalTableMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain> Self
    ): Self(Self)
    {

    }

    FRecoverIntervalTableMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheKey(

            Self->RecoverIntervalTableName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr Value;
                const auto CacheHit = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RecoverIntervalTableName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->RecoverIntervalTableName,
                    TOptional<int32>(),
                    [Self](Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Stamina::Request::FGetRecoverIntervalTableMasterRequest>()
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

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FModelTask>> FRecoverIntervalTableMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRecoverIntervalTableMasterDomain::FModelTask>>(this->AsShared());
    }

    void FRecoverIntervalTableMasterDomain::Invalidate()
    {
        Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            RecoverIntervalTableName,
            TOptional<int32>()
        );
    }

    FRecoverIntervalTableMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRecoverIntervalTableMasterDomain>& Self,
        TFunction<void(Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRecoverIntervalTableMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverIntervalTableMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRecoverIntervalTableMasterDomain::FSubscribeWithInitialCallTask>> FRecoverIntervalTableMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRecoverIntervalTableMasterDomain::Subscribe(
        TFunction<void(Gs2::Stamina::Model::FRecoverIntervalTableMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheKey(

            RecoverIntervalTableName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Stamina::Domain::FGs2StaminaDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryRecoverIntervalTableName = RecoverIntervalTableName;
        return Gs2->Cache->Subscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Stamina::Model::FRecoverIntervalTableMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryRecoverIntervalTableName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRecoverIntervalTableMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryRecoverIntervalTableName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRecoverIntervalTableMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Stamina::Model::Cache::FRecoverIntervalTableMasterCache::CreateCacheKey(

            RecoverIntervalTableName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Stamina::Model::FRecoverIntervalTableMaster::TypeName,
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
