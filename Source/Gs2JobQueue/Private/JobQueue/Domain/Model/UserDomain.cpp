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

#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/DeadLetterJob.h"
#include "JobQueue/Domain/Model/DeadLetterJobAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"

#include "Core/Domain/Model/AutoStampSheetDomain.h"
#include "Core/Domain/Model/StampSheetDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FCacheDatabasePtr Cache,
        const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
        const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
        const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Cache(Cache),
        JobQueueDomain(JobQueueDomain),
        StampSheetConfiguration(StampSheetConfiguration),
        Session(Session),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Session)),
        NamespaceName(NamespaceName),
        UserId(UserId),
        ParentKey(Gs2::JobQueue::Domain::Model::FNamespaceDomain::CreateCacheParentKey(
            NamespaceName,
            "User"
        ))
    {
    }

    FUserDomain::FUserDomain(
        const FUserDomain& From
    ):
        Cache(From.Cache),
        JobQueueDomain(From.JobQueueDomain),
        StampSheetConfiguration(From.StampSheetConfiguration),
        Session(From.Session),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FPushTask::FPushTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FPushByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FPushTask::FPushTask(
        const FPushTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FPushTask::Action(
        TSharedPtr<TSharedPtr<TArray<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>>>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->PushByUserId(
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
                for (auto Item : *ResultModel->GetItems())
                {
                    const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                        Self->NamespaceName,
                        Self->UserId,
                        "Job"
                    );
                    const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                        Item->GetName()
                    );
                    Self->Cache->Put(
                        Gs2::JobQueue::Model::FJob::TypeName,
                        ParentKey,
                        Key,
                        Item,
                        FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                    );
                }
            }
        }
        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>>>();
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::JobQueue::Domain::Model::FJobDomain>(
                    Self->Cache,
                    Self->JobQueueDomain,
                    Self->StampSheetConfiguration,
                    Self->Session,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
            const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                Self->NamespaceName,
                Self->UserId,
                "Job"
            );
            const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                (*ResultModel->GetItems())[i]->GetName()
            );
            Self->Cache->Put(
                Gs2::JobQueue::Model::FJob::TypeName,
                ParentKey,
                Key,
                (*ResultModel->GetItems())[i],
                FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
            );
        }
        if (ResultModel->GetAutoRun().IsSet() && *ResultModel->GetAutoRun())
        {
            Self->JobQueueDomain->Push(
                *Self->NamespaceName
            );
        }
        Self->AutoRun = ResultModel->GetAutoRun();
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPushTask>> FUserDomain::Push(
        Request::FPushByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPushTask>>(this->AsShared(), Request);
    }

    FUserDomain::FRunTask::FRunTask(
        const TSharedPtr<FUserDomain> Self,
        const Request::FRunByUserIdRequestPtr Request
    ): Self(Self), Request(Request)
    {

    }

    FUserDomain::FRunTask::FRunTask(
        const FRunTask& From
    ): TGs2Future(From), Self(From.Self), Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FRunTask::Action(
        TSharedPtr<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>> Result
    )
    {
        Request
            ->WithNamespaceName(Self->NamespaceName)
            ->WithUserId(Self->UserId);
        const auto Future = Self->Client->RunByUserId(
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
            
            if (ResultModel->GetItem() != nullptr)
            {
                const auto ParentKey = Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                    Self->NamespaceName,
                    Self->UserId,
                    "Job"
                );
                const auto Key = Gs2::JobQueue::Domain::Model::FJobDomain::CreateCacheKey(
                    ResultModel->GetItem()->GetName()
                );
                Self->Cache->Delete(Gs2::JobQueue::Model::FJob::TypeName, ParentKey, Key);
            }
        }
        if (ResultModel->GetItem() != nullptr) {
            Self->JobQueueDomain->OnExecutedEvent().Broadcast(
                ResultModel->GetItem(),
                ResultModel->GetResult()
                );
            auto Domain = MakeShared<Gs2::JobQueue::Domain::Model::FJobDomain>(
                Self->Cache,
                Self->JobQueueDomain,
                Self->StampSheetConfiguration,
                Self->Session,
                Request->GetNamespaceName(),
                ResultModel->GetItem()->GetUserId(),
                ResultModel->GetItem()->GetName()
            );
            Domain->IsLastJob = *ResultModel->GetIsLastJob();

            *Result = Domain;
        } else
        {
            Self->IsLastJob = *ResultModel->GetIsLastJob();

            *Result = nullptr;
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FRunTask>> FUserDomain::Run(
        Request::FRunByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRunTask>>(this->AsShared(), Request);
    }

    Gs2::JobQueue::Domain::Iterator::FDescribeJobsByUserIdIteratorPtr FUserDomain::Jobs(
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Iterator::FDescribeJobsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeJobs(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::JobQueue::Model::FJob::TypeName,
            Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Job"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeJobs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::JobQueue::Model::FJob::TypeName,
            Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "Job"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain> FUserDomain::Job(
        const FString JobName
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FJobDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            JobName == TEXT("") ? TOptional<FString>() : TOptional<FString>(JobName)
        );
    }

    Gs2::JobQueue::Domain::Iterator::FDescribeDeadLetterJobsByUserIdIteratorPtr FUserDomain::DeadLetterJobs(
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Iterator::FDescribeDeadLetterJobsByUserIdIterator>(
            Cache,
            Client,
            NamespaceName,
            UserId
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeDeadLetterJobs(
    TFunction<void()> Callback
    )
    {
        return Cache->ListSubscribe(
            Gs2::JobQueue::Model::FDeadLetterJob::TypeName,
            Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "DeadLetterJob"
            ),
            Callback
        );
    }

    void FUserDomain::UnsubscribeDeadLetterJobs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Cache->ListUnsubscribe(
            Gs2::JobQueue::Model::FDeadLetterJob::TypeName,
            Gs2::JobQueue::Domain::Model::FUserDomain::CreateCacheParentKey(
                NamespaceName,
                UserId,
                "DeadLetterJob"
            ),
            CallbackID
        );
    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain> FUserDomain::DeadLetterJob(
        const FString DeadLetterJobName
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FDeadLetterJobDomain>(
            Cache,
            JobQueueDomain,
            StampSheetConfiguration,
            Session,
            NamespaceName,
            UserId,
            DeadLetterJobName == TEXT("") ? TOptional<FString>() : TOptional<FString>(DeadLetterJobName)
        );
    }

    FString FUserDomain::CreateCacheParentKey(
        TOptional<FString> NamespaceName,
        TOptional<FString> UserId,
        FString ChildType
    )
    {
        return FString("") +
            (NamespaceName.IsSet() ? *NamespaceName : "null") + ":" +
            (UserId.IsSet() ? *UserId : "null") + ":" +
            ChildType;
    }

    FString FUserDomain::CreateCacheKey(
        TOptional<FString> UserId
    )
    {
        return FString("") +
            (UserId.IsSet() ? *UserId : "null");
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

