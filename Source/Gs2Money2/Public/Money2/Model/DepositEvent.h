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
#include "DepositTransaction.h"
#include "WalletSummary.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FDepositEvent final : public Gs2Object, public TSharedFromThis<FDepositEvent>
    {
        TOptional<int32> SlotValue;
        TSharedPtr<TArray<TSharedPtr<FDepositTransaction>>> DepositTransactionsValue;
        TSharedPtr<FWalletSummary> StatusValue;

    public:
        FDepositEvent();
        FDepositEvent(
            const FDepositEvent& From
        );
        virtual ~FDepositEvent() override = default;

        TSharedPtr<FDepositEvent> WithSlot(const TOptional<int32> Slot);
        TSharedPtr<FDepositEvent> WithDepositTransactions(const TSharedPtr<TArray<TSharedPtr<FDepositTransaction>>> DepositTransactions);
        TSharedPtr<FDepositEvent> WithStatus(const TSharedPtr<FWalletSummary> Status);

        TOptional<int32> GetSlot() const;
        FString GetSlotString() const;
        TSharedPtr<TArray<TSharedPtr<FDepositTransaction>>> GetDepositTransactions() const;
        TSharedPtr<FWalletSummary> GetStatus() const;


        static TSharedPtr<FDepositEvent> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDepositEvent, ESPMode::ThreadSafe> FDepositEventPtr;
}