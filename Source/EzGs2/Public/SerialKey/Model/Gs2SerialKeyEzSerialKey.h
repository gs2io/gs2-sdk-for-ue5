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
#include "SerialKey/Model/SerialKey.h"

namespace Gs2::UE5::SerialKey::Model
{
	class EZGS2_API FEzSerialKey final : public TSharedFromThis<FEzSerialKey>
	{
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> CodeValue;
        TOptional<FString> StatusValue;

	public:
        TSharedPtr<FEzSerialKey> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FEzSerialKey> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzSerialKey> WithCode(const TOptional<FString> Code);
        TSharedPtr<FEzSerialKey> WithStatus(const TOptional<FString> Status);

        TOptional<FString> GetCampaignModelName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetCode() const;

        TOptional<FString> GetStatus() const;

        Gs2::SerialKey::Model::FSerialKeyPtr ToModel() const;
        static TSharedPtr<FEzSerialKey> FromModel(Gs2::SerialKey::Model::FSerialKeyPtr Model);
    };
    typedef TSharedPtr<FEzSerialKey> FEzSerialKeyPtr;
}