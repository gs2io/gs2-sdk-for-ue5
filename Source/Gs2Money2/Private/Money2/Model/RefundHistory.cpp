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

#include "Money2/Model/RefundHistory.h"

namespace Gs2::Money2::Model
{
    FRefundHistory::FRefundHistory():
        RefundHistoryIdValue(TOptional<FString>()),
        TransactionIdValue(TOptional<FString>()),
        YearValue(TOptional<int32>()),
        MonthValue(TOptional<int32>()),
        DayValue(TOptional<int32>()),
        UserIdValue(TOptional<FString>()),
        DetailValue(nullptr),
        CreatedAtValue(TOptional<int64>())
    {
    }

    FRefundHistory::FRefundHistory(
        const FRefundHistory& From
    ):
        RefundHistoryIdValue(From.RefundHistoryIdValue),
        TransactionIdValue(From.TransactionIdValue),
        YearValue(From.YearValue),
        MonthValue(From.MonthValue),
        DayValue(From.DayValue),
        UserIdValue(From.UserIdValue),
        DetailValue(From.DetailValue),
        CreatedAtValue(From.CreatedAtValue)
    {
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithRefundHistoryId(
        const TOptional<FString> RefundHistoryId
    )
    {
        this->RefundHistoryIdValue = RefundHistoryId;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithTransactionId(
        const TOptional<FString> TransactionId
    )
    {
        this->TransactionIdValue = TransactionId;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithYear(
        const TOptional<int32> Year
    )
    {
        this->YearValue = Year;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithMonth(
        const TOptional<int32> Month
    )
    {
        this->MonthValue = Month;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithDay(
        const TOptional<int32> Day
    )
    {
        this->DayValue = Day;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithDetail(
        const TSharedPtr<FRefundEvent> Detail
    )
    {
        this->DetailValue = Detail;
        return SharedThis(this);
    }

    TSharedPtr<FRefundHistory> FRefundHistory::WithCreatedAt(
        const TOptional<int64> CreatedAt
    )
    {
        this->CreatedAtValue = CreatedAt;
        return SharedThis(this);
    }
    TOptional<FString> FRefundHistory::GetRefundHistoryId() const
    {
        return RefundHistoryIdValue;
    }
    TOptional<FString> FRefundHistory::GetTransactionId() const
    {
        return TransactionIdValue;
    }
    TOptional<int32> FRefundHistory::GetYear() const
    {
        return YearValue;
    }

    FString FRefundHistory::GetYearString() const
    {
        if (!YearValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), YearValue.GetValue());
    }
    TOptional<int32> FRefundHistory::GetMonth() const
    {
        return MonthValue;
    }

    FString FRefundHistory::GetMonthString() const
    {
        if (!MonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MonthValue.GetValue());
    }
    TOptional<int32> FRefundHistory::GetDay() const
    {
        return DayValue;
    }

    FString FRefundHistory::GetDayString() const
    {
        if (!DayValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DayValue.GetValue());
    }
    TOptional<FString> FRefundHistory::GetUserId() const
    {
        return UserIdValue;
    }
    TSharedPtr<FRefundEvent> FRefundHistory::GetDetail() const
    {
        return DetailValue;
    }
    TOptional<int64> FRefundHistory::GetCreatedAt() const
    {
        return CreatedAtValue;
    }

    FString FRefundHistory::GetCreatedAtString() const
    {
        if (!CreatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue());
    }

    TOptional<FString> FRefundHistory::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):refundHistory:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRefundHistory::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):refundHistory:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRefundHistory::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):refundHistory:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FRefundHistory::GetTransactionIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):refundHistory:(?<transactionId>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FRefundHistory> FRefundHistory::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FRefundHistory>()
            ->WithRefundHistoryId(Data->HasField(ANSI_TO_TCHAR("refundHistoryId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("refundHistoryId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithTransactionId(Data->HasField(ANSI_TO_TCHAR("transactionId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("transactionId"), v))
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
            ->WithDay(Data->HasField(ANSI_TO_TCHAR("day")) ? [Data]() -> TOptional<int32>
                {
                    int32 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("day"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int32>();
                }() : TOptional<int32>())
            ->WithUserId(Data->HasField(ANSI_TO_TCHAR("userId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("userId"), v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDetail(Data->HasField(ANSI_TO_TCHAR("detail")) ? [Data]() -> Model::FRefundEventPtr
                {
                    if (Data->HasTypedField<EJson::Null>(ANSI_TO_TCHAR("detail")))
                    {
                        return nullptr;
                    }
                    return Model::FRefundEvent::FromJson(Data->GetObjectField(ANSI_TO_TCHAR("detail")));
                 }() : nullptr)
            ->WithCreatedAt(Data->HasField(ANSI_TO_TCHAR("createdAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("createdAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FRefundHistory::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (RefundHistoryIdValue.IsSet())
        {
            JsonRootObject->SetStringField("refundHistoryId", RefundHistoryIdValue.GetValue());
        }
        if (TransactionIdValue.IsSet())
        {
            JsonRootObject->SetStringField("transactionId", TransactionIdValue.GetValue());
        }
        if (YearValue.IsSet())
        {
            JsonRootObject->SetNumberField("year", YearValue.GetValue());
        }
        if (MonthValue.IsSet())
        {
            JsonRootObject->SetNumberField("month", MonthValue.GetValue());
        }
        if (DayValue.IsSet())
        {
            JsonRootObject->SetNumberField("day", DayValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (DetailValue != nullptr && DetailValue.IsValid())
        {
            JsonRootObject->SetObjectField("detail", DetailValue->ToJson());
        }
        if (CreatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField("createdAt", FString::Printf(TEXT("%lld"), CreatedAtValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FRefundHistory::TypeName = "RefundHistory";
}