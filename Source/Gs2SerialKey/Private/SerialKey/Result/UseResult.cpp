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

#include "SerialKey/Result/UseResult.h"

namespace Gs2::SerialKey::Result
{
    FUseResult::FUseResult():
        ItemValue(nullptr),
        CampaignModelValue(nullptr)
    {
    }

    FUseResult::FUseResult(
        const FUseResult& From
    ):
        ItemValue(From.ItemValue),
        CampaignModelValue(From.CampaignModelValue)
    {
    }

    TSharedPtr<FUseResult> FUseResult::WithItem(
        const TSharedPtr<Model::FSerialKey> Item
    )
    {
        this->ItemValue = Item;
        return SharedThis(this);
    }

    TSharedPtr<FUseResult> FUseResult::WithCampaignModel(
        const TSharedPtr<Model::FCampaignModel> CampaignModel
    )
    {
        this->CampaignModelValue = CampaignModel;
        return SharedThis(this);
    }

    TSharedPtr<Model::FSerialKey> FUseResult::GetItem() const
    {
        if (!ItemValue.IsValid())
        {
            return nullptr;
        }
        return ItemValue;
    }

    TSharedPtr<Model::FCampaignModel> FUseResult::GetCampaignModel() const
    {
        if (!CampaignModelValue.IsValid())
        {
            return nullptr;
        }
        return CampaignModelValue;
    }

    TSharedPtr<FUseResult> FUseResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FUseResult>()
            ->WithItem(Data->HasField(ANSI_TO_TCHAR("item")) ? [Data]() -> Model::FSerialKeyPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("item")))
                    {
                        return nullptr;
                    }
                    return Model::FSerialKey::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("item")));
                 }() : nullptr)
            ->WithCampaignModel(Data->HasField(ANSI_TO_TCHAR("campaignModel")) ? [Data]() -> Model::FCampaignModelPtr
                 {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("campaignModel")))
                    {
                        return nullptr;
                    }
                    return Model::FCampaignModel::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("campaignModel")));
                 }() : nullptr);
    }

    TSharedPtr<FJsonObject> FUseResult::ToJson() const
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