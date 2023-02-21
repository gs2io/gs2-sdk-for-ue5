
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

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Domain/Iterator/DescribeRankingsIterator.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"

namespace Gs2::UE5::Ranking::Domain::Iterator
{

	class EZGS2_API FEzDescribeRankingsIterator:
            public TSharedFromThis<FEzDescribeRankingsIterator>
    {

		TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeRankingsIterator> Iterator;

	public:

        explicit FEzDescribeRankingsIterator(
            const Gs2::Ranking::Domain::Iterator::FDescribeRankingsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeRankingsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzRanking>,
            public TSharedFromThis<FDescribeRankingsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeRankingsIterator::FNextTask>> Task;

        public:
            explicit FDescribeRankingsIteratorLoadTask(
	            const TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeRankingsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Model::FEzRanking>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeRankingsIterator;

			TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeRankingsIterator::FNextTask>> Task;
			Gs2::UE5::Ranking::Model::FEzRankingPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeRankingsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Ranking::Model::FEzRankingPtr& operator*() const;
			Gs2::UE5::Ranking::Model::FEzRankingPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeRankingsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeRankingsIterator> FEzDescribeRankingsIteratorPtr;
}
