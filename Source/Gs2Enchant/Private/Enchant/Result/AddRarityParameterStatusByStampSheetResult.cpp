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

#include "Enchant/Result/AddRarityParameterStatusByStampSheetResult.h"

namespace Gs2::Enchant::Result
{
    FAddRarityParameterStatusByStampSheetResult::FAddRarityParameterStatusByStampSheetResult():
        ItemValue(nullptr),
        OldValue(nullptr)
    {
    }

    FAddRarityParameterStatusByStampSheetResult::FAddRarityParameterStatusByStampSheetResult(
        const FAddRarityParameterStatusByStampSheetResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue)
    {
    }

    TSharedPtr<FAddRarityParameterStatusByStampSheetResult> FAddRarityParameterStatusByStampSheetResult::WithItem(
        const TSharedPtr<Model::FRarityParameterStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FAddRarityParameterStatusByStampSheetResult> FAddRarityParameterStatusByStampSheetResult::WithOld(
        const TSharedPtr<Model::FRarityParameterStatus> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<Model::FRarityParameterStatus> FAddRarityParameterStatusByStampSheetResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FRarityParameterStatus> FAddRarityParameterStatusByStampSheetResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<FAddRarityParameterStatusByStampSheetResult> FAddRarityParameterStatusByStampSheetResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FAddRarityParameterStatusByStampSheetResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FRarityParameterStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FRarityParameterStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithOld(Data->HasField(ANSI_TO_TCHAR("old")) ? [Data]() -> Model::FRarityParameterStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("old")))
                    {
                        return nullptr;
                    }
                    return Model::FRarityParameterStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("old")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FAddRarityParameterStatusByStampSheetResult::ToJson() const
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