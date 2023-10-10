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

#include "Version/Domain/Gs2Version.h"
#include "Version/Domain/Model/Namespace.h"
#include "Version/Domain/Model/VersionModelMaster.h"
#include "Version/Domain/Model/VersionModel.h"
#include "Version/Domain/Model/AcceptVersion.h"
#include "Version/Domain/Model/Checker.h"
#include "Version/Domain/Model/User.h"
#include "Version/Domain/Model/UserAccessToken.h"
#include "Version/Domain/Model/CurrentVersionMaster.h"

namespace Gs2::Version::Domain
{

    FGs2VersionDomain::FGs2VersionDomain(
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
        Client(MakeShared<Gs2::Version::FGs2VersionRestClient>(Session)),
        ParentKey("version")
    {
    }

    FGs2VersionDomain::FGs2VersionDomain(
        const FGs2VersionDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2VersionDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2VersionDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2VersionDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2VersionDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Version::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("version:Namespace");
                const auto Key = Gs2::Version::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Version::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Version::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2VersionDomain::FCreateNamespaceTask>> FGs2VersionDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2VersionDomain::FDumpUserDataTask::FDumpUserDataTask(
        TSharedPtr<FGs2VersionDomain> Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2VersionDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2VersionDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2VersionDomain>> Result
    )
    {
        const auto Future = Self->Client->DumpUserDataByUserId(
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

    TSharedPtr<FAsyncTask<FGs2VersionDomain::FDumpUserDataTask>> FGs2VersionDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2VersionDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        TSharedPtr<FGs2VersionDomain> Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2VersionDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2VersionDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2VersionDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckDumpUserDataByUserId(
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
        Domain->Url = Domain->Url = ResultModel->GetUrl();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2VersionDomain::FCheckDumpUserDataTask>> FGs2VersionDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2VersionDomain::FCleanUserDataTask::FCleanUserDataTask(
        TSharedPtr<FGs2VersionDomain> Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2VersionDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2VersionDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2VersionDomain>> Result
    )
    {
        const auto Future = Self->Client->CleanUserDataByUserId(
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

    TSharedPtr<FAsyncTask<FGs2VersionDomain::FCleanUserDataTask>> FGs2VersionDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2VersionDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        TSharedPtr<FGs2VersionDomain> Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2VersionDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2VersionDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2VersionDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckCleanUserDataByUserId(
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

    TSharedPtr<FAsyncTask<FGs2VersionDomain::FCheckCleanUserDataTask>> FGs2VersionDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Version::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2VersionDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Version::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2VersionDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Version::Model::FNamespace::TypeName,
            "version:Namespace",
            Callback
        );
    }

    void FGs2VersionDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Version::Model::FNamespace::TypeName,
            "version:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Version::Domain::Model::FNamespaceDomain> FGs2VersionDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Version::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2VersionDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2VersionDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
    }

    void FGs2VersionDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
    }

    void FGs2VersionDomain::HandleNotification(
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

