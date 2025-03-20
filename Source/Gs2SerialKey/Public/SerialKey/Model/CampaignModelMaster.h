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
    class GS2SERIALKEY_API FCampaignModelMaster final : public FGs2Object, public TSharedFromThis<FCampaignModelMaster>
    {
        TOptional<FString> CampaignIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<bool> EnableCampaignCodeValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FCampaignModelMaster();
        FCampaignModelMaster(
            const FCampaignModelMaster& From
        );
        virtual ~FCampaignModelMaster() override = default;

        TSharedPtr<FCampaignModelMaster> WithCampaignId(const TOptional<FString> CampaignId);
        TSharedPtr<FCampaignModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FCampaignModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FCampaignModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FCampaignModelMaster> WithEnableCampaignCode(const TOptional<bool> EnableCampaignCode);
        TSharedPtr<FCampaignModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FCampaignModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FCampaignModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetCampaignId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<bool> GetEnableCampaignCode() const;
        FString GetEnableCampaignCodeString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetCampaignModelNameFromGrn(const FString Grn);

        static TSharedPtr<FCampaignModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FCampaignModelMaster, ESPMode::ThreadSafe> FCampaignModelMasterPtr;
}