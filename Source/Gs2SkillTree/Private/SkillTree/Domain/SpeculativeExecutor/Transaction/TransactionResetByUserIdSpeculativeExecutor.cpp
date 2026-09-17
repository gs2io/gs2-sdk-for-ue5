/*
 * Copyright 2016 Game Server Services, Inc. or its affiliates. All Rights
 * Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 * or in the "license" file accompanying this file.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * deny overwrite
 */

#include "SkillTree/Domain/SpeculativeExecutor/Transaction/ResetByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "SkillTree/Domain/SpeculativeExecutor/StatusSpeculativeCommit.h"

namespace Gs2::SkillTree::Domain::Transaction::SpeculativeExecutor
{
using FStatusSpeculativeCommit = Gs2::SkillTree::Domain::SpeculativeExecutor::Private::FStatusSpeculativeCommit;

FString FResetByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2SkillTree:ResetByUserId");
}

FResetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::SkillTree::Request::FResetByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FResetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FResetByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::SkillTree::Request::FResetByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::SkillTree::Request::FResetByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    const auto UserId = Token->GetUserId();
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != UserId.Get(FString())) return nullptr;
    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto PropertyId = Prepared->GetPropertyId();
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:skillTree:%s:user:%s:status:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
        *UserId.Get(FString()), *PropertyId.Get(FString()));
    Gs2::SkillTree::Model::FStatusPtr Cached;
    if (!Gs2::SkillTree::Model::Cache::FStatusCache::TryGet(
            Domain->Cache, NamespaceName, UserId, PropertyId, TimeOffset, &Cached) ||
        !Cached.IsValid() || !Cached->GetStatusId().IsSet() || Cached->GetStatusId().Get(FString()) != ExpectedId ||
        !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId.Get(FString()) ||
        !Cached->GetPropertyId().IsSet() || Cached->GetPropertyId().Get(FString()) != PropertyId.Get(FString()) ||
        !Cached->GetReleasedNodeNames().IsValid()) return nullptr;

    const auto Commit = FStatusSpeculativeCommit::Create(
        Domain->Cache, NamespaceName, UserId.Get(FString()), PropertyId.Get(FString()), TimeOffset, ExpectedId, true,
        [](const Gs2::SkillTree::Model::FStatusPtr& Source)
        {
            if (!Source.IsValid() || !Source->GetReleasedNodeNames().IsValid()) return Gs2::SkillTree::Model::FStatusPtr();
            return MakeShared<Gs2::SkillTree::Model::FStatus>(*Source)
                ->WithReleasedNodeNames(MakeShared<TArray<FString>>())->WithRevision(0);
        });
    if (!Commit.IsValid() || !Commit->CanPrepare()) return nullptr;
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); });
    return nullptr;
}

TSharedPtr<FAsyncTask<FResetByUserIdSpeculativeExecutor::FCommitTask>> FResetByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::SkillTree::Request::FResetByUserIdRequestPtr& Request)
{ return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }
}
