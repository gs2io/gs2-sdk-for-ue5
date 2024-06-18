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
#include "Matchmaking/Domain/Model/SeasonAccessToken.h"
#include "Matchmaking/Model/Gs2MatchmakingEzJoinedSeasonGathering.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Matchmaking::Domain::Iterator
{

	class EZGS2_API FEzDescribeJoinedSeasonGatheringsIterator :
        public TSharedFromThis<FEzDescribeJoinedSeasonGatheringsIterator>
    {
        Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIteratorPtr It;
        Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;

	public:

        explicit FEzDescribeJoinedSeasonGatheringsIterator(
            Gs2::Matchmaking::Domain::Model::FSeasonAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        ) :
            It(
                Domain->JoinedSeasonGatherings(
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection)
        {
        }

		FEzDescribeJoinedSeasonGatheringsIterator(
			const FEzDescribeJoinedSeasonGatheringsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeJoinedSeasonGatheringsIterator;

			Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIterator::FIterator DomainIterator;
			Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr CurrentValue;
        	static Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr ConvertCurrent(
        		Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGathering::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Matchmaking::Domain::Iterator::FDescribeJoinedSeasonGatheringsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeJoinedSeasonGatheringsIterator& Iterable
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
            Gs2::UE5::Matchmaking::Model::FEzJoinedSeasonGatheringPtr& Current()
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
	typedef TSharedPtr<FEzDescribeJoinedSeasonGatheringsIterator> FEzDescribeJoinedSeasonGatheringsIteratorPtr;
}
