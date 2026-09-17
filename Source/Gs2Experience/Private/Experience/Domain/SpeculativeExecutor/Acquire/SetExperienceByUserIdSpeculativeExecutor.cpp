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

#include "Experience/Domain/SpeculativeExecutor/Acquire/SetExperienceByUserIdSpeculativeExecutor.h"
#include "Experience/Domain/Gs2Experience.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Core/Util/ServerRate.h"
#include "Experience/Domain/SpeculativeExecutor/StatusSpeculativeCommit.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{

    FString FSetExperienceByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Experience:SetExperienceByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FSetExperienceByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr& Request,
        Gs2::Experience::Model::FStatusPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FSetExperienceByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FSetExperienceByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FSetExperienceByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Experience::Request::FSetExperienceByUserIdRequest>(*Request);
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
                if (!Source->GetRankCapValue().IsSet() || !PreparedRequest->GetExperienceValue().IsSet()) return nullptr;
                return FStatusSpeculativeCommit::RecalculateStatus(
                    Model, Source, *PreparedRequest->GetExperienceValue(), *Source->GetRankCapValue());
            },
            [PreparedRequest](const Gs2::Experience::Model::FStatusPtr& Source) -> Gs2::Experience::Model::FStatusPtr
            {
                if (!PreparedRequest->GetExperienceValue().IsSet()) return nullptr;
                return FStatusSpeculativeCommit::WithExperience(
                    Source, *PreparedRequest->GetExperienceValue());
            }
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FSetExperienceByUserIdSpeculativeExecutor::FCommitTask>> FSetExperienceByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Experience::Domain::FGs2ExperienceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr FSetExperienceByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        if (!Request.IsValid())
        {
            return nullptr;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetExperienceValue().Get(1), Rate, Value))
        {
            return nullptr;
        }
        Request->WithExperienceValue(Value);
        return Request;
    }

    Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr FSetExperienceByUserIdSpeculativeExecutor::Rate(
        const Gs2::Experience::Request::FSetExperienceByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        if (!Request.IsValid())
        {
            return nullptr;
        }
        int64 Value = 0;
        if (!Gs2::Core::Util::TryApplyServerRate(Request->GetExperienceValue().Get(1), Rate, Value))
        {
            return nullptr;
        }
        Request->WithExperienceValue(Value);
        return Request;
    }
}
