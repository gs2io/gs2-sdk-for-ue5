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

#include "SkillTree/Model/Gs2SkillTreeEzNodeModel.h"

namespace Gs2::UE5::SkillTree::Model
{

    TSharedPtr<FEzNodeModel> FEzNodeModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzNodeModel> FEzNodeModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzNodeModel> FEzNodeModel::WithReleaseConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzConsumeAction>>> ReleaseConsumeActions
    )
    {
        this->ReleaseConsumeActionsValue = ReleaseConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzNodeModel> FEzNodeModel::WithReturnAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzAcquireAction>>> ReturnAcquireActions
    )
    {
        this->ReturnAcquireActionsValue = ReturnAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzNodeModel> FEzNodeModel::WithRestrainReturnRate(
        const TOptional<float> RestrainReturnRate
    )
    {
        this->RestrainReturnRateValue = RestrainReturnRate;
        return SharedThis(this);
    }
    TOptional<FString> FEzNodeModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzNodeModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzConsumeAction>>> FEzNodeModel::GetReleaseConsumeActions() const
    {
        return ReleaseConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::SkillTree::Model::FEzAcquireAction>>> FEzNodeModel::GetReturnAcquireActions() const
    {
        return ReturnAcquireActionsValue;
    }
    TOptional<float> FEzNodeModel::GetRestrainReturnRate() const
    {
        return RestrainReturnRateValue;
    }

    FString FEzNodeModel::GetRestrainReturnRateString() const
    {
        if (!RestrainReturnRateValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), RestrainReturnRateValue.GetValue());
    }

    Gs2::SkillTree::Model::FNodeModelPtr FEzNodeModel::ToModel() const
    {
        return MakeShared<Gs2::SkillTree::Model::FNodeModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithReleaseConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::SkillTree::Model::FConsumeAction>>>();
                    if (ReleaseConsumeActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ReleaseConsumeActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithReturnAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::SkillTree::Model::FAcquireAction>>>();
                    if (ReturnAcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ReturnAcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithRestrainReturnRate(RestrainReturnRateValue);
    }

    TSharedPtr<FEzNodeModel> FEzNodeModel::FromModel(const Gs2::SkillTree::Model::FNodeModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzNodeModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithReleaseConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeAction>>>();
                    if (Model->GetReleaseConsumeActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetReleaseConsumeActions())
                    {
                        v->Add(FEzConsumeAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithReturnAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetReturnAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetReturnAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithRestrainReturnRate(Model->GetRestrainReturnRate());
    }
}