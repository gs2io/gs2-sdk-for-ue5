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
#include "Lottery/Model/BoxItem.h"
#include "Gs2LotteryEzAcquireAction.h"

namespace Gs2::UE5::Lottery::Model
{
	class EZGS2_API FEzBoxItem final : public TSharedFromThis<FEzBoxItem>
	{
        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> AcquireActionsValue;
        TOptional<int32> RemainingValue;
        TOptional<int32> InitialValue;

	public:
        TSharedPtr<FEzBoxItem> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> AcquireActions);
        TSharedPtr<FEzBoxItem> WithRemaining(const TOptional<int32> Remaining);
        TSharedPtr<FEzBoxItem> WithInitial(const TOptional<int32> Initial);

        TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Lottery::Model::FEzAcquireAction>>> GetAcquireActions() const;

        TOptional<int32> GetRemaining() const;
        FString GetRemainingString() const;

        TOptional<int32> GetInitial() const;
        FString GetInitialString() const;

        Gs2::Lottery::Model::FBoxItemPtr ToModel() const;
        static TSharedPtr<FEzBoxItem> FromModel(Gs2::Lottery::Model::FBoxItemPtr Model);
    };
    typedef TSharedPtr<FEzBoxItem> FEzBoxItemPtr;
}