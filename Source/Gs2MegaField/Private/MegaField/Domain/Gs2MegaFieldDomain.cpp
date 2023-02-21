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

#include "MegaField/Domain/Gs2MegaField.h"
#include "MegaField/Domain/Model/Namespace.h"
#include "MegaField/Domain/Model/AreaModel.h"
#include "MegaField/Domain/Model/AreaModelMaster.h"
#include "MegaField/Domain/Model/LayerModel.h"
#include "MegaField/Domain/Model/LayerModelMaster.h"
#include "MegaField/Domain/Model/CurrentFieldMaster.h"
#include "MegaField/Domain/Model/User.h"
#include "MegaField/Domain/Model/UserAccessToken.h"
#include "MegaField/Domain/Model/Spatial.h"

namespace Gs2::MegaField::Domain
{

    FGs2MegaFieldDomain::FGs2MegaFieldDomain(
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
        Client(MakeShared<Gs2::MegaField::FGs2MegaFieldRestClient>(Session)),
        ParentKey("megaField")
    {
    }

    FGs2MegaFieldDomain::FGs2MegaFieldDomain(
        const FGs2MegaFieldDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGs2MegaFieldDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2MegaFieldDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2MegaFieldDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2MegaFieldDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::MegaField::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("megaField:Namespace");
                const auto Key = Gs2::MegaField::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::MegaField::Model::FNamespace>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::MegaField::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2MegaFieldDomain::FCreateNamespaceTask>> FGs2MegaFieldDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::MegaField::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2MegaFieldDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::MegaField::Domain::Model::FNamespaceDomain> FGs2MegaFieldDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::MegaField::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    void FGs2MegaFieldDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2MegaFieldDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2MegaFieldDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2MegaFieldDomain::HandleNotification(
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

