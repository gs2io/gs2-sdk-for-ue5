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

#include "Mission/Domain/SpeculativeExecutor/Consume/DecreaseCounterByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Mission/Domain/Gs2Mission.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{

    FString FDecreaseCounterByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Mission:DecreaseCounterByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDecreaseCounterByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr& Request,
        Gs2::Mission::Model::FCounterPtr Item
    )
    {
        for (auto Value : *Item->GetValues())
        {
            Value->WithValue(*Value->GetValue() - *Request->GetValue());
        }
        return nullptr;
    }

    FDecreaseCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDecreaseCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDecreaseCounterByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Mission->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Counter(
                Request->GetCounterName().IsSet() ? *Request->GetCounterName() : FString("")
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
            FString("Counter")
        );
        const auto Key = Model::FCounterDomain::CreateCacheKey(
            Request->GetCounterName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Mission::Model::FCounter::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDecreaseCounterByUserIdSpeculativeExecutor::FCommitTask>> FDecreaseCounterByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr FDecreaseCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetValue().IsSet())
        {
            Request->WithValue(*Request->GetValue() * Rate);
        }
        return Request;
    }

    Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr FDecreaseCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FDecreaseCounterByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetValue().IsSet())
        {
            Rate.Multiply(*Request->GetValue());
            Request->WithValue(Rate.ToInt());
        }
        return Request;
    }
}
