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

#include "Quest/Domain/Model/Gs2QuestEzProgressGameSessionDomain.h"

namespace Gs2::UE5::Quest::Domain::Model
{

    TOptional<FString> FEzProgressGameSessionDomain::TransactionId() const
    {
        return Domain->TransactionId;
    }

    TOptional<bool> FEzProgressGameSessionDomain::AutoRunStampSheet() const
    {
        return Domain->AutoRunStampSheet;
    }

    TOptional<FString> FEzProgressGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzProgressGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzProgressGameSessionDomain::FEzProgressGameSessionDomain(
        Gs2::Quest::Domain::Model::FProgressAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzProgressGameSessionDomain::FGetProgressTask::FGetProgressTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FGetProgressTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Model::FEzProgress>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetProgressTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Quest::Request::FGetProgressRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Quest::Model::FEzProgress::FromModel(
                    Task->GetTask().Result()
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

    TSharedPtr<FAsyncTask<FEzProgressGameSessionDomain::FGetProgressTask>> FEzProgressGameSessionDomain::GetProgress(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetProgressTask>>(
            this->AsShared()
        );
    }

    FEzProgressGameSessionDomain::FEndTask::FEndTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self,
        bool IsComplete,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config
    ): Self(Self), IsComplete_(IsComplete), Rewards(Rewards), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FEndTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FEndTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->End(
                    MakeShared<Gs2::Quest::Request::FEndRequest>()
                        ->WithRewards([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FReward>>>();
                            if (!Rewards.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Rewards) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithIsComplete(IsComplete_)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Quest::Model::FConfig>>>();
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
                *Result = MakeShared<Gs2::UE5::Quest::Domain::Model::FEzProgressGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->ProfileValue
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

    TSharedPtr<FAsyncTask<FEzProgressGameSessionDomain::FEndTask>> FEzProgressGameSessionDomain::End(
        bool IsComplete,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzReward>>> Rewards,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Quest::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FEndTask>>(
            this->AsShared(),
            IsComplete,
            Rewards,
            Config
        );
    }

    FEzProgressGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Quest::Model::FEzProgressPtr> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FModelTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Model();
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Quest::Model::FEzProgress::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzProgressGameSessionDomain::FModelTask>> FEzProgressGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
