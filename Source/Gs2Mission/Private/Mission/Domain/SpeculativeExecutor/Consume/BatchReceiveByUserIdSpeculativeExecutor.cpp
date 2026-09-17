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

#include "Mission/Domain/SpeculativeExecutor/Consume/BatchReceiveByUserIdSpeculativeExecutor.h"
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

        FString BatchReceiveExpectedCompleteId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId, const FString& GroupName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:user:%s:group:%s:complete"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *GroupName);
        }
        FString BatchReceiveExpectedMissionTaskId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& GroupName, const FString& TaskName)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:mission:%s:group:%s:missionTaskModel:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *GroupName, *TaskName);
        }
        bool BatchReceiveIsExpectedTask(const FMissionTaskModelPtr& Task, const FString& ExpectedId, const FString& Name)
        {
            return Task.IsValid() && Task->GetMissionTaskId().IsSet() && Task->GetMissionTaskId().Get(FString()) == ExpectedId && Task->GetName().IsSet() && Task->GetName().Get(FString()) == Name;
        }
        bool BatchReceiveIsExpectedComplete(const FCompletePtr& Item, const FString& ExpectedId, const FString& UserId, const FString& GroupName)
        {
            return Item.IsValid() && Item->GetCompleteId().IsSet() && Item->GetCompleteId().Get(FString()) == ExpectedId && Item->GetUserId().IsSet() && Item->GetUserId().Get(FString()) == UserId && Item->GetMissionGroupName().IsSet() && Item->GetMissionGroupName().Get(FString()) == GroupName;
        }
        bool ValidateReceiveRules(const FCompletePtr& Source, const TArray<FMissionTaskModelPtr>& Tasks)
        {
            if (!Source.IsValid()) return false;
            for (const auto& Task : Tasks)
            {
                if (!Task.IsValid()) return false;
                const FString Type = Task->GetVerifyCompleteType().Get(FString());
                if (Type != TEXT("consumeActions") && Type != TEXT("verifyActions"))
                {
                    const auto Completed = Source->GetCompletedMissionTaskNames();
                    if (!Completed.IsValid() || !Completed->Contains(Task->GetName().Get(FString()))) return false;
                }
            }
            return true;
        }
    }

    FString FBatchReceiveByUserIdSpeculativeExecutor::Action() { return FString("Gs2Mission:BatchReceiveByUserId"); }
    Gs2::Core::Model::FGs2ErrorPtr FBatchReceiveByUserIdSpeculativeExecutor::Transform(const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&, const Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr&, Gs2::Mission::Model::FCompletePtr) { return nullptr; }

    FBatchReceiveByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr& Request): Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request) {}
    FBatchReceiveByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From): Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request) {}

    Gs2::Core::Model::FGs2ErrorPtr FBatchReceiveByUserIdSpeculativeExecutor::FCommitTask::Action(TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Mission::Request::FBatchReceiveByUserIdRequest>(*Request);
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !Token.IsValid() || !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetMissionTaskNames().IsValid()) Prepared->WithMissionTaskNames(MakeShared<TArray<FString>>(*Prepared->GetMissionTaskNames()));
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}")) Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) || !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() || !Prepared->GetMissionGroupName().IsSet() || Prepared->GetMissionGroupName().Get(FString()).IsEmpty() || !Prepared->GetMissionTaskNames().IsValid()) return nullptr;

        TArray<FString> Requested;
        for (const auto& Name : *Prepared->GetMissionTaskNames())
        {
            if (!Name.IsEmpty() && !Requested.Contains(Name)) Requested.Add(Name);
        }
        if (Requested.Num() == 0) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString GroupName = Prepared->GetMissionGroupName().Get(FString());
        TArray<FMissionTaskModelPtr> Tasks;
        for (const auto& Name : Requested)
        {
            FMissionTaskModelPtr Task;
            if (FMissionTaskModelCache::TryGet(Domain->Cache, NamespaceName, GroupName, Name, TOptional<int32>(), &Task) && BatchReceiveIsExpectedTask(Task, BatchReceiveExpectedMissionTaskId(Domain, NamespaceName.Get(FString()), GroupName, Name), Name)) Tasks.Add(Task);
        }
        if (Tasks.Num() == 0) return nullptr;
        TArray<FString> PredictableNames;
        for (const auto& Task : Tasks) PredictableNames.Add(Task->GetName().Get(FString()));
        const auto TimeOffset = Token->GetTimeOffset();
        const FString CompleteId = BatchReceiveExpectedCompleteId(Domain, NamespaceName.Get(FString()), UserId, GroupName);
        FCompletePtr Cached;
        if (!Gs2::Mission::Model::Cache::FCompleteCache::TryGet(Domain->Cache, NamespaceName, UserId, GroupName, TimeOffset, &Cached) || !BatchReceiveIsExpectedComplete(Cached, CompleteId, UserId, GroupName) || !Cached->GetReceivedMissionTaskNames().IsValid()) return nullptr;
        const int64 LogicalTime = static_cast<int64>(FDateTime::UtcNow().ToUnixTimestampDecimal() * 1000.0) + static_cast<int64>(TimeOffset.Get(0)) * 1000;
        const auto Transform = [Tasks, PredictableNames, LogicalTime](const FCompletePtr& Source) -> FCompletePtr
        {
            if (!ValidateReceiveRules(Source, Tasks) || !Source->GetReceivedMissionTaskNames().IsValid()) return nullptr;
            for (const auto& Name : PredictableNames) if (Source->GetReceivedMissionTaskNames()->Contains(Name)) return nullptr;
            auto Changed = FCompleteSpeculativeCommit::Clone(Source);
            for (const auto& Name : PredictableNames) Changed->GetReceivedMissionTaskNames()->Add(Name);
            Changed->WithUpdatedAt(LogicalTime)->WithRevision(0);
            return Changed;
        };
        const auto ComposeTransform = [Tasks, PredictableNames, LogicalTime](const FCompletePtr& Source, const TArray<FString>& Staged) -> FCompletePtr
        {
            if (!ValidateReceiveRules(Source, Tasks) || !Source->GetReceivedMissionTaskNames().IsValid()) return nullptr;
            TArray<FString> Remaining;
            for (const auto& Name : PredictableNames) if (!Staged.Contains(Name)) Remaining.Add(Name);
            if (Remaining.Num() == 0) return Source;
            for (const auto& Name : Remaining) if (Source->GetReceivedMissionTaskNames()->Contains(Name)) return nullptr;
            auto Changed = FCompleteSpeculativeCommit::Clone(Source);
            for (const auto& Name : Remaining) Changed->GetReceivedMissionTaskNames()->Add(Name);
            Changed->WithUpdatedAt(LogicalTime)->WithRevision(0);
            return Changed;
        };
        const auto Commit = MakeShared<FCompleteSpeculativeCommit>(Domain->Cache, NamespaceName, UserId, GroupName, TimeOffset, CompleteId, Transform, ComposeTransform, PredictableNames, false, FString());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(Commit->CompositionKey(), [Commit](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next) { return Commit->TryCompose(Current, HasCurrent, Next); }, [Commit](const TSharedPtr<void>& State) { Commit->Commit(State); });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBatchReceiveByUserIdSpeculativeExecutor::FCommitTask>> FBatchReceiveByUserIdSpeculativeExecutor::Execute(const Gs2::Core::Domain::FGs2Ptr& Domain, const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service, const Gs2::Auth::Model::FAccessTokenPtr& AccessToken, const Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr& Request) { return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request); }
    Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr FBatchReceiveByUserIdSpeculativeExecutor::Rate(const Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr& Request, const double) { return Request; }
    Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr FBatchReceiveByUserIdSpeculativeExecutor::Rate(const Gs2::Mission::Request::FBatchReceiveByUserIdRequestPtr& Request, TBigInt<1024, false>) { return Request; }
}
