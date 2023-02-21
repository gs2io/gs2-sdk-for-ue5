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

#pragma once

#include "CoreMinimal.h"
#include "SerialKey/Model/CampaignModel.h"

namespace Gs2::UE5::SerialKey::Model
{
	class EZGS2_API FEzCampaignModel final : public TSharedFromThis<FEzCampaignModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> EnableCampaignCodeValue;

	public:
        TSharedPtr<FEzCampaignModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzCampaignModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzCampaignModel> WithEnableCampaignCode(const TOptional<bool> EnableCampaignCode);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<bool> GetEnableCampaignCode() const;
        FString GetEnableCampaignCodeString() const;

        Gs2::SerialKey::Model::FCampaignModelPtr ToModel() const;
        static TSharedPtr<FEzCampaignModel> FromModel(Gs2::SerialKey::Model::FCampaignModelPtr Model);
    };
    typedef TSharedPtr<FEzCampaignModel> FEzCampaignModelPtr;
}