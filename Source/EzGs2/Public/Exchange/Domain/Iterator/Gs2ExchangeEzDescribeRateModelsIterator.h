
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
#include "Exchange/Domain/Iterator/DescribeRateModelsIterator.h"
#include "Exchange/Model/Gs2ExchangeEzRateModel.h"

namespace Gs2::UE5::Exchange::Domain::Iterator
{

	class EZGS2_API FEzDescribeRateModelsIterator:
            public TSharedFromThis<FEzDescribeRateModelsIterator>
    {

		TSharedPtr<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator> Iterator;

	public:

        explicit FEzDescribeRateModelsIterator(
            const Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeRateModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Exchange::Model::FEzRateModel>,
            public TSharedFromThis<FDescribeRateModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeRateModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Exchange::Model::FEzRateModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeRateModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator::FNextTask>> Task;
			Gs2::UE5::Exchange::Model::FEzRateModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Exchange::Domain::Iterator::FDescribeRateModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Exchange::Model::FEzRateModelPtr& operator*() const;
			Gs2::UE5::Exchange::Model::FEzRateModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeRateModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeRateModelsIterator> FEzDescribeRateModelsIteratorPtr;
}
