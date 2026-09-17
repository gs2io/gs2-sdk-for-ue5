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

#include "Schedule/Domain/SpeculativeExecutor/Consume/DeleteTriggerByUserIdSpeculativeExecutor.h"
#include "Schedule/Model/Cache/Trigger.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Schedule::Domain::SpeculativeExecutor
{

    namespace
    {
        using FTriggerPtr = Gs2::Schedule::Model::FTriggerPtr;
        using FTriggerCache = Gs2::Schedule::Model::Cache::FTriggerCache;

        static FString DeleteTriggerExpectedId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const FString& TriggerName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:schedule:%s:user:%s:trigger:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *TriggerName);
        }

        static FString DeleteTriggerSnapshot(const TSharedPtr<FJsonObject>& Json)
        {
            FString Result;
            const auto Writer = TJsonWriterFactory<>::Create(&Result);
            FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
            return Result;
        }

        static bool DeleteTriggerIsExpected(const FTriggerPtr& Item, const FString& ExpectedId, const FString& UserId, const FString& TriggerName)
        {
            return Item.IsValid() && Item->GetTriggerId().IsSet() && *Item->GetTriggerId() == ExpectedId && Item->GetUserId().IsSet() && *Item->GetUserId() == UserId && Item->GetName().IsSet() && *Item->GetName() == TriggerName;
        }

    }

    FString FDeleteTriggerByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Schedule:DeleteTriggerByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteTriggerByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr& Request,
        Gs2::Schedule::Model::FTriggerPtr Item
    )
    {
        return nullptr;
    }

    FDeleteTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteTriggerByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!AccessToken.IsValid() || !AccessToken->GetUserId().IsSet() || AccessToken->GetUserId()->IsEmpty() || !Request.IsValid()) return nullptr;
        const auto Prepared = Gs2::Schedule::Request::FDeleteTriggerByUserIdRequest::FromJson(Request->ToJson());
        if (!Prepared.IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(AccessToken->GetUserId());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || Prepared->GetUserId() != AccessToken->GetUserId() || !Prepared->GetNamespaceName().IsSet() || !Prepared->GetTriggerName().IsSet()) return nullptr;
        const auto UserId = *AccessToken->GetUserId();
        const auto TimeOffset = AccessToken->GetTimeOffset();
        const auto ExpectedId = DeleteTriggerExpectedId(Domain, *Prepared->GetNamespaceName(), UserId, *Prepared->GetTriggerName());
        FTriggerPtr PreparedItem;
        if (!FTriggerCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetTriggerName(), TimeOffset, &PreparedItem) || !DeleteTriggerIsExpected(PreparedItem, ExpectedId, UserId, *Prepared->GetTriggerName())) return nullptr;
        const FString PreparedSnapshot = DeleteTriggerSnapshot(PreparedItem->ToJson());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset, ExpectedId, PreparedSnapshot]()
        {
            FTriggerPtr Live;
            if (FTriggerCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetTriggerName(), TimeOffset, &Live) && DeleteTriggerIsExpected(Live, ExpectedId, UserId, *Prepared->GetTriggerName()) && DeleteTriggerSnapshot(Live->ToJson()) == PreparedSnapshot) {
                FTriggerCache::Put(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetTriggerName(), TimeOffset, nullptr);
            }
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteTriggerByUserIdSpeculativeExecutor::FCommitTask>> FDeleteTriggerByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr FDeleteTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr FDeleteTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FDeleteTriggerByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
