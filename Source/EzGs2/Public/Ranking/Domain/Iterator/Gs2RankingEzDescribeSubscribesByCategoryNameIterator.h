
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
#include "Ranking/Domain/Iterator/DescribeSubscribesByCategoryNameIterator.h"
#include "Ranking/Model/Gs2RankingEzSubscribeUser.h"

namespace Gs2::UE5::Ranking::Domain::Iterator
{

	class EZGS2_API FEzDescribeSubscribesByCategoryNameIterator:
            public TSharedFromThis<FEzDescribeSubscribesByCategoryNameIterator>
    {

		TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIterator> Iterator;

	public:

        explicit FEzDescribeSubscribesByCategoryNameIterator(
            const Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeSubscribesByCategoryNameIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzSubscribeUser>,
            public TSharedFromThis<FDescribeSubscribesByCategoryNameIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIterator::FNextTask>> Task;

        public:
            explicit FDescribeSubscribesByCategoryNameIteratorLoadTask(
	            const TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Model::FEzSubscribeUser>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeSubscribesByCategoryNameIterator;

			TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIterator::FNextTask>> Task;
			Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeSubscribesByCategoryNameIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr& operator*() const;
			Gs2::UE5::Ranking::Model::FEzSubscribeUserPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeSubscribesByCategoryNameIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeSubscribesByCategoryNameIterator> FEzDescribeSubscribesByCategoryNameIteratorPtr;
}
