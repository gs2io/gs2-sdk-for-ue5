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

#include "Stamina/Domain/SpeculativeExecutor/Verify/VerifyStaminaMaxValueByUserIdSpeculativeExecutor.h"
#include "Stamina/Model/Cache/Stamina.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Stamina::Domain::SpeculativeExecutor
{
namespace
{
    bool StaminaVerifyMaxValuePredicate(
        const Gs2::Stamina::Model::FStaminaPtr& Item,
        const FString& ExpectedId,
        const FString& UserId,
        const FString& StaminaName,
        const FString& VerifyType,
        const int32 RequestValue
    )
    {
        if (!Item.IsValid() || !Item->GetStaminaId().IsSet() || Item->GetStaminaId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetStaminaName().IsSet() || Item->GetStaminaName().Get(FString()) != StaminaName ||
            !Item->GetMaxValue().IsSet()) return false;
        const int32 Current = Item->GetMaxValue().Get(0);
        if (VerifyType == TEXT("less")) return Current < RequestValue;
        if (VerifyType == TEXT("lessEqual")) return Current <= RequestValue;
        if (VerifyType == TEXT("greater")) return Current > RequestValue;
        if (VerifyType == TEXT("greaterEqual")) return Current >= RequestValue;
        if (VerifyType == TEXT("equal")) return Current == RequestValue;
        if (VerifyType == TEXT("notEqual")) return Current != RequestValue;
        return false;
    }

    Gs2::Core::Model::FGs2ErrorPtr StaminaVerifyMaxValueError(const FString& VerifyType)
    {
        FString Reason;
        if (VerifyType == TEXT("less")) Reason = TEXT("greaterEqual");
        else if (VerifyType == TEXT("lessEqual")) Reason = TEXT("greater");
        else if (VerifyType == TEXT("greater")) Reason = TEXT("lessEqual");
        else if (VerifyType == TEXT("greaterEqual")) Reason = TEXT("less");
        else if (VerifyType == TEXT("equal")) Reason = TEXT("notEqual");
        else if (VerifyType == TEXT("notEqual")) Reason = TEXT("equal");
        if (Reason.IsEmpty()) return nullptr;
        auto Details = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
        Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
            TEXT("count"), FString::Printf(TEXT("stamina.stamina.count.error.%s"), *Reason), TEXT("")));
        return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
    }
}

    FString FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Stamina:VerifyStaminaMaxValueByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&,
        const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr& Request,
        Gs2::Stamina::Model::FStaminaPtr Item
    )
    {
        const int32 Current = Item->GetMaxValue().Get(0);
        const int32 Expected = Request->GetValue().Get(0);
        const FString VerifyType = Request->GetVerifyType().Get(FString());
        const bool Satisfied =
            (VerifyType == TEXT("less") && Current < Expected) ||
            (VerifyType == TEXT("lessEqual") && Current <= Expected) ||
            (VerifyType == TEXT("greater") && Current > Expected) ||
            (VerifyType == TEXT("greaterEqual") && Current >= Expected) ||
            (VerifyType == TEXT("equal") && Current == Expected) ||
            (VerifyType == TEXT("notEqual") && Current != Expected);
        return Satisfied ? nullptr : StaminaVerifyMaxValueError(VerifyType);
    }

    FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || Domain->RestSession->OwnerId().IsEmpty() ||
            !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetValue().IsSet() || !PreparedRequest->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        if (VerifyType != TEXT("less") && VerifyType != TEXT("lessEqual") && VerifyType != TEXT("greater") &&
            VerifyType != TEXT("greaterEqual") && VerifyType != TEXT("equal") && VerifyType != TEXT("notEqual")) return nullptr;
        const FString NamespaceName = PreparedRequest->GetNamespaceName().Get(FString());
        const FString UserId = PreparedToken->GetUserId().Get(FString());
        const FString StaminaName = PreparedRequest->GetStaminaName().Get(FString());
        const int32 RequestValue = PreparedRequest->GetValue().Get(0);
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:stamina:%s:user:%s:stamina:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName, *UserId, *StaminaName);
        Gs2::Stamina::Model::FStaminaPtr Cached;
        if (!Gs2::Stamina::Model::Cache::FStaminaCache::TryGet(
            Domain->Cache, NamespaceName, UserId, StaminaName, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetStaminaId().IsSet() || Cached->GetStaminaId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetStaminaName().IsSet() || Cached->GetStaminaName().Get(FString()) != StaminaName ||
            !Cached->GetMaxValue().IsSet()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, StaminaName, TimeOffset,
            ExpectedId, VerifyType, RequestValue]()
        {
            Gs2::Stamina::Model::FStaminaPtr Current;
            if (!Gs2::Stamina::Model::Cache::FStaminaCache::TryGet(
                Cache, NamespaceName, UserId, StaminaName, TimeOffset, &Current) || !Current.IsValid()) return false;
            return StaminaVerifyMaxValuePredicate(Current, ExpectedId, UserId, StaminaName, VerifyType, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::FCommitTask>> FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::FCommitTask>> FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Stamina::Domain::FGs2StaminaDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequest::FromJson(Request->ToJson());
        if (!Inverse.IsValid() || !Inverse->GetVerifyType().IsSet()) return nullptr;
        const FString VerifyType = Inverse->GetVerifyType().Get(FString());
        if (VerifyType == TEXT("less")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greaterEqual")));
        else if (VerifyType == TEXT("lessEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("greater")));
        else if (VerifyType == TEXT("greater")) Inverse->WithVerifyType(TOptional<FString>(TEXT("lessEqual")));
        else if (VerifyType == TEXT("greaterEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("less")));
        else if (VerifyType == TEXT("equal")) Inverse->WithVerifyType(TOptional<FString>(TEXT("notEqual")));
        else if (VerifyType == TEXT("notEqual")) Inverse->WithVerifyType(TOptional<FString>(TEXT("equal")));
        else return nullptr;
        return Execute(Domain, Service, AccessToken, Inverse);
    }

    Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr FVerifyStaminaMaxValueByUserIdSpeculativeExecutor::Rate(
        const Gs2::Stamina::Request::FVerifyStaminaMaxValueByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
