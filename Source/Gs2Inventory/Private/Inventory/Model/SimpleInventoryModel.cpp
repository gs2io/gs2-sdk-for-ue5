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

#include "Inventory/Model/SimpleInventoryModel.h"

namespace Gs2::Inventory::Model
{
    FSimpleInventoryModel::FSimpleInventoryModel():
        InventoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        SimpleItemModelsValue(nullptr)
    {
    }

    FSimpleInventoryModel::FSimpleInventoryModel(
        const FSimpleInventoryModel& From
    ):
        InventoryModelIdValue(From.InventoryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        SimpleItemModelsValue(From.SimpleItemModelsValue)
    {
    }

    TSharedPtr<FSimpleInventoryModel> FSimpleInventoryModel::WithInventoryModelId(
        const TOptional<FString> InventoryModelId
    )
    {
        this->InventoryModelIdValue = InventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FSimpleInventoryModel> FSimpleInventoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FSimpleInventoryModel> FSimpleInventoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FSimpleInventoryModel> FSimpleInventoryModel::WithSimpleItemModels(
        const TSharedPtr<TArray<TSharedPtr<Model::FSimpleItemModel>>> SimpleItemModels
    )
    {
        this->SimpleItemModelsValue = SimpleItemModels;
        return SharedThis(this);
    }
    TOptional<FString> FSimpleInventoryModel::GetInventoryModelId() const
    {
        return InventoryModelIdValue;
    }
    TOptional<FString> FSimpleInventoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FSimpleInventoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FSimpleItemModel>>> FSimpleInventoryModel::GetSimpleItemModels() const
    {
        return SimpleItemModelsValue;
    }

    TOptional<FString> FSimpleInventoryModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):simple:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSimpleInventoryModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):simple:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSimpleInventoryModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):simple:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FSimpleInventoryModel::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):simple:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FSimpleInventoryModel> FSimpleInventoryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSimpleInventoryModel>()
            ->WithInventoryModelId(Data->HasField("inventoryModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("inventoryModelId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField("name") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("name", v))
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
                }() : TOptional<FString>())
            ->WithSimpleItemModels(Data->HasField("simpleItemModels") ? [Data]() -> TSharedPtr<TArray<Model::FSimpleItemModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FSimpleItemModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>("simpleItemModels") && Data->HasTypedField<EJson::Array>("simpleItemModels"))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField("simpleItemModels"))
                        {
                            v->Add(Model::FSimpleItemModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FSimpleItemModelPtr>>());
    }

    TSharedPtr<FJsonObject> FSimpleInventoryModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (InventoryModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("inventoryModelId", InventoryModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (SimpleItemModelsValue != nullptr && SimpleItemModelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *SimpleItemModelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("simpleItemModels", v);
        }
        return JsonRootObject;
    }

    FString FSimpleInventoryModel::TypeName = "SimpleInventoryModel";
}