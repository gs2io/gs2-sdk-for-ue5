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
#include "Dictionary/Gs2Dictionary.h"

namespace Gs2::Dictionary::Domain::Iterator
{

    class FDescribeEntriesByUserIdIteratorLoadTask;

    class GS2DICTIONARY_API FDescribeEntriesByUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Dictionary::Model::FEntry, FDescribeEntriesByUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        friend FDescribeEntriesByUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeEntriesByUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeEntriesByUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId
        );

        class GS2DICTIONARY_API IteratorImpl
        {
            friend FDescribeEntriesByUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntriesByUserIdIterator::FNextTask>> Task;
            Gs2::Dictionary::Model::FEntryPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntriesByUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Dictionary::Model::FEntryPtr& operator*() const;
            Gs2::Dictionary::Model::FEntryPtr operator->();
            IteratorImpl& operator++();

            friend bool operator== (const IteratorImpl& a, const IteratorImpl& b)
            {
                if (a.Task == nullptr && b.Task == nullptr)
                {
                    return true;
                }
                if (a.Task == nullptr)
                {
                    return b.Current == nullptr;
                }
                if (b.Task == nullptr)
                {
                    return a.Current == nullptr;
                }
                return a.Current == b.Current;
            };
            friend bool operator!= (const IteratorImpl& a, const IteratorImpl& b)
            {
                return !operator==(a, b);
            };
        };

        IteratorImpl begin();
        IteratorImpl end();
    };
    typedef TSharedPtr<FDescribeEntriesByUserIdIterator> FDescribeEntriesByUserIdIteratorPtr;

    class FDescribeEntriesByUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Dictionary::Model::FEntryPtr>>,
        public TSharedFromThis<FDescribeEntriesByUserIdIteratorLoadTask>
    {
        TSharedPtr<FDescribeEntriesByUserIdIterator> Self;

    public:
        explicit FDescribeEntriesByUserIdIteratorLoadTask(
            TSharedPtr<FDescribeEntriesByUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Dictionary::Model::FEntryPtr>>> Result
        ) override;
    };
}
