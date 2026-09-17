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

#include "Enhance/Domain/SpeculativeExecutor/Transaction/UnleashByUserIdSpeculativeExecutor.h"

#include "Core/Domain/Gs2.h"
#include "Auth/Model/AccessToken.h"
#include "Core/Domain/SpeculativeExecutor/ActionConfig.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Enhance/Model/Cache/UnleashRateModel.h"
#include "Enhance/Model/UnleashRateModel.h"
#include "Grade/Model/Cache/Status.h"
#include "Grade/Model/Status.h"
#include "Grade/Request/AddGradeByUserIdRequest.h"
#include "Internationalization/Regex.h"
#include "Inventory/Request/ConsumeItemSetByUserIdRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Enhance::Domain::Transaction::SpeculativeExecutor
{
    namespace
    {
        FString SerializeUnleashSnapshot(const TSharedPtr<FJsonObject>& Object)
        {
            if (!Object.IsValid()) return FString();
            FString Body;
            const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
            FJsonSerializer::Serialize(Object.ToSharedRef(), Writer);
            return Body;
        }

        Gs2::Core::Model::FConsumeActionPtr BuildUnleashConsumeAction(
            const Gs2::Auth::Model::FAccessTokenPtr& Token,
            const FString& MaterialItemSetId
        )
        {
            const auto Pattern = FRegexPattern(
                TEXT("^grn:gs2:[-_.{}a-zA-Z0-9]+:[-_.{}a-zA-Z0-9]+:inventory:([-_.{}a-zA-Z0-9]+):user:[-_.{}a-zA-Z0-9]+:inventory:([-_.{}a-zA-Z0-9]+):item:([-_.{}a-zA-Z0-9]+):itemSet:([-_.{}a-zA-Z0-9]+)$"));
            FRegexMatcher Matcher(Pattern, MaterialItemSetId);
            if (!Matcher.FindNext() || !Token.IsValid() || !Token->GetUserId().IsSet()) return nullptr;
            const auto Request = MakeShared<Gs2::Inventory::Request::FConsumeItemSetByUserIdRequest>()
                ->WithNamespaceName(Matcher.GetCaptureGroup(1))
                ->WithInventoryName(Matcher.GetCaptureGroup(2))
                ->WithUserId(Token->GetUserId())
                ->WithItemName(Matcher.GetCaptureGroup(3))
                ->WithItemSetName(Matcher.GetCaptureGroup(4))
                ->WithConsumeCount(1);
            return MakeShared<Gs2::Core::Model::FConsumeAction>()
                ->WithAction(FString("Gs2Inventory:ConsumeItemSetByUserId"))
                ->WithRequest(SerializeUnleashSnapshot(Request->ToJson()));
        }
    }

    FString FUnleashByUserIdSpeculativeExecutor::Action() {
        return "Gs2Enhance:UnleashByUserId";
    }

    FUnleashByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FUnleashByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {
    }

    FUnleashByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FUnleashByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result)
    {
        if (!Result.IsValid() || !Domain.IsValid() || !Domain->RestSession.IsValid() ||
            !AccessToken.IsValid() || !Request.IsValid())
        {
            if (Result.IsValid()) *Result = nullptr;
            return nullptr;
        }
        const auto PreparedAccessToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        const auto PreparedRequest = Gs2::Enhance::Request::FUnleashByUserIdRequest::FromJson(Request->ToJson());
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
        const auto RateName = PreparedRequest->GetRateName();
        Gs2::Enhance::Model::FUnleashRateModelPtr RateModel;
        const bool RateFound = Gs2::Enhance::Model::Cache::FUnleashRateModelCache::TryGet(
            Domain->Cache, NamespaceName, RateName, TOptional<int32>(), &RateModel);
        const FString ExpectedRateId = FString::Printf(
            TEXT("grn:gs2:%s:%s:enhance:%s:unleashRateModel:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *NamespaceName.Get(FString()), *RateName.Get(FString()));
        if (RateFound && (!RateModel.IsValid() || !RateModel->GetUnleashRateModelId().IsSet() ||
            *RateModel->GetUnleashRateModelId() != ExpectedRateId || !RateModel->GetName().IsSet() ||
            *RateModel->GetName() != *RateName.Get(FString())))
        {
            *Result = nullptr;
            return nullptr;
        }

        Gs2::Grade::Model::FStatusPtr GradeStatus;
        bool GradeFound = false;
        TOptional<FString> GradeNamespace;
        TOptional<FString> GradeName;
        const auto TargetItemSetId = PreparedRequest->GetTargetItemSetId();
        if (RateModel.IsValid())
        {
            const auto GradeEntries = RateModel->GetGradeEntries();
            if (!GradeEntries.IsValid() || GradeEntries->Num() == 0 ||
                !RateModel->GetGradeModelId().IsSet())
            {
                *Result = nullptr;
                return nullptr;
            }
            const auto Pattern = FRegexPattern(
                TEXT("^grn:gs2:[-_.{}a-zA-Z0-9]+:[-_.{}a-zA-Z0-9]+:grade:([-_.{}a-zA-Z0-9]+):model:([-_.{}a-zA-Z0-9]+)$"));
            FRegexMatcher Matcher(Pattern, RateModel->GetGradeModelId().GetValue());
            if (!Matcher.FindNext())
            {
                *Result = nullptr;
                return nullptr;
            }
            GradeNamespace = Matcher.GetCaptureGroup(1);
            GradeName = Matcher.GetCaptureGroup(2);
            GradeFound = Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                Domain->Cache, GradeNamespace, PreparedAccessToken->GetUserId(),
                GradeName, TargetItemSetId, PreparedAccessToken->GetTimeOffset(), &GradeStatus);
            const FString ExpectedStatusId = FString::Printf(
                TEXT("grn:gs2:%s:%s:grade:%s:user:%s:gradeModel:%s:property:%s"),
                *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
                *GradeNamespace.Get(FString()), *PreparedAccessToken->GetUserId().Get(FString()),
                *GradeName.Get(FString()),
                *TargetItemSetId.Get(FString()));
            if (GradeFound && (!GradeStatus.IsValid() || !GradeStatus->GetStatusId().IsSet() ||
                *GradeStatus->GetStatusId() != ExpectedStatusId || !GradeStatus->GetUserId().IsSet() ||
                *GradeStatus->GetUserId() != *PreparedAccessToken->GetUserId() ||
                !GradeStatus->GetGradeName().IsSet() || *GradeStatus->GetGradeName() != *GradeName ||
                GradeStatus->GetPropertyId() != TargetItemSetId))
            {
                *Result = nullptr;
                return nullptr;
            }
            if (GradeStatus.IsValid())
            {
                if (!GradeStatus->GetGradeValue().IsSet())
                {
                    *Result = nullptr;
                    return nullptr;
                }
                bool Matched = false;
                for (const auto& Entry : *GradeEntries)
                {
                    if (Entry.IsValid() && Entry->GetGradeValue().IsSet() &&
                        Entry->GetGradeValue().GetValue() == GradeStatus->GetGradeValue().GetValue())
                    {
                        Matched = Entry->GetNeedCount().IsSet() &&
                            Entry->GetNeedCount().GetValue() ==
                            (PreparedRequest->GetMaterials().IsValid() ? PreparedRequest->GetMaterials()->Num() : 0);
                        break;
                    }
                }
                if (!Matched)
                {
                    *Result = nullptr;
                    return nullptr;
                }
            }
        }

        const auto ConsumeActions = MakeShared<TArray<Gs2::Core::Model::FConsumeActionPtr>>();
        if (const auto Materials = PreparedRequest->GetMaterials(); Materials.IsValid())
        {
            for (const auto& Material : *Materials)
            {
                Gs2::Core::Model::FConsumeActionPtr Action = BuildUnleashConsumeAction(PreparedAccessToken, Material);
                if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
                {
                    for (const auto& Entry : *Config)
                    {
                        if (!Entry.IsValid())
                        {
                            Action = nullptr;
                            break;
                        }
                        Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                            Gs2::Core::Model::FConsumeActionPtr(Action),
                            TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                    }
                }
                if (Action.IsValid()) ConsumeActions->Add(Action);
            }
        }
        const auto AcquireActions = MakeShared<TArray<Gs2::Core::Model::FAcquireActionPtr>>();
        if (GradeStatus.IsValid())
        {
            Gs2::Core::Model::FAcquireActionPtr Action = MakeShared<Gs2::Core::Model::FAcquireAction>()
                ->WithAction(FString("Gs2Grade:AddGradeByUserId"))
                ->WithRequest(SerializeUnleashSnapshot(
                    MakeShared<Gs2::Grade::Request::FAddGradeByUserIdRequest>()
                        ->WithNamespaceName(GradeNamespace)
                        ->WithUserId(PreparedAccessToken->GetUserId())
                        ->WithGradeName(GradeName)
                        ->WithPropertyId(TargetItemSetId)
                        ->WithGradeValue(1)
                        ->ToJson()));
            if (const auto Config = PreparedRequest->GetConfig(); Config.IsValid())
            {
                for (const auto& Entry : *Config)
                {
                    if (!Entry.IsValid())
                    {
                        Action = nullptr;
                        break;
                    }
                    Action = Gs2::Core::Domain::SpeculativeExecutor::ApplyConfig(
                        Gs2::Core::Model::FAcquireActionPtr(Action),
                        TOptional<FString>(Entry->GetKey()), TOptional<FString>(Entry->GetValue()));
                }
            }
            if (Action.IsValid()) AcquireActions->Add(Action);
        }
        if (ConsumeActions->Num() == 0 && AcquireActions->Num() == 0)
        {
            *Result = nullptr;
            return nullptr;
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
        const FString RateSnapshot = RateModel.IsValid() ? SerializeUnleashSnapshot(RateModel->ToJson()) : FString();
        const FString GradeSnapshot = GradeStatus.IsValid() ? SerializeUnleashSnapshot(GradeStatus->ToJson()) : FString();
        const auto PreparedCommit = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::WrapLegacy(Commit);
        *Result = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateGuarded(
            MakeShared<TFunction<void()>>([PreparedCommit]() { PreparedCommit->InvokeLegacy(); }),
            [DomainCopy = Domain, NamespaceName, RateName, RateFound, RateSnapshot,
             RateModel, GradeNamespace, GradeName, TargetItemSetId, GradeFound, GradeSnapshot,
             UserId = PreparedAccessToken->GetUserId(), TimeOffset = PreparedAccessToken->GetTimeOffset()]()
            {
                Gs2::Enhance::Model::FUnleashRateModelPtr LiveRate;
                const bool LiveRateFound = Gs2::Enhance::Model::Cache::FUnleashRateModelCache::TryGet(
                    DomainCopy->Cache, NamespaceName, RateName, TOptional<int32>(), &LiveRate);
                if (LiveRateFound != RateFound || (RateFound &&
                    (!LiveRate.IsValid() || SerializeUnleashSnapshot(LiveRate->ToJson()) != RateSnapshot))) return false;
                if (RateModel.IsValid())
                {
                    Gs2::Grade::Model::FStatusPtr LiveGrade;
                    const bool LiveGradeFound = Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                        DomainCopy->Cache, GradeNamespace, UserId, GradeName, TargetItemSetId,
                        TimeOffset, &LiveGrade);
                    if (LiveGradeFound != GradeFound) return false;
                    if (GradeFound && (!LiveGrade.IsValid() || SerializeUnleashSnapshot(LiveGrade->ToJson()) != GradeSnapshot)) return false;
                }
                return true;
            });
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FUnleashByUserIdSpeculativeExecutor::FCommitTask>> FUnleashByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Enhance::Domain::FGs2EnhanceDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Enhance::Request::FUnleashByUserIdRequestPtr& Request
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }
}
