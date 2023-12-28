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

#include "Inventory/Result/AcquireItemSetWithGradeByStampSheetResult.h"

namespace Gs2::Inventory::Result
{
    FAcquireItemSetWithGradeByStampSheetResult::FAcquireItemSetWithGradeByStampSheetResult():
        ItemValue(nullptr),
        StatusValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr),
        OverflowCountValue(TOptional<int64>())
    {
    }

    FAcquireItemSetWithGradeByStampSheetResult::FAcquireItemSetWithGradeByStampSheetResult(
        const FAcquireItemSetWithGradeByStampSheetResult& From
    ):
        ItemValue(From.ItemValue),
        StatusValue(From.StatusValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue),
        OverflowCountValue(From.OverflowCountValue)
    {
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FAcquireItemSetWithGradeByStampSheetResult::WithItem(
        const TSharedPtr<Model::FItemSet> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FAcquireItemSetWithGradeByStampSheetResult::WithStatus(
        const TSharedPtr<Gs2::Grade::Model::FStatus> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FAcquireItemSetWithGradeByStampSheetResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FAcquireItemSetWithGradeByStampSheetResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FAcquireItemSetWithGradeByStampSheetResult::WithOverflowCount(
        const TOptional<int64> OverflowCount
    )
    {
        this->OverflowCountValue = OverflowCount;
        return SharedThis(this);
    }

    TSharedPtr<Model::FItemSet> FAcquireItemSetWithGradeByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Gs2::Grade::Model::FStatus> FAcquireItemSetWithGradeByStampSheetResult::GetStatus() const
    {
        if (!StatusValue.IsValid())
        {
            return nullptr;
        }
        return StatusValue;
    }

    TSharedPtr<Model::FItemModel> FAcquireItemSetWithGradeByStampSheetResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FAcquireItemSetWithGradeByStampSheetResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TOptional<int64> FAcquireItemSetWithGradeByStampSheetResult::GetOverflowCount() const
    {
        return OverflowCountValue;
    }

    FString FAcquireItemSetWithGradeByStampSheetResult::GetOverflowCountString() const
    {
        if (!OverflowCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), OverflowCountValue.GetValue());
    }

    TSharedPtr<FAcquireItemSetWithGradeByStampSheetResult> FAcquireItemSetWithGradeByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireItemSetWithGradeByStampSheetResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FItemSetPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FItemSet::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithStatus(Data->HasField("status") ? [Data]() -> Gs2::Grade::Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("status"))
                    {
                        return nullptr;
                    }
                    return Gs2::Grade::Model::FStatus::FromJson(Data->GetObjectField("status"));
                 }() : nullptr)
            ->WithItemModel(Data->HasField("itemModel") ? [Data]() -> Model::FItemModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("itemModel"))
                    {
                        return nullptr;
                    }
                    return Model::FItemModel::FromJson(Data->GetObjectField("itemModel"));
                 }() : nullptr)
            ->WithInventory(Data->HasField("inventory") ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("inventory"))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField("inventory"));
                 }() : nullptr)
            ->WithOverflowCount(Data->HasField("overflowCount") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("overflowCount", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FAcquireItemSetWithGradeByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (StatusValue != nullptr && StatusValue.IsValid())
        {
            JsonRootObject->SetObjectField("status", StatusValue->ToJson());
        }
        if (ItemModelValue != nullptr && ItemModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("itemModel", ItemModelValue->ToJson());
        }
        if (InventoryValue != nullptr && InventoryValue.IsValid())
        {
            JsonRootObject->SetObjectField("inventory", InventoryValue->ToJson());
        }
        if (OverflowCountValue.IsSet())
        {
            JsonRootObject->SetStringField("overflowCount", FString::Printf(TEXT("%lld"), OverflowCountValue.GetValue()));
        }
        return JsonRootObject;
    }
}