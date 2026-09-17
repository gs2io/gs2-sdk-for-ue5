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

#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Domain/Model/Namespace.h"
#include "LoginReward/Domain/Model/BonusModelMaster.h"
#include "LoginReward/Domain/Model/CurrentBonusMaster.h"
#include "LoginReward/Domain/Model/BonusModel.h"
#include "LoginReward/Domain/Model/User.h"
#include "LoginReward/Domain/Model/UserAccessToken.h"
#include "LoginReward/Domain/Model/Bonus.h"
#include "LoginReward/Domain/Model/BonusAccessToken.h"
#include "LoginReward/Domain/Model/ReceiveStatus.h"
#include "LoginReward/Domain/Model/ReceiveStatusAccessToken.h"
#include "LoginReward/Model/Cache/BonusModel.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::LoginReward::Domain::Model
{

    FBonusModelDomain::FBonusModelDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> BonusModelName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::LoginReward::FGs2LoginRewardRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        BonusModelName(BonusModelName),
        ParentKey(Gs2::LoginReward::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "BonusModel"
        ))
    {
    }

    FBonusModelDomain::FBonusModelDomain(
        const FBonusModelDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        BonusModelName(From.BonusModelName),
        ParentKey(From.ParentKey)
    {

    }

    FBonusModelDomain::FGetTask::FGetTask(
        const TSharedPtr<FBonusModelDomain>& Self,
        const Request::FGetBonusModelRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FBonusModelDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBonusModelDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FBonusModel>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithBonusModelName(Self->BonusModelName);
        const auto Future = Self->Client->GetBonusModel(
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


        Gs2::LoginReward::Model::Cache::FBonusModelCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetBonusModelName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBonusModelDomain::FGetTask>> FBonusModelDomain::Get(
        Request::FGetBonusModelRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FBonusModelDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> BonusModelName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (BonusModelName.IsSet() ? *BonusModelName : "null") + ":" +
            ChildType;
    }

    FString FBonusModelDomain::CreateCacheKey(
        TOptional<FString> BonusModelName
    )
    {
        return FString("") +
            (BonusModelName.IsSet() ? *BonusModelName : "null");
    }

    FBonusModelDomain::FModelTask::FModelTask(
        const TSharedPtr<FBonusModelDomain> Self
    ): Self(Self)
    {

    }

    FBonusModelDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBonusModelDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::LoginReward::Model::FBonusModel>> Result
    )
    {
        const auto CacheParentKey = Gs2::LoginReward::Model::Cache::FBonusModelCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::LoginReward::Model::Cache::FBonusModelCache::CreateCacheKey(

            Self->BonusModelName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::LoginReward::Model::FBonusModel::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::LoginReward::Model::FBonusModelPtr Value;
                const auto CacheHit = Gs2::LoginReward::Model::Cache::FBonusModelCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->BonusModelName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::LoginReward::Model::Cache::FBonusModelCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->BonusModelName,
                    TOptional<int32>(),
                    [Self](Gs2::LoginReward::Model::FBonusModelPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::LoginReward::Request::FGetBonusModelRequest>()
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

    TSharedPtr<FAsyncTask<FBonusModelDomain::FModelTask>> FBonusModelDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBonusModelDomain::FModelTask>>(this->AsShared());
    }

    void FBonusModelDomain::Invalidate()
    {
        Gs2::LoginReward::Model::Cache::FBonusModelCache::Delete(
            Gs2->Cache,

            NamespaceName,
            BonusModelName,
            TOptional<int32>()
        );
    }

    FBonusModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBonusModelDomain>& Self,
        TFunction<void(Gs2::LoginReward::Model::FBonusModelPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBonusModelDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBonusModelDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FBonusModelDomain::FSubscribeWithInitialCallTask>> FBonusModelDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::LoginReward::Model::FBonusModelPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBonusModelDomain::Subscribe(
        TFunction<void(Gs2::LoginReward::Model::FBonusModelPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::LoginReward::Model::Cache::FBonusModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::LoginReward::Model::Cache::FBonusModelCache::CreateCacheKey(

            BonusModelName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<LoginReward::Domain::FGs2LoginRewardDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryBonusModelName = BonusModelName;
        return Gs2->Cache->Subscribe(
            Gs2::LoginReward::Model::FBonusModel::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::LoginReward::Model::FBonusModel>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryBonusModelName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FBonusModelDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryBonusModelName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBonusModelDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::LoginReward::Model::Cache::FBonusModelCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::LoginReward::Model::Cache::FBonusModelCache::CreateCacheKey(

            BonusModelName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::LoginReward::Model::FBonusModel::TypeName,
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
