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
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Schedule/Domain/SpeculativeExecutor/Acquire/ExtendTriggerByUserIdSpeculativeExecutor.h"
#include "Schedule/Domain/Gs2Schedule.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Schedule::Domain::SpeculativeExecutor
{

    FString FExtendTriggerByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Schedule:ExtendTriggerByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FExtendTriggerByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
        Gs2::Schedule::Model::FTriggerPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Schedule->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Trigger(
                Request->GetTriggerName().IsSet() ? *Request->GetTriggerName() : FString("")
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
            FString("Trigger")
        );
        const auto Key = Model::FTriggerDomain::CreateCacheKey(
            Request->GetTriggerName()
        );

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            Domain->Cache->Put(
                Schedule::Model::FTrigger::TypeName,
                ParentKey,
                Key,
                Item,
                FDateTime::Now() + FTimespan::FromSeconds(10)
            );
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FExtendTriggerByUserIdSpeculativeExecutor::FCommitTask>> FExtendTriggerByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Schedule::Domain::FGs2ScheduleDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr FExtendTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetExtendSeconds().IsSet())
        {
            Request->WithExtendSeconds(*Request->GetExtendSeconds() * Rate);
        }
        return Request;
    }

    Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr FExtendTriggerByUserIdSpeculativeExecutor::Rate(
        const Gs2::Schedule::Request::FExtendTriggerByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetExtendSeconds().IsSet())
        {
            Rate.Multiply(*Request->GetExtendSeconds());
            Request->WithExtendSeconds(Rate.ToInt());
        }
        return Request;
    }
}
