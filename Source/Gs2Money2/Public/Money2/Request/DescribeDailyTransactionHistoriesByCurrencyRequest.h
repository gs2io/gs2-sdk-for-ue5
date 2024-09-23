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

namespace Gs2::Money2::Request
{
    class FDescribeDailyTransactionHistoriesByCurrencyRequest;

    class GS2MONEY2_API FDescribeDailyTransactionHistoriesByCurrencyRequest final : public TSharedFromThis<FDescribeDailyTransactionHistoriesByCurrencyRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<FString> CurrencyValue;
        TOptional<int32> YearValue;
        TOptional<int32> MonthValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeDailyTransactionHistoriesByCurrencyRequest();
        FDescribeDailyTransactionHistoriesByCurrencyRequest(
            const FDescribeDailyTransactionHistoriesByCurrencyRequest& From
        );
        ~FDescribeDailyTransactionHistoriesByCurrencyRequest() = default;

        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithCurrency(const TOptional<FString> Currency);
        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithYear(const TOptional<int32> Year);
        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithMonth(const TOptional<int32> Month);
        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<FString> GetCurrency() const;
        TOptional<int32> GetYear() const;
        FString GetYearString() const;
        TOptional<int32> GetMonth() const;
        FString GetMonthString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest, ESPMode::ThreadSafe> FDescribeDailyTransactionHistoriesByCurrencyRequestPtr;
}