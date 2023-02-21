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

#include "EzGs2/Public/SerialKey/Model/Gs2SerialKeyEzCampaignModel.h"

namespace Gs2::UE5::SerialKey::Model
{

    TSharedPtr<FEzCampaignModel> FEzCampaignModel::WithName(
        const TOptional<FString> Name
    )
    {
        this->NameValue = Name;
        return SharedThis(this);
    }

    TSharedPtr<FEzCampaignModel> FEzCampaignModel::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzCampaignModel> FEzCampaignModel::WithEnableCampaignCode(
        const TOptional<bool> EnableCampaignCode
    )
    {
        this->EnableCampaignCodeValue = EnableCampaignCode;
        return SharedThis(this);
    }
    TOptional<FString> FEzCampaignModel::GetName() const
    {
        return NameValue;
    }
    TOptional<FString> FEzCampaignModel::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<bool> FEzCampaignModel::GetEnableCampaignCode() const
    {
        return EnableCampaignCodeValue;
    }

    FString FEzCampaignModel::GetEnableCampaignCodeString() const
    {
        if (!EnableCampaignCodeValue.IsSet())
        {
            return FString("null");
        }
        return FString(EnableCampaignCodeValue.GetValue() ? "true" : "false");
    }

    Gs2::SerialKey::Model::FCampaignModelPtr FEzCampaignModel::ToModel() const
    {
        return MakeShared<Gs2::SerialKey::Model::FCampaignModel>()
            ->WithName(NameValue)
            ->WithMetadata(MetadataValue)
            ->WithEnableCampaignCode(EnableCampaignCodeValue);
    }

    TSharedPtr<FEzCampaignModel> FEzCampaignModel::FromModel(const Gs2::SerialKey::Model::FCampaignModelPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzCampaignModel>()
            ->WithName(Model->GetName())
            ->WithMetadata(Model->GetMetadata())
            ->WithEnableCampaignCode(Model->GetEnableCampaignCode());
    }
}