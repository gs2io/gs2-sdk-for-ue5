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

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FPrizeLimit final : public TSharedFromThis<FPrizeLimit>
    {
        TOptional<FString> PrizeLimitIdValue;
        TOptional<FString> PrizeIdValue;
        TOptional<int32> DrawnCountValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FPrizeLimit();
        FPrizeLimit(
            const FPrizeLimit& From
        );
        ~FPrizeLimit() = default;

        TSharedPtr<FPrizeLimit> WithPrizeLimitId(const TOptional<FString> PrizeLimitId);
        TSharedPtr<FPrizeLimit> WithPrizeId(const TOptional<FString> PrizeId);
        TSharedPtr<FPrizeLimit> WithDrawnCount(const TOptional<int32> DrawnCount);
        TSharedPtr<FPrizeLimit> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPrizeLimit> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetPrizeLimitId() const;
        TOptional<FString> GetPrizeId() const;
        TOptional<int32> GetDrawnCount() const;
        FString GetDrawnCountString() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetPrizeTableNameFromGrn(const FString Grn);
        static TOptional<FString> GetPrizeIdFromGrn(const FString Grn);

        static TSharedPtr<FPrizeLimit> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPrizeLimit, ESPMode::ThreadSafe> FPrizeLimitPtr;
}