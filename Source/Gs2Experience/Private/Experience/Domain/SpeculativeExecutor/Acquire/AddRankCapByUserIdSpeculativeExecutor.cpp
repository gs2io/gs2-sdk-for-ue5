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

#include "Experience/Domain/SpeculativeExecutor/Acquire/AddRankCapByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{

    FString FAddRankCapByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Experience:AddRankCapByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddRankCapByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request,
        Gs2::Experience::Model::FExperienceModelPtr Model,
        Gs2::Experience::Model::FStatusPtr Item
    )
    {
        const auto RankCapValue = Item->GetRankCapValue().IsSet() ? *Item->GetRankCapValue() : 0;
        Item->WithRankCapValue(RankCapValue + *Request->GetRankCapValue());
        if (*Item->GetRankCapValue() > *Model->GetMaxRankCap())
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FAddRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddRankCapByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Experience->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->ExperienceModel(
                Request->GetExperienceName().IsSet() ? *Request->GetExperienceName() : FString("")
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
        
        const auto Future2 = Domain->Experience->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Status(
                Request->GetExperienceName().IsSet() ? *Request->GetExperienceName() : FString(""),
                Request->GetPropertyId().IsSet() ? *Request->GetPropertyId() : FString("")
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

    TSharedPtr<FAsyncTask<FAddRankCapByUserIdSpeculativeExecutor::FCommitTask>> FAddRankCapByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr FAddRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetRankCapValue().IsSet())
        {
            Request->WithRankCapValue(*Request->GetRankCapValue() * Rate);
        }
        return Request;
    }

    Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr FAddRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetRankCapValue().IsSet())
        {
            Rate.Multiply(*Request->GetRankCapValue());
            Request->WithRankCapValue(Rate.ToInt());
        }
        return Request;
    }
}
