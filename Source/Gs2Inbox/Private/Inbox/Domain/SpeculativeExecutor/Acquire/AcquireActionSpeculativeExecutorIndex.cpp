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

#include "Inbox/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Inbox/Domain/SpeculativeExecutor/Acquire/SendMessageByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inbox::Domain::SpeculativeExecutor
{
    FAcquireActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
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
        if (FSendMessageByUserIdSpeculativeExecutor::Action() == NewAcquireAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewAcquireAction->GetRequest().IsSet() ? *NewAcquireAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FSendMessageByUserIdRequest::FromJson(RequestModelJson);
            Request = FSendMessageByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FSendMessageByUserIdSpeculativeExecutor::Execute(
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
        const Gs2::Inbox::Domain::FGs2InboxDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FAcquireActionPtr& AcquireAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, AcquireAction, Rate);
    }
}