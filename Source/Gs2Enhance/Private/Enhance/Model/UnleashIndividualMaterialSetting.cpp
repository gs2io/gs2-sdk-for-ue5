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

#include "Enhance/Model/UnleashIndividualMaterialSetting.h"

namespace Gs2::Enhance::Model
{
    FUnleashIndividualMaterialSetting::FUnleashIndividualMaterialSetting():
        MatchTypeValue(TOptional<FString>()),
        GradeConditionValue(TOptional<FString>()),
        GradeValueValue(TOptional<int64>()),
        CountValue(TOptional<int32>())
    {
    }

    FUnleashIndividualMaterialSetting::FUnleashIndividualMaterialSetting(
        const FUnleashIndividualMaterialSetting& From
    ):
        MatchTypeValue(From.MatchTypeValue),
        GradeConditionValue(From.GradeConditionValue),
        GradeValueValue(From.GradeValueValue),
        CountValue(From.CountValue)
    {
    }

    TSharedPtr<FUnleashIndividualMaterialSetting> FUnleashIndividualMaterialSetting::WithMatchType(
        const TOptional<FString> MatchType
    )
    {
        this->MatchTypeValue = MatchType;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashIndividualMaterialSetting> FUnleashIndividualMaterialSetting::WithGradeCondition(
        const TOptional<FString> GradeCondition
    )
    {
        this->GradeConditionValue = GradeCondition;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashIndividualMaterialSetting> FUnleashIndividualMaterialSetting::WithGradeValue(
        const TOptional<int64> GradeValue
    )
    {
        this->GradeValueValue = GradeValue;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashIndividualMaterialSetting> FUnleashIndividualMaterialSetting::WithCount(
        const TOptional<int32> Count
    )
    {
        this->CountValue = Count;
        return SharedThis(this);
    }
    TOptional<FString> FUnleashIndividualMaterialSetting::GetMatchType() const
    {
        return MatchTypeValue;
    }
    TOptional<FString> FUnleashIndividualMaterialSetting::GetGradeCondition() const
    {
        return GradeConditionValue;
    }
    TOptional<int64> FUnleashIndividualMaterialSetting::GetGradeValue() const
    {
        return GradeValueValue;
    }

    FString FUnleashIndividualMaterialSetting::GetGradeValueString() const
    {
        if (!GradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), GradeValueValue.GetValue());
    }
    TOptional<int32> FUnleashIndividualMaterialSetting::GetCount() const
    {
        return CountValue;
    }

    FString FUnleashIndividualMaterialSetting::GetCountString() const
    {
        if (!CountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), CountValue.GetValue());
    }

    TSharedPtr<FUnleashIndividualMaterialSetting> FUnleashIndividualMaterialSetting::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashIndividualMaterialSetting>()
            ->WithMatchType(Data->HasField(ANSI_TO_TCHAR("matchType")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("matchType"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGradeCondition(Data->HasField(ANSI_TO_TCHAR("gradeCondition")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("gradeCondition"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGradeValue(Data->HasField(ANSI_TO_TCHAR("gradeValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("gradeValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithCount(Data->HasField(ANSI_TO_TCHAR("count")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("count"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FUnleashIndividualMaterialSetting::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MatchTypeValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("matchType"), MatchTypeValue.GetValue());
        }
        if (GradeConditionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("gradeCondition"), GradeConditionValue.GetValue());
        }
        if (GradeValueValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("gradeValue"), FString::Printf(TEXT("%lld"), GradeValueValue.GetValue()));
        }
        if (CountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("count"), CountValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FUnleashIndividualMaterialSetting::TypeName = "UnleashIndividualMaterialSetting";
}