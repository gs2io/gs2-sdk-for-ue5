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
#include "Ranking/Gs2Ranking.h"

namespace Gs2::Ranking::Domain::Iterator
{

    class FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask;

    class GS2RANKING_API FDescribeSubscribesByCategoryNameAndUserIdIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Ranking::Model::FSubscribeUser, FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Ranking::FGs2RankingRestClientPtr Client;

        friend FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        const TOptional<FString> CategoryName;
        const TOptional<FString> UserId;
        TOptional<int32> FetchSize;

        FDescribeSubscribesByCategoryNameAndUserIdIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Ranking::FGs2RankingRestClientPtr Client,
            const TOptional<FString> NamespaceName,
            const TOptional<FString> CategoryName,
            const TOptional<FString> UserId
        );

        class GS2RANKING_API IteratorImpl
        {
            friend FDescribeSubscribesByCategoryNameAndUserIdIterator;

            TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIterator::FNextTask>> Task;
            Gs2::Ranking::Model::FSubscribeUserPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameAndUserIdIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Ranking::Model::FSubscribeUserPtr& operator*() const;
            Gs2::Ranking::Model::FSubscribeUserPtr operator->();
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
    typedef TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdIterator> FDescribeSubscribesByCategoryNameAndUserIdIteratorPtr;

    class FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>,
        public TSharedFromThis<FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask>
    {
        TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdIterator> Self;

    public:
        explicit FDescribeSubscribesByCategoryNameAndUserIdIteratorLoadTask(
            TSharedPtr<FDescribeSubscribesByCategoryNameAndUserIdIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Ranking::Model::FSubscribeUserPtr>>> Result
        ) override;
    };
}
