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

namespace Gs2::JobQueue::Domain
{

    FGs2JobQueueDomain::FGs2JobQueueDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
        // ReSharper disable once CppMemberInitializersOrder
    ):
        CopiedCompletedJobs(MakeShared<TArray<Gs2::JobQueue::Model::FRunNotificationPtr>>()),
        CopiedCompletedJobsMutex(MakeShared<FCriticalSection>()),
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Session)),
        ParentKey("jobQueue")
    {
        OnPushNotification().AddLambda([&](
            Gs2::JobQueue::Model::FPushNotificationPtr Notification
        )
        {
            if (Notification->GetNamespaceName().IsSet())
            {
                this->JobQueueDomain->Push(Notification->GetNamespaceName().GetValue());
            }
        });
    }

    FGs2JobQueueDomain::FGs2JobQueueDomain(
        const FGs2JobQueueDomain& From
    ):
        CopiedCompletedJobs(From.CopiedCompletedJobs),
        CopiedCompletedJobsMutex(From.CopiedCompletedJobsMutex),
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client)
    {

    }

    FGs2JobQueueDomain::FCreateNamespaceTask::FCreateNamespaceTask(
        TSharedPtr<FGs2JobQueueDomain> Self,
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
                Self->Cache->Put<Gs2::JobQueue::Model::FNamespace>(
                    ParentKey,
                    Key,
                    ResultModel->GetItem(),
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
        }
        auto Domain = MakeShared<Gs2::JobQueue::Domain::Model::FNamespaceDomain>(
            Self->Cache,
            Self->JobQueueDomain,
            Self->StampSheetConfiguration,
            Self->Session,
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

    Gs2::JobQueue::Domain::Iterator::FDescribeNamespacesIteratorPtr FGs2JobQueueDomain::Namespaces(
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Iterator::FDescribeNamespacesIterator>(
            Cache,
            Client
        );
    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FNamespaceDomain> FGs2JobQueueDomain::Namespace(
        const FString NamespaceName
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FNamespaceDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName
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
                    Cache->Put<Gs2::JobQueue::Model::FJob>(
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
                    Cache->Put<Gs2::JobQueue::Model::FJob>(
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
                    Self->Session
                );
                for (auto CompletedJob : CopiedCopiedCompletedJobsTemp)
                {
                    const auto Future = Client->GetJobResult(
                        MakeShared<Gs2::JobQueue::Request::FGetJobResultRequest>()
                            ->WithNamespaceName(CompletedJob->GetNamespaceName())
                            ->WithJobName(CompletedJob->GetJobName())
                            ->WithAccessToken(AccessToken->GetToken())
                    );
                    Future->StartSynchronousTask();
                    if (Future->GetTask().IsError())
                    {
                        return Future->GetTask().Error();
                    }
                    const auto Result = Future->GetTask().Result();
                    if (Result != nullptr)
                    {
                        Self->JobQueueDomain->OnExecutedEvent().Broadcast(
                            MakeShared<Gs2::JobQueue::Model::FJob>()
                                ->WithScriptId(Result->GetItem()->GetScriptId())
                                ->WithArgs(Result->GetItem()->GetArgs()),
                            MakeShared<Gs2::JobQueue::Model::FJobResultBody>()
                                ->WithTryNumber(Result->GetItem()->GetTryNumber())
                                ->WithStatusCode(Result->GetItem()->GetStatusCode())
                                ->WithResult(Result->GetItem()->GetResult())
                                ->WithTryAt(Result->GetItem()->GetTryAt())
                        );
                    }
                    Future->EnsureCompletion();
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
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

