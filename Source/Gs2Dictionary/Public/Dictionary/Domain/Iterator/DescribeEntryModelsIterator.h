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

    class FDescribeEntryModelsIteratorLoadTask;

    class GS2DICTIONARY_API FDescribeEntryModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Dictionary::Model::FEntryModel, FDescribeEntryModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client;

        friend FDescribeEntryModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeEntryModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeEntryModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Dictionary::FGs2DictionaryRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2DICTIONARY_API IteratorImpl
        {
            friend FDescribeEntryModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator::FNextTask>> Task;
            Gs2::Dictionary::Model::FEntryModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Dictionary::Model::FEntryModelPtr& operator*() const;
            Gs2::Dictionary::Model::FEntryModelPtr operator->();
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
    typedef TSharedPtr<FDescribeEntryModelsIterator> FDescribeEntryModelsIteratorPtr;

    class FDescribeEntryModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Dictionary::Model::FEntryModelPtr>>,
        public TSharedFromThis<FDescribeEntryModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeEntryModelsIterator> Self;

    public:
        explicit FDescribeEntryModelsIteratorLoadTask(
            TSharedPtr<FDescribeEntryModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Dictionary::Model::FEntryModelPtr>>> Result
        ) override;
    };
}
