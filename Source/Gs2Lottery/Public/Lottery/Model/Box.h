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
    class GS2LOTTERY_API FBox final : public TSharedFromThis<FBox>
    {
        TOptional<FString> BoxIdValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<int32> IndexValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<TArray<int32>> DrawnIndexesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FBox();
        FBox(
            const FBox& From
        );
        ~FBox() = default;

        TSharedPtr<FBox> WithBoxId(const TOptional<FString> BoxId);
        TSharedPtr<FBox> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FBox> WithIndex(const TOptional<int32> Index);
        TSharedPtr<FBox> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FBox> WithDrawnIndexes(const TSharedPtr<TArray<int32>> DrawnIndexes);
        TSharedPtr<FBox> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FBox> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FBox> ToPtr();

        TOptional<FString> GetBoxId() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<int32> GetIndex() const;
        FString GetIndexString() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<TArray<int32>> GetDrawnIndexes() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TSharedPtr<FBox> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBox, ESPMode::ThreadSafe> FBoxPtr;
}