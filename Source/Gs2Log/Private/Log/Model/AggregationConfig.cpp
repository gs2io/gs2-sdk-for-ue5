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

#include "Log/Model/AggregationConfig.h"

namespace Gs2::Log::Model
{
    FAggregationConfig::FAggregationConfig():
        TypeValue(TOptional<FString>()),
        FieldValue(TOptional<FString>())
    {
    }

    FAggregationConfig::FAggregationConfig(
        const FAggregationConfig& From
    ):
        TypeValue(From.TypeValue),
        FieldValue(From.FieldValue)
    {
    }

    TSharedPtr<FAggregationConfig> FAggregationConfig::WithType(
        const TOptional<FString> Type
    )
    {
        this->TypeValue = Type;
        return SharedThis(this);
    }

    TSharedPtr<FAggregationConfig> FAggregationConfig::WithField(
        const TOptional<FString> Field
    )
    {
        this->FieldValue = Field;
        return SharedThis(this);
    }
    TOptional<FString> FAggregationConfig::GetType() const
    {
        return TypeValue;
    }
    TOptional<FString> FAggregationConfig::GetField() const
    {
        return FieldValue;
    }

    TSharedPtr<FAggregationConfig> FAggregationConfig::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAggregationConfig>()
            ->WithType(Data->HasField(ANSI_TO_TCHAR("type")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("type"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithField(Data->HasField(ANSI_TO_TCHAR("field")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("field"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FAggregationConfig::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TypeValue.IsSet())
        {
            JsonRootObject->SetStringField("type", TypeValue.GetValue());
        }
        if (FieldValue.IsSet())
        {
            JsonRootObject->SetStringField("field", FieldValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FAggregationConfig::TypeName = "AggregationConfig";
}