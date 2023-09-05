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

#include "Stamina/Domain/Gs2Stamina.h"
#include "Stamina/Domain/Model/Namespace.h"
#include "Stamina/Domain/Model/StaminaModelMaster.h"
#include "Stamina/Domain/Model/MaxStaminaTableMaster.h"
#include "Stamina/Domain/Model/RecoverIntervalTableMaster.h"
#include "Stamina/Domain/Model/RecoverValueTableMaster.h"
#include "Stamina/Domain/Model/CurrentStaminaMaster.h"
#include "Stamina/Domain/Model/StaminaModel.h"
#include "Stamina/Domain/Model/Stamina.h"
#include "Stamina/Domain/Model/User.h"
#include "Stamina/Domain/Model/UserAccessToken.h"

namespace Gs2::Stamina::Domain
{

    FGs2StaminaDomain::FGs2StaminaDomain(
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
        Client(MakeShared<Gs2::Stamina::FGs2StaminaRestClient>(Session)),
        ParentKey("stamina")
    {
    }

    FGs2StaminaDomain::FGs2StaminaDomain(
        const FGs2StaminaDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGs2StaminaDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2StaminaDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2StaminaDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2StaminaDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("stamina:Namespace");
                const auto Key = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Stamina::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Stamina::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2StaminaDomain::FCreateNamespaceTask>> FGs2StaminaDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    Gs2::Stamina::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2StaminaDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::Stamina::Domain::Model::FNamespaceDomain> FGs2StaminaDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Stamina::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2StaminaDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "RecoverStaminaByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FRecoverStaminaByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FRecoverStaminaByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "RaiseMaxValueByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FRaiseMaxValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "SetMaxValueByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FSetMaxValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FSetMaxValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "SetRecoverIntervalByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FSetRecoverIntervalByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FSetRecoverIntervalByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "SetRecoverValueByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FSetRecoverValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FSetRecoverValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2StaminaDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DecreaseMaxValueByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FDecreaseMaxValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FDecreaseMaxValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "ConsumeStaminaByUserId") {
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
            const auto RequestModel = Gs2::Stamina::Request::FConsumeStaminaByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FConsumeStaminaByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2StaminaDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "recover_stamina_by_user_id") {
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
            const auto RequestModel = Gs2::Stamina::Request::FRecoverStaminaByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FRecoverStaminaByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "raise_max_value_by_user_id") {
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
            const auto RequestModel = Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FRaiseMaxValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "set_max_value_by_user_id") {
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
            const auto RequestModel = Gs2::Stamina::Request::FSetMaxValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FSetMaxValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "set_recover_interval_by_user_id") {
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
            const auto RequestModel = Gs2::Stamina::Request::FSetRecoverIntervalByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FSetRecoverIntervalByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "set_recover_value_by_user_id") {
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
            const auto RequestModel = Gs2::Stamina::Request::FSetRecoverValueByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Stamina::Result::FSetRecoverValueByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Stamina"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetStaminaName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStamina::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetStaminaModel() != nullptr)
            {
                const auto ParentKey = Gs2::Stamina::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "StaminaModel"
                );
                const auto Key = Gs2::Stamina::Domain::Model::FStaminaModelDomain::CreateCacheKey(
                    ResultModel->GetStaminaModel()->GetName()
                );
                Cache->Put(
                    Gs2::Stamina::Model::FStaminaModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetStaminaModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2StaminaDomain::HandleNotification(
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

