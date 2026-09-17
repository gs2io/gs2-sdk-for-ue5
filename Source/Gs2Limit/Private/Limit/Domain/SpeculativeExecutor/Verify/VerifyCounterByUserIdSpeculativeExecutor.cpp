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

#include "Limit/Domain/SpeculativeExecutor/Verify/VerifyCounterByUserIdSpeculativeExecutor.h"
#include "Limit/Model/Cache/Counter.h"
#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"
namespace Gs2::Limit::Domain::SpeculativeExecutor
{
namespace
{
    bool LimitVerifyCounterPredicate(const Gs2::Limit::Model::FCounterPtr& Item, const FString& ExpectedId,
        const FString& UserId, const FString& LimitName, const FString& CounterName, const FString& VerifyType, const int32 RequestValue)
    {
        if (!Item.IsValid() || !Item->GetCounterId().IsSet() || Item->GetCounterId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetLimitName().IsSet() || Item->GetLimitName().Get(FString()) != LimitName ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != CounterName || !Item->GetCount().IsSet()) return false;
        const int32 Current = Item->GetCount().Get(0);
        if (VerifyType == TEXT("less")) return Current < RequestValue;
        if (VerifyType == TEXT("lessEqual")) return Current <= RequestValue;
        if (VerifyType == TEXT("greater")) return Current > RequestValue;
        if (VerifyType == TEXT("greaterEqual")) return Current >= RequestValue;
        if (VerifyType == TEXT("equal")) return Current == RequestValue;
        if (VerifyType == TEXT("notEqual")) return Current != RequestValue;
        return false;
    }
}
    FString FVerifyCounterByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Limit:VerifyCounterByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCounterByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr& Request,
        Gs2::Limit::Model::FCounterPtr Item
    )
    {
        const int32 Current = Item->GetCount().Get(0);
        const int32 Expected = Request->GetCount().Get(0);
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
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("count", "invalid", ""));
            return Details;
        }());
    }

    FVerifyCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr& Request
    ):
        Domain(Domain), Service(Service), AccessToken(AccessToken), Request(Request)
    {

    }

    FVerifyCounterByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(const FCommitTask& From):
        Domain(From.Domain), Service(From.Service), AccessToken(From.AccessToken), Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCounterByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Limit::Request::FVerifyCounterByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}")) PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetLimitName().IsSet() || PreparedRequest->GetLimitName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetCounterName().IsSet() || PreparedRequest->GetCounterName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString())) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString()), UserId = PreparedRequest->GetUserId().Get(FString()), LimitName = PreparedRequest->GetLimitName().Get(FString()), CounterName = PreparedRequest->GetCounterName().Get(FString());
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString()); const int32 RequestValue = PreparedRequest->GetCount().Get(0); const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(TEXT("grn:gs2:%s:%s:limit:%s:user:%s:limit:%s:counter:%s"), *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *LimitName, *CounterName);
        Gs2::Limit::Model::FCounterPtr Cached;
        if (!Gs2::Limit::Model::Cache::FCounterCache::TryGet(Domain->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetCounterId().IsSet() || Cached->GetCounterId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetLimitName().IsSet() || Cached->GetLimitName().Get(FString()) != LimitName ||
            !Cached->GetName().IsSet() || Cached->GetName().Get(FString()) != CounterName ||
            !Cached->GetCount().IsSet()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, ExpectedId, VerifyType, RequestValue]()
        {
            Gs2::Limit::Model::FCounterPtr Current;
            if (!Gs2::Limit::Model::Cache::FCounterCache::TryGet(Cache, NamespaceName, UserId, LimitName, CounterName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return LimitVerifyCounterPredicate(Current, ExpectedId, UserId, LimitName, CounterName, VerifyType, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyCounterByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCounterByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyCounterByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCounterByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Limit::Domain::FGs2LimitDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = MakeShared<Gs2::Limit::Request::FVerifyCounterByUserIdRequest>(*Request);
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

    Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr FVerifyCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int32 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetCount().Get(0), Rate, Value))
        {
            return Request;
        }
        Request->WithCount(Value);
        return Request;
    }

    Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr FVerifyCounterByUserIdSpeculativeExecutor::Rate(
        const Gs2::Limit::Request::FVerifyCounterByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int32 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetCount().Get(0), Rate, Value))
        {
            return Request;
        }
        Request->WithCount(Value);
        return Request;
    }
}
