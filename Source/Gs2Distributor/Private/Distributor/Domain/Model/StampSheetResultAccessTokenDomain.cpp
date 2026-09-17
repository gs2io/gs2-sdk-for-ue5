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

#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"
#include "Distributor/Model/Cache/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/Namespace.h"
#include "Distributor/Domain/Model/DistributorModelMaster.h"
#include "Distributor/Domain/Model/DistributorModel.h"
#include "Distributor/Domain/Model/CurrentDistributorMaster.h"
#include "Distributor/Domain/Model/Distribute.h"
#include "Distributor/Domain/Model/User.h"
#include "Distributor/Domain/Model/UserAccessToken.h"
#include "Distributor/Domain/Model/StampSheetResult.h"
#include "Distributor/Domain/Model/StampSheetResultAccessToken.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Distributor::Domain::Model
{

    FStampSheetResultAccessTokenDomain::FStampSheetResultAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> TransactionId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Distributor::FGs2DistributorRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        TransactionId(TransactionId)
    {
    }

    FStampSheetResultAccessTokenDomain::FStampSheetResultAccessTokenDomain(
        const FStampSheetResultAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        TransactionId(From.TransactionId)
    {

    }

    FStampSheetResultAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FStampSheetResultAccessTokenDomain>& Self,
        const Request::FGetStampSheetResultRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FStampSheetResultAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        const auto RequestNamespaceName = Self->NamespaceName;
        const auto RequestTransactionId = Self->TransactionId;
        Gs2::Auth::Model::FAccessTokenPtr SourceToken;
        if (Self->AccessToken.IsValid())
        {
            SourceToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*Self->AccessToken);
        }
        const auto RequestUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const auto RequestTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(RequestNamespaceName)
            ->WithAccessToken(SourceToken.IsValid() ? SourceToken->GetToken() : TOptional<FString>())
            ->WithTransactionId(RequestTransactionId);
        const auto Future = Self->Client->GetStampSheetResult(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        Gs2::Distributor::Model::FStampSheetResultPtr Item;
        if (ResultModel.IsValid())
        {
            Item = ResultModel->GetItem();
        }
        if (Item.IsValid())
        {
            Gs2::Distributor::Model::Cache::FStampSheetResultCache::Put(
                Self->Gs2->Cache,
                RequestNamespaceName,
                RequestUserId,
                Item->GetTransactionId(),
                RequestTimeOffset,
                Item
            );
        }
        *Result = Item;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStampSheetResultAccessTokenDomain::FGetTask>> FStampSheetResultAccessTokenDomain::Get(
        Request::FGetStampSheetResultRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FString FStampSheetResultAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> TransactionId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (TransactionId.IsSet() ? *TransactionId : "null") + ":" +
            ChildType;
    }

    FString FStampSheetResultAccessTokenDomain::CreateCacheKey(
        TOptional<FString> TransactionId
    )
    {
        return FString("") +
            (TransactionId.IsSet() ? *TransactionId : "null");
    }

    FStampSheetResultAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FStampSheetResultAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FStampSheetResultAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        const auto OwnerUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const auto OwnerTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        Gs2::Distributor::Model::FStampSheetResultPtr Value;
        const bool CacheHit = Gs2::Distributor::Model::Cache::FStampSheetResultCache::TryGet(
            Self->Gs2->Cache,
            Self->NamespaceName,
            OwnerUserId,
            Self->TransactionId,
            OwnerTimeOffset,
            &Value
        );
        if (CacheHit)
        {
            *Result = Value;
            return nullptr;
        }
        return Gs2::Distributor::Model::Cache::FStampSheetResultCache::Fetch(
            Self->Gs2->Cache,
            Self->NamespaceName,
            OwnerUserId,
            Self->TransactionId,
            OwnerTimeOffset,
            [this](Gs2::Distributor::Model::FStampSheetResultPtr* Fetched) -> Gs2::Core::Model::FGs2ErrorPtr
            {
                const auto Future = Self->Get(
                    MakeShared<Gs2::Distributor::Request::FGetStampSheetResultRequest>()
                );
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    const auto Error = Future->GetTask().Error();
                    Future->EnsureCompletion();
                    return Error;
                }
                *Fetched = Future->GetTask().Result();
                Future->EnsureCompletion();
                return nullptr;
            },
            Result.Get()
        );
    }

    TSharedPtr<FAsyncTask<FStampSheetResultAccessTokenDomain::FModelTask>> FStampSheetResultAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FStampSheetResultAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FStampSheetResultAccessTokenDomain::FModelNoCacheTask::FModelNoCacheTask(
        const TSharedPtr<FStampSheetResultAccessTokenDomain> Self
    ):
        Self(Self)
    {
    }

    FStampSheetResultAccessTokenDomain::FModelNoCacheTask::FModelNoCacheTask(
        const FModelNoCacheTask& From
    ):
        Self(From.Self)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultAccessTokenDomain::FModelNoCacheTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Distributor::Model::FStampSheetResult>> Result
    )
    {
        const auto SourceToken = Self->AccessToken;
        const auto OwnerUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const auto OwnerTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        return Gs2::Distributor::Model::Cache::FStampSheetResultCache::Fetch(
            Self->Gs2->Cache,
            Self->NamespaceName,
            OwnerUserId,
            Self->TransactionId,
            OwnerTimeOffset,
            [this](Gs2::Distributor::Model::FStampSheetResultPtr* Fetched) -> Gs2::Core::Model::FGs2ErrorPtr
            {
                const auto Future = Self->Get(
                    MakeShared<Gs2::Distributor::Request::FGetStampSheetResultRequest>()
                );
                Future->StartSynchronousTask();
                if (Future->GetTask().IsError())
                {
                    const auto Error = Future->GetTask().Error();
                    Future->EnsureCompletion();
                    return Error;
                }
                *Fetched = Future->GetTask().Result();
                Future->EnsureCompletion();
                return nullptr;
            },
            Result.Get()
        );
    }

    TSharedPtr<FAsyncTask<FStampSheetResultAccessTokenDomain::FModelNoCacheTask>> FStampSheetResultAccessTokenDomain::ModelNoCache()
    {
        return Gs2::Core::Util::New<FAsyncTask<FStampSheetResultAccessTokenDomain::FModelNoCacheTask>>(this->AsShared());
    }

    FStampSheetResultAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FStampSheetResultAccessTokenDomain> Self,
        const TFunction<void(Gs2::Distributor::Model::FStampSheetResultPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FStampSheetResultAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStampSheetResultAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FStampSheetResultAccessTokenDomain::FSubscribeWithInitialCallTask>> FStampSheetResultAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Distributor::Model::FStampSheetResultPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FStampSheetResultAccessTokenDomain::Invalidate()
    {
        const auto SourceToken = AccessToken;
        Gs2::Distributor::Model::Cache::FStampSheetResultCache::Delete(
            Gs2->Cache,
            NamespaceName,
            SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
            TransactionId,
            SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FStampSheetResultAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Distributor::Model::FStampSheetResultPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Distributor::Domain::FGs2DistributorDomain> WeakService = Service;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryTransactionId = TransactionId;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? SourceToken->GetUserId()
            : TOptional<FString>();
        const TOptional<int32> RegisteredTimeOffset = SourceToken.IsValid()
            ? SourceToken->GetTimeOffset()
            : TOptional<int32>();
        const auto RegisteredParentKey = Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheParentKey(
            QueryNamespaceName,
            RegisteredUserId,
            RegisteredTimeOffset
        );
        const auto RegisteredCacheKey = Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheKey(
            QueryTransactionId
        );
        return Gs2->Cache->Subscribe(
            Gs2::Distributor::Model::FStampSheetResult::TypeName,
            RegisteredParentKey,
            RegisteredCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Distributor::Model::FStampSheetResult>(obj));
            },
            [WeakGs2, WeakService, QueryNamespaceName, QueryTransactionId, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FStampSheetResultAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    TokenSnapshot,
                    QueryTransactionId
                );
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FStampSheetResultAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SourceToken = AccessToken;
        Gs2->Cache->Unsubscribe(
            Gs2::Distributor::Model::FStampSheetResult::TypeName,
            Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheParentKey(
                NamespaceName,
                SourceToken.IsValid() ? SourceToken->GetUserId() : TOptional<FString>(),
                SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Distributor::Model::Cache::FStampSheetResultCache::CreateCacheKey(TransactionId),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
