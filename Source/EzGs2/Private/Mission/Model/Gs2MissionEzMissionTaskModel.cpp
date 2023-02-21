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

#include "EzGs2/Public/Mission/Model/Gs2MissionEzMissionTaskModel.h"

namespace Gs2::UE5::Mission::Model
{

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithCounterName(
        const TOptional<FString> CounterName
    )
    {
        this->CounterNameValue = CounterName;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithTargetValue(
        const TOptional<int64> TargetValue
    )
    {
        this->TargetValueValue = TargetValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzAcquireAction>>> CompleteAcquireActions
    )
    {
        this->CompleteAcquireActionsValue = CompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::WithPremiseMissionTaskName(
        const TOptional<FString> PremiseMissionTaskName
    )
    {
        this->PremiseMissionTaskNameValue = PremiseMissionTaskName;
        return SharedThis(this);
    }
    TOptional<FString> FEzMissionTaskModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzMissionTaskModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzMissionTaskModel::GetCounterName() const
    {
        return CounterNameValue;
    }
    TOptional<int64> FEzMissionTaskModel::GetTargetValue() const
    {
        return TargetValueValue;
    }

    FString FEzMissionTaskModel::GetTargetValueString() const
    {
        if (!TargetValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), TargetValueValue.GetValue());
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Mission::Model::FEzAcquireAction>>> FEzMissionTaskModel::GetCompleteAcquireActions() const
    {
        return CompleteAcquireActionsValue;
    }
    TOptional<FString> FEzMissionTaskModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }
    TOptional<FString> FEzMissionTaskModel::GetPremiseMissionTaskName() const
    {
        return PremiseMissionTaskNameValue;
    }

    Gs2::Mission::Model::FMissionTaskModelPtr FEzMissionTaskModel::ToModel() const
    {
        return MakeShared<Gs2::Mission::Model::FMissionTaskModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithCounterName(CounterNameValue)
            ->WithTargetValue(TargetValueValue)
            ->WithCompleteAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Mission::Model::FAcquireAction>>>();
                    if (CompleteAcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *CompleteAcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(ChallengePeriodEventIdValue)
            ->WithPremiseMissionTaskName(PremiseMissionTaskNameValue);
    }

    TSharedPtr<FEzMissionTaskModel> FEzMissionTaskModel::FromModel(const Gs2::Mission::Model::FMissionTaskModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzMissionTaskModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithCounterName(Model->GetCounterName())
            ->WithTargetValue(Model->GetTargetValue())
            ->WithCompleteAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetCompleteAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetCompleteAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(Model->GetChallengePeriodEventId())
            ->WithPremiseMissionTaskName(Model->GetPremiseMissionTaskName());
    }
}