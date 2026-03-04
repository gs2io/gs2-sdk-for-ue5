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

#include "Enhance/Model/Gs2EnhanceEzUnleashRateEntryModel.h"

namespace Gs2::UE5::Enhance::Model
{

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::WithNeedCount(
        const TOptional<int32> NeedCount
    )
    {
        this->NeedCountValue = NeedCount;
        return SharedThis(this);
    }
    TOptional<int64> FEzUnleashRateEntryModel::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FEzUnleashRateEntryModel::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }
    TOptional<int32> FEzUnleashRateEntryModel::GetNeedCount() const
    {
        return NeedCountValue;
    }

    FString FEzUnleashRateEntryModel::GetNeedCountString() const
    {
        if (!NeedCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NeedCountValue.GetValue());
    }

    Gs2::Enhance::Model::FUnleashRateEntryModelPtr FEzUnleashRateEntryModel::ToModel() const
    {
        return MakeShared<Gs2::Enhance::Model::FUnleashRateEntryModel>()
            ->WithGradeValue(GradeValueValue)
            ->WithNeedCount(NeedCountValue);
    }

    TSharedPtr<FEzUnleashRateEntryModel> FEzUnleashRateEntryModel::FromModel(const Gs2::Enhance::Model::FUnleashRateEntryModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzUnleashRateEntryModel>()
            ->WithGradeValue(Model->GetGradeValue())
            ->WithNeedCount(Model->GetNeedCount());
    }
}