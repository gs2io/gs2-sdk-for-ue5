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

#include "Dictionary/Domain/SpeculativeExecutor/Verify/VerifyEntryCountByUserIdSpeculativeExecutor.h"
#include "Dictionary/Domain/Gs2Dictionary.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Dictionary::Domain::SpeculativeExecutor
{

    FString FVerifyEntryCountByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Dictionary:VerifyEntryCountByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEntryCountByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr& Request,
        Gs2::Dictionary::Model::FEntryPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "less")
            {
            } else if (*Request->GetVerifyType() == "lessEqual")
            {
            } else if (*Request->GetVerifyType() == "greater")
            {
            } else if (*Request->GetVerifyType() == "greaterEqual")
            {
            } else if (*Request->GetVerifyType() == "equal")
            {
            } else if (*Request->GetVerifyType() == "notEqual")
            {
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

    FVerifyEntryCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyEntryCountByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyEntryCountByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        // ドメインの無いモデル (Friend の Friend・Follow など) は手元で読めない。
        // Result を空のまま返し、サーバーに判定を任せる。
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyEntryCountByUserIdSpeculativeExecutor::FCommitTask>> FVerifyEntryCountByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Dictionary::Domain::FGs2DictionaryDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr FVerifyEntryCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr FVerifyEntryCountByUserIdSpeculativeExecutor::Rate(
        const Gs2::Dictionary::Request::FVerifyEntryCountByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
