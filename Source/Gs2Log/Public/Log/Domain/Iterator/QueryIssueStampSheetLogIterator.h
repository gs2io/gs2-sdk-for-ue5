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
#include "Log/Gs2Log.h"

namespace Gs2::Log::Domain::Iterator
{

    class GS2LOG_API FQueryIssueStampSheetLogIterator :
        public TSharedFromThis<FQueryIssueStampSheetLogIterator>
    {
        const TSharedPtr<Core::Domain::FGs2> Gs2;
        const Gs2::Log::FGs2LogRestClientPtr Client;
        const TOptional<FString> NamespaceName;
        const TOptional<FString> Service;
        const TOptional<FString> Method;
        const TOptional<FString> UserId;
        const TOptional<FString> Action;
        const TOptional<int64> Begin;
        const TOptional<int64> End;
        const TOptional<bool> LongTerm;
        const TOptional<FString> TimeOffsetToken;

    public:
        FQueryIssueStampSheetLogIterator(
            const TSharedPtr<Core::Domain::FGs2> Gs2,
            const Gs2::Log::FGs2LogRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> Service = TOptional<FString>(),
            const TOptional<FString> Method = TOptional<FString>(),
            const TOptional<FString> UserId = TOptional<FString>(),
            const TOptional<FString> Action = TOptional<FString>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        FQueryIssueStampSheetLogIterator(
            const FQueryIssueStampSheetLogIterator& From
        );

        class FIterator;

        class GS2LOG_API FIteratorNextTask :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FIssueStampSheetLog>
        {
        private:
            FIterator& Iterator;

        public:
            FIteratorNextTask(FIterator& Iterator) :
                Iterator(Iterator)
            {}

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Log::Model::FIssueStampSheetLog>> Result) override;

            static TSharedPtr<FAsyncTask<FIteratorNextTask>> Issue(FIterator& Iterator)
            {
                return Gs2::Core::Util::New<FAsyncTask<FIteratorNextTask>>(Iterator);
            }
        };

        class GS2LOG_API FIterator
        {
            TSharedRef<FQueryIssueStampSheetLogIterator> Self;
            TSharedPtr<TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>> Range;
            TOptional<TArray<Gs2::Log::Model::FIssueStampSheetLogPtr>::TIterator> RangeIteratorOpt;
            Gs2::Core::Model::FGs2ErrorPtr ErrorValue;
            bool bLast;
            bool bEnd;
            TOptional<FString> PageToken;
            TOptional<int32> FetchSize;

            class FOneBeforeBegin {};
            class FEnd {};

            FIterator(
                const TSharedRef<FQueryIssueStampSheetLogIterator> Iterable,
                FOneBeforeBegin
            );

            explicit FIterator(
                const TSharedRef<FQueryIssueStampSheetLogIterator> Iterable
            ) :
                FIterator(Iterable, FOneBeforeBegin())
            {
                operator++();
            }

            FIterator(
                const TSharedRef<FQueryIssueStampSheetLogIterator> Iterable,
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

            Gs2::Log::Model::FIssueStampSheetLogPtr& Current()
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

            static FIterator OneBeforeBeginOf(const TSharedRef<FQueryIssueStampSheetLogIterator> Iterable)
            {
                return FIterator(Iterable, FOneBeforeBegin());
            }

            static FIterator BeginOf(const TSharedRef<FQueryIssueStampSheetLogIterator> Iterable)
            {
                return FIterator(Iterable);
            }

            static FIterator EndOf(const TSharedRef<FQueryIssueStampSheetLogIterator> Iterable)
            {
                return FIterator(Iterable, FEnd());
            }
        };

        FIterator OneBeforeBegin();
        FIterator begin();
        FIterator end();
    };
    typedef TSharedPtr<FQueryIssueStampSheetLogIterator> FQueryIssueStampSheetLogIteratorPtr;
}
