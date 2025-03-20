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
#include "AttributeRange.h"
#include "CapacityOfRole.h"

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FGathering final : public FGs2Object, public TSharedFromThis<FGathering>
    {
        TOptional<FString> GatheringIdValue;
        TOptional<FString> NameValue;
        TSharedPtr<TArray<TSharedPtr<FAttributeRange>>> AttributeRangesValue;
        TSharedPtr<TArray<TSharedPtr<FCapacityOfRole>>> CapacityOfRolesValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> ExpiresAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FGathering();
        FGathering(
            const FGathering& From
        );
        virtual ~FGathering() override = default;

        TSharedPtr<FGathering> WithGatheringId(const TOptional<FString> GatheringId);
        TSharedPtr<FGathering> WithName(const TOptional<FString> Name);
        TSharedPtr<FGathering> WithAttributeRanges(const TSharedPtr<TArray<TSharedPtr<FAttributeRange>>> AttributeRanges);
        TSharedPtr<FGathering> WithCapacityOfRoles(const TSharedPtr<TArray<TSharedPtr<FCapacityOfRole>>> CapacityOfRoles);
        TSharedPtr<FGathering> WithAllowUserIds(const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FGathering> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FGathering> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FGathering> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FGathering> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FGathering> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetGatheringId() const;
        TOptional<FString> GetName() const;
        TSharedPtr<TArray<TSharedPtr<FAttributeRange>>> GetAttributeRanges() const;
        TSharedPtr<TArray<TSharedPtr<FCapacityOfRole>>> GetCapacityOfRoles() const;
        TSharedPtr<TArray<FString>> GetAllowUserIds() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetGatheringNameFromGrn(const FString Grn);

        static TSharedPtr<FGathering> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FGathering, ESPMode::ThreadSafe> FGatheringPtr;
}