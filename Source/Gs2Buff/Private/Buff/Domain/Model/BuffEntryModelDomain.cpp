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

#include "Buff/Domain/Model/BuffEntryModel.h"
#include "Buff/Domain/Model/Namespace.h"
#include "Buff/Domain/Model/BuffEntryModel.h"
#include "Buff/Domain/Model/BuffEntryModelMaster.h"
#include "Buff/Domain/Model/Buff.h"
#include "Buff/Domain/Model/BuffAccessToken.h"
#include "Buff/Domain/Model/CurrentBuffMaster.h"
#include "Buff/Domain/Model/User.h"
#include "Buff/Domain/Model/UserAccessToken.h"
#include "Buff/Model/Cache/BuffEntryModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Buff::Domain::Model
{

    FBuffEntryModelDomain::FBuffEntryModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Buff::Domain::FGs2BuffDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> BuffEntryName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Buff::FGs2BuffRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        BuffEntryName(BuffEntryName),
        ParentKey(Gs2::Buff::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "BuffEntryModel"
        ))
    {
    }

    FBuffEntryModelDomain::FBuffEntryModelDomain(
        const FBuffEntryModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        BuffEntryName(From.BuffEntryName),
        ParentKey(From.ParentKey)
    {

    }

    FBuffEntryModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FBuffEntryModelDomain>& Self,
        const Request::FGetBuffEntryModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBuffEntryModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBuffEntryModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Model::FBuffEntryModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithBuffEntryName(Self->BuffEntryName);
        const auto Future = Self->Client->GetBuffEntryModel(
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


        Gs2::Buff::Model::Cache::FBuffEntryModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetBuffEntryName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBuffEntryModelDomain::FGetTask>> FBuffEntryModelDomain::Get(
        Request::FGetBuffEntryModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBuffEntryModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> BuffEntryName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (BuffEntryName.IsSet() ? *BuffEntryName : "null") + ":" +
            ChildType;
    }

    FString FBuffEntryModelDomain::CreateCacheKey(
        TOptional<FString> BuffEntryName
    )
    {
        return FString("") +
            (BuffEntryName.IsSet() ? *BuffEntryName : "null");
    }

    FBuffEntryModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FBuffEntryModelDomain> Self
    ): Self(Self)
    {

    }

    FBuffEntryModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBuffEntryModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Buff::Model::FBuffEntryModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::Buff::Model::Cache::FBuffEntryModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Buff::Model::Cache::FBuffEntryModelCache::CreateCacheKey(

            Self->BuffEntryName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Buff::Model::FBuffEntryModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Buff::Model::FBuffEntryModelPtr Value;
                const auto CacheHit = Gs2::Buff::Model::Cache::FBuffEntryModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->BuffEntryName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Buff::Model::Cache::FBuffEntryModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->BuffEntryName,
                    TOptional<int32>(),
                    [Self](Gs2::Buff::Model::FBuffEntryModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Buff::Request::FGetBuffEntryModelRequest>()
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

    TSharedPtr<FAsyncTask<FBuffEntryModelDomain::FModelTask>> FBuffEntryModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBuffEntryModelDomain::FModelTask>>(this->AsShared());
    }

    void FBuffEntryModelDomain::Invalidate()
    {
        Gs2::Buff::Model::Cache::FBuffEntryModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            BuffEntryName,
            TOptional<int32>()
        );
    }

    FBuffEntryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBuffEntryModelDomain>& Self,
        TFunction<void(Gs2::Buff::Model::FBuffEntryModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBuffEntryModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBuffEntryModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FBuffEntryModelDomain::FSubscribeWithInitialCallTask>> FBuffEntryModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Buff::Model::FBuffEntryModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBuffEntryModelDomain::Subscribe(
        TFunction<void(Gs2::Buff::Model::FBuffEntryModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Buff::Model::Cache::FBuffEntryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Buff::Model::Cache::FBuffEntryModelCache::CreateCacheKey(

            BuffEntryName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Buff::Domain::FGs2BuffDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryBuffEntryName = BuffEntryName;
        return Gs2->Cache->Subscribe(
            Gs2::Buff::Model::FBuffEntryModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Buff::Model::FBuffEntryModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryBuffEntryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FBuffEntryModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryBuffEntryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBuffEntryModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Buff::Model::Cache::FBuffEntryModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Buff::Model::Cache::FBuffEntryModelCache::CreateCacheKey(

            BuffEntryName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Buff::Model::FBuffEntryModel::TypeName,
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
