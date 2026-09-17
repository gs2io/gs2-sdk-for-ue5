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

#pragma once

#include "Core/Domain/CacheDatabase.h"
#include "Core/Domain/SpeculativeExecutor/PreparedSpeculativeCommit.h"
#include "Experience/Model/Cache/ExperienceModel.h"
#include "Experience/Model/Cache/Status.h"

namespace Gs2::Experience::Domain::SpeculativeExecutor
{
    class FStatusSpeculativeCommit final
    {
    public:
        using FFullTransform = TFunction<Gs2::Experience::Model::FStatusPtr(
            const Gs2::Experience::Model::FStatusPtr&,
            const Gs2::Experience::Model::FExperienceModelPtr&)>;
        using FPartialTransform = TFunction<Gs2::Experience::Model::FStatusPtr(
            const Gs2::Experience::Model::FStatusPtr&)>;

        static Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::FPreparedCommitPtr Create(
            const Gs2::Core::Domain::FCacheDatabasePtr& Cache,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> ExperienceName,
            const TOptional<FString> PropertyId,
            const TOptional<int32> TimeOffset,
            const FString& ExpectedStatusId,
            const FString& ExpectedModelId,
            FFullTransform FullTransform,
            FPartialTransform PartialTransform
        )
        {
            if (!Cache.IsValid() || !UserId.IsSet() ||
                !PropertyId.IsSet() || !FullTransform || !PartialTransform)
            {
                return nullptr;
            }

            Gs2::Experience::Model::FStatusPtr Item;
            if (!Gs2::Experience::Model::Cache::FStatusCache::TryGet(
                    Cache, NamespaceName, UserId, ExperienceName, PropertyId,
                    TimeOffset, &Item) || !IsExpected(
                        Item, ExpectedStatusId, UserId, ExperienceName, PropertyId))
            {
                return nullptr;
            }

            // A model miss or mismatch is intentionally not a preparation failure.
            Gs2::Experience::Model::FExperienceModelPtr PreparedModel;
            Gs2::Experience::Model::Cache::FExperienceModelCache::TryGet(
                Cache, NamespaceName, ExperienceName, TOptional<int32>(),
                &PreparedModel);

            const FString CompositionKey =
                Gs2::Experience::Model::Cache::FStatusCache::CreateCacheParentKey(
                    NamespaceName, UserId, TimeOffset
                ) + TEXT(":") +
                Gs2::Experience::Model::Cache::FStatusCache::CreateCacheKey(
                    ExperienceName, PropertyId
                );

            return Gs2::Core::Domain::SpeculativeExecutor::FPreparedSpeculativeCommit::CreateComposable(
                CompositionKey,
                [Cache, NamespaceName, UserId, ExperienceName, PropertyId,
                    TimeOffset, ExpectedStatusId, ExpectedModelId,
                    FullTransform, PartialTransform](
                    const TSharedPtr<void>& Current,
                    const bool HasCurrent,
                    TSharedPtr<void>& Next
                )
                {
                    try
                    {
                        Gs2::Experience::Model::FExperienceModelPtr Model;
                        Gs2::Experience::Model::Cache::FExperienceModelCache::TryGet(
                            Cache, NamespaceName, ExperienceName, TOptional<int32>(),
                            &Model);
                        if (!IsExpectedModel(Model, ExpectedModelId, ExperienceName))
                        {
                            Model = nullptr;
                        }

                        Gs2::Experience::Model::FStatusPtr Source;
                        if (HasCurrent)
                        {
                            if (!Current.IsValid())
                            {
                                Next = nullptr;
                                return false;
                            }
                            Source = StaticCastSharedPtr<Gs2::Experience::Model::FStatus>(Current);
                        }
                        else if (!Gs2::Experience::Model::Cache::FStatusCache::TryGet(
                            Cache, NamespaceName, UserId, ExperienceName, PropertyId,
                            TimeOffset, &Source))
                        {
                            Next = nullptr;
                            return false;
                        }

                        if (!IsExpected(Source, ExpectedStatusId, UserId,
                            ExperienceName, PropertyId))
                        {
                            Next = nullptr;
                            return false;
                        }

                        Gs2::Experience::Model::FStatusPtr Changed;
                        if (Model.IsValid())
                        {
                            Changed = FullTransform(Source, Model);
                        }
                        else
                        {
                            Changed = PartialTransform(Source);
                        }
                        if (!IsExpected(Changed, ExpectedStatusId, UserId,
                            ExperienceName, PropertyId))
                        {
                            Next = nullptr;
                            return false;
                        }
                        Next = Changed;
                        return true;
                    }
                    catch (...)
                    {
                        Next = nullptr;
                        return false;
                    }
                },
                [Cache, NamespaceName, UserId, ExperienceName, PropertyId,
                    TimeOffset, ExpectedStatusId](const TSharedPtr<void>& State)
                {
                    if (!State.IsValid()) return;
                    const auto ItemToCommit =
                        StaticCastSharedPtr<Gs2::Experience::Model::FStatus>(State);
                    if (IsExpected(ItemToCommit, ExpectedStatusId, UserId,
                        ExperienceName, PropertyId))
                    {
                        Gs2::Experience::Model::Cache::FStatusCache::Put(
                            Cache, NamespaceName, UserId, ExperienceName, PropertyId,
                            TimeOffset, ItemToCommit
                        );
                    }
                }
            );
        }

        static bool IsExpected(
            const Gs2::Experience::Model::FStatusPtr& Item,
            const FString& ExpectedStatusId,
            const TOptional<FString>& UserId,
            const TOptional<FString>& ExperienceName,
            const TOptional<FString>& PropertyId
        )
        {
            return Item.IsValid() &&
                Item->GetStatusId().IsSet() &&
                Item->GetStatusId().Get(FString()) == ExpectedStatusId &&
                IsSame(Item->GetUserId(), UserId) &&
                IsSame(Item->GetExperienceName(), ExperienceName) &&
                IsSame(Item->GetPropertyId(), PropertyId);
        }

        static bool IsExpectedModel(
            const Gs2::Experience::Model::FExperienceModelPtr& Model,
            const FString& ExpectedModelId,
            const TOptional<FString>& ExperienceName
        )
        {
            return Model.IsValid() &&
                Model->GetExperienceModelId().IsSet() &&
                Model->GetExperienceModelId().Get(FString()) == ExpectedModelId &&
                IsSame(Model->GetName(), ExperienceName);
        }

    private:
        static bool IsSame(
            const TOptional<FString>& Actual,
            const TOptional<FString>& Expected
        )
        {
            return Actual.IsSet() == Expected.IsSet() &&
                (!Actual.IsSet() || Actual.Get(FString()) == Expected.Get(FString()));
        }

    public:
        static bool AddChecked(const int64 Base, const int64 Delta, int64& Result)
        {
            if ((Delta > 0 && Base > TNumericLimits<int64>::Max() - Delta) ||
                (Delta < 0 && Base < TNumericLimits<int64>::Min() - Delta))
            {
                return false;
            }
            Result = Base + Delta;
            return true;
        }

        static bool SubtractChecked(const int64 Base, const int64 Delta, int64& Result)
        {
            if ((Delta > 0 && Base < TNumericLimits<int64>::Min() + Delta) ||
                (Delta < 0 && Base > TNumericLimits<int64>::Max() + Delta))
            {
                return false;
            }
            Result = Base - Delta;
            return true;
        }

        static Gs2::Experience::Model::FStatusPtr WithExperience(
            const Gs2::Experience::Model::FStatusPtr& Source,
            const int64 Value
        )
        {
            if (!Source.IsValid()) return nullptr;
            Gs2::Experience::Model::FStatusPtr Clone =
                MakeShared<Gs2::Experience::Model::FStatus>(*Source);
            if (!Clone.IsValid()) return nullptr;
            Clone->WithExperienceValue(Value)->WithRevision(0);
            return Clone;
        }

        static Gs2::Experience::Model::FStatusPtr WithRankCap(
            const Gs2::Experience::Model::FStatusPtr& Source,
            const int64 Value
        )
        {
            if (!Source.IsValid()) return nullptr;
            Gs2::Experience::Model::FStatusPtr Clone =
                MakeShared<Gs2::Experience::Model::FStatus>(*Source);
            if (!Clone.IsValid()) return nullptr;
            Clone->WithRankCapValue(Value);
            if (Value <= 1)
            {
                Clone->WithExperienceValue(0);
                Clone->WithRankValue(1);
                Clone->WithNextRankUpExperienceValue(0);
            }
            Clone->WithRevision(0);
            return Clone;
        }

        static Gs2::Experience::Model::FStatusPtr RecalculateStatus(
            const Gs2::Experience::Model::FExperienceModelPtr& Model,
            const Gs2::Experience::Model::FStatusPtr& Source,
            int64 ExperienceValue,
            int64 RankCapValue
        )
        {
            if (!Model.IsValid() || !Model->GetMaxRankCap().IsSet() ||
                !Source.IsValid()) return nullptr;
            Gs2::Experience::Model::FStatusPtr Clone =
                MakeShared<Gs2::Experience::Model::FStatus>(*Source);
            if (!Clone.IsValid()) return nullptr;

            const auto Threshold = Model->GetRankThreshold();
            TSharedPtr<TArray<int64>> Values = nullptr;
            if (Threshold.IsValid()) Values = Threshold->GetValues();
            const int32 ValueCount = Values.IsValid() ? Values->Num() : 0;
            if (RankCapValue <= 1 || ValueCount == 0)
            {
                ExperienceValue = 0;
            }
            else
            {
                int64 RankCapExperienceValue = (*Values)[ValueCount - 1];
                if (RankCapValue - 1 < ValueCount)
                {
                    RankCapExperienceValue = (*Values)[static_cast<int32>(RankCapValue) - 2];
                }
                if (ExperienceValue > RankCapExperienceValue)
                {
                    ExperienceValue = RankCapExperienceValue;
                }
            }

            RankCapValue = FMath::Min(RankCapValue, *Model->GetMaxRankCap());
            int64 RankValue = 1;
            int64 NextRankUpExperienceValue = 0;
            if (Values.IsValid())
            {
                for (const int64 ThresholdValue : *Values)
                {
                    if (ExperienceValue < ThresholdValue)
                    {
                        if (RankCapValue > RankValue)
                        {
                            NextRankUpExperienceValue = ThresholdValue;
                        }
                        break;
                    }
                    ++RankValue;
                }
            }

            Clone->WithExperienceValue(ExperienceValue)
                ->WithRankValue(RankValue)
                ->WithRankCapValue(RankCapValue)
                ->WithNextRankUpExperienceValue(NextRankUpExperienceValue)
                ->WithRevision(0);
            return Clone;
        }

        static Gs2::Experience::Model::FStatusPtr AddExperience(
            const Gs2::Experience::Model::FStatusPtr& Source,
            const int64 Value,
            const bool Truncate
        )
        {
            if (!Source.IsValid() || !Source->GetExperienceValue().IsSet()) return nullptr;
            int64 ChangedValue = Value;
            if (Truncate)
            {
                if (!Source->GetNextRankUpExperienceValue().IsSet()) return nullptr;
                int64 Remaining;
                if (!SubtractChecked(*Source->GetNextRankUpExperienceValue(),
                    *Source->GetExperienceValue(), Remaining)) return nullptr;
                if (ChangedValue > Remaining) ChangedValue = Remaining;
            }
            int64 Result;
            if (!AddChecked(*Source->GetExperienceValue(), ChangedValue, Result)) return nullptr;
            return WithExperience(Source, Result);
        }

        static Gs2::Experience::Model::FStatusPtr SubExperience(
            const Gs2::Experience::Model::FStatusPtr& Source,
            const int64 Value
        )
        {
            if (!Source.IsValid() || !Source->GetExperienceValue().IsSet()) return nullptr;
            int64 Result;
            if (!SubtractChecked(*Source->GetExperienceValue(), Value, Result) || Result < 0)
            {
                return nullptr;
            }
            return WithExperience(Source, Result);
        }

        static Gs2::Experience::Model::FStatusPtr AddRankCap(
            const Gs2::Experience::Model::FStatusPtr& Source,
            const int64 Value
        )
        {
            if (!Source.IsValid() || !Source->GetRankCapValue().IsSet()) return nullptr;
            int64 Result;
            if (!AddChecked(*Source->GetRankCapValue(), Value, Result)) return nullptr;
            return WithRankCap(Source, Result);
        }

        static Gs2::Experience::Model::FStatusPtr SubRankCap(
            const Gs2::Experience::Model::FStatusPtr& Source,
            const int64 Value
        )
        {
            if (!Source.IsValid() || !Source->GetRankCapValue().IsSet()) return nullptr;
            int64 Result;
            if (!SubtractChecked(*Source->GetRankCapValue(), Value, Result) || Result <= 0)
            {
                return nullptr;
            }
            return WithRankCap(Source, Result);
        }
    };
}
