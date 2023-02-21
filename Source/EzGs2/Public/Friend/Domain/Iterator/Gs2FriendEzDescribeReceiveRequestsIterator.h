
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
#include "Friend/Domain/Iterator/DescribeReceiveRequestsIterator.h"
#include "Friend/Model/Gs2FriendEzFriendRequest.h"

namespace Gs2::UE5::Friend::Domain::Iterator
{

	class EZGS2_API FEzDescribeReceiveRequestsIterator:
            public TSharedFromThis<FEzDescribeReceiveRequestsIterator>
    {

		TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator> Iterator;

	public:

        explicit FEzDescribeReceiveRequestsIterator(
            const Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeReceiveRequestsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Friend::Model::FEzFriendRequest>,
            public TSharedFromThis<FDescribeReceiveRequestsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator::FNextTask>> Task;

        public:
            explicit FDescribeReceiveRequestsIteratorLoadTask(
	            const TSharedPtr<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendRequest>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeReceiveRequestsIterator;

			TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator::FNextTask>> Task;
			Gs2::UE5::Friend::Model::FEzFriendRequestPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Friend::Domain::Iterator::FDescribeReceiveRequestsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Friend::Model::FEzFriendRequestPtr& operator*() const;
			Gs2::UE5::Friend::Model::FEzFriendRequestPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeReceiveRequestsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeReceiveRequestsIterator> FEzDescribeReceiveRequestsIteratorPtr;
}
