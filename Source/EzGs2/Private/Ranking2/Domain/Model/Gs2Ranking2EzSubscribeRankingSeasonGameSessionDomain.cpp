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

#include "Ranking2/Domain/Model/Gs2Ranking2EzSubscribeRankingSeasonGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TOptional<FString> FEzSubscribeRankingSeasonGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzSubscribeRankingSeasonGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSubscribeRankingSeasonGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSubscribeRankingSeasonGameSessionDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<int64> FEzSubscribeRankingSeasonGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    FEzSubscribeRankingSeasonGameSessionDomain::FEzSubscribeRankingSeasonGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FSubscribeRankingSeasonAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzSubscribeRankingSeasonGameSessionDomain::FPutSubscribeRankingTask::FPutSubscribeRankingTask(
        TSharedPtr<FEzSubscribeRankingSeasonGameSessionDomain> Self,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSubscribeRankingSeasonGameSessionDomain::FPutSubscribeRankingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PutSubscribeRankingScore(
                    MakeShared<Gs2::Ranking2::Request::FPutSubscribeRankingScoreRequest>()
                        ->WithScore(Score)
                        ->WithMetadata(Metadata)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSubscribeRankingSeasonGameSessionDomain::FPutSubscribeRankingTask>> FEzSubscribeRankingSeasonGameSessionDomain::PutSubscribeRanking(
        int64 Score,
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPutSubscribeRankingTask>>(
            this->AsShared(),
            Score,
            Metadata
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingScoresIteratorPtr FEzSubscribeRankingSeasonGameSessionDomain::SubscribeRankingScores(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeRankingSeasonGameSessionDomain::SubscribeSubscribeRankingScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscribeRankingScores(
            Callback
        );
    }

    void FEzSubscribeRankingSeasonGameSessionDomain::UnsubscribeSubscribeRankingScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscribeRankingScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomainPtr FEzSubscribeRankingSeasonGameSessionDomain::SubscribeRankingScore(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingScoreGameSessionDomain>(
            Domain->SubscribeRankingScore(
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingsIteratorPtr FEzSubscribeRankingSeasonGameSessionDomain::SubscribeRankings(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Iterator::FEzDescribeSubscribeRankingsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzSubscribeRankingSeasonGameSessionDomain::SubscribeSubscribeRankings(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscribeRankings(
            Callback
        );
    }

    void FEzSubscribeRankingSeasonGameSessionDomain::UnsubscribeSubscribeRankings(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscribeRankings(
            CallbackId
        );
    }

    Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataGameSessionDomainPtr FEzSubscribeRankingSeasonGameSessionDomain::SubscribeRankingData(
        const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzSubscribeRankingDataGameSessionDomain>(
            Domain->SubscribeRankingData(
                ScorerUserId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
