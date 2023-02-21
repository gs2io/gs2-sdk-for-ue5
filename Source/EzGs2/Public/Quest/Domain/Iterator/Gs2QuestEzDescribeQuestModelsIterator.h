
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
#include "Quest/Domain/Iterator/DescribeQuestModelsIterator.h"
#include "Quest/Model/Gs2QuestEzQuestModel.h"

namespace Gs2::UE5::Quest::Domain::Iterator
{

	class EZGS2_API FEzDescribeQuestModelsIterator:
            public TSharedFromThis<FEzDescribeQuestModelsIterator>
    {

		TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator> Iterator;

	public:

        explicit FEzDescribeQuestModelsIterator(
            const Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeQuestModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzQuestModel>,
            public TSharedFromThis<FDescribeQuestModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeQuestModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeQuestModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator::FNextTask>> Task;
			Gs2::UE5::Quest::Model::FEzQuestModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Quest::Model::FEzQuestModelPtr& operator*() const;
			Gs2::UE5::Quest::Model::FEzQuestModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeQuestModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeQuestModelsIterator> FEzDescribeQuestModelsIteratorPtr;
}
