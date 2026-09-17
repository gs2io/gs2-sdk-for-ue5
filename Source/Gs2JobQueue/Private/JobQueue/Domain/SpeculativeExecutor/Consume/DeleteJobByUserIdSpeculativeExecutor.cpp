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

#include "JobQueue/Domain/SpeculativeExecutor/Consume/DeleteJobByUserIdSpeculativeExecutor.h"
#include "JobQueue/Domain/Gs2JobQueue.h"


#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Auth/Model/AccessToken.h"
#include "JobQueue/Model/Cache/Job.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::JobQueue::Domain::SpeculativeExecutor
{

    namespace
    {
        FString DeleteJobSnapshot(const Gs2::JobQueue::Model::FJobPtr& Item)
        {
            FString Value;
            auto Writer = TJsonWriterFactory<TCHAR, TCondensedJsonPrintPolicy<TCHAR>>::Create(&Value);
            FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer);
            return Value;
        }
    }

    FString FDeleteJobByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2JobQueue:DeleteJobByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteJobByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request,
        Gs2::JobQueue::Model::FJobPtr Item
    )
    {
        return nullptr;
    }

    FDeleteJobByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteJobByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteJobByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid() || !AccessToken->GetUserId().IsSet() || AccessToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        const auto Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto Prepared = MakeShared<Gs2::JobQueue::Request::FDeleteJobByUserIdRequest>(*Request);
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString())) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto JobName = Prepared->GetJobName();
        const auto UserId = Token->GetUserId();
        const auto TimeOffset = Token->GetTimeOffset();
        const auto ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:queue:%s:user:%s:job:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *UserId.Get(FString()), *JobName.Get(FString()));
        Gs2::JobQueue::Model::FJobPtr Expected;
        if (!Gs2::JobQueue::Model::Cache::FJobCache::TryGet(Domain->Cache, NamespaceName, UserId, JobName, TimeOffset, &Expected) || !Expected.IsValid() || Expected->GetJobId().Get(FString()) != ExpectedId || Expected->GetUserId().Get(FString()) != UserId.Get(FString()) || Expected->GetName().Get(FString()) != JobName.Get(FString())) return nullptr;
        const auto Snapshot = DeleteJobSnapshot(Expected);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>(
            [DomainCopy = Domain, NamespaceName, JobName, UserId, TimeOffset, ExpectedId, Snapshot]()
        {
            Gs2::JobQueue::Model::FJobPtr Live;
            if (!Gs2::JobQueue::Model::Cache::FJobCache::TryGet(DomainCopy->Cache, NamespaceName, UserId, JobName, TimeOffset, &Live) || !Live.IsValid() || Live->GetJobId().Get(FString()) != ExpectedId || Live->GetUserId().Get(FString()) != UserId.Get(FString()) || Live->GetName().Get(FString()) != JobName.Get(FString()) || DeleteJobSnapshot(Live) != Snapshot) return;
            Gs2::JobQueue::Model::Cache::FJobCache::Put(DomainCopy->Cache, NamespaceName, UserId, JobName, TimeOffset, nullptr);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteJobByUserIdSpeculativeExecutor::FCommitTask>> FDeleteJobByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::JobQueue::Domain::FGs2JobQueueDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr FDeleteJobByUserIdSpeculativeExecutor::Rate(
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr FDeleteJobByUserIdSpeculativeExecutor::Rate(
        const Gs2::JobQueue::Request::FDeleteJobByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
