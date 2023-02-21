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
#include "Limit/Gs2Limit.h"

namespace Gs2::Limit::Domain::Iterator
{

    class FDescribeCountersByUserIdIteratorLoadTask;

    class GS2LIMIT_API FDescribeCountersByUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Limit::Model::FCounter, FDescribeCountersByUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Limit::FGs2LimitRestClientPtr Client;

        friend FDescribeCountersByUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeCountersByUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> UserId;
        const TOptional<FString> LimitName;
        TOptional<FString> PageToken;
        TOptional<int32> FetchSize;

        FDescribeCountersByUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Limit::FGs2LimitRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> UserId,
            const TOptional<FString> LimitName
        );

        class GS2LIMIT_API IteratorImpl
        {
            friend FDescribeCountersByUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeCountersByUserIdIterator::FNextTask>> Task;
            Gs2::Limit::Model::FCounterPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeCountersByUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Limit::Model::FCounterPtr& operator*() const;
            Gs2::Limit::Model::FCounterPtr operator->();
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
    typedef TSharedPtr<FDescribeCountersByUserIdIterator> FDescribeCountersByUserIdIteratorPtr;

    class FDescribeCountersByUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Limit::Model::FCounterPtr>>,
        public TSharedFromThis<FDescribeCountersByUserIdIteratorLoadTask>
    {
        TSharedPtr<FDescribeCountersByUserIdIterator> Self;

    public:
        explicit FDescribeCountersByUserIdIteratorLoadTask(
            TSharedPtr<FDescribeCountersByUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Limit::Model::FCounterPtr>>> Result
        ) override;
    };
}
