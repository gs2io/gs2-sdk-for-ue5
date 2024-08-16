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

#include "Experience/Domain/SpeculativeExecutor/Acquire/SetRankCapByUserIdSpeculativeExecutor.h"
#include "Experience/Domain/Gs2Experience.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{

    FString FSetRankCapByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Experience:SetRankCapByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetRankCapByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request,
        Gs2::Experience::Model::FStatusPtr Item
    )
    {
        Item->WithRankCapValue(Request->GetRankCapValue());
        return nullptr;
    }

    FSetRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSetRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetRankCapByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Experience->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Status(
                Request->GetExperienceName().IsSet() ? *Request->GetExperienceName() : FString(""),
                Request->GetPropertyId().IsSet() ? *Request->GetPropertyId() : FString("")
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Item = Future->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
        }
        auto Err = Transform(Domain, AccessToken, Request, Item);
        if (Err != nullptr)
        {
            return Err;
        }

        const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            FString("Status")
        );
        const auto Key = Model::FStatusDomain::CreateCacheKey(
            Request->GetExperienceName(),
            Request->GetPropertyId()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Experience::Model::FStatus::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetRankCapByUserIdSpeculativeExecutor::FCommitTask>> FSetRankCapByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr FSetRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr FSetRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FSetRankCapByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
