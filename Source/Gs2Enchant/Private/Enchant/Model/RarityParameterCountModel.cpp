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

#include "Enchant/Model/RarityParameterCountModel.h"

namespace Gs2::Enchant::Model
{
    FRarityParameterCountModel::FRarityParameterCountModel():
        CountValue(TOptional<int32>()),
        WeightValue(TOptional<int32>())
    {
    }

    FRarityParameterCountModel::FRarityParameterCountModel(
        const FRarityParameterCountModel& From
    ):
        CountValue(From.CountValue),
        WeightValue(From.WeightValue)
    {
    }

    TSharedPtr<FRarityParameterCountModel> FRarityParameterCountModel::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }

    TSharedPtr<FRarityParameterCountModel> FRarityParameterCountModel::WithWeight(
        const TOptional<int32> Weight
    )
    {
        this->WeightValue = Weight;
        return SharedThis(this);
    }
    TOptional<int32> FRarityParameterCountModel::GetCount() const
    {
        return CountValue;
    }

    FString FRarityParameterCountModel::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }
    TOptional<int32> FRarityParameterCountModel::GetWeight() const
    {
        return WeightValue;
    }

    FString FRarityParameterCountModel::GetWeightString() const
    {
        if (!WeightValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), WeightValue.GetValue());
    }

    TSharedPtr<FRarityParameterCountModel> FRarityParameterCountModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRarityParameterCountModel>()
            ->WithCount(Data->HasField("count") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("count", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithWeight(Data->HasField("weight") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("weight", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FRarityParameterCountModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField("count", CountValue.GetValue());
        }
        if (WeightValue.IsSet())
        {
            JsonRootObject->SetNumberField("weight", WeightValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FRarityParameterCountModel::TypeName = "RarityParameterCountModel";
}