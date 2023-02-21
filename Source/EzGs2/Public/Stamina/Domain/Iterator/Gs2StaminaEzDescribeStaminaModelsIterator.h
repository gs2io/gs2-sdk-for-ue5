
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
#include "Stamina/Domain/Iterator/DescribeStaminaModelsIterator.h"
#include "Stamina/Model/Gs2StaminaEzStaminaModel.h"

namespace Gs2::UE5::Stamina::Domain::Iterator
{

	class EZGS2_API FEzDescribeStaminaModelsIterator:
            public TSharedFromThis<FEzDescribeStaminaModelsIterator>
    {

		TSharedPtr<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator> Iterator;

	public:

        explicit FEzDescribeStaminaModelsIterator(
            const Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeStaminaModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Stamina::Model::FEzStaminaModel>,
            public TSharedFromThis<FDescribeStaminaModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeStaminaModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Stamina::Model::FEzStaminaModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeStaminaModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator::FNextTask>> Task;
			Gs2::UE5::Stamina::Model::FEzStaminaModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Stamina::Domain::Iterator::FDescribeStaminaModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Stamina::Model::FEzStaminaModelPtr& operator*() const;
			Gs2::UE5::Stamina::Model::FEzStaminaModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeStaminaModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeStaminaModelsIterator> FEzDescribeStaminaModelsIteratorPtr;
}
