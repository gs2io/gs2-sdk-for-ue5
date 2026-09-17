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

#include "Distributor/Domain/SpeculativeExecutor/Verify/AndExpressionByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Distributor/Domain/Gs2Distributor.h"

namespace Gs2::Distributor::Domain::SpeculativeExecutor
{
namespace
{
    Gs2::Auth::Model::FAccessTokenPtr PrepareAndExpressionAccessToken(
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
    )
    {
        Gs2::Auth::Model::FAccessTokenPtr Prepared = nullptr;
        if (AccessToken.IsValid()) Prepared = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        return Prepared;
    }

    Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr PrepareAndExpressionRequest(
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        const auto Prepared = MakeShared<Gs2::Distributor::Request::FAndExpressionByUserIdRequest>(*Request);
        const auto Actions = Request->GetActions();
        if (Actions.IsValid())
        {
            const auto PreparedActions = MakeShared<TArray<Gs2::Core::Model::FVerifyActionPtr>>();
            for (const auto& Action : *Actions)
            {
                Gs2::Core::Model::FVerifyActionPtr PreparedAction = nullptr;
                if (Action.IsValid()) PreparedAction = MakeShared<Gs2::Core::Model::FVerifyAction>(*Action);
                PreparedActions->Add(PreparedAction);
            }
            Prepared->WithActions(PreparedActions);
        }
        return Prepared;
    }

    bool AndExpressionUserIdMatches(
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
    )
    {
        const auto RequestUserId = Request->GetUserId();
        const auto TokenUserId = AccessToken.IsValid()
            ? AccessToken->GetUserId()
            : TOptional<FString>();
        return RequestUserId.IsSet() == TokenUserId.IsSet() &&
            (!RequestUserId.IsSet() || RequestUserId.GetValue() == TokenUserId.GetValue());
    }

    Gs2::Core::Model::FGs2ErrorPtr DispatchAndExpressionVerify(
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FVerifyActionPtr& Action,
        const TBigInt<1024, false>& Rate,
        const bool Inverse,
        Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr* Result
    )
    {
        if (Result == nullptr) return nullptr;
        *Result = nullptr;
        if (!Service.IsValid() || !Action.IsValid()) return nullptr;
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            AccessToken, Action, Rate, Inverse);
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        *Result = Event->GetPreparedCommit();
        return nullptr;
    }
}

    FString FAndExpressionByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Distributor:AndExpressionByUserId");
    }

    FAndExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request,
        const TBigInt<1024, false>& Rate,
        const bool Inverse
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request),
        Rate(Rate),
        Inverse(Inverse)
    {

    }

    FAndExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request),
        Rate(From.Rate),
        Inverse(From.Inverse)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAndExpressionByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto PreparedRequest = PrepareAndExpressionRequest(Request);
        const auto PreparedAccessToken = PrepareAndExpressionAccessToken(AccessToken);
        if (PreparedRequest.IsValid() && PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().GetValue() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        }
        if (!PreparedRequest.IsValid() || !AndExpressionUserIdMatches(PreparedRequest, PreparedAccessToken))
        {
            return nullptr;
        }
        const auto Actions = PreparedRequest->GetActions();
        if (!Actions.IsValid()) return nullptr;

        if (Inverse)
        {
            if (Actions->Num() == 0) return nullptr;
            Gs2::Core::Model::FGs2ErrorPtr LastError;
            bool HasUnknown = false;
            for (const auto& Action : *Actions)
            {
                Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Prepared;
                const auto Error = DispatchAndExpressionVerify(
                    Service, PreparedAccessToken, Action, Rate, true, &Prepared);
                if (Error.IsValid())
                {
                    LastError = Error;
                    continue;
                }
                if (Prepared.IsValid())
                {
                    *Result = Prepared;
                    return nullptr;
                }
                HasUnknown = true;
            }
            if (HasUnknown) return nullptr;
            return LastError;
        }

        const auto Commits = MakeShared<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray>();
        bool HasUnknown = false;
        for (const auto& Action : *Actions)
        {
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Prepared;
            const auto Error = DispatchAndExpressionVerify(
                Service, PreparedAccessToken, Action, Rate, false, &Prepared);
            if (Error.IsValid()) return Error;
            if (!Prepared.IsValid())
            {
                HasUnknown = true;
                continue;
            }
            Commits->Add(Prepared);
        }
        if (HasUnknown) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::BuildAtomicVerificationPreparedCommit(
            Commits, Actions->Num());
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAndExpressionByUserIdSpeculativeExecutor::FCommitTask>> FAndExpressionByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(
            Domain, Service, AccessToken, Request, TBigInt<1024, false>(1), false);
    }

    TSharedPtr<FAsyncTask<FAndExpressionByUserIdSpeculativeExecutor::FCommitTask>> FAndExpressionByUserIdSpeculativeExecutor::ExecuteRated(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, Rate, false);
    }

    TSharedPtr<FAsyncTask<FAndExpressionByUserIdSpeculativeExecutor::FCommitTask>> FAndExpressionByUserIdSpeculativeExecutor::ExecuteInverseRated(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, Rate, true);
    }

    Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr FAndExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr FAndExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FAndExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
