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

#include "Grade/Model/Gs2GradeEzGradeEntryModel.h"

namespace Gs2::UE5::Grade::Model
{

    TSharedPtr<FEzGradeEntryModel> FEzGradeEntryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzGradeEntryModel> FEzGradeEntryModel::WithRankCapValue(
        const TOptional<int64> RankCapValue
    )
    {
        this->RankCapValueValue = RankCapValue;
        return SharedThis(this);
    }
    TOptional<FString> FEzGradeEntryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzGradeEntryModel::GetRankCapValue() const
    {
        return RankCapValueValue;
    }

    FString FEzGradeEntryModel::GetRankCapValueString() const
    {
        if (!RankCapValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RankCapValueValue.GetValue());
    }

    Gs2::Grade::Model::FGradeEntryModelPtr FEzGradeEntryModel::ToModel() const
    {
        return MakeShared<Gs2::Grade::Model::FGradeEntryModel>()
            ->WithMetadata(MetadataValue)
            ->WithRankCapValue(RankCapValueValue);
    }

    TSharedPtr<FEzGradeEntryModel> FEzGradeEntryModel::FromModel(const Gs2::Grade::Model::FGradeEntryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzGradeEntryModel>()
            ->WithMetadata(Model->GetMetadata())
            ->WithRankCapValue(Model->GetRankCapValue());
    }
}