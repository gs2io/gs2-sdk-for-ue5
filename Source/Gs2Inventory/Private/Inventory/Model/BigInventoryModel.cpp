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

#include "Inventory/Model/BigInventoryModel.h"

namespace Gs2::Inventory::Model
{
    FBigInventoryModel::FBigInventoryModel():
        InventoryModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        BigItemModelsValue(nullptr)
    {
    }

    FBigInventoryModel::FBigInventoryModel(
        const FBigInventoryModel& From
    ):
        InventoryModelIdValue(From.InventoryModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        BigItemModelsValue(From.BigItemModelsValue)
    {
    }

    TSharedPtr<FBigInventoryModel> FBigInventoryModel::WithInventoryModelId(
        const TOptional<FString> InventoryModelId
    )
    {
        this->InventoryModelIdValue = InventoryModelId;
        return SharedThis(this);
    }

    TSharedPtr<FBigInventoryModel> FBigInventoryModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FBigInventoryModel> FBigInventoryModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FBigInventoryModel> FBigInventoryModel::WithBigItemModels(
        const TSharedPtr<TArray<TSharedPtr<Model::FBigItemModel>>> BigItemModels
    )
    {
        this->BigItemModelsValue = BigItemModels;
        return SharedThis(this);
    }
    TOptional<FString> FBigInventoryModel::GetInventoryModelId() const
    {
        return InventoryModelIdValue;
    }
    TOptional<FString> FBigInventoryModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FBigInventoryModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TSharedPtr<TArray<TSharedPtr<Model::FBigItemModel>>> FBigInventoryModel::GetBigItemModels() const
    {
        return BigItemModelsValue;
    }

    TOptional<FString> FBigInventoryModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):big:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBigInventoryModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):big:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBigInventoryModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):big:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FBigInventoryModel::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):big:model:(?<inventoryName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FBigInventoryModel> FBigInventoryModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FBigInventoryModel>()
            ->WithInventoryModelId(Data->HasField(ANSI_TO_TCHAR("inventoryModelId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("inventoryModelId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithName(Data->HasField(ANSI_TO_TCHAR("name")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("name"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithMetadata(Data->HasField(ANSI_TO_TCHAR("metadata")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("metadata"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithBigItemModels(Data->HasField(ANSI_TO_TCHAR("bigItemModels")) ? [Data]() -> TSharedPtr<TArray<Model::FBigItemModelPtr>>
                {
                    auto v = MakeShared<TArray<Model::FBigItemModelPtr>>();
                    if (!Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("bigItemModels")) && Data->HasTypedField<EJson::Array>(ANSI_TO_TCHAR("bigItemModels")))
                    {
                        for (auto JsonObjectValue : Data->GetArrayField(ANSI_TO_TCHAR("bigItemModels")))
                        {
                            v->Add(Model::FBigItemModel::FromJson(JsonObjectValue->AsObject()));
                        }
                    }
                    return v;
                 }() : MakeShared<TArray<Model::FBigItemModelPtr>>());
    }

    TSharedPtr<FJsonObject> FBigInventoryModel::ToJson() const
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
        if (BigItemModelsValue != nullptr && BigItemModelsValue.IsValid())
        {
            TArray<TSharedPtr<FJsonValue>> v;
            for (auto JsonObjectValue : *BigItemModelsValue)
            {
                v.Add(MakeShared<FJsonValueObject>(JsonObjectValue->ToJson()));
            }
            JsonRootObject->SetArrayField("bigItemModels", v);
        }
        return JsonRootObject;
    }

    FString FBigInventoryModel::TypeName = "BigInventoryModel";
}