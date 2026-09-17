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

#include "Showcase/Domain/SpeculativeExecutor/Acquire/AcquireActionSpeculativeExecutorIndex.h"
#include "Showcase/Domain/SpeculativeExecutor/Acquire/DecrementPurchaseCountByUserIdSpeculativeExecutor.h"
#include "Showcase/Domain/SpeculativeExecutor/Acquire/ForceReDrawByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Showcase::Domain::SpeculativeExecutor
{
    FAcquireActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
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
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        auto NewAcquireAction = AcquireAction->WithAction(AcquireAction->GetAction()->Replace(TEXT("{region}"), ToCStr(Domain->RestSession->RegionName())));
        NewAcquireAction = AcquireAction->WithAction(NewAcquireAction->GetAction()->Replace(TEXT("{ownerId}"), ToCStr(Domain->RestSession->OwnerId())));
        NewAcquireAction = AcquireAction->WithAction(NewAcquireAction->GetAction()->Replace(TEXT("{userId}"), ToCStr(AccessToken->GetUserId().IsSet() ? *AccessToken->GetUserId() : "")));
        if (FDecrementPurchaseCountByUserIdSpeculativeExecutor::Action() == NewAcquireAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewAcquireAction->GetRequest().IsSet() ? *NewAcquireAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FDecrementPurchaseCountByUserIdRequest::FromJson(RequestModelJson);
            const int64 Count = Request->GetCount().IsSet() ? static_cast<int64>(*Request->GetCount()) : 1;
            if (Count == 0)
            {
                Request->WithCount(0);
            }
            else
            {
                const uint64 Magnitude = Count < 0 ? static_cast<uint64>(-Count) : static_cast<uint64>(Count);
                const uint64 MaxMagnitude = Count < 0 ? 2147483648ULL : 2147483647ULL;
                const uint64 MaxRate = MaxMagnitude / Magnitude;
                if (Rate > TBigInt<1024, false>(static_cast<int64>(MaxRate)))
                {
                    return nullptr;
                }
                const int64 Scaled = Count * Rate.ToInt();
                Request->WithCount(static_cast<int32>(Scaled));
            }
            auto Future = FDecrementPurchaseCountByUserIdSpeculativeExecutor::Execute(
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
            return nullptr;
        }
        if (FForceReDrawByUserIdSpeculativeExecutor::Action() == NewAcquireAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewAcquireAction->GetRequest().IsSet() ? *NewAcquireAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FForceReDrawByUserIdRequest::FromJson(RequestModelJson);
            Request = FForceReDrawByUserIdSpeculativeExecutor::Rate(Request, Rate);
            auto Future = FForceReDrawByUserIdSpeculativeExecutor::Execute(
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
            return nullptr;
        }
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAcquireActionSpeculativeExecutorIndex::FCommitTask>> FAcquireActionSpeculativeExecutorIndex::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Showcase::Domain::FGs2ShowcaseDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FAcquireActionPtr& AcquireAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, AcquireAction, Rate);
    }
}
