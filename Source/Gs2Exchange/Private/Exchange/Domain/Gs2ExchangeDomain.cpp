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

#include "Exchange/Domain/Gs2Exchange.h"
#include "Exchange/Domain/Model/Namespace.h"
#include "Exchange/Domain/Model/RateModel.h"
#include "Exchange/Domain/Model/RateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"

namespace Gs2::Exchange::Domain
{

    FGs2ExchangeDomain::FGs2ExchangeDomain(
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
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Session)),
        ParentKey("exchange")
    {
    }

    FGs2ExchangeDomain::FGs2ExchangeDomain(
        const FGs2ExchangeDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGs2ExchangeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2ExchangeDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Exchange::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("exchange:Namespace");
                const auto Key = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put<Gs2::Exchange::Model::FNamespace>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Exchange::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FCreateNamespaceTask>> FGs2ExchangeDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Exchange::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2ExchangeDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FNamespaceDomain> FGs2ExchangeDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
        );
    }

    void FGs2ExchangeDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "ExchangeByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Exchange::Request::FExchangeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FExchangeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "RateModel"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put<Gs2::Exchange::Model::FRateModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "CreateAwaitByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Exchange::Request::FCreateAwaitByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FCreateAwaitByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put<Gs2::Exchange::Model::FAwait>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2ExchangeDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DeleteAwaitByUserId") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Request);
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Result);
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Exchange::Request::FDeleteAwaitByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FDeleteAwaitByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Delete<Gs2::Exchange::Model::FAwait>(ParentKey, Key);
            }
        }
    }

    void FGs2ExchangeDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "exchange_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Exchange::Request::FExchangeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FExchangeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "RateModel"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put<Gs2::Exchange::Model::FRateModel>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "create_await_by_user_id") {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (!Job->GetArgs().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Job->GetArgs());
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return;
            }
            TSharedPtr<FJsonObject> ResultModelJson;
            if (!Result->GetResult().IsSet())
            {
                return;
            }
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(*Result->GetResult());
                !FJsonSerializer::Deserialize(JsonReader, ResultModelJson))
            {
                return;
            }
            const auto RequestModel = Gs2::Exchange::Request::FCreateAwaitByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FCreateAwaitByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Await"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FAwaitDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put<Gs2::Exchange::Model::FAwait>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2ExchangeDomain::HandleNotification(
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

