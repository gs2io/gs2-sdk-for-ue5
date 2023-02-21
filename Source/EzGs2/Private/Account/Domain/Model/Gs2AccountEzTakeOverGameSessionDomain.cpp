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

#include "Account/Domain/Model/Gs2AccountEzTakeOverGameSessionDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TOptional<FString> FEzTakeOverGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzTakeOverGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<int32> FEzTakeOverGameSessionDomain::Type() const
    {
        return Domain->Type;
    }

    FEzTakeOverGameSessionDomain::FEzTakeOverGameSessionDomain(
        Gs2::Account::Domain::Model::FTakeOverAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzTakeOverGameSessionDomain::FAddTakeOverSettingTask::FAddTakeOverSettingTask(
        TSharedPtr<FEzTakeOverGameSessionDomain> Self,
        FString UserIdentifier,
        FString Password
    ): Self(Self), UserIdentifier(UserIdentifier), Password(Password)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTakeOverGameSessionDomain::FAddTakeOverSettingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FAddTakeOverSettingTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Create(
                    MakeShared<Gs2::Account::Request::FCreateTakeOverRequest>()
                        ->WithUserIdentifier(UserIdentifier)
                        ->WithPassword(Password)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzTakeOverGameSessionDomain::FAddTakeOverSettingTask>> FEzTakeOverGameSessionDomain::AddTakeOverSetting(
        FString UserIdentifier,
        FString Password
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAddTakeOverSettingTask>>(
            this->AsShared(),
            UserIdentifier,
            Password
        );
    }

    FEzTakeOverGameSessionDomain::FGetTask::FGetTask(
        TSharedPtr<FEzTakeOverGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTakeOverGameSessionDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Model::FEzTakeOver>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::Account::Request::FGetTakeOverRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::Account::Model::FEzTakeOver::FromModel(
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

    TSharedPtr<FAsyncTask<FEzTakeOverGameSessionDomain::FGetTask>> FEzTakeOverGameSessionDomain::Get(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(
            this->AsShared()
        );
    }

    FEzTakeOverGameSessionDomain::FUpdateTakeOverSettingTask::FUpdateTakeOverSettingTask(
        TSharedPtr<FEzTakeOverGameSessionDomain> Self,
        FString OldPassword,
        FString Password
    ): Self(Self), OldPassword(OldPassword), Password(Password)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTakeOverGameSessionDomain::FUpdateTakeOverSettingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FUpdateTakeOverSettingTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Update(
                    MakeShared<Gs2::Account::Request::FUpdateTakeOverRequest>()
                        ->WithOldPassword(OldPassword)
                        ->WithPassword(Password)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzTakeOverGameSessionDomain::FUpdateTakeOverSettingTask>> FEzTakeOverGameSessionDomain::UpdateTakeOverSetting(
        FString OldPassword,
        FString Password
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUpdateTakeOverSettingTask>>(
            this->AsShared(),
            OldPassword,
            Password
        );
    }

    FEzTakeOverGameSessionDomain::FDeleteTakeOverSettingTask::FDeleteTakeOverSettingTask(
        TSharedPtr<FEzTakeOverGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTakeOverGameSessionDomain::FDeleteTakeOverSettingTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FDeleteTakeOverSettingTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Account::Request::FDeleteTakeOverRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzTakeOverGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzTakeOverGameSessionDomain::FDeleteTakeOverSettingTask>> FEzTakeOverGameSessionDomain::DeleteTakeOverSetting(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteTakeOverSettingTask>>(
            this->AsShared()
        );
    }

    FEzTakeOverGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzTakeOverGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTakeOverGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Account::Model::FEzTakeOverPtr> Result
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
                *Result = Gs2::UE5::Account::Model::FEzTakeOver::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzTakeOverGameSessionDomain::FModelTask>> FEzTakeOverGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
