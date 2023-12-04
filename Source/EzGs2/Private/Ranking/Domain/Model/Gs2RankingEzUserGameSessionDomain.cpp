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

#include "Ranking/Domain/Model/Gs2RankingEzUserGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<bool> FEzUserGameSessionDomain::Processing() const
    {
        return Domain->Processing;
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
        Gs2::Ranking::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FSubscribeTask::FSubscribeTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        FString CategoryName,
        FString TargetUserId
    ): Self(Self), CategoryName(CategoryName), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Subscribe(
                    MakeShared<Gs2::Ranking::Request::FSubscribeRequest>()
                        ->WithCategoryName(CategoryName)
                        ->WithTargetUserId(TargetUserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FSubscribeTask>> FEzUserGameSessionDomain::Subscribe(
        FString CategoryName,
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(
            this->AsShared(),
            CategoryName,
            TargetUserId
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeSubscribesByCategoryNameIteratorPtr FEzUserGameSessionDomain::SubscribeUsers(
          const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeSubscribesByCategoryNameIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            CategoryName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeSubscribeUsers(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscribeUsers(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeSubscribeUsers(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscribeUsers(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomainPtr FEzUserGameSessionDomain::SubscribeUser(
        const FString CategoryName,
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>(
            Domain->SubscribeUser(
                CategoryName,
                TargetUserId
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeRankingsIteratorPtr FEzUserGameSessionDomain::Rankings(
          const FString CategoryName,
          const TOptional<FString> AdditionalScopeName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeRankingsIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            CategoryName,
            AdditionalScopeName
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeRankings(TFunction<void()> Callback)
    {
        return Domain->SubscribeRankings(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeRankings(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeRankings(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomainPtr FEzUserGameSessionDomain::Ranking(
        const FString CategoryName
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomain>(
            Domain->Ranking(
                CategoryName
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeScoresIteratorPtr FEzUserGameSessionDomain::Scores(
          const FString CategoryName,
          const FString ScorerUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeScoresIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            CategoryName,
            ScorerUserId
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeScores(TFunction<void()> Callback)
    {
        return Domain->SubscribeScores(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeScores(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeScores(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomainPtr FEzUserGameSessionDomain::Score(
        const FString CategoryName,
        const FString ScorerUserId,
        const FString UniqueId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>(
            Domain->Score(
                CategoryName,
                ScorerUserId,
                UniqueId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
