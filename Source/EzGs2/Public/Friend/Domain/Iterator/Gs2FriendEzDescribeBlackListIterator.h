
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
#include "Friend/Domain/Iterator/DescribeBlackListIterator.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

	class EZGS2_API FEzDescribeBlackListIterator:
            public TSharedFromThis<FEzDescribeBlackListIterator>
    {

		TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator> Iterator;

	public:

        explicit FEzDescribeBlackListIterator(
            const Gs2::Friend::Domain::Iterator::FDescribeBlackListIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeBlackListIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::Friend::Model::FBlackListEntry>,
            public TSharedFromThis<FDescribeBlackListIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator::FNextTask>> Task;

        public:
            explicit FDescribeBlackListIteratorLoadTask(
	            const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Friend::Model::FBlackListEntry>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeBlackListIterator;

			TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator::FNextTask>> Task;
			Gs2::Friend::Model::FBlackListEntryPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeBlackListIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::Friend::Model::FBlackListEntryPtr& operator*() const;
			Gs2::Friend::Model::FBlackListEntryPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeBlackListIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeBlackListIterator> FEzDescribeBlackListIteratorPtr;
}
