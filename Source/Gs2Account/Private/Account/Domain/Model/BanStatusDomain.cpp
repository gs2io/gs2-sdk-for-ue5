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

#include "Account/Domain/Model/BanStatus.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/TakeOverTypeModel.h"
#include "Account/Domain/Model/TakeOverTypeModelMaster.h"
#include "Account/Domain/Model/CurrentModelMaster.h"
#include "Account/Model/Cache/BanStatus.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Account::Domain::Model
{

    FBanStatusDomain::FBanStatusDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> Name
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        Name(Name),
        ParentKey("account:BanStatus")
    {
    }

    FBanStatusDomain::FBanStatusDomain(
        const FBanStatusDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        Name(From.Name),
        ParentKey(From.ParentKey)
    {

    }

    FString FBanStatusDomain::CreateCacheParentKey(
        TOptional<FString> Name,
        FString ChildType
    )
    {
        return FString("") +
            (Name.IsSet() ? *Name : "null") + ":" +
            ChildType;
    }

    FString FBanStatusDomain::CreateCacheKey(
        TOptional<FString> Name
    )
    {
        return FString("") +
            (Name.IsSet() ? *Name : "null");
    }

    FBanStatusDomain::FModelTask::FModelTask(
        const TSharedPtr<FBanStatusDomain> Self
    ): Self(Self)
    {

    }

    FBanStatusDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FBanStatusDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FBanStatus>> Result
    )
    {
        const auto CacheParentKey = Gs2::Account::Model::Cache::FBanStatusCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Account::Model::Cache::FBanStatusCache::CreateCacheKey(

            Self->Name
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FBanStatus::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Account::Model::FBanStatusPtr Value;
                const auto CacheHit = Gs2::Account::Model::Cache::FBanStatusCache::TryGet(
                    Self->Gs2->Cache,

                    Self->Name,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FBanStatusDomain::FModelTask>> FBanStatusDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FBanStatusDomain::FModelTask>>(this->AsShared());
    }

    void FBanStatusDomain::Invalidate()
    {
        Gs2::Account::Model::Cache::FBanStatusCache::Delete(
            Gs2->Cache,

            Name,
            TOptional<int32>()
        );
    }

    FBanStatusDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FBanStatusDomain>& Self,
        TFunction<void(Gs2::Account::Model::FBanStatusPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FBanStatusDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBanStatusDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FBanStatusDomain::FSubscribeWithInitialCallTask>> FBanStatusDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Account::Model::FBanStatusPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FBanStatusDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FBanStatusPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Account::Model::Cache::FBanStatusCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Account::Model::Cache::FBanStatusCache::CreateCacheKey(

            Name
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryName = Name;
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FBanStatus::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FBanStatus>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FBanStatusDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FBanStatusDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Account::Model::Cache::FBanStatusCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Account::Model::Cache::FBanStatusCache::CreateCacheKey(

            Name
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FBanStatus::TypeName,
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
