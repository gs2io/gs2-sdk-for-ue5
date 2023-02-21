
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
#include "Formation/Domain/Iterator/DescribeMoldsIterator.h"
#include "Formation/Model/Gs2FormationEzMold.h"

namespace Gs2::UE5::Formation::Domain::Iterator
{

	class EZGS2_API FEzDescribeMoldsIterator:
            public TSharedFromThis<FEzDescribeMoldsIterator>
    {

		TSharedPtr<Gs2::Formation::Domain::Iterator::FDescribeMoldsIterator> Iterator;

	public:

        explicit FEzDescribeMoldsIterator(
            const Gs2::Formation::Domain::Iterator::FDescribeMoldsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeMoldsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Formation::Model::FEzMold>,
            public TSharedFromThis<FDescribeMoldsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribeMoldsIterator::FNextTask>> Task;

        public:
            explicit FDescribeMoldsIteratorLoadTask(
	            const TSharedPtr<Gs2::Formation::Domain::Iterator::FDescribeMoldsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Formation::Model::FEzMold>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeMoldsIterator;

			TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribeMoldsIterator::FNextTask>> Task;
			Gs2::UE5::Formation::Model::FEzMoldPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Formation::Domain::Iterator::FDescribeMoldsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Formation::Model::FEzMoldPtr& operator*() const;
			Gs2::UE5::Formation::Model::FEzMoldPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeMoldsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeMoldsIterator> FEzDescribeMoldsIteratorPtr;
}
