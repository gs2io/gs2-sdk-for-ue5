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

#include "Mission/Domain/SpeculativeExecutor/Verify/VerifyCompleteByUserIdSpeculativeExecutor.h"
#include "Mission/Model/Cache/Complete.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
namespace
{
    bool MissionVerifyCompletePredicate(
        const Gs2::Mission::Model::FCompletePtr& Item,
        const FString& ExpectedId,
        const FString& UserId,
        const FString& MissionGroupName,
        const FString& VerifyType,
        const FString& MissionTaskName
    )
    {
        if (!Item.IsValid() || !Item->GetCompleteId().IsSet() || Item->GetCompleteId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetMissionGroupName().IsSet() || Item->GetMissionGroupName().Get(FString()) != MissionGroupName ||
            !Item->GetCompletedMissionTaskNames().IsValid() || !Item->GetReceivedMissionTaskNames().IsValid()) return false;
        const bool Completed = Item->GetCompletedMissionTaskNames()->Contains(MissionTaskName);
        const bool Received = Item->GetReceivedMissionTaskNames()->Contains(MissionTaskName);
        if (VerifyType == TEXT("completed")) return Completed;
        if (VerifyType == TEXT("notCompleted")) return !Completed;
        if (VerifyType == TEXT("received")) return Received;
        if (VerifyType == TEXT("notReceived")) return !Received;
        if (VerifyType == TEXT("completedAndNotReceived")) return Completed && !Received;
        return false;
    }
}

    FString FVerifyCompleteByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Mission:VerifyCompleteByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCompleteByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr& Request,
        Gs2::Mission::Model::FCompletePtr Item
    )
    {
        const bool Completed = Item->GetCompletedMissionTaskNames()->Contains(Request->GetMissionTaskName().Get(FString()));
        const bool Received = Item->GetReceivedMissionTaskNames()->Contains(Request->GetMissionTaskName().Get(FString()));
        const FString Type = Request->GetVerifyType().Get(FString());
        const bool Satisfied =
            (Type == TEXT("completed") && Completed) ||
            (Type == TEXT("notCompleted") && !Completed) ||
            (Type == TEXT("received") && Received) ||
            (Type == TEXT("notReceived") && !Received) ||
            (Type == TEXT("completedAndNotReceived") && Completed && !Received);
        if (Satisfied) return nullptr;
        return MakeShared<Gs2::Core::Model::FBadRequestError>([]
        {
            auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("missionTaskName", "invalid", ""));
            return Details;
        }());
    }

    FVerifyCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCompleteByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Mission::Request::FVerifyCompleteByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetMissionGroupName().IsSet() || PreparedRequest->GetMissionGroupName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetMissionTaskName().IsSet() || PreparedRequest->GetMissionTaskName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString())) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("completed") && VerifyType != TEXT("notCompleted") && VerifyType != TEXT("received") &&
            VerifyType != TEXT("notReceived") && VerifyType != TEXT("completedAndNotReceived")) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString());
        const FString UserId = PreparedRequest->GetUserId().Get(FString());
        const FString MissionGroupName = PreparedRequest->GetMissionGroupName().Get(FString());
        const FString MissionTaskName = PreparedRequest->GetMissionTaskName().Get(FString());
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:mission:%s:user:%s:group:%s:complete"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *MissionGroupName);
        Gs2::Mission::Model::FCompletePtr Cached;
        if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(
            Domain->Cache, NamespaceName, UserId, MissionGroupName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetCompleteId().IsSet() || Cached->GetCompleteId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetMissionGroupName().IsSet() || Cached->GetMissionGroupName().Get(FString()) != MissionGroupName ||
            !Cached->GetCompletedMissionTaskNames().IsValid() || !Cached->GetReceivedMissionTaskNames().IsValid()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, MissionGroupName, TimeOffset,
            ExpectedId, VerifyType, MissionTaskName]()
        {
            Gs2::Mission::Model::FCompletePtr Current;
            if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(
                Cache, NamespaceName, UserId, MissionGroupName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return MissionVerifyCompletePredicate(Current, ExpectedId, UserId, MissionGroupName, VerifyType, MissionTaskName);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyCompleteByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCompleteByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyCompleteByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCompleteByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = MakeShared<Gs2::Mission::Request::FVerifyCompleteByUserIdRequest>(*Request);
        if (!Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("completed")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notCompleted")));
        else if (*Inverse->GetVerifyType() == TEXT("notCompleted")) Inverse->WithVerifyType(TOptional<FString>(TEXT("completed")));
        else if (*Inverse->GetVerifyType() == TEXT("received")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notReceived")));
        else if (*Inverse->GetVerifyType() == TEXT("notReceived")) Inverse->WithVerifyType(TOptional<FString>(TEXT("received")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr FVerifyCompleteByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr FVerifyCompleteByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FVerifyCompleteByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
