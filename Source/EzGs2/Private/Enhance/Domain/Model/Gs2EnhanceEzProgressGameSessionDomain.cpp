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

#include "Enhance/Domain/Model/Gs2EnhanceEzProgressGameSessionDomain.h"

namespace Gs2::UE5::Enhance::Domain::Model
{

    TOptional<int64> FEzProgressGameSessionDomain::AcquireExperience() const
    {
        return Domain->AcquireExperience;
    }

    TOptional<float> FEzProgressGameSessionDomain::BonusRate() const
    {
        return Domain->BonusRate;
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
        Gs2::Enhance::Domain::Model::FProgressAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzProgressGameSessionDomain::FStartTask::FStartTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self,
        FString RateName,
        FString TargetItemSetId,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>> Materials,
        TOptional<bool> Force,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config
    ): Self(Self), RateName(RateName), TargetItemSetId(TargetItemSetId), Materials(Materials), Force(Force), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FStartTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Start(
                    MakeShared<Gs2::Enhance::Request::FStartRequest>()
                        ->WithRateName(RateName)
                        ->WithTargetItemSetId(TargetItemSetId)
                        ->WithMaterials([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FMaterial>>>();
                            if (!Materials.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *Materials) {
                                Arr->Add(Value->ToModel());
                            }
                            return Arr;
                        }())
                        ->WithForce(Force)
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FConfig>>>();
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
                *Result = MakeShared<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzProgressGameSessionDomain::FStartTask>> FEzProgressGameSessionDomain::Start(
        FString RateName,
        FString TargetItemSetId,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzMaterial>>> Materials,
        TOptional<bool> Force,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FStartTask>>(
            this->AsShared(),
            RateName,
            TargetItemSetId,
            Materials,
            Force,
            Config
        );
    }

    FEzProgressGameSessionDomain::FEndTask::FEndTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self,
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config
    ): Self(Self), Config(Config)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FEndTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->End(
                    MakeShared<Gs2::Enhance::Request::FEndRequest>()
                        ->WithConfig([&]{
                            auto Arr = MakeShared<TArray<TSharedPtr<Gs2::Enhance::Model::FConfig>>>();
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
                *Result = MakeShared<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzProgressGameSessionDomain::FEndTask>> FEzProgressGameSessionDomain::End(
        TOptional<TArray<TSharedPtr<Gs2::UE5::Enhance::Model::FEzConfig>>> Config
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FEndTask>>(
            this->AsShared(),
            Config
        );
    }

    FEzProgressGameSessionDomain::FDeleteProgressTask::FDeleteProgressTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FDeleteProgressTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Enhance::Request::FDeleteProgressRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Enhance::Domain::Model::FEzProgressGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzProgressGameSessionDomain::FDeleteProgressTask>> FEzProgressGameSessionDomain::DeleteProgress(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteProgressTask>>(
            this->AsShared()
        );
    }

    FEzProgressGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzProgressGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzProgressGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Enhance::Model::FEzProgressPtr> Result
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
                *Result = Gs2::UE5::Enhance::Model::FEzProgress::FromModel(Task->GetTask().Result());
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

    Gs2::Core::Domain::CallbackID FEzProgressGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Enhance::Model::FEzProgressPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Enhance::Model::FProgressPtr Item)
            {
                Callback(Gs2::UE5::Enhance::Model::FEzProgress::FromModel(Item));
            }
        );
    }

    void FEzProgressGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
