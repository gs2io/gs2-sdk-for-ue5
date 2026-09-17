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

#include "SkillTree/Domain/SpeculativeExecutor/Consume/MarkRestrainByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "SkillTree/Domain/SpeculativeExecutor/StatusSpeculativeCommit.h"

namespace Gs2::SkillTree::Domain::SpeculativeExecutor
{
using Private::FStatusSpeculativeCommit;

FString FMarkRestrainByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2SkillTree:MarkRestrainByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FMarkRestrainByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr&,
    Gs2::SkillTree::Model::FStatusPtr
)
{
    return nullptr;
}

FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::SkillTree::Request::FMarkRestrainByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
        !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() ||
        Token->GetUserId().Get(FString()).IsEmpty() || !Prepared->GetNodeModelNames().IsValid() ||
        Prepared->GetNodeModelNames()->Num() == 0) return nullptr;
    Prepared->WithNodeModelNames(MakeShared<TArray<FString>>(*Prepared->GetNodeModelNames()));
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    const auto UserId = Token->GetUserId();
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != UserId.Get(FString())) return nullptr;
    const auto NamespaceName = Prepared->GetNamespaceName();
    auto PropertyId = Prepared->GetPropertyId();
    if (PropertyId.IsSet())
    {
        PropertyId = TOptional<FString>(PropertyId.Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *UserId.Get(FString())));
        Prepared->WithPropertyId(PropertyId);
    }
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:skillTree:%s:user:%s:status:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
        *UserId.Get(FString()), *PropertyId.Get(FString()));
    const auto RequestedNames = MakeShared<TArray<FString>>(*Prepared->GetNodeModelNames());
    const auto Commit = FStatusSpeculativeCommit::Create(
        Domain->Cache, NamespaceName, UserId.Get(FString()), PropertyId.Get(FString()), TimeOffset, ExpectedId, true,
        [RequestedNames](const Gs2::SkillTree::Model::FStatusPtr& Source)
        {
            if (!Source.IsValid() || !Source->GetReleasedNodeNames().IsValid()) return Gs2::SkillTree::Model::FStatusPtr();
            const auto Existing = Source->GetReleasedNodeNames();
            const auto Seen = MakeShared<TArray<FString>>();
            for (const auto& Requested : *RequestedNames)
            {
                if (Seen->Contains(Requested) || !Existing->Contains(Requested)) return Gs2::SkillTree::Model::FStatusPtr();
                Seen->Add(Requested);
            }
            const auto Names = MakeShared<TArray<FString>>();
            for (const auto& ExistingName : *Existing)
            {
                if (!RequestedNames->Contains(ExistingName)) Names->Add(ExistingName);
            }
            return MakeShared<Gs2::SkillTree::Model::FStatus>(*Source)->WithReleasedNodeNames(Names)->WithRevision(0);
        });
    if (!Commit.IsValid() || !Commit->CanPrepare()) return nullptr;
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); });
    return nullptr;
}

TSharedPtr<FAsyncTask<FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask>> FMarkRestrainByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request)
{ return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }

Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr FMarkRestrainByUserIdSpeculativeExecutor::Rate(
    const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request, const double)
{ return Request; }

Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr FMarkRestrainByUserIdSpeculativeExecutor::Rate(
    const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request, TBigInt<1024, false>)
{ return Request; }
}
