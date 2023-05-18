
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
#include "Datastore/Domain/Iterator/DescribeDataObjectHistoriesIterator.h"
#include "Datastore/Model/Gs2DatastoreEzDataObjectHistory.h"

namespace Gs2::UE5::Datastore::Domain::Iterator
{

	class EZGS2_API FEzDescribeDataObjectHistoriesIterator :
        public TSharedFromThis<FEzDescribeDataObjectHistoriesIterator>
    {

		Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIteratorPtr DomainIterable;

	public:

        explicit FEzDescribeDataObjectHistoriesIterator(
            Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIterator& DomainIterable
        ) : DomainIterable(DomainIterable.AsShared())
        {}

        explicit FEzDescribeDataObjectHistoriesIterator(
            Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIteratorPtr DomainIterable
        ) : DomainIterable(DomainIterable)
        {}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeDataObjectHistoriesIterator;

			Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIterator::FIterator DomainIterator;
			Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr CurrentValue;

        	static Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr ConvertCurrent(
        		Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Datastore::Model::FEzDataObjectHistory::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Datastore::Domain::Iterator::FDescribeDataObjectHistoriesIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeDataObjectHistoriesIterator& Iterable
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
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}

            Gs2::UE5::Datastore::Model::FEzDataObjectHistoryPtr& Current()
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
	typedef TSharedPtr<FEzDescribeDataObjectHistoriesIterator> FEzDescribeDataObjectHistoriesIteratorPtr;
}
