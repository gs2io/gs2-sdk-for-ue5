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

#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Model/Cache/PlatformId.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/Namespace.h"
#include "Account/Domain/Model/Account.h"
#include "Account/Domain/Model/AccountAccessToken.h"
#include "Account/Domain/Model/TakeOver.h"
#include "Account/Domain/Model/TakeOverAccessToken.h"
#include "Account/Domain/Model/PlatformId.h"
#include "Account/Domain/Model/PlatformIdAccessToken.h"
#include "Account/Domain/Model/DataOwner.h"
#include "Account/Domain/Model/DataOwnerAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Account::Domain::Model
{

    FPlatformIdAccessTokenDomain::FPlatformIdAccessTokenDomain(
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
            "PlatformId"
        ))
    {
    }

    FPlatformIdAccessTokenDomain::FPlatformIdAccessTokenDomain(
        const FPlatformIdAccessTokenDomain& From
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

    FPlatformIdAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
        const Request::FGetPlatformIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformId>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->GetPlatformId(
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
        if (ResultModel != nullptr) {
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Account::Model::Cache::FPlatformIdCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(),
                    CacheOwnerUserId,
                    ResultModel->GetItem()->GetType(),
                    CacheOwnerTimeOffset,
                    ResultModel->GetItem()
                );
            }
            *Result = ResultModel->GetItem();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdAccessTokenDomain::FGetTask>> FPlatformIdAccessTokenDomain::Get(
        Request::FGetPlatformIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FPlatformIdAccessTokenDomain::FCreateTask::FCreateTask(
        const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
        const Request::FCreatePlatformIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdAccessTokenDomain::FCreateTask::FCreateTask(
        const FCreateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdAccessTokenDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->CreatePlatformId(
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
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Account::Model::Cache::FPlatformIdCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(),
                    CacheOwnerUserId,
                    ResultModel->GetItem()->GetType(),
                    CacheOwnerTimeOffset,
                    ResultModel->GetItem()
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdAccessTokenDomain::FCreateTask>> FPlatformIdAccessTokenDomain::Create(
        Request::FCreatePlatformIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(this->AsShared(), Request);
    }

    FPlatformIdAccessTokenDomain::FFindTask::FFindTask(
        const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
        const Request::FFindPlatformIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdAccessTokenDomain::FFindTask::FFindTask(
        const FFindTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdAccessTokenDomain::FFindTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformUser>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto Future = Self->Client->FindPlatformId(
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
        if (ResultModel != nullptr) {
            *Result = ResultModel->GetItem();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdAccessTokenDomain::FFindTask>> FPlatformIdAccessTokenDomain::Find(
        Request::FFindPlatformIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FFindTask>>(this->AsShared(), Request);
    }

    FPlatformIdAccessTokenDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FPlatformIdAccessTokenDomain>& Self,
        const Request::FDeletePlatformIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FPlatformIdAccessTokenDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdAccessTokenDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithType(Self->Type);
        const auto CacheOwnerUserId = Self->UserId();
        const auto CacheOwnerTimeOffset = Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>();
        const auto Future = Self->Client->DeletePlatformId(
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
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                Gs2::Account::Model::Cache::FPlatformIdCache::Delete(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(),
                    CacheOwnerUserId,
                    ResultModel->GetItem()->GetType(),
                    CacheOwnerTimeOffset
                );
            }
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FPlatformIdAccessTokenDomain::FDeleteTask>> FPlatformIdAccessTokenDomain::Delete(
        Request::FDeletePlatformIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FPlatformIdAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> Type,
        TOptional<FString> UserIdentifier,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (Type.IsSet() ? *Type : "null") + ":" +
            (UserIdentifier.IsSet() ? *UserIdentifier : "null") + ":" +
            ChildType;
    }

    FString FPlatformIdAccessTokenDomain::CreateCacheKey(
        TOptional<FString> Type,
        TOptional<FString> UserIdentifier
    )
    {
        return FString("") +
            (Type.IsSet() ? *Type : "null") + ":" + 
            (UserIdentifier.IsSet() ? *UserIdentifier : "null");
    }

    FPlatformIdAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FPlatformIdAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FPlatformIdAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FPlatformIdAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Account::Model::FPlatformId>> Result
    )
    {
        const auto CacheParentKey = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheKey(
            Self->Type
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Account::Model::FPlatformId::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheParentKey, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Account::Model::FPlatformIdPtr Value;
                const auto CacheHit = Gs2::Account::Model::Cache::FPlatformIdCache::TryGet(
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
                const auto Error = Gs2::Account::Model::Cache::FPlatformIdCache::Fetch(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->Type,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self = Self](Gs2::Account::Model::FPlatformIdPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Account::Request::FGetPlatformIdRequest>()
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

    TSharedPtr<FAsyncTask<FPlatformIdAccessTokenDomain::FModelTask>> FPlatformIdAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FPlatformIdAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FPlatformIdAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Account::Model::FPlatformIdPtr)> Callback
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
        const auto OwnerSubscriptionParentKey = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheKey(Type);
        return Gs2->Cache->Subscribe(
            Gs2::Account::Model::FPlatformId::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Account::Model::FPlatformId>(obj));
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
                const auto Domain = MakeShared<FPlatformIdAccessTokenDomain>(
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

    void FPlatformIdAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto OwnerSubscriptionParentKey = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Account::Model::Cache::FPlatformIdCache::CreateCacheKey(Type);
        Gs2->Cache->Unsubscribe(
            Gs2::Account::Model::FPlatformId::TypeName,
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
