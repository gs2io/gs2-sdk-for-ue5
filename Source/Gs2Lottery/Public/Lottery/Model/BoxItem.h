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
    class GS2LOTTERY_API FBoxItem final : public Gs2Object, public TSharedFromThis<FBoxItem>
    {
        TOptional<FString> PrizeIdValue;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActionsValue;
        TOptional<int32> RemainingValue;
        TOptional<int32> InitialValue;

    public:
        FBoxItem();
        FBoxItem(
            const FBoxItem& From
        );
        virtual ~FBoxItem() override = default;

        TSharedPtr<FBoxItem> WithPrizeId(const TOptional<FString> PrizeId);
        TSharedPtr<FBoxItem> WithAcquireActions(const TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> AcquireActions);
        TSharedPtr<FBoxItem> WithRemaining(const TOptional<int32> Remaining);
        TSharedPtr<FBoxItem> WithInitial(const TOptional<int32> Initial);

        TOptional<FString> GetPrizeId() const;
        TSharedPtr<TArray<TSharedPtr<FAcquireAction>>> GetAcquireActions() const;
        TOptional<int32> GetRemaining() const;
        FString GetRemainingString() const;
        TOptional<int32> GetInitial() const;
        FString GetInitialString() const;


        static TSharedPtr<FBoxItem> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FBoxItem, ESPMode::ThreadSafe> FBoxItemPtr;
}