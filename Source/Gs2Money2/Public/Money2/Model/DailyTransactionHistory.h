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

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FDailyTransactionHistory final : public FGs2Object, public TSharedFromThis<FDailyTransactionHistory>
    {
        TOptional<FString> DailyTransactionHistoryIdValue;
        TOptional<int32> YearValue;
        TOptional<int32> MonthValue;
        TOptional<int32> DayValue;
        TOptional<FString> CurrencyValue;
        TOptional<double> DepositAmountValue;
        TOptional<double> WithdrawAmountValue;
        TOptional<int64> UpdatedAtValue;
        TOptional<int64> RevisionValue;

    public:
        FDailyTransactionHistory();
        FDailyTransactionHistory(
            const FDailyTransactionHistory& From
        );
        virtual ~FDailyTransactionHistory() override = default;

        TSharedPtr<FDailyTransactionHistory> WithDailyTransactionHistoryId(const TOptional<FString> DailyTransactionHistoryId);
        TSharedPtr<FDailyTransactionHistory> WithYear(const TOptional<int32> Year);
        TSharedPtr<FDailyTransactionHistory> WithMonth(const TOptional<int32> Month);
        TSharedPtr<FDailyTransactionHistory> WithDay(const TOptional<int32> Day);
        TSharedPtr<FDailyTransactionHistory> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FDailyTransactionHistory> WithDepositAmount(const TOptional<double> DepositAmount);
        TSharedPtr<FDailyTransactionHistory> WithWithdrawAmount(const TOptional<double> WithdrawAmount);
        TSharedPtr<FDailyTransactionHistory> WithUpdatedAt(const TOptional<int64> UpdatedAt);
        TSharedPtr<FDailyTransactionHistory> WithRevision(const TOptional<int64> Revision);

        TOptional<FString> GetDailyTransactionHistoryId() const;
        TOptional<int32> GetYear() const;
        FString GetYearString() const;
        TOptional<int32> GetMonth() const;
        FString GetMonthString() const;
        TOptional<int32> GetDay() const;
        FString GetDayString() const;
        TOptional<FString> GetCurrency() const;
        TOptional<double> GetDepositAmount() const;
        FString GetDepositAmountString() const;
        TOptional<double> GetWithdrawAmount() const;
        FString GetWithdrawAmountString() const;
        TOptional<int64> GetUpdatedAt() const;
        FString GetUpdatedAtString() const;
        TOptional<int64> GetRevision() const;
        FString GetRevisionString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetYearFromGrn(const FString Grn);
        static TOptional<FString> GetMonthFromGrn(const FString Grn);
        static TOptional<FString> GetDayFromGrn(const FString Grn);
        static TOptional<FString> GetCurrencyFromGrn(const FString Grn);

        static TSharedPtr<FDailyTransactionHistory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FDailyTransactionHistory, ESPMode::ThreadSafe> FDailyTransactionHistoryPtr;
}