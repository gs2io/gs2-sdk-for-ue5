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

#include "Quest/Domain/Gs2Quest.h"
#include "Quest/Domain/Model/Namespace.h"
#include "Quest/Domain/Model/QuestGroupModelMaster.h"
#include "Quest/Domain/Model/QuestModelMaster.h"
#include "Quest/Domain/Model/CurrentQuestMaster.h"
#include "Quest/Domain/Model/Progress.h"
#include "Quest/Domain/Model/CompletedQuestList.h"
#include "Quest/Domain/Model/QuestGroupModel.h"
#include "Quest/Domain/Model/QuestModel.h"
#include "Quest/Domain/Model/User.h"
#include "Quest/Domain/Model/UserAccessToken.h"

namespace Gs2::Quest::Domain
{

    FGs2QuestDomain::FGs2QuestDomain(
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
        Client(MakeShared<Gs2::Quest::FGs2QuestRestClient>(Session)),
        ParentKey("quest")
    {
    }

    FGs2QuestDomain::FGs2QuestDomain(
        const FGs2QuestDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2QuestDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2QuestDomain> Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2QuestDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2QuestDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Quest::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("quest:Namespace");
                const auto Key = Gs2::Quest::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Put(
                    Gs2::Quest::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::Quest::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2QuestDomain::FCreateNamespaceTask>> FGs2QuestDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2QuestDomain::FDumpUserDataTask::FDumpUserDataTask(
        TSharedPtr<FGs2QuestDomain> Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2QuestDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2QuestDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2QuestDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2QuestDomain::FDumpUserDataTask>> FGs2QuestDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2QuestDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        TSharedPtr<FGs2QuestDomain> Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2QuestDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2QuestDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2QuestDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2QuestDomain::FCheckDumpUserDataTask>> FGs2QuestDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2QuestDomain::FCleanUserDataTask::FCleanUserDataTask(
        TSharedPtr<FGs2QuestDomain> Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2QuestDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2QuestDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2QuestDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2QuestDomain::FCleanUserDataTask>> FGs2QuestDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2QuestDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        TSharedPtr<FGs2QuestDomain> Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2QuestDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2QuestDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2QuestDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2QuestDomain::FCheckCleanUserDataTask>> FGs2QuestDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::Quest::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2QuestDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2QuestDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::Quest::Model::FNamespace::TypeName,
            "quest:Namespace",
            Callback
        );
    }

    void FGs2QuestDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::Quest::Model::FNamespace::TypeName,
            "quest:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::Quest::Domain::Model::FNamespaceDomain> FGs2QuestDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::Quest::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2QuestDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "CreateProgressByUserId") {
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
            const auto RequestModel = Gs2::Quest::Request::FCreateProgressByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Quest::Result::FCreateProgressByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::Quest::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2QuestDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DeleteProgressByUserId") {
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
            const auto RequestModel = Gs2::Quest::Request::FDeleteProgressByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Quest::Result::FDeleteProgressByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Cache->Delete(Gs2::Quest::Model::FProgress::TypeName, ParentKey, Key);
            }
        }
    }

    void FGs2QuestDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "create_progress_by_user_id") {
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
            const auto RequestModel = Gs2::Quest::Request::FCreateProgressByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::Quest::Result::FCreateProgressByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::Quest::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Progress"
                );
                const auto Key = Gs2::Quest::Domain::Model::FProgressDomain::CreateCacheKey(
                );
                Cache->Put(
                    Gs2::Quest::Model::FProgress::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
    }

    void FGs2QuestDomain::HandleNotification(
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

