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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Domain/Gs2Core.h"
#include "Auth/Gs2Auth.h"
#include "Money2/Gs2Money2.h"

namespace Gs2::Money2::Domain::Iterator
{

    class GS2MONEY2_API FDescribeDailyTransactionHistoriesIterator :
        public TSharedFromThis<FDescribeDailyTransactionHistoriesIterator>
    {
        const TSharedPtr<Core::Domain::FGs2> Gs2;
        const Gs2::Money2::FGs2Money2RestClientPtr Client;
        const TOptional<FString> NamespaceName;
        const TOptional<int32> Year;
        const TOptional<int32> Month;
        const TOptional<int32> Day;

    public:
        FDescribeDailyTransactionHistoriesIterator(
            const TSharedPtr<Core::Domain::FGs2> Gs2,
            const Gs2::Money2::FGs2Money2RestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<int32> Year,
            const TOptional<int32> Month = TOptional<int32>(),
            const TOptional<int32> Day = TOptional<int32>()
        );

        FDescribeDailyTransactionHistoriesIterator(
            const FDescribeDailyTransactionHistoriesIterator& From
        );

        class FIterator;

        class GS2MONEY2_API FIteratorNextTask :
            public Gs2::Core::Util::TGs2Future<Gs2::Money2::Model::FDailyTransactionHistory>
        {
        private:
            FIterator& Iterator;

        public:
            FIteratorNextTask(FIterator& Iterator) :
                Iterator(Iterator)
            {}

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Money2::Model::FDailyTransactionHistory>> Result) override;

            static TSharedPtr<FAsyncTask<FIteratorNextTask>> Issue(FIterator& Iterator)
            {
                return Gs2::Core::Util::New<FAsyncTask<FIteratorNextTask>>(Iterator);
            }
        };

        class GS2MONEY2_API FIterator
        {
            TSharedRef<FDescribeDailyTransactionHistoriesIterator> Self;
            TSharedPtr<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>> Range;
            TOptional<TArray<Gs2::Money2::Model::FDailyTransactionHistoryPtr>::TIterator> RangeIteratorOpt;
            Gs2::Core::Model::FGs2ErrorPtr ErrorValue;
            bool bLast;
            bool bEnd;
            TOptional<FString> PageToken;
            TOptional<int32> FetchSize;

            class FOneBeforeBegin {};
            class FEnd {};

            FIterator(
                const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable,
                FOneBeforeBegin
            );

            explicit FIterator(
                const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable
            ) :
                FIterator(Iterable, FOneBeforeBegin())
            {
                operator++();
            }

            FIterator(
                const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable,
                FEnd
            ) : Self(Iterable), bEnd(true)
            {}

        public:
            FIterator(
                const FIterator& Iterator
            ) :
                Self(Iterator.Self),
                Range(Iterator.Range),
                RangeIteratorOpt(Iterator.RangeIteratorOpt),
                ErrorValue(Iterator.ErrorValue),
                bLast(Iterator.bLast),
                bEnd(Iterator.bEnd),
                PageToken(Iterator.PageToken),
                FetchSize(Iterator.FetchSize)
            {}

            FIterator& operator*()
            {
                return *this;
            }

            const FIterator& operator*() const
            {
                return *this;
            }

            FIterator* operator->()
            {
                return this;
            }

            const FIterator* operator->() const
            {
                return this;
            }

            FIterator& operator++();

            friend bool operator== (const FIterator& a, const FIterator& b)
            {
                return a.Self == b.Self && a.bEnd && b.bEnd;
            }
            friend bool operator!= (const FIterator& a, const FIterator& b)
            {
                return !operator==(a, b);
            }

            bool HasNext() const
            {
                return !bEnd;
            }

            TSharedPtr<FAsyncTask<FIteratorNextTask>> Next()
            {
                return FIteratorNextTask::Issue(*this);
            }

            Gs2::Money2::Model::FDailyTransactionHistoryPtr& Current()
            {
                return **RangeIteratorOpt;
            }

            bool IsCurrentValid() const
            {
                return RangeIteratorOpt && *RangeIteratorOpt;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error() const
            {
                return ErrorValue;
            }

            bool IsError() const
            {
                return ErrorValue != nullptr;
            }

            void Retry()
            {
                if (ErrorValue && bLast)
                {
                    bLast = false;
                }
            }

            static FIterator OneBeforeBeginOf(const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable)
            {
                return FIterator(Iterable, FOneBeforeBegin());
            }

            static FIterator BeginOf(const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable)
            {
                return FIterator(Iterable);
            }

            static FIterator EndOf(const TSharedRef<FDescribeDailyTransactionHistoriesIterator> Iterable)
            {
                return FIterator(Iterable, FEnd());
            }
        };

        FIterator OneBeforeBegin();
        FIterator begin();
        FIterator end();
    };
    typedef TSharedPtr<FDescribeDailyTransactionHistoriesIterator> FDescribeDailyTransactionHistoriesIteratorPtr;
}
