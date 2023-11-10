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

#include "Inventory/Model/ItemModel.h"

namespace Gs2::Inventory::Model
{
    FItemModel::FItemModel():
        ItemModelIdValue(TOptional<FString>()),
        NameValue(TOptional<FString>()),
        MetadataValue(TOptional<FString>()),
        StackingLimitValue(TOptional<int64>()),
        AllowMultipleStacksValue(TOptional<bool>()),
        SortValueValue(TOptional<int32>())
    {
    }

    FItemModel::FItemModel(
        const FItemModel& From
    ):
        ItemModelIdValue(From.ItemModelIdValue),
        NameValue(From.NameValue),
        MetadataValue(From.MetadataValue),
        StackingLimitValue(From.StackingLimitValue),
        AllowMultipleStacksValue(From.AllowMultipleStacksValue),
        SortValueValue(From.SortValueValue)
    {
    }

    TSharedPtr<FItemModel> FItemModel::WithItemModelId(
        const TOptional<FString> ItemModelId
    )
    {
        this->ItemModelIdValue = ItemModelId;
        return SharedThis(this);
    }

    TSharedPtr<FItemModel> FItemModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FItemModel> FItemModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FItemModel> FItemModel::WithStackingLimit(
        const TOptional<int64> StackingLimit
    )
    {
        this->StackingLimitValue = StackingLimit;
        return SharedThis(this);
    }

    TSharedPtr<FItemModel> FItemModel::WithAllowMultipleStacks(
        const TOptional<bool> AllowMultipleStacks
    )
    {
        this->AllowMultipleStacksValue = AllowMultipleStacks;
        return SharedThis(this);
    }

    TSharedPtr<FItemModel> FItemModel::WithSortValue(
        const TOptional<int32> SortValue
    )
    {
        this->SortValueValue = SortValue;
        return SharedThis(this);
    }
    TOptional<FString> FItemModel::GetItemModelId() const
    {
        return ItemModelIdValue;
    }
    TOptional<FString> FItemModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FItemModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FItemModel::GetStackingLimit() const
    {
        return StackingLimitValue;
    }

    FString FItemModel::GetStackingLimitString() const
    {
        if (!StackingLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StackingLimitValue.GetValue());
    }
    TOptional<bool> FItemModel::GetAllowMultipleStacks() const
    {
        return AllowMultipleStacksValue;
    }

    FString FItemModel::GetAllowMultipleStacksString() const
    {
        if (!AllowMultipleStacksValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowMultipleStacksValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FItemModel::GetSortValue() const
    {
        return SortValueValue;
    }

    FString FItemModel::GetSortValueString() const
    {
        if (!SortValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), SortValueValue.GetValue());
    }

    TOptional<FString> FItemModel::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModel::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModel::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModel::GetInventoryNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FItemModel::GetItemNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):inventory:(?<namespaceName>.+):model:(?<inventoryName>.+):item:(?<itemName>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FItemModel> FItemModel::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FItemModel>()
            ->WithItemModelId(Data->HasField("itemModelId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("itemModelId", v))
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
            ->WithStackingLimit(Data->HasField("stackingLimit") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("stackingLimit", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithAllowMultipleStacks(Data->HasField("allowMultipleStacks") ? [Data]() -> TOptional<bool>
                {
                    bool v;
                    if (Data->TryGetBoolField("allowMultipleStacks", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<bool>();
                }() : TOptional<bool>())
            ->WithSortValue(Data->HasField("sortValue") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("sortValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FItemModel::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemModelIdValue.IsSet())
        {
            JsonRootObject->SetStringField("itemModelId", ItemModelIdValue.GetValue());
        }
        if (NameValue.IsSet())
        {
            JsonRootObject->SetStringField("name", NameValue.GetValue());
        }
        if (MetadataValue.IsSet())
        {
            JsonRootObject->SetStringField("metadata", MetadataValue.GetValue());
        }
        if (StackingLimitValue.IsSet())
        {
            JsonRootObject->SetStringField("stackingLimit", FString::Printf(TEXT("%lld"), StackingLimitValue.GetValue()));
        }
        if (AllowMultipleStacksValue.IsSet())
        {
            JsonRootObject->SetBoolField("allowMultipleStacks", AllowMultipleStacksValue.GetValue());
        }
        if (SortValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("sortValue", SortValueValue.GetValue());
        }
        return JsonRootObject;
    }

    FString FItemModel::TypeName = "ItemModel";
}