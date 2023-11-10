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

#include "Experience/Domain/SpeculativeExecutor/Consume/VerifyRankCapByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{

    FString FVerifyRankCapByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Experience:VerifyRankCapByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyRankCapByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr& Request,
        Gs2::Experience::Model::FStatusPtr Item
    )
    {
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "less")
            {
                if (*Item->GetRankCapValue() >= *Request->GetRankCapValue())
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "lessEqual")
            {
                if (*Item->GetRankCapValue() > *Request->GetRankCapValue())
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "greater")
            {
                if (*Item->GetRankCapValue() <= *Request->GetRankCapValue())
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "greaterEqual")
            {
                if (*Item->GetRankCapValue() > *Request->GetRankCapValue())
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "equal")
            {
                if (*Item->GetRankCapValue() != *Request->GetRankCapValue())
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "notEqual")
            {
                if (*Item->GetRankCapValue() == *Request->GetRankCapValue())
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                        return Arr;
                    }());
                }
            } else {
                return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                {
                    auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                    Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("verifyType", "invalid", ""));
                    return Arr;
                }());
            }
        }
        return nullptr;
    }

    FVerifyRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyRankCapByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Experience->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Status(
                Request->GetExperienceName().IsSet() ? *Request->GetExperienceName() : FString(""),
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

        *Result = MakeShared<TFunction<void()>>([&]()
        {
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyRankCapByUserIdSpeculativeExecutor::FCommitTask>> FVerifyRankCapByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr FVerifyRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr FVerifyRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FVerifyRankCapByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
