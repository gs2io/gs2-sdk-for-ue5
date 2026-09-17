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

#include "Grade/Domain/SpeculativeExecutor/Acquire/AddGradeByUserIdSpeculativeExecutor.h"
#include "Grade/Domain/Gs2Grade.h"
#include "Grade/Domain/SpeculativeExecutor/StatusSpeculativeCommit.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"

namespace Gs2::Grade::Domain::SpeculativeExecutor
{

    FString FAddGradeByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Grade:AddGradeByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddGradeByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FAddGradeByUserIdRequestPtr& Request,
        Gs2::Grade::Model::FStatusPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FAddGradeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FAddGradeByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddGradeByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddGradeByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Grade::Request::FAddGradeByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Grade::Request::FAddGradeByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !Domain->Cache.IsValid() || !PreparedToken.IsValid() ||
            !PreparedRequest.IsValid() || !PreparedToken->GetUserId().IsSet() ||
            PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetNamespaceName().IsSet() ||
            PreparedRequest->GetNamespaceName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetGradeName().IsSet() ||
            PreparedRequest->GetGradeName().Get(FString()).IsEmpty() ||
            !PreparedRequest->GetPropertyId().IsSet() ||
            PreparedRequest->GetPropertyId().Get(FString()).IsEmpty()) return nullptr;

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedToken->GetUserId();
        const auto GradeName = PreparedRequest->GetGradeName();
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const auto PropertyId = PreparedRequest->GetPropertyId().Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *UserId.Get(FString()));
        if (PropertyId.IsEmpty()) return nullptr;
        const FString ExpectedStatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:user:%s:gradeModel:%s:property:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId.Get(FString()),
            *GradeName.Get(FString()), *PropertyId
        );
        *Result = FStatusSpeculativeCommit::Create(
            Domain->Cache, NamespaceName, UserId, GradeName, PropertyId,
            TimeOffset, ExpectedStatusId,
            [PreparedRequest](const Gs2::Grade::Model::FStatusPtr& Source) -> Gs2::Grade::Model::FStatusPtr
            {
                if (!Source->GetGradeValue().IsSet() ||
                    !PreparedRequest->GetGradeValue().IsSet() ||
                    *PreparedRequest->GetGradeValue() < 0) return nullptr;
                const int64 Base = *Source->GetGradeValue();
                const int64 Delta = *PreparedRequest->GetGradeValue();
                if (Base > TNumericLimits<int64>::Max() - Delta) return nullptr;
                const int64 ChangedValue = Base + Delta;
                if (ChangedValue < 1) return nullptr;
                return MakeShared<Gs2::Grade::Model::FStatus>(*Source)
                    ->WithGradeValue(ChangedValue)->WithRevision(0);
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAddGradeByUserIdSpeculativeExecutor::FCommitTask>> FAddGradeByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FAddGradeByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Grade::Request::FAddGradeByUserIdRequestPtr FAddGradeByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FAddGradeByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (Request->GetGradeValue().IsSet())
        {
            Request->WithGradeValue(*Request->GetGradeValue() * Rate);
        }
        return Request;
    }

    Gs2::Grade::Request::FAddGradeByUserIdRequestPtr FAddGradeByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FAddGradeByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (Request->GetGradeValue().IsSet())
        {
            Rate.Multiply(*Request->GetGradeValue());
            Request->WithGradeValue(Rate.ToInt());
        }
        return Request;
    }
}
