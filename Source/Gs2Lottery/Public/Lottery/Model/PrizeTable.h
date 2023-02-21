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
#include "Prize.h"

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FPrizeTable final : public TSharedFromThis<FPrizeTable>
    {
        TOptional<FString> PrizeTableIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TSharedPtr<TArray<TSharedPtr<FPrize>>> PrizesValue;

    public:
        FPrizeTable();
        FPrizeTable(
            const FPrizeTable& From
        );
        ~FPrizeTable() = default;

        TSharedPtr<FPrizeTable> WithPrizeTableId(const TOptional<FString> PrizeTableId);
        TSharedPtr<FPrizeTable> WithName(const TOptional<FString> Name);
        TSharedPtr<FPrizeTable> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPrizeTable> WithPrizes(const TSharedPtr<TArray<TSharedPtr<FPrize>>> Prizes);

        TOptional<FString> GetPrizeTableId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TSharedPtr<TArray<TSharedPtr<FPrize>>> GetPrizes() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetPrizeTableNameFromGrn(const FString Grn);

        static TSharedPtr<FPrizeTable> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPrizeTable, ESPMode::ThreadSafe> FPrizeTablePtr;
}