
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
#include "Lottery/Domain/Iterator/DescribeBoxesIterator.h"
#include "Lottery/Model/Gs2LotteryEzBoxItems.h"

namespace Gs2::UE5::Lottery::Domain::Iterator
{

	class EZGS2_API FEzDescribeBoxesIterator:
            public TSharedFromThis<FEzDescribeBoxesIterator>
    {

		TSharedPtr<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator> Iterator;

	public:

        explicit FEzDescribeBoxesIterator(
            const Gs2::Lottery::Domain::Iterator::FDescribeBoxesIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeBoxesIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Lottery::Model::FEzBoxItems>,
            public TSharedFromThis<FDescribeBoxesIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator::FNextTask>> Task;

        public:
            explicit FDescribeBoxesIteratorLoadTask(
	            const TSharedPtr<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Model::FEzBoxItems>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeBoxesIterator;

			TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator::FNextTask>> Task;
			Gs2::UE5::Lottery::Model::FEzBoxItemsPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribeBoxesIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Lottery::Model::FEzBoxItemsPtr& operator*() const;
			Gs2::UE5::Lottery::Model::FEzBoxItemsPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeBoxesIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeBoxesIterator> FEzDescribeBoxesIteratorPtr;
}
