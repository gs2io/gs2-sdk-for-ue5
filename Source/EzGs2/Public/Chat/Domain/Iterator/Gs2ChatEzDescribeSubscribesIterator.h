
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
#include "Chat/Domain/Iterator/DescribeSubscribesIterator.h"
#include "Chat/Model/Gs2ChatEzSubscribe.h"

namespace Gs2::UE5::Chat::Domain::Iterator
{

	class EZGS2_API FEzDescribeSubscribesIterator:
            public TSharedFromThis<FEzDescribeSubscribesIterator>
    {

		TSharedPtr<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator> Iterator;

	public:

        explicit FEzDescribeSubscribesIterator(
            const Gs2::Chat::Domain::Iterator::FDescribeSubscribesIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeSubscribesIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Model::FEzSubscribe>,
            public TSharedFromThis<FDescribeSubscribesIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator::FNextTask>> Task;

        public:
            explicit FDescribeSubscribesIteratorLoadTask(
	            const TSharedPtr<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Model::FEzSubscribe>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeSubscribesIterator;

			TSharedPtr<FAsyncTask<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator::FNextTask>> Task;
			Gs2::UE5::Chat::Model::FEzSubscribePtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Chat::Domain::Iterator::FDescribeSubscribesIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Chat::Model::FEzSubscribePtr& operator*() const;
			Gs2::UE5::Chat::Model::FEzSubscribePtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeSubscribesIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeSubscribesIterator> FEzDescribeSubscribesIteratorPtr;
}
