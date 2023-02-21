
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
#include "Quest/Domain/Iterator/DescribeQuestGroupModelsIterator.h"
#include "Quest/Model/Gs2QuestEzQuestGroupModel.h"

namespace Gs2::UE5::Quest::Domain::Iterator
{

	class EZGS2_API FEzDescribeQuestGroupModelsIterator:
            public TSharedFromThis<FEzDescribeQuestGroupModelsIterator>
    {

		TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeQuestGroupModelsIterator> Iterator;

	public:

        explicit FEzDescribeQuestGroupModelsIterator(
            const Gs2::Quest::Domain::Iterator::FDescribeQuestGroupModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeQuestGroupModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzQuestGroupModel>,
            public TSharedFromThis<FDescribeQuestGroupModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestGroupModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeQuestGroupModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeQuestGroupModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzQuestGroupModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeQuestGroupModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestGroupModelsIterator::FNextTask>> Task;
			Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeQuestGroupModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr& operator*() const;
			Gs2::UE5::Quest::Model::FEzQuestGroupModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeQuestGroupModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeQuestGroupModelsIterator> FEzDescribeQuestGroupModelsIteratorPtr;
}
