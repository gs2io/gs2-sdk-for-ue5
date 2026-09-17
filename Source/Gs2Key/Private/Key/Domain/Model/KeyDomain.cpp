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

#include "Key/Domain/Model/Key.h"
#include "Key/Domain/Model/Namespace.h"
#include "Key/Domain/Model/Key.h"
#include "Key/Domain/Model/GitHubApiKey.h"
#include "Key/Model/Cache/Key.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::Key::Domain::Model
{

    FKeyDomain::FKeyDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const Key::Domain::FGs2KeyDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> KeyName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::Key::FGs2KeyRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        KeyName(KeyName),
        ParentKey(Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "Key"
        ))
    {
    }

    FKeyDomain::FKeyDomain(
        const FKeyDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        KeyName(From.KeyName),
        ParentKey(From.ParentKey)
    {

    }

    FKeyDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FKeyDomain>& Self,
        const Request::FUpdateKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FKeyDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithKeyName(Self->KeyName);
        const auto Future = Self->Client->UpdateKey(
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


        Gs2::Key::Model::Cache::FKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetKeyName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FUpdateTask>> FKeyDomain::Update(
        Request::FUpdateKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FKeyDomain::FGetTask::FGetTask(
        const TSharedPtr<FKeyDomain>& Self,
        const Request::FGetKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FKeyDomain::FGetTask::FGetTask(
        const FGetTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Model::FKey>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithKeyName(Self->KeyName);
        const auto Future = Self->Client->GetKey(
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


        Gs2::Key::Model::Cache::FKeyCache::Put(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetKeyName(),
            TOptional<int32>(),
            ResultModel->GetItem()
        );
            }
        *Result = ResultModel->GetItem();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FGetTask>> FKeyDomain::Get(
        Request::FGetKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FKeyDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FKeyDomain>& Self,
        const Request::FDeleteKeyRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FKeyDomain::FDeleteTask::FDeleteTask(
        const FDeleteTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FDeleteTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithKeyName(Self->KeyName);
        const auto Future = Self->Client->DeleteKey(
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


              Gs2::Key::Model::Cache::FKeyCache::Delete(
            Self->Gs2->Cache,

            Request->GetNamespaceName(),
            Request->GetKeyName(),
            TOptional<int32>()
        );
        auto Domain = Self;

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FDeleteTask>> FKeyDomain::Delete(
        Request::FDeleteKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTask>>(this->AsShared(), Request);
    }

    FKeyDomain::FEncryptTask::FEncryptTask(
        const TSharedPtr<FKeyDomain>& Self,
        const Request::FEncryptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FKeyDomain::FEncryptTask::FEncryptTask(
        const FEncryptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FEncryptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithKeyName(Self->KeyName);
        const auto Future = Self->Client->Encrypt(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetData().IsSet())
            {
                Self->Data = Domain->Data = ResultModel->GetData();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FEncryptTask>> FKeyDomain::Encrypt(
        Request::FEncryptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEncryptTask>>(this->AsShared(), Request);
    }

    FKeyDomain::FDecryptTask::FDecryptTask(
        const TSharedPtr<FKeyDomain>& Self,
        const Request::FDecryptRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FKeyDomain::FDecryptTask::FDecryptTask(
        const FDecryptTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FDecryptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Domain::Model::FKeyDomain>> Result
    )
    {
        Request
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
            ->WithNamespaceName(Self->NamespaceName)
            ->WithKeyName(Self->KeyName);
        const auto Future = Self->Client->Decrypt(
            Request
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        const auto Domain = Self;
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetData().IsSet())
            {
                Self->Data = Domain->Data = ResultModel->GetData();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FDecryptTask>> FKeyDomain::Decrypt(
        Request::FDecryptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDecryptTask>>(this->AsShared(), Request);
    }

    FString FKeyDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> KeyName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (KeyName.IsSet() ? *KeyName : "null") + ":" +
            ChildType;
    }

    FString FKeyDomain::CreateCacheKey(
        TOptional<FString> KeyName
    )
    {
        return FString("") +
            (KeyName.IsSet() ? *KeyName : "null");
    }

    FKeyDomain::FModelTask::FModelTask(
        const TSharedPtr<FKeyDomain> Self
    ): Self(Self)
    {

    }

    FKeyDomain::FModelTask::FModelTask(
        const FModelTask& From
    ): TGs2Future(From), Self(From.Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Key::Model::FKey>> Result
    )
    {
        const auto CacheParentKey = Gs2::Key::Model::Cache::FKeyCache::CreateCacheParentKey(

            Self->NamespaceName,
            TOptional<int32>()
        );
        const auto CacheKey = Gs2::Key::Model::Cache::FKeyCache::CreateCacheKey(

            Self->KeyName
        );
        return Self->Gs2->Cache->ExecuteWithKeyLock(
            Gs2::Key::Model::FKey::TypeName,
            CacheParentKey,
            CacheKey,
            [Self = Self, Result]() -> Gs2::Core::Model::FGs2ErrorPtr
            {
                Gs2::Key::Model::FKeyPtr Value;
                const auto CacheHit = Gs2::Key::Model::Cache::FKeyCache::TryGet(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->KeyName,
                    TOptional<int32>(),
                    &Value
                );
                if (CacheHit)
                {
                    *Result = Value;
                    return nullptr;
                }
                const auto Error = Gs2::Key::Model::Cache::FKeyCache::Fetch(
                    Self->Gs2->Cache,

                    Self->NamespaceName,
                    Self->KeyName,
                    TOptional<int32>(),
                    [Self](Gs2::Key::Model::FKeyPtr* OutItem) -> Gs2::Core::Model::FGs2ErrorPtr
                    {
                        const auto Future = Self->Get(
                            MakeShared<Gs2::Key::Request::FGetKeyRequest>()
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

    TSharedPtr<FAsyncTask<FKeyDomain::FModelTask>> FKeyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FKeyDomain::FModelTask>>(this->AsShared());
    }

    void FKeyDomain::Invalidate()
    {
        Gs2::Key::Model::Cache::FKeyCache::Delete(
            Gs2->Cache,

            NamespaceName,
            KeyName,
            TOptional<int32>()
        );
    }

    FKeyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const TSharedPtr<FKeyDomain>& Self,
        TFunction<void(Gs2::Key::Model::FKeyPtr)> Callback
    ):
        Self(Self),
        Callback(Callback)
    {
    }

    FKeyDomain::FSubscribeWithInitialCallTask::FSubscribeWithInitialCallTask(
        const FSubscribeWithInitialCallTask& From
    ):
        TGs2Future(From),
        Self(From.Self),
        Callback(From.Callback)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FKeyDomain::FSubscribeWithInitialCallTask::Action(
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

    TSharedPtr<FAsyncTask<FKeyDomain::FSubscribeWithInitialCallTask>> FKeyDomain::SubscribeWithInitialCall(
        TFunction<void(Gs2::Key::Model::FKeyPtr)> Callback
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeWithInitialCallTask>>(this->AsShared(), Callback);
    }

    Gs2::Core::Domain::CallbackID FKeyDomain::Subscribe(
        TFunction<void(Gs2::Key::Model::FKeyPtr)> Callback
    )
    {
        const auto SubscriptionParentKey = Gs2::Key::Model::Cache::FKeyCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Key::Model::Cache::FKeyCache::CreateCacheKey(

            KeyName
        );
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = Gs2;
        const TWeakPtr<Key::Domain::FGs2KeyDomain> WeakService = Service;
        const FString RegisteredParentKey = SubscriptionParentKey;
        const TOptional<FString> QueryNamespaceName = NamespaceName;
        const TOptional<FString> QueryKeyName = KeyName;
        return Gs2->Cache->Subscribe(
            Gs2::Key::Model::FKey::TypeName,
            SubscriptionParentKey,
            SubscriptionCacheKey,
            [Callback](TSharedPtr<FGs2Object> obj)
            {
                Callback(StaticCastSharedPtr<Gs2::Key::Model::FKey>(obj));
            },
            [WeakGs2, WeakService, RegisteredParentKey, QueryNamespaceName, QueryKeyName]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid())
                {
                    return;
                }
                const auto Domain = MakeShared<FKeyDomain>(
                    Owner,
                    WeakService.Pin(),
                    QueryNamespaceName,
                    QueryKeyName
                );
                Domain->ParentKey = RegisteredParentKey;
                const auto Task = Domain->Model();
                Task->StartBackgroundTask();
            }
        );
    }

    void FKeyDomain::Unsubscribe(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        const auto SubscriptionParentKey = Gs2::Key::Model::Cache::FKeyCache::CreateCacheParentKey(

            NamespaceName,
            TOptional<int32>()
        );
        const auto SubscriptionCacheKey = Gs2::Key::Model::Cache::FKeyCache::CreateCacheKey(

            KeyName
        );
        Gs2->Cache->Unsubscribe(
            Gs2::Key::Model::FKey::TypeName,
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
