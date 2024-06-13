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

#include "Ranking/Domain/Model/Gs2RankingEzRankingCategoryGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzRankingCategoryGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<bool> FEzRankingCategoryGameSessionDomain::Processing() const
    {
        return Domain->Processing;
    }

    TOptional<FString> FEzRankingCategoryGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRankingCategoryGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRankingCategoryGameSessionDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    TOptional<FString> FEzRankingCategoryGameSessionDomain::AdditionalScopeName() const
    {
        return Domain->AdditionalScopeName;
    }

    FEzRankingCategoryGameSessionDomain::FEzRankingCategoryGameSessionDomain(
        Gs2::Ranking::Domain::Model::FRankingCategoryAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzRankingCategoryGameSessionDomain::FSubscribeTask::FSubscribeTask(
        TSharedPtr<FEzRankingCategoryGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRankingCategoryGameSessionDomain::FSubscribeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Subscribe(
                    MakeShared<Gs2::Ranking::Request::FSubscribeRequest>()
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

    TSharedPtr<FAsyncTask<FEzRankingCategoryGameSessionDomain::FSubscribeTask>> FEzRankingCategoryGameSessionDomain::Subscribe(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FSubscribeTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    FEzRankingCategoryGameSessionDomain::FPutScoreTask::FPutScoreTask(
        TSharedPtr<FEzRankingCategoryGameSessionDomain> Self,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRankingCategoryGameSessionDomain::FPutScoreTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->PutScore(
                    MakeShared<Gs2::Ranking::Request::FPutScoreRequest>()
                        ->WithScore(Score)
                        ->WithMetadata(Metadata)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzScoreGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzRankingCategoryGameSessionDomain::FPutScoreTask>> FEzRankingCategoryGameSessionDomain::PutScore(
        int64 Score,
        TOptional<FString> Metadata
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPutScoreTask>>(
            this->AsShared(),
            Score,
            Metadata
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeSubscribesByCategoryNameIteratorPtr FEzRankingCategoryGameSessionDomain::SubscribeUsers(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeSubscribesByCategoryNameIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzRankingCategoryGameSessionDomain::SubscribeSubscribeUsers(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscribeUsers(
            Callback
        );
    }

    void FEzRankingCategoryGameSessionDomain::UnsubscribeSubscribeUsers(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscribeUsers(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomainPtr FEzRankingCategoryGameSessionDomain::SubscribeUser(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzSubscribeUserGameSessionDomain>(
            Domain->SubscribeUser(
                TargetUserId
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeRankingsIteratorPtr FEzRankingCategoryGameSessionDomain::Rankings(
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Iterator::FEzDescribeRankingsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzRankingCategoryGameSessionDomain::SubscribeRankings(TFunction<void()> Callback)
    {
        return Domain->SubscribeRankings(
            Callback
        );
    }

    void FEzRankingCategoryGameSessionDomain::UnsubscribeRankings(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeRankings(
            CallbackId
        );
    }

    Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomainPtr FEzRankingCategoryGameSessionDomain::Ranking(
        const TOptional<FString> ScorerUserId,
        const TOptional<int64> Index
    ) const
    {
        return MakeShared<Gs2::UE5::Ranking::Domain::Model::FEzRankingGameSessionDomain>(
            Domain->Ranking(
                ScorerUserId,
                Index
            ),
            GameSession,
            ConnectionValue
        );
    }
}
