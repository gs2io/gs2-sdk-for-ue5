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

#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/Namespace.h"
#include "Enchant/Domain/Model/BalanceParameterModel.h"
#include "Enchant/Domain/Model/BalanceParameterModelMaster.h"
#include "Enchant/Domain/Model/RarityParameterModel.h"
#include "Enchant/Domain/Model/RarityParameterModelMaster.h"
#include "Enchant/Domain/Model/CurrentParameterMaster.h"
#include "Enchant/Domain/Model/User.h"
#include "Enchant/Domain/Model/UserAccessToken.h"
#include "Enchant/Domain/Model/BalanceParameterStatus.h"
#include "Enchant/Domain/Model/BalanceParameterStatusAccessToken.h"
#include "Enchant/Domain/Model/RarityParameterStatus.h"
#include "Enchant/Domain/Model/RarityParameterStatusAccessToken.h"
#include "Enchant/Model/Cache/RarityParameterModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Enchant::Domain::Model
{

    FRarityParameterModelDomain::FRarityParameterModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ParameterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Enchant::FGs2EnchantRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParameterName(ParameterName),
        ParentKey(Gs2::Enchant::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "RarityParameterModel"
        ))
    {
    }

    FRarityParameterModelDomain::FRarityParameterModelDomain(
        const FRarityParameterModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParameterName(From.ParameterName),
        ParentKey(From.ParentKey)
    {

    }

    FRarityParameterModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FRarityParameterModelDomain>& Self,
        const Request::FGetRarityParameterModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FRarityParameterModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithParameterName(Self->ParameterName);
        const auto Future = Self->Client->GetRarityParameterModel(
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


        Gs2::Enchant::Model::Cache::FRarityParameterModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetParameterName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRarityParameterModelDomain::FGetTask>> FRarityParameterModelDomain::Get(
        Request::FGetRarityParameterModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FRarityParameterModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ParameterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ParameterName.IsSet() ? *ParameterName : "null") + ":" +
            ChildType;
    }

    FString FRarityParameterModelDomain::CreateCacheKey(
        TOptional<FString> ParameterName
    )
    {
        return FString("") +
            (ParameterName.IsSet() ? *ParameterName : "null");
    }

    FRarityParameterModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FRarityParameterModelDomain> Self
    ): Self(Self)
    {

    }

    FRarityParameterModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Enchant::Model::FRarityParameterModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::CreateCacheKey(

            Self->ParameterName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Enchant::Model::FRarityParameterModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Enchant::Model::FRarityParameterModelPtr Value;
                const auto CacheHit = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ParameterName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ParameterName,
                    TOptional<int32>(),
                    [Self](Gs2::Enchant::Model::FRarityParameterModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Enchant::Request::FGetRarityParameterModelRequest>()
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

    TSharedPtr<FAsyncTask<FRarityParameterModelDomain::FModelTask>> FRarityParameterModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FRarityParameterModelDomain::FModelTask>>(this->AsShared());
    }

    void FRarityParameterModelDomain::Invalidate()
    {
        Gs2::Enchant::Model::Cache::FRarityParameterModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            ParameterName,
            TOptional<int32>()
        );
    }

    FRarityParameterModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FRarityParameterModelDomain>& Self,
        TFunction<void(Gs2::Enchant::Model::FRarityParameterModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FRarityParameterModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FRarityParameterModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FRarityParameterModelDomain::FSubscribeWithInitialCallTask>> FRarityParameterModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Enchant::Model::FRarityParameterModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FRarityParameterModelDomain::Subscribe(
        TFunction<void(Gs2::Enchant::Model::FRarityParameterModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::CreateCacheKey(

            ParameterName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Enchant::Domain::FGs2EnchantDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryParameterName = ParameterName;
        return Gs2->Cache->Subscribe(
            Gs2::Enchant::Model::FRarityParameterModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Enchant::Model::FRarityParameterModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryParameterName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FRarityParameterModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryParameterName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FRarityParameterModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Enchant::Model::Cache::FRarityParameterModelCache::CreateCacheKey(

            ParameterName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Enchant::Model::FRarityParameterModel::TypeName,
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
