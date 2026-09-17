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

#include "Inbox/Domain/SpeculativeExecutor/Transaction/ReadMessageByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Inbox/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Inbox/Model/Cache/Message.h"
#include "Inbox/Request/OpenMessageByUserIdRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Inbox::Domain::Transaction::SpeculativeExecutor
{
    FString FReadMessageByUserIdSpeculativeExecutor::Action() {
        return "Gs2Inbox:ReadMessageByUserId";
    }

    FReadMessageByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FReadMessageByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FReadMessageByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FReadMessageByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !AccessToken.IsValid() || !Request.IsValid()) return nullptr;

        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Inbox::Request::FReadMessageByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid())
        {
            const auto Config = Request->GetConfig();
            const Gs2::Inbox::Request::FReadMessageByUserIdRequestPtr RequestForJson = MakeShared<Gs2::Inbox::Request::FReadMessageByUserIdRequest>()
                ->WithContextStack(Request->GetContextStack())
                ->WithNamespaceName(Request->GetNamespaceName())
                ->WithUserId(Request->GetUserId())
                ->WithMessageName(Request->GetMessageName())
                ->WithTimeOffsetToken(Request->GetTimeOffsetToken())
                ->WithDuplicationAvoider(Request->GetDuplicationAvoider());
            if (Config.IsValid())
            {
                const TSharedPtr<TArray<TSharedPtr<Gs2::Inbox::Model::FConfig>>> FilteredConfig = MakeShared<TArray<TSharedPtr<Gs2::Inbox::Model::FConfig>>>();
                for (const auto& Item : *Config)
                {
                    if (Item.IsValid()) FilteredConfig->Add(MakeShared<Gs2::Inbox::Model::FConfig>(*Item));
                }
                RequestForJson->WithConfig(FilteredConfig);
            }
            PreparedRequest = Gs2::Inbox::Request::FReadMessageByUserIdRequest::FromJson(RequestForJson->ToJson());
        }
        if (!PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetMessageName().IsSet() || PreparedRequest->GetMessageName().Get(FString()).IsEmpty()) return nullptr;

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto MessageName = PreparedRequest->GetMessageName();
        const auto UserId = PreparedToken->GetUserId();
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:inbox:%s:user:%s:message:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId.Get(FString()), *MessageName.Get(FString()));
        Gs2::Inbox::Model::FMessagePtr Item;
        if (!Gs2::Inbox::Model::Cache::FMessageCache::TryGet(
                Domain->Cache, NamespaceName, UserId, MessageName, TimeOffset, &Item) ||
            !Item.IsValid() || !Item->GetMessageId().IsSet() || Item->GetMessageId().Get(FString()) != ExpectedId ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != MessageName.Get(FString()) ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId.Get(FString())) return nullptr;

        const Gs2::Inbox::Request::FOpenMessageByUserIdRequestPtr ChildRequest =
            MakeShared<Gs2::Inbox::Request::FOpenMessageByUserIdRequest>()
                ->WithNamespaceName(NamespaceName)
                ->WithUserId(UserId)
                ->WithMessageName(MessageName);
        FString ChildRequestBody;
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&ChildRequestBody);
        FJsonSerializer::Serialize(ChildRequest->ToJson().ToSharedRef(), Writer);
        const Gs2::Core::Model::FConsumeActionPtr ChildAction =
            MakeShared<Gs2::Core::Model::FConsumeAction>()
                ->WithAction(TOptional<FString>(TEXT("Gs2Inbox:OpenMessageByUserId")))
                ->WithRequest(TOptional<FString>(ChildRequestBody));
        const auto Future = Gs2::Inbox::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
            Domain, Service, PreparedToken, ChildAction, TBigInt<1024, false>(static_cast<int64>(1)));
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError()) return Future->GetTask().Error();
        *Result = Future->GetTask().Result();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FReadMessageByUserIdSpeculativeExecutor::FCommitTask>> FReadMessageByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inbox::Request::FReadMessageByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
