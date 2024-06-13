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
#include "Ranking2/Domain/Model/UserAccessToken.h"
#include "Ranking2/Model/Gs2Ranking2EzClusterRankingReceivedReward.h"
#include "Util/Net/GameSession.h"

namespace Gs2::UE5::Ranking2::Domain::Iterator
{

	class EZGS2_API FEzDescribeClusterRankingReceivedRewardsIterator :
        public TSharedFromThis<FEzDescribeClusterRankingReceivedRewardsIterator>
    {
        Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIteratorPtr It;
        Gs2::Ranking2::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr Connection;
        TOptional<FString> RankingName;
        TOptional<FString> ClusterName;
        TOptional<int64> Season;

	public:

        explicit FEzDescribeClusterRankingReceivedRewardsIterator(
            Gs2::Ranking2::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection,
            TOptional<FString> RankingName = TOptional<FString>(),
            TOptional<FString> ClusterName = TOptional<FString>(),
            TOptional<int64> Season = TOptional<int64>()
        ) :
            It(
                Domain->ClusterRankingReceivedRewards(
                    RankingName,
                    ClusterName,
                    Season
                )
            ),
            Domain(Domain),
            GameSession(GameSession),
            Connection(Connection),
            RankingName(RankingName),
            ClusterName(ClusterName),
            Season(Season)
        {
        }

		FEzDescribeClusterRankingReceivedRewardsIterator(
			const FEzDescribeClusterRankingReceivedRewardsIterator& From
		) :
			It(From.It),
			Domain(From.Domain),
			GameSession(From.GameSession),
			Connection(From.Connection),
            RankingName(From.RankingName),
            ClusterName(From.ClusterName),
            Season(From.Season)
		{
		}

		class EZGS2_API FIterator
		{
		    friend class FEzDescribeClusterRankingReceivedRewardsIterator;

			Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIterator::FIterator DomainIterator;
			Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr CurrentValue;
        	static Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr ConvertCurrent(
        		Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIterator::FIterator& DomainIterator
        	)
        	{
				return DomainIterator.IsCurrentValid()
	    			? Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedReward::FromModel(DomainIterator.Current())
					: nullptr;
        	}

			explicit FIterator(
				Gs2::Ranking2::Domain::Iterator::FDescribeClusterRankingReceivedRewardsIterator::FIterator&& DomainIterator
			) :
			    DomainIterator(DomainIterator),
			    CurrentValue(ConvertCurrent(DomainIterator))
			{}

		public:
			explicit FIterator(
				FEzDescribeClusterRankingReceivedRewardsIterator& Iterable
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
            Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr& Current()
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
	typedef TSharedPtr<FEzDescribeClusterRankingReceivedRewardsIterator> FEzDescribeClusterRankingReceivedRewardsIteratorPtr;
}
