
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
#include "Version/Domain/Iterator/DescribeAcceptVersionsIterator.h"
#include "Version/Model/Gs2VersionEzAcceptVersion.h"

namespace Gs2::UE5::Version::Domain::Iterator
{

	class EZGS2_API FEzDescribeAcceptVersionsIterator:
            public TSharedFromThis<FEzDescribeAcceptVersionsIterator>
    {

		TSharedPtr<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIterator> Iterator;

	public:

        explicit FEzDescribeAcceptVersionsIterator(
            const Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeAcceptVersionsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Version::Model::FEzAcceptVersion>,
            public TSharedFromThis<FDescribeAcceptVersionsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIterator::FNextTask>> Task;

        public:
            explicit FDescribeAcceptVersionsIteratorLoadTask(
	            const TSharedPtr<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Version::Model::FEzAcceptVersion>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeAcceptVersionsIterator;

			TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIterator::FNextTask>> Task;
			Gs2::UE5::Version::Model::FEzAcceptVersionPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Version::Domain::Iterator::FDescribeAcceptVersionsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Version::Model::FEzAcceptVersionPtr& operator*() const;
			Gs2::UE5::Version::Model::FEzAcceptVersionPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeAcceptVersionsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeAcceptVersionsIterator> FEzDescribeAcceptVersionsIteratorPtr;
}
