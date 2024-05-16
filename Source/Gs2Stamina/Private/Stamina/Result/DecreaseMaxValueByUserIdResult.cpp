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

#include "Stamina/Result/DecreaseMaxValueByUserIdResult.h"

namespace Gs2::Stamina::Result
{
    FDecreaseMaxValueByUserIdResult::FDecreaseMaxValueByUserIdResult():
        ItemValue(nullptr),
        StaminaModelValue(nullptr)
    {
    }

    FDecreaseMaxValueByUserIdResult::FDecreaseMaxValueByUserIdResult(
        const FDecreaseMaxValueByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        StaminaModelValue(From.StaminaModelValue)
    {
    }

    TSharedPtr<FDecreaseMaxValueByUserIdResult> FDecreaseMaxValueByUserIdResult::WithItem(
        const TSharedPtr<Model::FStamina> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDecreaseMaxValueByUserIdResult> FDecreaseMaxValueByUserIdResult::WithStaminaModel(
        const TSharedPtr<Model::FStaminaModel> StaminaModel
    )
    {
        this->StaminaModelValue = StaminaModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStamina> FDecreaseMaxValueByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FStaminaModel> FDecreaseMaxValueByUserIdResult::GetStaminaModel() const
    {
        if (!StaminaModelValue.IsValid())
        {
            return nullptr;
        }
        return StaminaModelValue;
    }

    TSharedPtr<FDecreaseMaxValueByUserIdResult> FDecreaseMaxValueByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDecreaseMaxValueByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FStaminaPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FStamina::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithStaminaModel(Data->HasField(ANSI_TO_TCHAR("staminaModel")) ? [Data]() -> Model::FStaminaModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("staminaModel")))
                    {
                        return nullptr;
                    }
                    return Model::FStaminaModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("staminaModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDecreaseMaxValueByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (StaminaModelValue != nullptr && StaminaModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("staminaModel", StaminaModelValue->ToJson());
        }
        return JsonRootObject;
    }
}