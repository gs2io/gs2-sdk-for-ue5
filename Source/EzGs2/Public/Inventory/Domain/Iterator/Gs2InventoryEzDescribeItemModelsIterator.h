
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

	class EZGS2_API FEzDescribeItemModelsIterator :
        public TSharedFromThis<FEzDescribeItemModelsIterator>
    {

		Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIteratorPtr DomainIterable;

	public:

        explicit FEzDescribeItemModelsIterator(
            Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator& DomainIterable
        ) : DomainIterable(DomainIterable.AsShared())
        {}

        explicit FEzDescribeItemModelsIterator(
            Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIteratorPtr DomainIterable
        ) : DomainIterable(DomainIterable)
        {}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeItemModelsIterator;

			Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FIterator DomainIterator;
			Gs2::UE5::Inventory::Model::FEzItemModelPtr CurrentValue;

			explicit FIterator(
				Gs2::Inventory::Domain::Iterator::FDescribeItemModelsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(nullptr)
			{}

		public:
			explicit FIterator(
				FEzDescribeItemModelsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = DomainIterator.HasNext() && !DomainIterator.IsError()
	    			? Gs2::UE5::Inventory::Model::FEzItemModel::FromModel(DomainIterator.Current())
					: nullptr;
				return *this;
			}

            Gs2::UE5::Inventory::Model::FEzItemModelPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(DomainIterable->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(DomainIterable->begin());
		}
		FIterator end()
		{
			return FIterator(DomainIterable->end());
		}
    };
	typedef TSharedPtr<FEzDescribeItemModelsIterator> FEzDescribeItemModelsIteratorPtr;
}
