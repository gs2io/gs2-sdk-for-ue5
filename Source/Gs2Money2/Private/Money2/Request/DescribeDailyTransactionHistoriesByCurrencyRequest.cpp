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

#include "Money2/Request/DescribeDailyTransactionHistoriesByCurrencyRequest.h"

namespace Gs2::Money2::Request
{
    FDescribeDailyTransactionHistoriesByCurrencyRequest::FDescribeDailyTransactionHistoriesByCurrencyRequest():
        NamespaceNameValue(TOptional<FString>()),
        CurrencyValue(TOptional<FString>()),
        YearValue(TOptional<int32>()),
        MonthValue(TOptional<int32>()),
        PageTokenValue(TOptional<FString>()),
        LimitValue(TOptional<int32>())
    {
    }

    FDescribeDailyTransactionHistoriesByCurrencyRequest::FDescribeDailyTransactionHistoriesByCurrencyRequest(
        const FDescribeDailyTransactionHistoriesByCurrencyRequest& From
    ):
        NamespaceNameValue(From.NamespaceNameValue),
        CurrencyValue(From.CurrencyValue),
        YearValue(From.YearValue),
        MonthValue(From.MonthValue),
        PageTokenValue(From.PageTokenValue),
        LimitValue(From.LimitValue)
    {
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithContextStack(
        const TOptional<FString> ContextStack
    )
    {
        this->ContextStackValue = ContextStack;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithNamespaceName(
        const TOptional<FString> NamespaceName
    )
    {
        this->NamespaceNameValue = NamespaceName;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithYear(
        const TOptional<int32> Year
    )
    {
        this->YearValue = Year;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithMonth(
        const TOptional<int32> Month
    )
    {
        this->MonthValue = Month;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithPageToken(
        const TOptional<FString> PageToken
    )
    {
        this->PageTokenValue = PageToken;
        return SharedThis(this);
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::WithLimit(
        const TOptional<int32> Limit
    )
    {
        this->LimitValue = Limit;
        return SharedThis(this);
    }

    TOptional<FString> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetContextStack() const
    {
        return ContextStackValue;
    }

    TOptional<FString> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetNamespaceName() const
    {
        return NamespaceNameValue;
    }

    TOptional<FString> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetCurrency() const
    {
        return CurrencyValue;
    }

    TOptional<int32> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetYear() const
    {
        return YearValue;
    }

    FString FDescribeDailyTransactionHistoriesByCurrencyRequest::GetYearString() const
    {
        if (!YearValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), YearValue.GetValue());
    }

    TOptional<int32> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetMonth() const
    {
        return MonthValue;
    }

    FString FDescribeDailyTransactionHistoriesByCurrencyRequest::GetMonthString() const
    {
        if (!MonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MonthValue.GetValue());
    }

    TOptional<FString> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetPageToken() const
    {
        return PageTokenValue;
    }

    TOptional<int32> FDescribeDailyTransactionHistoriesByCurrencyRequest::GetLimit() const
    {
        return LimitValue;
    }

    FString FDescribeDailyTransactionHistoriesByCurrencyRequest::GetLimitString() const
    {
        if (!LimitValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), LimitValue.GetValue());
    }

    TSharedPtr<FDescribeDailyTransactionHistoriesByCurrencyRequest> FDescribeDailyTransactionHistoriesByCurrencyRequest::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDescribeDailyTransactionHistoriesByCurrencyRequest>()
            ->WithContextStack(Data->HasField(ANSI_TO_TCHAR("contextStack")) ? TOptional<FString>(Data->GetStringField(ANSI_TO_TCHAR("contextStack"))) : TOptional<FString>())
            ->WithNamespaceName(Data->HasField(ANSI_TO_TCHAR("namespaceName")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("namespaceName"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithCurrency(Data->HasField(ANSI_TO_TCHAR("currency")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currency"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithYear(Data->HasField(ANSI_TO_TCHAR("year")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("year"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithMonth(Data->HasField(ANSI_TO_TCHAR("month")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("month"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>())
            ->WithPageToken(Data->HasField(ANSI_TO_TCHAR("pageToken")) ? [Data]() -> TOptional<FString>
              {
                  FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("pageToken"), v))
                  {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                  }
                  return TOptional<FString>();
              }() : TOptional<FString>())
            ->WithLimit(Data->HasField(ANSI_TO_TCHAR("limit")) ? [Data]() -> TOptional<int32>
              {
                  int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("limit"), v))
                  {
                        return TOptional(v);
                  }
                  return TOptional<int32>();
              }() : TOptional<int32>());
    }

    TSharedPtr<FJsonObject> FDescribeDailyTransactionHistoriesByCurrencyRequest::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (ContextStackValue.IsSet())
        {
            JsonRootObject->SetStringField("contextStack", ContextStackValue.GetValue());
        }
        if (NamespaceNameValue.IsSet())
        {
            JsonRootObject->SetStringField("namespaceName", NamespaceNameValue.GetValue());
        }
        if (CurrencyValue.IsSet())
        {
            JsonRootObject->SetStringField("currency", CurrencyValue.GetValue());
        }
        if (YearValue.IsSet())
        {
            JsonRootObject->SetNumberField("year", YearValue.GetValue());
        }
        if (MonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("month", MonthValue.GetValue());
        }
        if (PageTokenValue.IsSet())
        {
            JsonRootObject->SetStringField("pageToken", PageTokenValue.GetValue());
        }
        if (LimitValue.IsSet())
        {
            JsonRootObject->SetNumberField("limit", LimitValue.GetValue());
        }
        return JsonRootObject;
    }
}