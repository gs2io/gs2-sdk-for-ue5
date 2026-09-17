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

#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/Namespace.h"
#include "Money2/Domain/Model/User.h"
#include "Money2/Domain/Model/UserAccessToken.h"
#include "Money2/Domain/Model/Wallet.h"
#include "Money2/Domain/Model/WalletAccessToken.h"
#include "Money2/Domain/Model/Event.h"
#include "Money2/Domain/Model/EventAccessToken.h"
#include "Money2/Domain/Model/SubscriptionStatus.h"
#include "Money2/Domain/Model/SubscriptionStatusAccessToken.h"
#include "Money2/Domain/Model/RefundHistory.h"
#include "Money2/Domain/Model/StoreContentModel.h"
#include "Money2/Domain/Model/StoreContentModelMaster.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModel.h"
#include "Money2/Domain/Model/StoreSubscriptionContentModelMaster.h"
#include "Money2/Domain/Model/CurrentModelMaster.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/UnusedBalance.h"
#include "Money2/Model/Cache/StoreSubscriptionContentModelMaster.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FStoreSubscriptionContentModelMasterDomain::FStoreSubscriptionContentModelMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ContentName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ContentName(ContentName),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "StoreSubscriptionContentModelMaster"
        ))
    {
    }

    FStoreSubscriptionContentModelMasterDomain::FStoreSubscriptionContentModelMasterDomain(
        const FStoreSubscriptionContentModelMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ContentName(From.ContentName),
        ParentKey(From.ParentKey)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FGetTask::FGetTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        const Request::FGetStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->GetStoreSubscriptionContentModelMaster(
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


        Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetContentName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FGetTask>> FStoreSubscriptionContentModelMasterDomain::Get(
        Request::FGetStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FStoreSubscriptionContentModelMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        const Request::FUpdateStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->UpdateStoreSubscriptionContentModelMaster(
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


        Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetContentName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FUpdateTask>> FStoreSubscriptionContentModelMasterDomain::Update(
        Request::FUpdateStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FStoreSubscriptionContentModelMasterDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        const Request::FDeleteStoreSubscriptionContentModelMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Domain::Model::FStoreSubscriptionContentModelMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithContentName(Self->ContentName);
        const auto Future = Self->Client->DeleteStoreSubscriptionContentModelMaster(
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


              Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetContentName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FDeleteTask>> FStoreSubscriptionContentModelMasterDomain::Delete(
        Request::FDeleteStoreSubscriptionContentModelMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FStoreSubscriptionContentModelMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ContentName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ContentName.IsSet() ? *ContentName : "null") + ":" +
            ChildType;
    }

    FString FStoreSubscriptionContentModelMasterDomain::CreateCacheKey(
        TOptional<FString> ContentName
    )
    {
        return FString("") +
            (ContentName.IsSet() ? *ContentName : "null");
    }

    FStoreSubscriptionContentModelMasterDomain::FModelTask::FModelTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain> Self
    ): Self(Self)
    {

    }

    FStoreSubscriptionContentModelMasterDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>> Result
    )
    {
        const auto CacheParentKey = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheKey(

            Self->ContentName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr Value;
                const auto CacheHit = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ContentName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ContentName,
                    TOptional<int32>(),
                    [Self](Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Money2::Request::FGetStoreSubscriptionContentModelMasterRequest>()
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

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FModelTask>> FStoreSubscriptionContentModelMasterDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FModelTask>>(this->AsShared());
    }

    void FStoreSubscriptionContentModelMasterDomain::Invalidate()
    {
        Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::Delete(
            Gs2->Cache,

            NamespaceName,
            ContentName,
            TOptional<int32>()
        );
    }

    FStoreSubscriptionContentModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FStoreSubscriptionContentModelMasterDomain>& Self,
        TFunction<void(Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FStoreSubscriptionContentModelMasterDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStoreSubscriptionContentModelMasterDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FStoreSubscriptionContentModelMasterDomain::FSubscribeWithInitialCallTask>> FStoreSubscriptionContentModelMasterDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FStoreSubscriptionContentModelMasterDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FStoreSubscriptionContentModelMasterPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheKey(

            ContentName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryContentName = ContentName;
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FStoreSubscriptionContentModelMaster>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryContentName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FStoreSubscriptionContentModelMasterDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryContentName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStoreSubscriptionContentModelMasterDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FStoreSubscriptionContentModelMasterCache::CreateCacheKey(

            ContentName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FStoreSubscriptionContentModelMaster::TypeName,
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
