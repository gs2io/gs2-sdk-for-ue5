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
#include "SeasonRating/Domain/Model/Namespace.h"
#include "SeasonRating/Model/Gs2SeasonRatingEzSeasonModel.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::SeasonRating::Domain::Iterator
{

	class EZGS2_API FEzDescribeSeasonModelsIterator :
        public TSharedFromThis<FEzDescribeSeasonModelsIterator>
    {
        Gs2::SeasonRating::Domain::Iterator::FDescribeSeasonModelsIteratorPtr It;
        Gs2::SeasonRating::Domain::Model::FNamespaceDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;

	public:

        explicit FEzDescribeSeasonModelsIterator(
            Gs2::SeasonRating::Domain::Model::FNamespaceDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        ) :
            It(
                Domain->SeasonModels(
                )
            ),
            Domain(Domain),
            Connection(Connection)
        {
        }

		FEzDescribeSeasonModelsIterator(
			const FEzDescribeSeasonModelsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			Connection(From.Connection)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeSeasonModelsIterator;

			Gs2::SeasonRating::Domain::Iterator::FDescribeSeasonModelsIterator::FIterator DomainIterator;
			Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr CurrentValue;
        	static Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr ConvertCurrent(
        		Gs2::SeasonRating::Domain::Iterator::FDescribeSeasonModelsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::SeasonRating::Model::FEzSeasonModel::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::SeasonRating::Domain::Iterator::FDescribeSeasonModelsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeSeasonModelsIterator& Iterable
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
				CurrentValue = ConvertCurrent(DomainIterator);
				return *this;
			}
            Gs2::UE5::SeasonRating::Model::FEzSeasonModelPtr& Current()
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
			return FIterator(It->OneBeforeBegin());
		}
		FIterator begin()
		{
			return FIterator(It->begin());
		}
		FIterator end()
		{
			return FIterator(It->end());
		}
    };
	typedef TSharedPtr<FEzDescribeSeasonModelsIterator> FEzDescribeSeasonModelsIteratorPtr;
}
