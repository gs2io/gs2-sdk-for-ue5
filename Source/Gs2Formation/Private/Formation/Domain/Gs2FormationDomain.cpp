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

#include "Formation/Domain/Gs2Formation.h"
#include "Formation/Domain/Model/Namespace.h"
#include "Formation/Domain/Model/FormModel.h"
#include "Formation/Domain/Model/FormModelMaster.h"
#include "Formation/Domain/Model/MoldModel.h"
#include "Formation/Domain/Model/MoldModelMaster.h"
#include "Formation/Domain/Model/PropertyFormModel.h"
#include "Formation/Domain/Model/PropertyFormModelMaster.h"
#include "Formation/Domain/Model/CurrentFormMaster.h"
#include "Formation/Domain/Model/Mold.h"
#include "Formation/Domain/Model/Form.h"
#include "Formation/Domain/Model/PropertyForm.h"
#include "Formation/Domain/Model/User.h"
#include "Formation/Domain/Model/UserAccessToken.h"

namespace Gs2::Formation::Domain
{

    FGs2FormationDomain::FGs2FormationDomain(
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
        Client(MakeShared<Gs2::Formation::FGs2FormationRestClient>(Session)),
        ParentKey("formation")
    {
    }

    FGs2FormationDomain::FGs2FormationDomain(
        const FGs2FormationDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2FormationDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2FormationDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("formation:Namespace");
                const auto Key = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Formation::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Formation::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCreateNamespaceTask>> FGs2FormationDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FDumpUserDataTask::FDumpUserDataTask(
        TSharedPtr<FGs2FormationDomain> Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FDumpUserDataTask>> FGs2FormationDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        TSharedPtr<FGs2FormationDomain> Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCheckDumpUserDataTask>> FGs2FormationDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCleanUserDataTask::FCleanUserDataTask(
        TSharedPtr<FGs2FormationDomain> Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCleanUserDataTask>> FGs2FormationDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2FormationDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        TSharedPtr<FGs2FormationDomain> Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2FormationDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2FormationDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2FormationDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2FormationDomain::FCheckCleanUserDataTask>> FGs2FormationDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Formation::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2FormationDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2FormationDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Formation::Model::FNamespace::TypeName,
            "formation:Namespace",
            Callback
        );
    }

    void FGs2FormationDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Formation::Model::FNamespace::TypeName,
            "formation:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Formation::Domain::Model::FNamespaceDomain> FGs2FormationDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Formation::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2FormationDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "AddMoldCapacityByUserId") {
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
            const auto RequestModel = Gs2::Formation::Request::FAddMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAddMoldCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "SetMoldCapacityByUserId") {
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
            const auto RequestModel = Gs2::Formation::Request::FSetMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSetMoldCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "AcquireActionsToFormProperties") {
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
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToFormPropertiesResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "AcquireActionsToPropertyFormProperties") {
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
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToPropertyFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToPropertyFormPropertiesResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "PropertyForm"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName(),
                    RequestModel->GetPropertyId()
                );
                Cache->Put(
                    Gs2::Formation::Model::FPropertyForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2FormationDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "SubMoldCapacityByUserId") {
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
            const auto RequestModel = Gs2::Formation::Request::FSubMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSubMoldCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2FormationDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "add_mold_capacity_by_user_id") {
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
            const auto RequestModel = Gs2::Formation::Request::FAddMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAddMoldCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "set_mold_capacity_by_user_id") {
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
            const auto RequestModel = Gs2::Formation::Request::FSetMoldCapacityByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FSetMoldCapacityByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMoldModel() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    "MoldModel"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldModelDomain::CreateCacheKey(
                    ResultModel->GetMoldModel()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMoldModel::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMoldModel(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "acquire_actions_to_form_properties") {
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
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToFormPropertiesResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    RequestModel->GetMoldModelName(),
                    "Form"
                );
                const auto Key = Gs2::Formation::Domain::Model::FFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetIndex().IsSet() ? FString::FromInt(*ResultModel->GetItem()->GetIndex()) : TOptional<FString>()
                );
                Cache->Put(
                    Gs2::Formation::Model::FForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetMold() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Mold"
                );
                const auto Key = Gs2::Formation::Domain::Model::FMoldDomain::CreateCacheKey(
                    ResultModel->GetMold()->GetName()
                );
                Cache->Put(
                    Gs2::Formation::Model::FMold::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetMold(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "acquire_actions_to_property_form_properties") {
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
            const auto RequestModel = Gs2::Formation::Request::FAcquireActionsToPropertyFormPropertiesRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Formation::Result::FAcquireActionsToPropertyFormPropertiesResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Formation::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "PropertyForm"
                );
                const auto Key = Gs2::Formation::Domain::Model::FPropertyFormDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName(),
                    RequestModel->GetPropertyId()
                );
                Cache->Put(
                    Gs2::Formation::Model::FPropertyForm::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2FormationDomain::HandleNotification(
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

