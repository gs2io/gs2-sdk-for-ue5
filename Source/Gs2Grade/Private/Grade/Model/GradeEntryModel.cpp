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

#include "Grade/Model/GradeEntryModel.h"

namespace Gs2::Grade::Model
{
    FGradeEntryModel::FGradeEntryModel():
        MetadataValue(TOptional<FString>()),
        RankCapValueValue(TOptional<int64>()),
        PropertyIdRegexValue(TOptional<FString>()),
        GradeUpPropertyIdRegexValue(TOptional<FString>())
    {
    }

    FGradeEntryModel::FGradeEntryModel(
        const FGradeEntryModel& From
    ):
        MetadataValue(From.MetadataValue),
        RankCapValueValue(From.RankCapValueValue),
        PropertyIdRegexValue(From.PropertyIdRegexValue),
        GradeUpPropertyIdRegexValue(From.GradeUpPropertyIdRegexValue)
    {
    }

    TSharedPtr<FGradeEntryModel> FGradeEntryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FGradeEntryModel> FGradeEntryModel::WithRankCapValue(
        const TOptional<int64> RankCapValue
    )
    {
        this->RankCapValueValue = RankCapValue;
        return SharedThis(this);
    }

    TSharedPtr<FGradeEntryModel> FGradeEntryModel::WithPropertyIdRegex(
        const TOptional<FString> PropertyIdRegex
    )
    {
        this->PropertyIdRegexValue = PropertyIdRegex;
        return SharedThis(this);
    }

    TSharedPtr<FGradeEntryModel> FGradeEntryModel::WithGradeUpPropertyIdRegex(
        const TOptional<FString> GradeUpPropertyIdRegex
    )
    {
        this->GradeUpPropertyIdRegexValue = GradeUpPropertyIdRegex;
        return SharedThis(this);
    }
    TOptional<FString> FGradeEntryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FGradeEntryModel::GetRankCapValue() const
    {
        return RankCapValueValue;
    }

    FString FGradeEntryModel::GetRankCapValueString() const
    {
        if (!RankCapValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RankCapValueValue.GetValue());
    }
    TOptional<FString> FGradeEntryModel::GetPropertyIdRegex() const
    {
        return PropertyIdRegexValue;
    }
    TOptional<FString> FGradeEntryModel::GetGradeUpPropertyIdRegex() const
    {
        return GradeUpPropertyIdRegexValue;
    }

    TSharedPtr<FGradeEntryModel> FGradeEntryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGradeEntryModel>()
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithRankCapValue(Data->HasField("rankCapValue") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("rankCapValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithPropertyIdRegex(Data->HasField("propertyIdRegex") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("propertyIdRegex", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithGradeUpPropertyIdRegex(Data->HasField("gradeUpPropertyIdRegex") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("gradeUpPropertyIdRegex", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FGradeEntryModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (RankCapValueValue.IsSet())
        {
            JsonRootObject->SetStringField("rankCapValue", FString::Printf(TEXT("%lld"), RankCapValueValue.GetValue()));
        }
        if (PropertyIdRegexValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyIdRegex", PropertyIdRegexValue.GetValue());
        }
        if (GradeUpPropertyIdRegexValue.IsSet())
        {
            JsonRootObject->SetStringField("gradeUpPropertyIdRegex", GradeUpPropertyIdRegexValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FGradeEntryModel::TypeName = "GradeEntryModel";
}