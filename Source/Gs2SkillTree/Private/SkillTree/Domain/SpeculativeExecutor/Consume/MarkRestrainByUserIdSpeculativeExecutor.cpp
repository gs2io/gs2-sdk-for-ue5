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

#include "SkillTree/Domain/SpeculativeExecutor/Consume/MarkRestrainByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "SkillTree/Domain/Gs2SkillTree.h"

namespace Gs2::SkillTree::Domain::SpeculativeExecutor
{

    FString FMarkRestrainByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2SkillTree:MarkRestrainByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FMarkRestrainByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request,
        Gs2::SkillTree::Model::FStatusPtr Item
    )
    {
        const auto NewNodeNames = Item->GetReleasedNodeNames()->FilterByPredicate([Request](FString V)
        {
            return !Request->GetNodeModelNames()->Contains(V);
        });
        Item->WithReleasedNodeNames(MakeShared<TArray<FString>>(NewNodeNames));
        return nullptr;
    }

    FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->SkillTree->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Status(
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
            FString("Status")
        );
        const auto Key = Model::FStatusDomain::CreateCacheKey(
            Request->GetPropertyId()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                SkillTree::Model::FStatus::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FMarkRestrainByUserIdSpeculativeExecutor::FCommitTask>> FMarkRestrainByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::SkillTree::Domain::FGs2SkillTreeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr FMarkRestrainByUserIdSpeculativeExecutor::Rate(
        const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr FMarkRestrainByUserIdSpeculativeExecutor::Rate(
        const Gs2::SkillTree::Request::FMarkRestrainByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
