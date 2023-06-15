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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Key::Domain::Model
{

    FKeyDomain::FKeyDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> KeyName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Key::FGs2KeyRestClient>(Session)),
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
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FKeyDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FKeyDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Key"
                );
                const auto Key = Gs2::Key::Domain::Model::FKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Key::Model::FKey::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
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
        const TSharedPtr<FKeyDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Key"
                );
                const auto Key = Gs2::Key::Domain::Model::FKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Key::Model::FKey::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
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
        const TSharedPtr<FKeyDomain> Self,
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
            ->WithNamespaceName(Self->NamespaceName)
            ->WithKeyName(Self->KeyName);
        const auto Future = Self->Client->DeleteKey(
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
                const auto ParentKey = Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "Key"
                );
                const auto Key = Gs2::Key::Domain::Model::FKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Key::Model::FKey::TypeName, ParentKey, Key);
            }
        }
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
        const TSharedPtr<FKeyDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        Domain->Data = Domain->Data = ResultModel->GetData();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FEncryptTask>> FKeyDomain::Encrypt(
        Request::FEncryptRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FEncryptTask>>(this->AsShared(), Request);
    }

    FKeyDomain::FDecryptTask::FDecryptTask(
        const TSharedPtr<FKeyDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
        }
        const auto Domain = Self;
        Domain->Data = Domain->Data = ResultModel->GetData();
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
        return FString() +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (KeyName.IsSet() ? *KeyName : "null") + ":" +
            ChildType;
    }

    FString FKeyDomain::CreateCacheKey(
        TOptional<FString> KeyName
    )
    {
        return FString() +
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Key::Model::FKey> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Key::Model::FKey>(
            Self->ParentKey,
            Gs2::Key::Domain::Model::FKeyDomain::CreateCacheKey(
                Self->KeyName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Key::Request::FGetKeyRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Key::Domain::Model::FKeyDomain::CreateCacheKey(
                    Self->KeyName
                );
                Self->Cache->Put(
                    Gs2::Key::Model::FKey::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "key")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Key::Model::FKey>(
                Self->ParentKey,
                Gs2::Key::Domain::Model::FKeyDomain::CreateCacheKey(
                    Self->KeyName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FKeyDomain::FModelTask>> FKeyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FKeyDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

