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

#include "Mission/Domain/Model/Gs2MissionEzCompleteGameSessionDomain.h"

namespace Gs2::UE5::Mission::Domain::Model
{

    TOptional<FString> FEzCompleteGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzCompleteGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzCompleteGameSessionDomain::MissionGroupName() const
    {
        return Domain->MissionGroupName;
    }

    FEzCompleteGameSessionDomain::FEzCompleteGameSessionDomain(
        Gs2::Mission::Domain::Model::FCompleteAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzCompleteGameSessionDomain::FReceiveRewardsTask::FReceiveRewardsTask(
        TSharedPtr<FEzCompleteGameSessionDomain> Self,
        FString MissionTaskName
    ): Self(Self), MissionTaskName(MissionTaskName)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCompleteGameSessionDomain::FReceiveRewardsTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Complete(
                    MakeShared<Gs2::Mission::Request::FCompleteRequest>()
                        ->WithMissionTaskName(MissionTaskName)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzCompleteGameSessionDomain::FReceiveRewardsTask>> FEzCompleteGameSessionDomain::ReceiveRewards(
        FString MissionTaskName
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FReceiveRewardsTask>>(
            this->AsShared(),
            MissionTaskName
        );
    }

    FEzCompleteGameSessionDomain::FBatchReceiveRewardsTask::FBatchReceiveRewardsTask(
        TSharedPtr<FEzCompleteGameSessionDomain> Self,
        TArray<FString> MissionTaskNames
    ): Self(Self), MissionTaskNames(MissionTaskNames)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCompleteGameSessionDomain::FBatchReceiveRewardsTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Batch(
                    MakeShared<Gs2::Mission::Request::FBatchCompleteRequest>()
                        ->WithMissionTaskNames([&]{
                            auto Arr = MakeShared<TArray<FString>>();
                            for (auto Value : MissionTaskNames) {
                                Arr->Add(Value);
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
                *Result = MakeShared<Gs2::UE5::Mission::Domain::Model::FEzCompleteGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzCompleteGameSessionDomain::FBatchReceiveRewardsTask>> FEzCompleteGameSessionDomain::BatchReceiveRewards(
        TArray<FString> MissionTaskNames
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FBatchReceiveRewardsTask>>(
            this->AsShared(),
            MissionTaskNames
        );
    }

    FEzCompleteGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzCompleteGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzCompleteGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Mission::Model::FEzCompletePtr> Result
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
                *Result = Gs2::UE5::Mission::Model::FEzComplete::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzCompleteGameSessionDomain::FModelTask>> FEzCompleteGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzCompleteGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Mission::Model::FEzCompletePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Mission::Model::FCompletePtr Item)
            {
                Callback(Gs2::UE5::Mission::Model::FEzComplete::FromModel(Item));
            }
        );
    }

    void FEzCompleteGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
