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

#include "Account/Domain/Model/DataOwnerAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"

#include "Account/Model/Cache/DataOwner.h"
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

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Account::Domain::Model
{

    FDataOwnerAccessTokenDomain::FDataOwnerAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken)
    {
    }

    FDataOwnerAccessTokenDomain::FDataOwnerAccessTokenDomain(
        const FDataOwnerAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken)
    {

    }

    FString FDataOwnerAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FDataOwnerAccessTokenDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FDataOwnerAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FDataOwnerAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FDataOwnerAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDataOwnerAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FDataOwner>> Result
    )
    {
        const auto CacheParentKey = Gs2::Account::Model::Cache::FDataOwnerCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Account::Model::Cache::FDataOwnerCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FDataOwner::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Account::Model::FDataOwnerPtr Value;
                Gs2::Account::Model::Cache::FDataOwnerCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FDataOwnerAccessTokenDomain::FModelTask>> FDataOwnerAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FDataOwnerAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FDataOwnerAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FDataOwnerAccessTokenDomain> Self,
        const TFunction<void(Gs2::Account::Model::FDataOwnerPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FDataOwnerAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDataOwnerAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result
    )
    {
        const auto Future = Self->Model();
        Future->StartSynchronousTask();
        Future->EnsureCompletion();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto Item = Future->GetTask().Result();
        const auto ID = Self->Subscribe(Callback);
        Callback(Item);
        *Result = MakeShared<Gs2::Core::Domain::CallbackID>(ID);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDataOwnerAccessTokenDomain::FSubscribeWithInitialCallTask>> FDataOwnerAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Account::Model::FDataOwnerPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDataOwnerAccessTokenDomain::FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }
    void FDataOwnerAccessTokenDomain::Invalidate()
    {
        Gs2::Account::Model::Cache::FDataOwnerCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FDataOwnerAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FDataOwnerPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const TOptional<int32> RegisteredTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        const auto OwnerSubscriptionParentKey = Gs2::Account::Model::Cache::FDataOwnerCache::CreateCacheParentKey(
            QueryNamespaceName,
            RegisteredUserId,
            RegisteredTimeOffset
        );
        const auto OwnerSubscriptionKey = Gs2::Account::Model::Cache::FDataOwnerCache::CreateCacheKey(

        );
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FDataOwner::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FDataOwner>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset() != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FDataOwnerAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FDataOwnerAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto OwnerSubscriptionParentKey = Gs2::Account::Model::Cache::FDataOwnerCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Account::Model::Cache::FDataOwnerCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FDataOwner::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
