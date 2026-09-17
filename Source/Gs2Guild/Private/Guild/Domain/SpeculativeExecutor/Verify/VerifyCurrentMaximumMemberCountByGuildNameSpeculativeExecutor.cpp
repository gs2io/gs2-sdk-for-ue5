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

#include "Guild/Domain/SpeculativeExecutor/Verify/VerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor.h"
#include "Guild/Model/Cache/Guild.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
namespace Gs2::Guild::Domain::SpeculativeExecutor
{
namespace
{
    bool GuildVerifyMaximumPredicate(const Gs2::Guild::Model::FGuildPtr& Item, const FString& ExpectedId,
        const FString& GuildModelName, const FString& GuildName, const FString& VerifyType, const int32 RequestValue)
    {
        if (!Item.IsValid() || !Item->GetGuildId().IsSet() || Item->GetGuildId().Get(FString()) != ExpectedId ||
            !Item->GetGuildModelName().IsSet() || Item->GetGuildModelName().Get(FString()) != GuildModelName ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != GuildName || !Item->GetCurrentMaximumMemberCount().IsSet()) return false;
        const int32 Current = Item->GetCurrentMaximumMemberCount().Get(0);
        if (VerifyType == TEXT("less")) return Current < RequestValue;
        if (VerifyType == TEXT("lessEqual")) return Current <= RequestValue;
        if (VerifyType == TEXT("greater")) return Current > RequestValue;
        if (VerifyType == TEXT("greaterEqual")) return Current >= RequestValue;
        if (VerifyType == TEXT("equal")) return Current == RequestValue;
        if (VerifyType == TEXT("notEqual")) return Current != RequestValue;
        return false;
    }
}
    FString FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Action()
    {
        return FString("Gs2Guild:VerifyCurrentMaximumMemberCountByGuildName");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr& Request,
        Gs2::Guild::Model::FGuildPtr Item
    )
    {
        const int32 Current = Item->GetCurrentMaximumMemberCount().Get(0);
        const int32 Expected = Request->GetValue().Get(0);
        const FString Type = Request->GetVerifyType().Get(FString());
        const bool Satisfied =
            (Type == TEXT("less") && Current < Expected) ||
            (Type == TEXT("lessEqual") && Current <= Expected) ||
            (Type == TEXT("greater") && Current > Expected) ||
            (Type == TEXT("greaterEqual") && Current >= Expected) ||
            (Type == TEXT("equal") && Current == Expected) ||
            (Type == TEXT("notEqual") && Current != Expected);
        if (Satisfied) return nullptr;
        return MakeShared<Gs2::Core::Model::FBadRequestError>([]
        {
            auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("value", "invalid", ""));
            return Details;
        }());
    }

    FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr& Request
    ):
        Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
    {

    }

    FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
        Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid()) return nullptr;
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGuildModelName().IsSet() || PreparedRequest->GetGuildModelName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGuildName().IsSet() || PreparedRequest->GetGuildName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() || !PreparedRequest->GetValue().IsSet()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("less") && VerifyType != TEXT("lessEqual") && VerifyType != TEXT("greater") && VerifyType != TEXT("greaterEqual") && VerifyType != TEXT("equal") && VerifyType != TEXT("notEqual")) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString()), GuildModelName = PreparedRequest->GetGuildModelName().Get(FString()), GuildName = PreparedRequest->GetGuildName().Get(FString());
        const int32 RequestValue = PreparedRequest->GetValue().Get(0); const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:guild:%s:guild:%s:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *GuildModelName, *GuildName);
        Gs2::Guild::Model::FGuildPtr Cached;
        if (!Gs2::Guild::Model::Cache::FGuildCache::TryGet(Domain->Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetGuildId().IsSet() || Cached->GetGuildId().Get(FString()) != ExpectedId ||
            !Cached->GetGuildModelName().IsSet() || Cached->GetGuildModelName().Get(FString()) != GuildModelName ||
            !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != GuildName ||
            !Cached->GetCurrentMaximumMemberCount().IsSet()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, ExpectedId, VerifyType, RequestValue]()
        {
            Gs2::Guild::Model::FGuildPtr Current;
            if (!Gs2::Guild::Model::Cache::FGuildCache::TryGet(Cache, NamespaceName, GuildModelName, GuildName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return GuildVerifyMaximumPredicate(Current, ExpectedId, GuildModelName, GuildName, VerifyType, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask>> FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::FCommitTask>> FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Guild::Domain::FGs2GuildDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = MakeShared<Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequest>(*Request);
        if (!Inverse->GetVerifyType().IsSet()) return nullptr;
        if (*Inverse->GetVerifyType() == TEXT("less")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greaterEqual")));
        else if (*Inverse->GetVerifyType() == TEXT("lessEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greater")));
        else if (*Inverse->GetVerifyType() == TEXT("greater")) Inverse->WithVerifyType(TOptional<FString>(TEXT("lessEqual")));
        else if (*Inverse->GetVerifyType() == TEXT("greaterEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("less")));
        else if (*Inverse->GetVerifyType() == TEXT("equal")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notEqual")));
        else if (*Inverse->GetVerifyType() == TEXT("notEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("equal")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Rate(
        const Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr FVerifyCurrentMaximumMemberCountByGuildNameSpeculativeExecutor::Rate(
        const Gs2::Guild::Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
