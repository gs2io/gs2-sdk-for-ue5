
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
#include "Matchmaking/Domain/Iterator/DescribeRatingsIterator.h"
#include "Matchmaking/Model/Gs2MatchmakingEzRating.h"

namespace Gs2::UE5::Matchmaking::Domain::Iterator
{

	class EZGS2_API FEzDescribeRatingsIterator:
            public TSharedFromThis<FEzDescribeRatingsIterator>
    {

		TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator> Iterator;

	public:

        explicit FEzDescribeRatingsIterator(
            const Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeRatingsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Model::FEzRating>,
            public TSharedFromThis<FDescribeRatingsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator::FNextTask>> Task;

        public:
            explicit FDescribeRatingsIteratorLoadTask(
	            const TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRating>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeRatingsIterator;

			TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator::FNextTask>> Task;
			Gs2::UE5::Matchmaking::Model::FEzRatingPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Matchmaking::Model::FEzRatingPtr& operator*() const;
			Gs2::UE5::Matchmaking::Model::FEzRatingPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeRatingsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeRatingsIterator> FEzDescribeRatingsIteratorPtr;
}
