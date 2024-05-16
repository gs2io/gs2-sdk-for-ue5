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

#include "LoginReward/Result/DeleteReceiveStatusByUserIdResult.h"

namespace Gs2::LoginReward::Result
{
    FDeleteReceiveStatusByUserIdResult::FDeleteReceiveStatusByUserIdResult():
        ItemValue(nullptr),
        BonusModelValue(nullptr)
    {
    }

    FDeleteReceiveStatusByUserIdResult::FDeleteReceiveStatusByUserIdResult(
        const FDeleteReceiveStatusByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        BonusModelValue(From.BonusModelValue)
    {
    }

    TSharedPtr<FDeleteReceiveStatusByUserIdResult> FDeleteReceiveStatusByUserIdResult::WithItem(
        const TSharedPtr<Model::FReceiveStatus> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FDeleteReceiveStatusByUserIdResult> FDeleteReceiveStatusByUserIdResult::WithBonusModel(
        const TSharedPtr<Model::FBonusModel> BonusModel
    )
    {
        this->BonusModelValue = BonusModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FReceiveStatus> FDeleteReceiveStatusByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FBonusModel> FDeleteReceiveStatusByUserIdResult::GetBonusModel() const
    {
        if (!BonusModelValue.IsValid())
        {
            return nullptr;
        }
        return BonusModelValue;
    }

    TSharedPtr<FDeleteReceiveStatusByUserIdResult> FDeleteReceiveStatusByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDeleteReceiveStatusByUserIdResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FReceiveStatusPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FReceiveStatus::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithBonusModel(Data->HasField(ANSI_TO_TCHAR("bonusModel")) ? [Data]() -> Model::FBonusModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("bonusModel")))
                    {
                        return nullptr;
                    }
                    return Model::FBonusModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("bonusModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FDeleteReceiveStatusByUserIdResult::ToJson() const
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