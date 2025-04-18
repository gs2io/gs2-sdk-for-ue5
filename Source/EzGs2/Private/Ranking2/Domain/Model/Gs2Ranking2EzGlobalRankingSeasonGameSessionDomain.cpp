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

#include "Ranking2/Domain/Model/Gs2Ranking2EzGlobalRankingSeasonGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzGlobalRankingSeasonGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzGlobalRankingSeasonGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzGlobalRankingSeasonGameSessionDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzGlobalRankingSeasonGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<FString> FEzGlobalRankingSeasonGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzGlobalRankingSeasonGameSessionDomain::FEzGlobalRankingSeasonGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FGlobalRankingSeasonAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzGlobalRankingSeasonGameSessionDomain::FPutGlobalRankingTask::FPutGlobalRankingTask(
        TSharedPtr<FEzGlobalRankingSeasonGameSessionDomain> Self,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzGlobalRankingSeasonGameSessionDomain::FPutGlobalRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PutGlobalRankingScore(
                    MakeShared<Gs2::Ranking2::Request::FPutGlobalRankingScoreRequest>()
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

    TSharedPtr<FAsyncTask<FEzGlobalRankingSeasonGameSessionDomain::FPutGlobalRankingTask>> FEzGlobalRankingSeasonGameSessionDomain::PutGlobalRanking(
        int64 Score,
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPutGlobalRankingTask>>(
            this->AsShared(),
            Score,
            Metadata
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingScoresIteratorPtr FEzGlobalRankingSeasonGameSessionDomain::GlobalRankingScores(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzGlobalRankingSeasonGameSessionDomain::SubscribeGlobalRankingScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeGlobalRankingScores(
            Callback
        );
    }

    void FEzGlobalRankingSeasonGameSessionDomain::UnsubscribeGlobalRankingScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeGlobalRankingScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomainPtr FEzGlobalRankingSeasonGameSessionDomain::GlobalRankingScore(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingScoreGameSessionDomain>(
            Domain->GlobalRankingScore(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingsIteratorPtr FEzGlobalRankingSeasonGameSessionDomain::GlobalRankings(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzGlobalRankingSeasonGameSessionDomain::SubscribeGlobalRankings(TFunction<void()> Callback)
    {
        return Domain->SubscribeGlobalRankings(
            Callback
        );
    }

    void FEzGlobalRankingSeasonGameSessionDomain::UnsubscribeGlobalRankings(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeGlobalRankings(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingDataGameSessionDomainPtr FEzGlobalRankingSeasonGameSessionDomain::GlobalRankingData(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingDataGameSessionDomain>(
            Domain->GlobalRankingData(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingReceivedRewardsIteratorPtr FEzGlobalRankingSeasonGameSessionDomain::GlobalRankingReceivedRewards(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeGlobalRankingReceivedRewardsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzGlobalRankingSeasonGameSessionDomain::SubscribeGlobalRankingReceivedRewards(TFunction<void()> Callback)
    {
        return Domain->SubscribeGlobalRankingReceivedRewards(
            Callback
        );
    }

    void FEzGlobalRankingSeasonGameSessionDomain::UnsubscribeGlobalRankingReceivedRewards(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeGlobalRankingReceivedRewards(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardGameSessionDomainPtr FEzGlobalRankingSeasonGameSessionDomain::GlobalRankingReceivedReward(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzGlobalRankingReceivedRewardGameSessionDomain>(
            Domain->GlobalRankingReceivedReward(
            ),
            GameSession,
            ConnectionValue
        );
    }
}
