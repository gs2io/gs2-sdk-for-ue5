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
#include "Core/Gs2Object.h"

namespace Gs2::SerialKey::Model
{
    class GS2SERIALKEY_API FCampaignModel final : public FGs2Object, public TSharedFromThis<FCampaignModel>
    {
        TOptional<FString> CampaignIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> EnableCampaignCodeValue;

    public:
        FCampaignModel();
        FCampaignModel(
            const FCampaignModel& From
        );
        virtual ~FCampaignModel() override = default;

        TSharedPtr<FCampaignModel> WithCampaignId(const TOptional<FString> CampaignId);
        TSharedPtr<FCampaignModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FCampaignModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCampaignModel> WithEnableCampaignCode(const TOptional<bool> EnableCampaignCode);

        TOptional<FString> GetCampaignId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<bool> GetEnableCampaignCode() const;
        FString GetEnableCampaignCodeString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCampaignModelNameFromGrn(const FString Grn);

        static TSharedPtr<FCampaignModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCampaignModel, ESPMode::ThreadSafe> FCampaignModelPtr;
}