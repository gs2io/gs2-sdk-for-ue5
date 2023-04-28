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

#include "Showcase/Model/SalesItemGroup.h"

namespace Gs2::Showcase::Model
{
    FSalesItemGroup::FSalesItemGroup():
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        SalesItemsValue(nullptr)
    {
    }

    FSalesItemGroup::FSalesItemGroup(
        const FSalesItemGroup& From
    ):
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        SalesItemsValue(From.SalesItemsValue)
    {
    }

    TSharedPtr<FSalesItemGroup> FSalesItemGroup::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroup> FSalesItemGroup::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSalesItemGroup> FSalesItemGroup::WithSalesItems(
        const TSharedPtr<TArray<TSharedPtr<Model::FSalesItem>>> SalesItems
    )
    {
        this->SalesItemsValue = SalesItems;
        return SharedThis(this);
    }
    TOptional<FString> FSalesItemGroup::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSalesItemGroup::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FSalesItem>>> FSalesItemGroup::GetSalesItems() const
    {
        return SalesItemsValue;
    }

    TSharedPtr<FSalesItemGroup> FSalesItemGroup::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSalesItemGroup>()
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("name", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField("metadata") ? [Data]() -> TOptional<FString>
                {
                    FString v;
                    if (Data->TryGetStringField("metadata", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithSalesItems(Data->HasField("salesItems") ? [Data]() -> TSharedPtr<TArray<Model::FSalesItemPtr>>
                {
                    auto v = MakeShared<TArray<Model::FSalesItemPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("salesItems") && Data->HasTypedField<EJson::Array>("salesItems"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("salesItems"))
                        {
                            v->Add(Model::FSalesItem::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSalesItemPtr>>());
    }

    TSharedPtr<FJsonObject> FSalesItemGroup::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (SalesItemsValue != nullptr && SalesItemsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SalesItemsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("salesItems", v);
        }
        return JsonRootObject;
    }

    FString FSalesItemGroup::TypeName = "SalesItemGroup";
}