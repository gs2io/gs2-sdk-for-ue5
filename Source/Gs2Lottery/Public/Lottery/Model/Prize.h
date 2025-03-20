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
#include "AcquireAction.h"

namespace Gs2::Lottery::Model
{
    class GS2LOTTERY_API FPrize final : public FGs2Object, public TSharedFromThis<FPrize>
    {
        TOptional<FString> PrizeIdValue;
        TOptional<FString> TypeValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int32> DrawnLimitValue;
        TOptional<FString> LimitFailOverPrizeIdValue;
        TOptional<FString> PrizeTableNameValue;
        TOptional<int32> WeightValue;

    public:
        FPrize();
        FPrize(
            const FPrize& From
        );
        virtual ~FPrize() override = default;

        TSharedPtr<FPrize> WithPrizeId(const TOptional<FString> PrizeId);
        TSharedPtr<FPrize> WithType(const TOptional<FString> Type);
        TSharedPtr<FPrize> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FPrize> WithDrawnLimit(const TOptional<int32> DrawnLimit);
        TSharedPtr<FPrize> WithLimitFailOverPrizeId(const TOptional<FString> LimitFailOverPrizeId);
        TSharedPtr<FPrize> WithPrizeTableName(const TOptional<FString> PrizeTableName);
        TSharedPtr<FPrize> WithWeight(const TOptional<int32> Weight);

        TOptional<FString> GetPrizeId() const;
        TOptional<FString> GetType() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;
        TOptional<int32> GetDrawnLimit() const;
        FString GetDrawnLimitString() const;
        TOptional<FString> GetLimitFailOverPrizeId() const;
        TOptional<FString> GetPrizeTableName() const;
        TOptional<int32> GetWeight() const;
        FString GetWeightString() const;


        static TSharedPtr<FPrize> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FPrize, ESPMode::ThreadSafe> FPrizePtr;
}