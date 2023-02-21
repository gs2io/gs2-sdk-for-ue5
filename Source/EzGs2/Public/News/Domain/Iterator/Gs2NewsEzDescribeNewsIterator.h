
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
#include "News/Domain/Iterator/DescribeNewsIterator.h"
#include "News/Model/Gs2NewsEzNews.h"

namespace Gs2::UE5::News::Domain::Iterator
{

	class EZGS2_API FEzDescribeNewsIterator:
            public TSharedFromThis<FEzDescribeNewsIterator>
    {

		TSharedPtr<Gs2::News::Domain::Iterator::FDescribeNewsIterator> Iterator;

	public:

        explicit FEzDescribeNewsIterator(
            const Gs2::News::Domain::Iterator::FDescribeNewsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeNewsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::News::Model::FEzNews>,
            public TSharedFromThis<FDescribeNewsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::News::Domain::Iterator::FDescribeNewsIterator::FNextTask>> Task;

        public:
            explicit FDescribeNewsIteratorLoadTask(
	            const TSharedPtr<Gs2::News::Domain::Iterator::FDescribeNewsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::News::Model::FEzNews>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeNewsIterator;

			TSharedPtr<FAsyncTask<Gs2::News::Domain::Iterator::FDescribeNewsIterator::FNextTask>> Task;
			Gs2::UE5::News::Model::FEzNewsPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::News::Domain::Iterator::FDescribeNewsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::News::Model::FEzNewsPtr& operator*() const;
			Gs2::UE5::News::Model::FEzNewsPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeNewsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeNewsIterator> FEzDescribeNewsIteratorPtr;
}
