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

#include "LoginReward/Domain/Model/Gs2LoginRewardEzBonusGameSessionDomain.h"

namespace Gs2::UE5::LoginReward::Domain::Model
{

    TOptional<FString> FEzBonusGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzBonusGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzBonusGameSessionDomain::FEzBonusGameSessionDomain(
        Gs2::LoginReward::Domain::Model::FBonusAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzBonusGameSessionDomain::FReceiveTask::FReceiveTask(
        TSharedPtr<FEzBonusGameSessionDomain> Self,
        FString BonusModelName,
        TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config
    ): Self(Self), BonusModelName(BonusModelName), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBonusGameSessionDomain::FReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Receive(
                    MakeShared<Gs2::LoginReward::Request::FReceiveRequest>()
                        ->WithBonusModelName(BonusModelName)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::LoginReward::Model::FConfig>>>();
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
                *Result = MakeShared<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzBonusGameSessionDomain::FReceiveTask>> FEzBonusGameSessionDomain::Receive(
        FString BonusModelName,
        TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveTask>>(
            this->AsShared(),
            BonusModelName,
            Config
        );
    }

    FEzBonusGameSessionDomain::FMissedReceiveTask::FMissedReceiveTask(
        TSharedPtr<FEzBonusGameSessionDomain> Self,
        FString BonusModelName,
        TOptional<int32> StepNumber,
        TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config
    ): Self(Self), BonusModelName(BonusModelName), StepNumber(StepNumber), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzBonusGameSessionDomain::FMissedReceiveTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->MissedReceive(
                    MakeShared<Gs2::LoginReward::Request::FMissedReceiveRequest>()
                        ->WithBonusModelName(BonusModelName)
                        ->WithStepNumber(StepNumber)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::LoginReward::Model::FConfig>>>();
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
                *Result = MakeShared<Gs2::UE5::LoginReward::Domain::Model::FEzBonusGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzBonusGameSessionDomain::FMissedReceiveTask>> FEzBonusGameSessionDomain::MissedReceive(
        FString BonusModelName,
        TOptional<int32> StepNumber,
        TOptional<TArray<TSharedPtr<Gs2::UE5::LoginReward::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FMissedReceiveTask>>(
            this->AsShared(),
            BonusModelName,
            StepNumber,
            Config
        );
    }
}
