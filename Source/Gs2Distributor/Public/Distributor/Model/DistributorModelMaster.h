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

namespace Gs2::Distributor::Model
{
    class GS2DISTRIBUTOR_API FDistributorModelMaster final : public TSharedFromThis<FDistributorModelMaster>
    {
        TOptional<FString> DistributorModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> InboxNamespaceIdValue;
        TSharedPtr<TArray<FString>> WhiteListTargetIdsValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FDistributorModelMaster();
        FDistributorModelMaster(
            const FDistributorModelMaster& From
        );
        ~FDistributorModelMaster() = default;

        TSharedPtr<FDistributorModelMaster> WithDistributorModelId(const TOptional<FString> DistributorModelId);
        TSharedPtr<FDistributorModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FDistributorModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FDistributorModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FDistributorModelMaster> WithInboxNamespaceId(const TOptional<FString> InboxNamespaceId);
        TSharedPtr<FDistributorModelMaster> WithWhiteListTargetIds(const TSharedPtr<TArray<FString>> WhiteListTargetIds);
        TSharedPtr<FDistributorModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FDistributorModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetDistributorModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetInboxNamespaceId() const;
        TSharedPtr<TArray<FString>> GetWhiteListTargetIds() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetDistributorNameFromGrn(const FString Grn);

        static TSharedPtr<FDistributorModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDistributorModelMaster, ESPMode::ThreadSafe> FDistributorModelMasterPtr;
}