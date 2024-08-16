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

#include "AdReward/Domain/SpeculativeExecutor/Consume/ConsumePointByUserIdSpeculativeExecutor.h"

#include "AdReward/Domain/Gs2AdReward.h"
#include "Core/Domain/Gs2.h"

namespace Gs2::AdReward::Domain::SpeculativeExecutor
{

    FString FConsumePointByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2AdReward:ConsumePointByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumePointByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request,
        Gs2::AdReward::Model::FPointPtr Item
    )
    {
        Item->WithPoint(*Item->GetPoint() - *Request->GetPoint());
        if (*Item->GetPoint() < 0)
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("point", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FConsumePointByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FConsumePointByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FConsumePointByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->AdReward->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Point(
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
            FString("Point")
        );
        const auto Key = Model::FPointDomain::CreateCacheKey(
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                AdReward::Model::FPoint::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FConsumePointByUserIdSpeculativeExecutor::FCommitTask>> FConsumePointByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::AdReward::Domain::FGs2AdRewardDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr FConsumePointByUserIdSpeculativeExecutor::Rate(
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr FConsumePointByUserIdSpeculativeExecutor::Rate(
        const Gs2::AdReward::Request::FConsumePointByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
