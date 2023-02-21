
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
#include "Inventory/Domain/Iterator/DescribeInventoriesIterator.h"
#include "Inventory/Model/Gs2InventoryEzInventory.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

	class EZGS2_API FEzDescribeInventoriesIterator:
            public TSharedFromThis<FEzDescribeInventoriesIterator>
    {

		TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIterator> Iterator;

	public:

        explicit FEzDescribeInventoriesIterator(
            const Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeInventoriesIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzInventory>,
            public TSharedFromThis<FDescribeInventoriesIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIterator::FNextTask>> Task;

        public:
            explicit FDescribeInventoriesIteratorLoadTask(
	            const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzInventory>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeInventoriesIterator;

			TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIterator::FNextTask>> Task;
			Gs2::UE5::Inventory::Model::FEzInventoryPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeInventoriesIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Inventory::Model::FEzInventoryPtr& operator*() const;
			Gs2::UE5::Inventory::Model::FEzInventoryPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeInventoriesIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeInventoriesIterator> FEzDescribeInventoriesIteratorPtr;
}
