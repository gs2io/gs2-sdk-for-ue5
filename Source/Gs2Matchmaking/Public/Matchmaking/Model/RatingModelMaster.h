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

namespace Gs2::Matchmaking::Model
{
    class GS2MATCHMAKING_API FRatingModelMaster final : public Gs2Object, public TSharedFromThis<FRatingModelMaster>
    {
        TOptional<FString> RatingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<int32> InitialValueValue;
        TOptional<int32> VolatilityValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FRatingModelMaster();
        FRatingModelMaster(
            const FRatingModelMaster& From
        );
        virtual ~FRatingModelMaster() override = default;

        TSharedPtr<FRatingModelMaster> WithRatingModelId(const TOptional<FString> RatingModelId);
        TSharedPtr<FRatingModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FRatingModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRatingModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FRatingModelMaster> WithInitialValue(const TOptional<int32> InitialValue);
        TSharedPtr<FRatingModelMaster> WithVolatility(const TOptional<int32> Volatility);
        TSharedPtr<FRatingModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FRatingModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FRatingModelMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetRatingModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<int32> GetInitialValue() const;
        FString GetInitialValueString() const;
        TOptional<int32> GetVolatility() const;
        FString GetVolatilityString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRatingNameFromGrn(const FString Grn);

        static TSharedPtr<FRatingModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRatingModelMaster, ESPMode::ThreadSafe> FRatingModelMasterPtr;
}