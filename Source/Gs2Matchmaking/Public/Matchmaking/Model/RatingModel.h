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
    class GS2MATCHMAKING_API FRatingModel final : public FGs2Object, public TSharedFromThis<FRatingModel>
    {
        TOptional<FString> RatingModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<int32> InitialValueValue;
        TOptional<int32> VolatilityValue;

    public:
        FRatingModel();
        FRatingModel(
            const FRatingModel& From
        );
        virtual ~FRatingModel() override = default;

        TSharedPtr<FRatingModel> WithRatingModelId(const TOptional<FString> RatingModelId);
        TSharedPtr<FRatingModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FRatingModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FRatingModel> WithInitialValue(const TOptional<int32> InitialValue);
        TSharedPtr<FRatingModel> WithVolatility(const TOptional<int32> Volatility);

        TOptional<FString> GetRatingModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<int32> GetInitialValue() const;
        FString GetInitialValueString() const;
        TOptional<int32> GetVolatility() const;
        FString GetVolatilityString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetRatingNameFromGrn(const FString Grn);

        static TSharedPtr<FRatingModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRatingModel, ESPMode::ThreadSafe> FRatingModelPtr;
}