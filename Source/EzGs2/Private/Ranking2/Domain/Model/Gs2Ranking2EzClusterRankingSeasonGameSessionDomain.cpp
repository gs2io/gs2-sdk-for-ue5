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

#include "Ranking2/Domain/Model/Gs2Ranking2EzClusterRankingSeasonGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzClusterRankingSeasonGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzClusterRankingSeasonGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzClusterRankingSeasonGameSessionDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<FString> FEzClusterRankingSeasonGameSessionDomain::ClusterName() const
    {
        return Domain->ClusterName;
    }

    TOptional<int64> FEzClusterRankingSeasonGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<FString> FEzClusterRankingSeasonGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzClusterRankingSeasonGameSessionDomain::FEzClusterRankingSeasonGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FClusterRankingSeasonAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzClusterRankingSeasonGameSessionDomain::FPutClusterRankingTask::FPutClusterRankingTask(
        TSharedPtr<FEzClusterRankingSeasonGameSessionDomain> Self,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzClusterRankingSeasonGameSessionDomain::FPutClusterRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PutClusterRankingScore(
                    MakeShared<Gs2::Ranking2::Request::FPutClusterRankingScoreRequest>()
                        ->WithScore(Score)
                        ->WithMetadata(Metadata)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
                );
                Task->EnsureCompletion();
                return nullptr;
            },
            nullptr
        );
        Future->StartSynchronousTask();
        if (Future->GetTask().IsError())
        {
            Future->EnsureCompletion();
            return Future->GetTask().Error();
        }
        Future->EnsureCompletion();
        return nullptr;
    }

    TSharedPtr<FAsyncTask<FEzClusterRankingSeasonGameSessionDomain::FPutClusterRankingTask>> FEzClusterRankingSeasonGameSessionDomain::PutClusterRanking(
        int64 Score,
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPutClusterRankingTask>>(
            this->AsShared(),
            Score,
            Metadata
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingsIteratorPtr FEzClusterRankingSeasonGameSessionDomain::ClusterRankings(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzClusterRankingSeasonGameSessionDomain::SubscribeClusterRankings(TFunction<void()> Callback)
    {
        return Domain->SubscribeClusterRankings(
            Callback
        );
    }

    void FEzClusterRankingSeasonGameSessionDomain::UnsubscribeClusterRankings(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeClusterRankings(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingDataGameSessionDomainPtr FEzClusterRankingSeasonGameSessionDomain::ClusterRankingData(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingDataGameSessionDomain>(
            Domain->ClusterRankingData(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingReceivedRewardsIteratorPtr FEzClusterRankingSeasonGameSessionDomain::ClusterRankingReceivedRewards(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingReceivedRewardsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzClusterRankingSeasonGameSessionDomain::SubscribeClusterRankingReceivedRewards(TFunction<void()> Callback)
    {
        return Domain->SubscribeClusterRankingReceivedRewards(
            Callback
        );
    }

    void FEzClusterRankingSeasonGameSessionDomain::UnsubscribeClusterRankingReceivedRewards(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeClusterRankingReceivedRewards(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomainPtr FEzClusterRankingSeasonGameSessionDomain::ClusterRankingReceivedReward(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomain>(
            Domain->ClusterRankingReceivedReward(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingScoresIteratorPtr FEzClusterRankingSeasonGameSessionDomain::ClusterRankingScores(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzClusterRankingSeasonGameSessionDomain::SubscribeClusterRankingScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeClusterRankingScores(
            Callback
        );
    }

    void FEzClusterRankingSeasonGameSessionDomain::UnsubscribeClusterRankingScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeClusterRankingScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomainPtr FEzClusterRankingSeasonGameSessionDomain::ClusterRankingScore(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>(
            Domain->ClusterRankingScore(
            ),
            GameSession,
            ConnectionValue
        );
    }
}
