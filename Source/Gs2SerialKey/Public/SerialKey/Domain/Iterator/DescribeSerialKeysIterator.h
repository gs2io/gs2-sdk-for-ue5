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
#include "SerialKey/Gs2SerialKey.h"

namespace Gs2::SerialKey::Domain::Iterator
{

    class GS2SERIALKEY_API FDescribeSerialKeysIterator :
        public TSharedFromThis<FDescribeSerialKeysIterator>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client;
        const TOptional<FString> NamespaceName;
        const TOptional<FString> CampaignModelName;
        const TOptional<FString> IssueJobName;

    public:
        FDescribeSerialKeysIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::SerialKey::FGs2SerialKeyRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CampaignModelName,
            const TOptional<FString> IssueJobName
        );

        class FIterator;

        class GS2SERIALKEY_API FIteratorNextTask :
            public Gs2::Core::Util::TGs2Future<Gs2::SerialKey::Model::FSerialKey>
        {
        private:
            FIterator& Iterator;

        public:
            FIteratorNextTask(FIterator& Iterator) :
                Iterator(Iterator)
            {}

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(TSharedPtr<TSharedPtr<Gs2::SerialKey::Model::FSerialKey>> Result) override;

            static TSharedPtr<FAsyncTask<FIteratorNextTask>> Issue(FIterator& Iterator)
            {
                return Gs2::Core::Util::New<FAsyncTask<FIteratorNextTask>>(Iterator);
            }
        };

        class GS2SERIALKEY_API FIterator
        {
            TSharedRef<FDescribeSerialKeysIterator> Self;
            TSharedPtr<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>> Range;
            TOptional<TArray<Gs2::SerialKey::Model::FSerialKeyPtr>::TIterator> RangeIteratorOpt;
            Gs2::Core::Model::FGs2ErrorPtr ErrorValue;
            bool bLast;
            bool bEnd;
            TOptional<FString> PageToken;
            TOptional<int32> FetchSize;

            class FOneBeforeBegin {};
            class FEnd {};

            FIterator(
                const TSharedRef<FDescribeSerialKeysIterator> Iterable,
                FOneBeforeBegin
            );

            explicit FIterator(
                const TSharedRef<FDescribeSerialKeysIterator> Iterable
            ) :
                FIterator(Iterable, FOneBeforeBegin())
            {
                operator++();
            }

            FIterator(
                const TSharedRef<FDescribeSerialKeysIterator> Iterable,
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

            Gs2::SerialKey::Model::FSerialKeyPtr& Current()
            {
                return **RangeIteratorOpt;
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

            static FIterator OneBeforeBeginOf(const TSharedRef<FDescribeSerialKeysIterator> Iterable)
            {
                return FIterator(Iterable, FOneBeforeBegin());
            }

            static FIterator BeginOf(const TSharedRef<FDescribeSerialKeysIterator> Iterable)
            {
                return FIterator(Iterable);
            }

            static FIterator EndOf(const TSharedRef<FDescribeSerialKeysIterator> Iterable)
            {
                return FIterator(Iterable, FEnd());
            }
        };

        FIterator OneBeforeBegin();
        FIterator begin();
        FIterator end();
    };
    typedef TSharedPtr<FDescribeSerialKeysIterator> FDescribeSerialKeysIteratorPtr;
}
