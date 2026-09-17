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
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyActionSpeculativeExecutorIndex.h"
#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyStaminaValueByUserIdSpeculativeExecutor.h"
#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyStaminaMaxValueByUserIdSpeculativeExecutor.h"
#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyStaminaRecoverIntervalMinutesByUserIdSpeculativeExecutor.h"
#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyStaminaRecoverValueByUserIdSpeculativeExecutor.h"
#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyStaminaOverflowValueByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{
    FVerifyActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FVerifyActionPtr& VerifyAction,
        TBigInt<1024, false> Rate,
        bool Inverse
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        VerifyAction(VerifyAction),
        Rate(Rate),
        Inverse(Inverse)
    {

    }

    FVerifyActionSpeculativeExecutorIndex::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        VerifyAction(From.VerifyAction),
        Rate(From.Rate),
        Inverse(From.Inverse)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyActionSpeculativeExecutorIndex::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        auto NewVerifyAction = VerifyAction->WithAction(VerifyAction->GetAction()->Replace(TEXT("{region}"), ToCStr(Domain->RestSession->RegionName())));
        NewVerifyAction = NewVerifyAction->WithAction(NewVerifyAction->GetAction()->Replace(TEXT("{ownerId}"), ToCStr(Domain->RestSession->OwnerId())));
        NewVerifyAction = NewVerifyAction->WithAction(NewVerifyAction->GetAction()->Replace(TEXT("{userId}"), ToCStr(AccessToken->GetUserId().IsSet() ? *AccessToken->GetUserId() : "")));
        if (FVerifyStaminaValueByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyStaminaValueByUserIdRequest::FromJson(RequestModelJson);
            if (Rate != 1)
            {
                Request = FVerifyStaminaValueByUserIdSpeculativeExecutor::Rate(Request, Rate);
            }
            auto Future = Inverse ? FVerifyStaminaValueByUserIdSpeculativeExecutor::ExecuteInverse(
                Domain,
                Service,
                AccessToken,
                Request
            ) : FVerifyStaminaValueByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            if (!Future.IsValid()) return nullptr;
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyStaminaMaxValueByUserIdRequest::FromJson(RequestModelJson);
            if (Rate != 1)
            {
                Request = FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Rate(Request, Rate);
            }
            auto Future = Inverse ? FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::ExecuteInverse(
                Domain,
                Service,
                AccessToken,
                Request
            ) : FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            if (!Future.IsValid()) return nullptr;
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FVerifyStaminaRecoverIntervalMinutesByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyStaminaRecoverIntervalMinutesByUserIdRequest::FromJson(RequestModelJson);
            if (Rate != 1)
            {
                Request = FVerifyStaminaRecoverIntervalMinutesByUserIdSpeculativeExecutor::Rate(Request, Rate);
            }
            auto Future = Inverse ? FVerifyStaminaRecoverIntervalMinutesByUserIdSpeculativeExecutor::ExecuteInverse(
                Domain,
                Service,
                AccessToken,
                Request
            ) : FVerifyStaminaRecoverIntervalMinutesByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            if (!Future.IsValid()) return nullptr;
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FVerifyStaminaRecoverValueByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyStaminaRecoverValueByUserIdRequest::FromJson(RequestModelJson);
            if (Rate != 1)
            {
                Request = FVerifyStaminaRecoverValueByUserIdSpeculativeExecutor::Rate(Request, Rate);
            }
            auto Future = Inverse ? FVerifyStaminaRecoverValueByUserIdSpeculativeExecutor::ExecuteInverse(
                Domain,
                Service,
                AccessToken,
                Request
            ) : FVerifyStaminaRecoverValueByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            if (!Future.IsValid()) return nullptr;
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                return Future->GetTask().Error();
            }
            *Result = Future->GetTask().Result();
        }
        if (FVerifyStaminaOverflowValueByUserIdSpeculativeExecutor::Action() == NewVerifyAction->GetAction()) {
            TSharedPtr<FJsonObject> RequestModelJson;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(NewVerifyAction->GetRequest().IsSet() ? *NewVerifyAction->GetRequest() : "{}");
                !FJsonSerializer::Deserialize(JsonReader, RequestModelJson))
            {
                return nullptr;
            }
            auto Request = Request::FVerifyStaminaOverflowValueByUserIdRequest::FromJson(RequestModelJson);
            if (Rate != 1)
            {
                Request = FVerifyStaminaOverflowValueByUserIdSpeculativeExecutor::Rate(Request, Rate);
            }
            auto Future = Inverse ? FVerifyStaminaOverflowValueByUserIdSpeculativeExecutor::ExecuteInverse(
                Domain,
                Service,
                AccessToken,
                Request
            ) : FVerifyStaminaOverflowValueByUserIdSpeculativeExecutor::Execute(
                Domain,
                Service,
                AccessToken,
                Request
            );
            if (!Future.IsValid()) return nullptr;
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
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FVerifyActionPtr& VerifyAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, VerifyAction, Rate, false);
    }

    TSharedPtr<FAsyncTask<FVerifyActionSpeculativeExecutorIndex::FCommitTask>> FVerifyActionSpeculativeExecutorIndex::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Core::Model::FVerifyActionPtr& VerifyAction,
        TBigInt<1024, false> Rate
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, VerifyAction, Rate, true);
    }

}
