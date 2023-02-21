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
#include "Lottery/Model/DrawnPrize.h"
#include "Gs2LotteryEzAcquireAction.h"

namespace Gs2::UE5::Lottery::Model
{
	class EZGS2_API FEzDrawnPrize final : public TSharedFromThis<FEzDrawnPrize>
	{
        TOptional<FString> PrizeIdValue;
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> AcquireActionsValue;

	public:
        TSharedPtr<FEzDrawnPrize> WithPrizeId(const TOptional<FString> PrizeId);
        TSharedPtr<FEzDrawnPrize> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> AcquireActions);

        TOptional<FString> GetPrizeId() const;

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> GetAcquireActions() const;

        Gs2::Lottery::Model::FDrawnPrizePtr ToModel() const;
        static TSharedPtr<FEzDrawnPrize> FromModel(Gs2::Lottery::Model::FDrawnPrizePtr Model);
    };
    typedef TSharedPtr<FEzDrawnPrize> FEzDrawnPrizePtr;
}