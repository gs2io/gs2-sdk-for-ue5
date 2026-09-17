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

#include "Schedule/Domain/SpeculativeExecutor/Acquire/ExtendTriggerByUserIdSpeculativeExecutor.h"
#include "Schedule/Domain/Gs2Schedule.h"
#include "Schedule/Model/Cache/Trigger.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Schedule::Domain::SpeculativeExecutor
{

    namespace
    {
        using FTrigger = Gs2::Schedule::Model::FTrigger;
        using FTriggerPtr = Gs2::Schedule::Model::FTriggerPtr;
        using FTriggerCache = Gs2::Schedule::Model::Cache::FTriggerCache;

        static int64 ExtendTriggerByUserIdCurrentTimeMillis(const Gs2::Auth::Model::FAccessTokenPtr& Token)
        {
            return static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) + static_cast<int64>(Token.IsValid() ? Token->GetTimeOffset().Get(0) : 0) * 1000;
        }

        static FString ExtendTriggerByUserIdSnapshot(const TSharedPtr<FJsonObject>& Json)
        {
            FString Result;
            const auto Writer = TJsonWriterFactory<>::Create(&Result);
            FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
            return Result;
        }

        static FString ExtendTriggerByUserIdExpectedTriggerId(
            const Gs2::Core::Domain::FGs2Ptr& Domain,
            const FString& NamespaceName,
            const FString& UserId,
            const FString& TriggerName
        )
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:schedule:%s:user:%s:trigger:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *TriggerName);
        }

        static bool ExtendTriggerByUserIdIsExpected(const FTriggerPtr& Item, const FString& Id, const FString& UserId, const FString& Name)
        {
            return Item.IsValid() && Item->GetTriggerId().IsSet() && *Item->GetTriggerId() == Id && Item->GetUserId().IsSet() && *Item->GetUserId() == UserId && Item->GetName().IsSet() && *Item->GetName() == Name;
        }

        static FTriggerPtr ExtendTriggerByUserIdTransform(const FTriggerPtr& Item, const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request, const int64 Now)
        {
            if (!Request.IsValid() || !Request->GetExtendSeconds().IsSet()) return nullptr;
            const bool Expired = !Item.IsValid() || !Item->GetExpiresAt().IsSet() || *Item->GetExpiresAt() <= Now;
            if (Item.IsValid() && !Item->GetExpiresAt().IsSet()) return nullptr;
            const int64 Base = Expired ? Now : *Item->GetExpiresAt();
            const int64 Delta = static_cast<int64>(*Request->GetExtendSeconds()) * 1000;
            if ((Delta > 0 && Base > TNumericLimits<int64>::Max() - Delta) || (Delta < 0 && Base < TNumericLimits<int64>::Min() - Delta)) return nullptr;
            auto Clone = Item.IsValid() ? FTrigger::FromJson(Item->ToJson()) : MakeShared<FTrigger>();
            if (!Clone.IsValid()) return nullptr;
            if (!Item.IsValid()) Clone->WithName(Request->GetTriggerName())->WithUserId(Request->GetUserId());
            if (Expired) Clone->WithTriggeredAt(Now);
            Clone->WithExpiresAt(Base + Delta)->WithCreatedAt(Now)->WithRevision(0);
            return Clone;
        }
    }

    FString FExtendTriggerByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Schedule:ExtendTriggerByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FExtendTriggerByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
        Gs2::Schedule::Model::FTriggerPtr Item
    )
    {
        const auto Changed = ExtendTriggerByUserIdTransform(Item, Request, ExtendTriggerByUserIdCurrentTimeMillis(AccessToken));
        if (Item.IsValid() && Changed.IsValid()) *Item = *Changed;
        return nullptr;
    }

    FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto Prepared = Request.IsValid() ? Gs2::Schedule::Request::FExtendTriggerByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !PreparedAccessToken.IsValid() || !PreparedAccessToken->GetUserId().IsSet() ||
            Prepared->GetUserId() != PreparedAccessToken->GetUserId() || !Prepared->GetExtendSeconds().IsSet() || !Prepared->GetNamespaceName().IsSet() || !Prepared->GetTriggerName().IsSet()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        const auto ExpectedId = ExtendTriggerByUserIdExpectedTriggerId(Domain, *Prepared->GetNamespaceName(), UserId, *Prepared->GetTriggerName());
        FTriggerPtr PreparedItem;
        if (!FTriggerCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetTriggerName(), TimeOffset, &PreparedItem) || (PreparedItem.IsValid() && !ExtendTriggerByUserIdIsExpected(PreparedItem, ExpectedId, UserId, *Prepared->GetTriggerName()))) return nullptr;
        const FString PreparedSnapshot = PreparedItem.IsValid() ? ExtendTriggerByUserIdSnapshot(PreparedItem->ToJson()) : FString();
        const int64 Now = ExtendTriggerByUserIdCurrentTimeMillis(PreparedAccessToken);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset, ExpectedId, PreparedItem, PreparedSnapshot, Now]()
        {
            FTriggerPtr Live;
            if (!FTriggerCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetTriggerName(), TimeOffset, &Live) || (Live.IsValid() && !ExtendTriggerByUserIdIsExpected(Live, ExpectedId, UserId, *Prepared->GetTriggerName()))) return;
            if (!PreparedItem.IsValid()) {
                if (Live.IsValid() && (!Live->GetRevision().IsSet() || *Live->GetRevision() != 0)) return;
            } else if (!Live.IsValid() || ((!Live->GetRevision().IsSet() || *Live->GetRevision() != 0) && ExtendTriggerByUserIdSnapshot(Live->ToJson()) != PreparedSnapshot)) return;
            const auto Changed = ExtendTriggerByUserIdTransform(Live, Prepared, Now);
            if (!Changed.IsValid()) return;
            Changed->WithTriggerId(ExpectedId)->WithUserId(UserId)->WithName(Prepared->GetTriggerName())->WithRevision(0);
            FTriggerCache::Put(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, Prepared->GetTriggerName(), TimeOffset, Changed);
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask>> FExtendTriggerByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr FExtendTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetExtendSeconds().IsSet())
        {
            Request->WithExtendSeconds(*Request->GetExtendSeconds() * Rate);
        }
        return Request;
    }

    Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr FExtendTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetExtendSeconds().IsSet())
        {
            Rate.Multiply(*Request->GetExtendSeconds());
            Request->WithExtendSeconds(Rate.ToInt());
        }
        return Request;
    }
}
