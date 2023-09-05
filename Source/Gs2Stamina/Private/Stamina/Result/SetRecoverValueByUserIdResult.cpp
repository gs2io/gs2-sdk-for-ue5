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

#include "Stamina/Result/SetRecoverValueByUserIdResult.h"

namespace Gs2::Stamina::Result
{
    FSetRecoverValueByUserIdResult::FSetRecoverValueByUserIdResult():
        ItemValue(nullptr),
        OldValue(nullptr),
        StaminaModelValue(nullptr)
    {
    }

    FSetRecoverValueByUserIdResult::FSetRecoverValueByUserIdResult(
        const FSetRecoverValueByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        OldValue(From.OldValue),
        StaminaModelValue(From.StaminaModelValue)
    {
    }

    TSharedPtr<FSetRecoverValueByUserIdResult> FSetRecoverValueByUserIdResult::WithItem(
        const TSharedPtr<Model::FStamina> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByUserIdResult> FSetRecoverValueByUserIdResult::WithOld(
        const TSharedPtr<Model::FStamina> Old
    )
    {
        this->OldValue = Old;
        return SharedThis(this);
    }

    TSharedPtr<FSetRecoverValueByUserIdResult> FSetRecoverValueByUserIdResult::WithStaminaModel(
        const TSharedPtr<Model::FStaminaModel> StaminaModel
    )
    {
        this->StaminaModelValue = StaminaModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStamina> FSetRecoverValueByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FStamina> FSetRecoverValueByUserIdResult::GetOld() const
    {
        if (!OldValue.IsValid())
        {
            return nullptr;
        }
        return OldValue;
    }

    TSharedPtr<Model::FStaminaModel> FSetRecoverValueByUserIdResult::GetStaminaModel() const
    {
        if (!StaminaModelValue.IsValid())
        {
            return nullptr;
        }
        return StaminaModelValue;
    }

    TSharedPtr<FSetRecoverValueByUserIdResult> FSetRecoverValueByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FSetRecoverValueByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStaminaPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStamina::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithOld(Data->HasField("old") ? [Data]() -> Model::FStaminaPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("old"))
                    {
                        return nullptr;
                    }
                    return Model::FStamina::FromJson(Data->GetObjectField("old"));
                 }() : nullptr)
            ->WithStaminaModel(Data->HasField("staminaModel") ? [Data]() -> Model::FStaminaModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("staminaModel"))
                    {
                        return nullptr;
                    }
                    return Model::FStaminaModel::FromJson(Data->GetObjectField("staminaModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FSetRecoverValueByUserIdResult::ToJson() const
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
        if (StaminaModelValue != nullptr && StaminaModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("staminaModel", StaminaModelValue->ToJson());
        }
        return JsonRootObject;
    }
}