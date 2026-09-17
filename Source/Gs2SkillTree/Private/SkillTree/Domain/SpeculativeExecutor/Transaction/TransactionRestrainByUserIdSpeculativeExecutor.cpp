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
#include "SkillTree/Domain/SpeculativeExecutor/Transaction/RestrainByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "SkillTree/Domain/SpeculativeExecutor/Consume/MarkRestrainByUserIdSpeculativeExecutor.h"
#include "SkillTree/Model/Cache/NodeModel.h"
#include "SkillTree/Model/Config.h"
#include "SkillTree/Model/NodeModel.h"

namespace Gs2::SkillTree::Domain::Transaction::SpeculativeExecutor
{
    FString FRestrainByUserIdSpeculativeExecutor::Action()
    {
        return TEXT("Gs2SkillTree:RestrainByUserId");
    }

    FRestrainByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FRestrainByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FRestrainByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr
    FRestrainByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid())
        {
            Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        }
        Gs2::SkillTree::Request::FRestrainByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid())
        {
            Prepared =
                Gs2::SkillTree::Request::FRestrainByUserIdRequest::FromJson(
                    Request->ToJson()
                );
        }
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !Domain->Cache.IsValid() || !Token.IsValid() ||
            !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
            Token->GetUserId().Get(FString()).IsEmpty() ||
            !Prepared->GetNodeModelNames().IsValid())
        {
            return nullptr;
        }

        if (Prepared->GetUserId().IsSet() &&
            Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            Prepared->WithUserId(Token->GetUserId());
        }
        if (!Prepared->GetUserId().IsSet() ||
            Prepared->GetUserId().Get(FString()) !=
                Token->GetUserId().Get(FString()))
        {
            return nullptr;
        }

        const auto Namespace = Prepared->GetNamespaceName();
        const auto UserId = Token->GetUserId();
        const auto Property = Prepared->GetPropertyId();
        const auto ChildRequest =
            MakeShared<Gs2::SkillTree::Request::FMarkRestrainByUserIdRequest>()
                ->WithNamespaceName(Namespace)
                ->WithUserId(UserId)
                ->WithPropertyId(Property)
                ->WithNodeModelNames(
                    MakeShared<TArray<FString>>(
                        *Prepared->GetNodeModelNames()
                    )
                );
        const auto MarkFuture =
            Gs2::SkillTree::Domain::SpeculativeExecutor::
                FMarkRestrainByUserIdSpeculativeExecutor::Execute(
                    Domain, Service, Token, ChildRequest
                );
        MarkFuture->StartSynchronousTask();
        if (MarkFuture->GetTask().IsError())
        {
            return MarkFuture->GetTask().Error();
        }

        const auto Commits = MakeShared<
            Gs2::Core::Domain::SpeculativeExecutor::
                FPreparedSpeculativeCommit::FPreparedCommitArray
        >();
        const auto Consumes =
            MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        const auto Acquires =
            MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        for (const auto& NodeName : *Prepared->GetNodeModelNames())
        {
            Gs2::SkillTree::Model::FNodeModelPtr Model = nullptr;
            const FString ExpectedId = FString::Printf(
                TEXT("grn:gs2:%s:%s:skillTree:%s:model:%s"),
                *Domain->RestSession->RegionName(),
                *Domain->RestSession->OwnerId(),
                *Namespace.Get(FString()),
                *NodeName
            );
            if (!Gs2::SkillTree::Model::Cache::FNodeModelCache::TryGet(
                    Domain->Cache, Namespace, TOptional<FString>(NodeName),
                    TOptional<int32>(), &Model
                ) ||
                !Model.IsValid() || !Model->GetNodeModelId().IsSet() ||
                *Model->GetNodeModelId() != ExpectedId ||
                !Model->GetName().IsSet() ||
                *Model->GetName() != NodeName ||
                !Model->GetReturnAcquireActions().IsValid())
            {
                continue;
            }
            for (const auto& Source : *Model->GetReturnAcquireActions())
            {
                if (!Source.IsValid()) continue;
                Gs2::Core::Model::FAcquireActionPtr Action =
                    MakeShared<Gs2::Core::Model::FAcquireAction>(*Source);
                if (Prepared->GetConfig().IsValid())
                {
                    for (const auto& Config : *Prepared->GetConfig())
                    {
                        if (Config.IsValid())
                        {
                            Action =
                                Gs2::Core::Domain::SpeculativeExecutor::
                                    ApplyConfig(
                                        Action, Config->GetKey(),
                                        Config->GetValue()
                                    );
                        }
                    }
                }
                if (Action.IsValid()) Acquires->Add(Action);
            }
        }
        if (Acquires->Num() > 0)
        {
            const auto Event =
                MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
                    Token, Consumes, Acquires, TBigInt<1024, false>(1)
                );
            Service->OnIssueTransaction.Broadcast(Event);
            if (Event->GetError().IsValid()) return Event->GetError();
            const auto Commit = Event->GetCommit();
            if (Commit.IsValid())
            {
                Commits->Add(
                    Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(
                        Commit
                    )
                );
            }
        }

        const auto Mark = MarkFuture->GetTask().Result();
        if (Mark.IsValid()) Commits->Insert(Mark, 0);
        const auto Atomic =
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::
                BuildAtomicCommit(Commits, 2);
        if (!Atomic.IsValid()) return nullptr;
        *Result =
            Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::
                WrapLegacy(Atomic);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<
        FRestrainByUserIdSpeculativeExecutor::FCommitTask>>
    FRestrainByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FRestrainByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(
            Domain, Service, AccessToken, Request
        );
    }
}
