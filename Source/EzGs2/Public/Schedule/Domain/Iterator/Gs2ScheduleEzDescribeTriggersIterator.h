
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
#include "Schedule/Domain/Iterator/DescribeTriggersIterator.h"
#include "Schedule/Model/Gs2ScheduleEzTrigger.h"

namespace Gs2::UE5::Schedule::Domain::Iterator
{

	class EZGS2_API FEzDescribeTriggersIterator:
            public TSharedFromThis<FEzDescribeTriggersIterator>
    {

		TSharedPtr<Gs2::Schedule::Domain::Iterator::FDescribeTriggersIterator> Iterator;

	public:

        explicit FEzDescribeTriggersIterator(
            const Gs2::Schedule::Domain::Iterator::FDescribeTriggersIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeTriggersIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Schedule::Model::FEzTrigger>,
            public TSharedFromThis<FDescribeTriggersIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeTriggersIterator::FNextTask>> Task;

        public:
            explicit FDescribeTriggersIteratorLoadTask(
	            const TSharedPtr<Gs2::Schedule::Domain::Iterator::FDescribeTriggersIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Schedule::Model::FEzTrigger>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeTriggersIterator;

			TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeTriggersIterator::FNextTask>> Task;
			Gs2::UE5::Schedule::Model::FEzTriggerPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Schedule::Domain::Iterator::FDescribeTriggersIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Schedule::Model::FEzTriggerPtr& operator*() const;
			Gs2::UE5::Schedule::Model::FEzTriggerPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeTriggersIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeTriggersIterator> FEzDescribeTriggersIteratorPtr;
}
