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
#include "Lottery/Model/LotteryModel.h"

namespace Gs2::UE5::Lottery::Model
{
	class EZGS2_API FEzLotteryModel final : public TSharedFromThis<FEzLotteryModel>
	{
        TOptional<FString> NameValue;
        TOptional<FString> MetadataValue;
        TOptional<FString> ModeValue;
        TOptional<FString> PrizeTableNameValue;

	public:
        TSharedPtr<FEzLotteryModel> WithName(const TOptional<FString> Name);
        TSharedPtr<FEzLotteryModel> WithMetadata(const TOptional<FString> Metadata);
        TSharedPtr<FEzLotteryModel> WithMode(const TOptional<FString> Mode);
        TSharedPtr<FEzLotteryModel> WithPrizeTableName(const TOptional<FString> PrizeTableName);

        TOptional<FString> GetName() const;

        TOptional<FString> GetMetadata() const;

        TOptional<FString> GetMode() const;

        TOptional<FString> GetPrizeTableName() const;

        Gs2::Lottery::Model::FLotteryModelPtr ToModel() const;
        static TSharedPtr<FEzLotteryModel> FromModel(Gs2::Lottery::Model::FLotteryModelPtr Model);
    };
    typedef TSharedPtr<FEzLotteryModel> FEzLotteryModelPtr;
}