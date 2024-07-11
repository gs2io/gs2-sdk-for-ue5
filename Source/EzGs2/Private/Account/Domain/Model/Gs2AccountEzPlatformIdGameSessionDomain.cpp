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

#include "Account/Domain/Model/Gs2AccountEzPlatformIdGameSessionDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TOptional<FString> FEzPlatformIdGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzPlatformIdGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<int32> FEzPlatformIdGameSessionDomain::Type() const
    {
        return Domain->Type;
    }

    TOptional<FString> FEzPlatformIdGameSessionDomain::UserIdentifier() const
    {
        return Domain->UserIdentifier;
    }

    FEzPlatformIdGameSessionDomain::FEzPlatformIdGameSessionDomain(
        Gs2::Account::Domain::Model::FPlatformIdAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzPlatformIdGameSessionDomain::FAddPlatformIdSettingTask::FAddPlatformIdSettingTask(
        TSharedPtr<FEzPlatformIdGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPlatformIdGameSessionDomain::FAddPlatformIdSettingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzPlatformIdGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Create(
                    MakeShared<Gs2::Account::Request::FCreatePlatformIdRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzPlatformIdGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzPlatformIdGameSessionDomain::FAddPlatformIdSettingTask>> FEzPlatformIdGameSessionDomain::AddPlatformIdSetting(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAddPlatformIdSettingTask>>(
            this->AsShared()
        );
    }

    FEzPlatformIdGameSessionDomain::FFindPlatformUserTask::FFindPlatformUserTask(
        TSharedPtr<FEzPlatformIdGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPlatformIdGameSessionDomain::FFindPlatformUserTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Model::FEzPlatformUser>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Find(
                    MakeShared<Gs2::Account::Request::FFindPlatformIdRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Account::Model::FEzPlatformUser::FromModel(
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

    TSharedPtr<FAsyncTask<FEzPlatformIdGameSessionDomain::FFindPlatformUserTask>> FEzPlatformIdGameSessionDomain::FindPlatformUser(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FFindPlatformUserTask>>(
            this->AsShared()
        );
    }

    FEzPlatformIdGameSessionDomain::FDeletePlatformIdSettingTask::FDeletePlatformIdSettingTask(
        TSharedPtr<FEzPlatformIdGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPlatformIdGameSessionDomain::FDeletePlatformIdSettingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzPlatformIdGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Account::Request::FDeletePlatformIdRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzPlatformIdGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzPlatformIdGameSessionDomain::FDeletePlatformIdSettingTask>> FEzPlatformIdGameSessionDomain::DeletePlatformIdSetting(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeletePlatformIdSettingTask>>(
            this->AsShared()
        );
    }

    FEzPlatformIdGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzPlatformIdGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPlatformIdGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Account::Model::FEzPlatformIdPtr> Result
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
                *Result = Gs2::UE5::Account::Model::FEzPlatformId::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzPlatformIdGameSessionDomain::FModelTask>> FEzPlatformIdGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzPlatformIdGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzPlatformIdPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Account::Model::FPlatformIdPtr Item)
            {
                Callback(Gs2::UE5::Account::Model::FEzPlatformId::FromModel(Item));
            }
        );
    }

    void FEzPlatformIdGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
