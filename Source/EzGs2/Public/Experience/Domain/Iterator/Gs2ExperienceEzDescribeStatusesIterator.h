
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
#include "Experience/Domain/Iterator/DescribeStatusesIterator.h"
#include "Experience/Model/Gs2ExperienceEzStatus.h"

namespace Gs2::UE5::Experience::Domain::Iterator
{

	class EZGS2_API FEzDescribeStatusesIterator:
            public TSharedFromThis<FEzDescribeStatusesIterator>
    {

		TSharedPtr<Gs2::Experience::Domain::Iterator::FDescribeStatusesIterator> Iterator;

	public:

        explicit FEzDescribeStatusesIterator(
            const Gs2::Experience::Domain::Iterator::FDescribeStatusesIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeStatusesIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Experience::Model::FEzStatus>,
            public TSharedFromThis<FDescribeStatusesIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Experience::Domain::Iterator::FDescribeStatusesIterator::FNextTask>> Task;

        public:
            explicit FDescribeStatusesIteratorLoadTask(
	            const TSharedPtr<Gs2::Experience::Domain::Iterator::FDescribeStatusesIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Experience::Model::FEzStatus>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeStatusesIterator;

			TSharedPtr<FAsyncTask<Gs2::Experience::Domain::Iterator::FDescribeStatusesIterator::FNextTask>> Task;
			Gs2::UE5::Experience::Model::FEzStatusPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Experience::Domain::Iterator::FDescribeStatusesIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Experience::Model::FEzStatusPtr& operator*() const;
			Gs2::UE5::Experience::Model::FEzStatusPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeStatusesIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeStatusesIterator> FEzDescribeStatusesIteratorPtr;
}
