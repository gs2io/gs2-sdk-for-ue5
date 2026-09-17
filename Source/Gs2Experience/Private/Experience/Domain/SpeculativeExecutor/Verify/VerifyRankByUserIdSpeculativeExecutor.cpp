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

#include "Experience/Domain/SpeculativeExecutor/Verify/VerifyRankByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"
#include "Experience/Model/Cache/Status.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{
namespace
{
bool ExperienceVerifyRankPredicate(const Gs2::Experience::Model::FStatusPtr& Item, const FString& ExpectedId,
    const FString& UserId, const FString& ExperienceName, const FString& PropertyId,
    const FString& VerifyType, const int64 RequestValue)
{
    if (!Item.IsValid() || !Item->GetStatusId().IsSet() || Item->GetStatusId().Get(FString()) != ExpectedId ||
        !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
        !Item->GetExperienceName().IsSet() || Item->GetExperienceName().Get(FString()) != ExperienceName ||
        !Item->GetPropertyId().IsSet() || Item->GetPropertyId().Get(FString()) != PropertyId ||
        !Item->GetRankValue().IsSet()) return false;
    const int64 Current = Item->GetRankValue().Get(0);
    if (VerifyType == TEXT("less")) return Current < RequestValue;
    if (VerifyType == TEXT("lessEqual")) return Current <= RequestValue;
    if (VerifyType == TEXT("greater")) return Current > RequestValue;
    if (VerifyType == TEXT("greaterEqual")) return Current >= RequestValue;
    if (VerifyType == TEXT("equal")) return Current == RequestValue;
    if (VerifyType == TEXT("notEqual")) return Current != RequestValue;
    return false;
}
}

    FString FVerifyRankByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Experience:VerifyRankByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyRankByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr& Request,
        Gs2::Experience::Model::FStatusPtr Item)
    {
        bool Satisfied = false;
        if (Item.IsValid() && Item->GetRankValue().IsSet())
        {
            const int64 Current = Item->GetRankValue().Get(0);
            const int64 Expected = Request->GetRankValue().Get(0);
            const auto Type = Request->GetVerifyType().Get(FString());
            if (Type == TEXT("less")) Satisfied = Current < Expected;
            else if (Type == TEXT("lessEqual")) Satisfied = Current <= Expected;
            else if (Type == TEXT("greater")) Satisfied = Current > Expected;
            else if (Type == TEXT("greaterEqual")) Satisfied = Current >= Expected;
            else if (Type == TEXT("equal")) Satisfied = Current == Expected;
            else if (Type == TEXT("notEqual")) Satisfied = Current != Expected;
        }
        if (Satisfied) return nullptr;
        return MakeShared<Gs2::Core::Model::FBadRequestError>([]
        {
            auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankValue", "invalid", ""));
            return Arr;
        }());
    }

    FVerifyRankByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyRankByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyRankByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr Token = nullptr;
        if (AccessToken.IsValid()) Token = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr Prepared = nullptr;
        if (Request.IsValid()) Prepared = MakeShared<Gs2::Experience::Request::FVerifyRankByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Token.IsValid() || !Prepared.IsValid() ||
            !Token->GetUserId().IsSet() || Token->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (Prepared->GetUserId().IsSet() && Prepared->GetUserId().Get(FString()) == TEXT("#{userId}"))
            Prepared->WithUserId(Token->GetUserId());
        if (!Prepared->GetUserId().IsSet() || Prepared->GetUserId().Get(FString()) != Token->GetUserId().Get(FString()) ||
            !Prepared->GetNamespaceName().IsSet() || Prepared->GetNamespaceName().Get(FString()).IsEmpty() ||
            !Prepared->GetExperienceName().IsSet() || Prepared->GetExperienceName().Get(FString()).IsEmpty() ||
            !Prepared->GetPropertyId().IsSet() || Prepared->GetPropertyId().Get(FString()).IsEmpty()) return nullptr;
        const auto NamespaceName = Prepared->GetNamespaceName();
        const FString UserId = Token->GetUserId().Get(FString());
        const FString ExperienceName = Prepared->GetExperienceName().Get(FString());
        const FString PropertyId = Prepared->GetPropertyId().Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *UserId);
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:experience:%s:user:%s:experienceModel:%s:property:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
            *UserId, *ExperienceName, *PropertyId);
        const auto TimeOffset = Token->GetTimeOffset();
        const FString VerifyType = Prepared->GetVerifyType().Get(FString());
        const int64 RequestValue = Prepared->GetRankValue().Get(0);
        Gs2::Experience::Model::FStatusPtr Cached;
        if (!Gs2::Experience::Model::Cache::FStatusCache::TryGet(
            Domain->Cache, NamespaceName, UserId, ExperienceName, PropertyId, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetStatusId().IsSet() || Cached->GetStatusId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetExperienceName().IsSet() || Cached->GetExperienceName().Get(FString()) != ExperienceName ||
            !Cached->GetPropertyId().IsSet() || Cached->GetPropertyId().Get(FString()) != PropertyId) return nullptr;
        if (const auto Error = Transform(Domain, Token, Prepared, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, ExperienceName, PropertyId, TimeOffset,
            ExpectedId, VerifyType, RequestValue]()
        {
            Gs2::Experience::Model::FStatusPtr Current;
            if (!Gs2::Experience::Model::Cache::FStatusCache::TryGet(
                Cache, NamespaceName, UserId, ExperienceName, PropertyId, TimeOffset, &Current) || !Current.IsValid()) return false;
            return ExperienceVerifyRankPredicate(Current, ExpectedId, UserId, ExperienceName, PropertyId, VerifyType, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyRankByUserIdSpeculativeExecutor::FCommitTask>> FVerifyRankByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyRankByUserIdSpeculativeExecutor::FCommitTask>> FVerifyRankByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Experience::Request::FVerifyRankByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        const auto Type = *Inverse->GetVerifyType();
        if (Type == TEXT("less")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greaterEqual")));
        else if (Type == TEXT("lessEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greater")));
        else if (Type == TEXT("greater")) Inverse->WithVerifyType(TOptional<FString>(TEXT("lessEqual")));
        else if (Type == TEXT("greaterEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("less")));
        else if (Type == TEXT("equal")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notEqual")));
        else if (Type == TEXT("notEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("equal")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr FVerifyRankByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetRankValue().Get(0), Rate, Value))
        {
            return Request;
        }
        Request->WithRankValue(Value);
        return Request;
    }

    Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr FVerifyRankByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FVerifyRankByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetRankValue().Get(0), Rate, Value))
        {
            return Request;
        }
        Request->WithRankValue(Value);
        return Request;
    }
}
