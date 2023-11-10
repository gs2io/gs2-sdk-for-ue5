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

#include "Idle/Domain/SpeculativeExecutor/Acquire/IncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Idle::Domain::SpeculativeExecutor
{

    FString FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Idle:IncreaseMaximumIdleMinutesByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request,
        Gs2::Idle::Model::FStatusPtr Item
    )
    {
        Item->WithMaximumIdleMinutes(*Item->GetMaximumIdleMinutes() + *Request->GetIncreaseMinutes());
        return nullptr;
    }

    FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Idle::Domain::FGs2IdleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Idle->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Status(
                Request->GetCategoryName().IsSet() ? *Request->GetCategoryName() : FString("")
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
            Request->GetCategoryName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Idle::Model::FStatus::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::FCommitTask>> FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Idle::Domain::FGs2IdleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetIncreaseMinutes().IsSet())
        {
            Request->WithIncreaseMinutes(*Request->GetIncreaseMinutes() * Rate);
        }
        return Request;
    }

    Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr FIncreaseMaximumIdleMinutesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Idle::Request::FIncreaseMaximumIdleMinutesByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetIncreaseMinutes().IsSet())
        {
            Rate.Multiply(*Request->GetIncreaseMinutes());
            Request->WithIncreaseMinutes(Rate.ToInt());
        }
        return Request;
    }
}
