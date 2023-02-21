
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
#include "MegaField/Domain/Iterator/DescribeAreaModelsIterator.h"
#include "MegaField/Model/Gs2MegaFieldEzAreaModel.h"

namespace Gs2::UE5::MegaField::Domain::Iterator
{

	class EZGS2_API FEzDescribeAreaModelsIterator:
            public TSharedFromThis<FEzDescribeAreaModelsIterator>
    {

		TSharedPtr<Gs2::MegaField::Domain::Iterator::FDescribeAreaModelsIterator> Iterator;

	public:

        explicit FEzDescribeAreaModelsIterator(
            const Gs2::MegaField::Domain::Iterator::FDescribeAreaModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeAreaModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzAreaModel>,
            public TSharedFromThis<FDescribeAreaModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeAreaModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeAreaModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::MegaField::Domain::Iterator::FDescribeAreaModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::MegaField::Model::FEzAreaModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeAreaModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeAreaModelsIterator::FNextTask>> Task;
			Gs2::UE5::MegaField::Model::FEzAreaModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeAreaModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::MegaField::Model::FEzAreaModelPtr& operator*() const;
			Gs2::UE5::MegaField::Model::FEzAreaModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeAreaModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeAreaModelsIterator> FEzDescribeAreaModelsIteratorPtr;
}
