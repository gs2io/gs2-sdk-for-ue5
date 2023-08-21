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
    class GS2SERIALKEY_API FSerialKey final : public Gs2Object, public TSharedFromThis<FSerialKey>
    {
        TOptional<FString> SerialKeyIdValue;
        TOptional<FString> CampaignModelNameValue;
        TOptional<FString> CodeValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> StatusValue;
        TOptional<FString> UsedUserIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UsedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FSerialKey();
        FSerialKey(
            const FSerialKey& From
        );
        virtual ~FSerialKey() override = default;

        TSharedPtr<FSerialKey> WithSerialKeyId(const TOptional<FString> SerialKeyId);
        TSharedPtr<FSerialKey> WithCampaignModelName(const TOptional<FString> CampaignModelName);
        TSharedPtr<FSerialKey> WithCode(const TOptional<FString> Code);
        TSharedPtr<FSerialKey> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FSerialKey> WithStatus(const TOptional<FString> Status);
        TSharedPtr<FSerialKey> WithUsedUserId(const TOptional<FString> UsedUserId);
        TSharedPtr<FSerialKey> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FSerialKey> WithUsedAt(const TOptional<int64> UsedAt);
        TSharedPtr<FSerialKey> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FSerialKey> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetSerialKeyId() const;
        TOptional<FString> GetCampaignModelName() const;
        TOptional<FString> GetCode() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetStatus() const;
        TOptional<FString> GetUsedUserId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUsedAt() const;
        FString GetUsedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetSerialKeyCodeFromGrn(const FString Grn);

        static TSharedPtr<FSerialKey> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FSerialKey, ESPMode::ThreadSafe> FSerialKeyPtr;
}