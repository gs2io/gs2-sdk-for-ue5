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
    class GS2LOTTERY_API FLotteryModelMaster final : public TSharedFromThis<FLotteryModelMaster>
    {
        TOptional<FString> LotteryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> DescriptionValue;
        TOptional<FString> ModeValue;
        TOptional<FString> MethodValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> ChoicePrizeTableScriptIdValue;
        TOptional<int64> CreatedAtValue;
        TOptional<int64> UpdatedAtValue;

    public:
        FLotteryModelMaster();
        FLotteryModelMaster(
            const FLotteryModelMaster& From
        );
        ~FLotteryModelMaster() = default;

        TSharedPtr<FLotteryModelMaster> WithLotteryModelId(const TOptional<FString> LotteryModelId);
        TSharedPtr<FLotteryModelMaster> WithName(const TOptional<FString> Name);
        TSharedPtr<FLotteryModelMaster> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FLotteryModelMaster> WithDescription(const TOptional<FString> Description);
        TSharedPtr<FLotteryModelMaster> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FLotteryModelMaster> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FLotteryModelMaster> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FLotteryModelMaster> WithChoicePrizeTableScriptId(const TOptional<FString> ChoicePrizeTableScriptId);
        TSharedPtr<FLotteryModelMaster> WithCreatedAt(const TOptional<int64> CreatedAt);
        TSharedPtr<FLotteryModelMaster> WithUpdatedAt(const TOptional<int64> UpdatedAt);

        TOptional<FString> GetLotteryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetDescription() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetChoicePrizeTableScriptId() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetLotteryNameFromGrn(const FString Grn);

        static TSharedPtr<FLotteryModelMaster> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLotteryModelMaster, ESPMode::ThreadSafe> FLotteryModelMasterPtr;
}