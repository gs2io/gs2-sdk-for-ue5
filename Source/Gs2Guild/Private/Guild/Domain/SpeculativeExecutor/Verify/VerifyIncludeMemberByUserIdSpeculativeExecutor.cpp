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

#include "Guild/Domain/SpeculativeExecutor/Verify/VerifyIncludeMemberByUserIdSpeculativeExecutor.h"
#include "Guild/Model/Cache/Guild.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
namespace Gs2::Guild::Domain::SpeculativeExecutor
{
namespace
{
    bool GuildVerifyIncludeMemberPredicate(const Gs2::Guild::Model::FGuildPtr& Item, const FString& ExpectedId,
        const FString& GuildModelName, const FString& GuildName, const FString& RequestUserId, const FString& VerifyType)
    {
        if (!Item.IsValid() || !Item->GetGuildId().IsSet() || Item->GetGuildId().Get(FString()) != ExpectedId ||
            !Item->GetGuildModelName().IsSet() || Item->GetGuildModelName().Get(FString()) != GuildModelName ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != GuildName || !Item->GetMembers().IsValid()) return false;
        bool Included = false;
        for (const auto& Member : *Item->GetMembers())
        {
            if (Member.IsValid() && Member->GetUserId().IsSet() && Member->GetUserId().Get(FString()) == RequestUserId) { Included = true; break; }
        }
        if (VerifyType == TEXT("include")) return Included;
        if (VerifyType == TEXT("notInclude")) return !Included;
        return false;
    }
}
    FString FVerifyIncludeMemberByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Guild:VerifyIncludeMemberByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyIncludeMemberByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr& Request,
        Gs2::Guild::Model::FGuildPtr Item
    )
    {
        bool Included = false;
        for (const auto& Member : *Item->GetMembers())
        {
            if (Member.IsValid() && Member->GetUserId().IsSet() &&
                Member->GetUserId().Get(FString()) == Request->GetUserId().Get(FString()))
            {
                Included = true;
                break;
            }
        }
        const FString Type = Request->GetVerifyType().Get(FString());
        const bool Satisfied = (Type == TEXT("include") && Included) ||
            (Type == TEXT("notInclude") && !Included);
        if (Satisfied) return nullptr;
        return MakeShared<Gs2::Core::Model::FBadRequestError>([]
        {
            auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("userId", "invalid", ""));
            return Details;
        }());
    }

    FVerifyIncludeMemberByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr& Request
    ):
        Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
    {

    }

    FVerifyIncludeMemberByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
        Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyIncludeMemberByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGuildModelName().IsSet() || PreparedRequest->GetGuildModelName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGuildName().IsSet() || PreparedRequest->GetGuildName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() || !PreparedRequest->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("include") && VerifyType != TEXT("notInclude")) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString());
        const FString GuildModelName = PreparedRequest->GetGuildModelName().Get(FString());
        const FString GuildName = PreparedRequest->GetGuildName().Get(FString());
        const FString RequestUserId = PreparedRequest->GetUserId().Get(FString());
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:guild:%s:guild:%s:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *GuildModelName, *GuildName);
        Gs2::Guild::Model::FGuildPtr Cached;
        if (!Gs2::Guild::Model::Cache::FGuildCache::TryGet(Domain->Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetGuildId().IsSet() || Cached->GetGuildId().Get(FString()) != ExpectedId ||
            !Cached->GetGuildModelName().IsSet() || Cached->GetGuildModelName().Get(FString()) != GuildModelName ||
            !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != GuildName ||
            !Cached->GetMembers().IsValid()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, ExpectedId, RequestUserId, VerifyType]()
        {
            Gs2::Guild::Model::FGuildPtr Current;
            if (!Gs2::Guild::Model::Cache::FGuildCache::TryGet(Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return GuildVerifyIncludeMemberPredicate(Current, ExpectedId, GuildModelName, GuildName, RequestUserId, VerifyType);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyIncludeMemberByUserIdSpeculativeExecutor::FCommitTask>> FVerifyIncludeMemberByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyIncludeMemberByUserIdSpeculativeExecutor::FCommitTask>> FVerifyIncludeMemberByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = MakeShared<Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequest>(*Request);
        if (!Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("include")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notInclude")));
        else if (*Inverse->GetVerifyType() == TEXT("notInclude")) Inverse->WithVerifyType(TOptional<FString>(TEXT("include")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr FVerifyIncludeMemberByUserIdSpeculativeExecutor::Rate(
        const Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr FVerifyIncludeMemberByUserIdSpeculativeExecutor::Rate(
        const Gs2::Guild::Request::FVerifyIncludeMemberByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
