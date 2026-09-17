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
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Schedule/Domain/SpeculativeExecutor/Verify/VerifyTriggerByUserIdSpeculativeExecutor.h"
#include "Schedule/Domain/Gs2Schedule.h"
#include "Schedule/Model/Cache/Trigger.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Schedule::Domain::SpeculativeExecutor
{

    namespace
    {
        using FTriggerPtr = Gs2::Schedule::Model::FTriggerPtr;
        using FTriggerCache = Gs2::Schedule::Model::Cache::FTriggerCache;

        static int64 ScheduleVerifyTriggerCurrentTimeMillis(const TOptional<int32>& TimeOffset)
        {
            return static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) +
                static_cast<int64>(TimeOffset.Get(0)) * 1000;
        }

        static bool ScheduleVerifyTriggerCanEvaluate(const FString& VerifyType, const bool HasElapsedMinutes)
        {
            return VerifyType == TEXT("notTriggerd") ||
                ((VerifyType == TEXT("elapsed") || VerifyType == TEXT("notElapsed")) && HasElapsedMinutes);
        }

        static bool ScheduleVerifyTriggerIsExpected(
            const FTriggerPtr& Item,
            const FString& ExpectedTriggerId,
            const FString& UserId,
            const FString& TriggerName
        )
        {
            return Item.IsValid() && Item->GetTriggerId().IsSet() && *Item->GetTriggerId() == ExpectedTriggerId &&
                Item->GetUserId().IsSet() && *Item->GetUserId() == UserId &&
                Item->GetName().IsSet() && *Item->GetName() == TriggerName;
        }

        static bool ScheduleVerifyTriggerPredicate(
            const FTriggerPtr& Item,
            const FString& ExpectedTriggerId,
            const FString& UserId,
            const FString& TriggerName,
            const FString& VerifyType,
            const int32 ElapsedMinutes,
            const int64 LogicalNow
        )
        {
            if (VerifyType == TEXT("notTriggerd") && !Item.IsValid()) return true;
            if (!ScheduleVerifyTriggerIsExpected(Item, ExpectedTriggerId, UserId, TriggerName)) return false;
            if (VerifyType == TEXT("notTriggerd"))
            {
                return Item->GetExpiresAt().IsSet() && *Item->GetExpiresAt() <= LogicalNow;
            }
            if (!Item->GetCreatedAt().IsSet()) return false;
            const int64 Elapsed = (LogicalNow - *Item->GetCreatedAt()) / 60000;
            return VerifyType == TEXT("elapsed") ? Elapsed >= ElapsedMinutes : Elapsed < ElapsedMinutes;
        }
    }

    FString FVerifyTriggerByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Schedule:VerifyTriggerByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyTriggerByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr&,
        Gs2::Schedule::Model::FTriggerPtr
    )
    {
        return nullptr;
    }

    FVerifyTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr& Request,
        bool Inverse
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request),
        Inverse(Inverse)
    {

    }

    FVerifyTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request),
        Inverse(From.Inverse)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyTriggerByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;

        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr PreparedRequest =
            Gs2::Schedule::Request::FVerifyTriggerByUserIdRequest::FromJson(Request->ToJson());
        if (!PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty() ||
            Domain->RestSession->OwnerId().IsEmpty()) return nullptr;

        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString())) return nullptr;

        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        const bool HasElapsedMinutes = PreparedRequest->GetElapsedMinutes().IsSet();
        if (!ScheduleVerifyTriggerCanEvaluate(VerifyType, HasElapsedMinutes)) return nullptr;

        const FString UserId = PreparedToken->GetUserId().Get(FString());
        const TOptional<FString> NamespaceName = PreparedRequest->GetNamespaceName();
        const TOptional<FString> TriggerName = PreparedRequest->GetTriggerName();
        const FString NamespaceValue = NamespaceName.Get(FString());
        const FString TriggerValue = TriggerName.Get(FString());
        const int32 ElapsedMinutes = PreparedRequest->GetElapsedMinutes().Get(0);
        const TOptional<int32> TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedTriggerId = FString::Printf(
            TEXT("grn:gs2:%s:%s:schedule:%s:user:%s:trigger:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceValue, *UserId, *TriggerValue);
        FTriggerPtr PreparedItem;
        if (!FTriggerCache::TryGet(Domain->Cache, NamespaceName, UserId, TriggerName, TimeOffset, &PreparedItem)) return nullptr;
        const int64 LogicalNow = ScheduleVerifyTriggerCurrentTimeMillis(TimeOffset);
        bool Satisfied = false;
        if (VerifyType == TEXT("notTriggerd") && !PreparedItem.IsValid())
        {
            Satisfied = true;
        }
        else
        {
            if (!ScheduleVerifyTriggerIsExpected(PreparedItem, ExpectedTriggerId, UserId, TriggerValue) ||
                (VerifyType == TEXT("notTriggerd") && !PreparedItem->GetExpiresAt().IsSet()) ||
                (VerifyType != TEXT("notTriggerd") && !PreparedItem->GetCreatedAt().IsSet())) return nullptr;
            Satisfied = ScheduleVerifyTriggerPredicate(
                PreparedItem,
                ExpectedTriggerId,
                UserId,
                TriggerValue,
                VerifyType,
                ElapsedMinutes,
                LogicalNow);
        }
        if (Satisfied == Inverse)
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            const FString Reason = VerifyType == TEXT("notTriggerd") ? TEXT("triggered") :
                (VerifyType == TEXT("elapsed") ? TEXT("notElapsed") : TEXT("elapsed"));
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("trigger"), Reason, TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }

        const bool PreparedInverse = Inverse;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, TriggerName, ExpectedTriggerId,
            TriggerValue, VerifyType, ElapsedMinutes, TimeOffset, PreparedInverse]()
        {
            FTriggerPtr Current;
            if (!FTriggerCache::TryGet(Cache, NamespaceName, UserId, TriggerName, TimeOffset, &Current)) return false;
            return ScheduleVerifyTriggerPredicate(
                Current,
                ExpectedTriggerId,
                UserId,
                TriggerValue,
                VerifyType,
                ElapsedMinutes,
                ScheduleVerifyTriggerCurrentTimeMillis(TimeOffset)) != PreparedInverse;
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyTriggerByUserIdSpeculativeExecutor::FCommitTask>> FVerifyTriggerByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr& Request,
        bool Inverse
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, Inverse);
    }

    TSharedPtr<FAsyncTask<FVerifyTriggerByUserIdSpeculativeExecutor::FCommitTask>> FVerifyTriggerByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Schedule::Request::FVerifyTriggerByUserIdRequest::FromJson(Request->ToJson());
        return Execute(Domain, Service, AccessToken, Inverse, true);
    }

    Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr FVerifyTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr FVerifyTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FVerifyTriggerByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
