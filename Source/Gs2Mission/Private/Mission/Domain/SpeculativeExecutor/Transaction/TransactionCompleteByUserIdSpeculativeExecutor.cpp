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

#include "Mission/Domain/SpeculativeExecutor/Transaction/CompleteByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Model/ConsumeAction.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/ReceiveByUserIdSpeculativeExecutor.h"
#include "Mission/Model/Cache/Complete.h"
#include "Mission/Model/Cache/MissionTaskModel.h"
#include "Mission/Model/MissionTaskModel.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Mission::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        using FCompletePtr = Gs2::Mission::Model::FCompletePtr;
        using FMissionTaskModelPtr = Gs2::Mission::Model::FMissionTaskModelPtr;

        FString CompleteExpectedId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const FString& GroupName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:user:%s:group:%s:complete"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *GroupName);
        }
        FString CompleteTaskExpectedId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& GroupName, const FString& TaskName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:group:%s:missionTaskModel:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *GroupName, *TaskName);
        }
        FString CompleteSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
        bool IsExpectedComplete(const FCompletePtr& Item, const FString& ExpectedId, const FString& UserId, const FString& GroupName)
        {
            return Item.IsValid() && Item->GetCompleteId().IsSet() && Item->GetCompleteId().Get(FString()) == ExpectedId && Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId && Item->GetMissionGroupName().IsSet() && Item->GetMissionGroupName().Get(FString()) == GroupName;
        }
        bool IsKnownReceiveFailure(const FCompletePtr& Complete, const FMissionTaskModelPtr& Model, const FString& MissionTaskName)
        {
            if (!Complete.IsValid() || !Complete->GetReceivedMissionTaskNames().IsValid()) return false;
            if (Complete->GetReceivedMissionTaskNames()->Contains(MissionTaskName)) return true;
            const FString Type = Model.IsValid() ? Model->GetVerifyCompleteType().Get(FString()) : FString();
            if (Type == TEXT("consumeActions") || Type == TEXT("verifyActions")) return false;
            return Complete->GetCompletedMissionTaskNames().IsValid() && !Complete->GetCompletedMissionTaskNames()->Contains(MissionTaskName);
        }
        bool HasKnownReceiveFailure(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Auth::Model::FAccessTokenPtr& Token, const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request, const FMissionTaskModelPtr& Model)
        {
            if (!Domain.IsValid() || !Token.IsValid() || !Request.IsValid() || !Token->GetUserId().IsSet() || !Request->GetNamespaceName().IsSet() || !Request->GetMissionGroupName().IsSet() || !Request->GetMissionTaskName().IsSet()) return false;
            FCompletePtr Complete;
            if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(Domain->Cache, Request->GetNamespaceName(), Token->GetUserId(), Request->GetMissionGroupName(), Token->GetTimeOffset(), &Complete)) return false;
            const FString UserId = Token->GetUserId().Get(FString());
            const FString GroupName = Request->GetMissionGroupName().Get(FString());
            return IsExpectedComplete(Complete, CompleteExpectedId(Domain, Request->GetNamespaceName().Get(FString()), UserId, GroupName), UserId, GroupName) && IsKnownReceiveFailure(Complete, Model, Request->GetMissionTaskName().Get(FString()));
        }
        bool IsPreparedModelCurrent(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request, const FString& ExpectedId, const FString& PreparedSnapshot)
        {
            if (!Domain.IsValid() || !Request.IsValid()) return false;
            FMissionTaskModelPtr Current;
            if (!Gs2::Mission::Model::Cache::FMissionTaskModelCache::TryGet(Domain->Cache, Request->GetNamespaceName(), Request->GetMissionGroupName(), Request->GetMissionTaskName(), TOptional<int32>(), &Current) || !Current.IsValid()) return false;
            return Current->GetMissionTaskId().IsSet() && Current->GetName().IsSet() && Current->GetMissionTaskId().Get(FString()) == ExpectedId && Current->GetName().Get(FString()) == Request->GetMissionTaskName().Get(FString()) && CompleteSnapshot(Current->ToJson()) == PreparedSnapshot;
        }
        bool PrepareCompleteVerifications(const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& Token, const TSharedPtr<TArray<Gs2::Core::Model::FVerifyActionPtr>>& Sources, const TSharedPtr<TArray<TSharedPtr<Gs2::Mission::Model::FConfig>>>& Config, Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray& Commits)
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
        FString SerializeCompleteReceiveRequest(const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request, const FString& UserId)
        {
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(MakeShared<Gs2::Mission::Request::FReceiveByUserIdRequest>()->WithNamespaceName(Request->GetNamespaceName())->WithUserId(TOptional<FString>(UserId))->WithMissionGroupName(Request->GetMissionGroupName())->WithMissionTaskName(Request->GetMissionTaskName())->ToJson().ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FCompleteByUserIdSpeculativeExecutor::Action() { return "Gs2Mission:CompleteByUserId"; }

    FCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
    FCompleteByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From): Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

    Gs2::Core::Model::FGs2ErrorPtr FCompleteByUserIdSpeculativeExecutor::FCommitTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        auto Prepared = Request.IsValid() ? Gs2::Mission::Request::FCompleteByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() || !Service.IsValid() || !Token.IsValid() || !Prepared.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetMissionGroupName().IsSet() || Prepared->GetMissionGroupName().Get(FString()).IsEmpty() || !Prepared->GetMissionTaskName().IsSet() || Prepared->GetMissionTaskName().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const auto GroupName = Prepared->GetMissionGroupName();
        const auto TaskName = Prepared->GetMissionTaskName();
        const auto UserId = Token->GetUserId();
        FMissionTaskModelPtr Model;
        if (!Gs2::Mission::Model::Cache::FMissionTaskModelCache::TryGet(Domain->Cache, NamespaceName, GroupName, TaskName, TOptional<int32>(), &Model) || !Model.IsValid() || !Model->GetMissionTaskId().IsSet() || !Model->GetName().IsSet()) return nullptr;
        const FString ExpectedModelId = CompleteTaskExpectedId(Domain, NamespaceName.Get(FString()), GroupName.Get(FString()), TaskName.Get(FString()));
        if (Model->GetMissionTaskId().Get(FString()) != ExpectedModelId || Model->GetName().Get(FString()) != TaskName.Get(FString())) return nullptr;
        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        if (const auto Sources = Model->GetCompleteAcquireActions(); Sources.IsValid()) for (const auto& Source : *Sources)
        {
            if (!Source.IsValid()) continue;
                Gs2::Core::Model::FAcquireActionPtr Action = MakeShared<Gs2::Core::Model::FAcquireAction>(*Source);
            if (const auto Config = Prepared->GetConfig(); Config.IsValid()) for (const auto& Entry : *Config) if (Entry.IsValid()) Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(Action, Entry->GetKey(), Entry->GetValue());
            if (Action.IsValid()) AcquireActions->Add(Action);
        }
        Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray Verifications;
        if (!PrepareCompleteVerifications(Service, Token, Model->GetVerifyCompleteConsumeActions(), Prepared->GetConfig(), Verifications)) return nullptr;
        if (HasKnownReceiveFailure(Domain, Token, Prepared, Model)) return nullptr;
        const FString ModelSnapshot = CompleteSnapshot(Model->ToJson());
        const auto ReceiveActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        ReceiveActions->Add(MakeShared<Gs2::Core::Model::FConsumeAction>()->WithAction(TOptional<FString>(Gs2::Mission::Domain::SpeculativeExecutor::FReceiveByUserIdSpeculativeExecutor::Action()))->WithRequest(TOptional<FString>(SerializeCompleteReceiveRequest(Prepared, UserId.Get(FString())))));
        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(Token, ReceiveActions, AcquireActions, TBigInt<1024, false>(1));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid()) return nullptr;
        const auto Verification = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::BuildAtomicVerificationPreparedCommit(MakeShared<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray>(Verifications), Verifications.Num());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([Commit, Verification]() { if (Verification.IsValid()) Verification->InvokeLegacy(); (*Commit)(); }), [DomainCopy = Domain, Prepared, ExpectedModelId, ModelSnapshot, Model, Token, Verification]() -> bool { return IsPreparedModelCurrent(DomainCopy, Prepared, ExpectedModelId, ModelSnapshot) && !HasKnownReceiveFailure(DomainCopy, Token, Prepared, Model) && (!Verification.IsValid() || Verification->IsStillSatisfied()); });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCompleteByUserIdSpeculativeExecutor::FCommitTask>> FCompleteByUserIdSpeculativeExecutor::Execute(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FCompleteByUserIdRequestPtr& Request) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
