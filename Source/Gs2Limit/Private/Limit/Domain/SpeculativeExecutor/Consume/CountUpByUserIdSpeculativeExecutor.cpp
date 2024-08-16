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

#include "Limit/Domain/SpeculativeExecutor/Consume/CountUpByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Limit/Domain/Gs2Limit.h"

namespace Gs2::Limit::Domain::SpeculativeExecutor
{

    FString FCountUpByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Limit:CountUpByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FCountUpByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request,
        Gs2::Limit::Model::FCounterPtr Item
    )
    {
        Item->WithCount(*Item->GetCount() - *Request->GetCountUpValue());
        if (*Item->GetCount() > *Request->GetMaxValue())
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FCountUpByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FCountUpByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FCountUpByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Limit->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Counter(
                Request->GetLimitName().IsSet() ? *Request->GetLimitName() : FString(""),
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
            Request->GetLimitName(),
            Request->GetCounterName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Limit::Model::FCounter::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FCountUpByUserIdSpeculativeExecutor::FCommitTask>> FCountUpByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Limit::Request::FCountUpByUserIdRequestPtr FCountUpByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetCountUpValue().IsSet())
        {
            Request->WithCountUpValue(*Request->GetCountUpValue() * Rate);
        }
        return Request;
    }

    Gs2::Limit::Request::FCountUpByUserIdRequestPtr FCountUpByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FCountUpByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetCountUpValue().IsSet())
        {
            Rate.Multiply(*Request->GetCountUpValue());
            Request->WithCountUpValue(Rate.ToInt());
        }
        return Request;
    }
}
