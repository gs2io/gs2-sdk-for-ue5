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

#include "Stamina/Domain/SpeculativeExecutor/Acquire/RecoverStaminaByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{

    FString FRecoverStaminaByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Stamina:RecoverStaminaByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverStaminaByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr& Request,
        Gs2::Stamina::Model::FStaminaModelPtr Model,
        Gs2::Stamina::Model::FStaminaPtr Item
    )
    {
        Item->WithValue(*Item->GetValue() + *Request->GetRecoverValue());
        if (*Item->GetValue() > *Item->GetMaxValue()) {
            Item->WithOverflowValue(*Item->GetValue() - *Item->GetMaxValue());

            if (*Item->GetValue() > *Model->GetMaxCapacity()) {
                Item->WithOverflowValue(*Model->GetMaxCapacity() - *Item->GetValue());
                Item->WithValue(Model->GetMaxCapacity());
            }
        }
        return nullptr;
    }

    FRecoverStaminaByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FRecoverStaminaByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRecoverStaminaByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Stamina->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->StaminaModel(
                Request->GetStaminaName().IsSet() ? *Request->GetStaminaName() : FString("")
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Model = Future->GetTask().Result();

        if (!Model.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
        }
        
        const auto Future2 = Domain->Stamina->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Stamina(
                Request->GetStaminaName().IsSet() ? *Request->GetStaminaName() : FString("")
            )->Model();
        Future2->StartSynchronousTask();
        if (Future2->GetTask().IsError())
        {
            return Future2->GetTask().Error();
        }
        auto Item = Future2->GetTask().Result();

        if (!Item.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
        }
        
        auto Err = Transform(Domain, AccessToken, Request, Model, Item);
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

    TSharedPtr<FAsyncTask<FRecoverStaminaByUserIdSpeculativeExecutor::FCommitTask>> FRecoverStaminaByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr FRecoverStaminaByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetRecoverValue().IsSet())
        {
            Request->WithRecoverValue(*Request->GetRecoverValue() * Rate);
        }
        return Request;
    }

    Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr FRecoverStaminaByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FRecoverStaminaByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetRecoverValue().IsSet())
        {
            Rate.Multiply(*Request->GetRecoverValue());
            Request->WithRecoverValue(Rate.ToInt());
        }
        return Request;
    }
}
