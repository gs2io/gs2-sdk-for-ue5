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

#include "Enchant/Domain/SpeculativeExecutor/Acquire/SetBalanceParameterStatusByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Enchant/Domain/Gs2Enchant.h"

namespace Gs2::Enchant::Domain::SpeculativeExecutor
{

    FString FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Enchant:SetBalanceParameterStatusByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request,
        Gs2::Enchant::Model::FBalanceParameterStatusPtr Item
    )
    {
        Item->WithParameterValues(Request->GetParameterValues());
        return nullptr;
    }

    FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Enchant->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->BalanceParameterStatus(
                Request->GetParameterName().IsSet() ? *Request->GetParameterName() : FString(""),
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
            FString("BalanceParameterStatus")
        );
        const auto Key = Model::FBalanceParameterStatusDomain::CreateCacheKey(
            Request->GetParameterName(),
            Request->GetPropertyId()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Enchant::Model::FBalanceParameterStatus::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetBalanceParameterStatusByUserIdSpeculativeExecutor::FCommitTask>> FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enchant::Domain::FGs2EnchantDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr FSetBalanceParameterStatusByUserIdSpeculativeExecutor::Rate(
        const Gs2::Enchant::Request::FSetBalanceParameterStatusByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
