
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
#include "Dictionary/Domain/Iterator/DescribeEntryModelsIterator.h"
#include "Dictionary/Model/Gs2DictionaryEzEntryModel.h"

namespace Gs2::UE5::Dictionary::Domain::Iterator
{

	class EZGS2_API FEzDescribeEntryModelsIterator:
            public TSharedFromThis<FEzDescribeEntryModelsIterator>
    {

		TSharedPtr<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator> Iterator;

	public:

        explicit FEzDescribeEntryModelsIterator(
            const Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeEntryModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Dictionary::Model::FEzEntryModel>,
            public TSharedFromThis<FDescribeEntryModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeEntryModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Dictionary::Model::FEzEntryModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeEntryModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator::FNextTask>> Task;
			Gs2::UE5::Dictionary::Model::FEzEntryModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Dictionary::Domain::Iterator::FDescribeEntryModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Dictionary::Model::FEzEntryModelPtr& operator*() const;
			Gs2::UE5::Dictionary::Model::FEzEntryModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeEntryModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeEntryModelsIterator> FEzDescribeEntryModelsIteratorPtr;
}
