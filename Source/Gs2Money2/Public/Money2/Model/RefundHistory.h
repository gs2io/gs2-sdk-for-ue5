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
#include "RefundEvent.h"

namespace Gs2::Money2::Model
{
    class GS2MONEY2_API FRefundHistory final : public Gs2Object, public TSharedFromThis<FRefundHistory>
    {
        TOptional<FString> RefundHistoryIdValue;
        TOptional<FString> TransactionIdValue;
        TOptional<int32> YearValue;
        TOptional<int32> MonthValue;
        TOptional<int32> DayValue;
        TOptional<FString> UserIdValue;
        TSharedPtr<FRefundEvent> DetailValue;
        TOptional<int64> CreatedAtValue;

    public:
        FRefundHistory();
        FRefundHistory(
            const FRefundHistory& From
        );
        virtual ~FRefundHistory() override = default;

        TSharedPtr<FRefundHistory> WithRefundHistoryId(const TOptional<FString> RefundHistoryId);
        TSharedPtr<FRefundHistory> WithTransactionId(const TOptional<FString> TransactionId);
        TSharedPtr<FRefundHistory> WithYear(const TOptional<int32> Year);
        TSharedPtr<FRefundHistory> WithMonth(const TOptional<int32> Month);
        TSharedPtr<FRefundHistory> WithDay(const TOptional<int32> Day);
        TSharedPtr<FRefundHistory> WithUserId(const TOptional<FString> UserId);
        TSharedPtr<FRefundHistory> WithDetail(const TSharedPtr<FRefundEvent> Detail);
        TSharedPtr<FRefundHistory> WithCreatedAt(const TOptional<int64> CreatedAt);

        TOptional<FString> GetRefundHistoryId() const;
        TOptional<FString> GetTransactionId() const;
        TOptional<int32> GetYear() const;
        FString GetYearString() const;
        TOptional<int32> GetMonth() const;
        FString GetMonthString() const;
        TOptional<int32> GetDay() const;
        FString GetDayString() const;
        TOptional<FString> GetUserId() const;
        TSharedPtr<FRefundEvent> GetDetail() const;
        TOptional<int64> GetCreatedAt() const;
        FString GetCreatedAtString() const;

        static TOptional<FString> GetRegionFromGrn(const FString Grn);
        static TOptional<FString> GetOwnerIdFromGrn(const FString Grn);
        static TOptional<FString> GetNamespaceNameFromGrn(const FString Grn);
        static TOptional<FString> GetTransactionIdFromGrn(const FString Grn);

        static TSharedPtr<FRefundHistory> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;

        static FString TypeName;
    };
    typedef TSharedPtr<FRefundHistory, ESPMode::ThreadSafe> FRefundHistoryPtr;
}