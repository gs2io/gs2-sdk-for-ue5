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

#include "Stamina/Domain/SpeculativeExecutor/Acquire/RaiseMaxValueByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{

    FString FRaiseMaxValueByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Stamina:RaiseMaxValueByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FRaiseMaxValueByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr& Request,
        Gs2::Stamina::Model::FStaminaPtr Item
    )
    {
        Item->WithMaxValue(*Item->GetMaxValue() + *Request->GetRaiseValue());
        return nullptr;
    }

    FRaiseMaxValueByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FRaiseMaxValueByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRaiseMaxValueByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Stamina->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Stamina(
                Request->GetStaminaName().IsSet() ? *Request->GetStaminaName() : FString("")
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
            FString("Stamina")
        );
        const auto Key = Model::FStaminaDomain::CreateCacheKey(
            Request->GetStaminaName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Stamina::Model::FStamina::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRaiseMaxValueByUserIdSpeculativeExecutor::FCommitTask>> FRaiseMaxValueByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr FRaiseMaxValueByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetRaiseValue().IsSet())
        {
            Request->WithRaiseValue(*Request->GetRaiseValue() * Rate);
        }
        return Request;
    }

    Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr FRaiseMaxValueByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FRaiseMaxValueByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetRaiseValue().IsSet())
        {
            Rate.Multiply(*Request->GetRaiseValue());
            Request->WithRaiseValue(Rate.ToInt());
        }
        return Request;
    }
}
