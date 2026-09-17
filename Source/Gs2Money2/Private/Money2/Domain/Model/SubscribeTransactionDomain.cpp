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

#include "Money2/Domain/Model/SubscribeTransaction.h"
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
#include "Money2/Model/Cache/SubscribeTransaction.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Money2::Domain::Model
{

    FSubscribeTransactionDomain::FSubscribeTransactionDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Money2::Domain::FGs2Money2DomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ContentName,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Money2::FGs2Money2RestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ContentName(ContentName),
        TransactionId(TransactionId),
        ParentKey(Gs2::Money2::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "SubscribeTransaction"
        ))
    {
    }

    FSubscribeTransactionDomain::FSubscribeTransactionDomain(
        const FSubscribeTransactionDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ContentName(From.ContentName),
        TransactionId(From.TransactionId),
        ParentKey(From.ParentKey)
    {

    }

    FString FSubscribeTransactionDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ContentName,
        TOptional<FString> TransactionId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ContentName.IsSet() ? *ContentName : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null") + ":" +
            ChildType;
    }

    FString FSubscribeTransactionDomain::CreateCacheKey(
        TOptional<FString> ContentName,
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (ContentName.IsSet() ? *ContentName : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FSubscribeTransactionDomain::FModelTask::FModelTask(
        const TSharedPtr<FSubscribeTransactionDomain> Self
    ): Self(Self)
    {

    }

    FSubscribeTransactionDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeTransactionDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Money2::Model::FSubscribeTransaction>> Result
    )
    {
        const auto CacheParentKey = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::CreateCacheKey(

            Self->ContentName,
            Self->TransactionId
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Money2::Model::FSubscribeTransaction::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Money2::Model::FSubscribeTransactionPtr Value;
                const auto CacheHit = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ContentName,
                    Self->TransactionId,
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

    TSharedPtr<FAsyncTask<FSubscribeTransactionDomain::FModelTask>> FSubscribeTransactionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTransactionDomain::FModelTask>>(this->AsShared());
    }

    void FSubscribeTransactionDomain::Invalidate()
    {
        Gs2::Money2::Model::Cache::FSubscribeTransactionCache::Delete(
            Gs2->Cache,

            NamespaceName,
            ContentName,
            TransactionId,
            TOptional<int32>()
        );
    }

    FSubscribeTransactionDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSubscribeTransactionDomain>& Self,
        TFunction<void(Gs2::Money2::Model::FSubscribeTransactionPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSubscribeTransactionDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSubscribeTransactionDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSubscribeTransactionDomain::FSubscribeWithInitialCallTask>> FSubscribeTransactionDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Money2::Model::FSubscribeTransactionPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSubscribeTransactionDomain::Subscribe(
        TFunction<void(Gs2::Money2::Model::FSubscribeTransactionPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::CreateCacheKey(

            ContentName,
            TransactionId
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Money2::Domain::FGs2Money2Domain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryContentName = ContentName;
        const TOptional<FString> QueryTransactionId = TransactionId;
        return Gs2->Cache->Subscribe(
            Gs2::Money2::Model::FSubscribeTransaction::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Money2::Model::FSubscribeTransaction>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryContentName, QueryTransactionId]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSubscribeTransactionDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryContentName,
                    QueryTransactionId
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSubscribeTransactionDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Money2::Model::Cache::FSubscribeTransactionCache::CreateCacheKey(

            ContentName,
            TransactionId
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Money2::Model::FSubscribeTransaction::TypeName,
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
