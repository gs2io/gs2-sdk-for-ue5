
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
#include "Account/Domain/Iterator/DescribeTakeOversIterator.h"
#include "Account/Model/Gs2AccountEzTakeOver.h"

namespace Gs2::UE5::Account::Domain::Iterator
{

	class EZGS2_API FEzDescribeTakeOversIterator:
            public TSharedFromThis<FEzDescribeTakeOversIterator>
    {

		TSharedPtr<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator> Iterator;

	public:

        explicit FEzDescribeTakeOversIterator(
            const Gs2::Account::Domain::Iterator::FDescribeTakeOversIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeTakeOversIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Account::Model::FEzTakeOver>,
            public TSharedFromThis<FDescribeTakeOversIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator::FNextTask>> Task;

        public:
            explicit FDescribeTakeOversIteratorLoadTask(
	            const TSharedPtr<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Account::Model::FEzTakeOver>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeTakeOversIterator;

			TSharedPtr<FAsyncTask<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator::FNextTask>> Task;
			Gs2::UE5::Account::Model::FEzTakeOverPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Account::Domain::Iterator::FDescribeTakeOversIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Account::Model::FEzTakeOverPtr& operator*() const;
			Gs2::UE5::Account::Model::FEzTakeOverPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeTakeOversIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeTakeOversIterator> FEzDescribeTakeOversIteratorPtr;
}
