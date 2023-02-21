
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
#include "Inventory/Domain/Iterator/DescribeItemModelsIterator.h"
#include "Inventory/Model/Gs2InventoryEzItemModel.h"

namespace Gs2::UE5::Inventory::Domain::Iterator
{

	class EZGS2_API FEzDescribeItemModelsIterator:
            public TSharedFromThis<FEzDescribeItemModelsIterator>
    {

		TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator> Iterator;

	public:

        explicit FEzDescribeItemModelsIterator(
            const Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeItemModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Inventory::Model::FEzItemModel>,
            public TSharedFromThis<FDescribeItemModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeItemModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Inventory::Model::FEzItemModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeItemModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FNextTask>> Task;
			Gs2::UE5::Inventory::Model::FEzItemModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Inventory::Model::FEzItemModelPtr& operator*() const;
			Gs2::UE5::Inventory::Model::FEzItemModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeItemModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeItemModelsIterator> FEzDescribeItemModelsIteratorPtr;
}
