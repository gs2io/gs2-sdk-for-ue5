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

#include "Quest/Model/Gs2QuestEzQuestModel.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithQuestModelId(
        const TOptional<FString> QuestModelId
    )
    {
        this->QuestModelIdValue = QuestModelId;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithContents(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzContents>>> Contents
    )
    {
        this->ContentsValue = Contents;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithFirstCompleteAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FirstCompleteAcquireActions
    )
    {
        this->FirstCompleteAcquireActionsValue = FirstCompleteAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithVerifyActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzVerifyAction>>> VerifyActions
    )
    {
        this->VerifyActionsValue = VerifyActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithConsumeActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConsumeAction>>> ConsumeActions
    )
    {
        this->ConsumeActionsValue = ConsumeActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithFailedAcquireActions(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FailedAcquireActions
    )
    {
        this->FailedAcquireActionsValue = FailedAcquireActions;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::WithPremiseQuestNames(
        const TSharedPtr<TArray<FString>> PremiseQuestNames
    )
    {
        this->PremiseQuestNamesValue = PremiseQuestNames;
        return SharedThis(this);
    }
    TOptional<FString> FEzQuestModel::GetQuestModelId() const
    {
        return QuestModelIdValue;
    }
    TOptional<FString> FEzQuestModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzQuestModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzContents>>> FEzQuestModel::GetContents() const
    {
        return ContentsValue;
    }
    TOptional<FString> FEzQuestModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FEzQuestModel::GetFirstCompleteAcquireActions() const
    {
        return FirstCompleteAcquireActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzVerifyAction>>> FEzQuestModel::GetVerifyActions() const
    {
        return VerifyActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConsumeAction>>> FEzQuestModel::GetConsumeActions() const
    {
        return ConsumeActionsValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzAcquireAction>>> FEzQuestModel::GetFailedAcquireActions() const
    {
        return FailedAcquireActionsValue;
    }
    TSharedPtr<TArray<FString>> FEzQuestModel::GetPremiseQuestNames() const
    {
        return PremiseQuestNamesValue;
    }

    Gs2::Quest::Model::FQuestModelPtr FEzQuestModel::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FQuestModel>()
            ->WithQuestModelId(QuestModelIdValue)
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithContents([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FContents>>>();
                    if (ContentsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ContentsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(ChallengePeriodEventIdValue)
            ->WithFirstCompleteAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FAcquireAction>>>();
                    if (FirstCompleteAcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *FirstCompleteAcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithVerifyActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FVerifyAction>>>();
                    if (VerifyActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *VerifyActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FConsumeAction>>>();
                    if (ConsumeActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *ConsumeActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithFailedAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FAcquireAction>>>();
                    if (FailedAcquireActionsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *FailedAcquireActionsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithPremiseQuestNames(PremiseQuestNamesValue);
    }

    TSharedPtr<FEzQuestModel> FEzQuestModel::FromModel(const Gs2::Quest::Model::FQuestModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzQuestModel>()
            ->WithQuestModelId(Model->GetQuestModelId())
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithContents([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzContents>>>();
                    if (Model->GetContents() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetContents())
                    {
                        v->Add(FEzContents::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(Model->GetChallengePeriodEventId())
            ->WithFirstCompleteAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetFirstCompleteAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetFirstCompleteAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithVerifyActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzVerifyAction>>>();
                    if (Model->GetVerifyActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetVerifyActions())
                    {
                        v->Add(FEzVerifyAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithConsumeActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzConsumeAction>>>();
                    if (Model->GetConsumeActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetConsumeActions())
                    {
                        v->Add(FEzConsumeAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithFailedAcquireActions([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzAcquireAction>>>();
                    if (Model->GetFailedAcquireActions() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetFailedAcquireActions())
                    {
                        v->Add(FEzAcquireAction::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithPremiseQuestNames(Model->GetPremiseQuestNames());
    }
}