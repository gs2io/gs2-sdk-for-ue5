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

#include "Ranking2/Domain/Model/Gs2Ranking2EzUserGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FPutGlobalRankingTask::FPutGlobalRankingTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString RankingName,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), RankingName(RankingName), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FPutGlobalRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PutGlobalRankingScore(
                    MakeShared<Gs2::Ranking2::Request::FPutGlobalRankingScoreRequest>()
                        ->WithRankingName(RankingName)
                        ->WithScore(Score)
                        ->WithMetadata(Metadata)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FPutGlobalRankingTask>> FEzUserGameSessionDomain::PutGlobalRanking(
        FString RankingName,
        int64 Score,
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPutGlobalRankingTask>>(
            this->AsShared(),
            RankingName,
            Score,
            Metadata
        );
    }

    FEzUserGameSessionDomain::FPutClusterRankingTask::FPutClusterRankingTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString RankingName,
        FString ClusterName,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), RankingName(RankingName), ClusterName(ClusterName), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FPutClusterRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PutClusterRankingScore(
                    MakeShared<Gs2::Ranking2::Request::FPutClusterRankingScoreRequest>()
                        ->WithRankingName(RankingName)
                        ->WithClusterName(ClusterName)
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FPutClusterRankingTask>> FEzUserGameSessionDomain::PutClusterRanking(
        FString RankingName,
        FString ClusterName,
        int64 Score,
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPutClusterRankingTask>>(
            this->AsShared(),
            RankingName,
            ClusterName,
            Score,
            Metadata
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingScoresIteratorPtr FEzUserGameSessionDomain::GlobalRankingScores(
          const TOptional<FString> RankingName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            RankingName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeGlobalRankingScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeGlobalRankingScores(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeGlobalRankingScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeGlobalRankingScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomainPtr FEzUserGameSessionDomain::GlobalRankingScore(
        const FString RankingName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>(
            Domain->GlobalRankingScore(
                RankingName,
                Season
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingSeasonGameSessionDomainPtr FEzUserGameSessionDomain::SubscribeRankingSeason(
        const FString RankingName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingSeasonGameSessionDomain>(
            Domain->SubscribeRankingSeason(
                RankingName,
                Season
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeGameSessionDomainPtr FEzUserGameSessionDomain::Subscribe(
        const FString RankingName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeGameSessionDomain>(
            Domain->Subscribe(
                RankingName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingReceivedRewardsIteratorPtr FEzUserGameSessionDomain::GlobalRankingReceivedRewards(
          const TOptional<FString> RankingName,
          const TOptional<int64> Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingReceivedRewardsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            RankingName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeGlobalRankingReceivedRewards(TFunction<void()> Callback)
    {
        return Domain->SubscribeGlobalRankingReceivedRewards(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeGlobalRankingReceivedRewards(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeGlobalRankingReceivedRewards(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardGameSessionDomainPtr FEzUserGameSessionDomain::GlobalRankingReceivedReward(
        const FString RankingName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardGameSessionDomain>(
            Domain->GlobalRankingReceivedReward(
                RankingName,
                Season
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingReceivedRewardsIteratorPtr FEzUserGameSessionDomain::ClusterRankingReceivedRewards(
          const TOptional<FString> RankingName,
          const TOptional<FString> ClusterName,
          const TOptional<int64> Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingReceivedRewardsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            RankingName,
            ClusterName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeClusterRankingReceivedRewards(TFunction<void()> Callback)
    {
        return Domain->SubscribeClusterRankingReceivedRewards(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeClusterRankingReceivedRewards(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeClusterRankingReceivedRewards(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomainPtr FEzUserGameSessionDomain::ClusterRankingReceivedReward(
        const FString RankingName,
        const FString ClusterName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomain>(
            Domain->ClusterRankingReceivedReward(
                RankingName,
                ClusterName,
                Season
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingScoresIteratorPtr FEzUserGameSessionDomain::ClusterRankingScores(
          const TOptional<FString> RankingName,
          const TOptional<FString> ClusterName,
          const TOptional<int64> Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeClusterRankingScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            RankingName,
            ClusterName,
            Season
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeClusterRankingScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeClusterRankingScores(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeClusterRankingScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeClusterRankingScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomainPtr FEzUserGameSessionDomain::ClusterRankingScore(
        const FString RankingName,
        const FString ClusterName,
        const int64 Season
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingScoreGameSessionDomain>(
            Domain->ClusterRankingScore(
                RankingName,
                ClusterName,
                Season
            ),
            GameSession,
            ConnectionValue
        );
    }
}
