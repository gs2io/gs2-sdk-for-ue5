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
 *
 * deny overwrite
 */

#if defined(_MSC_VER)
#pragma warning (push)
#pragma warning (disable: 4458) // Declaration hides class member
#elif defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wshadow" // declaration shadows a field of
#endif

// ReSharper disable CppUnusedIncludeDirective

#include "Log/Domain/Iterator/QueryTimeseriesIterator.h"
#include "Log/Domain/Model/LogEntry.h"

#include "Core/Domain/Gs2.h"

namespace Gs2::Log::Domain::Iterator
{

    FQueryTimeseriesIterator::FQueryTimeseriesIterator(
        const TSharedPtr<Core::Domain::FGs2> Gs2,
        const Gs2::Log::FGs2LogRestClientPtr Client,
        const TOptional<FString> NamespaceName,
        const Gs2::Log::Model::FAggregationConfigPtr Aggregation,
        const TOptional<int64> Begin,
        const TOptional<int64> End,
        const TOptional<FString> Query,
        const TOptional<TArray<FString>> GroupBy,
        const TOptional<int32> Interval,
        const TOptional<int32> SeriesLimit
        // ReSharper disable once CppMemberInitializersOrder
    ):
        Gs2(Gs2),
        Client(Client),
        NamespaceName(NamespaceName),
        Begin(Begin),
        End(End),
        Query(Query),
        GroupBy(GroupBy),
        Aggregation(Aggregation),
        Interval(Interval),
        SeriesLimit(SeriesLimit)
    {
    }

    FQueryTimeseriesIterator::FQueryTimeseriesIterator(
        const FQueryTimeseriesIterator& From
    ):
        Gs2(From.Gs2),
        Client(From.Client),
        NamespaceName(From.NamespaceName),
        Begin(From.Begin),
        End(From.End),
        Query(From.Query),
        GroupBy(From.GroupBy),
        Aggregation(From.Aggregation),
        Interval(From.Interval),
        SeriesLimit(From.SeriesLimit)
    {
    }

    Gs2::Core::Model::FGs2ErrorPtr FQueryTimeseriesIterator::FIteratorNextTask::Action(TSharedPtr<TSharedPtr<Gs2::Log::Model::FTimeseriesPoint>> Result)
    {
        ++Iterator;
        *Result = Iterator->Current();
        return Iterator.Error();
    }

    FQueryTimeseriesIterator::FIterator::FIterator(
        const TSharedRef<FQueryTimeseriesIterator> Iterable,
        FOneBeforeBegin
    ) :
        Self(Iterable),
        bLast(false),
        bEnd(false),
        PageToken(TOptional<FString>()),
        FetchSize(TOptional<int32>())
    {
    }

    FQueryTimeseriesIterator::FIterator& FQueryTimeseriesIterator::FIterator::operator++()
    {
        

        if (bEnd) return *this;

        if (ErrorValue && bLast)
        {
            bEnd = true;
            return *this;
        }

        if (RangeIteratorOpt) ++*RangeIteratorOpt;

        if (!RangeIteratorOpt || (!*RangeIteratorOpt && !bLast))
        {
            const auto ListParentKey = "log:TimeseriesPoint";

            if (!RangeIteratorOpt)
            {
                Range = Self->Gs2->Cache->TryGetList<Gs2::Log::Model::FTimeseriesPoint>(ListParentKey);

                if (Range)
                {
                    Range->RemoveAll([this](const Gs2::Log::Model::FTimeseriesPointPtr& Item) { return Self->Begin && *Item->GetTimestamp() < *Self->Begin; });
                    Range->RemoveAll([this](const Gs2::Log::Model::FTimeseriesPointPtr& Item) { return Self->End && *Item->GetTimestamp() > *Self->End; });
                    bLast = true;
                    RangeIteratorOpt = Range->CreateIterator();
                    PageToken = TOptional<FString>();
                    bEnd = !static_cast<bool>(*RangeIteratorOpt) && bLast;
                    return *this;
                }
            }

            const auto Future = Self->Client->QueryTimeseries(
                MakeShared<Gs2::Log::Request::FQueryTimeseriesRequest>()
                    ->WithNamespaceName(Self->NamespaceName)
                    ->WithBegin(Self->Begin)
                    ->WithEnd(Self->End)
                    ->WithAggregation(Self->Aggregation)
                    ->WithInterval(Self->Interval)
                    ->WithSeriesLimit(Self->SeriesLimit)
                    ->WithPageToken(PageToken)
                    ->WithLimit(FetchSize)
            );
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
            Range = R->GetItems();
            for (auto Item : *R->GetItems())
            {
                Self->Gs2->Cache->Put(
                    Gs2::Log::Model::FTimeseriesPoint::TypeName,
                    ListParentKey,
                    Gs2::Log::Domain::Model::FLogEntryDomain::CreateCacheKey(
                    ),
                    Item,
                    FDateTime::Now() + FTimespan::FromMinutes(Gs2::Core::Domain::DefaultCacheMinutes)
                );
            }
            if (Range)
            {
                Range->RemoveAll([this](const Gs2::Log::Model::FTimeseriesPointPtr& Item) { return Self->Begin && *Item->GetTimestamp() < *Self->Begin; });
                Range->RemoveAll([this](const Gs2::Log::Model::FTimeseriesPointPtr& Item) { return Self->End && *Item->GetTimestamp() > *Self->End; });
            }
            RangeIteratorOpt = Range->CreateIterator();
            PageToken = R->GetNextPageToken();
            bLast = !PageToken.IsSet();
            if (bLast) {
                Self->Gs2->Cache->SetListCached(
                    Gs2::Log::Model::FTimeseriesPoint::TypeName,
                    ListParentKey
                );
            }
        }

        bEnd = bLast && !*RangeIteratorOpt;
        return *this;
    }

    FQueryTimeseriesIterator::FIterator FQueryTimeseriesIterator::OneBeforeBegin()
    {
        return FIterator::OneBeforeBeginOf(this->AsShared());
    }

    FQueryTimeseriesIterator::FIterator FQueryTimeseriesIterator::begin()
    {
        return FIterator::BeginOf(this->AsShared());
    }

    FQueryTimeseriesIterator::FIterator FQueryTimeseriesIterator::end()
    {
        return FIterator::EndOf(this->AsShared());
    }
}

#if defined(_MSC_VER)
#pragma warning (pop)
#elif defined(__clang__)
#pragma clang diagnostic pop
#endif

