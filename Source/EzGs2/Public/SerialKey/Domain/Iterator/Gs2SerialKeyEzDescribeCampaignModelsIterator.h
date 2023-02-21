
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
#include "SerialKey/Domain/Iterator/DescribeCampaignModelsIterator.h"
#include "SerialKey/Model/EzCampaignModel.h"

namespace Gs2::UE5::SerialKey::Domain::Iterator
{

	class EZGS2_API FEzDescribeCampaignModelsIterator:
            public TSharedFromThis<FEzDescribeCampaignModelsIterator>
    {

		TSharedPtr<Gs2::SerialKey::Domain::Iterator::FDescribeCampaignModelsIterator> Iterator;

	public:

        explicit FEzDescribeCampaignModelsIterator(
            const Gs2::SerialKey::Domain::Iterator::FDescribeCampaignModelsIteratorPtr Iterator
        );

	    class FDescribeCampaignModelsIteratorLoadTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::SerialKey::Model::FEzCampaignModel>,
            public TSharedFromThis<FDescribeCampaignModelsIteratorLoadTask>
        {
	        TSharedPtr<FAsyncTask<Gs2::SerialKey::Domain::Iterator::FDescribeCampaignModelsIterator::FNextTask>> Task;

        public:
            explicit FDescribeCampaignModelsIteratorLoadTask(
	            const TSharedPtr<Gs2::SerialKey::Domain::Iterator::FDescribeCampaignModelsIterator> Self
            );

        	virtual Gs2::Core::Model::FGs2ErrorPtr Action(
				TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Model::FEzCampaignModel>> Result
			) override;
        };

		class EZGS2_API IteratorImpl
		{
			friend FEzDescribeCampaignModelsIterator;

			TSharedPtr<FAsyncTask<Gs2::SerialKey::Domain::Iterator::FDescribeCampaignModelsIterator::FNextTask>> Task;
			Gs2::UE5::SerialKey::Model::FEzCampaignModelPtr Current;

		public:
			explicit IteratorImpl(
				const TSharedPtr<FAsyncTask<Gs2::SerialKey::Domain::Iterator::FDescribeCampaignModelsIterator::FNextTask>> Task
			): Task(Task)
			{

			}
			const Gs2::UE5::SerialKey::Model::FEzCampaignModelPtr& operator*() const;
			Gs2::UE5::SerialKey::Model::FEzCampaignModelPtr operator->();
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

		TSharedPtr<FAsyncTask<FDescribeCampaignModelsIteratorLoadTask>> Next() const;
    };
	typedef TSharedPtr<FEzDescribeCampaignModelsIterator> FEzDescribeCampaignModelsIteratorPtr;
}
