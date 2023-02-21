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
    class GS2MEGAFIELD_API FAreaModelMaster final : public TSharedFromThis<FAreaModelMaster>
    {
        TOptional<FString> AreaModelMasterIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FAreaModelMaster();
        FAreaModelMaster(
            const FAreaModelMaster& From
        );
        ~FAreaModelMaster() = default;

        TSharedPtr<FAreaModelMaster> WithAreaModelMasterId(const TOptional<FString> AreaModelMasterId);
        TSharedPtr<FAreaModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FAreaModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FAreaModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FAreaModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FAreaModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetAreaModelMasterId() const;
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

        static TSharedPtr<FAreaModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FAreaModelMaster, ESPMode::ThreadSafe> FAreaModelMasterPtr;
}