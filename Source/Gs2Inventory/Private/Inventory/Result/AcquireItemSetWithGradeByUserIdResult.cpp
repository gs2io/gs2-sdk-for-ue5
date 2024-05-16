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

#include "Inventory/Result/AcquireItemSetWithGradeByUserIdResult.h"

namespace Gs2::Inventory::Result
{
    FAcquireItemSetWithGradeByUserIdResult::FAcquireItemSetWithGradeByUserIdResult():
        ItemValue(nullptr),
        StatusValue(nullptr),
        ItemModelValue(nullptr),
        InventoryValue(nullptr),
        OverflowCountValue(TOptional<int64>())
    {
    }

    FAcquireItemSetWithGradeByUserIdResult::FAcquireItemSetWithGradeByUserIdResult(
        const FAcquireItemSetWithGradeByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        StatusValue(From.StatusValue),
        ItemModelValue(From.ItemModelValue),
        InventoryValue(From.InventoryValue),
        OverflowCountValue(From.OverflowCountValue)
    {
    }

    TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FAcquireItemSetWithGradeByUserIdResult::WithItem(
        const TSharedPtr<Model::FItemSet> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FAcquireItemSetWithGradeByUserIdResult::WithStatus(
        const TSharedPtr<Gs2::Grade::Model::FStatus> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FAcquireItemSetWithGradeByUserIdResult::WithItemModel(
        const TSharedPtr<Model::FItemModel> ItemModel
    )
    {
        this->ItemModelValue = ItemModel;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FAcquireItemSetWithGradeByUserIdResult::WithInventory(
        const TSharedPtr<Model::FInventory> Inventory
    )
    {
        this->InventoryValue = Inventory;
        return SharedThis(this);
    }

    TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FAcquireItemSetWithGradeByUserIdResult::WithOverflowCount(
        const TOptional<int64> OverflowCount
    )
    {
        this->OverflowCountValue = OverflowCount;
        return SharedThis(this);
    }

    TSharedPtr<Model::FItemSet> FAcquireItemSetWithGradeByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Gs2::Grade::Model::FStatus> FAcquireItemSetWithGradeByUserIdResult::GetStatus() const
    {
        if (!StatusValue.IsValid())
        {
            return nullptr;
        }
        return StatusValue;
    }

    TSharedPtr<Model::FItemModel> FAcquireItemSetWithGradeByUserIdResult::GetItemModel() const
    {
        if (!ItemModelValue.IsValid())
        {
            return nullptr;
        }
        return ItemModelValue;
    }

    TSharedPtr<Model::FInventory> FAcquireItemSetWithGradeByUserIdResult::GetInventory() const
    {
        if (!InventoryValue.IsValid())
        {
            return nullptr;
        }
        return InventoryValue;
    }

    TOptional<int64> FAcquireItemSetWithGradeByUserIdResult::GetOverflowCount() const
    {
        return OverflowCountValue;
    }

    FString FAcquireItemSetWithGradeByUserIdResult::GetOverflowCountString() const
    {
        if (!OverflowCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), OverflowCountValue.GetValue());
    }

    TSharedPtr<FAcquireItemSetWithGradeByUserIdResult> FAcquireItemSetWithGradeByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAcquireItemSetWithGradeByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FItemSetPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FItemSet::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithStatus(Data->HasField(ANSI_TO_TCHAR("status")) ? [Data]() -> Gs2::Grade::Model::FStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("status")))
                    {
                        return nullptr;
                    }
                    return Gs2::Grade::Model::FStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("status")));
                 }() : nullptr)
            ->WithItemModel(Data->HasField(ANSI_TO_TCHAR("itemModel")) ? [Data]() -> Model::FItemModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("itemModel")))
                    {
                        return nullptr;
                    }
                    return Model::FItemModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("itemModel")));
                 }() : nullptr)
            ->WithInventory(Data->HasField(ANSI_TO_TCHAR("inventory")) ? [Data]() -> Model::FInventoryPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("inventory")))
                    {
                        return nullptr;
                    }
                    return Model::FInventory::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("inventory")));
                 }() : nullptr)
            ->WithOverflowCount(Data->HasField(ANSI_TO_TCHAR("overflowCount")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("overflowCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FAcquireItemSetWithGradeByUserIdResult::ToJson() const
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