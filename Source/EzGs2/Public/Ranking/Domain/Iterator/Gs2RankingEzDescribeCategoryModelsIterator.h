
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
#include "Ranking/Domain/Iterator/DescribeCategoryModelsIterator.h"
#include "Ranking/Model/Gs2RankingEzCategoryModel.h"

namespace Gs2::UE5::Ranking::Domain::Iterator
{

	class EZGS2_API FEzDescribeCategoryModelsIterator:
            public TSharedFromThis<FEzDescribeCategoryModelsIterator>
    {

		TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator> Iterator;

	public:

        explicit FEzDescribeCategoryModelsIterator(
            const Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeCategoryModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Ranking::Model::FEzCategoryModel>,
            public TSharedFromThis<FDescribeCategoryModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeCategoryModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Model::FEzCategoryModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeCategoryModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator::FNextTask>> Task;
			Gs2::UE5::Ranking::Model::FEzCategoryModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Ranking::Domain::Iterator::FDescribeCategoryModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Ranking::Model::FEzCategoryModelPtr& operator*() const;
			Gs2::UE5::Ranking::Model::FEzCategoryModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeCategoryModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeCategoryModelsIterator> FEzDescribeCategoryModelsIteratorPtr;
}
