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

#include "Deploy/Model/OutputField.h"

namespace Gs2::Deploy::Model
{
    FOutputField::FOutputField():
        NameValue(TOptional<FString>()),
        FieldNameValue(TOptional<FString>())
    {
    }

    FOutputField::FOutputField(
        const FOutputField& From
    ):
        NameValue(From.NameValue),
        FieldNameValue(From.FieldNameValue)
    {
    }

    TSharedPtr<FOutputField> FOutputField::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FOutputField> FOutputField::WithFieldName(
        const TOptional<FString> FieldName
    )
    {
        this->FieldNameValue = FieldName;
        return SharedThis(this);
    }
    TOptional<FString> FOutputField::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FOutputField::GetFieldName() const
    {
        return FieldNameValue;
    }

    TSharedPtr<FOutputField> FOutputField::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FOutputField>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithFieldName(Data->HasField(ANSI_TO_TCHAR("fieldName")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("fieldName"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FOutputField::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (FieldNameValue.IsSet())
        {
            JsonRootObject->SetStringField("fieldName", FieldNameValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FOutputField::TypeName = "OutputField";
}