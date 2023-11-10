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

#include "Inventory/Domain/SpeculativeExecutor/Consume/VerifyBigItemByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FVerifyBigItemByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifyBigItemByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyBigItemByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request,
        Gs2::Inventory::Model::FBigItemPtr Item
    )
    {
        if (Request->GetVerifyType().IsSet()) {
            TBigInt<1024, false> Count;
            TBigInt<1024, false> VerifyCount;
            Count.Parse(*Item->GetCount());
            VerifyCount.Parse(*Request->GetCount());
            if (*Request->GetVerifyType() == "less")
            {
                if (Count >= VerifyCount)
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "lessEqual")
            {
                if (Count > VerifyCount)
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "greater")
            {
                if (Count <= VerifyCount)
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "greaterEqual")
            {
                if (Count > VerifyCount)
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "equal")
            {
                if (Count != VerifyCount)
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "notEqual")
            {
                if (Count == VerifyCount)
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
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

    FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Inventory->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->BigInventory(
                Request->GetInventoryName().IsSet() ? *Request->GetInventoryName() : FString("")
            )->BigItem(
                Request->GetItemName().IsSet() ? *Request->GetItemName() : FString("")
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

    TSharedPtr<FAsyncTask<FVerifyBigItemByUserIdSpeculativeExecutor::FCommitTask>> FVerifyBigItemByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr FVerifyBigItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr FVerifyBigItemByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyBigItemByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
