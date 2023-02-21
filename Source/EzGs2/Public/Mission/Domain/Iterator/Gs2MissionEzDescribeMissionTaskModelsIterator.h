
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
#include "Mission/Domain/Iterator/DescribeMissionTaskModelsIterator.h"
#include "Mission/Model/Gs2MissionEzMissionTaskModel.h"

namespace Gs2::UE5::Mission::Domain::Iterator
{

	class EZGS2_API FEzDescribeMissionTaskModelsIterator:
            public TSharedFromThis<FEzDescribeMissionTaskModelsIterator>
    {

		TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator> Iterator;

	public:

        explicit FEzDescribeMissionTaskModelsIterator(
            const Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIteratorPtr Iterator
        );

	    class EZGS2_API FDescribeMissionTaskModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Mission::Model::FEzMissionTaskModel>,
            public TSharedFromThis<FDescribeMissionTaskModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeMissionTaskModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Model::FEzMissionTaskModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeMissionTaskModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator::FNextTask>> Task;
			Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::Mission::Domain::Iterator::FDescribeMissionTaskModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr& operator*() const;
			Gs2::UE5::Mission::Model::FEzMissionTaskModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeMissionTaskModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeMissionTaskModelsIterator> FEzDescribeMissionTaskModelsIteratorPtr;
}
