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

#include "Formation/Model/SlotModel.h"

namespace Gs2::Formation::Model
{
    FSlotModel::FSlotModel():
        NameValue(TOptional<FString>()),
        PropertyRegexValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>())
    {
    }

    FSlotModel::FSlotModel(
        const FSlotModel& From
    ):
        NameValue(From.NameValue),
        PropertyRegexValue(From.PropertyRegexValue),
        MetadataValue(From.MetadataValue)
    {
    }

    TSharedPtr<FSlotModel> FSlotModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSlotModel> FSlotModel::WithPropertyRegex(
        const TOptional<FString> PropertyRegex
    )
    {
        this->PropertyRegexValue = PropertyRegex;
        return SharedThis(this);
    }

    TSharedPtr<FSlotModel> FSlotModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }
    TOptional<FString> FSlotModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSlotModel::GetPropertyRegex() const
    {
        return PropertyRegexValue;
    }
    TOptional<FString> FSlotModel::GetMetadata() const
    {
        return MetadataValue;
    }

    TSharedPtr<FSlotModel> FSlotModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSlotModel>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithPropertyRegex(Data->HasField("propertyRegex") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("propertyRegex", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>());
    }

    TSharedPtr<FJsonObject> FSlotModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (PropertyRegexValue.IsSet())
        {
            JsonRootObject->SetStringField("propertyRegex", PropertyRegexValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FSlotModel::TypeName = "SlotModel";
}