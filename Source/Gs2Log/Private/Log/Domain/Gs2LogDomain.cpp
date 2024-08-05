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

#include "Log/Domain/Gs2Log.h"
#include "Log/Domain/Model/Namespace.h"
#include "Log/Domain/Model/AccessLog.h"
#include "Log/Domain/Model/IssueStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampSheetLog.h"
#include "Log/Domain/Model/ExecuteStampTaskLog.h"
#include "Log/Domain/Model/InGameLog.h"
#include "Log/Domain/Model/AccessLogWithTelemetry.h"
#include "Log/Domain/Model/User.h"
#include "Log/Domain/Model/UserAccessToken.h"
#include "Log/Domain/Model/Insight.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Log::Domain
{

    FGs2LogDomain::FGs2LogDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Log::FGs2LogRestClient>(Gs2->RestSession)),
        ParentKey("log")
    {
    }

    FGs2LogDomain::FGs2LogDomain(
        const FGs2LogDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2LogDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2LogDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2LogDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2LogDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("log:Namespace");
                const auto Key = Gs2::Log::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Log::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2LogDomain::FCreateNamespaceTask>> FGs2LogDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Log::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2LogDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Log::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2LogDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            "log:Namespace",
            Callback
        );
    }

    void FGs2LogDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Log::Model::FNamespace::TypeName,
            "log:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Log::Domain::Model::FNamespaceDomain> FGs2LogDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Log::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2LogDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2LogDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2LogDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2LogDomain::HandleNotification(
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

