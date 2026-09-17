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

#include "Schedule/Domain/SpeculativeExecutor/Verify/VerifyEventByUserIdSpeculativeExecutor.h"
#include "Schedule/Domain/Gs2Schedule.h"
#include "Schedule/Model/Cache/Event.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Schedule::Domain::SpeculativeExecutor
{
    namespace
    {
        using FEventPtr = Gs2::Schedule::Model::FEventPtr;
        using FEventCache = Gs2::Schedule::Model::Cache::FEventCache;

        bool ScheduleVerifyEventTypeIsValid(const FString& VerifyType)
        {
            return VerifyType == TEXT("inSchedule") || VerifyType == TEXT("notInSchedule");
        }

        bool ScheduleVerifyEventIsExpected(
            const FEventPtr& Item,
            const FString& ExpectedEventId,
            const FString& EventName
        )
        {
            return Item.IsValid() && Item->GetEventId().IsSet() && *Item->GetEventId() == ExpectedEventId &&
                Item->GetName().IsSet() && *Item->GetName() == EventName;
        }

        Gs2::Core::Model::FGs2ErrorPtr ScheduleVerifyEventFailure(const FString& Reason)
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("event"), Reason, TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
    }

    FString FVerifyEventByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Schedule:VerifyEventByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEventByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr& Request,
        Gs2::Schedule::Model::FEventPtr Item
    )
    {
        if (!Request.IsValid() || !Request->GetVerifyType().IsSet() ||
            !ScheduleVerifyEventTypeIsValid(*Request->GetVerifyType()))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("verifyType"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        if (!Item.IsValid()) return ScheduleVerifyEventFailure(TEXT("notInSchedule"));
        return nullptr;
    }

    FVerifyEventByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyEventByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEventByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Schedule::Request::FVerifyEventByUserIdRequest::FromJson(Request->ToJson());
        if (!PreparedToken.IsValid() || !PreparedRequest.IsValid() || !PreparedToken->GetUserId().IsSet() ||
            PreparedToken->GetUserId().Get(FString()).IsEmpty() || Domain->RestSession->OwnerId().IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetEventName().IsSet() || PreparedRequest->GetEventName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() || !ScheduleVerifyEventTypeIsValid(PreparedRequest->GetVerifyType().Get(FString()))) return nullptr;

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto EventName = PreparedRequest->GetEventName();
        const auto UserId = PreparedToken->GetUserId().Get(FString());
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedEventId = FString::Printf(
            TEXT("grn:gs2:%s:%s:schedule:%s:event:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *EventName.Get(FString()));
        FEventPtr Active;
        FEventPtr Inactive;
        if (!FEventCache::TryGet(Domain->Cache, NamespaceName, UserId, EventName, TOptional<bool>(true), TimeOffset, &Active)) return nullptr;
        const bool InSchedule = Active.IsValid();
        if (!InSchedule && !FEventCache::TryGet(Domain->Cache, NamespaceName, UserId, EventName, TOptional<bool>(false), TimeOffset, &Inactive)) return nullptr;
        const auto Item = InSchedule ? Active : Inactive;
        if (!ScheduleVerifyEventIsExpected(Item, ExpectedEventId, EventName.Get(FString()))) return nullptr;
        const bool Satisfied = PreparedRequest->GetVerifyType().Get(FString()) == TEXT("inSchedule") ? InSchedule : !InSchedule;
        if (!Satisfied)
        {
            return ScheduleVerifyEventFailure(PreparedRequest->GetVerifyType().Get(FString()) == TEXT("inSchedule") ? TEXT("notInSchedule") : TEXT("inSchedule"));
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, EventName, TimeOffset, ExpectedEventId, VerifyType = PreparedRequest->GetVerifyType().Get(FString())]()
        {
            FEventPtr CurrentActive;
            FEventPtr CurrentInactive;
            if (!FEventCache::TryGet(Cache, NamespaceName, UserId, EventName, TOptional<bool>(true), TimeOffset, &CurrentActive)) return false;
            const bool CurrentInSchedule = CurrentActive.IsValid();
            if (!CurrentInSchedule && !FEventCache::TryGet(Cache, NamespaceName, UserId, EventName, TOptional<bool>(false), TimeOffset, &CurrentInactive)) return false;
            const auto Current = CurrentInSchedule ? CurrentActive : CurrentInactive;
            if (!ScheduleVerifyEventIsExpected(Current, ExpectedEventId, EventName.Get(FString()))) return false;
            return VerifyType == TEXT("inSchedule") ? CurrentInSchedule : !CurrentInSchedule;
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyEventByUserIdSpeculativeExecutor::FCommitTask>> FVerifyEventByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyEventByUserIdSpeculativeExecutor::FCommitTask>> FVerifyEventByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Schedule::Request::FVerifyEventByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = Inverse->GetVerifyType().Get(FString());
        if (VerifyType == TEXT("inSchedule")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notInSchedule")));
        else if (VerifyType == TEXT("notInSchedule")) Inverse->WithVerifyType(TOptional<FString>(TEXT("inSchedule")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr FVerifyEventByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr FVerifyEventByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FVerifyEventByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
