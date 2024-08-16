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

#include "Exchange/Domain/SpeculativeExecutor/Consume/DeleteAwaitByUserIdSpeculativeExecutor.h"
#include "Exchange/Domain/Gs2Exchange.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Exchange::Domain::SpeculativeExecutor
{

    FString FDeleteAwaitByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Exchange:DeleteAwaitByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteAwaitByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request,
        Gs2::Exchange::Model::FAwaitPtr Item
    )
    {
        return nullptr;
    }

    FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
            Request->GetNamespaceName(),
            AccessToken->GetUserId(),
            FString("Await")
        );
        const auto Key = Model::FAwaitDomain::CreateCacheKey(
            Request->GetAwaitName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Exchange::Model::FAwait::TypeName,
                ParentKey,
                Key,
                nullptr,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteAwaitByUserIdSpeculativeExecutor::FCommitTask>> FDeleteAwaitByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Exchange::Domain::FGs2ExchangeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr FDeleteAwaitByUserIdSpeculativeExecutor::Rate(
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr FDeleteAwaitByUserIdSpeculativeExecutor::Rate(
        const Gs2::Exchange::Request::FDeleteAwaitByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
