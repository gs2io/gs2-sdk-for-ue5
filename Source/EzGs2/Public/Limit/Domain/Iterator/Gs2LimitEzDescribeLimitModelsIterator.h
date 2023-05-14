
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
#include "Limit/Domain/Iterator/DescribeLimitModelsIterator.h"
#include "Limit/Model/Gs2LimitEzLimitModel.h"

namespace Gs2::UE5::Limit::Domain::Iterator
{

	class EZGS2_API FEzDescribeLimitModelsIterator :
        public TSharedFromThis<FEzDescribeLimitModelsIterator>
    {

		Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIteratorPtr DomainIterable;

	public:

        explicit FEzDescribeLimitModelsIterator(
            Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator& DomainIterable
        ) : DomainIterable(DomainIterable.AsShared())
        {}

        explicit FEzDescribeLimitModelsIterator(
            Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIteratorPtr DomainIterable
        ) : DomainIterable(DomainIterable)
        {}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeLimitModelsIterator;

			Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FIterator DomainIterator;
			Gs2::UE5::Limit::Model::FEzLimitModelPtr CurrentValue;

			explicit FIterator(
				Gs2::Limit::Domain::Iterator::FDescribeLimitModelsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(nullptr)
			{}

		public:
			explicit FIterator(
				FEzDescribeLimitModelsIterator& Iterable
			) :
			    FIterator(Iterable.begin())
			{}

			FIterator(
			    const FIterator& Iterator
            ) :
                DomainIterator(Iterator.DomainIterator),
                CurrentValue(Iterator.CurrentValue)
            {}

			FIterator& operator*()
			{
				return *this;
			}

			const FIterator& operator*() const
			{
				return *this;
			}

			FIterator* operator->()
			{
				return this;
			}

			const FIterator* operator->() const
			{
				return this;
			}

			FIterator& operator++()
			{
				++DomainIterator;
				CurrentValue = DomainIterator.HasNext() && !DomainIterator.IsError()
	    			? Gs2::UE5::Limit::Model::FEzLimitModel::FromModel(DomainIterator.Current())
					: nullptr;
				return *this;
			}

            Gs2::UE5::Limit::Model::FEzLimitModelPtr& Current()
            {
                return CurrentValue;
            }

            Gs2::Core::Model::FGs2ErrorPtr Error()
            {
                return DomainIterator.Error();
            }

            bool IsError() const
            {
                return DomainIterator.IsError();
            }

            void Retry()
            {
                DomainIterator.Retry();
            }

			friend bool operator== (const FIterator& a, const FIterator& b)
			{
				return a.DomainIterator == b.DomainIterator;
			}
			friend bool operator!= (const FIterator& a, const FIterator& b)
			{
				return !operator==(a, b);
			}
		};

		FIterator OneBeforeBegin()
		{
			return FIterator(DomainIterable->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(DomainIterable->begin());
		}
		FIterator end()
		{
			return FIterator(DomainIterable->end());
		}
    };
	typedef TSharedPtr<FEzDescribeLimitModelsIterator> FEzDescribeLimitModelsIteratorPtr;
}
