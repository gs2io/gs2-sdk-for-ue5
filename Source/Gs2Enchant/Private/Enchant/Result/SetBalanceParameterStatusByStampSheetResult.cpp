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

#include "Enchant/Result/SetBalanceParameterStatusByStampSheetResult.h"

namespace Gs2::Enchant::Result
{
    FSetBalanceParameterStatusByStampSheetResult::FSetBalanceParameterStatusByStampSheetResult():
        ItemValue(nullptr),
        OldValue(nullptr)
    {
    }

    FSetBalanceParameterStatusByStampSheetResult::FSetBalanceParameterStatusByStampSheetResult(
        const FSetBalanceParameterStatusByStampSheetResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue)
    {
    }

    TSharedPtr<FSetBalanceParameterStatusByStampSheetResult> FSetBalanceParameterStatusByStampSheetResult::WithItem(
        const TSharedPtr<Model::FBalanceParameterStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetBalanceParameterStatusByStampSheetResult> FSetBalanceParameterStatusByStampSheetResult::WithOld(
        const TSharedPtr<Model::FBalanceParameterStatus> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<Model::FBalanceParameterStatus> FSetBalanceParameterStatusByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FBalanceParameterStatus> FSetBalanceParameterStatusByStampSheetResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<FSetBalanceParameterStatusByStampSheetResult> FSetBalanceParameterStatusByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetBalanceParameterStatusByStampSheetResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FBalanceParameterStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FBalanceParameterStatus::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithOld(Data->HasField("old") ? [Data]() -> Model::FBalanceParameterStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("old"))
                    {
                        return nullptr;
                    }
                    return Model::FBalanceParameterStatus::FromJson(Data->GetObjectField("old"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetBalanceParameterStatusByStampSheetResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (OldValue != nullptr && OldValue.IsValid())
        {
            JsonRootObject->SetObjectField("old", OldValue->ToJson());
        }
        return JsonRootObject;
    }
}