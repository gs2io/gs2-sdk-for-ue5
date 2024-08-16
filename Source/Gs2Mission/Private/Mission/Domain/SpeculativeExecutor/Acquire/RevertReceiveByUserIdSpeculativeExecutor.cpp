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

#include "Mission/Domain/SpeculativeExecutor/Acquire/RevertReceiveByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Mission/Domain/Gs2Mission.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{

    FString FRevertReceiveByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Mission:RevertReceiveByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FRevertReceiveByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request,
        Gs2::Mission::Model::FCompletePtr Item
    )
    {
        auto ReceivedMissionTaskNames = Item->GetReceivedMissionTaskNames()->FilterByPredicate([Request](FString V)
        {
            return V != *Request->GetMissionTaskName();
        });
        Item->WithReceivedMissionTaskNames(MakeShared<TArray<FString>>(ReceivedMissionTaskNames));
        return nullptr;
    }

    FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Mission->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Complete(
                Request->GetMissionGroupName().IsSet() ? *Request->GetMissionGroupName() : FString("")
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
            FString("Complete")
        );
        const auto Key = Model::FCompleteDomain::CreateCacheKey(
            Request->GetMissionGroupName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Mission::Model::FComplete::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FRevertReceiveByUserIdSpeculativeExecutor::FCommitTask>> FRevertReceiveByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr FRevertReceiveByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr FRevertReceiveByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FRevertReceiveByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
