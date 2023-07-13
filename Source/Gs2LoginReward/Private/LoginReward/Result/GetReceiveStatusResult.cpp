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

#include "LoginReward/Result/GetReceiveStatusResult.h"

namespace Gs2::LoginReward::Result
{
    FGetReceiveStatusResult::FGetReceiveStatusResult():
        ItemValue(nullptr),
        BonusModelValue(nullptr)
    {
    }

    FGetReceiveStatusResult::FGetReceiveStatusResult(
        const FGetReceiveStatusResult& From
    ):
        ItemValue(From.ItemValue),
        BonusModelValue(From.BonusModelValue)
    {
    }

    TSharedPtr<FGetReceiveStatusResult> FGetReceiveStatusResult::WithItem(
        const TSharedPtr<Model::FReceiveStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FGetReceiveStatusResult> FGetReceiveStatusResult::WithBonusModel(
        const TSharedPtr<Model::FBonusModel> BonusModel
    )
    {
        this->BonusModelValue = BonusModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FReceiveStatus> FGetReceiveStatusResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FBonusModel> FGetReceiveStatusResult::GetBonusModel() const
    {
        if (!BonusModelValue.IsValid())
        {
            return nullptr;
        }
        return BonusModelValue;
    }

    TSharedPtr<FGetReceiveStatusResult> FGetReceiveStatusResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FGetReceiveStatusResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FReceiveStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FReceiveStatus::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithBonusModel(Data->HasField("bonusModel") ? [Data]() -> Model::FBonusModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("bonusModel"))
                    {
                        return nullptr;
                    }
                    return Model::FBonusModel::FromJson(Data->GetObjectField("bonusModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FGetReceiveStatusResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (BonusModelValue != nullptr && BonusModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("bonusModel", BonusModelValue->ToJson());
        }
        return JsonRootObject;
    }
}