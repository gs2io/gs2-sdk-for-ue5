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

// ReSharper disable CppUnusedIncludeDirective

#include "News/Domain/Gs2News.h"
#include "News/Domain/Model/Namespace.h"
#include "News/Domain/Model/CurrentNewsMaster.h"
#include "News/Domain/Model/News.h"
#include "News/Domain/Model/User.h"
#include "News/Domain/Model/UserAccessToken.h"

namespace Gs2::News::Domain
{

    FGs2NewsDomain::FGs2NewsDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::News::FGs2NewsRestClient>(Session)),
        ParentKey("news")
    {
    }

    FGs2NewsDomain::FGs2NewsDomain(
        const FGs2NewsDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGs2NewsDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2NewsDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2NewsDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2NewsDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::News::Domain::Model::FNamespaceDomain>> Result
    )
    {
        const auto Future = Self->Client->CreateNamespace(
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
            
            {
                const auto ParentKey = FString("news:Namespace");
                const auto Key = Gs2::News::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::News::Model::FNamespace>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::News::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2NewsDomain::FCreateNamespaceTask>> FGs2NewsDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::News::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2NewsDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::News::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::News::Domain::Model::FNamespaceDomain> FGs2NewsDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::News::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    void FGs2NewsDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2NewsDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2NewsDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2NewsDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

