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

#include "Quest/Domain/SpeculativeExecutor/Consume/DeleteProgressByUserIdSpeculativeExecutor.h"
#include "Quest/Domain/Gs2Quest.h"
#include "Quest/Model/Cache/Progress.h"

#include "Auth/Model/AccessToken.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Quest::Domain::SpeculativeExecutor
{

    namespace
    {
        using FProgress = Gs2::Quest::Model::FProgress;
        using FProgressPtr = Gs2::Quest::Model::FProgressPtr;
        using FProgressCache = Gs2::Quest::Model::Cache::FProgressCache;

        static FString ExpectedProgressId(const Gs2::Core::Domain::FGs2Ptr& Domain, const FString& NamespaceName, const FString& UserId)
        {
            return FString::Printf(TEXT("grn:gs2:%s:%s:quest:%s:user:%s:progress"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId);
        }

        static FString DeleteProgressSnapshot(const TSharedPtr<FJsonObject>& Json)
        {
            FString Result;
            const auto Writer = TJsonWriterFactory<>::Create(&Result);
            FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);
            return Result;
        }

    }

    FString FDeleteProgressByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Quest:DeleteProgressByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteProgressByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr& Request,
        Gs2::Quest::Model::FProgressPtr Item
    )
    {
        return nullptr;
    }

    FDeleteProgressByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Quest::Domain::FGs2QuestDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FDeleteProgressByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FDeleteProgressByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        const auto Prepared = Request.IsValid() ? Gs2::Quest::Request::FDeleteProgressByUserIdRequest::FromJson(Request->ToJson()) : nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedAccessToken;
        if (AccessToken.IsValid()) PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        if (Prepared.IsValid() && Prepared->GetUserId().IsSet() && *Prepared->GetUserId() == TEXT("#{userId}")) Prepared->WithUserId(PreparedAccessToken.IsValid() ? PreparedAccessToken->GetUserId() : TOptional<FString>());
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Prepared.IsValid() || !PreparedAccessToken.IsValid() || !PreparedAccessToken->GetUserId().IsSet() || PreparedAccessToken->GetUserId()->IsEmpty() || Prepared->GetUserId() != PreparedAccessToken->GetUserId() || !Prepared->GetNamespaceName().IsSet()) return nullptr;
        const auto UserId = *PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        FProgressPtr PreparedItem;
        if (!FProgressCache::TryGet(Domain->Cache, Prepared->GetNamespaceName(), UserId, TimeOffset, &PreparedItem) || !PreparedItem.IsValid() || !PreparedItem->GetProgressId().IsSet() || *PreparedItem->GetProgressId() != ExpectedProgressId(Domain, *Prepared->GetNamespaceName(), UserId) || !PreparedItem->GetUserId().IsSet() || *PreparedItem->GetUserId() != UserId) return nullptr;
        const FString PreparedSnapshot = DeleteProgressSnapshot(PreparedItem->ToJson());
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(MakeShared<TFunction<void()>>([DomainCopy = Domain, Prepared, UserId, TimeOffset, PreparedSnapshot]()
        {
            FProgressPtr Live;
            if (FProgressCache::TryGet(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, TimeOffset, &Live) && Live.IsValid() && DeleteProgressSnapshot(Live->ToJson()) == PreparedSnapshot) {
                FProgressCache::Put(DomainCopy->Cache, Prepared->GetNamespaceName(), UserId, TimeOffset, nullptr);
            }
        }));
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FDeleteProgressByUserIdSpeculativeExecutor::FCommitTask>> FDeleteProgressByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Quest::Domain::FGs2QuestDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr FDeleteProgressByUserIdSpeculativeExecutor::Rate(
        const Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr FDeleteProgressByUserIdSpeculativeExecutor::Rate(
        const Gs2::Quest::Request::FDeleteProgressByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
