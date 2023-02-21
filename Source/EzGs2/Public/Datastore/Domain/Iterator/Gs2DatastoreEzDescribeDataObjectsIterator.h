
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
#include "Datastore/Domain/Iterator/DescribeDataObjectsIterator.h"
#include "Datastore/Model/Gs2DatastoreEzDataObject.h"

namespace Gs2::UE5::Datastore::Domain::Iterator
{

	class EZGS2_API FEzDescribeDataObjectsIterator:
            public TSharedFromThis<FEzDescribeDataObjectsIterator>
    {

		TSharedPtr<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator> Iterator;

	public:

        explicit FEzDescribeDataObjectsIterator(
            const Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeDataObjectsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Datastore::Model::FEzDataObject>,
            public TSharedFromThis<FDescribeDataObjectsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator::FNextTask>> Task;

        public:
            explicit FDescribeDataObjectsIteratorLoadTask(
	            const TSharedPtr<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Datastore::Model::FEzDataObject>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeDataObjectsIterator;

			TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator::FNextTask>> Task;
			Gs2::UE5::Datastore::Model::FEzDataObjectPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Datastore::Domain::Iterator::FDescribeDataObjectsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Datastore::Model::FEzDataObjectPtr& operator*() const;
			Gs2::UE5::Datastore::Model::FEzDataObjectPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeDataObjectsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeDataObjectsIterator> FEzDescribeDataObjectsIteratorPtr;
}
