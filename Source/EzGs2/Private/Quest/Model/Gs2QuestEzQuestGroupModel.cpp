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

#include "EzGs2/Public/Quest/Model/Gs2QuestEzQuestGroupModel.h"

namespace Gs2::UE5::Quest::Model
{

    TSharedPtr<FEzQuestGroupModel> FEzQuestGroupModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestGroupModel> FEzQuestGroupModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestGroupModel> FEzQuestGroupModel::WithQuests(
        const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>>> Quests
    )
    {
        this->QuestsValue = Quests;
        return SharedThis(this);
    }

    TSharedPtr<FEzQuestGroupModel> FEzQuestGroupModel::WithChallengePeriodEventId(
        const TOptional<FString> ChallengePeriodEventId
    )
    {
        this->ChallengePeriodEventIdValue = ChallengePeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzQuestGroupModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzQuestGroupModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>>> FEzQuestGroupModel::GetQuests() const
    {
        return QuestsValue;
    }
    TOptional<FString> FEzQuestGroupModel::GetChallengePeriodEventId() const
    {
        return ChallengePeriodEventIdValue;
    }

    Gs2::Quest::Model::FQuestGroupModelPtr FEzQuestGroupModel::ToModel() const
    {
        return MakeShared<Gs2::Quest::Model::FQuestGroupModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithQuests([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FQuestModel>>>();
                    if (QuestsValue == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *QuestsValue)
                    {
                        v->Add(v2->ToModel());
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(ChallengePeriodEventIdValue);
    }

    TSharedPtr<FEzQuestGroupModel> FEzQuestGroupModel::FromModel(const Gs2::Quest::Model::FQuestGroupModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzQuestGroupModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithQuests([&]
                {
                    auto v = MakeShared<TArray<TSharedPtr<FEzQuestModel>>>();
                    if (Model->GetQuests() == nullptr)
                    {
                        return v;
                    }
                    for (auto v2 : *Model->GetQuests())
                    {
                        v->Add(FEzQuestModel::FromModel(v2));
                    }
                    return v;
                }()
            )
            ->WithChallengePeriodEventId(Model->GetChallengePeriodEventId());
    }
}