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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Grade/Domain/Gs2Grade.h"
#include "Grade/Domain/Model/Namespace.h"
#include "Grade/Domain/Model/GradeModelMaster.h"
#include "Grade/Domain/Model/GradeModel.h"
#include "Grade/Domain/Model/User.h"
#include "Grade/Domain/Model/UserAccessToken.h"
#include "Grade/Domain/Model/Status.h"
#include "Grade/Domain/Model/CurrentGradeMaster.h"
#include "Core/Domain/Gs2.h"
#include "Experience/Domain/Model/Status.h"

namespace Gs2::Grade::Domain
{

    FGs2GradeDomain::FGs2GradeDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(MakeShared<Gs2::Grade::FGs2GradeRestClient>(Gs2->RestSession)),
        ParentKey("grade")
    {
    }

    FGs2GradeDomain::FGs2GradeDomain(
        const FGs2GradeDomain& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2GradeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Grade::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("grade:Namespace");
                const auto Key = Gs2::Grade::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::Grade::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Grade::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FCreateNamespaceTask>> FGs2GradeDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FDumpUserDataTask>> FGs2GradeDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FCheckDumpUserDataTask>> FGs2GradeDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FCleanUserDataTask>> FGs2GradeDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FCheckCleanUserDataTask>> FGs2GradeDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FPrepareImportUserDataTask>> FGs2GradeDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FImportUserDataTask>> FGs2GradeDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2GradeDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2GradeDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2GradeDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2GradeDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2GradeDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2GradeDomain::FCheckImportUserDataTask>> FGs2GradeDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Grade::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2GradeDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Grade::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2GradeDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::Grade::Model::FNamespace::TypeName,
            "grade:Namespace",
            Callback
        );
    }

    void FGs2GradeDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::Grade::Model::FNamespace::TypeName,
            "grade:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Grade::Domain::Model::FNamespaceDomain> FGs2GradeDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::Grade::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2GradeDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "AddGradeByUserId") {
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
            const auto RequestModel = Gs2::Grade::Request::FAddGradeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FAddGradeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "ApplyRankCapByUserId") {
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
            const auto RequestModel = Gs2::Grade::Request::FApplyRankCapByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FApplyRankCapByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "MultiplyAcquireActionsByUserId") {
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
            const auto RequestModel = Gs2::Grade::Request::FMultiplyAcquireActionsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FMultiplyAcquireActionsByUserIdResult::FromJson(ResultModelJson);
            
        }
    }

    void FGs2GradeDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "SubGradeByUserId") {
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
            const auto RequestModel = Gs2::Grade::Request::FSubGradeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FSubGradeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2GradeDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "add_grade_by_user_id") {
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
            const auto RequestModel = Gs2::Grade::Request::FAddGradeByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FAddGradeByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "apply_rank_cap_by_user_id") {
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
            const auto RequestModel = Gs2::Grade::Request::FApplyRankCapByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FApplyRankCapByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Grade::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetGradeName(),
                    ResultModel->GetItem()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Grade::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (ResultModel->GetExperienceStatus() != nullptr)
            {
                const auto ParentKey = Gs2::Grade::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Status"
                );
                const auto Key = Gs2::Experience::Domain::Model::FStatusDomain::CreateCacheKey(
                    ResultModel->GetExperienceStatus()->GetExperienceName(),
                    ResultModel->GetExperienceStatus()->GetPropertyId()
                );
                Gs2->Cache->Put(
                    Gs2::Experience::Model::FStatus::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetExperienceStatus(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        if (Method == "multiply_acquire_actions_by_user_id") {
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
            const auto RequestModel = Gs2::Grade::Request::FMultiplyAcquireActionsByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Grade::Result::FMultiplyAcquireActionsByUserIdResult::FromJson(ResultModelJson);
            
        }
    }

    void FGs2GradeDomain::HandleNotification(
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

