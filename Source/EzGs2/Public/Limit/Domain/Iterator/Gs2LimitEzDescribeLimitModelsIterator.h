
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
#include "Limit/Domain/Iterator/DescribeLimitModelsIterator.h"
#include "Limit/Model/Gs2LimitEzLimitModel.h"

namespace Gs2::UE5::Limit::Domain::Iterator
{

	class EZGS2_API FEzDescribeLimitModelsIterator:
            public TSharedFromThis<FEzDescribeLimitModelsIterator>
    {

		TSharedPtr<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator> Iterator;

	public:

        explicit FEzDescribeLimitModelsIterator(
            const Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeLimitModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Limit::Model::FEzLimitModel>,
            public TSharedFromThis<FDescribeLimitModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeLimitModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Limit::Model::FEzLimitModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeLimitModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FNextTask>> Task;
			Gs2::UE5::Limit::Model::FEzLimitModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Limit::Model::FEzLimitModelPtr& operator*() const;
			Gs2::UE5::Limit::Model::FEzLimitModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeLimitModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeLimitModelsIterator> FEzDescribeLimitModelsIteratorPtr;
}
