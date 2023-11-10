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

#include "Dictionary/Domain/SpeculativeExecutor/Consume/VerifyEntryByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Dictionary::Domain::SpeculativeExecutor
{

    FString FVerifyEntryByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Dictionary:VerifyEntryByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEntryByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request,
        TSharedRef<TArray<Gs2::Dictionary::Model::FEntryPtr>> Items
    )
    {
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "havent")
            {
                if (Items->ContainsByPredicate([Request](Gs2::Dictionary::Model::FEntryPtr V)
                {
                    return V->GetName() == Request->GetEntryModelName();
                }))
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("entryModelName", "invalid", ""));
                        return Arr;
                    }());
                }
            } else if (*Request->GetVerifyType() == "have")
            {
                if (!Items->ContainsByPredicate([Request](Gs2::Dictionary::Model::FEntryPtr V)
                {
                    return V->GetName() == Request->GetEntryModelName();
                }))
                {
                    return MakeShared<Gs2::Core::Model::FBadRequestError>([]
                    {
                        auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                        Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("entryModelName", "invalid", ""));
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

    FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        const auto It = Domain->Dictionary->Namespace(
                Request->GetNamespaceName().IsSet() ? *Request->GetNamespaceName() : FString("")
            )->AccessToken(
                AccessToken
            )->Entries();
        auto Items = MakeShared<TArray<Gs2::Dictionary::Model::FEntryPtr>>();
        for (auto Item : *It)
        {
            if (Item->IsError())
            {
                return Item->Error();
            }
            Items->Add(Item->Current());
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

    TSharedPtr<FAsyncTask<FVerifyEntryByUserIdSpeculativeExecutor::FCommitTask>> FVerifyEntryByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr FVerifyEntryByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr FVerifyEntryByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FVerifyEntryByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
