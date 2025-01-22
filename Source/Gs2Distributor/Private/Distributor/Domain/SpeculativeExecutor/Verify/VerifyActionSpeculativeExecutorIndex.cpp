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

#include "Distributor/Domain/SpeculativeExecutor/Verify/VerifyActionSpeculativeExecutorIndex.h"
#include "Distributor/Domain/SpeculativeExecutor/Verify/IfExpressionByUserIdSpeculativeExecutor.h"
#include "Distributor/Domain/SpeculativeExecutor/Verify/AndExpressionByUserIdSpeculativeExecutor.h"
#include "Distributor/Domain/SpeculativeExecutor/Verify/OrExpressionByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Distributor::Domain::SpeculativeExecutor
{
    FVerifyActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FVerifyActionPtr& VerifyAction,
        TBigInt<1024, false> Rate
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        VerifyAction(VerifyAction),
        Rate(Rate)
    {

    }

    FVerifyActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        VerifyAction(From.VerifyAction),
        Rate(From.Rate)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyActionSpeculativeExecutorIndex::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        auto NewVerifyAction = VerifyAction->WithAction(VerifyAction->GetAction()->Replace(TEXT("{region}"), ToCStr(Domain->RestSession->RegionName())));
        NewVerifyAction = VerifyAction->WithAction(NewVerifyAction->GetAction()->Replace(TEXT("{ownerId}"), ToCStr(Domain->RestSession->OwnerId())));
        NewVerifyAction = VerifyAction->WithAction(NewVerifyAction->GetAction()->Replace(TEXT("{userId}"), ToCStr(AccessToken->GetUserId().IsSet() ? *AccessToken->GetUserId() : "")));
        if (FIfExpressionByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FIfExpressionByUserIdRequest::FromJson(RequestModelJson);
            Request = FIfExpressionByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FIfExpressionByUserIdSpeculativeExecutor::Execute(
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
        if (FAndExpressionByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FAndExpressionByUserIdRequest::FromJson(RequestModelJson);
            Request = FAndExpressionByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FAndExpressionByUserIdSpeculativeExecutor::Execute(
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
        if (FOrExpressionByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FOrExpressionByUserIdRequest::FromJson(RequestModelJson);
            Request = FOrExpressionByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FOrExpressionByUserIdSpeculativeExecutor::Execute(
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

    TSharedPtr<FAsyncTask<FVerifyActionSpeculativeExecutorIndex::FCommitTask>> FVerifyActionSpeculativeExecutorIndex::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Distributor::Domain::FGs2DistributorDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FVerifyActionPtr& VerifyAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, VerifyAction, Rate);
    }
}