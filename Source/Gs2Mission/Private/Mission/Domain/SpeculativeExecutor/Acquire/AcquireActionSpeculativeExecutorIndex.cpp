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

#include "Mission/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Mission/Domain/SpeculativeExecutor/Acquire/RevertReceiveByUserIdSpeculativeExecutor.h"
#include "Mission/Domain/SpeculativeExecutor/Acquire/IncreaseCounterByUserIdSpeculativeExecutor.h"
#include "Mission/Domain/SpeculativeExecutor/Acquire/SetCounterByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
    FAcquireActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FAcquireActionPtr& AcquireAction,
        TBigInt<1024, false> Rate
    ):
         Domain(Domain),
         Service(Service),
         AccessToken(AccessToken),
         AcquireAction(AcquireAction),
         Rate(Rate)
    {

    }

    FAcquireActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
         Service(From.Service),
        AccessToken(From.AccessToken),
        AcquireAction(From.AcquireAction),
        Rate(From.Rate)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAcquireActionSpeculativeExecutorIndex::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        auto NewAcquireAction = AcquireAction->WithAction(AcquireAction->GetAction()->Replace(TEXT("{region}"), ToCStr(Domain->RestSession->RegionName())));
        NewAcquireAction = AcquireAction->WithAction(NewAcquireAction->GetAction()->Replace(TEXT("{ownerId}"), ToCStr(Domain->RestSession->OwnerId())));
        NewAcquireAction = AcquireAction->WithAction(NewAcquireAction->GetAction()->Replace(TEXT("{userId}"), ToCStr(AccessToken->GetUserId().IsSet() ? *AccessToken->GetUserId() : "")));
        if (FRevertReceiveByUserIdSpeculativeExecutor::Action() == NewAcquireAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewAcquireAction->GetRequest().IsSet() ? *NewAcquireAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FRevertReceiveByUserIdRequest::FromJson(RequestModelJson);
            Request = FRevertReceiveByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FRevertReceiveByUserIdSpeculativeExecutor::Execute(
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
        if (FIncreaseCounterByUserIdSpeculativeExecutor::Action() == NewAcquireAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewAcquireAction->GetRequest().IsSet() ? *NewAcquireAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FIncreaseCounterByUserIdRequest::FromJson(RequestModelJson);
            Request = FIncreaseCounterByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FIncreaseCounterByUserIdSpeculativeExecutor::Execute(
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
        if (FSetCounterByUserIdSpeculativeExecutor::Action() == NewAcquireAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewAcquireAction->GetRequest().IsSet() ? *NewAcquireAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FSetCounterByUserIdRequest::FromJson(RequestModelJson);
            Request = FSetCounterByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FSetCounterByUserIdSpeculativeExecutor::Execute(
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

    TSharedPtr<FAsyncTask<FAcquireActionSpeculativeExecutorIndex::FCommitTask>> FAcquireActionSpeculativeExecutorIndex::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FAcquireActionPtr& AcquireAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, AcquireAction, Rate);
    }
}