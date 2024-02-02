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
 *
 * deny overwrite
 */

#pragma once

#include "CoreMinimal.h"
#include "Ranking/Domain/Model/RankingCategory.h"
#include "Ranking/Model/Gs2RankingEzRanking.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Ranking::Domain::Iterator
{

	class EZGS2_API FEzDescribeNearRankingsIterator :
        public TSharedFromThis<FEzDescribeNearRankingsIterator>
    {
        Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIteratorPtr It;
        Gs2::Ranking::Domain::Model::FRankingCategoryDomainPtr Domain;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        int64 Score;

	public:

        explicit FEzDescribeNearRankingsIterator(
            Gs2::Ranking::Domain::Model::FRankingCategoryDomainPtr Domain,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            int64 Score
        ) :
            It(
                Domain->NearRankings(
                    Score
                )
            ),
            Domain(Domain),
            Connection(Connection),
            Score(Score)
        {
        }

		FEzDescribeNearRankingsIterator(
			const FEzDescribeNearRankingsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			Connection(From.Connection),
            Score(From.Score)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeNearRankingsIterator;

			Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator::FIterator DomainIterator;
			Gs2::UE5::Ranking::Model::FEzRankingPtr CurrentValue;
        	static Gs2::UE5::Ranking::Model::FEzRankingPtr ConvertCurrent(
        		Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Ranking::Model::FEzRanking::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Ranking::Domain::Iterator::FDescribeNearRankingsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeNearRankingsIterator& Iterable
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
            Gs2::UE5::Ranking::Model::FEzRankingPtr& Current()
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
	typedef TSharedPtr<FEzDescribeNearRankingsIterator> FEzDescribeNearRankingsIteratorPtr;
}
