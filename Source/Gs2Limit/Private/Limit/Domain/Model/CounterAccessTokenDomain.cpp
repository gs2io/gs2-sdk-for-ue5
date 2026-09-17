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

#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/Namespace.h"
#include "Limit/Domain/Model/Counter.h"
#include "Limit/Domain/Model/CounterAccessToken.h"
#include "Limit/Domain/Model/LimitModelMaster.h"
#include "Limit/Domain/Model/CurrentLimitMaster.h"
#include "Limit/Domain/Model/LimitModel.h"
#include "Limit/Domain/Model/User.h"
#include "Limit/Domain/Model/UserAccessToken.h"
#include "Limit/Model/Cache/Counter.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionAccessTokenDomain.h"

namespace Gs2::Limit::Domain::Model
{

    FCounterAccessTokenDomain::FCounterAccessTokenDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Limit::Domain::FGs2LimitDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TOptional<FString> LimitName,
        const TOptional<FString> CounterName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Limit::FGs2LimitRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        AccessToken(AccessToken),
        LimitName(LimitName),
        CounterName(CounterName),
        ParentKey(Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        ))
    {
    }

    FCounterAccessTokenDomain::FCounterAccessTokenDomain(
        const FCounterAccessTokenDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        AccessToken(From.AccessToken),
        LimitName(From.LimitName),
        CounterName(From.CounterName),
        ParentKey(From.ParentKey)
    {

    }

    FCounterAccessTokenDomain::FGetTask::FGetTask(
        const TSharedPtr<FCounterAccessTokenDomain>& Self,
        const Request::FGetCounterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterAccessTokenDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->GetCounter(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItem().IsValid())
        {
            Gs2::Limit::Model::Cache::FCounterCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(), Self->UserId(), Request->GetLimitName(),
                Request->GetCounterName(), Self->AccessToken->GetTimeOffset(), ResultModel->GetItem()
            );
        }
        *Result = ResultModel.IsValid() ? ResultModel->GetItem() : nullptr;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FGetTask>> FCounterAccessTokenDomain::Get(
        Request::FGetCounterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FCounterAccessTokenDomain::FCountUpTask::FCountUpTask(
        const TSharedPtr<FCounterAccessTokenDomain>& Self,
        const Request::FCountUpRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterAccessTokenDomain::FCountUpTask::FCountUpTask(
        const FCountUpTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FCountUpTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName)
            ->WithAccessToken(Self->AccessToken->GetToken());
        const auto Future = Self->Client->CountUp(
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
            Gs2::Limit::Model::Cache::FCounterCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                ResultModel->GetItem()->GetLimitName(),
                Request->GetCounterName(),
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                ResultModel->GetItem()
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FCountUpTask>> FCounterAccessTokenDomain::CountUp(
        Request::FCountUpRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCountUpTask>>(this->AsShared(), Request);
    }

    FCounterAccessTokenDomain::FVerifyTask::FVerifyTask(
        const TSharedPtr<FCounterAccessTokenDomain>& Self,
        const Request::FVerifyCounterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCounterAccessTokenDomain::FVerifyTask::FVerifyTask(
        const FVerifyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FVerifyTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Domain::Model::FCounterAccessTokenDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithAccessToken(Self->AccessToken->GetToken())
            ->WithLimitName(Self->LimitName)
            ->WithCounterName(Self->CounterName);
        const auto Future = Self->Client->VerifyCounter(
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
            Gs2::Limit::Model::Cache::FCounterCache::Put(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                ResultModel->GetItem()->GetLimitName(),
                Request->GetCounterName(),
                Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                ResultModel->GetItem()
            );
        }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FVerifyTask>> FCounterAccessTokenDomain::Verify(
        Request::FVerifyCounterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FVerifyTask>>(this->AsShared(), Request);
    }

    FString FCounterAccessTokenDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        TOptional<FString> LimitName,
        TOptional<FString> CounterName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            (LimitName.IsSet() ? *LimitName : "null") + ":" +
            (CounterName.IsSet() ? *CounterName : "null") + ":" +
            ChildType;
    }

    FString FCounterAccessTokenDomain::CreateCacheKey(
        TOptional<FString> LimitName,
        TOptional<FString> CounterName
    )
    {
        return FString("") +
            (LimitName.IsSet() ? *LimitName : "null") + ":" + 
            (CounterName.IsSet() ? *CounterName : "null");
    }

    FCounterAccessTokenDomain::FModelTask::FModelTask(
        const TSharedPtr<FCounterAccessTokenDomain> Self
    ): Self(Self)
    {

    }

    FCounterAccessTokenDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Limit::Model::FCounter>> Result
    )
    {
        const auto CacheParentKey = Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(

            Self->NamespaceName,
            Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
            Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto CacheKey = Gs2::Limit::Model::Cache::FCounterCache::CreateCacheKey(

            Self->LimitName,
            Self->CounterName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Limit::Model::FCounter::TypeName,
            CacheParentKey,
            CacheKey,
            [this, Result, CacheKey]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Limit::Model::FCounterPtr Value;
                if (Gs2::Limit::Model::Cache::FCounterCache::TryGet(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->LimitName,
                    Self->CounterName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    &Value
                ))
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Limit::Model::Cache::FCounterCache::Fetch(
                    Self->Gs2->Cache,
                    Self->NamespaceName,
                    Self->AccessToken.IsValid() ? Self->UserId() : TOptional<FString>(),
                    Self->LimitName,
                    Self->CounterName,
                    Self->AccessToken.IsValid() ? Self->AccessToken->GetTimeOffset() : TOptional<int32>(),
                    [Self = Self](Gs2::Limit::Model::FCounterPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Limit::Request::FGetCounterRequest>()
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
                if (Error.IsValid())
                {
                    return Error;
                }
                *Result = Value;
                return nullptr;
            }
        );
    }

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FModelTask>> FCounterAccessTokenDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FCounterAccessTokenDomain::FModelTask>>(this->AsShared());
    }

    FCounterAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FCounterAccessTokenDomain> Self,
        const TFunction<void(Gs2::Limit::Model::FCounterPtr)>& Callback
    ): Self(Self), Callback(Callback)
    {
    }

    FCounterAccessTokenDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ): TGs2Future(From), Self(From.Self), Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCounterAccessTokenDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FCounterAccessTokenDomain::FSubscribeWithInitialCallTask>> FCounterAccessTokenDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Limit::Model::FCounterPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    void FCounterAccessTokenDomain::Invalidate()
    {
        Gs2::Limit::Model::Cache::FCounterCache::Delete(
            Gs2->Cache,
            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            LimitName,
            CounterName,
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
    }

    Gs2::Core::Domain::CallbackID FCounterAccessTokenDomain::Subscribe(
        TFunction<void(Gs2::Limit::Model::FCounterPtr)> Callback
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Gs2::Limit::Domain::FGs2LimitDomain> WeakService = Service;
        const FString RegisteredParentKey = ParentKey;
        const TOptional<FString> QueryNamespace = NamespaceName;
        const TOptional<FString> QueryLimit = LimitName;
        const TOptional<FString> QueryCounter = CounterName;
        const auto SourceToken = AccessToken;
        const TOptional<FString> RegisteredUserId = SourceToken.IsValid()
            ? TOptional<FString>(SourceToken->GetUserId())
            : TOptional<FString>();
        const auto RegisteredTimeOffset = SourceToken.IsValid() ? SourceToken->GetTimeOffset() : TOptional<int32>();
        const auto OwnerSubscriptionParentKey = Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(

            NamespaceName,
            AccessToken.IsValid() ? UserId() : TOptional<FString>(),
            AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
        );
        const auto OwnerSubscriptionKey = Gs2::Limit::Model::Cache::FCounterCache::CreateCacheKey(

            LimitName,
            CounterName
        );
        return Gs2->Cache->Subscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            OwnerSubscriptionParentKey,
            OwnerSubscriptionKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Limit::Model::FCounter>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespace, QueryLimit, QueryCounter, SourceToken, RegisteredUserId, RegisteredTimeOffset]()
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
                const auto Domain = MakeShared<FCounterAccessTokenDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespace,
                    TokenSnapshot,
                    QueryLimit,
                    QueryCounter
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FCounterAccessTokenDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->Unsubscribe(
            Gs2::Limit::Model::FCounter::TypeName,
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheParentKey(
                NamespaceName,
                AccessToken.IsValid() ? UserId() : TOptional<FString>(),
                AccessToken.IsValid() ? AccessToken->GetTimeOffset() : TOptional<int32>()
            ),
            Gs2::Limit::Model::Cache::FCounterCache::CreateCacheKey(
                LimitName,
                CounterName
            ),
            CallbackID
        );
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif
