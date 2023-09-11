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

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::Key::Domain::Model
{

    FGitHubApiKeyDomain::FGitHubApiKeyDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> ApiKeyName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::Key::FGs2KeyRestClient>(Session)),
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
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ApiKeyName(From.ApiKeyName),
        ParentKey(From.ParentKey)
    {

    }

    FGitHubApiKeyDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FGitHubApiKeyDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "GitHubApiKey"
                );
                const auto Key = Gs2::Key::Domain::Model::FGitHubApiKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Key::Model::FGitHubApiKey::TypeName,
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

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FUpdateTask>> FGitHubApiKeyDomain::Update(
        Request::FUpdateGitHubApiKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FGitHubApiKeyDomain::FGetTask::FGetTask(
        const TSharedPtr<FGitHubApiKeyDomain> Self,
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
        const auto RequestModel = Request;
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel != nullptr) {
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Key::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    "GitHubApiKey"
                );
                const auto Key = Gs2::Key::Domain::Model::FGitHubApiKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Key::Model::FGitHubApiKey::TypeName,
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

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FGetTask>> FGitHubApiKeyDomain::Get(
        Request::FGetGitHubApiKeyRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(this->AsShared(), Request);
    }

    FGitHubApiKeyDomain::FDeleteTask::FDeleteTask(
        const TSharedPtr<FGitHubApiKeyDomain> Self,
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
            ->WithNamespaceName(Self->NamespaceName)
            ->WithApiKeyName(Self->ApiKeyName);
        const auto Future = Self->Client->DeleteGitHubApiKey(
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
                    "GitHubApiKey"
                );
                const auto Key = Gs2::Key::Domain::Model::FGitHubApiKeyDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::Key::Model::FGitHubApiKey::TypeName, ParentKey, Key);
            }
        }
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
        // ReSharper disable once CppLocalVariableMayBeConst
        TSharedPtr<Gs2::Key::Model::FGitHubApiKey> Value;
        auto bCacheHit = Self->Cache->TryGet<Gs2::Key::Model::FGitHubApiKey>(
            Self->ParentKey,
            Gs2::Key::Domain::Model::FGitHubApiKeyDomain::CreateCacheKey(
                Self->ApiKeyName
            ),
            &Value
        );
        if (!bCacheHit) {
            const auto Future = Self->Get(
                MakeShared<Gs2::Key::Request::FGetGitHubApiKeyRequest>()
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                if (Future->GetTask().Error()->Type() != Gs2::Core::Model::FNotFoundError::TypeString)
                {
                    return Future->GetTask().Error();
                }

                const auto Key = Gs2::Key::Domain::Model::FGitHubApiKeyDomain::CreateCacheKey(
                    Self->ApiKeyName
                );
                Self->Cache->Put(
                    Gs2::Key::Model::FGitHubApiKey::TypeName,
                    Self->ParentKey,
                    Key,
                    nullptr,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );

                if (Future->GetTask().Error()->Detail(0)->GetComponent() != "gitHubApiKey")
                {
                    return Future->GetTask().Error();
                }
            }
            Self->Cache->TryGet<Gs2::Key::Model::FGitHubApiKey>(
                Self->ParentKey,
                Gs2::Key::Domain::Model::FGitHubApiKeyDomain::CreateCacheKey(
                    Self->ApiKeyName
                ),
                &Value
            );
            Future->EnsureCompletion();
        }
        *Result = Value;

        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGitHubApiKeyDomain::FModelTask>> FGitHubApiKeyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FGitHubApiKeyDomain::FModelTask>>(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

