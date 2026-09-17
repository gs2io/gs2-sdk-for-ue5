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

#include "Distributor/Domain/SpeculativeExecutor/Verify/OrExpressionByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Distributor/Domain/Gs2Distributor.h"

namespace Gs2::Distributor::Domain::SpeculativeExecutor
{
namespace
{
    Gs2::Auth::Model::FAccessTokenPtr PrepareOrExpressionAccessToken(
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
    )
    {
        Gs2::Auth::Model::FAccessTokenPtr Prepared = nullptr;
        if (AccessToken.IsValid()) Prepared = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        return Prepared;
    }

    Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr PrepareOrExpressionRequest(
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        const auto Prepared = MakeShared<Gs2::Distributor::Request::FOrExpressionByUserIdRequest>(*Request);
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

    bool OrExpressionUserIdMatches(
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request,
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

    Gs2::Core::Model::FGs2ErrorPtr DispatchOrExpressionVerify(
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

    FString FOrExpressionByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Distributor:OrExpressionByUserId");
    }

    FOrExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request,
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

    FOrExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
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

    Gs2::Core::Model::FGs2ErrorPtr FOrExpressionByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto PreparedRequest = PrepareOrExpressionRequest(Request);
        const auto PreparedAccessToken = PrepareOrExpressionAccessToken(AccessToken);
        if (PreparedRequest.IsValid() && PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().GetValue() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        }
        if (!PreparedRequest.IsValid() || !OrExpressionUserIdMatches(PreparedRequest, PreparedAccessToken))
        {
            return nullptr;
        }
        const auto Actions = PreparedRequest->GetActions();
        if (!Actions.IsValid() || (Inverse && Actions->Num() == 0)) return nullptr;

        if (Inverse)
        {
            const auto Commits = MakeShared<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray>();
            bool HasUnknown = false;
            for (const auto& Action : *Actions)
            {
                Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Prepared;
                const auto Error = DispatchOrExpressionVerify(
                    Service, PreparedAccessToken, Action, Rate, true, &Prepared);
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

        Gs2::Core::Model::FGs2ErrorPtr LastError;
        bool HasUnknown = false;
        for (const auto& Action : *Actions)
        {
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Prepared;
            const auto Error = DispatchOrExpressionVerify(
                Service, PreparedAccessToken, Action, Rate, false, &Prepared);
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
        if (LastError.IsValid())
        {
            return LastError;
        }
        const auto Empty = MakeShared<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray>();
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::BuildAtomicVerificationPreparedCommit(Empty, 0);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FOrExpressionByUserIdSpeculativeExecutor::FCommitTask>> FOrExpressionByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, TBigInt<1024, false>(1), false);
    }

    TSharedPtr<FAsyncTask<FOrExpressionByUserIdSpeculativeExecutor::FCommitTask>> FOrExpressionByUserIdSpeculativeExecutor::ExecuteRated(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, Rate, false);
    }

    Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr FOrExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr FOrExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }

    TSharedPtr<FAsyncTask<FOrExpressionByUserIdSpeculativeExecutor::FCommitTask>> FOrExpressionByUserIdSpeculativeExecutor::ExecuteInverseRated(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FOrExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, Rate, true);
    }
}
