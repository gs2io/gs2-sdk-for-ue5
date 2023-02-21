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

#include "SerialKey/Result/UseByUserIdResult.h"

namespace Gs2::SerialKey::Result
{
    FUseByUserIdResult::FUseByUserIdResult():
        ItemValue(nullptr),
        CampaignModelValue(nullptr)
    {
    }

    FUseByUserIdResult::FUseByUserIdResult(
        const FUseByUserIdResult& From
    ):
        ItemValue(From.ItemValue),
        CampaignModelValue(From.CampaignModelValue)
    {
    }

    TSharedPtr<FUseByUserIdResult> FUseByUserIdResult::WithItem(
        const TSharedPtr<Model::FSerialKey> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FUseByUserIdResult> FUseByUserIdResult::WithCampaignModel(
        const TSharedPtr<Model::FCampaignModel> CampaignModel
    )
    {
        this->CampaignModelValue = CampaignModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FSerialKey> FUseByUserIdResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FCampaignModel> FUseByUserIdResult::GetCampaignModel() const
    {
        if (!CampaignModelValue.IsValid())
        {
            return nullptr;
        }
        return CampaignModelValue;
    }

    TSharedPtr<FUseByUserIdResult> FUseByUserIdResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUseByUserIdResult>()
            ->WithItem(Data->HasField("item") ? [Data]() -> Model::FSerialKeyPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("item"))
                    {
                        return nullptr;
                    }
                    return Model::FSerialKey::FromJson(Data->GetObjectField("item"));
                 }() : nullptr)
            ->WithCampaignModel(Data->HasField("campaignModel") ? [Data]() -> Model::FCampaignModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>("campaignModel"))
                    {
                        return nullptr;
                    }
                    return Model::FCampaignModel::FromJson(Data->GetObjectField("campaignModel"));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUseByUserIdResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ItemValue != nullptr && ItemValue.IsValid())
        {
            JsonRootObject->SetObjectField("item", ItemValue->ToJson());
        }
        if (CampaignModelValue != nullptr && CampaignModelValue.IsValid())
        {
            JsonRootObject->SetObjectField("campaignModel", CampaignModelValue->ToJson());
        }
        return JsonRootObject;
    }
}