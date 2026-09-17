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

#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"
#include "Identifier/Model/Cache/SecurityPolicy.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FSecurityPolicyDomain::FSecurityPolicyDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> SecurityPolicyName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        SecurityPolicyName(SecurityPolicyName),
        ParentKey("identifier:SecurityPolicy")
    {
    }

    FSecurityPolicyDomain::FSecurityPolicyDomain(
        const FSecurityPolicyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        SecurityPolicyName(From.SecurityPolicyName),
        ParentKey(From.ParentKey)
    {

    }

    FSecurityPolicyDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        const Request::FUpdateSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSecurityPolicyDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithSecurityPolicyName(Self->SecurityPolicyName);
        const auto Future = Self->Client->UpdateSecurityPolicy(
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


        Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Put(
            Self->Gs2->Cache,

            Request->GetSecurityPolicyName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FUpdateTask>> FSecurityPolicyDomain::Update(
        Request::FUpdateSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FSecurityPolicyDomain::FGetTask::FGetTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        const Request::FGetSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSecurityPolicyDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithSecurityPolicyName(Self->SecurityPolicyName);
        const auto Future = Self->Client->GetSecurityPolicy(
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


        Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Put(
            Self->Gs2->Cache,

            Request->GetSecurityPolicyName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FGetTask>> FSecurityPolicyDomain::Get(
        Request::FGetSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FSecurityPolicyDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        const Request::FDeleteSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FSecurityPolicyDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithSecurityPolicyName(Self->SecurityPolicyName);
        const auto Future = Self->Client->DeleteSecurityPolicy(
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


              Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Delete(
            Self->Gs2->Cache,

            Request->GetSecurityPolicyName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FDeleteTask>> FSecurityPolicyDomain::Delete(
        Request::FDeleteSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FSecurityPolicyDomain::CreateCacheParentKey(
        TOptional<FString> SecurityPolicyName,
        FString ChildType
    )
    {
        return FString("") +
            (SecurityPolicyName.IsSet() ? *SecurityPolicyName : "null") + ":" +
            ChildType;
    }

    FString FSecurityPolicyDomain::CreateCacheKey(
        TOptional<FString> SecurityPolicyName
    )
    {
        return FString("") +
            (SecurityPolicyName.IsSet() ? *SecurityPolicyName : "null");
    }

    FSecurityPolicyDomain::FModelTask::FModelTask(
        const TSharedPtr<FSecurityPolicyDomain> Self
    ): Self(Self)
    {

    }

    FSecurityPolicyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>> Result
    )
    {
        const auto CacheParentKey = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::CreateCacheKey(

            Self->SecurityPolicyName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Identifier::Model::FSecurityPolicy::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Identifier::Model::FSecurityPolicyPtr Value;
                const auto CacheHit = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::TryGet(
                    Self->Gs2->Cache,

                    Self->SecurityPolicyName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Fetch(
                    Self->Gs2->Cache,

                    Self->SecurityPolicyName,
                    TOptional<int32>(),
                    [Self](Gs2::Identifier::Model::FSecurityPolicyPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Identifier::Request::FGetSecurityPolicyRequest>()
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

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FModelTask>> FSecurityPolicyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FSecurityPolicyDomain::FModelTask>>(this->AsShared());
    }

    void FSecurityPolicyDomain::Invalidate()
    {
        Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Delete(
            Gs2->Cache,

            SecurityPolicyName,
            TOptional<int32>()
        );
    }

    FSecurityPolicyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FSecurityPolicyDomain>& Self,
        TFunction<void(Gs2::Identifier::Model::FSecurityPolicyPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FSecurityPolicyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FSecurityPolicyDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FSecurityPolicyDomain::FSubscribeWithInitialCallTask>> FSecurityPolicyDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Identifier::Model::FSecurityPolicyPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FSecurityPolicyDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FSecurityPolicyPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::CreateCacheKey(

            SecurityPolicyName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Identifier::Domain::FGs2IdentifierDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QuerySecurityPolicyName = SecurityPolicyName;
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FSecurityPolicy::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FSecurityPolicy>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QuerySecurityPolicyName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FSecurityPolicyDomain>(
                    Owner,
                    WeakService.Pin(),
                    QuerySecurityPolicyName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FSecurityPolicyDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::CreateCacheParentKey(

            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Identifier::Model::Cache::FSecurityPolicyCache::CreateCacheKey(

            SecurityPolicyName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FSecurityPolicy::TypeName,
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
