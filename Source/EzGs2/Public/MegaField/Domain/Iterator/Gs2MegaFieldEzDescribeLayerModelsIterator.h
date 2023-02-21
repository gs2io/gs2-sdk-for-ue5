
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
#include "MegaField/Domain/Iterator/DescribeLayerModelsIterator.h"
#include "MegaField/Model/Gs2MegaFieldEzLayerModel.h"

namespace Gs2::UE5::MegaField::Domain::Iterator
{

	class EZGS2_API FEzDescribeLayerModelsIterator:
            public TSharedFromThis<FEzDescribeLayerModelsIterator>
    {

		TSharedPtr<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator> Iterator;

	public:

        explicit FEzDescribeLayerModelsIterator(
            const Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeLayerModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::MegaField::Model::FEzLayerModel>,
            public TSharedFromThis<FDescribeLayerModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeLayerModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::MegaField::Model::FEzLayerModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeLayerModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator::FNextTask>> Task;
			Gs2::UE5::MegaField::Model::FEzLayerModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::MegaField::Domain::Iterator::FDescribeLayerModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::MegaField::Model::FEzLayerModelPtr& operator*() const;
			Gs2::UE5::MegaField::Model::FEzLayerModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeLayerModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeLayerModelsIterator> FEzDescribeLayerModelsIteratorPtr;
}
