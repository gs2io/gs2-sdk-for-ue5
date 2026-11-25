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

#include "Friend/Domain/SpeculativeExecutor/Verify/VerifyFriendByUserIdSpeculativeExecutor.h"
#include "Friend/Domain/Gs2Friend.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Friend::Domain::SpeculativeExecutor
{

    FString FVerifyFriendByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Friend:VerifyFriendByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyFriendByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr& Request,
        Gs2::Friend::Model::FFriendPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        if (Request->GetVerifyType().IsSet()) {
            if (*Request->GetVerifyType() == "include")
            {
            } else if (*Request->GetVerifyType() == "notInclude")
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

    FVerifyFriendByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Friend::Domain::FGs2FriendDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyFriendByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyFriendByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        // ドメインの無いモデル (Friend の Friend・Follow など) は手元で読めない。
        // Result を空のまま返し、サーバーに判定を任せる。
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyFriendByUserIdSpeculativeExecutor::FCommitTask>> FVerifyFriendByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Friend::Domain::FGs2FriendDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr FVerifyFriendByUserIdSpeculativeExecutor::Rate(
        const Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr FVerifyFriendByUserIdSpeculativeExecutor::Rate(
        const Gs2::Friend::Request::FVerifyFriendByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
