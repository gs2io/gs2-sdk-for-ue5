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

#include "Enhance/Model/UnleashMaterialSelection.h"

namespace Gs2::Enhance::Model
{
    FUnleashMaterialSelection::FUnleashMaterialSelection():
        NameValue(TOptional<FString>()),
        ItemSetIdsValue(nullptr)
    {
    }

    FUnleashMaterialSelection::FUnleashMaterialSelection(
        const FUnleashMaterialSelection& From
    ):
        NameValue(From.NameValue),
        ItemSetIdsValue(From.ItemSetIdsValue)
    {
    }

    TSharedPtr<FUnleashMaterialSelection> FUnleashMaterialSelection::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FUnleashMaterialSelection> FUnleashMaterialSelection::WithItemSetIds(
        const TSharedPtr<TArray<FString>> ItemSetIds
    )
    {
        this->ItemSetIdsValue = ItemSetIds;
        return SharedThis(this);
    }
    TOptional<FString> FUnleashMaterialSelection::GetName() const
    {
        return NameValue;
    }
    TSharedPtr<TArray<FString>> FUnleashMaterialSelection::GetItemSetIds() const
    {
        return ItemSetIdsValue;
    }

    TSharedPtr<FUnleashMaterialSelection> FUnleashMaterialSelection::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUnleashMaterialSelection>()
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithItemSetIds(Data->HasField(ANSI_TO_TCHAR("itemSetIds")) ? [Data]() -> TSharedPtr<TArray<FString>>
                {
                    if (!Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("itemSetIds")))
                    {
                        return nullptr;
                    }
                    auto v = MakeShared<TArray<FString>>();
                    for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("itemSetIds")))
                    {
                        v->Add(JsonObjectValue->AsString());
                    }
                    return v;
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUnleashMaterialSelection::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("name"), NameValue.GetValue());
        }
        if (ItemSetIdsValue != nullptr && ItemSetIdsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *ItemSetIdsValue)
            {
                v.Add(MakeShared<FJsonValueString>(JsonObjectValue));
            }
            JsonRootObject->SetArrayField(TEXT("itemSetIds"), v);
        }
        return JsonRootObject;
    }

    FString FUnleashMaterialSelection::TypeName = "UnleashMaterialSelection";
}