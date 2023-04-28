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

#include "Stamina/Result/RecoverStaminaByUserIdResult.h"

namespace Gs2::Stamina::Result
{
    FRecoverStaminaByUserIdResult::FRecoverStaminaByUserIdResult():
        ItemValue(nullptr),
        StaminaModelValue(nullptr),
        OverflowValueValue(TOptional<int32>())
    {
    }

    FRecoverStaminaByUserIdResult::FRecoverStaminaByUserIdResult(
        const FRecoverStaminaByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        StaminaModelValue(From.StaminaModelValue),
        OverflowValueValue(From.OverflowValueValue)
    {
    }

    TSharedPtr<FRecoverStaminaByUserIdResult> FRecoverStaminaByUserIdResult::WithItem(
        const TSharedPtr<Model::FStamina> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FRecoverStaminaByUserIdResult> FRecoverStaminaByUserIdResult::WithStaminaModel(
        const TSharedPtr<Model::FStaminaModel> StaminaModel
    )
    {
        this->StaminaModelValue = StaminaModel;
        return SharedThis(this);
    }

    TSharedPtr<FRecoverStaminaByUserIdResult> FRecoverStaminaByUserIdResult::WithOverflowValue(
        const TOptional<int32> OverflowValue
    )
    {
        this->OverflowValueValue = OverflowValue;
        return SharedThis(this);
    }

    TSharedPtr<Model::FStamina> FRecoverStaminaByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FStaminaModel> FRecoverStaminaByUserIdResult::GetStaminaModel() const
    {
        if (!StaminaModelValue.IsValid())
        {
            return nullptr;
        }
        return StaminaModelValue;
    }

    TOptional<int32> FRecoverStaminaByUserIdResult::GetOverflowValue() const
    {
        return OverflowValueValue;
    }

    FString FRecoverStaminaByUserIdResult::GetOverflowValueString() const
    {
        if (!OverflowValueValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), OverflowValueValue.GetValue());
    }

    TSharedPtr<FRecoverStaminaByUserIdResult> FRecoverStaminaByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRecoverStaminaByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FStaminaPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FStamina::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithStaminaModel(Data->HasField("staminaModel") ? [Data]() -> Model::FStaminaModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("staminaModel"))
                    {
                        return nullptr;
                    }
                    return Model::FStaminaModel::FromJson(Data->GetObjectField("staminaModel"));
                 }() : nullptr)
            ->WithOverflowValue(Data->HasField("overflowValue") ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField("overflowValue", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FRecoverStaminaByUserIdResult::ToJson() const
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
        if (OverflowValueValue.IsSet())
        {
            JsonRootObject->SetNumberField("overflowValue", OverflowValueValue.GetValue());
        }
        return JsonRootObject;
    }
}