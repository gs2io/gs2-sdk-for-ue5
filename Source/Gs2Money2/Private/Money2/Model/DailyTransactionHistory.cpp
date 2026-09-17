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

#include "Money2/Model/DailyTransactionHistory.h"

namespace Gs2::Money2::Model
{
    FDailyTransactionHistory::FDailyTransactionHistory():
        DailyTransactionHistoryIdValue(TOptional<FString>()),
        YearValue(TOptional<int32>()),
        MonthValue(TOptional<int32>()),
        DayValue(TOptional<int32>()),
        CurrencyValue(TOptional<FString>()),
        DepositAmountValue(TOptional<double>()),
        WithdrawAmountValue(TOptional<double>()),
        IssueCountValue(TOptional<int64>()),
        ConsumeCountValue(TOptional<int64>()),
        UpdatedAtValue(TOptional<int64>()),
        RevisionValue(TOptional<int64>())
    {
    }

    FDailyTransactionHistory::FDailyTransactionHistory(
        const FDailyTransactionHistory& From
    ):
        DailyTransactionHistoryIdValue(From.DailyTransactionHistoryIdValue),
        YearValue(From.YearValue),
        MonthValue(From.MonthValue),
        DayValue(From.DayValue),
        CurrencyValue(From.CurrencyValue),
        DepositAmountValue(From.DepositAmountValue),
        WithdrawAmountValue(From.WithdrawAmountValue),
        IssueCountValue(From.IssueCountValue),
        ConsumeCountValue(From.ConsumeCountValue),
        UpdatedAtValue(From.UpdatedAtValue),
        RevisionValue(From.RevisionValue)
    {
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithDailyTransactionHistoryId(
        const TOptional<FString> DailyTransactionHistoryId
    )
    {
        this->DailyTransactionHistoryIdValue = DailyTransactionHistoryId;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithYear(
        const TOptional<int32> Year
    )
    {
        this->YearValue = Year;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithMonth(
        const TOptional<int32> Month
    )
    {
        this->MonthValue = Month;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithDay(
        const TOptional<int32> Day
    )
    {
        this->DayValue = Day;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithCurrency(
        const TOptional<FString> Currency
    )
    {
        this->CurrencyValue = Currency;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithDepositAmount(
        const TOptional<double> DepositAmount
    )
    {
        this->DepositAmountValue = DepositAmount;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithWithdrawAmount(
        const TOptional<double> WithdrawAmount
    )
    {
        this->WithdrawAmountValue = WithdrawAmount;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithIssueCount(
        const TOptional<int64> IssueCount
    )
    {
        this->IssueCountValue = IssueCount;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithConsumeCount(
        const TOptional<int64> ConsumeCount
    )
    {
        this->ConsumeCountValue = ConsumeCount;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithUpdatedAt(
        const TOptional<int64> UpdatedAt
    )
    {
        this->UpdatedAtValue = UpdatedAt;
        return SharedThis(this);
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::WithRevision(
        const TOptional<int64> Revision
    )
    {
        this->RevisionValue = Revision;
        return SharedThis(this);
    }
    TOptional<FString> FDailyTransactionHistory::GetDailyTransactionHistoryId() const
    {
        return DailyTransactionHistoryIdValue;
    }
    TOptional<int32> FDailyTransactionHistory::GetYear() const
    {
        return YearValue;
    }

    FString FDailyTransactionHistory::GetYearString() const
    {
        if (!YearValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), YearValue.GetValue());
    }
    TOptional<int32> FDailyTransactionHistory::GetMonth() const
    {
        return MonthValue;
    }

    FString FDailyTransactionHistory::GetMonthString() const
    {
        if (!MonthValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), MonthValue.GetValue());
    }
    TOptional<int32> FDailyTransactionHistory::GetDay() const
    {
        return DayValue;
    }

    FString FDailyTransactionHistory::GetDayString() const
    {
        if (!DayValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%d"), DayValue.GetValue());
    }
    TOptional<FString> FDailyTransactionHistory::GetCurrency() const
    {
        return CurrencyValue;
    }
    TOptional<double> FDailyTransactionHistory::GetDepositAmount() const
    {
        return DepositAmountValue;
    }

    FString FDailyTransactionHistory::GetDepositAmountString() const
    {
        if (!DepositAmountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), DepositAmountValue.GetValue());
    }
    TOptional<double> FDailyTransactionHistory::GetWithdrawAmount() const
    {
        return WithdrawAmountValue;
    }

    FString FDailyTransactionHistory::GetWithdrawAmountString() const
    {
        if (!WithdrawAmountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%f"), WithdrawAmountValue.GetValue());
    }
    TOptional<int64> FDailyTransactionHistory::GetIssueCount() const
    {
        return IssueCountValue;
    }

    FString FDailyTransactionHistory::GetIssueCountString() const
    {
        if (!IssueCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), IssueCountValue.GetValue());
    }
    TOptional<int64> FDailyTransactionHistory::GetConsumeCount() const
    {
        return ConsumeCountValue;
    }

    FString FDailyTransactionHistory::GetConsumeCountString() const
    {
        if (!ConsumeCountValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ConsumeCountValue.GetValue());
    }
    TOptional<int64> FDailyTransactionHistory::GetUpdatedAt() const
    {
        return UpdatedAtValue;
    }

    FString FDailyTransactionHistory::GetUpdatedAtString() const
    {
        if (!UpdatedAtValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue());
    }
    TOptional<int64> FDailyTransactionHistory::GetRevision() const
    {
        return RevisionValue;
    }

    FString FDailyTransactionHistory::GetRevisionString() const
    {
        if (!RevisionValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), RevisionValue.GetValue());
    }

    TOptional<FString> FDailyTransactionHistory::GetRegionFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(1);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDailyTransactionHistory::GetOwnerIdFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(2);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDailyTransactionHistory::GetNamespaceNameFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(3);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDailyTransactionHistory::GetYearFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(4);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDailyTransactionHistory::GetMonthFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(5);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDailyTransactionHistory::GetDayFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(6);
        }
        return TOptional<FString>();
    }

    TOptional<FString> FDailyTransactionHistory::GetCurrencyFromGrn(const FString Grn)
    {
        const auto Pattern = FRegexPattern(TEXT("grn:gs2:(?<region>.+):(?<ownerId>.+):money2:(?<namespaceName>.+):transaction:history:daily:(?<year>.+):(?<month>.+):(?<day>.+):currency:(?<currency>.+)"));
        FRegexMatcher Matcher(Pattern, Grn);
        while (Matcher.FindNext())
        {
            return Matcher.GetCaptureGroup(7);
        }
        return TOptional<FString>();
    }

    TSharedPtr<FDailyTransactionHistory> FDailyTransactionHistory::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FDailyTransactionHistory>()
            ->WithDailyTransactionHistoryId(Data->HasField(ANSI_TO_TCHAR("dailyTransactionHistoryId")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("dailyTransactionHistoryId"), v))
                    {
                        return TOptional(v);
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
            ->WithCurrency(Data->HasField(ANSI_TO_TCHAR("currency")) ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField(ANSI_TO_TCHAR("currency"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithDepositAmount(Data->HasField(ANSI_TO_TCHAR("depositAmount")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("depositAmount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithWithdrawAmount(Data->HasField(ANSI_TO_TCHAR("withdrawAmount")) ? [Data]() -> TOptional<double>
                {
                    double v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("withdrawAmount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<double>();
                }() : TOptional<double>())
            ->WithIssueCount(Data->HasField(ANSI_TO_TCHAR("issueCount")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("issueCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithConsumeCount(Data->HasField(ANSI_TO_TCHAR("consumeCount")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("consumeCount"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithUpdatedAt(Data->HasField(ANSI_TO_TCHAR("updatedAt")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("updatedAt"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>())
            ->WithRevision(Data->HasField(ANSI_TO_TCHAR("revision")) ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField(ANSI_TO_TCHAR("revision"), v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FDailyTransactionHistory::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (DailyTransactionHistoryIdValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("dailyTransactionHistoryId"), DailyTransactionHistoryIdValue.GetValue());
        }
        if (YearValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("year"), YearValue.GetValue());
        }
        if (MonthValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("month"), MonthValue.GetValue());
        }
        if (DayValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("day"), DayValue.GetValue());
        }
        if (CurrencyValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("currency"), CurrencyValue.GetValue());
        }
        if (DepositAmountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("depositAmount"), DepositAmountValue.GetValue());
        }
        if (WithdrawAmountValue.IsSet())
        {
            JsonRootObject->SetNumberField(TEXT("withdrawAmount"), WithdrawAmountValue.GetValue());
        }
        if (IssueCountValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("issueCount"), FString::Printf(TEXT("%lld"), IssueCountValue.GetValue()));
        }
        if (ConsumeCountValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("consumeCount"), FString::Printf(TEXT("%lld"), ConsumeCountValue.GetValue()));
        }
        if (UpdatedAtValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("updatedAt"), FString::Printf(TEXT("%lld"), UpdatedAtValue.GetValue()));
        }
        if (RevisionValue.IsSet())
        {
            JsonRootObject->SetStringField(TEXT("revision"), FString::Printf(TEXT("%lld"), RevisionValue.GetValue()));
        }
        return JsonRootObject;
    }

    FString FDailyTransactionHistory::TypeName = "DailyTransactionHistory";
}
#include "Money2/Model/Cache/DailyTransactionHistory.h"

namespace Gs2::Money2::Model::Cache
{
    FString FDailyTransactionHistoryCache::CreateCacheParentKey(
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        return FString("money2:")
            + CacheOwnerArgumentNamespaceName.Get(FString()) + FString(":")
            + FString::FromInt(CacheOwnerArgumentTimeOffset.Get(0)) + FString(":DailyTransactionHistory");
    }

    FString FDailyTransactionHistoryCache::CreateCacheKey(
        TOptional<int32> CacheOwnerArgumentYear,
        TOptional<int32> CacheOwnerArgumentMonth,
        TOptional<int32> CacheOwnerArgumentDay,
        TOptional<FString> CacheOwnerArgumentCurrency
    )
    {
        return
            FString()
            + (CacheOwnerArgumentYear.IsSet() ? FString::FromInt(CacheOwnerArgumentYear.Get(0)) : FString()) + FString(":")
            + (CacheOwnerArgumentMonth.IsSet() ? FString::FromInt(CacheOwnerArgumentMonth.Get(0)) : FString()) + FString(":")
            + (CacheOwnerArgumentDay.IsSet() ? FString::FromInt(CacheOwnerArgumentDay.Get(0)) : FString()) + FString(":")
            + CacheOwnerArgumentCurrency.Get(FString())
            ;
    }

    bool FDailyTransactionHistoryCache::TryGet(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentYear,
        TOptional<int32> CacheOwnerArgumentMonth,
        TOptional<int32> CacheOwnerArgumentDay,
        TOptional<FString> CacheOwnerArgumentCurrency,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Money2::Model::FDailyTransactionHistoryPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid())
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return false;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        Gs2::Money2::Model::FDailyTransactionHistoryPtr CacheOwnerValue;
        const bool CacheOwnerFound = CacheSnapshot->TryGet<Gs2::Money2::Model::FDailyTransactionHistory>(
            CreateCacheParentKey(
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentTimeOffset
            ),
            CreateCacheKey(
                CacheOwnerArgumentYear,
                CacheOwnerArgumentMonth,
                CacheOwnerArgumentDay,
                CacheOwnerArgumentCurrency
            ),
            &CacheOwnerValue
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFound ? CacheOwnerValue : nullptr;
        return CacheOwnerFound;
    }

    void FDailyTransactionHistoryCache::Put(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentYear,
        TOptional<int32> CacheOwnerArgumentMonth,
        TOptional<int32> CacheOwnerArgumentDay,
        TOptional<FString> CacheOwnerArgumentCurrency,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const Gs2::Money2::Model::FDailyTransactionHistoryPtr& CacheOwnerArgumentItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        const auto CacheOwnerParentKey = CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        );
        const auto CacheOwnerKey = CreateCacheKey(
            CacheOwnerArgumentYear,
            CacheOwnerArgumentMonth,
            CacheOwnerArgumentDay,
            CacheOwnerArgumentCurrency
        );
        auto CacheOwnerValue = CacheOwnerArgumentItem;
        Gs2::Money2::Model::FDailyTransactionHistoryPtr CacheOwnerExisting;
        if (CacheSnapshot->TryGet<Gs2::Money2::Model::FDailyTransactionHistory>(CacheOwnerParentKey, CacheOwnerKey, &CacheOwnerExisting))
        {
            const int64 CacheOwnerOldRevision = CacheOwnerExisting.IsValid() ? CacheOwnerExisting->GetRevision().Get(-1) : -1;
            const int64 CacheOwnerNewRevision = CacheOwnerValue.IsValid() ? CacheOwnerValue->GetRevision().Get(-1) : -1;
            if (CacheOwnerOldRevision > CacheOwnerNewRevision && CacheOwnerNewRevision > 1) return;
            if (CacheOwnerOldRevision == CacheOwnerNewRevision) return;
        }
        CacheSnapshot->Put(Gs2::Money2::Model::FDailyTransactionHistory::TypeName, CacheOwnerParentKey, CacheOwnerKey, CacheOwnerValue,
            FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
        );
    }

    void FDailyTransactionHistoryCache::Delete(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentYear,
        TOptional<int32> CacheOwnerArgumentMonth,
        TOptional<int32> CacheOwnerArgumentDay,
        TOptional<FString> CacheOwnerArgumentCurrency,
        TOptional<int32> CacheOwnerArgumentTimeOffset
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->Delete(Gs2::Money2::Model::FDailyTransactionHistory::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CreateCacheKey(
            CacheOwnerArgumentYear,
            CacheOwnerArgumentMonth,
            CacheOwnerArgumentDay,
            CacheOwnerArgumentCurrency
        ));
    }

    Gs2::Core::Model::FGs2ErrorPtr FDailyTransactionHistoryCache::Fetch(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentYear,
        TOptional<int32> CacheOwnerArgumentMonth,
        TOptional<int32> CacheOwnerArgumentDay,
        TOptional<FString> CacheOwnerArgumentCurrency,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        const TFunction<Gs2::Core::Model::FGs2ErrorPtr(Gs2::Money2::Model::FDailyTransactionHistoryPtr*)>& CacheOwnerArgumentFetchImpl,
        Gs2::Money2::Model::FDailyTransactionHistoryPtr* CacheOwnerArgumentOutItem
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        const auto FetchImplSnapshot = CacheOwnerArgumentFetchImpl;
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        if (!FetchImplSnapshot)
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            const auto Details = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
            Details->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(TEXT("fetchImpl"), TEXT("fetchImpl is required."), TEXT("required")));
            return MakeShared<Gs2::Core::Model::FBadRequestError>(Details);
        }
        Gs2::Money2::Model::FDailyTransactionHistoryPtr CacheOwnerFetchedItem;
        const auto CacheOwnerError = FetchImplSnapshot(&CacheOwnerFetchedItem);
        if (!CacheOwnerError)
        {
            Put(
                CacheSnapshot,
                CacheOwnerArgumentNamespaceName,
                CacheOwnerArgumentYear,
                CacheOwnerArgumentMonth,
                CacheOwnerArgumentDay,
                CacheOwnerArgumentCurrency,
                CacheOwnerArgumentTimeOffset,
                CacheOwnerFetchedItem
            );
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = CacheOwnerFetchedItem;
            return nullptr;
        }
        if (!CacheOwnerError->IsChildOf(Gs2::Core::Model::FNotFoundError::Class))
        {
            if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
            return CacheOwnerError;
        }
        Put(
            CacheSnapshot,
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentYear,
            CacheOwnerArgumentMonth,
            CacheOwnerArgumentDay,
            CacheOwnerArgumentCurrency,
            CacheOwnerArgumentTimeOffset,
            nullptr
        );
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        const auto CacheOwnerDetails = CacheOwnerError->GetErrors();
        if (CacheOwnerDetails.IsValid() && CacheOwnerDetails->Num() > 0 && (*CacheOwnerDetails)[0].IsValid() && (*CacheOwnerDetails)[0]->GetComponent() == TEXT("dailyTransactionHistory"))
        {
            return nullptr;
        }
        if (CacheOwnerArgumentOutItem) *CacheOwnerArgumentOutItem = nullptr;
        return CacheOwnerError;
    }

    Gs2::Core::Domain::CallbackID FDailyTransactionHistoryCache::ListSubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        TFunction<void(TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>)> CacheOwnerArgumentCallback
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return 0;
        return CacheSnapshot->ListSubscribeTyped(Gs2::Money2::Model::FDailyTransactionHistory::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), [CacheOwnerArgumentCallback](const TArray<FGs2ObjectPtr>& CacheOwnerValues)
        {
            TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr> CacheOwnerTypedValues;
            for (const auto& CacheOwnerValue : CacheOwnerValues) if (CacheOwnerValue) CacheOwnerTypedValues.Add(StaticCastSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>(CacheOwnerValue));
            if (CacheOwnerArgumentCallback) CacheOwnerArgumentCallback(CacheOwnerTypedValues);
        });
    }

    void FDailyTransactionHistoryCache::ListUnsubscribe(
        const Gs2::Core::Domain::FCacheDatabasePtr& CacheOwnerArgumentCache,
        TOptional<FString> CacheOwnerArgumentNamespaceName,
        TOptional<int32> CacheOwnerArgumentTimeOffset,
        Gs2::Core::Domain::CallbackID CacheOwnerArgumentCallbackID
    )
    {
        const auto CacheSnapshot = CacheOwnerArgumentCache;
        if (!CacheSnapshot.IsValid()) return;
        CacheSnapshot->ListUnsubscribe(Gs2::Money2::Model::FDailyTransactionHistory::TypeName, CreateCacheParentKey(
            CacheOwnerArgumentNamespaceName,
            CacheOwnerArgumentTimeOffset
        ), CacheOwnerArgumentCallbackID);
    }
}