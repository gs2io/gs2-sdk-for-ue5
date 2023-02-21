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

#include "EzGs2/Public/SerialKey/Model/Gs2SerialKeyEzSerialKey.h"

namespace Gs2::UE5::SerialKey::Model
{

    TSharedPtr<FEzSerialKey> FEzSerialKey::WithCampaignModelName(
        const TOptional<FString> CampaignModelName
    )
    {
        this->CampaignModelNameValue = CampaignModelName;
        return SharedThis(this);
    }

    TSharedPtr<FEzSerialKey> FEzSerialKey::WithMetadata(
        const TOptional<FString> Metadata
    )
    {
        this->MetadataValue = Metadata;
        return SharedThis(this);
    }

    TSharedPtr<FEzSerialKey> FEzSerialKey::WithCode(
        const TOptional<FString> Code
    )
    {
        this->CodeValue = Code;
        return SharedThis(this);
    }

    TSharedPtr<FEzSerialKey> FEzSerialKey::WithStatus(
        const TOptional<FString> Status
    )
    {
        this->StatusValue = Status;
        return SharedThis(this);
    }
    TOptional<FString> FEzSerialKey::GetCampaignModelName() const
    {
        return CampaignModelNameValue;
    }
    TOptional<FString> FEzSerialKey::GetMetadata() const
    {
        return MetadataValue;
    }
    TOptional<FString> FEzSerialKey::GetCode() const
    {
        return CodeValue;
    }
    TOptional<FString> FEzSerialKey::GetStatus() const
    {
        return StatusValue;
    }

    Gs2::SerialKey::Model::FSerialKeyPtr FEzSerialKey::ToModel() const
    {
        return MakeShared<Gs2::SerialKey::Model::FSerialKey>()
            ->WithCampaignModelName(CampaignModelNameValue)
            ->WithMetadata(MetadataValue)
            ->WithCode(CodeValue)
            ->WithStatus(StatusValue);
    }

    TSharedPtr<FEzSerialKey> FEzSerialKey::FromModel(const Gs2::SerialKey::Model::FSerialKeyPtr Model)
    {
        if (Model == nullptr)
        {
            return nullptr;
        }
        return MakeShared<FEzSerialKey>()
            ->WithCampaignModelName(Model->GetCampaignModelName())
            ->WithMetadata(Model->GetMetadata())
            ->WithCode(Model->GetCode())
            ->WithStatus(Model->GetStatus());
    }
}