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

#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/Progress.h"
#include "News/Domain/Model/Output.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"
#include "News/Domain/Model/NewsAccessToken.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/SetCookieRequestEntry.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::News::Domain::Model
{

    FCurrentNewsMasterDomain::FCurrentNewsMasterDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const News::Domain::FGs2NewsDomainPtr& Service,
        const TOptional<FString> NamespaceName
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Gs2->RestSession)),
        NamespaceName(NamespaceName),
        ParentKey(Gs2::News::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "CurrentNewsMaster"
        ))
    {
    }

    FCurrentNewsMasterDomain::FCurrentNewsMasterDomain(
        const FCurrentNewsMasterDomain& From
    ):
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        ParentKey(From.ParentKey)
    {

    }

    FCurrentNewsMasterDomain::FPrepareUpdateTask::FPrepareUpdateTask(
        const TSharedPtr<FCurrentNewsMasterDomain>& Self,
        const Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentNewsMasterDomain::FPrepareUpdateTask::FPrepareUpdateTask(
        const FPrepareUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentNewsMasterDomain::FPrepareUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PrepareUpdateCurrentNewsMaster(
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
            if (ResultModel->GetTemplateUploadUrl().IsSet())
            {
                Self->TemplateUploadUrl = Domain->TemplateUploadUrl = ResultModel->GetTemplateUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentNewsMasterDomain::FPrepareUpdateTask>> FCurrentNewsMasterDomain::PrepareUpdate(
        Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentNewsMasterDomain::FUpdateTask::FUpdateTask(
        const TSharedPtr<FCurrentNewsMasterDomain>& Self,
        const Request::FUpdateCurrentNewsMasterRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentNewsMasterDomain::FUpdateTask::FUpdateTask(
        const FUpdateTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentNewsMasterDomain::FUpdateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->UpdateCurrentNewsMaster(
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
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentNewsMasterDomain::FUpdateTask>> FCurrentNewsMasterDomain::Update(
        Request::FUpdateCurrentNewsMasterRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTask>>(this->AsShared(), Request);
    }

    FCurrentNewsMasterDomain::FPrepareUpdateFromGitHubTask::FPrepareUpdateFromGitHubTask(
        const TSharedPtr<FCurrentNewsMasterDomain>& Self,
        const Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FCurrentNewsMasterDomain::FPrepareUpdateFromGitHubTask::FPrepareUpdateFromGitHubTask(
        const FPrepareUpdateFromGitHubTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FCurrentNewsMasterDomain::FPrepareUpdateFromGitHubTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FCurrentNewsMasterDomain>> Result
    )
    {
        Request
            ->WithContextStack(Self->Gs2->DefaultContextStack)
            ->WithNamespaceName(Self->NamespaceName);
        const auto Future = Self->Client->PrepareUpdateCurrentNewsMasterFromGitHub(
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUploadToken().IsSet())
            {
                Self->UploadToken = Domain->UploadToken = ResultModel->GetUploadToken();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCurrentNewsMasterDomain::FPrepareUpdateFromGitHubTask>> FCurrentNewsMasterDomain::PrepareUpdateFromGitHub(
        Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareUpdateFromGitHubTask>>(this->AsShared(), Request);
    }

    FString FCurrentNewsMasterDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            ChildType;
    }

    FString FCurrentNewsMasterDomain::CreateCacheKey(
    )
    {
        return "Singleton";
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

