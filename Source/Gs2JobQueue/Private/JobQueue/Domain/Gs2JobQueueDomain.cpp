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

#include "JobQueue/Domain/Gs2JobQueue.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"
#include "Core/Domain/Transaction/AutoJobQueueAccessTokenDomain.h"
#include "Core/Domain/Transaction/AutoJobQueueDomain.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::JobQueue::Domain
{

    FGs2JobQueueDomain::FGs2JobQueueDomain(
        const Core::Domain::FGs2Ptr& Gs2
        // ReSharper disable once CppMemberInitializersOrder
    ):
        CopiedCompletedJobs(MakeShared<TArray<Gs2::JobQueue::Model::FRunNotificationPtr>>()),
        CopiedCompletedJobsMutex(MakeShared<FCriticalSection>()),
        Gs2(Gs2),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
        ParentKey("jobQueue")
    {
        OnPushNotification().AddLambda([&](
            Gs2::JobQueue::Model::FPushNotificationPtr Notification
        )
        {
            if (Notification->GetNamespaceName().IsSet())
            {
                this->Gs2->JobQueueDomain->Push(Notification->GetNamespaceName().GetValue());
            }
        });
    }

    FGs2JobQueueDomain::FGs2JobQueueDomain(
        const FGs2JobQueueDomain& From
    ):
        CopiedCompletedJobs(From.CopiedCompletedJobs),
        CopiedCompletedJobsMutex(From.CopiedCompletedJobsMutex),
        Gs2(From.Gs2),
        Client(From.Client),
        ParentKey(From.ParentKey)
    {

    }

    FGs2JobQueueDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FCreateNamespaceRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        const FCreateNamespaceTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FCreateNamespaceTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FNamespaceDomain>> Result
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
                const auto ParentKey = FString("jobQueue:Namespace");
                const auto Key = Gs2::JobQueue::Domain::Model::FNamespaceDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Gs2->Cache->Put(
                    Gs2::JobQueue::Model::FNamespace::TypeName,
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::JobQueue::Domain::Model::FNamespaceDomain>(
            Self->Gs2,
            Self,
            ResultModel->GetItem()->GetName()
        );
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FCreateNamespaceTask>> FGs2JobQueueDomain::CreateNamespace(
        Request::FCreateNamespaceRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCreateNamespaceTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FDumpUserDataTask::FDumpUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FDumpUserDataTask::FDumpUserDataTask(
        const FDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FDumpUserDataTask>> FGs2JobQueueDomain::DumpUserData(
        Request::FDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FCheckDumpUserDataTask::FCheckDumpUserDataTask(
        const FCheckDumpUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FCheckDumpUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FCheckDumpUserDataTask>> FGs2JobQueueDomain::CheckDumpUserData(
        Request::FCheckDumpUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckDumpUserDataTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FCleanUserDataTask::FCleanUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FCleanUserDataTask::FCleanUserDataTask(
        const FCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FCleanUserDataTask>> FGs2JobQueueDomain::CleanUserData(
        Request::FCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FCheckCleanUserDataTask::FCheckCleanUserDataTask(
        const FCheckCleanUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FCheckCleanUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FCheckCleanUserDataTask>> FGs2JobQueueDomain::CheckCleanUserData(
        Request::FCheckCleanUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckCleanUserDataTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FPrepareImportUserDataTask::FPrepareImportUserDataTask(
        const FPrepareImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FPrepareImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FPrepareImportUserDataTask>> FGs2JobQueueDomain::PrepareImportUserData(
        Request::FPrepareImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPrepareImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FImportUserDataTask::FImportUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FImportUserDataTask::FImportUserDataTask(
        const FImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FImportUserDataTask>> FGs2JobQueueDomain::ImportUserData(
        Request::FImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FImportUserDataTask>>(this->AsShared(), Request);
    }

    FGs2JobQueueDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const TSharedPtr<FGs2JobQueueDomain>& Self,
        const Request::FCheckImportUserDataByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FGs2JobQueueDomain::FCheckImportUserDataTask::FCheckImportUserDataTask(
        const FCheckImportUserDataTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FCheckImportUserDataTask::Action(
        TSharedPtr<TSharedPtr<FGs2JobQueueDomain>> Result
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

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FCheckImportUserDataTask>> FGs2JobQueueDomain::CheckImportUserData(
        Request::FCheckImportUserDataByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCheckImportUserDataTask>>(this->AsShared(), Request);
    }

    Gs2::JobQueue::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2JobQueueDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Iterator::FDescribeNamespacesIterator>(
            Gs2->Cache,
            Client
        );
    }

    Gs2::Core::Domain::CallbackID FGs2JobQueueDomain::SubscribeNamespaces(
    TFunction<void()> Callback
    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::JobQueue::Model::FNamespace::TypeName,
            "jobQueue:Namespace",
            Callback
        );
    }

    void FGs2JobQueueDomain::UnsubscribeNamespaces(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::JobQueue::Model::FNamespace::TypeName,
            "jobQueue:Namespace",
            CallbackID
        );
    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FNamespaceDomain> FGs2JobQueueDomain::Namespace(
        const FString NamespaceName
    )
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FNamespaceDomain>(
            Gs2,
            AsShared(),
            NamespaceName == TEXT("") ? TOptional<FString>() : TOptional<FString>(NamespaceName)
        );
    }

    void FGs2JobQueueDomain::UpdateCacheFromStampSheet(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "PushByUserId") {
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
            const auto RequestModel = Gs2::JobQueue::Request::FPushByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Job"
                    );
                    const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Gs2->Cache->Put(
                        Gs2::JobQueue::Model::FJob::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
            const auto Notification = MakeShared<Gs2::JobQueue::Model::FPushNotification>()
                    ->WithNamespaceName(RequestModelJson->GetStringField("namespaceName"));
            PushNotificationEvent.Broadcast(Notification);
        }
    }

    void FGs2JobQueueDomain::UpdateCacheFromStampTask(
        const FString Method,
        const FString Request,
        const FString Result
    ) {
        if (Method == "DeleteJobByUserId") {
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
            const auto RequestModel = Gs2::JobQueue::Request::FDeleteJobByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::JobQueue::Result::FDeleteJobByUserIdResult::FromJson(ResultModelJson);
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                    RequestModel->GetNamespaceName(),
                    RequestModel->GetUserId(),
                    "Job"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Gs2->Cache->Delete(Gs2::JobQueue::Model::FJob::TypeName, ParentKey, Key);
            }
        }
    }

    void FGs2JobQueueDomain::UpdateCacheFromJobResult(
        const FString Method,
        const Gs2::JobQueue::Model::FJobPtr Job,
        const Gs2::JobQueue::Model::FJobResultBodyPtr Result
    ) {
        if (Method == "push_by_user_id") {
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
            const auto RequestModel = Gs2::JobQueue::Request::FPushByUserIdRequest::FromJson(RequestModelJson);
            const auto ResultModel = Gs2::JobQueue::Result::FPushByUserIdResult::FromJson(ResultModelJson);
            {
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                        RequestModel->GetNamespaceName(),
                        RequestModel->GetUserId(),
                        "Job"
                    );
                    const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Gs2->Cache->Put(
                        Gs2::JobQueue::Model::FJob::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
            const auto Notification = MakeShared<Gs2::JobQueue::Model::FPushNotification>()
                    ->WithNamespaceName(RequestModelJson->GetStringField("namespaceName"));
            PushNotificationEvent.Broadcast(Notification);
        }
    }

    void FGs2JobQueueDomain::HandleNotification(
        const FString Action,
        const FString Payload
    ) {
        if (Action == "Push") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            PushNotificationEvent.Broadcast(Gs2::JobQueue::Model::FPushNotification::FromJson(PayloadJson));
        }
        if (Action == "RunNotification") {
            TSharedPtr<FJsonObject> PayloadJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Payload);
                !FJsonSerializer::Deserialize(JsonReader, PayloadJson))
            {
                return;
            }
            CopiedCompletedJobsMutex->Lock();
            {
                const auto Notification = Gs2::JobQueue::Model::FRunNotification::FromJson(PayloadJson);
                CopiedCompletedJobs->Add(Notification);
                RunNotificationEvent.Broadcast(Notification);
            }
            CopiedCompletedJobsMutex->Unlock();
        }
    }

    FPushNotificationEvent& FGs2JobQueueDomain::OnPushNotification()
    {
        return PushNotificationEvent;
    }

    FRunNotificationEvent& FGs2JobQueueDomain::OnRunNotification()
    {
        return RunNotificationEvent;
    }

    FGs2JobQueueDomain::FDispatchTask::FDispatchTask(
        const TSharedPtr<FGs2JobQueueDomain> Self,
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    ): Self(Self), AccessToken(AccessToken)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FDispatchTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        if (Self->CopiedCompletedJobsMutex->TryLock())
        {
            TArray CopiedCopiedCompletedJobsTemp(*Self->CopiedCompletedJobs);
            {
                if (Self->CopiedCompletedJobs->Num() == 0)
                {
                    return nullptr;
                }

                const auto Client = MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(
                    Self->Gs2->RestSession
                );
                for (auto CompletedJob : CopiedCopiedCompletedJobsTemp)
                {
                    if (!CompletedJob.IsValid()) continue;
                    {
                        auto Future = Self->Namespace(
                            *CompletedJob->GetNamespaceName()
                        )->AccessToken(
                            AccessToken
                        )->Job(
                            *CompletedJob->GetJobName()
                        )->JobResult()->ModelNoCache();
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                            {
                            }
                            else
                            {
                                return Future->GetTask().Error();
                            }
                        }
                        Future->EnsureCompletion();
                    }
                    {
                        const auto AutoRun = Gs2::Core::Domain::FJobQueueJobDomainFactory::ToTransaction(
                            Self->Gs2,
                            [](
                                bool bAutoRun,
                                FString TransactionId,
                                FString StampSheet,
                                FString StampSheetEncryptionKeyId
                            ) -> TSharedPtr<Gs2::Core::Domain::FTransactionAccessTokenDomain>
                            {
                                return nullptr;
                            },
                            AccessToken,
                            true,
                            *CompletedJob->GetNamespaceName(),
                            *CompletedJob->GetJobName()
                        );
                        const auto Future = AutoRun->Wait();
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                            {
                            }
                            else
                            {
                                return Future->GetTask().Error();
                            }
                        }
                        Future->EnsureCompletion();
                    }
                }

                Self->CopiedCompletedJobs->Reset();
            }
            Self->CopiedCompletedJobsMutex->Unlock();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FDispatchTask>> FGs2JobQueueDomain::Dispatch(
        const Gs2::Auth::Model::FAccessTokenPtr AccessToken
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGs2JobQueueDomain::FDispatchTask>>(this->AsShared(), AccessToken);
    }

    FGs2JobQueueDomain::FDispatchByUserIdTask::FDispatchByUserIdTask(
        const TSharedPtr<FGs2JobQueueDomain> Self,
        const FString UserId
    ):
        Self(Self),
        UserId(UserId)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FGs2JobQueueDomain::FDispatchByUserIdTask::Action(
        TSharedPtr<TSharedPtr<void*>> Result
    )
    {
        if (Self->CopiedCompletedJobsMutex->TryLock())
        {
            TArray CopiedCopiedCompletedJobsTemp(*Self->CopiedCompletedJobs);
            {
                if (Self->CopiedCompletedJobs->Num() == 0)
                {
                    return nullptr;
                }

                const auto Client = MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(
                    Self->Gs2->RestSession
                );
                for (auto CompletedJob : CopiedCopiedCompletedJobsTemp)
                {
                    if (!CompletedJob.IsValid()) continue;
                    {
                        auto Future = Self->Namespace(
                            *CompletedJob->GetNamespaceName()
                        )->User(
                            UserId
                        )->Job(
                            *CompletedJob->GetJobName()
                        )->JobResult()->ModelNoCache();
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                            {
                            }
                            else
                            {
                                return Future->GetTask().Error();
                            }
                        }
                        Future->EnsureCompletion();
                    }
                    {
                        const auto AutoRun = Gs2::Core::Domain::FJobQueueJobDomainFactory::ToTransaction(
                            Self->Gs2,
                            [](
                                bool bAutoRun,
                                FString TransactionId,
                                FString StampSheet,
                                FString StampSheetEncryptionKeyId
                            ) -> TSharedPtr<Gs2::Core::Domain::FTransactionDomain>
                            {
                                return nullptr;
                            },
                            UserId,
                            true,
                            *CompletedJob->GetNamespaceName(),
                            *CompletedJob->GetJobName()
                        );
                        const auto Future = AutoRun->Wait();
                        Future->StartSynchronousTask();
                        if (Future->GetTask().IsError())
                        {
                            if (Future->GetTask().Error()->Type() == Gs2::Core::Model::FNotFoundError::TypeString)
                            {
                            }
                            else
                            {
                                return Future->GetTask().Error();
                            }
                        }
                        Future->EnsureCompletion();
                    }
                }

                Self->CopiedCompletedJobs->Reset();
            }
            Self->CopiedCompletedJobsMutex->Unlock();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FGs2JobQueueDomain::FDispatchByUserIdTask>> FGs2JobQueueDomain::DispatchByUserId(
        const FString UserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGs2JobQueueDomain::FDispatchByUserIdTask>>(this->AsShared(), UserId);
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

