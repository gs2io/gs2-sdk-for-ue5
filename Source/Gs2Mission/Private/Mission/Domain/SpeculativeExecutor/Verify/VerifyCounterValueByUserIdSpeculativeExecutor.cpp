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
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

#include "Mission/Domain/SpeculativeExecutor/Verify/VerifyCounterValueByUserIdSpeculativeExecutor.h"
#include "Mission/Model/Cache/Counter.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"

namespace Gs2::Mission::Domain::SpeculativeExecutor
{
namespace
{
    bool MissionVerifyCounterScopeMatches(
        const Gs2::Mission::Model::FScopedValuePtr& Item,
        const FString& ScopeType,
        const FString& ResetType,
        const TOptional<FString>& ConditionName
    )
    {
        if (!Item.IsValid() || !Item->GetScopeType().IsSet() || Item->GetScopeType().Get(FString()) != ScopeType) return false;
        if (ScopeType == TEXT("resetTiming"))
        {
            const auto ItemResetType = Item->GetResetType();
            return ItemResetType.IsSet() == !ResetType.IsEmpty() &&
                (!ItemResetType.IsSet() || ItemResetType.Get(FString()) == ResetType);
        }
        const auto ItemConditionName = Item->GetConditionName();
        return ItemConditionName.IsSet() == ConditionName.IsSet() &&
            (!ItemConditionName.IsSet() || ItemConditionName.Get(FString()) == ConditionName.Get(FString()));
    }

    bool MissionVerifyCounterPredicate(
        const Gs2::Mission::Model::FCounterPtr& Item,
        const FString& ExpectedId,
        const FString& UserId,
        const FString& CounterName,
        const FString& VerifyType,
        const FString& ScopeType,
        const FString& ResetType,
        const TOptional<FString>& ConditionName,
        const int64 RequestValue
    )
    {
        if (!Item.IsValid() || !Item->GetCounterId().IsSet() || Item->GetCounterId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetName().IsSet() || Item->GetName().Get(FString()) != CounterName ||
            !Item->GetValues().IsValid()) return false;
        int64 Current = 0;
        for (const auto& ScopedValue : *Item->GetValues())
        {
            if (!MissionVerifyCounterScopeMatches(ScopedValue, ScopeType, ResetType, ConditionName)) continue;
            if (!ScopedValue->GetValue().IsSet()) return false;
            Current = ScopedValue->GetValue().Get(0);
            break;
        }
        if (VerifyType == TEXT("less")) return Current < RequestValue;
        if (VerifyType == TEXT("lessEqual")) return Current <= RequestValue;
        if (VerifyType == TEXT("greater")) return Current > RequestValue;
        if (VerifyType == TEXT("greaterEqual")) return Current >= RequestValue;
        if (VerifyType == TEXT("equal")) return Current == RequestValue;
        if (VerifyType == TEXT("notEqual")) return Current != RequestValue;
        return false;
    }
}

    FString FVerifyCounterValueByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Mission:VerifyCounterValueByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCounterValueByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr&,
        Gs2::Mission::Model::FCounterPtr
    )
    {
        return nullptr;
    }

    FVerifyCounterValueByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyCounterValueByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyCounterValueByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Mission::Request::FVerifyCounterValueByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetCounterName().IsSet() || PreparedRequest->GetCounterName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() || !PreparedRequest->GetScopeType().IsSet() ||
            !PreparedRequest->GetResetType().IsSet() || !PreparedRequest->GetValue().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString())) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("less") && VerifyType != TEXT("lessEqual") && VerifyType != TEXT("greater") &&
            VerifyType != TEXT("greaterEqual") && VerifyType != TEXT("equal") && VerifyType != TEXT("notEqual")) return nullptr;
        const FString ScopeType = PreparedRequest->GetScopeType().Get(FString());
        if (ScopeType != TEXT("resetTiming") && ScopeType != TEXT("verifyAction")) return nullptr;
        const FString ResetType = PreparedRequest->GetResetType().Get(FString());
        if (ResetType != TEXT("notReset") && ResetType != TEXT("daily") && ResetType != TEXT("weekly") &&
            ResetType != TEXT("monthly") && ResetType != TEXT("days")) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString());
        const FString UserId = PreparedRequest->GetUserId().Get(FString());
        const FString CounterName = PreparedRequest->GetCounterName().Get(FString());
        const TOptional<FString> ConditionName = PreparedRequest->GetConditionName();
        const int64 RequestValue = PreparedRequest->GetValue().Get(0);
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:mission:%s:user:%s:counter:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *CounterName);
        Gs2::Mission::Model::FCounterPtr Cached;
        if (!Gs2::Mission::Model::Cache::FCounterCache::TryGet(
            Domain->Cache, NamespaceName, UserId, CounterName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!MissionVerifyCounterPredicate(Cached, ExpectedId, UserId, CounterName, VerifyType, ScopeType, ResetType, ConditionName, RequestValue))
        {
            const auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("value"), TEXT("invalid"), TEXT("")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, CounterName, TimeOffset,
            ExpectedId, VerifyType, ScopeType, ResetType, ConditionName, RequestValue]()
        {
            Gs2::Mission::Model::FCounterPtr Current;
            if (!Gs2::Mission::Model::Cache::FCounterCache::TryGet(
                Cache, NamespaceName, UserId, CounterName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return MissionVerifyCounterPredicate(Current, ExpectedId, UserId, CounterName, VerifyType, ScopeType, ResetType, ConditionName, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyCounterValueByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCounterValueByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyCounterValueByUserIdSpeculativeExecutor::FCommitTask>> FVerifyCounterValueByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Mission::Domain::FGs2MissionDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = MakeShared<Gs2::Mission::Request::FVerifyCounterValueByUserIdRequest>(*Request);
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

    Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr FVerifyCounterValueByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetValue().Get(1), Rate, Value))
        {
            return Request;
        }
        Request->WithValue(Value);
        return Request;
    }

    Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr FVerifyCounterValueByUserIdSpeculativeExecutor::Rate(
        const Gs2::Mission::Request::FVerifyCounterValueByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetValue().Get(1), Rate, Value))
        {
            return Request;
        }
        Request->WithValue(Value);
        return Request;
    }
}
