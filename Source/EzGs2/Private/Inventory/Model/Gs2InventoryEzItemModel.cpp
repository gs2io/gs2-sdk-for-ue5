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

#include "EzGs2/Public/Inventory/Model/Gs2InventoryEzItemModel.h"

namespace Gs2::UE5::Inventory::Model
{

    TSharedPtr<FEzItemModel> FEzItemModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemModel> FEzItemModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemModel> FEzItemModel::WithStackingLimit(
        const TOptional<int64> StackingLimit
    )
    {
        this->StackingLimitValue = StackingLimit;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemModel> FEzItemModel::WithAllowMultipleStacks(
        const TOptional<bool> AllowMultipleStacks
    )
    {
        this->AllowMultipleStacksValue = AllowMultipleStacks;
        return SharedThis(this);
    }

    TSharedPtr<FEzItemModel> FEzItemModel::WithSortValue(
        const TOptional<int32> SortValue
    )
    {
        this->SortValueValue = SortValue;
        return SharedThis(this);
    }
    TOptional<FString> FEzItemModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzItemModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<int64> FEzItemModel::GetStackingLimit() const
    {
        return StackingLimitValue;
    }

    FString FEzItemModel::GetStackingLimitString() const
    {
        if (!StackingLimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), StackingLimitValue.GetValue());
    }
    TOptional<bool> FEzItemModel::GetAllowMultipleStacks() const
    {
        return AllowMultipleStacksValue;
    }

    FString FEzItemModel::GetAllowMultipleStacksString() const
    {
        if (!AllowMultipleStacksValue.IsSet())
        {
            return FString("null");
        }
        return FString(AllowMultipleStacksValue.GetValue() ? "true" : "false");
    }
    TOptional<int32> FEzItemModel::GetSortValue() const
    {
        return SortValueValue;
    }

    FString FEzItemModel::GetSortValueString() const
    {
        if (!SortValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%ld"), SortValueValue.GetValue());
    }

    Gs2::Inventory::Model::FItemModelPtr FEzItemModel::ToModel() const
    {
        return MakeShared<Gs2::Inventory::Model::FItemModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithStackingLimit(StackingLimitValue)
            ->WithAllowMultipleStacks(AllowMultipleStacksValue)
            ->WithSortValue(SortValueValue);
    }

    TSharedPtr<FEzItemModel> FEzItemModel::FromModel(const Gs2::Inventory::Model::FItemModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzItemModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithStackingLimit(Model->GetStackingLimit())
            ->WithAllowMultipleStacks(Model->GetAllowMultipleStacks())
            ->WithSortValue(Model->GetSortValue());
    }
}