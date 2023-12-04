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

#include "Ranking/Domain/Model/Gs2RankingEzRankingGameSessionDomain.h"

namespace Gs2::UE5::Ranking::Domain::Model
{

    TOptional<FString> FEzRankingGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRankingGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRankingGameSessionDomain::CategoryName() const
    {
        return Domain->CategoryName;
    }

    FEzRankingGameSessionDomain::FEzRankingGameSessionDomain(
        Gs2::Ranking::Domain::Model::FRankingAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzRankingGameSessionDomain::FPutScoreTask::FPutScoreTask(
        TSharedPtr<FEzRankingGameSessionDomain> Self,
        int64 Score,
        TOptional<FString> Metadata
    ): Self(Self), Score(Score), Metadata(Metadata)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRankingGameSessionDomain::FPutScoreTask::Action(
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

    TSharedPtr<FAsyncTask<FEzRankingGameSessionDomain::FPutScoreTask>> FEzRankingGameSessionDomain::PutScore(
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

    FEzRankingGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRankingGameSessionDomain> Self,
        FString ScorerUserId
    ): Self(Self), ScorerUserId(ScorerUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRankingGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking::Model::FEzRankingPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model(ScorerUserId);
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRankingGameSessionDomain::FModelTask>> FEzRankingGameSessionDomain::Model(
        FString ScorerUserId
    ) {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared(), ScorerUserId);
    }

    Gs2::Core::Domain::CallbackID FEzRankingGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking::Model::FEzRankingPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking::Model::FRankingPtr Item)
            {
                Callback(Gs2::UE5::Ranking::Model::FEzRanking::FromModel(Item));
            }
        );
    }

    void FEzRankingGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
