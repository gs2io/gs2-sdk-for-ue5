
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
#include "Inventory/Domain/Iterator/DescribeItemSetsIterator.h"
#include "Inventory/Model/Gs2InventoryEzItemSet.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

	class EZGS2_API FEzDescribeItemSetsIterator:
            public TSharedFromThis<FEzDescribeItemSetsIterator>
    {

		TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator> Iterator;

	public:

        explicit FEzDescribeItemSetsIterator(
            const Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeItemSetsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzItemSet>,
            public TSharedFromThis<FDescribeItemSetsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator::FNextTask>> Task;

        public:
            explicit FDescribeItemSetsIteratorLoadTask(
	            const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemSet>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeItemSetsIterator;

			TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator::FNextTask>> Task;
			Gs2::UE5::Inventory::Model::FEzItemSetPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemSetsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Inventory::Model::FEzItemSetPtr& operator*() const;
			Gs2::UE5::Inventory::Model::FEzItemSetPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeItemSetsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeItemSetsIterator> FEzDescribeItemSetsIteratorPtr;
}
