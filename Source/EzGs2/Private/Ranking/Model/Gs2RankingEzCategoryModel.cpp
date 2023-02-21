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

#include "EzGs2/Public/Ranking/Model/Gs2RankingEzCategoryModel.h"

namespace Gs2::UE5::Ranking::Model
{

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithEntryPeriodEventId(
        const TOptional<FString> EntryPeriodEventId
    )
    {
        this->EntryPeriodEventIdValue = EntryPeriodEventId;
        return SharedThis(this);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::WithAccessPeriodEventId(
        const TOptional<FString> AccessPeriodEventId
    )
    {
        this->AccessPeriodEventIdValue = AccessPeriodEventId;
        return SharedThis(this);
    }
    TOptional<FString> FEzCategoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzCategoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzCategoryModel::GetEntryPeriodEventId() const
    {
        return EntryPeriodEventIdValue;
    }
    TOptional<FString> FEzCategoryModel::GetAccessPeriodEventId() const
    {
        return AccessPeriodEventIdValue;
    }

    Gs2::Ranking::Model::FCategoryModelPtr FEzCategoryModel::ToModel() const
    {
        return MakeShared<Gs2::Ranking::Model::FCategoryModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithEntryPeriodEventId(EntryPeriodEventIdValue)
            ->WithAccessPeriodEventId(AccessPeriodEventIdValue);
    }

    TSharedPtr<FEzCategoryModel> FEzCategoryModel::FromModel(const Gs2::Ranking::Model::FCategoryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCategoryModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithEntryPeriodEventId(Model->GetEntryPeriodEventId())
            ->WithAccessPeriodEventId(Model->GetAccessPeriodEventId());
    }
}