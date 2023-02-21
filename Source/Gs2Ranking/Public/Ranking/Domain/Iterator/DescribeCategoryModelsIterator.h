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

    class FDescribeCategoryModelsIteratorLoadTask;

    class GS2RANKING_API FDescribeCategoryModelsIterator :
        public Gs2::Core::Domain::Model::TGs2Iterator<Gs2::Ranking::Model::FCategoryModel, FDescribeCategoryModelsIteratorLoadTask>
    {
        const Core::Domain::FCacheDatabasePtr Cache;
        const Gs2::Ranking::FGs2RankingRestClientPtr Client;

        friend FDescribeCategoryModelsIteratorLoadTask;
        virtual TSharedPtr<FAsyncTask<FDescribeCategoryModelsIteratorLoadTask>> Load() override;

public:
        const TOptional<FString> NamespaceName;
        TOptional<int32> FetchSize;

        FDescribeCategoryModelsIterator(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Ranking::FGs2RankingRestClientPtr Client,
            const TOptional<FString> NamespaceName
        );

        class GS2RANKING_API IteratorImpl
        {
            friend FDescribeCategoryModelsIterator;

            TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator::FNextTask>> Task;
            Gs2::Ranking::Model::FCategoryModelPtr Current;

        public:
            explicit IteratorImpl(
                const TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator::FNextTask>> Task
            ): Task(Task)
            {

            }
            const Gs2::Ranking::Model::FCategoryModelPtr& operator*() const;
            Gs2::Ranking::Model::FCategoryModelPtr operator->();
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
    typedef TSharedPtr<FDescribeCategoryModelsIterator> FDescribeCategoryModelsIteratorPtr;

    class FDescribeCategoryModelsIteratorLoadTask :
        public Gs2::Core::Util::TGs2Future<TArray<Gs2::Ranking::Model::FCategoryModelPtr>>,
        public TSharedFromThis<FDescribeCategoryModelsIteratorLoadTask>
    {
        TSharedPtr<FDescribeCategoryModelsIterator> Self;

    public:
        explicit FDescribeCategoryModelsIteratorLoadTask(
            TSharedPtr<FDescribeCategoryModelsIterator> Self
        ): Self(Self)
        {

        }

        virtual Gs2::Core::Model::FGs2ErrorPtr Action(
            TSharedPtr<TSharedPtr<TArray<Gs2::Ranking::Model::FCategoryModelPtr>>> Result
        ) override;
    };
}
