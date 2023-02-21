
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
#include "Schedule/Domain/Iterator/DescribeEventsIterator.h"
#include "Schedule/Model/Gs2ScheduleEzEvent.h"

namespace Gs2::UE5::Schedule::Domain::Iterator
{

	class EZGS2_API FEzDescribeEventsIterator:
            public TSharedFromThis<FEzDescribeEventsIterator>
    {

		TSharedPtr<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator> Iterator;

	public:

        explicit FEzDescribeEventsIterator(
            const Gs2::Schedule::Domain::Iterator::FDescribeEventsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeEventsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzEvent>,
            public TSharedFromThis<FDescribeEventsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator::FNextTask>> Task;

        public:
            explicit FDescribeEventsIteratorLoadTask(
	            const TSharedPtr<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Schedule::Model::FEzEvent>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeEventsIterator;

			TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator::FNextTask>> Task;
			Gs2::UE5::Schedule::Model::FEzEventPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeEventsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Schedule::Model::FEzEventPtr& operator*() const;
			Gs2::UE5::Schedule::Model::FEzEventPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeEventsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeEventsIterator> FEzDescribeEventsIteratorPtr;
}
