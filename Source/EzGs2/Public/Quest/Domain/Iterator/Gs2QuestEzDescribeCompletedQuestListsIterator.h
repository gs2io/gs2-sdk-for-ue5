
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
#include "Quest/Domain/Iterator/DescribeCompletedQuestListsIterator.h"
#include "Quest/Model/Gs2QuestEzCompletedQuestList.h"

namespace Gs2::UE5::Quest::Domain::Iterator
{

	class EZGS2_API FEzDescribeCompletedQuestListsIterator:
            public TSharedFromThis<FEzDescribeCompletedQuestListsIterator>
    {

		TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator> Iterator;

	public:

        explicit FEzDescribeCompletedQuestListsIterator(
            const Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeCompletedQuestListsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Quest::Model::FEzCompletedQuestList>,
            public TSharedFromThis<FDescribeCompletedQuestListsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator::FNextTask>> Task;

        public:
            explicit FDescribeCompletedQuestListsIteratorLoadTask(
	            const TSharedPtr<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzCompletedQuestList>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeCompletedQuestListsIterator;

			TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator::FNextTask>> Task;
			Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Quest::Domain::Iterator::FDescribeCompletedQuestListsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr& operator*() const;
			Gs2::UE5::Quest::Model::FEzCompletedQuestListPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeCompletedQuestListsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeCompletedQuestListsIterator> FEzDescribeCompletedQuestListsIteratorPtr;
}
