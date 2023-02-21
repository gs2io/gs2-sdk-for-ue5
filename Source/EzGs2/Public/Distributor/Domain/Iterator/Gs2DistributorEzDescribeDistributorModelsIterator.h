
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
#include "Distributor/Domain/Iterator/DescribeDistributorModelsIterator.h"
#include "Distributor/Model/Gs2DistributorEzDistributorModel.h"

namespace Gs2::UE5::Distributor::Domain::Iterator
{

	class EZGS2_API FEzDescribeDistributorModelsIterator:
            public TSharedFromThis<FEzDescribeDistributorModelsIterator>
    {

		TSharedPtr<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator> Iterator;

	public:

        explicit FEzDescribeDistributorModelsIterator(
            const Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeDistributorModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Distributor::Model::FEzDistributorModel>,
            public TSharedFromThis<FDescribeDistributorModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeDistributorModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Distributor::Model::FEzDistributorModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeDistributorModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator::FNextTask>> Task;
			Gs2::UE5::Distributor::Model::FEzDistributorModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Distributor::Domain::Iterator::FDescribeDistributorModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Distributor::Model::FEzDistributorModelPtr& operator*() const;
			Gs2::UE5::Distributor::Model::FEzDistributorModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeDistributorModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeDistributorModelsIterator> FEzDescribeDistributorModelsIteratorPtr;
}
