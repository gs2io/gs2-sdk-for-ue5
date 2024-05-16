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

#include "Grade/Model/DefaultGradeModel.h"

namespace Gs2::Grade::Model
{
    FDefaultGradeModel::FDefaultGradeModel():
        PropertyIdRegexValue(TOptional<FString>()),
        DefaultGradeValueValue(TOptional<int64>())
    {
    }

    FDefaultGradeModel::FDefaultGradeModel(
        const FDefaultGradeModel& From
    ):
        PropertyIdRegexValue(From.PropertyIdRegexValue),
        DefaultGradeValueValue(From.DefaultGradeValueValue)
    {
    }

    TSharedPtr<FDefaultGradeModel> FDefaultGradeModel::WithPropertyIdRegex(
        const TOptional<FString> PropertyIdRegex
    )
    {
        this->PropertyIdRegexValue = PropertyIdRegex;
        return SharedThis(this);
    }

    TSharedPtr<FDefaultGradeModel> FDefaultGradeModel::WithDefaultGradeValue(
        const TOptional<int64> DefaultGradeValue
    )
    {
        this->DefaultGradeValueValue = DefaultGradeValue;
        return SharedThis(this);
    }
    TOptional<FString> FDefaultGradeModel::GetPropertyIdRegex() const
    {
        return PropertyIdRegexValue;
    }
    TOptional<int64> FDefaultGradeModel::GetDefaultGradeValue() const
    {
        return DefaultGradeValueValue;
    }

    FString FDefaultGradeModel::GetDefaultGradeValueString() const
    {
        if (!DefaultGradeValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), DefaultGradeValueValue.GetValue());
    }

    TSharedPtr<FDefaultGradeModel> FDefaultGradeModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDefaultGradeModel>()
            ->WithPropertyIdRegex(Data->HasField(ANSI_TO_TCHAR("propertyIdRegex")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("propertyIdRegex"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDefaultGradeValue(Data->HasField(ANSI_TO_TCHAR("defaultGradeValue")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("defaultGradeValue"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDefaultGradeModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (PropertyIdRegexValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyIdRegex", PropertyIdRegexValue.GetValue());
        }
        if (DefaultGradeValueValue.IsSet())
        {
            JsonRootObject->SetStringField("defaultGradeValue", FString::Printf(TEXT("%lld"), DefaultGradeValueValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FDefaultGradeModel::TypeName = "DefaultGradeModel";
}