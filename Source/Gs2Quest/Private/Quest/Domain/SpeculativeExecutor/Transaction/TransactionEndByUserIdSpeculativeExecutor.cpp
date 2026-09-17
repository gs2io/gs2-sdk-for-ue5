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

#include "Quest/Domain/SpeculativeExecutor/Transaction/EndByUserIdSpeculativeExecutor.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Model/ConsumeAction.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Quest/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Quest/Request/DeleteProgressByUserIdRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Quest::Domain::Transaction::SpeculativeExecutor
{
    FString FEndByUserIdSpeculativeExecutor::Action() {
        return "Gs2Quest:EndByUserId";
    }

    FEndByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Quest::Domain::FGs2QuestDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FEndByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FEndByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEndByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Quest::Request::FEndByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid())
        {
            PreparedRequest = Gs2::Quest::Request::FEndByUserIdRequest::FromJson(Request->ToJson());
        }
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString())) return nullptr;

        const Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr ChildRequest =
            MakeShared<Gs2::Quest::Request::FDeleteProgressByUserIdRequest>()
                ->WithNamespaceName(PreparedRequest->GetNamespaceName())
                ->WithUserId(PreparedToken->GetUserId());
        FString ChildRequestBody;
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&ChildRequestBody);
        FJsonSerializer::Serialize(ChildRequest->ToJson().ToSharedRef(), Writer);
        const Gs2::Core::Model::FConsumeActionPtr ChildAction =
            MakeShared<Gs2::Core::Model::FConsumeAction>()
                ->WithAction(TOptional<FString>(TEXT("Gs2Quest:DeleteProgressByUserId")))
                ->WithRequest(TOptional<FString>(ChildRequestBody));
        const auto Future = Gs2::Quest::Domain::SpeculativeExecutor::FConsumeActionSpeculativeExecutorIndex::Execute(
            Domain, Service, PreparedToken, ChildAction, TBigInt<1024, false>(static_cast<int64>(1)));
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError()) return Future->GetTask().Error();
        *Result = Future->GetTask().Result();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEndByUserIdSpeculativeExecutor::FCommitTask>> FEndByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Quest::Domain::FGs2QuestDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FEndByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
