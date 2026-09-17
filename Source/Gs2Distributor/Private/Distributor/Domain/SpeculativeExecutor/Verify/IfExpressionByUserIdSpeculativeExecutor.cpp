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

#include "Distributor/Domain/SpeculativeExecutor/Verify/IfExpressionByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Distributor/Domain/Gs2Distributor.h"

namespace Gs2::Distributor::Domain::SpeculativeExecutor
{
namespace
{
    Gs2::Auth::Model::FAccessTokenPtr PrepareIfExpressionAccessToken(
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken
    )
    {
        Gs2::Auth::Model::FAccessTokenPtr Prepared = nullptr;
        if (AccessToken.IsValid()) Prepared = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        return Prepared;
    }

    Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr PrepareIfExpressionRequest(
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        const auto Prepared = MakeShared<Gs2::Distributor::Request::FIfExpressionByUserIdRequest>(*Request);
        if (const auto Condition = Request->GetCondition(); Condition.IsValid())
        {
            Prepared->WithCondition(MakeShared<Gs2::Core::Model::FVerifyAction>(*Condition));
        }
        const auto CloneActions = [](const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& Actions)
            -> TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>
        {
            if (!Actions.IsValid()) return nullptr;
            const auto PreparedActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
            for (const auto& Action : *Actions)
            {
                Gs2::Core::Model::FConsumeActionPtr PreparedAction = nullptr;
                if (Action.IsValid()) PreparedAction = MakeShared<Gs2::Core::Model::FConsumeAction>(*Action);
                PreparedActions->Add(PreparedAction);
            }
            return PreparedActions;
        };
        if (Request->GetTrueActions().IsValid())
            Prepared->WithTrueActions(CloneActions(Request->GetTrueActions()));
        if (Request->GetFalseActions().IsValid())
            Prepared->WithFalseActions(CloneActions(Request->GetFalseActions()));
        return Prepared;
    }

    bool IfExpressionUserIdMatches(
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
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

    Gs2::Core::Model::FGs2ErrorPtr DispatchIfExpressionVerify(
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

    TSharedPtr<TFunction<void()>> DispatchIfExpressionConsume(
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>>& Actions,
        const TBigInt<1024, false>& Rate,
        Gs2::Core::Model::FGs2ErrorPtr& Error
    )
    {
        if (!Service.IsValid() || !Actions.IsValid()) return nullptr;
        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            AccessToken, Actions, AcquireActions, Rate);
        Service->OnIssueTransaction.Broadcast(Event);
        Error = Event->GetError();
        return Event->GetCommit();
    }
}

    FString FIfExpressionByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Distributor:IfExpressionByUserId");
    }

    FIfExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
        const TBigInt<1024, false>& Rate
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request),
        Rate(Rate)
    {

    }

    FIfExpressionByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request),
        Rate(From.Rate)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIfExpressionByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto PreparedRequest = PrepareIfExpressionRequest(Request);
        const auto PreparedAccessToken = PrepareIfExpressionAccessToken(AccessToken);
        if (PreparedRequest.IsValid() && PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().GetValue() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        }
        if (!PreparedRequest.IsValid() || !IfExpressionUserIdMatches(PreparedRequest, PreparedAccessToken) ||
            !PreparedRequest->GetCondition().IsValid())
        {
            return nullptr;
        }

        Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr ConditionCommit;
        const auto ConditionError = DispatchIfExpressionVerify(
            Service, PreparedAccessToken, PreparedRequest->GetCondition(), Rate, false, &ConditionCommit);
        TSharedPtr<TArray<Gs2::Core::Model::FConsumeActionPtr>> SelectedActions;
        if (ConditionError.IsValid())
        {
            const auto InverseError = DispatchIfExpressionVerify(
                Service, PreparedAccessToken, PreparedRequest->GetCondition(), Rate, true, &ConditionCommit);
            if (InverseError.IsValid() || !ConditionCommit.IsValid()) return nullptr;
            SelectedActions = PreparedRequest->GetFalseActions();
        }
        else
        {
            if (!ConditionCommit.IsValid()) return nullptr;
            SelectedActions = PreparedRequest->GetTrueActions();
        }
        if (!ConditionCommit->IsGuarded() || !SelectedActions.IsValid()) return nullptr;

        Gs2::Core::Model::FGs2ErrorPtr BranchError;
        const auto BranchCommit = DispatchIfExpressionConsume(
            Service, PreparedAccessToken, SelectedActions, Rate, BranchError);
        if (BranchError.IsValid() || !BranchCommit.IsValid()) return BranchError;
        const auto BranchPrepared = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(BranchCommit);
        if (!BranchPrepared.IsValid()) return nullptr;
        const auto PreparedCondition = ConditionCommit;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([PreparedCondition, BranchPrepared]()
            {
                if (!PreparedCondition->IsStillSatisfied()) return;
                PreparedCondition->InvokeLegacy();
                BranchPrepared->InvokeLegacy();
            }),
            [PreparedCondition]()
            {
                return PreparedCondition->IsStillSatisfied();
            });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIfExpressionByUserIdSpeculativeExecutor::FCommitTask>> FIfExpressionByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(
            Domain, Service, AccessToken, Request, TBigInt<1024, false>(1));
    }

    TSharedPtr<FAsyncTask<FIfExpressionByUserIdSpeculativeExecutor::FCommitTask>> FIfExpressionByUserIdSpeculativeExecutor::ExecuteRated(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request, Rate);
    }

    Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr FIfExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr FIfExpressionByUserIdSpeculativeExecutor::Rate(
        const Gs2::Distributor::Request::FIfExpressionByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
