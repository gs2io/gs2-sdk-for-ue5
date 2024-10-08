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

#include "Dictionary/Domain/SpeculativeExecutor/Consume/DeleteEntriesByUserIdSpeculativeExecutor.h"
#include "Dictionary/Domain/Gs2Dictionary.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Dictionary::Domain::SpeculativeExecutor
{

    FString FDeleteEntriesByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Dictionary:DeleteEntriesByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteEntriesByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request,
        Gs2::Dictionary::Model::FEntryPtr Item
    )
    {
        return nullptr;
    }

    FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<TFunction<void()>>> Result
    )
    {
        *Result = MakeShared<TFunction<void()>>([&]()
        {
            if (!Request->GetEntryModelNames()->IsEmpty())
            {
                for (auto EntryModelName : *Request->GetEntryModelNames())
                {
                    const auto ParentKey = Model::FUserDomain::CreateCacheParentKey(
                        Request->GetNamespaceName(),
                        AccessToken->GetUserId(),
                        FString("Entry")
                    );
                    const auto Key = Model::FEntryDomain::CreateCacheKey(
                        EntryModelName
                    );

                    Domain->Cache->Put(
                        Dictionary::Model::FEntry::TypeName,
                        ParentKey,
                        Key,
                        nullptr,
                        FDateTime::Now() + FTimespan::FromSeconds(10)
                    );
                }
            }
            return nullptr;
        });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteEntriesByUserIdSpeculativeExecutor::FCommitTask>> FDeleteEntriesByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr FDeleteEntriesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr FDeleteEntriesByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FDeleteEntriesByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
