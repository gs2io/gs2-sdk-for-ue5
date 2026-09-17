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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Model/Cache/TakeOver.h"
#include "Account/Domain/Model/TakeOver.h"
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

    FTakeOverAccessTokenDomain::FTakeOverAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Account::Domain::FGs2AccountDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<int32> Type
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Account::FGs2AccountRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        Type(Type),
        ParentKey(Gs2::Account::Domain::Model::FAccountDomain::CreateCacheParentKey(
            NamespaceName,
            UserId(),
            "TakeOver"
        ))
    {
    }

    FTakeOverAccessTokenDomain::FTakeOverAccessTokenDomain(
        const FTakeOverAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        Type(From.Type),
        ParentKey(From.ParentKey)
    {

    }

    FTakeOverAccessTokenDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
        const Request::FCreateTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->CreateTakeOver(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            Gs2::Account::Model::Cache::FTakeOverCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerUserId,
                ResultModel->GetItem()->GetType().Get(0),
                CacheOwnerTimeOffset,
                ResultModel->GetItem()
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FCreateTask>> FTakeOverAccessTokenDomain::Create(
        Request::FCreateTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FCreateOpenIdConnectTask::FCreateOpenIdConnectTask(
        const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
        const Request::FCreateTakeOverOpenIdConnectRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FCreateOpenIdConnectTask::FCreateOpenIdConnectTask(
        const FCreateOpenIdConnectTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FCreateOpenIdConnectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->CreateTakeOverOpenIdConnect(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            Gs2::Account::Model::Cache::FTakeOverCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerUserId,
                ResultModel->GetItem()->GetType().Get(0),
                CacheOwnerTimeOffset,
                ResultModel->GetItem()
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FCreateOpenIdConnectTask>> FTakeOverAccessTokenDomain::CreateOpenIdConnect(
        Request::FCreateTakeOverOpenIdConnectRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateOpenIdConnectTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
        const Request::FGetTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetTakeOver(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            Gs2::Account::Model::Cache::FTakeOverCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerUserId,
                ResultModel->GetItem()->GetType().Get(0),
                CacheOwnerTimeOffset,
                ResultModel->GetItem()
            );
        }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FGetTask>> FTakeOverAccessTokenDomain::Get(
        Request::FGetTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
        const Request::FUpdateTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->UpdateTakeOver(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel->GetItem() != nullptr)
        {
            Gs2::Account::Model::Cache::FTakeOverCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerUserId,
                ResultModel->GetItem()->GetType().Get(0),
                CacheOwnerTimeOffset,
                ResultModel->GetItem()
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FUpdateTask>> FTakeOverAccessTokenDomain::Update(
        Request::FUpdateTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FTakeOverAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FTakeOverAccessTokenDomain>& Self,
        const Request::FDeleteTakeOverRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FTakeOverAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FTakeOverAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeleteTakeOver(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr && ResultModel->GetItem() != nullptr)
        {
            Gs2::Account::Model::Cache::FTakeOverCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                CacheOwnerUserId,
                ResultModel->GetItem()->GetType().Get(0),
                CacheOwnerTimeOffset
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FDeleteTask>> FTakeOverAccessTokenDomain::Delete(
        Request::FDeleteTakeOverRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FTakeOverAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<int32> Type,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Type.IsSet() ? FString::FromInt(*Type) : "null") + ":" +
            ChildType;
    }

    FString FTakeOverAccessTokenDomain::CreateCacheKey(
        TOptional<int32> Type
    )
    {
        return FString("") +
            (Type.IsSet() ? FString::FromInt(*Type) : "null");
    }

    FTakeOverAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FTakeOverAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FTakeOverAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FTakeOverAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FTakeOver>> Result
    )
    {
        const auto CacheParentKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheKey(
            Self->Type
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FTakeOver::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheParentKey, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Account::Model::FTakeOverPtr Value;
                const auto CacheHit = Gs2::Account::Model::Cache::FTakeOverCache::TryGet(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->Type,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Account::Model::Cache::FTakeOverCache::Fetch(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->Type,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self = Self](Gs2::Account::Model::FTakeOverPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Account::Request::FGetTakeOverRequest>()
                        );
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            return Future->GetTask().Error();
                        }
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

    TSharedPtr<FAsyncTask<FTakeOverAccessTokenDomain::FModelTask>> FTakeOverAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FTakeOverAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FTakeOverAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FTakeOverPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Account::Domain::FGs2AccountDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<int32> QueryType = Type;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const int32 RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset().Get(0) : 0;
        const auto OwnerSubscriptionParentKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheKey(Type);
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FTakeOver>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryType, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid() || !SourceToken.IsValid() || !RegisteredUserId.IsSet())
                {
                    return;
                }
                const auto TokenSnapshot = MakeShared<Gs2::Auth::Model::FAccessToken>(*SourceToken);
                if (TokenSnapshot->GetUserId() != RegisteredUserId || TokenSnapshot->GetTimeOffset().Get(0) != RegisteredTimeOffset)
                {
                    return;
                }
                const auto Domain = MakeShared<FTakeOverAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryType
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FTakeOverAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto OwnerSubscriptionParentKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Account::Model::Cache::FTakeOverCache::CreateCacheKey(Type);
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FTakeOver::TypeName,
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
