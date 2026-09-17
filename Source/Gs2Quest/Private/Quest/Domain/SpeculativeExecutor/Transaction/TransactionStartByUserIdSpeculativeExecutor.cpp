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

#include "Quest/Domain/SpeculativeExecutor/Transaction/StartByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Model/ConsumeAction.h"
#include "Quest/Model/Cache/QuestModel.h"
#include "Quest/Model/QuestModel.h"
#include "Quest/Request/CreateProgressByUserIdRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Quest::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString SerializeQuestStartSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }
    }

    FString FStartByUserIdSpeculativeExecutor::Action() {
        return "Gs2Quest:StartByUserId";
    }

    FStartByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Quest::Domain::FGs2QuestDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FStartByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FStartByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FStartByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid())
        {
            PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        }
        Gs2::Quest::Request::FStartByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid())
        {
            PreparedRequest = Gs2::Quest::Request::FStartByUserIdRequest::FromJson(Request->ToJson());
        }
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
            !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty())
        {
            return nullptr;
        }
        if (PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()))
        {
            return nullptr;
        }

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto QuestGroupName = PreparedRequest->GetQuestGroupName();
        const auto QuestName = PreparedRequest->GetQuestName();
        const auto UserId = PreparedToken->GetUserId();
        Gs2::Quest::Model::FQuestModelPtr Item = nullptr;
        if (!Gs2::Quest::Model::Cache::FQuestModelCache::TryGet(
                Domain->Cache, NamespaceName, QuestGroupName, QuestName, TOptional<int32>(), &Item) ||
            !Item.IsValid() || !Item->GetQuestModelId().IsSet() ||
            !Item->GetName().IsSet())
        {
            return nullptr;
        }
        const FString ExpectedQuestModelId = FString::Printf(
            TEXT("grn:gs2:%s:%s:quest:%s:group:%s:quest:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *QuestGroupName.Get(FString()), *QuestName.Get(FString()));
        if (*Item->GetQuestModelId() != ExpectedQuestModelId ||
            *Item->GetName() != *QuestName.Get(FString()))
        {
            return nullptr;
        }

        const auto ConsumeActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        if (const auto Sources = Item->GetConsumeActions(); Sources.IsValid())
        {
            for (const auto& Source : *Sources)
            {
                if (!Source.IsValid()) continue;
                Gs2::Core::Model::FConsumeActionPtr Action =
                    MakeShared<Gs2::Core::Model::FConsumeAction>(*Source);
                if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
                {
                    for (const auto& Entry : *Config)
                    {
                        if (!Entry.IsValid()) continue;
                        Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                            Gs2::Core::Model::FConsumeActionPtr(Action),
                            TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                    }
                }
                if (Action.IsValid()) ConsumeActions->Add(Action);
            }
        }

        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        const auto CreateProgressRequest = MakeShared<Gs2::Quest::Request::FCreateProgressByUserIdRequest>()
            ->WithNamespaceName(NamespaceName)
            ->WithUserId(UserId)
            ->WithForce(PreparedRequest->GetForce())
            ->WithConfig(PreparedRequest->GetConfig());
        FString CreateProgressRequestBody;
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&CreateProgressRequestBody);
        FJsonSerializer::Serialize(CreateProgressRequest->ToJson().ToSharedRef(), Writer);
        AcquireActions->Add(
            MakeShared<Gs2::Core::Model::FAcquireAction>()
                ->WithAction(TOptional<FString>(TEXT("Gs2Quest:CreateProgressByUserId")))
                ->WithRequest(TOptional<FString>(CreateProgressRequestBody))
        );

        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            PreparedToken, ConsumeActions, AcquireActions, TBigInt<1024, false>(1));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid()) return nullptr;
        const FString QuestSnapshot = SerializeQuestStartSnapshot(Item->ToJson());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([Commit]() { (*Commit)(); }),
            [DomainCopy = Domain, NamespaceName, QuestGroupName, QuestName, QuestSnapshot]()
            {
                Gs2::Quest::Model::FQuestModelPtr Current = nullptr;
                return Gs2::Quest::Model::Cache::FQuestModelCache::TryGet(
                    DomainCopy->Cache, NamespaceName, QuestGroupName, QuestName, TOptional<int32>(), &Current) &&
                    Current.IsValid() && SerializeQuestStartSnapshot(Current->ToJson()) == QuestSnapshot;
            });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FStartByUserIdSpeculativeExecutor::FCommitTask>> FStartByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Quest::Domain::FGs2QuestDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FStartByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
