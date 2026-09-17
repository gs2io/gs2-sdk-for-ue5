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

#include "Identifier/Domain/Model/AttachSecurityPolicy.h"
#include "Identifier/Domain/Model/User.h"
#include "Identifier/Domain/Model/SecurityPolicy.h"
#include "Identifier/Domain/Model/Identifier.h"
#include "Identifier/Domain/Model/Password.h"
#include "Identifier/Domain/Model/AttachSecurityPolicy.h"
#include "Identifier/Model/Cache/AttachSecurityPolicy.h"
#include "Identifier/Model/Cache/SecurityPolicy.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Identifier::Domain::Model
{

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Identifier::Domain::FGs2IdentifierDomainPtr& Service,
        const TOptional<FString> UserName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Identifier::FGs2IdentifierRestClient>(Gs2->RestSession)),
        UserName(UserName),
        ParentKey(Gs2::Identifier::Domain::Model::FUserDomain::CreateCacheParentKey(
            UserName,
            "AttachSecurityPolicy"
        ))
    {
    }

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyDomain(
        const FAttachSecurityPolicyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        UserName(From.UserName),
        ParentKey(From.ParentKey)
    {

    }

    FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask::FGetHasSecurityPolicyTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        const Request::FGetHasSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask::FGetHasSecurityPolicyTask(
        const FGetHasSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->GetHasSecurityPolicy(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Put(
                    Self->Gs2->Cache,
                    Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FGetHasSecurityPolicyTask>> FAttachSecurityPolicyDomain::GetHasSecurityPolicy(
        Request::FGetHasSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetHasSecurityPolicyTask>>(this->AsShared(), Request);
    }

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask::FAttachSecurityPolicyTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        const Request::FAttachSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask::FAttachSecurityPolicyTask(
        const FAttachSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->AttachSecurityPolicy(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Put(
                    Self->Gs2->Cache,
                    Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FAttachSecurityPolicyTask>> FAttachSecurityPolicyDomain::AttachSecurityPolicy(
        Request::FAttachSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FAttachSecurityPolicyTask>>(this->AsShared(), Request);
    }

    FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask::FDetachSecurityPolicyTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        const Request::FDetachSecurityPolicyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask::FDetachSecurityPolicyTask(
        const FDetachSecurityPolicyTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithUserName(Self->UserName);
        const auto Future = Self->Client->DetachSecurityPolicy(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::Identifier::Model::Cache::FSecurityPolicyCache::Put(
                    Self->Gs2->Cache,
                    Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::Identifier::Domain::Model::FSecurityPolicyDomain>(
                    Self->Gs2,
                    Self->Service,
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FDetachSecurityPolicyTask>> FAttachSecurityPolicyDomain::DetachSecurityPolicy(
        Request::FDetachSecurityPolicyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDetachSecurityPolicyTask>>(this->AsShared(), Request);
    }

    FString FAttachSecurityPolicyDomain::CreateCacheParentKey(
        TOptional<FString> UserName,
        FString ChildType
    )
    {
        return FString("") +
            (UserName.IsSet() ? *UserName : "null") + ":" +
            ChildType;
    }

    FString FAttachSecurityPolicyDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }

    FAttachSecurityPolicyDomain::FModelTask::FModelTask(
        const TSharedPtr<FAttachSecurityPolicyDomain> Self
    ): Self(Self)
    {

    }

    FAttachSecurityPolicyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy>> Result
    )
    {
        const auto CacheParentKey = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::CreateCacheParentKey(

            Self->UserName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::CreateCacheKey(

        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Identifier::Model::FAttachSecurityPolicyPtr Value;
                const auto CacheHit = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::TryGet(
                    Self->Gs2->Cache,

                    Self->UserName,
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

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FModelTask>> FAttachSecurityPolicyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FAttachSecurityPolicyDomain::FModelTask>>(this->AsShared());
    }

    void FAttachSecurityPolicyDomain::Invalidate()
    {
        Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::Delete(
            Gs2->Cache,

            UserName,
            TOptional<int32>()
        );
    }

    FAttachSecurityPolicyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FAttachSecurityPolicyDomain>& Self,
        TFunction<void(Gs2::Identifier::Model::FAttachSecurityPolicyPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FAttachSecurityPolicyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FAttachSecurityPolicyDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FAttachSecurityPolicyDomain::FSubscribeWithInitialCallTask>> FAttachSecurityPolicyDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Identifier::Model::FAttachSecurityPolicyPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FAttachSecurityPolicyDomain::Subscribe(
        TFunction<void(Gs2::Identifier::Model::FAttachSecurityPolicyPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::CreateCacheParentKey(

            UserName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::CreateCacheKey(

        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Identifier::Domain::FGs2IdentifierDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryUserName = UserName;
        return Gs2->Cache->Subscribe(
            Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Identifier::Model::FAttachSecurityPolicy>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryUserName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FAttachSecurityPolicyDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryUserName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FAttachSecurityPolicyDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::CreateCacheParentKey(

            UserName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Identifier::Model::Cache::FAttachSecurityPolicyCache::CreateCacheKey(

        );
        Gs2->Cache->Unsubscribe(
            Gs2::Identifier::Model::FAttachSecurityPolicy::TypeName,
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
