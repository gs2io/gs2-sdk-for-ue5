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

#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/Namespace.h"
#include "JobQueue/Domain/Model/Job.h"
#include "JobQueue/Domain/Model/JobAccessToken.h"
#include "JobQueue/Domain/Model/JobResult.h"
#include "JobQueue/Domain/Model/JobResultAccessToken.h"
#include "JobQueue/Domain/Model/User.h"
#include "JobQueue/Domain/Model/UserAccessToken.h"
#include "JobQueue/Model/Cache/Job.h"
#include "JobQueue/Model/Cache/JobResult.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/Transaction/JobQueueJobDomainFactory.h"
#include "Core/Domain/Transaction/InternalTransactionDomainFactory.h"
#include "Core/Domain/Transaction/ManualTransactionDomain.h"

namespace Gs2::JobQueue::Domain::Model
{

    FUserDomain::FUserDomain(
        const Core::Domain::FGs2Ptr& Gs2,
        const JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const TOptional<FString> NamespaceName,
        const TOptional<FString> UserId
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Service(Service),
        Client(MakeShared<Gs2::JobQueue::FGs2JobQueueRestClient>(Gs2->RestSession)),
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
        Gs2(From.Gs2),
        Service(From.Service),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        UserId(From.UserId),
        ParentKey(From.ParentKey)
    {

    }

    FUserDomain::FPushTask::FPushTask(
        const TSharedPtr<FUserDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
            for (const auto& Item : *ResultModel->GetItems())
            {
                if (!Item.IsValid()) continue;
                Gs2::JobQueue::Model::Cache::FJobCache::Put(
                    Self->Gs2->Cache,
                    Request->GetNamespaceName(), Request->GetUserId(), Item->GetName(),
                    TOptional<int32>(), Item
                );
            }
        }

        auto Domain = MakeShared<TArray<TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain>>>();
        if (ResultModel.IsValid() && ResultModel->GetItems().IsValid())
        {
        for (auto i=0; i<ResultModel->GetItems()->Num(); i++)
        {
            Domain->Add(
                MakeShared<Gs2::JobQueue::Domain::Model::FJobDomain>(
                    Self->Gs2,
                    Self->Service,
                    Request->GetNamespaceName(),
                    (*ResultModel->GetItems())[i]->GetUserId(),
                    (*ResultModel->GetItems())[i]->GetName()
                )
            );
        }
        }
        if (ResultModel->GetAutoRun().IsSet() && !*ResultModel->GetAutoRun() &&
            Self->NamespaceName.IsSet() && Self->UserId.IsSet())
        {
            Self->Gs2->JobQueueDomain->PushForUser(
                *Self->NamespaceName,
                *Self->UserId
            );
        }
        if (ResultModel != nullptr)
        {
            if (ResultModel->GetAutoRun().IsSet())
            {
                Self->AutoRun = ResultModel->GetAutoRun();
            }
        }
        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FPushTask>> FUserDomain::Push(
        Request::FPushByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FPushTask>>(this->AsShared(), Request);
    }

    FUserDomain::FRunTask::FRunTask(
        const TSharedPtr<FUserDomain>& Self,
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
            ->WithContextStack((!Request->GetContextStack().IsSet() || Request->GetContextStack()->IsEmpty()) ? Self->Gs2->DefaultContextStack : Request->GetContextStack())
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
        const auto ResultModel = Future->GetTask().Result();
        Future->EnsureCompletion();

        if (!ResultModel.IsValid())
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
        }
        const auto Item = ResultModel->GetItem();
        if (Item.IsValid())
        {
            if (!Item->GetUserId().IsSet())
            {
                const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
                Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("userId"), TEXT("userId is invalid."), TEXT("invalid_response")));
                return MakeShared<Gs2::Core::Model::FUnknownError>(Details);
            }
            Self->Gs2->JobQueueDomain->JobQueueExecutedEventHandler(
                Item,
                ResultModel->GetResult(),
                TOptional<int32>()
            );
            Gs2::JobQueue::Model::Cache::FJobCache::Delete(
                Self->Gs2->Cache,
                Request->GetNamespaceName(),
                Item->GetUserId(),
                TOptional<FString>(),
                TOptional<int32>()
            );
        }
        auto Domain = MakeShared<Gs2::JobQueue::Domain::Model::FJobDomain>(
            Self->Gs2,
            Self->Service,
            Request->GetNamespaceName(),
            Item.IsValid() ? Item->GetUserId() : Self->UserId,
            Item.IsValid() ? Item->GetName() : TOptional<FString>()
        );
        if (ResultModel.IsValid())
        {
            if (ResultModel->GetIsLastJob().IsSet())
            {
                Domain->IsLastJob = *ResultModel->GetIsLastJob();
            }
            Domain->Item = Item;
            Domain->Result = ResultModel->GetResult();
        }

        *Result = Domain;
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUserDomain::FRunTask>> FUserDomain::Run(
        Request::FRunByUserIdRequestPtr Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FRunTask>>(this->AsShared(), Request);
    }

    Gs2::JobQueue::Domain::Iterator::FDescribeJobsByUserIdIteratorPtr FUserDomain::Jobs(
        const TOptional<FString> TimeOffsetToken
    ) const
    {
        return MakeShared<Gs2::JobQueue::Domain::Iterator::FDescribeJobsByUserIdIterator>(
            Gs2,
            Client,
            NamespaceName,
            UserId,
            TimeOffsetToken
        );
    }

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeJobs(
    TFunction<void()> Callback

    )
    {
        return Gs2->Cache->ListSubscribe(
            Gs2::JobQueue::Model::FJob::TypeName,
            Gs2::JobQueue::Model::Cache::FJobCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            Callback,
            Callback
        );
    }
    void FUserDomain::UnsubscribeJobs(
        Gs2::Core::Domain::CallbackID CallbackID
    )
    {
        Gs2->Cache->ListUnsubscribe(
            Gs2::JobQueue::Model::FJob::TypeName,
            Gs2::JobQueue::Model::Cache::FJobCache::CreateCacheParentKey(
                NamespaceName,
                UserId,
                TOptional<int32>()
            ),
            CallbackID
        );
    }
    class FUserDomain::FCollectJobsTask : public Gs2::Core::Util::TGs2Future<TArray<Gs2::JobQueue::Model::FJobPtr>>, public TSharedFromThis<FCollectJobsTask>
    {
        const TSharedPtr<FUserDomain> Self;
        const TFunction<void(TArray<Gs2::JobQueue::Model::FJobPtr>)> OnCollected;
    const TOptional<FString> QueryTimeOffsetToken;
    public:
        explicit FCollectJobsTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::JobQueue::Model::FJobPtr>)> OnCollected,const TOptional<FString> TimeOffsetToken) : Self(Self), OnCollected(OnCollected), QueryTimeOffsetToken(TimeOffsetToken) {}
        FCollectJobsTask(const FCollectJobsTask& From) : TGs2Future(From), Self(From.Self), OnCollected(From.OnCollected), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
        virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<TArray<Gs2::JobQueue::Model::FJobPtr>>> Result) override
        {
            TArray<Gs2::JobQueue::Model::FJobPtr> Items;
            auto Iterator = Self->Jobs(QueryTimeOffsetToken)->begin();
            while (Iterator.HasNext())
            {
                if (Iterator.IsError()) return Iterator.Error();
                if (Iterator.IsCurrentValid()) Items.Add(Iterator.Current());
                ++Iterator;
            }
            if (Iterator.IsError()) return Iterator.Error();
            *Result = MakeShared<TArray<Gs2::JobQueue::Model::FJobPtr>>(Items);
            if (OnCollected) OnCollected(Items);
            return nullptr;
        }
    };

    Gs2::Core::Domain::CallbackID FUserDomain::SubscribeJobs(
        TFunction<void(TArray<Gs2::JobQueue::Model::FJobPtr>)> Callback,const TOptional<FString> TimeOffsetToken
    )
    {
        const TWeakPtr<Gs2::Core::Domain::FGs2> WeakGs2 = this->Gs2;
        const TWeakPtr<JobQueue::Domain::FGs2JobQueueDomain> WeakService = this->Service;
        const auto QueryNamespaceName = NamespaceName;
        const auto QueryUserId = UserId;
        const auto QueryTimeOffsetToken = TimeOffsetToken;
        const auto Parent = Gs2::JobQueue::Model::Cache::FJobCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    );
        return Gs2->Cache->ListSubscribeTyped(
            Gs2::JobQueue::Model::FJob::TypeName,
            Parent,
            [Callback, WeakGs2](const TArray<FGs2ObjectPtr>& Values)
            {
                if (!WeakGs2.Pin().IsValid()) return;
                TArray<Gs2::JobQueue::Model::FJobPtr> TypedValues;
                for (const auto& Value : Values) if (Value.IsValid()) TypedValues.Add(StaticCastSharedPtr<Gs2::JobQueue::Model::FJob>(Value));
                Callback(TypedValues);
            },
            [WeakGs2, WeakService, Callback, QueryNamespaceName, QueryUserId, QueryTimeOffsetToken]()
            {
                const auto Owner = WeakGs2.Pin();
                if (!Owner.IsValid()) return;
                const auto Domain = MakeShared<FUserDomain>(Owner, WeakService.Pin(), QueryNamespaceName, QueryUserId);
                const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJobsTask>>(Domain, Callback, QueryTimeOffsetToken);
                Task->StartBackgroundTask();
            }
        );
    }

    void FUserDomain::InvalidateJobs(const TOptional<FString> TimeOffsetToken)
    {
        Gs2->Cache->ClearListCache(
            Gs2::JobQueue::Model::FJob::TypeName,
            Gs2::JobQueue::Model::Cache::FJobCache::CreateCacheParentKey(
        NamespaceName,
        UserId,
        TOptional<int32>()
    )
        );
    }

    FUserDomain::FSubscribeJobsWithInitialCallTask::FSubscribeJobsWithInitialCallTask(const TSharedPtr<FUserDomain>& Self, TFunction<void(TArray<Gs2::JobQueue::Model::FJobPtr>)> Callback,const TOptional<FString> TimeOffsetToken) : Self(Self), Callback(Callback), QueryTimeOffsetToken(TimeOffsetToken) {}
    FUserDomain::FSubscribeJobsWithInitialCallTask::FSubscribeJobsWithInitialCallTask(const FSubscribeJobsWithInitialCallTask& From) : TGs2Future(From), Self(From.Self), Callback(From.Callback), QueryTimeOffsetToken(From.QueryTimeOffsetToken) {}
    Gs2::Core::Model::FGs2ErrorPtr FUserDomain::FSubscribeJobsWithInitialCallTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::CallbackID>> Result)
    {
        const auto Task = Gs2::Core::Util::New<FAsyncTask<FCollectJobsTask>>(Self, TFunction<void(TArray<Gs2::JobQueue::Model::FJobPtr>)>(), QueryTimeOffsetToken);
        Task->StartSynchronousTask(); Task->EnsureCompletion();
        if (Task->GetTask().IsError()) return Task->GetTask().Error();
        const auto Values = Task->GetTask().Result();
        const auto CallbackId = Self->SubscribeJobs(Callback, QueryTimeOffsetToken);
        Callback(*Values); *Result = MakeShared<Gs2::Core::Domain::CallbackID>(CallbackId);
        return nullptr;
    }
    TSharedPtr<FAsyncTask<FUserDomain::FSubscribeJobsWithInitialCallTask>> FUserDomain::SubscribeJobsWithInitialCall(TFunction<void(TArray<Gs2::JobQueue::Model::FJobPtr>)> Callback,const TOptional<FString> TimeOffsetToken)
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeJobsWithInitialCallTask>>(this->AsShared(), Callback, TimeOffsetToken);
    }

    TSharedPtr<Gs2::JobQueue::Domain::Model::FJobDomain> FUserDomain::Job(
        const FString JobName
    )
    {
        return MakeShared<Gs2::JobQueue::Domain::Model::FJobDomain>(
            Gs2,
            Service,
            NamespaceName,
            UserId,
            JobName == TEXT("") ? TOptional<FString>() : TOptional<FString>(JobName)
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
