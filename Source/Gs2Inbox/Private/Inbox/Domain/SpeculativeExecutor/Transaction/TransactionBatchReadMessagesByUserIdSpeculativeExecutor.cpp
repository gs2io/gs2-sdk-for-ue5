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

#include "Inbox/Domain/SpeculativeExecutor/Transaction/BatchReadMessagesByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inbox/Domain/SpeculativeExecutor/Transaction/ReadMessageByUserIdSpeculativeExecutor.h"

namespace Gs2::Inbox::Domain::Transaction::SpeculativeExecutor
{
    FString FBatchReadMessagesByUserIdSpeculativeExecutor::Action() {
        return "Gs2Inbox:BatchReadMessagesByUserId";
    }

    FBatchReadMessagesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FBatchReadMessagesByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FBatchReadMessagesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FBatchReadMessagesByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;

        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inbox::Request::FBatchReadMessagesByUserIdRequestPtr PreparedRequest = nullptr;
        const auto MessageNames = Request->GetMessageNames();
        if (Request.IsValid())
        {
            const auto Config = Request->GetConfig();
            const Gs2::Inbox::Request::FBatchReadMessagesByUserIdRequestPtr RequestForJson = MakeShared<Gs2::Inbox::Request::FBatchReadMessagesByUserIdRequest>()
                ->WithContextStack(Request->GetContextStack())
                ->WithNamespaceName(Request->GetNamespaceName())
                ->WithUserId(Request->GetUserId())
                ->WithTimeOffsetToken(Request->GetTimeOffsetToken())
                ->WithDuplicationAvoider(Request->GetDuplicationAvoider());
            if (MessageNames.IsValid())
            {
                const TSharedPtr<TArray<FString>> MessageNamesCopy = MakeShared<TArray<FString>>();
                *MessageNamesCopy = *MessageNames;
                RequestForJson->WithMessageNames(MessageNamesCopy);
            }
            if (Config.IsValid())
            {
                const TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Model::FConfig>>> FilteredConfig = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Model::FConfig>>>();
                for (const auto& Item : *Config)
                {
                    if (Item.IsValid()) FilteredConfig->Add(MakeShared<Gs2::Inbox::Model::FConfig>(*Item));
                }
                RequestForJson->WithConfig(FilteredConfig);
            }
            PreparedRequest = Gs2::Inbox::Request::FBatchReadMessagesByUserIdRequest::FromJson(RequestForJson->ToJson());
        }
        if (!PreparedToken.IsValid() || !PreparedRequest.IsValid() || !PreparedToken->GetUserId().IsSet() ||
            PreparedToken->GetUserId().Get(FString()).IsEmpty() || !MessageNames.IsValid()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetMessageNames().IsValid()) return nullptr;

        const TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray> PreparedCommits =
            MakeShared<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitArray>();
        for (const auto& MessageName : *PreparedRequest->GetMessageNames())
        {
            if (MessageName.IsEmpty()) continue;
            const Gs2::Inbox::Request::FReadMessageByUserIdRequestPtr ReadRequest =
                MakeShared<Gs2::Inbox::Request::FReadMessageByUserIdRequest>()
                    ->WithNamespaceName(PreparedRequest->GetNamespaceName())
                    ->WithUserId(PreparedToken->GetUserId())
                    ->WithMessageName(TOptional<FString>(MessageName))
                    ->WithConfig(PreparedRequest->GetConfig())
                    ->WithTimeOffsetToken(PreparedRequest->GetTimeOffsetToken());
            const auto Future = Gs2::Inbox::Domain::Transaction::SpeculativeExecutor::FReadMessageByUserIdSpeculativeExecutor::Execute(
                Domain, Service, PreparedToken, ReadRequest);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError()) return Future->GetTask().Error();
            const auto ChildCommit = Future->GetTask().Result();
            if (ChildCommit.IsValid()) PreparedCommits->Add(ChildCommit);
        }
        if (PreparedCommits->Num() == 0) return nullptr;
        const auto AtomicCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::BuildAtomicCommit(
            PreparedCommits, PreparedCommits->Num());
        if (!AtomicCommit.IsValid()) return nullptr;
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(AtomicCommit);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FBatchReadMessagesByUserIdSpeculativeExecutor::FCommitTask>> FBatchReadMessagesByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FBatchReadMessagesByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
