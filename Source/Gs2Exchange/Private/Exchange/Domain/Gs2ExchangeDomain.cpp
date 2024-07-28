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
#include "Exchange/Domain/Model/IncrementalRateModel.h"
#include "Exchange/Domain/Model/IncrementalRateModelMaster.h"
#include "Exchange/Domain/Model/Exchange.h"
#include "Exchange/Domain/Model/CurrentRateMaster.h"
#include "Exchange/Domain/Model/Await.h"
#include "Exchange/Domain/Model/User.h"
#include "Exchange/Domain/Model/UserAccessToken.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::Exchange::Domain
{

    FGs2ExchangeDomain::FGs2ExchangeDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Exchange::FGs2ExchangeRestClient>(Gs2->RestSession)),
        ParentKey("exchange")
    {
    }

    FGs2ExchangeDomain::FGs2ExchangeDomain(
        const FGs2ExchangeDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2ExchangeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
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
                Self->Gs2->Cache->Put(
                    Gs2::Exchange::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Exchange::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
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

    FGs2ExchangeDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FDumpUserDataTask>> FGs2ExchangeDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2ExchangeDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
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
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FCheckDumpUserDataTask>> FGs2ExchangeDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2ExchangeDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FCleanUserDataTask>> FGs2ExchangeDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2ExchangeDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FCheckCleanUserDataTask>> FGs2ExchangeDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2ExchangeDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
    )
    {
        const auto Future = Self->Client->PrepareImportUserDataByUserId(
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
            if (ResultModel->GetUploadUrl().IsSet())
            {
                Self->UploadUrl = Domain->UploadUrl = ResultModel->GetUploadUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FPrepareImportUserDataTask>> FGs2ExchangeDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2ExchangeDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
    )
    {
        const auto Future = Self->Client->ImportUserDataByUserId(
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

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FImportUserDataTask>> FGs2ExchangeDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2ExchangeDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2ExchangeDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2ExchangeDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2ExchangeDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2ExchangeDomain>> Result
    )
    {
        const auto Future = Self->Client->CheckImportUserDataByUserId(
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
            if (ResultModel->GetUrl().IsSet())
            {
                Self->Url = Domain->Url = ResultModel->GetUrl();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2ExchangeDomain::FCheckImportUserDataTask>> FGs2ExchangeDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Exchange::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2ExchangeDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Exchange::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2ExchangeDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Exchange::Model::FNamespace::TypeName,
            "exchange:Namespace",
            Callback
        );
    }

    void FGs2ExchangeDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Exchange::Model::FNamespace::TypeName,
            "exchange:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Exchange::Domain::Model::FNamespaceDomain> FGs2ExchangeDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Exchange::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
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
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FRateModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "IncrementalExchangeByUserId") {
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
            const auto RequestModel = Gs2::Exchange::Request::FIncrementalExchangeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FIncrementalExchangeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "IncrementalRateModel"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FIncrementalRateModel::TypeName,
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
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "SkipByUserId") {
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
            const auto RequestModel = Gs2::Exchange::Request::FSkipByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FSkipByUserIdResult::FromJson(ResultModelJson);
            
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
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
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
                Gs2->Cache->Delete(Gs2::Exchange::Model::FAwait::TypeName, ParentKey, Key);
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
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FRateModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "incremental_exchange_by_user_id") {
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
            const auto RequestModel = Gs2::Exchange::Request::FIncrementalExchangeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FIncrementalExchangeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Exchange::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "IncrementalRateModel"
                );
                const auto Key = Gs2::Exchange::Domain::Model::FIncrementalRateModelDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FIncrementalRateModel::TypeName,
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
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "skip_by_user_id") {
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
            const auto RequestModel = Gs2::Exchange::Request::FSkipByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Exchange::Result::FSkipByUserIdResult::FromJson(ResultModelJson);
            
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
                Gs2->Cache->Put(
                    Gs2::Exchange::Model::FAwait::TypeName,
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

