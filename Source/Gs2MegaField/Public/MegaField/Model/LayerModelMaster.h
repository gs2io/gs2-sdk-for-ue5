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

namespace Gs2::MegaField::Model
{
    class GS2MEGAFIELD_API FLayerModelMaster final : public TSharedFromThis<FLayerModelMaster>
    {
        TOptional<FString> LayerModelMasterIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FLayerModelMaster();
        FLayerModelMaster(
            const FLayerModelMaster& From
        );
        ~FLayerModelMaster() = default;

        TSharedPtr<FLayerModelMaster> WithLayerModelMasterId(const TOptional<FString> LayerModelMasterId);
        TSharedPtr<FLayerModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FLayerModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FLayerModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FLayerModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FLayerModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetLayerModelMasterId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetAreaModelNameFromGrn(const FString Grn);
        static TOptional<FString> GetLayerModelNameFromGrn(const FString Grn);

        static TSharedPtr<FLayerModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLayerModelMaster, ESPMode::ThreadSafe> FLayerModelMasterPtr;
}