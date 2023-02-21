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
    class GS2LOTTERY_API FLotteryModel final : public TSharedFromThis<FLotteryModel>
    {
        TOptional<FString> LotteryModelIdValue;
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> MethodValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<FString> ChoicePrizeTableScriptIdValue;

    public:
        FLotteryModel();
        FLotteryModel(
            const FLotteryModel& From
        );
        ~FLotteryModel() = default;

        TSharedPtr<FLotteryModel> WithLotteryModelId(const TOptional<FString> LotteryModelId);
        TSharedPtr<FLotteryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FLotteryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FLotteryModel> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FLotteryModel> WithMethod(const TOptional<FString> Method);
        TSharedPtr<FLotteryModel> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FLotteryModel> WithChoicePrizeTableScriptId(const TOptional<FString> ChoicePrizeTableScriptId);

        TOptional<FString> GetLotteryModelId() const;
        TOptional<FString> GetName() const;
        TOptional<FString> GetMetadata() const;
        TOptional<FString> GetMode() const;
        TOptional<FString> GetMethod() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<FString> GetChoicePrizeTableScriptId() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetLotteryNameFromGrn(const FString Grn);

        static TSharedPtr<FLotteryModel> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FLotteryModel, ESPMode::ThreadSafe> FLotteryModelPtr;
}