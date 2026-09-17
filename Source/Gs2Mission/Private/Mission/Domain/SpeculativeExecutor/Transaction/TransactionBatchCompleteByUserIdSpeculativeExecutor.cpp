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
#pragma warning (disable: 4458)
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow"
#endif

#include "Mission/Domain/SpeculativeExecutor/Transaction/BatchCompleteByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Model/VerifyAction.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/BatchReceiveByUserIdSpeculativeExecutor.h"
#include "Mission/Model/Cache/Complete.h"
#include "Mission/Model/Cache/MissionGroupModel.h"
#include "Mission/Model/Cache/MissionTaskModel.h"
#include "Mission/Model/MissionGroupModel.h"
#include "Mission/Model/MissionTaskModel.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Mission::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        using FCompletePtr = Gs2::Mission::Model::FCompletePtr;
        using FGroupPtr = Gs2::Mission::Model::FMissionGroupModelPtr;
        using FTaskPtr = Gs2::Mission::Model::FMissionTaskModelPtr;
        FString BatchExpectedCompleteId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const FString& GroupName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:user:%s:group:%s:complete"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *GroupName);
        }
        FString BatchExpectedTaskId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& GroupName, const FString& TaskName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:group:%s:missionTaskModel:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *GroupName, *TaskName);
        }
        FString BatchSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
        bool BatchExpectedComplete(const FCompletePtr& Item, const FString& ExpectedId, const FString& UserId, const FString& GroupName)
        {
            return Item.IsValid() && Item->GetCompleteId().IsSet() && Item->GetCompleteId().Get(FString()) == ExpectedId && Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId && Item->GetMissionGroupName().IsSet() && Item->GetMissionGroupName().Get(FString()) == GroupName;
        }
        bool BatchKnownReceiveFailure(const FCompletePtr& Complete, const TArray<FTaskPtr>& Models, const TArray<FString>& Names)
        {
            if (!Complete.IsValid() || !Complete->GetReceivedMissionTaskNames().IsValid()) return false;
            for (const auto& Name : Names) if (Complete->GetReceivedMissionTaskNames()->Contains(Name)) return true;
            for (const auto& Model : Models)
            {
                if (!Model.IsValid()) continue;
                const FString Type = Model->GetVerifyCompleteType().Get(FString());
                if (Type != TEXT("consumeActions") && Type != TEXT("verifyActions") && Complete->GetCompletedMissionTaskNames().IsValid() && !Complete->GetCompletedMissionTaskNames()->Contains(Model->GetName().Get(FString()))) return true;
            }
            return false;
        }
        bool HasBatchKnownReceiveFailure(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Auth::Model::FAccessTokenPtr& Token, const Gs2::Mission::Request::FBatchCompleteByUserIdRequestPtr& Request, const TArray<FTaskPtr>& Models, const TArray<FString>& Names)
        {
            if (!Domain.IsValid() || !Token.IsValid() || !Request.IsValid() || !Request->GetNamespaceName().IsSet() || !Request->GetMissionGroupName().IsSet()) return false;
            FCompletePtr Complete;
            if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(Domain->Cache, Request->GetNamespaceName(), Token->GetUserId(), Request->GetMissionGroupName(), Token->GetTimeOffset(), &Complete)) return false;
            const FString UserId = Token->GetUserId().Get(FString());
            const FString GroupName = Request->GetMissionGroupName().Get(FString());
            return BatchExpectedComplete(Complete, BatchExpectedCompleteId(Domain, Request->GetNamespaceName().Get(FString()), UserId, GroupName), UserId, GroupName) && BatchKnownReceiveFailure(Complete, Models, Names);
        }
        bool PrepareBatchVerifications(const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& Token, const TSharedPtr<TArray<Gs2::Core::Model::FVerifyActionPtr>>& Sources, const TSharedPtr<TArray<TSharedPtr<Gs2::Mission::Model::FConfig>>>& Config, Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray& Commits)
        {
            if (!Service.IsValid() || !Token.IsValid()) return false;
            if (!Sources.IsValid()) return true;
            for (const auto& Source : *Sources)
            {
                if (!Source.IsValid()) continue;
                Gs2::Core::Model::FVerifyActionPtr Action = MakeShared<Gs2::Core::Model::FVerifyAction>(*Source);
                if (Config.IsValid()) for (const auto& Entry : *Config) if (Entry.IsValid()) Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(Action, Entry->GetKey(), Entry->GetValue());
                if (!Action.IsValid()) continue;
                auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(Token, Action, TBigInt<1024, false>(1), false);
                Service->OnIssueTransaction.Broadcast(Event);
                if (Event->GetPreparedCommit().IsValid()) { Commits.Add(Event->GetPreparedCommit()); continue; }
                Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(Token, Action, TBigInt<1024, false>(1), true);
                Service->OnIssueTransaction.Broadcast(Event);
                if (Event->GetPreparedCommit().IsValid()) return false;
            }
            return true;
        }
        FString SerializeBatchReceiveRequest(const Gs2::Mission::Request::FBatchCompleteByUserIdRequestPtr& Request, const FString& UserId)
        {
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(MakeShared<Gs2::Mission::Request::FBatchReceiveByUserIdRequest>()->WithNamespaceName(Request->GetNamespaceName())->WithUserId(TOptional<FString>(UserId))->WithMissionGroupName(Request->GetMissionGroupName())->WithMissionTaskNames(Request->GetMissionTaskNames())->ToJson().ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FBatchCompleteByUserIdSpeculativeExecutor::Action() { return "Gs2Mission:BatchCompleteByUserId"; }
    FBatchCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FBatchCompleteByUserIdRequestPtr& Request): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
    FBatchCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From): Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

    Gs2::Core::Model::FGs2ErrorPtr FBatchCompleteByUserIdSpeculativeExecutor::FCommitTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        auto Prepared = Request.IsValid() ? Gs2::Mission::Request::FBatchCompleteByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() || !Service.IsValid() || !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty() || !Prepared->GetMissionTaskNames().IsValid()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetMissionGroupName().IsSet() || Prepared->GetMissionGroupName().Get(FString()).IsEmpty()) return nullptr;
        TArray<FString> Requested;
        for (const auto& Name : *Prepared->GetMissionTaskNames()) if (!Name.IsEmpty() && !Requested.Contains(Name)) Requested.Add(Name);
        if (Requested.Num() == 0) return nullptr;
        Gs2::Mission::Model::FMissionGroupModelPtr Group;
        if (!Gs2::Mission::Model::Cache::FMissionGroupModelCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), Prepared->GetMissionGroupName(), TOptional<int32>(), &Group) || !Group.IsValid() || !Group->GetMissionGroupId().IsSet() || !Group->GetName().IsSet()) return nullptr;
        const FString ExpectedGroupId = FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:group:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *Prepared->GetNamespaceName().Get(FString()), *Prepared->GetMissionGroupName().Get(FString()));
        if (Group->GetMissionGroupId().Get(FString()) != ExpectedGroupId || Group->GetName().Get(FString()) != Prepared->GetMissionGroupName().Get(FString()) || !Group->GetTasks().IsValid()) return nullptr;
        TArray<FTaskPtr> Ordered;
        for (const auto& Task : *Group->GetTasks())
        {
            if (!Task.IsValid() || !Task->GetName().IsSet() || !Requested.Contains(Task->GetName().Get(FString()))) continue;
            if (!Task->GetMissionTaskId().IsSet() || Task->GetMissionTaskId().Get(FString()) != BatchExpectedTaskId(Domain, Prepared->GetNamespaceName().Get(FString()), Prepared->GetMissionGroupName().Get(FString()), Task->GetName().Get(FString()))) return nullptr;
            Ordered.Add(Task);
            Requested.Remove(Task->GetName().Get(FString()));
        }
        if (Ordered.Num() == 0) return nullptr;
        auto OrderedNames = MakeShared<TArray<FString>>();
        for (const auto& Task : Ordered) OrderedNames->Add(Task->GetName().Get(FString()));
        Prepared->WithMissionTaskNames(OrderedNames);
        const FString GroupSnapshot = BatchSnapshot(Group->ToJson());
        TMap<FString, FString> ModelSnapshots;
        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        const auto VerifyActions = MakeShared<TArray<Gs2::Core::Model::FVerifyActionPtr>>();
        for (const auto& Model : Ordered)
        {
            FTaskPtr Direct;
            const bool Found = Gs2::Mission::Model::Cache::FMissionTaskModelCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), Prepared->GetMissionGroupName(), Model->GetName(), TOptional<int32>(), &Direct);
            const FString DirectSnapshot = Found && Direct.IsValid() ? BatchSnapshot(Direct->ToJson()) : FString();
            ModelSnapshots.Add(Model->GetName().Get(FString()), DirectSnapshot);
            if (Direct.IsValid() && DirectSnapshot != BatchSnapshot(Model->ToJson())) return nullptr;
            if (const auto Sources = Model->GetVerifyCompleteConsumeActions(); Sources.IsValid()) for (const auto& Source : *Sources) if (Source.IsValid()) VerifyActions->Add(Source);
            if (const auto Sources = Model->GetCompleteAcquireActions(); Sources.IsValid()) for (const auto& Source : *Sources)
            {
                if (!Source.IsValid()) continue;
                Gs2::Core::Model::FAcquireActionPtr Action = MakeShared<Gs2::Core::Model::FAcquireAction>(*Source);
                if (const auto Config = Prepared->GetConfig(); Config.IsValid()) for (const auto& Entry : *Config) if (Entry.IsValid()) Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(Action, Entry->GetKey(), Entry->GetValue());
                if (Action.IsValid()) AcquireActions->Add(Action);
            }
        }
        Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray Verifications;
        if (!PrepareBatchVerifications(Service, Token, VerifyActions, Prepared->GetConfig(), Verifications)) return nullptr;
        if (HasBatchKnownReceiveFailure(Domain, Token, Prepared, Ordered, *OrderedNames)) return nullptr;
        const auto ReceiveActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        ReceiveActions->Add(MakeShared<Gs2::Core::Model::FConsumeAction>()->WithAction(TOptional<FString>(Gs2::Mission::Domain::SpeculativeExecutor::FBatchReceiveByUserIdSpeculativeExecutor::Action()))->WithRequest(TOptional<FString>(SerializeBatchReceiveRequest(Prepared, Token->GetUserId().Get(FString())))));
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(Token, ReceiveActions, AcquireActions, TBigInt<1024, false>(1));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid()) return nullptr;
        const auto Verification = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::BuildAtomicVerificationPreparedCommit(MakeShared<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray>(Verifications), Verifications.Num());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([Commit, Verification]() { if (Verification.IsValid()) Verification->InvokeLegacy(); (*Commit)(); }), [DomainCopy = Domain, Prepared, GroupSnapshot, ModelSnapshots, Ordered, OrderedNames, Token, Verification]() -> bool
        {
            FGroupPtr CurrentGroup;
            if (!Gs2::Mission::Model::Cache::FMissionGroupModelCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), Prepared->GetMissionGroupName(), TOptional<int32>(), &CurrentGroup) || !CurrentGroup.IsValid() || BatchSnapshot(CurrentGroup->ToJson()) != GroupSnapshot) return false;
            for (const auto& Pair : ModelSnapshots)
            {
                FTaskPtr Current;
                const bool Found = Gs2::Mission::Model::Cache::FMissionTaskModelCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), Prepared->GetMissionGroupName(), TOptional<FString>(Pair.Key), TOptional<int32>(), &Current);
                if (Found && Current.IsValid() && BatchSnapshot(Current->ToJson()) != Pair.Value) return false;
                if (!Found && !Pair.Value.IsEmpty()) return false;
            }
            return !HasBatchKnownReceiveFailure(DomainCopy, Token, Prepared, Ordered, *OrderedNames) && (!Verification.IsValid() || Verification->IsStillSatisfied());
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBatchCompleteByUserIdSpeculativeExecutor::FCommitTask>> FBatchCompleteByUserIdSpeculativeExecutor::Execute(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FBatchCompleteByUserIdRequestPtr& Request) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
