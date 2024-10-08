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

#include "Inventory/Domain/SpeculativeExecutor/Verify/VerifyItemSetByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Inventory/Domain/Gs2Inventory.h"

namespace Gs2::Inventory::Domain::SpeculativeExecutor
{

    FString FVerifyItemSetByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Inventory:VerifyItemSetByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyItemSetByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request,
        TSharedPtr<TArray<Gs2::Inventory::Model::FItemSetPtr>> Items
    )
    {
        if (Request->GetVerifyType().IsSet()) {
            auto Sum = 0;
            for (auto Item : *Items)
            {
                Sum += *Item->GetCount();
            }
            if (*Request->GetVerifyType() == "less")
            {
                if (Sum >= *Request->GetCount())
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
                if (Sum > *Request->GetCount())
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
                if (Sum <= *Request->GetCount())
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
                if (Sum > *Request->GetCount())
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
                if (Sum != *Request->GetCount())
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
                if (Sum == *Request->GetCount())
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

    FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto Future = Domain->Inventory->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Inventory(
                Request->GetInventoryName().IsSet() ? *Request->GetInventoryName() : FString("")
            )->ItemSet(
                Request->GetItemName().IsSet() ? *Request->GetItemName() : FString(""),
                Request->GetItemSetName()
            )->Model();
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            return Future->GetTask().Error();
        }
        auto Items = Future->GetTask().Result();

        if (!Items.IsValid())
        {
            *Result = MakeShared<TFunction<void()>>([&]()
            {
                return nullptr;
            });
            return nullptr;
        }
        auto Err = Transform(Domain, AccessToken, Request, Items);
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

    TSharedPtr<FAsyncTask<FVerifyItemSetByUserIdSpeculativeExecutor::FCommitTask>> FVerifyItemSetByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Inventory::Domain::FGs2InventoryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr FVerifyItemSetByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr FVerifyItemSetByUserIdSpeculativeExecutor::Rate(
        const Gs2::Inventory::Request::FVerifyItemSetByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
