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

#include "Ranking2/Domain/Model/Gs2Ranking2EzClusterRankingReceivedRewardGameSessionDomain.h"

namespace Gs2::UE5::Ranking2::Domain::Model
{

    TSharedPtr<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>> FEzClusterRankingReceivedRewardGameSessionDomain::AcquireActions() const
    {
        return [&]{
            auto Result = MakeShared<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzAcquireAction>>>();
            for (auto Value : *Domain->AcquireActions) {
                Result->Add(
                    Gs2::UE5::Ranking2::Model::FEzAcquireAction::FromModel(
                        Value
                    )
                );
            }
            return Result;
        }();
    }

    TOptional<FString> FEzClusterRankingReceivedRewardGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzClusterRankingReceivedRewardGameSessionDomain::RankingName() const
    {
        return Domain->RankingName;
    }

    TOptional<FString> FEzClusterRankingReceivedRewardGameSessionDomain::ClusterName() const
    {
        return Domain->ClusterName;
    }

    TOptional<int64> FEzClusterRankingReceivedRewardGameSessionDomain::Season() const
    {
        return Domain->Season;
    }

    TOptional<FString> FEzClusterRankingReceivedRewardGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzClusterRankingReceivedRewardGameSessionDomain::FEzClusterRankingReceivedRewardGameSessionDomain(
        Gs2::Ranking2::Domain::Model::FClusterRankingReceivedRewardAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzClusterRankingReceivedRewardGameSessionDomain::FReceiveClusterRankingRewardTask::FReceiveClusterRankingRewardTask(
        TSharedPtr<FEzClusterRankingReceivedRewardGameSessionDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzConfig>>> Config
    ): Self(Self), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzClusterRankingReceivedRewardGameSessionDomain::FReceiveClusterRankingRewardTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Receive(
                    MakeShared<Gs2::Ranking2::Request::FReceiveClusterRankingReceivedRewardRequest>()
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Ranking2::Model::FConfig>>>();
                            if (!Config.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Config) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Ranking2::Domain::Model::FEzClusterRankingReceivedRewardGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzClusterRankingReceivedRewardGameSessionDomain::FReceiveClusterRankingRewardTask>> FEzClusterRankingReceivedRewardGameSessionDomain::ReceiveClusterRankingReward(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Ranking2::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveClusterRankingRewardTask>>(
            this->AsShared(),
            Config
        );
    }

    FEzClusterRankingReceivedRewardGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzClusterRankingReceivedRewardGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzClusterRankingReceivedRewardGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedReward::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzClusterRankingReceivedRewardGameSessionDomain::FModelTask>> FEzClusterRankingReceivedRewardGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzClusterRankingReceivedRewardGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedRewardPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Ranking2::Model::FClusterRankingReceivedRewardPtr Item)
            {
                Callback(Gs2::UE5::Ranking2::Model::FEzClusterRankingReceivedReward::FromModel(Item));
            }
        );
    }

    void FEzClusterRankingReceivedRewardGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
