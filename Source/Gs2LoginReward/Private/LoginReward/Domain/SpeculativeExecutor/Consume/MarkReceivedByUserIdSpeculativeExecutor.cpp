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

#include "LoginReward/Domain/SpeculativeExecutor/Consume/MarkReceivedByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "LoginReward/Domain/Gs2LoginReward.h"
#include "LoginReward/Domain/SpeculativeExecutor/ReceiveStatusSpeculativeCommit.h"

namespace Gs2::LoginReward::Domain::SpeculativeExecutor
{

    FString FMarkReceivedByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2LoginReward:MarkReceivedByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FMarkReceivedByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr& Request,
        Gs2::LoginReward::Model::FReceiveStatusPtr Item
    )
    {
        return nullptr;
    }

    FMarkReceivedByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FMarkReceivedByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMarkReceivedByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid()) return nullptr;

        const auto Prepared = Gs2::LoginReward::Request::FMarkReceivedByUserIdRequest::FromJson(
            Request->ToJson()
        );
        if (!Prepared.IsValid() || !AccessToken->GetUserId().IsSet() ||
            AccessToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() &&
            Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            Prepared->WithUserId(AccessToken->GetUserId());
        }
        if (!Prepared->GetUserId().IsSet() ||
            Prepared->GetUserId().Get(FString()) != AccessToken->GetUserId().Get(FString()) ||
            !Prepared->GetStepNumber().IsSet() || Prepared->GetStepNumber().Get(0) < 0) return nullptr;

        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto BonusModelName = Prepared->GetBonusModelName();
        const auto UserId = AccessToken->GetUserId();
        const auto TimeOffset = AccessToken->GetTimeOffset();
        const int64 CurrentTimeMillis = static_cast<int64>(
            FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0
        ) + static_cast<int64>(TimeOffset.Get(0)) * 1000;
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:loginReward:%s:user:%s:status:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId.Get(FString()), *BonusModelName.Get(FString())
        );
        const int32 StepNumber = Prepared->GetStepNumber().Get(0);
        auto Commit = MakeShared<FReceiveStatusSpeculativeCommit>(
            Domain->Cache, NamespaceName, UserId.Get(FString()), BonusModelName, TimeOffset,
            ExpectedId,
            [StepNumber, CurrentTimeMillis](const Gs2::LoginReward::Model::FReceiveStatusPtr& Source)
                -> Gs2::LoginReward::Model::FReceiveStatusPtr
            {
                if (!Source.IsValid() || StepNumber == TNumericLimits<int32>::Max()) return nullptr;
                const auto Changed = MakeShared<Gs2::LoginReward::Model::FReceiveStatus>(*Source);
                const auto Existing = Source->GetReceivedSteps();
                const auto Steps = Existing.IsValid()
                    ? MakeShared<TArray<bool>>(*Existing)
                    : MakeShared<TArray<bool>>();
                if (StepNumber < Steps->Num() && (*Steps)[StepNumber]) return nullptr;
                if (StepNumber >= Steps->Num()) Steps->SetNum(StepNumber + 1);
                (*Steps)[StepNumber] = true;
                return Changed->WithReceivedSteps(Steps)
                    ->WithLastReceivedAt(CurrentTimeMillis)
                    ->WithUpdatedAt(CurrentTimeMillis)
                    ->WithRevision(0);
            }
        );
        if (!Commit->CanPrepare()) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
            Commit->CompositionKey(),
            [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
            { return Commit->TryCompose(Current, HasCurrent, Next); },
            [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMarkReceivedByUserIdSpeculativeExecutor::FCommitTask>> FMarkReceivedByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::LoginReward::Domain::FGs2LoginRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr FMarkReceivedByUserIdSpeculativeExecutor::Rate(
        const Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr FMarkReceivedByUserIdSpeculativeExecutor::Rate(
        const Gs2::LoginReward::Request::FMarkReceivedByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
