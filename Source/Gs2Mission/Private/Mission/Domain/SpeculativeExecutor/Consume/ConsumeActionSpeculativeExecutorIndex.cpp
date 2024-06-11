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
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Mission/Domain/SpeculativeExecutor/Consume/ConsumeActionSpeculativeExecutorIndex.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/ReceiveByUserIdSpeculativeExecutor.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/VerifyCompleteByUserIdSpeculativeExecutor.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/DecreaseCounterByUserIdSpeculativeExecutor.h"
#include "Mission/Domain/SpeculativeExecutor/Consume/VerifyCounterValueByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
    FConsumeActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FConsumeActionPtr& ConsumeAction,
        TBigInt<1024, false> Rate
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        ConsumeAction(ConsumeAction),
        Rate(Rate)
    {

    }

    FConsumeActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        ConsumeAction(From.ConsumeAction),
        Rate(From.Rate)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumeActionSpeculativeExecutorIndex::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        auto NewConsumeAction = ConsumeAction->WithAction(ConsumeAction->GetAction()->Replace(TEXT("{region}"), ToCStr(Domain->RestSession->RegionName())));
        NewConsumeAction = ConsumeAction->WithAction(NewConsumeAction->GetAction()->Replace(TEXT("{ownerId}"), ToCStr(Domain->RestSession->OwnerId())));
        NewConsumeAction = ConsumeAction->WithAction(NewConsumeAction->GetAction()->Replace(TEXT("{userId}"), ToCStr(AccessToken->GetUserId().IsSet() ? *AccessToken->GetUserId() : "")));
        if (FReceiveByUserIdSpeculativeExecutor::Action() == NewConsumeAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewConsumeAction->GetRequest().IsSet() ? *NewConsumeAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FReceiveByUserIdRequest::FromJson(RequestModelJson);
            Request = FReceiveByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FReceiveByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FVerifyCompleteByUserIdSpeculativeExecutor::Action() == NewConsumeAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewConsumeAction->GetRequest().IsSet() ? *NewConsumeAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyCompleteByUserIdRequest::FromJson(RequestModelJson);
            Request = FVerifyCompleteByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FVerifyCompleteByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FDecreaseCounterByUserIdSpeculativeExecutor::Action() == NewConsumeAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewConsumeAction->GetRequest().IsSet() ? *NewConsumeAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FDecreaseCounterByUserIdRequest::FromJson(RequestModelJson);
            Request = FDecreaseCounterByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FDecreaseCounterByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FVerifyCounterValueByUserIdSpeculativeExecutor::Action() == NewConsumeAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewConsumeAction->GetRequest().IsSet() ? *NewConsumeAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyCounterValueByUserIdRequest::FromJson(RequestModelJson);
            Request = FVerifyCounterValueByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FVerifyCounterValueByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FConsumeActionSpeculativeExecutorIndex::FCommitTask>> FConsumeActionSpeculativeExecutorIndex::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FConsumeActionPtr& ConsumeAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, ConsumeAction, Rate);
    }
}