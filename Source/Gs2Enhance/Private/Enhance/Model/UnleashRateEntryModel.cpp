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

#include "Enhance/Model/UnleashRateEntryModel.h"

namespace Gs2::Enhance::Model
{
    FUnleashRateEntryModel::FUnleashRateEntryModel():
        GradeValueValue(TOptional<int64>()),
        NeedCountValue(TOptional<int32>())
    {
    }

    FUnleashRateEntryModel::FUnleashRateEntryModel(
        const FUnleashRateEntryModel& From
    ):
        GradeValueValue(From.GradeValueValue),
        NeedCountValue(From.NeedCountValue)
    {
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::WithNeedCount(
        const TOptional<int32> NeedCount
    )
    {
        this->NeedCountValue = NeedCount;
        return SharedThis(this);
    }
    TOptional<int64> FUnleashRateEntryModel::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FUnleashRateEntryModel::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }
    TOptional<int32> FUnleashRateEntryModel::GetNeedCount() const
    {
        return NeedCountValue;
    }

    FString FUnleashRateEntryModel::GetNeedCountString() const
    {
        if (!NeedCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), NeedCountValue.GetValue());
    }

    TSharedPtr<FUnleashRateEntryModel> FUnleashRateEntryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashRateEntryModel>()
            ->WithGradeValue(Data->HasField("gradeValue") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("gradeValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithNeedCount(Data->HasField("needCount") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("needCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUnleashRateEntryModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (GradeValueValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeValue", FString::Printf(TEXT("%lld"), GradeValueValue.GetValue()));
        }
        if (NeedCountValue.IsSet())
        {
            JsonRootObject->SetNumberField("needCount", NeedCountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FUnleashRateEntryModel::TypeName = "UnleashRateEntryModel";
}