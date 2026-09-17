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

#include "Formation/Domain/SpeculativeExecutor/Acquire/AddMoldCapacityByUserIdSpeculativeExecutor.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Formation/Domain/SpeculativeExecutor/MoldCapacityMutationSpeculativeCommit.h"
#include "Formation/Model/Cache/Mold.h"
#include "Formation/Model/Cache/MoldModel.h"

namespace Gs2::Formation::Domain::SpeculativeExecutor
{
using Private::FMoldCapacityMutationSpeculativeCommit;

FString FAddMoldCapacityByUserIdSpeculativeExecutor::Action()
{
    return FString("Gs2Formation:AddMoldCapacityByUserId");
}

Gs2::Core::Model::FGs2ErrorPtr FAddMoldCapacityByUserIdSpeculativeExecutor::Transform(
    const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
    const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr&, Gs2::Formation::Model::FMoldPtr
)
{
    return nullptr;
}

FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request
): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}

FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
    Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
)
{
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = MakeShared<Gs2::Formation::Request::FAddMoldCapacityByUserIdRequest>(*Request);
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() ||
        !Prepared->GetCapacity().IsSet()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
        Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString())) return nullptr;

    const auto NamespaceName = Prepared->GetNamespaceName();
    const auto MoldModelName = Prepared->GetMoldModelName();
    const auto UserId = Token->GetUserId();
    const auto TimeOffset = Token->GetTimeOffset();
    const FString ExpectedMoldId = FString::Printf(
        TEXT("grn:gs2:%s:%s:formation:%s:user:%s:mold:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
        *UserId.Get(FString()), *MoldModelName.Get(FString())
    );
    const FString ExpectedModelId = FString::Printf(
        TEXT("grn:gs2:%s:%s:formation:%s:model:mold:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
        *MoldModelName.Get(FString())
    );
    Gs2::Formation::Model::FMoldPtr Mold;
    if (!Gs2::Formation::Model::Cache::FMoldCache::TryGet(
        Domain->Cache, NamespaceName, UserId, MoldModelName, TimeOffset, &Mold
    ) || !Mold.IsValid() || !Mold->GetMoldId().IsSet() || Mold->GetMoldId().Get(FString()) != ExpectedMoldId ||
        !Mold->GetName().IsSet() || Mold->GetName().Get(FString()) != MoldModelName.Get(FString()) ||
        !Mold->GetUserId().IsSet() || Mold->GetUserId().Get(FString()) != UserId.Get(FString()) ||
        !Mold->GetCapacity().IsSet()) return nullptr;
    Gs2::Formation::Model::FMoldModelPtr Model;
    if (!Gs2::Formation::Model::Cache::FMoldModelCache::TryGet(
        Domain->Cache, NamespaceName, MoldModelName, TOptional<int32>(), &Model
    ) || !Model.IsValid() || !Model->GetMoldModelId().IsSet() || Model->GetMoldModelId().Get(FString()) != ExpectedModelId ||
        !Model->GetName().IsSet() || Model->GetName().Get(FString()) != MoldModelName.Get(FString()) ||
        !Model->GetMaxCapacity().IsSet()) return nullptr;
    const auto PreparedRevision = Mold->GetRevision();
    const int32 PreparedMaxCapacity = Model->GetMaxCapacity().Get(0);
    const int32 RequestedCapacity = Prepared->GetCapacity().Get(0);
    const auto Commit = MakeShared<FMoldCapacityMutationSpeculativeCommit>(
        Domain->Cache, NamespaceName, UserId.Get(FString()), MoldModelName.Get(FString()), TimeOffset,
        ExpectedMoldId, ExpectedModelId, PreparedRevision, PreparedMaxCapacity,
        [RequestedCapacity](const Gs2::Formation::Model::FMoldPtr& Current) -> Gs2::Formation::Model::FMoldPtr
        {
            if (!Current.IsValid() || !Current->GetCapacity().IsSet()) return Gs2::Formation::Model::FMoldPtr(nullptr);
            const int64 Value = static_cast<int64>(Current->GetCapacity().Get(0)) + static_cast<int64>(RequestedCapacity);
            if (Value > 2147483647 || Value < -2147483648) return Gs2::Formation::Model::FMoldPtr(nullptr);
            Gs2::Formation::Model::FMoldPtr Changed = MakeShared<Gs2::Formation::Model::FMold>(*Current);
            return Changed->WithCapacity(static_cast<int32>(Value));
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

TSharedPtr<FAsyncTask<FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask>> FAddMoldCapacityByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain,
    const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request
)
{
    return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
}

Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr FAddMoldCapacityByUserIdSpeculativeExecutor::Rate(
    const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request, const double
)
{ return Request; }

Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr FAddMoldCapacityByUserIdSpeculativeExecutor::Rate(
    const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request, TBigInt<1024, false>
)
{ return Request; }
}
