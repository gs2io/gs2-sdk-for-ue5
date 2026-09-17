
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

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Money2/Domain/Iterator/DescribeDailyTransactionHistoriesIterator.h"
#include "Money2/Domain/Model/DailyTransactionHistory.h"
#include "Money2/Domain/Model/Namespace.h"

#include "Core/Domain/Gs2.h"

#include "Money2/Model/Cache/DailyTransactionHistory.h"
#include "Money2/Model/Cache/Namespace.h"

namespace Gs2::Money2::Domain::Iterator
{

    FDescribeDailyTransactionHistoriesIterator::FDescribeDailyTransactionHistoriesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Money2::FGs2Money2RestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const TOptional<int32> Year,
        const TOptional<int32> Month,
        const TOptional<int32> Day
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        Year(Year),
        Month(Month),
        Day(Day)
    {
    }

    FDescribeDailyTransactionHistoriesIterator::FDescribeDailyTransactionHistoriesIterator(
        const FDescribeDailyTransactionHistoriesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Year(From.Year),
        Month(From.Month),
        Day(From.Day)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FDescribeDailyTransactionHistoriesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FDescribeDailyTransactionHistoriesIterator::FIterator::FIterator(
        const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FDescribeDailyTransactionHistoriesIterator::FIterator& FDescribeDailyTransactionHistoriesIterator::FIterator::operator++()
    {


        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt && *RangeIteratorOpt) ++*RangeIteratorOpt;

        // Keep the previous page alive until its iterator has been replaced.
        const auto PreviousRange = Range;
        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::CreateCacheParentKey(
                Self->NamespaceName,
                TOptional<int32>()
            );
            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Money2::Model::FDailyTransactionHistory>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item) { return Self->Year && Item->GetYear() != Self->Year; });
                    Range->RemoveAll([this](const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item) { return Self->Month && Item->GetMonth() != Self->Month; });
                    Range->RemoveAll([this](const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item) { return Self->Day && Item->GetDay() != Self->Day; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }
            const auto Request =
                MakeShared<Gs2::Money2::Request::FDescribeDailyTransactionHistoriesRequest>()
                    ->WithContextStack(Self->Gs2->DefaultContextStack)
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithYear(Self->Year)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            ;
            const auto Future = Self->Client->DescribeDailyTransactionHistories(Request);
            Future->StartSynchronousTask();
            if (Future->GetTask().IsError())
            {
                ErrorValue = Future->GetTask().Error();
                bLast = true;
                return *this;
            }
            else
            {
                ErrorValue = nullptr;
            }
            const auto R = Future->GetTask().Result();
            Future->EnsureCompletion();
            Range = R->GetItems().IsValid() ? R->GetItems() : MakeShared<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>>();
            const auto ResultModel = R;


            if (Range.IsValid())
            {
                for (const auto& Item : *Range)
                {
                    if (!Item.IsValid()) continue;
                    Gs2::Money2::Model::Cache::FDailyTransactionHistoryCache::Put(
                        Self->Gs2->Cache,
                        Request->GetNamespaceName(), Item->GetYear(), Item->GetMonth(), Item->GetDay(), Item->GetCurrency(),
                        TOptional<int32>(), Item
                    );
                }
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item) { return Self->Year && Item->GetYear() != Self->Year; });
                Range->RemoveAll([this](const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item) { return Self->Month && Item->GetMonth() != Self->Month; });
                Range->RemoveAll([this](const Gs2::Money2::Model::FDailyTransactionHistoryPtr& Item) { return Self->Day && Item->GetDay() != Self->Day; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Money2::Model::FDailyTransactionHistory::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FDescribeDailyTransactionHistoriesIterator::FIterator FDescribeDailyTransactionHistoriesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FDescribeDailyTransactionHistoriesIterator::FIterator FDescribeDailyTransactionHistoriesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FDescribeDailyTransactionHistoriesIterator::FIterator FDescribeDailyTransactionHistoriesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

