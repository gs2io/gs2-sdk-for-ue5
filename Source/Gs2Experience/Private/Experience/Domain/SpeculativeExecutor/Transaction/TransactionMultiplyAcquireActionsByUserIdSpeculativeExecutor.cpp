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
#include "Experience/Domain/SpeculativeExecutor/Transaction/MultiplyAcquireActionsByUserIdSpeculativeExecutor.h"
#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Experience/Model/Cache/ExperienceModel.h"
#include "Experience/Model/Cache/Status.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Experience::Domain::Transaction::SpeculativeExecutor {
namespace {
FString ExpSnapshot(const Gs2::Experience::Model::FExperienceModelPtr& Item) {
    if (!Item.IsValid()) return FString();
    FString Body; const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
    FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer); return Body;
}
FString ExpStatusSnapshot(const Gs2::Experience::Model::FStatusPtr& Item) {
    if (!Item.IsValid()) return FString();
    FString Body; const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
    FJsonSerializer::Serialize(Item->ToJson().ToSharedRef(), Writer); return Body;
}
bool ExpUnitRate(const Gs2::Experience::Model::FAcquireActionRatePtr& Def, int32 Index) {
    if (!Def.IsValid() || Index < 0 || !Def->GetMode().IsSet()) return false;
    if (*Def->GetMode() == TEXT("double"))
        return Def->GetRates().IsValid() && Def->GetRates()->IsValidIndex(Index) && (*Def->GetRates())[Index] == 1.0;
    return *Def->GetMode() == TEXT("big") && Def->GetBigRates().IsValid() &&
        Def->GetBigRates()->IsValidIndex(Index) && (*Def->GetBigRates())[Index] == TEXT("1");
}
}
FString FMultiplyAcquireActionsByUserIdSpeculativeExecutor::Action() { return TEXT("Gs2Experience:MultiplyAcquireActionsByUserId"); }
FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
    const Gs2::Experience::Request::FMultiplyAcquireActionsByUserIdRequestPtr& Request)
    : Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From)
    : Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

Gs2::Core::Model::FGs2ErrorPtr FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask::Action(
    TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result) {
    *Result = nullptr;
    Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
    if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
    Gs2::Experience::Request::FMultiplyAcquireActionsByUserIdRequestPtr Prepared = nullptr;
    if (Request.IsValid()) Prepared = Gs2::Experience::Request::FMultiplyAcquireActionsByUserIdRequest::FromJson(Request->ToJson());
    if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
        !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
    if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
    if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
        !Prepared->GetNamespaceName().IsSet() || !Prepared->GetExperienceName().IsSet() || !Prepared->GetPropertyId().IsSet() ||
        !Prepared->GetRateName().IsSet() || !Prepared->GetAcquireActions().IsValid()) return nullptr;
    auto PropertyId = Prepared->GetPropertyId();
    PropertyId = TOptional<FString>(PropertyId.Get(FString()).Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
        .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId()).Replace(TEXT("{userId}"), *Token->GetUserId().Get(FString())));
    Prepared->WithPropertyId(PropertyId);
    const auto Namespace = Prepared->GetNamespaceName(); const auto Name = Prepared->GetExperienceName();
    const auto UserId = Token->GetUserId(); const auto Offset = Token->GetTimeOffset();
    const FString ModelId = FString::Printf(
        TEXT("grn:gs2:%s:%s:experience:%s:model:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
        *Namespace.Get(FString()), *Name.Get(FString())
    );
    const FString StatusId = FString::Printf(
        TEXT("grn:gs2:%s:%s:experience:%s:user:%s:experienceModel:%s:property:%s"),
        *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
        *Namespace.Get(FString()), *UserId.Get(FString()),
        *Name.Get(FString()), *PropertyId.Get(FString())
    );
    Gs2::Experience::Model::FExperienceModelPtr Model = nullptr; Gs2::Experience::Model::FStatusPtr Status = nullptr;
    if (!Gs2::Experience::Model::Cache::FExperienceModelCache::TryGet(Domain->Cache, Namespace, Name, TOptional<int32>(), &Model) ||
        !Gs2::Experience::Model::Cache::FStatusCache::TryGet(Domain->Cache, Namespace, UserId, Name, PropertyId, Offset, &Status) ||
        !Model.IsValid() || !Status.IsValid() || !Model->GetExperienceModelId().IsSet() || *Model->GetExperienceModelId() != ModelId ||
        !Model->GetName().IsSet() || *Model->GetName() != Name.Get(FString()) || !Status->GetStatusId().IsSet() || *Status->GetStatusId() != StatusId ||
        !Status->GetUserId().IsSet() ||
        *Status->GetUserId() != UserId.Get(FString()) ||
        !Status->GetExperienceName().IsSet() ||
        *Status->GetExperienceName() != Name.Get(FString()) ||
        !Status->GetPropertyId().IsSet() || *Status->GetPropertyId() != PropertyId.Get(FString()) || !Status->GetRankValue().IsSet() ||
        *Status->GetRankValue() <= 0 || *Status->GetRankValue() > MAX_int32) return nullptr;
    Gs2::Experience::Model::FAcquireActionRatePtr Rate = nullptr;
    if (Model->GetAcquireActionRates().IsValid()) for (const auto& Candidate : *Model->GetAcquireActionRates())
        if (Candidate.IsValid() && Candidate->GetName().IsSet() && *Candidate->GetName() == Prepared->GetRateName().Get(FString())) { Rate = Candidate; break; }
    if (!ExpUnitRate(Rate, static_cast<int32>(*Status->GetRankValue()) - 1) ||
        Prepared->GetBaseRate().Get(1.0f) != 1.0f) return nullptr;
    const auto Consumes = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
    const auto Acquires = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
    for (const auto& Source : *Prepared->GetAcquireActions()) if (Source.IsValid()) {
        Gs2::Core::Model::FAcquireActionPtr SourceAction =
            MakeShared<Gs2::Core::Model::FAcquireAction>(*Source);
        const auto Action =
            Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                SourceAction, TOptional<FString>(TEXT("userId")), UserId
            );
        if (Action.IsValid()) Acquires->Add(Action);
    }
    if (Acquires->Num() == 0) return nullptr;
    const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
        Token, Consumes, Acquires, TBigInt<1024, false>(1)
    );
    Service->OnIssueTransaction.Broadcast(Event);
    if (Event->GetError().IsValid()) return Event->GetError();
    const auto Child = Event->GetCommit(); if (!Child.IsValid()) return nullptr;
    const FString ExpectedModel = ExpSnapshot(Model); const FString ExpectedStatus = ExpStatusSnapshot(Status);
    *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
        MakeShared<TFunction<void()>>([Child] { (*Child)(); }),
        [Domain = Domain, Namespace, Name, UserId, PropertyId, Offset, ExpectedModel, ExpectedStatus] {
            Gs2::Experience::Model::FExperienceModelPtr CurrentModel = nullptr; Gs2::Experience::Model::FStatusPtr CurrentStatus = nullptr;
            return Gs2::Experience::Model::Cache::FExperienceModelCache::TryGet(Domain->Cache, Namespace, Name, TOptional<int32>(), &CurrentModel) &&
                Gs2::Experience::Model::Cache::FStatusCache::TryGet(Domain->Cache, Namespace, UserId, Name, PropertyId, Offset, &CurrentStatus) &&
                ExpSnapshot(CurrentModel) == ExpectedModel && ExpStatusSnapshot(CurrentStatus) == ExpectedStatus;
        });
    return nullptr;
}
TSharedPtr<FAsyncTask<FMultiplyAcquireActionsByUserIdSpeculativeExecutor::FCommitTask>> FMultiplyAcquireActionsByUserIdSpeculativeExecutor::Execute(
    const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
    const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Experience::Request::FMultiplyAcquireActionsByUserIdRequestPtr& Request)
{ return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }
}
