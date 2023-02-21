
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
#include "Mission/Domain/Iterator/DescribeCounterModelsIterator.h"
#include "Mission/Model/Gs2MissionEzCounterModel.h"

namespace Gs2::UE5::Mission::Domain::Iterator
{

	class EZGS2_API FEzDescribeCounterModelsIterator:
            public TSharedFromThis<FEzDescribeCounterModelsIterator>
    {

		TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator> Iterator;

	public:

        explicit FEzDescribeCounterModelsIterator(
            const Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeCounterModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzCounterModel>,
            public TSharedFromThis<FDescribeCounterModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeCounterModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzCounterModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeCounterModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator::FNextTask>> Task;
			Gs2::UE5::Mission::Model::FEzCounterModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeCounterModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Mission::Model::FEzCounterModelPtr& operator*() const;
			Gs2::UE5::Mission::Model::FEzCounterModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeCounterModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeCounterModelsIterator> FEzDescribeCounterModelsIteratorPtr;
}
