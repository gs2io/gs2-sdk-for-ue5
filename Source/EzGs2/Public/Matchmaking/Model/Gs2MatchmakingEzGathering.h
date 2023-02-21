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
#include "Matchmaking/Model/Gathering.h"
#include "Gs2MatchmakingEzAttributeRange.h"
#include "Gs2MatchmakingEzCapacityOfRole.h"

namespace Gs2::UE5::Matchmaking::Model
{
	class EZGS2_API FEzGathering final : public TSharedFromThis<FEzGathering>
	{
        TOptional<FString> GatheringIdValue;
        TOptional<FString> NameValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRangesValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRolesValue;
        TSharedPtr<TArray<FString>> AllowUserIdsValue;
        TOptional<FString> MetadataValue;
        TOptional<int64> ExpiresAtValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

	public:
        TSharedPtr<FEzGathering> WithGatheringId(const TOptional<FString> GatheringId);
        TSharedPtr<FEzGathering> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzGathering> WithAttributeRanges(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> AttributeRanges);
        TSharedPtr<FEzGathering> WithCapacityOfRoles(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> CapacityOfRoles);
        TSharedPtr<FEzGathering> WithAllowUserIds(const TSharedPtr<TArray<FString>> AllowUserIds);
        TSharedPtr<FEzGathering> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzGathering> WithExpiresAt(const TOptional<int64> ExpiresAt);
        TSharedPtr<FEzGathering> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FEzGathering> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetGatheringId() const;

        TOptional<FString> GetName() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzAttributeRange>>> GetAttributeRanges() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzCapacityOfRole>>> GetCapacityOfRoles() const;

        TSharedPtr<TArray<FString>> GetAllowUserIds() const;

        TOptional<FString> GetMetadata() const;

        TOptional<int64> GetExpiresAt() const;
        FString GetExpiresAtString() const;

        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        Gs2::Matchmaking::Model::FGatheringPtr ToModel() const;
        static TSharedPtr<FEzGathering> FromModel(Gs2::Matchmaking::Model::FGatheringPtr Model);
    };
    typedef TSharedPtr<FEzGathering> FEzGatheringPtr;
}