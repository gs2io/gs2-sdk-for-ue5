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

#include "Key/Domain/Model/GitHubApiKey.h"
#include "Key/Domain/Model/Namespace.h"
#include "Key/Domain/Model/Key.h"
#include "Key/Domain/Model/GitHubApiKey.h"
#include "Key/Model/Cache/GitHubApiKey.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Key::Domain::Model
{

    FGitHubApiKeyDomain::FGitHubApiKeyDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Key::Domain::FGs2KeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ApiKeyName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Key::FGs2KeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ApiKeyName(ApiKeyName),
        ParentKey(Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "GitHubApiKey"
        ))
    {
    }

    FGitHubApiKeyDomain::FGitHubApiKeyDomain(
        const FGitHubApiKeyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ApiKeyName(From.ApiKeyName),
        ParentKey(From.ParentKey)
    {

    }

    FGitHubApiKeyDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGitHubApiKeyDomain>& Self,
        const Request::FUpdateGitHubApiKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGitHubApiKeyDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGitHubApiKeyDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithApiKeyName(Self->ApiKeyName);
        const auto Future = Self->Client->UpdateGitHubApiKey(
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


        Gs2::Key::Model::Cache::FGitHubApiKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetApiKeyName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FUpdateTask>> FGitHubApiKeyDomain::Update(
        Request::FUpdateGitHubApiKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGitHubApiKeyDomain::FGetTask::FGetTask(
        const TSharedPtr<FGitHubApiKeyDomain>& Self,
        const Request::FGetGitHubApiKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGitHubApiKeyDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGitHubApiKeyDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Model::FGitHubApiKey>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithApiKeyName(Self->ApiKeyName);
        const auto Future = Self->Client->GetGitHubApiKey(
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


        Gs2::Key::Model::Cache::FGitHubApiKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetApiKeyName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FGetTask>> FGitHubApiKeyDomain::Get(
        Request::FGetGitHubApiKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGitHubApiKeyDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FGitHubApiKeyDomain>& Self,
        const Request::FDeleteGitHubApiKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGitHubApiKeyDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGitHubApiKeyDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FGitHubApiKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithApiKeyName(Self->ApiKeyName);
        const auto Future = Self->Client->DeleteGitHubApiKey(
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


              Gs2::Key::Model::Cache::FGitHubApiKeyCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetApiKeyName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FDeleteTask>> FGitHubApiKeyDomain::Delete(
        Request::FDeleteGitHubApiKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FString FGitHubApiKeyDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> ApiKeyName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (ApiKeyName.IsSet() ? *ApiKeyName : "null") + ":" +
            ChildType;
    }

    FString FGitHubApiKeyDomain::CreateCacheKey(
        TOptional<FString> ApiKeyName
    )
    {
        return FString("") +
            (ApiKeyName.IsSet() ? *ApiKeyName : "null");
    }

    FGitHubApiKeyDomain::FModelTask::FModelTask(
        const TSharedPtr<FGitHubApiKeyDomain> Self
    ): Self(Self)
    {

    }

    FGitHubApiKeyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FGitHubApiKeyDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Model::FGitHubApiKey>> Result
    )
    {
        const auto CacheParentKey = Gs2::Key::Model::Cache::FGitHubApiKeyCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Key::Model::Cache::FGitHubApiKeyCache::CreateCacheKey(

            Self->ApiKeyName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Key::Model::FGitHubApiKey::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Key::Model::FGitHubApiKeyPtr Value;
                const auto CacheHit = Gs2::Key::Model::Cache::FGitHubApiKeyCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ApiKeyName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Key::Model::Cache::FGitHubApiKeyCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->ApiKeyName,
                    TOptional<int32>(),
                    [Self](Gs2::Key::Model::FGitHubApiKeyPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Key::Request::FGetGitHubApiKeyRequest>()
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

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FModelTask>> FGitHubApiKeyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGitHubApiKeyDomain::FModelTask>>(this->AsShared());
    }

    void FGitHubApiKeyDomain::Invalidate()
    {
        Gs2::Key::Model::Cache::FGitHubApiKeyCache::Delete(
            Gs2->Cache,

            NamespaceName,
            ApiKeyName,
            TOptional<int32>()
        );
    }

    FGitHubApiKeyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FGitHubApiKeyDomain>& Self,
        TFunction<void(Gs2::Key::Model::FGitHubApiKeyPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FGitHubApiKeyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGitHubApiKeyDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FSubscribeWithInitialCallTask>> FGitHubApiKeyDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Key::Model::FGitHubApiKeyPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FGitHubApiKeyDomain::Subscribe(
        TFunction<void(Gs2::Key::Model::FGitHubApiKeyPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Key::Model::Cache::FGitHubApiKeyCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Key::Model::Cache::FGitHubApiKeyCache::CreateCacheKey(

            ApiKeyName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Key::Domain::FGs2KeyDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryApiKeyName = ApiKeyName;
        return Gs2->Cache->Subscribe(
            Gs2::Key::Model::FGitHubApiKey::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Key::Model::FGitHubApiKey>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryApiKeyName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FGitHubApiKeyDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryApiKeyName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FGitHubApiKeyDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Key::Model::Cache::FGitHubApiKeyCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Key::Model::Cache::FGitHubApiKeyCache::CreateCacheKey(

            ApiKeyName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Key::Model::FGitHubApiKey::TypeName,
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
