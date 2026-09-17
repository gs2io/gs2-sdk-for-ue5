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

#include "Grade/Domain/SpeculativeExecutor/Verify/VerifyGradeByUserIdSpeculativeExecutor.h"
#include "Grade/Domain/Gs2Grade.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"

namespace Gs2::Grade::Domain::SpeculativeExecutor
{
namespace
{
    bool GradeVerifyTypeIsValid(const FString& Type)
    {
        return Type == TEXT("less") || Type == TEXT("lessEqual") || Type == TEXT("greater") ||
            Type == TEXT("greaterEqual") || Type == TEXT("equal") || Type == TEXT("notEqual");
    }

    bool GradeVerifyPredicate(const Gs2::Grade::Model::FStatusPtr& Item, const FString& ExpectedId,
        const FString& UserId, const FString& GradeName, const FString& PropertyId,
        const FString& Type, const int64 RequestValue)
    {
        if (!Item.IsValid() || !Item->GetStatusId().IsSet() || Item->GetStatusId().Get(FString()) != ExpectedId ||
            !Item->GetUserId().IsSet() || Item->GetUserId().Get(FString()) != UserId ||
            !Item->GetGradeName().IsSet() || Item->GetGradeName().Get(FString()) != GradeName ||
            !Item->GetPropertyId().IsSet() || Item->GetPropertyId().Get(FString()) != PropertyId ||
            !Item->GetGradeValue().IsSet()) return false;
        const int64 Current = Item->GetGradeValue().Get(0);
        if (Type == TEXT("less")) return Current < RequestValue;
        if (Type == TEXT("lessEqual")) return Current <= RequestValue;
        if (Type == TEXT("greater")) return Current > RequestValue;
        if (Type == TEXT("greaterEqual")) return Current >= RequestValue;
        if (Type == TEXT("equal")) return Current == RequestValue;
        if (Type == TEXT("notEqual")) return Current != RequestValue;
        return false;
    }


}
}


namespace Gs2::Grade::Domain::SpeculativeExecutor
{

    FString FVerifyGradeByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Grade:VerifyGradeByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyGradeByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr&, const Gs2::Auth::Model::FAccessTokenPtr&,
        const Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr& Request,
        Gs2::Grade::Model::FStatusPtr Item)
    {
        bool Satisfied = false;
        if (Item.IsValid() && Item->GetGradeValue().IsSet())
        {
            const int64 Current = Item->GetGradeValue().Get(0);
            const int64 Expected = Request->GetGradeValue().Get(0);
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
            Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("gradeValue", "invalid", ""));
            return Arr;
        }());
    }

    FVerifyGradeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FVerifyGradeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FVerifyGradeByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Grade::Request::FVerifyGradeByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() && PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        if (!PreparedRequest->GetUserId().IsSet() || PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() || PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGradeName().IsSet() || PreparedRequest->GetGradeName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetPropertyId().IsSet() || PreparedRequest->GetPropertyId().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetVerifyType().IsSet() || !GradeVerifyTypeIsValid(PreparedRequest->GetVerifyType().Get(FString()))) return nullptr;
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const FString UserId = PreparedToken->GetUserId().Get(FString());
        const FString GradeName = PreparedRequest->GetGradeName().Get(FString());
        const FString PropertyId = PreparedRequest->GetPropertyId().Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *UserId);
        if (PropertyId.IsEmpty()) return nullptr;
        const FString VerifyType = PreparedRequest->GetVerifyType().Get(FString());
        const int64 RequestValue = PreparedRequest->GetGradeValue().Get(1);
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString ExpectedId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:user:%s:gradeModel:%s:property:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(), *NamespaceName.Get(FString()),
            *UserId, *GradeName, *PropertyId);
        Gs2::Grade::Model::FStatusPtr Cached;
        if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(
            Domain->Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset, &Cached) || !Cached.IsValid()) return nullptr;
        if (!Cached->GetStatusId().IsSet() || Cached->GetStatusId().Get(FString()) != ExpectedId ||
            !Cached->GetUserId().IsSet() || Cached->GetUserId().Get(FString()) != UserId ||
            !Cached->GetGradeName().IsSet() || Cached->GetGradeName().Get(FString()) != GradeName ||
            !Cached->GetPropertyId().IsSet() || Cached->GetPropertyId().Get(FString()) != PropertyId ||
            !Cached->GetGradeValue().IsSet()) return nullptr;
        if (const auto Error = Transform(Domain, PreparedToken, PreparedRequest, Cached); Error.IsValid()) return Error;
        const auto Guard = [Cache = Domain->Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset,
            ExpectedId, VerifyType, RequestValue]()
        {
            Gs2::Grade::Model::FStatusPtr Current;
            if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                Cache, NamespaceName, UserId, GradeName, PropertyId, TimeOffset, &Current) || !Current.IsValid()) return false;
            return GradeVerifyPredicate(Current, ExpectedId, UserId, GradeName, PropertyId, VerifyType, RequestValue);
        };
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([]() {}), Guard);
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FVerifyGradeByUserIdSpeculativeExecutor::FCommitTask>> FVerifyGradeByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    TSharedPtr<FAsyncTask<FVerifyGradeByUserIdSpeculativeExecutor::FCommitTask>> FVerifyGradeByUserIdSpeculativeExecutor::ExecuteInverse(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr& Request
    )
    {
        if (!Request.IsValid()) return nullptr;
        auto Inverse = Gs2::Grade::Request::FVerifyGradeByUserIdRequest::FromJson(Request->ToJson());
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

    Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr FVerifyGradeByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetGradeValue().Get(1), Rate, Value))
        {
            return Request;
        }
        Request->WithGradeValue(Value);
        return Request;
    }

    Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr FVerifyGradeByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FVerifyGradeByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid() || !Request->GetMultiplyValueSpecifyingQuantity().Get(false))
        {
            return Request;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetGradeValue().Get(1), Rate, Value))
        {
            return Request;
        }
        Request->WithGradeValue(Value);
        return Request;
    }
}
