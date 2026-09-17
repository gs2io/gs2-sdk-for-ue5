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

#include "Enhance/Domain/SpeculativeExecutor/Transaction/EndByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Auth/Model/AccessToken.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Enhance/Model/Cache/Progress.h"
#include "Enhance/Model/Cache/RateModel.h"
#include "Enhance/Model/Progress.h"
#include "Enhance/Model/RateModel.h"
#include "Enhance/Request/DeleteProgressByUserIdRequest.h"
#include "Experience/Model/ExperienceModel.h"
#include "Experience/Request/AddExperienceByUserIdRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Enhance::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString SerializeEndSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }

        Gs2::Core::Model::FConsumeActionPtr BuildEndDeleteAction(
            const TOptional<FString>& NamespaceName,
            const TOptional<FString>& UserId
        )
        {
            const auto Request = MakeShared<Gs2::Enhance::Request::FDeleteProgressByUserIdRequest>()
                ->WithNamespaceName(NamespaceName)
                ->WithUserId(UserId);
            return MakeShared<Gs2::Core::Model::FConsumeAction>()
                ->WithAction(FString("Gs2Enhance:DeleteProgressByUserId"))
                ->WithRequest(SerializeEndSnapshot(Request->ToJson()));
        }
    }

    FString FEndByUserIdSpeculativeExecutor::Action() {
        return "Gs2Enhance:EndByUserId";
    }

    FEndByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FEndByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FEndByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FEndByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        if (!Result.IsValid() || !Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            if (Result.IsValid()) *Result = nullptr;
            return nullptr;
        }
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Enhance::Request::FEndByUserIdRequest::FromJson(Request->ToJson());
        if (!PreparedRequest.IsValid() || !PreparedAccessToken->GetUserId().IsSet() ||
            PreparedAccessToken->GetUserId()->IsEmpty())
        {
            *Result = nullptr;
            return nullptr;
        }
        if (PreparedRequest->GetUserId().IsSet() && *PreparedRequest->GetUserId() == TEXT("#{userId}"))
        {
            PreparedRequest->WithUserId(PreparedAccessToken->GetUserId());
        }
        if (!PreparedRequest->GetUserId().IsSet() ||
            *PreparedRequest->GetUserId() != *PreparedAccessToken->GetUserId())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto NamespaceName = PreparedRequest->GetNamespaceName();
        const auto UserId = PreparedAccessToken->GetUserId();
        const auto TimeOffset = PreparedAccessToken->GetTimeOffset();
        Gs2::Enhance::Model::FProgressPtr Progress;
        const bool ProgressFound = Gs2::Enhance::Model::Cache::FProgressCache::TryGet(
            Domain->Cache, NamespaceName, UserId, TimeOffset, &Progress);
        const FString ExpectedProgressId = FString::Printf(
            TEXT("grn:gs2:%s:%s:enhance:%s:user:%s:progress"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *UserId.Get(FString()));
        if (!ProgressFound || !Progress.IsValid() || !Progress->GetProgressId().IsSet() ||
            *Progress->GetProgressId() != ExpectedProgressId || !Progress->GetUserId().IsSet() ||
            *Progress->GetUserId() != *UserId || !Progress->GetRateName().IsSet())
        {
            *Result = nullptr;
            return nullptr;
        }
        const auto RateName = Progress->GetRateName();
        Gs2::Enhance::Model::FRateModelPtr RateModel;
        const bool RateFound = Gs2::Enhance::Model::Cache::FRateModelCache::TryGet(
            Domain->Cache, NamespaceName, RateName, TOptional<int32>(), &RateModel);
        const FString ExpectedRateId = FString::Printf(
            TEXT("grn:gs2:%s:%s:enhance:%s:rateModel:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *RateName.Get(FString()));
        if (RateFound && (!RateModel.IsValid() || !RateModel->GetRateModelId().IsSet() ||
            *RateModel->GetRateModelId() != ExpectedRateId || !RateModel->GetName().IsSet() ||
            *RateModel->GetName() != *RateName))
        {
            *Result = nullptr;
            return nullptr;
        }

        const auto ConsumeActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        Gs2::Core::Model::FConsumeActionPtr DeleteAction = BuildEndDeleteAction(NamespaceName, UserId);
        if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
        {
            for (const auto& Entry : *Config)
            {
                if (!Entry.IsValid())
                {
                    DeleteAction = nullptr;
                    break;
                }
                DeleteAction = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                    Gs2::Core::Model::FConsumeActionPtr(DeleteAction),
                    TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
            }
        }
        if (DeleteAction.IsValid()) ConsumeActions->Add(DeleteAction);

        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        if (RateModel.IsValid())
        {
            if (!RateModel->GetExperienceModelId().IsSet() ||
                !Progress->GetPropertyId().IsSet() || !Progress->GetExperienceValue().IsSet())
            {
                *Result = nullptr;
                return nullptr;
            }
            const auto ExperienceModelId = RateModel->GetExperienceModelId().GetValue();
            const auto ExperienceNamespace = Gs2::Experience::Model::FExperienceModel::GetNamespaceNameFromGrn(ExperienceModelId);
            const auto ExperienceName = Gs2::Experience::Model::FExperienceModel::GetExperienceNameFromGrn(ExperienceModelId);
            if (!ExperienceNamespace.IsSet() || !ExperienceName.IsSet())
            {
                *Result = nullptr;
                return nullptr;
            }
            Gs2::Core::Model::FAcquireActionPtr AcquireAction = MakeShared<Gs2::Core::Model::FAcquireAction>()
                ->WithAction(FString("Gs2Experience:AddExperienceByUserId"))
                ->WithRequest(SerializeEndSnapshot(
                    MakeShared<Gs2::Experience::Request::FAddExperienceByUserIdRequest>()
                        ->WithNamespaceName(ExperienceNamespace)
                        ->WithUserId(UserId)
                        ->WithExperienceName(ExperienceName)
                        ->WithPropertyId(Progress->GetPropertyId())
                        ->WithExperienceValue(Progress->GetExperienceValue())
                        ->WithTruncateExperienceWhenRankUp(false)
                        ->ToJson()));
            if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
            {
                for (const auto& Entry : *Config)
                {
                    if (!Entry.IsValid())
                    {
                        AcquireAction = nullptr;
                        break;
                    }
                    AcquireAction = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                        Gs2::Core::Model::FAcquireActionPtr(AcquireAction),
                        TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                }
            }
            if (AcquireAction.IsValid()) AcquireActions->Add(AcquireAction);
        }

        const auto Event = MakeShared<Gs2::Core::Domain::Model::FIssueTransactionEvent>(
            PreparedAccessToken, ConsumeActions, AcquireActions, TBigInt<1024, false>(1));
        Service->OnIssueTransaction.Broadcast(Event);
        if (Event->GetError().IsValid()) return Event->GetError();
        const auto Commit = Event->GetCommit();
        if (!Commit.IsValid())
        {
            *Result = nullptr;
            return nullptr;
        }
        const FString ProgressSnapshot = SerializeEndSnapshot(Progress->ToJson());
        const FString RateSnapshot = RateModel.IsValid() ? SerializeEndSnapshot(RateModel->ToJson()) : FString();
        const auto PreparedCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(Commit);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([PreparedCommit]() { PreparedCommit->InvokeLegacy(); }),
            [DomainCopy = Domain, NamespaceName, UserId, TimeOffset, ProgressSnapshot,
             RateName, RateFound, RateSnapshot]()
            {
                Gs2::Enhance::Model::FProgressPtr LiveProgress;
                const bool LiveProgressFound = Gs2::Enhance::Model::Cache::FProgressCache::TryGet(
                    DomainCopy->Cache, NamespaceName, UserId, TimeOffset, &LiveProgress);
                if (!LiveProgressFound || !LiveProgress.IsValid() ||
                    SerializeEndSnapshot(LiveProgress->ToJson()) != ProgressSnapshot) return false;
                Gs2::Enhance::Model::FRateModelPtr LiveRate;
                const bool LiveRateFound = Gs2::Enhance::Model::Cache::FRateModelCache::TryGet(
                    DomainCopy->Cache, NamespaceName, RateName, TOptional<int32>(), &LiveRate);
                if (LiveRateFound != RateFound) return false;
                return !RateFound || (LiveRate.IsValid() && SerializeEndSnapshot(LiveRate->ToJson()) == RateSnapshot);
            });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEndByUserIdSpeculativeExecutor::FCommitTask>> FEndByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FEndByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
