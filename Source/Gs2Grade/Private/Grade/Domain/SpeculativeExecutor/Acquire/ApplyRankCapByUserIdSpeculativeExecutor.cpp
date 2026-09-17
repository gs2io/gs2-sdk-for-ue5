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

#include "Grade/Domain/SpeculativeExecutor/Acquire/ApplyRankCapByUserIdSpeculativeExecutor.h"
#include "Grade/Domain/Gs2Grade.h"
#include "Grade/Domain/SpeculativeExecutor/StatusSpeculativeCommit.h"

#include "Core/Domain/Gs2.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Grade/Model/Cache/GradeModel.h"
#include "Grade/Model/Cache/Status.h"
#include "Experience/Model/Cache/ExperienceModel.h"
#include "Experience/Model/Cache/Status.h"
#include "Experience/Model/ExperienceModel.h"
#include "Experience/Model/Status.h"

namespace Gs2::Grade::Domain::SpeculativeExecutor
{

    class FApplyRankCapSpeculativeCommit final
    {
        const Gs2::Core::Domain::FCacheDatabasePtr Cache;
        const TOptional<FString> GradeNamespaceName;
        const TOptional<FString> GradeName;
        const TOptional<FString> ExperienceNamespaceName;
        const TOptional<FString> ExperienceName;
        const TOptional<FString> UserId;
        const TOptional<FString> PropertyId;
        const TOptional<int32> TimeOffset;
        const FString ExpectedGradeStatusId;
        const FString ExpectedGradeModelId;
        const FString ExpectedExperienceModelId;
        const FString ExpectedExperienceStatusId;

        static bool IsExpectedExperienceStatus(
            const Gs2::Experience::Model::FStatusPtr& Item,
            const FString& ExpectedStatusId,
            const TOptional<FString>& UserId,
            const TOptional<FString>& ExperienceName,
            const TOptional<FString>& PropertyId
        )
        {
            return Item.IsValid() &&
                Item->GetStatusId().Get(FString()) == ExpectedStatusId &&
                Item->GetUserId().Get(FString()) == UserId.Get(FString()) &&
                Item->GetExperienceName().Get(FString()) == ExperienceName.Get(FString()) &&
                Item->GetPropertyId().Get(FString()) == PropertyId.Get(FString());
        }

        bool TryResolveRankCap(int64& RankCapValue) const
        {
            RankCapValue = 0;
            Gs2::Grade::Model::FStatusPtr GradeStatus;
            Gs2::Grade::Model::FGradeModelPtr GradeModel;
            if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                    Cache, GradeNamespaceName, UserId, GradeName, PropertyId,
                    TimeOffset, &GradeStatus) ||
                !Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(
                    Cache, GradeNamespaceName, GradeName, TOptional<int32>(),
                    &GradeModel) ||
                !GradeStatus.IsValid() ||
                !Gs2::Grade::Domain::SpeculativeExecutor::FStatusSpeculativeCommit::IsExpected(
                    GradeStatus, ExpectedGradeStatusId, UserId, GradeName, PropertyId) ||
                !GradeStatus->GetGradeValue().IsSet() ||
                !GradeModel.IsValid() || !GradeModel->GetGradeModelId().IsSet() ||
                GradeModel->GetGradeModelId().Get(FString()) != ExpectedGradeModelId ||
                GradeModel->GetName().Get(FString()) != GradeName.Get(FString()) ||
                !GradeModel->GetExperienceModelId().IsSet() ||
                GradeModel->GetExperienceModelId().Get(FString()) != ExpectedExperienceModelId ||
                !GradeModel->GetGradeEntries().IsValid() ||
                GradeModel->GetGradeEntries()->Num() == 0 ||
                *GradeStatus->GetGradeValue() <= 0)
            {
                return false;
            }
            const int64 Index = FMath::Min<int64>(
                GradeModel->GetGradeEntries()->Num() - 1,
                *GradeStatus->GetGradeValue() - 1
            );
            const auto Entry = (*GradeModel->GetGradeEntries())[static_cast<int32>(Index)];
            if (!Entry.IsValid() || !Entry->GetRankCapValue().IsSet()) return false;
            RankCapValue = *Entry->GetRankCapValue();
            return true;
        }

        Gs2::Experience::Model::FExperienceModelPtr GetExperienceModel() const
        {
            Gs2::Experience::Model::FExperienceModelPtr Model;
            if (!Gs2::Experience::Model::Cache::FExperienceModelCache::TryGet(
                    Cache, ExperienceNamespaceName, ExperienceName,
                    TOptional<int32>(), &Model) || !Model.IsValid() ||
                !Model->GetExperienceModelId().IsSet() ||
                Model->GetExperienceModelId().Get(FString()) != ExpectedExperienceModelId ||
                Model->GetName().Get(FString()) != ExperienceName.Get(FString()))
            {
                return nullptr;
            }
            return Model;
        }

        static Gs2::Experience::Model::FStatusPtr RecalculateStatus(
            const Gs2::Experience::Model::FExperienceModelPtr& Model,
            const Gs2::Experience::Model::FStatusPtr& Source,
            int64 ExperienceValue,
            int64 RankCapValue
        )
        {
            if (!Model.IsValid() || !Model->GetMaxRankCap().IsSet() || !Source.IsValid()) return nullptr;
            const auto Changed = MakeShared<Gs2::Experience::Model::FStatus>(*Source);
            const auto Values = Model->GetRankThreshold().IsValid()
                ? Model->GetRankThreshold()->GetValues()
                : nullptr;
            if (RankCapValue <= 1 || !Values.IsValid() || Values->Num() == 0)
            {
                ExperienceValue = 0;
            }
            else
            {
                int64 RankCapExperienceValue = (*Values)[Values->Num() - 1];
                if (RankCapValue - 1 < Values->Num())
                {
                    RankCapExperienceValue = (*Values)[static_cast<int32>(RankCapValue - 2)];
                }
                if (ExperienceValue > RankCapExperienceValue) ExperienceValue = RankCapExperienceValue;
            }
            RankCapValue = FMath::Min(RankCapValue, *Model->GetMaxRankCap());
            int64 RankValue = 1;
            int64 NextRankUpExperienceValue = 0;
            if (Values.IsValid())
            {
                for (const auto ThresholdValue : *Values)
                {
                    if (ExperienceValue < ThresholdValue)
                    {
                        if (RankCapValue > RankValue) NextRankUpExperienceValue = ThresholdValue;
                        break;
                    }
                    ++RankValue;
                }
            }
            return Changed->WithExperienceValue(ExperienceValue)
                ->WithRankValue(RankValue)
                ->WithRankCapValue(RankCapValue)
                ->WithNextRankUpExperienceValue(NextRankUpExperienceValue)
                ->WithRevision(0);
        }

        bool TryCompose(
            const TSharedPtr<void>& Current,
            bool HasCurrent,
            TSharedPtr<void>& Next
        ) const
        {
            int64 RankCapValue;
            if (!TryResolveRankCap(RankCapValue)) { Next = nullptr; return false; }
            Gs2::Experience::Model::FStatusPtr Source;
            if (HasCurrent)
            {
                if (!Current.IsValid()) { Next = nullptr; return false; }
                Source = StaticCastSharedPtr<Gs2::Experience::Model::FStatus>(Current);
            }
            else if (!Gs2::Experience::Model::Cache::FStatusCache::TryGet(
                Cache, ExperienceNamespaceName, UserId, ExperienceName, PropertyId,
                TimeOffset, &Source)) { Next = nullptr; return false; }
            if (!IsExpectedExperienceStatus(Source, ExpectedExperienceStatusId, UserId, ExperienceName, PropertyId))
            {
                Next = nullptr;
                return false;
            }
            const auto ExperienceModel = GetExperienceModel();
            Gs2::Experience::Model::FStatusPtr Changed;
            if (ExperienceModel.IsValid() && Source->GetExperienceValue().IsSet())
            {
                Changed = RecalculateStatus(
                    ExperienceModel, Source, *Source->GetExperienceValue(), RankCapValue
                );
                if (!Changed.IsValid()) { Next = nullptr; return false; }
            }
            else
            {
                Changed = MakeShared<Gs2::Experience::Model::FStatus>(*Source)
                    ->WithRankCapValue(RankCapValue);
                if (RankCapValue <= 1)
                {
                    Changed->WithExperienceValue(0)
                        ->WithRankValue(1)
                        ->WithNextRankUpExperienceValue(0);
                }
                Changed->WithRevision(0);
            }
            if (!IsExpectedExperienceStatus(Changed, ExpectedExperienceStatusId, UserId, ExperienceName, PropertyId) ||
                !Changed->GetRevision().IsSet() || *Changed->GetRevision() != 0)
            {
                Next = nullptr;
                return false;
            }
            Next = Changed;
            return true;
        }

    public:
        FApplyRankCapSpeculativeCommit(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString> GradeNamespaceName,
            const TOptional<FString> GradeName,
            const TOptional<FString> ExperienceNamespaceName,
            const TOptional<FString> ExperienceName,
            const TOptional<FString> UserId,
            const TOptional<FString> PropertyId,
            const TOptional<int32> TimeOffset,
            const FString& ExpectedGradeStatusId,
            const FString& ExpectedGradeModelId,
            const FString& ExpectedExperienceModelId,
            const FString& ExpectedExperienceStatusId
        ):
            Cache(Cache), GradeNamespaceName(GradeNamespaceName), GradeName(GradeName),
            ExperienceNamespaceName(ExperienceNamespaceName), ExperienceName(ExperienceName),
            UserId(UserId), PropertyId(PropertyId), TimeOffset(TimeOffset),
            ExpectedGradeStatusId(ExpectedGradeStatusId), ExpectedGradeModelId(ExpectedGradeModelId),
            ExpectedExperienceModelId(ExpectedExperienceModelId),
            ExpectedExperienceStatusId(ExpectedExperienceStatusId)
        {
        }

    public:
        static Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Create(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString> GradeNamespaceName,
            const TOptional<FString> GradeName,
            const TOptional<FString> ExperienceNamespaceName,
            const TOptional<FString> ExperienceName,
            const TOptional<FString> UserId,
            const TOptional<FString> PropertyId,
            const TOptional<int32> TimeOffset,
            const FString& ExpectedGradeStatusId,
            const FString& ExpectedGradeModelId,
            const FString& ExpectedExperienceModelId,
            const FString& ExpectedExperienceStatusId
        )
        {
            const auto Self = MakeShared<FApplyRankCapSpeculativeCommit>(
                Cache, GradeNamespaceName, GradeName, ExperienceNamespaceName,
                ExperienceName, UserId, PropertyId, TimeOffset,
                ExpectedGradeStatusId, ExpectedGradeModelId,
                ExpectedExperienceModelId, ExpectedExperienceStatusId
            );
            const FString CompositionKey =
                Gs2::Experience::Model::Cache::FStatusCache::CreateCacheParentKey(
                    ExperienceNamespaceName, UserId, TimeOffset
                ) + TEXT(":") +
                Gs2::Experience::Model::Cache::FStatusCache::CreateCacheKey(
                    ExperienceName, PropertyId
                );
            const auto Prepared = Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
                CompositionKey,
                [Self](const TSharedPtr<void>& Current, const bool HasCurrent, TSharedPtr<void>& Next)
                {
                    return Self->TryCompose(Current, HasCurrent, Next);
                },
                [Self](const TSharedPtr<void>& State)
                {
                    if (!State.IsValid()) return;
                    const auto Item = StaticCastSharedPtr<Gs2::Experience::Model::FStatus>(State);
                    if (IsExpectedExperienceStatus(Item, Self->ExpectedExperienceStatusId, Self->UserId, Self->ExperienceName, Self->PropertyId) &&
                        Item->GetRevision().IsSet() && *Item->GetRevision() == 0)
                    {
                        Gs2::Experience::Model::Cache::FStatusCache::Put(
                            Self->Cache, Self->ExperienceNamespaceName, Self->UserId,
                            Self->ExperienceName, Self->PropertyId, Self->TimeOffset, Item
                        );
                    }
                }
            );
            TSharedPtr<void> Initial;
            return Prepared.IsValid() && Prepared->TryCompose(nullptr, false, Initial)
                ? Prepared : nullptr;
        }
    };

    FString FApplyRankCapByUserIdSpeculativeExecutor::Action()
    {
        return FString("Gs2Grade:ApplyRankCapByUserId");
    }

    Gs2::Core::Model::FGs2ErrorPtr FApplyRankCapByUserIdSpeculativeExecutor::Transform(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr& Request,
        Gs2::Grade::Model::FStatusPtr Item
    )
    {
        // TODO: Speculative execution not supported
        UE_LOG(Gs2Log, Warning, TEXT("Speculative execution not supported on this action: %s"), ToCStr(Action()))
        return nullptr;
    }

    FApplyRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr& Request
    ):
        Domain(Domain),
        Service(Service),
        AccessToken(AccessToken),
        Request(Request)
    {

    }

    FApplyRankCapByUserIdSpeculativeExecutor::FCommitTask::FCommitTask(
        const FCommitTask& From
    ):
        Domain(From.Domain),
        Service(From.Service),
        AccessToken(From.AccessToken),
        Request(From.Request)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FApplyRankCapByUserIdSpeculativeExecutor::FCommitTask::Action(
        TSharedPtr<TSharedPtr<Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit>> Result
    )
    {
        *Result = nullptr;
        Gs2::Auth::Model::FAccessTokenPtr PreparedToken = nullptr;
        if (AccessToken.IsValid()) PreparedToken = MakeShared<Gs2::Auth::Model::FAccessToken>(*AccessToken);
        Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr PreparedRequest = nullptr;
        if (Request.IsValid()) PreparedRequest = MakeShared<Gs2::Grade::Request::FApplyRankCapByUserIdRequest>(*Request);
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
            !PreparedRequest->GetPropertyId().IsSet()) return nullptr;

        const auto GradeNamespaceName = PreparedRequest->GetNamespaceName();
        const auto GradeName = PreparedRequest->GetGradeName();
        const auto UserId = PreparedToken->GetUserId();
        const auto TimeOffset = PreparedToken->GetTimeOffset();
        const auto PropertyId = PreparedRequest->GetPropertyId().Get(FString())
            .Replace(TEXT("{region}"), *Domain->RestSession->RegionName())
            .Replace(TEXT("{ownerId}"), *Domain->RestSession->OwnerId())
            .Replace(TEXT("{userId}"), *UserId.Get(FString()));
        const FString ExpectedGradeStatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:user:%s:gradeModel:%s:property:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *GradeNamespaceName.Get(FString()), *UserId.Get(FString()),
            *GradeName.Get(FString()), *PropertyId
        );
        const FString ExpectedGradeModelId = FString::Printf(
            TEXT("grn:gs2:%s:%s:grade:%s:model:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *GradeNamespaceName.Get(FString()), *GradeName.Get(FString())
        );
        Gs2::Grade::Model::FStatusPtr GradeStatus;
        Gs2::Grade::Model::FGradeModelPtr GradeModel;
        if (!Gs2::Grade::Model::Cache::FStatusCache::TryGet(
                Domain->Cache, GradeNamespaceName, UserId, GradeName, PropertyId,
                TimeOffset, &GradeStatus) ||
            !Gs2::Grade::Model::Cache::FGradeModelCache::TryGet(
                Domain->Cache, GradeNamespaceName, GradeName, TOptional<int32>(),
                &GradeModel) ||
            !GradeStatus.IsValid() ||
            !FStatusSpeculativeCommit::IsExpected(
                GradeStatus, ExpectedGradeStatusId, UserId, GradeName, PropertyId) ||
            !GradeStatus->GetGradeValue().IsSet() || !GradeModel.IsValid() ||
            !GradeModel->GetGradeModelId().IsSet() ||
            GradeModel->GetGradeModelId().Get(FString()) != ExpectedGradeModelId ||
            GradeModel->GetName().Get(FString()) != GradeName.Get(FString()) ||
            !GradeModel->GetGradeEntries().IsValid() ||
            GradeModel->GetGradeEntries()->Num() == 0 ||
            *GradeStatus->GetGradeValue() <= 0 ||
            !GradeModel->GetExperienceModelId().IsSet()) return nullptr;

        const auto ExperienceNamespaceName =
            Gs2::Experience::Model::FExperienceModel::GetNamespaceNameFromGrn(
                *GradeModel->GetExperienceModelId()
            );
        const auto ExperienceName =
            Gs2::Experience::Model::FExperienceModel::GetExperienceNameFromGrn(
                *GradeModel->GetExperienceModelId()
            );
        const FString ExpectedExperienceModelId = FString::Printf(
            TEXT("grn:gs2:%s:%s:experience:%s:model:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *ExperienceNamespaceName.Get(FString()), *ExperienceName.Get(FString())
        );
        if (*GradeModel->GetExperienceModelId() != ExpectedExperienceModelId) return nullptr;
        const FString ExpectedExperienceStatusId = FString::Printf(
            TEXT("grn:gs2:%s:%s:experience:%s:user:%s:experienceModel:%s:property:%s"),
            *Domain->RestSession->RegionName(), *Domain->RestSession->OwnerId(),
            *ExperienceNamespaceName.Get(FString()), *UserId.Get(FString()),
            *ExperienceName.Get(FString()), *PropertyId
        );
        *Result = FApplyRankCapSpeculativeCommit::Create(
            Domain->Cache, GradeNamespaceName, GradeName,
            ExperienceNamespaceName, ExperienceName, UserId, PropertyId,
            TimeOffset, ExpectedGradeStatusId, ExpectedGradeModelId,
            ExpectedExperienceModelId, ExpectedExperienceStatusId
        );
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FApplyRankCapByUserIdSpeculativeExecutor::FCommitTask>> FApplyRankCapByUserIdSpeculativeExecutor::Execute(
        const Gs2::Core::Domain::FGs2Ptr& Domain,
        const Gs2::Grade::Domain::FGs2GradeDomainPtr& Service,
        const Gs2::Auth::Model::FAccessTokenPtr& AccessToken,
        const Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr& Request
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCommitTask>>(Domain, Service, AccessToken, Request);
    }

    Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr FApplyRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr& Request,
        const double Rate
    )
    {
        return Request;
    }

    Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr FApplyRankCapByUserIdSpeculativeExecutor::Rate(
        const Gs2::Grade::Request::FApplyRankCapByUserIdRequestPtr& Request,
        TBigInt<1024, false> Rate
    )
    {
        return Request;
    }
}
