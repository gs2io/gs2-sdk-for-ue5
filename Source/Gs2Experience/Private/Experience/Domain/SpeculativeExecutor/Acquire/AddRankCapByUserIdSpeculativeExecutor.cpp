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

#include "Experience/Domain/SpeculativeExecutor/Acquire/AddRankCapByUserIdSpeculativeExecutor.h"
#include "Experience/Domain/Gs2Experience.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"
#include "Experience/Domain/SpeculativeExecutor/StatusSpeculativeCommit.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{

    FString FAddRankCapByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Experience:AddRankCapByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FAddRankCapByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request,
        Gs2::Experience::Model::FExperienceModelPtr Model,
        Gs2::Experience::Model::FStatusPtr Item
    )
    {
        const auto RankCapValue = Item->GetRankCapValue().IsSet() ? *Item->GetRankCapValue() : 0;
        Item->WithRankCapValue(RankCapValue + *Request->GetRankCapValue());
        if (*Item->GetRankCapValue() > *Model->GetMaxRankCap())
        {
            return MakeShared<Gs2::Core::Model::FBadRequestError>([]
            {
                auto Arr = MakeShared<TArray<Gs2::Core::Model::FGs2ErrorDetailPtr>>();
                Arr->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>("rankCapValue", "invalid", ""));
                return Arr;
            }());
        }
        return nullptr;
    }

    FAddRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FAddRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FAddRankCapByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Experience::Request::FAddRankCapByUserIdRequest>(*Request);
        if (!Domain.IsValid() || !Domain->RestSession.IsValid() || !Domain->Cache.IsValid() ||
            !PreparedToken.IsValid() || !PreparedRequest.IsValid() ||
            !PreparedToken->GetUserId().IsSet() || PreparedToken->GetUserId().Get(FString()).IsEmpty()) return nullptr;
        if (PreparedRequest->GetUserId().IsSet() &&
            PreparedRequest->GetUserId().Get(FString()) == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            PreparedRequest->GetUserId().Get(FString()) != PreparedToken->GetUserId().Get(FString()) ||
            !PreparedRequest->GetPropertyId().IsSet()) return nullptr;

        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedToken->GetUserId();
        const auto ExperienceName = PreparedRequest->GetExperienceName();
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const FString PropertyId = PreparedRequest->GetPropertyId().Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *UserId.Get(FString()));
        const FString ExpectedStatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:experience:%s:user:%s:experienceModel:%s:property:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId.Get(FString()),
            *ExperienceName.Get(FString()), *PropertyId
        );
        const FString ExpectedModelId = FString::Printf(
            TEXT("grn:gs2:%s:%s:experience:%s:model:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *ExperienceName.Get(FString())
        );
        *Result = FStatusSpeculativeCommit::Create(
            Domain->Cache, NamespaceName, UserId, ExperienceName, PropertyId,
            TimeOffset, ExpectedStatusId, ExpectedModelId,
            [PreparedRequest](const Gs2::Experience::Model::FStatusPtr& Source, const Gs2::Experience::Model::FExperienceModelPtr& Model) -> Gs2::Experience::Model::FStatusPtr
            {
                if (!Source->GetExperienceValue().IsSet() || !Source->GetRankCapValue().IsSet() ||
                    !PreparedRequest->GetRankCapValue().IsSet()) return nullptr;
                const auto Changed = FStatusSpeculativeCommit::AddRankCap(
                    Source, *PreparedRequest->GetRankCapValue());
                if (!Changed.IsValid() || !Changed->GetRankCapValue().IsSet()) return nullptr;
                return FStatusSpeculativeCommit::RecalculateStatus(
                    Model, Source, *Source->GetExperienceValue(), *Changed->GetRankCapValue());
            },
            [PreparedRequest](const Gs2::Experience::Model::FStatusPtr& Source) -> Gs2::Experience::Model::FStatusPtr
            {
                if (!PreparedRequest->GetRankCapValue().IsSet()) return nullptr;
                return FStatusSpeculativeCommit::AddRankCap(
                    Source, *PreparedRequest->GetRankCapValue());
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FAddRankCapByUserIdSpeculativeExecutor::FCommitTask>> FAddRankCapByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr FAddRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid())
        {
            return nullptr;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetRankCapValue().Get(1), Rate, Value))
        {
            return nullptr;
        }
        Request->WithRankCapValue(Value);
        return Request;
    }

    Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr FAddRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FAddRankCapByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid())
        {
            return nullptr;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetRankCapValue().Get(1), Rate, Value))
        {
            return nullptr;
        }
        Request->WithRankCapValue(Value);
        return Request;
    }
}
