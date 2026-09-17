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

#include "Distributor/Domain/Model/DistributorModel.h"
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
#include "Distributor/Model/Cache/DistributorModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FDistributorModelDomain::FDistributorModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> DistributorName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        DistributorName(DistributorName),
        ParentKey(Gs2::Distributor::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "DistributorModel"
        ))
    {
    }

    FDistributorModelDomain::FDistributorModelDomain(
        const FDistributorModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        DistributorName(From.DistributorName),
        ParentKey(From.ParentKey)
    {

    }

    FDistributorModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FDistributorModelDomain>& Self,
        const Request::FGetDistributorModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FDistributorModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithDistributorName(Self->DistributorName);
        const auto Future = Self->Client->GetDistributorModel(
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


        Gs2::Distributor::Model::Cache::FDistributorModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetDistributorName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDistributorModelDomain::FGetTask>> FDistributorModelDomain::Get(
        Request::FGetDistributorModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FDistributorModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> DistributorName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (DistributorName.IsSet() ? *DistributorName : "null") + ":" +
            ChildType;
    }

    FString FDistributorModelDomain::CreateCacheKey(
        TOptional<FString> DistributorName
    )
    {
        return FString("") +
            (DistributorName.IsSet() ? *DistributorName : "null");
    }

    FDistributorModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FDistributorModelDomain> Self
    ): Self(Self)
    {

    }

    FDistributorModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FDistributorModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheKey(

            Self->DistributorName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Distributor::Model::FDistributorModelPtr Value;
                const auto CacheHit = Gs2::Distributor::Model::Cache::FDistributorModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->DistributorName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Distributor::Model::Cache::FDistributorModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->DistributorName,
                    TOptional<int32>(),
                    [Self](Gs2::Distributor::Model::FDistributorModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Distributor::Request::FGetDistributorModelRequest>()
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

    TSharedPtr<FAsyncTask<FDistributorModelDomain::FModelTask>> FDistributorModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDistributorModelDomain::FModelTask>>(this->AsShared());
    }

    void FDistributorModelDomain::Invalidate()
    {
        Gs2::Distributor::Model::Cache::FDistributorModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            DistributorName,
            TOptional<int32>()
        );
    }

    FDistributorModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDistributorModelDomain>& Self,
        TFunction<void(Gs2::Distributor::Model::FDistributorModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FDistributorModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDistributorModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FDistributorModelDomain::FSubscribeWithInitialCallTask>> FDistributorModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Distributor::Model::FDistributorModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FDistributorModelDomain::Subscribe(
        TFunction<void(Gs2::Distributor::Model::FDistributorModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheKey(

            DistributorName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Distributor::Domain::FGs2DistributorDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryDistributorName = DistributorName;
        return Gs2->Cache->Subscribe(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Distributor::Model::FDistributorModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryDistributorName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FDistributorModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryDistributorName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDistributorModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Distributor::Model::Cache::FDistributorModelCache::CreateCacheKey(

            DistributorName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Distributor::Model::FDistributorModel::TypeName,
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
