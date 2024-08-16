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

#include "Formation/Domain/SpeculativeExecutor/Acquire/AddMoldCapacityByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Formation/Domain/Gs2Formation.h"

namespace Gs2::Formation::Domain::SpeculativeExecutor
{

    FString FAddMoldCapacityByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Formation:AddMoldCapacityByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddMoldCapacityByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request,
        Gs2::Formation::Model::FMoldPtr Item
    )
    {
        Item->WithCapacity(*Item->GetCapacity() + *Request->GetCapacity());
        return nullptr;
    }

    FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Formation->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Mold(
                Request->GetMoldModelName().IsSet() ? *Request->GetMoldModelName() : FString("")
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
            FString("Mold")
        );
        const auto Key = Model::FMoldDomain::CreateCacheKey(
            Request->GetMoldModelName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Formation::Model::FMold::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAddMoldCapacityByUserIdSpeculativeExecutor::FCommitTask>> FAddMoldCapacityByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Formation::Domain::FGs2FormationDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr FAddMoldCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetCapacity().IsSet())
        {
            Request->WithCapacity(*Request->GetCapacity() * Rate);
        }
        return Request;
    }

    Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr FAddMoldCapacityByUserIdSpeculativeExecutor::Rate(
        const Gs2::Formation::Request::FAddMoldCapacityByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetCapacity().IsSet())
        {
            Rate.Multiply(*Request->GetCapacity());
            Request->WithCapacity(Rate.ToInt());
        }
        return Request;
    }
}
