
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
#include "Friend/Domain/Iterator/DescribeFollowsIterator.h"
#include "Friend/Model/Gs2FriendEzFollowUser.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

	class EZGS2_API FEzDescribeFollowsIterator:
            public TSharedFromThis<FEzDescribeFollowsIterator>
    {

		TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator> Iterator;

	public:

        explicit FEzDescribeFollowsIterator(
            const Gs2::Friend::Domain::Iterator::FDescribeFollowsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeFollowsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzFollowUser>,
            public TSharedFromThis<FDescribeFollowsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator::FNextTask>> Task;

        public:
            explicit FDescribeFollowsIteratorLoadTask(
	            const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Model::FEzFollowUser>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeFollowsIterator;

			TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator::FNextTask>> Task;
			Gs2::UE5::Friend::Model::FEzFollowUserPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeFollowsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Friend::Model::FEzFollowUserPtr& operator*() const;
			Gs2::UE5::Friend::Model::FEzFollowUserPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeFollowsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeFollowsIterator> FEzDescribeFollowsIteratorPtr;
}
