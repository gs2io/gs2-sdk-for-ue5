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
#include "Prize.h"

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FPrizeTableMaster final : public Gs2Object, public TSharedFromThis<FPrizeTableMaster>
    {
        TOptional<FString> PrizeTableIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TSharedPtr<TArray<TSharedPtr<FPrize>>> PrizesValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FPrizeTableMaster();
        FPrizeTableMaster(
            const FPrizeTableMaster& From
        );
        virtual ~FPrizeTableMaster() override = default;

        TSharedPtr<FPrizeTableMaster> WithPrizeTableId(const TOptional<FString> PrizeTableId);
        TSharedPtr<FPrizeTableMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FPrizeTableMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FPrizeTableMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FPrizeTableMaster> WithPrizes(const TSharedPtr<TArray<TSharedPtr<FPrize>>> Prizes);
        TSharedPtr<FPrizeTableMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FPrizeTableMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FPrizeTableMaster> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetPrizeTableId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TSharedPtr<TArray<TSharedPtr<FPrize>>> GetPrizes() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetPrizeTableNameFromGrn(const FString Grn);

        static TSharedPtr<FPrizeTableMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPrizeTableMaster, ESPMode::ThreadSafe> FPrizeTableMasterPtr;
}