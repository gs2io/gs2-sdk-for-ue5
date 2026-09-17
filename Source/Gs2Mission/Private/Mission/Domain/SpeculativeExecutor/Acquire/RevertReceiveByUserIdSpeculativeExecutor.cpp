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

#include "Mission/Domain/SpeculativeExecutor/Acquire/RevertReceiveByUserIdSpeculativeExecutor.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Mission/Domain/SpeculativeExecutor/CompleteSpeculativeCommit.h"
#include "Mission/Model/Cache/Complete.h"
#include "Mission/Model/Cache/MissionTaskModel.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
    namespace
    {
        using FCompletePtr = Gs2::Mission::Model::FCompletePtr;
        using FMissionTaskModelPtr = Gs2::Mission::Model::FMissionTaskModelPtr;
        using FMissionTaskModelCache = Gs2::Mission::Model::Cache::FMissionTaskModelCache;
        using Private::FCompleteSpeculativeCommit;

        FString RevertReceiveExpectedCompleteId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const FString& GroupName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:user:%s:group:%s:complete"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *GroupName);
        }
        FString RevertReceiveExpectedMissionTaskId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& GroupName, const FString& TaskName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:group:%s:missionTaskModel:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *GroupName, *TaskName);
        }
        bool RevertReceiveIsExpectedTask(const FMissionTaskModelPtr& Task, const FString& ExpectedId, const FString& Name)
        {
            return Task.IsValid() && Task->GetMissionTaskId().IsSet() && Task->GetMissionTaskId().Get(FString()) == ExpectedId && Task->GetName().IsSet() && Task->GetName().Get(FString()) == Name;
        }
        bool RevertReceiveIsExpectedComplete(const FCompletePtr& Item, const FString& ExpectedId, const FString& UserId, const FString& GroupName)
        {
            return Item.IsValid() && Item->GetCompleteId().IsSet() && Item->GetCompleteId().Get(FString()) == ExpectedId && Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId && Item->GetMissionGroupName().IsSet() && Item->GetMissionGroupName().Get(FString()) == GroupName;
        }
    }

    FString FRevertReceiveByUserIdSpeculativeExecutor::Action() { return FString("Gs2Mission:RevertReceiveByUserId"); }
    Gs2::Core::Model::FGs2ErrorPtr FRevertReceiveByUserIdSpeculativeExecutor::Transform(const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&, const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr&, Gs2::Mission::Model::FCompletePtr) { return nullptr; }

    FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
    FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From): Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

    Gs2::Core::Model::FGs2ErrorPtr FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Mission::Request::FRevertReceiveByUserIdRequest>(*Request);
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !Token.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetMissionGroupName().IsSet() || Prepared->GetMissionGroupName().Get(FString()).IsEmpty() || !Prepared->GetMissionTaskName().IsSet() || Prepared->GetMissionTaskName().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString GroupName = Prepared->GetMissionGroupName().Get(FString());
        const FString TaskName = Prepared->GetMissionTaskName().Get(FString());
        FMissionTaskModelPtr Task;
        if (!FMissionTaskModelCache::TryGet(Domain->Cache, NamespaceName, GroupName, TaskName, TOptional<int32>(), &Task) || !RevertReceiveIsExpectedTask(Task, RevertReceiveExpectedMissionTaskId(Domain, NamespaceName.Get(FString()), GroupName, TaskName), TaskName)) return nullptr;
        const auto TimeOffset = Token->GetTimeOffset();
        const FString CompleteId = RevertReceiveExpectedCompleteId(Domain, NamespaceName.Get(FString()), UserId, GroupName);
        FCompletePtr Cached;
        if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(Domain->Cache, NamespaceName, UserId, GroupName, TimeOffset, &Cached) || !RevertReceiveIsExpectedComplete(Cached, CompleteId, UserId, GroupName) || !Cached->GetReceivedMissionTaskNames().IsValid()) return nullptr;
        const auto Transform = [TaskName](const FCompletePtr& Source) -> FCompletePtr
        {
            if (!Source.IsValid() || !Source->GetReceivedMissionTaskNames().IsValid() || !Source->GetReceivedMissionTaskNames()->Contains(TaskName)) return nullptr;
            auto Changed = FCompleteSpeculativeCommit::Clone(Source);
            Changed->GetReceivedMissionTaskNames()->RemoveAll([TaskName](const FString& Name) { return Name == TaskName; });
            Changed->WithRevision(0);
            return Changed;
        };
        const TArray<FString> NoReceives;
        const auto ComposeTransform = [Transform](const FCompletePtr& Source, const TArray<FString>&) -> FCompletePtr { return Transform(Source); };
        const auto Commit = MakeShared<FCompleteSpeculativeCommit>(Domain->Cache, NamespaceName, UserId, GroupName, TimeOffset, CompleteId, Transform, ComposeTransform, NoReceives, true, TaskName);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(Commit->CompositionKey(), [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) { return Commit->TryCompose(Current, HasCurrent, Next); }, [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask>> FRevertReceiveByUserIdSpeculativeExecutor::Execute(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request) { return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }
    Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr FRevertReceiveByUserIdSpeculativeExecutor::Rate(const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request, const double) { return Request; }
    Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr FRevertReceiveByUserIdSpeculativeExecutor::Rate(const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request, TBigInt<1024, false>) { return Request; }
}
