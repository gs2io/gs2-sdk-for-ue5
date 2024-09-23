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
    class FDescribeDailyTransactionHistoriesRequest;

    class GS2MONEY2_API FDescribeDailyTransactionHistoriesRequest final : public TSharedFromThis<FDescribeDailyTransactionHistoriesRequest>
    {
        TOptional<FString> ContextStackValue;
        TOptional<FString> NamespaceNameValue;
        TOptional<int32> YearValue;
        TOptional<int32> MonthValue;
        TOptional<int32> DayValue;
        TOptional<FString> PageTokenValue;
        TOptional<int32> LimitValue;
        
    public:
        
        FDescribeDailyTransactionHistoriesRequest();
        FDescribeDailyTransactionHistoriesRequest(
            const FDescribeDailyTransactionHistoriesRequest& From
        );
        ~FDescribeDailyTransactionHistoriesRequest() = default;

        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithContextStack(const TOptional<FString> ContextStack);
        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithNamespaceName(const TOptional<FString> NamespaceName);
        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithYear(const TOptional<int32> Year);
        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithMonth(const TOptional<int32> Month);
        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithDay(const TOptional<int32> Day);
        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithPageToken(const TOptional<FString> PageToken);
        TSharedPtr<FDescribeDailyTransactionHistoriesRequest> WithLimit(const TOptional<int32> Limit);

        TOptional<FString> GetContextStack() const;
        TOptional<FString> GetNamespaceName() const;
        TOptional<int32> GetYear() const;
        FString GetYearString() const;
        TOptional<int32> GetMonth() const;
        FString GetMonthString() const;
        TOptional<int32> GetDay() const;
        FString GetDayString() const;
        TOptional<FString> GetPageToken() const;
        TOptional<int32> GetLimit() const;
        FString GetLimitString() const;

        static TSharedPtr<FDescribeDailyTransactionHistoriesRequest> FromJson(const TSharedPtr<FJsonObject> Data);
        TSharedPtr<FJsonObject> ToJson() const;
    };
    typedef TSharedPtr<FDescribeDailyTransactionHistoriesRequest, ESPMode::ThreadSafe> FDescribeDailyTransactionHistoriesRequestPtr;
}