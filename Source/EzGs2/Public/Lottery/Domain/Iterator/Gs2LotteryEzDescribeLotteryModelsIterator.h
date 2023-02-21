
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
#include "Lottery/Domain/Iterator/DescribeLotteryModelsIterator.h"
#include "Lottery/Model/Gs2LotteryEzLotteryModel.h"

namespace Gs2::UE5::Lottery::Domain::Iterator
{

	class EZGS2_API FEzDescribeLotteryModelsIterator:
            public TSharedFromThis<FEzDescribeLotteryModelsIterator>
    {

		TSharedPtr<Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator> Iterator;

	public:

        explicit FEzDescribeLotteryModelsIterator(
            const Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeLotteryModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Lottery::Model::FEzLotteryModel>,
            public TSharedFromThis<FDescribeLotteryModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeLotteryModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Lottery::Model::FEzLotteryModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeLotteryModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator::FNextTask>> Task;
			Gs2::UE5::Lottery::Model::FEzLotteryModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Lottery::Domain::Iterator::FDescribeLotteryModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Lottery::Model::FEzLotteryModelPtr& operator*() const;
			Gs2::UE5::Lottery::Model::FEzLotteryModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeLotteryModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeLotteryModelsIterator> FEzDescribeLotteryModelsIteratorPtr;
}
