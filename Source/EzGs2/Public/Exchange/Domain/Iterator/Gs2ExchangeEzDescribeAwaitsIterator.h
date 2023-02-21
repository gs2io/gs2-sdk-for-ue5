
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
#include "Exchange/Domain/Iterator/DescribeAwaitsIterator.h"
#include "Exchange/Model/Gs2ExchangeEzAwait.h"

namespace Gs2::UE5::Exchange::Domain::Iterator
{

	class EZGS2_API FEzDescribeAwaitsIterator:
            public TSharedFromThis<FEzDescribeAwaitsIterator>
    {

		TSharedPtr<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator> Iterator;

	public:

        explicit FEzDescribeAwaitsIterator(
            const Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeAwaitsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzAwait>,
            public TSharedFromThis<FDescribeAwaitsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator::FNextTask>> Task;

        public:
            explicit FDescribeAwaitsIteratorLoadTask(
	            const TSharedPtr<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzAwait>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeAwaitsIterator;

			TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator::FNextTask>> Task;
			Gs2::UE5::Exchange::Model::FEzAwaitPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeAwaitsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Exchange::Model::FEzAwaitPtr& operator*() const;
			Gs2::UE5::Exchange::Model::FEzAwaitPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeAwaitsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeAwaitsIterator> FEzDescribeAwaitsIteratorPtr;
}
