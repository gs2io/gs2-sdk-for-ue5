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

#include "Guild/Domain/SpeculativeExecutor/Acquire/SetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Guild/Domain/SpeculativeExecutor/GuildMaximumMemberCountMutationSpeculativeCommit.h"
#include "Guild/Model/Cache/Guild.h"
#include "Guild/Model/Cache/GuildModel.h"

namespace Gs2::Guild::Domain::SpeculativeExecutor
{
using Private::FGuildMaximumMemberCountMutationSpeculativeCommit;

FString FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Action() { return FString("Gs2Guild:SetMaximumCurrentMaximumMemberCountByGuildName"); }
Gs2::Core::Model::FGs2ErrorPtr FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr&, Gs2::Guild::Model::FGuildPtr
) { return nullptr; }

FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Prepared->GetValue().IsSet()) return nullptr;
    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto GuildModelName = Prepared->GetGuildModelName();
    const auto GuildName = Prepared->GetGuildName();
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedGuildId = FString::Printf(
        TEXT("grn:gs2:%s:%s:guild:%s:guild:%s:%s"), *Domain->RestSession->RegionName(),
        *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *GuildModelName.Get(FString()), *GuildName.Get(FString())
    );
    const FString ExpectedModelId = FString::Printf(
        TEXT("grn:gs2:%s:%s:guild:%s:model:%s"), *Domain->RestSession->RegionName(),
        *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()), *GuildModelName.Get(FString())
    );
    Gs2::Guild::Model::FGuildPtr Guild;
    if (!Gs2::Guild::Model::Cache::FGuildCache::TryGet(
        Domain->Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, &Guild
    ) || !Guild.IsValid() || !Guild->GetGuildId().IsSet() || Guild->GetGuildId().Get(FString()) != ExpectedGuildId ||
        Guild->GetGuildModelName() != GuildModelName || Guild->GetName() != GuildName ||
        !Guild->GetMembers().IsValid()) return nullptr;
    Gs2::Guild::Model::FGuildModelPtr Model;
    if (!Gs2::Guild::Model::Cache::FGuildModelCache::TryGet(
        Domain->Cache, NamespaceName, GuildModelName, TOptional<int32>(), &Model
    ) || !Model.IsValid() || !Model->GetGuildModelId().IsSet() || Model->GetGuildModelId().Get(FString()) != ExpectedModelId ||
        Model->GetName() != GuildModelName) return nullptr;
    const auto PreparedRevision = Guild->GetRevision();
    const int32 RequestedValue = Prepared->GetValue().Get(0);
    const auto Commit = MakeShared<FGuildMaximumMemberCountMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, GuildModelName, GuildName, TimeOffset,
        ExpectedGuildId, ExpectedModelId, PreparedRevision, true,
        [RequestedValue](const Gs2::Guild::Model::FGuildPtr& Current, const int32 Maximum) -> Gs2::Guild::Model::FGuildPtr
        {
            if (!Current.IsValid() || !Current->GetMembers().IsValid()) return Gs2::Guild::Model::FGuildPtr(nullptr);
            int64 Value = RequestedValue;
            if (Value > Maximum) Value = Maximum;
            if (Value < Current->GetMembers()->Num()) Value = Current->GetMembers()->Num();
            if (Value > 2147483647 || Value < -2147483648) return Gs2::Guild::Model::FGuildPtr(nullptr);
            Gs2::Guild::Model::FGuildPtr Changed = MakeShared<Gs2::Guild::Model::FGuild>(*Current);
            return Changed->WithCurrentMaximumMemberCount(static_cast<int32>(Value));
        }
    );
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
        Commit->CompositionKey(),
        [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
        { return Commit->TryCompose(Current, HasCurrent, Next); },
        [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); }
    );
    return nullptr;
}

TSharedPtr<FAsyncTask<FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask>> FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr& Request
) { return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }
Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Rate(
    const Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr& Request, const double
) { return Request; }
Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr FSetMaximumCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Rate(
    const Gs2::Guild::Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr& Request, TBigInt<1024, false>
) { return Request; }
}
