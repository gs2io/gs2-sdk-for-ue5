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

    class GS2LOG_API FCountExecuteStampTaskLogIterator :
        public TSharedFromThis<FCountExecuteStampTaskLogIterator>
    {
        const TSharedPtr<Core::Domain::FGs2> Gs2;
        const Gs2::Log::FGs2LogRestClientPtr Client;
        const TOptional<FString> NamespaceName;
        const TOptional<bool> Service;
        const TOptional<bool> Method;
        const TOptional<bool> UserId;
        const TOptional<bool> Action;
        const TOptional<int64> Begin;
        const TOptional<int64> End;
        const TOptional<bool> LongTerm;
        const TOptional<FString> TimeOffsetToken;

    public:
        FCountExecuteStampTaskLogIterator(
            const TSharedPtr<Core::Domain::FGs2> Gs2,
            const Gs2::Log::FGs2LogRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<bool> Service = TOptional<bool>(),
            const TOptional<bool> Method = TOptional<bool>(),
            const TOptional<bool> UserId = TOptional<bool>(),
            const TOptional<bool> Action = TOptional<bool>(),
            const TOptional<int64> Begin = TOptional<int64>(),
            const TOptional<int64> End = TOptional<int64>(),
            const TOptional<bool> LongTerm = TOptional<bool>(),
            const TOptional<FString> TimeOffsetToken = TOptional<FString>()
        );

        FCountExecuteStampTaskLogIterator(
            const FCountExecuteStampTaskLogIterator& From
        );

        class FIterator;

        class GS2LOG_API FIteratorNextTask :
            public Gs2::Core::Util::TGs2Future<Gs2::Log::Model::FExecuteStampTaskLogCount>
        {
        private:
            FIterator& Iterator;

        public:
            FIteratorNextTask(FIterator& Iterator) :
                Iterator(Iterator)
            {}

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::Log::Model::FExecuteStampTaskLogCount>> Result) override;

            static TSharedPtr<FAsyncTask<FIteratorNextTask>> Issue(FIterator& Iterator)
            {
                return Gs2::Core::Util::New<FAsyncTask<FIteratorNextTask>>(Iterator);
            }
        };

        class GS2LOG_API FIterator
        {
            TSharedRef<FCountExecuteStampTaskLogIterator> Self;
            TSharedPtr<TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>> Range;
            TOptional<TArray<Gs2::Log::Model::FExecuteStampTaskLogCountPtr>::TIterator> RangeIteratorOpt;
            Gs2::Core::Model::FGs2ErrorPtr ErrorValue;
            bool bLast;
            bool bEnd;
            TOptional<FString> PageToken;
            TOptional<int32> FetchSize;

            class FOneBeforeBegin {};
            class FEnd {};

            FIterator(
                const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable,
                FOneBeforeBegin
            );

            explicit FIterator(
                const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable
            ) :
                FIterator(Iterable, FOneBeforeBegin())
            {
                operator++();
            }

            FIterator(
                const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable,
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

            Gs2::Log::Model::FExecuteStampTaskLogCountPtr& Current()
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

            static FIterator OneBeforeBeginOf(const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable)
            {
                return FIterator(Iterable, FOneBeforeBegin());
            }

            static FIterator BeginOf(const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable)
            {
                return FIterator(Iterable);
            }

            static FIterator EndOf(const TSharedRef<FCountExecuteStampTaskLogIterator> Iterable)
            {
                return FIterator(Iterable, FEnd());
            }
        };

        FIterator OneBeforeBegin();
        FIterator begin();
        FIterator end();
    };
    typedef TSharedPtr<FCountExecuteStampTaskLogIterator> FCountExecuteStampTaskLogIteratorPtr;
}
