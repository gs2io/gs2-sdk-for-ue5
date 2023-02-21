
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
#include "Matchmaking/Domain/Iterator/DescribeRatingModelsIterator.h"
#include "Matchmaking/Model/Gs2MatchmakingEzRatingModel.h"

namespace Gs2::UE5::Matchmaking::Domain::Iterator
{

	class EZGS2_API FEzDescribeRatingModelsIterator:
            public TSharedFromThis<FEzDescribeRatingModelsIterator>
    {

		TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator> Iterator;

	public:

        explicit FEzDescribeRatingModelsIterator(
            const Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeRatingModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Matchmaking::Model::FEzRatingModel>,
            public TSharedFromThis<FDescribeRatingModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeRatingModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Matchmaking::Model::FEzRatingModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeRatingModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator::FNextTask>> Task;
			Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Matchmaking::Domain::Iterator::FDescribeRatingModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr& operator*() const;
			Gs2::UE5::Matchmaking::Model::FEzRatingModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeRatingModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeRatingModelsIterator> FEzDescribeRatingModelsIteratorPtr;
}
