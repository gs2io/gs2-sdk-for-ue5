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

#include "Account/Domain/Model/Gs2AccountEzNamespaceDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TOptional<FString> FEzNamespaceDomain::Status() const
    {
        return Domain->Status;
    }

    TOptional<FString> FEzNamespaceDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzNamespaceDomain::UploadToken() const
    {
        return Domain->UploadToken;
    }

    TOptional<FString> FEzNamespaceDomain::UploadUrl() const
    {
        return Domain->UploadUrl;
    }

    TOptional<FString> FEzNamespaceDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzNamespaceDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    FEzNamespaceDomain::FEzNamespaceDomain(
        Gs2::Account::Domain::Model::FNamespaceDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzNamespaceDomain::FCreateTask::FCreateTask(
        TSharedPtr<FEzNamespaceDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNamespaceDomain::FCreateTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CreateAccount(
                    MakeShared<Gs2::Account::Request::FCreateAccountRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>(
                    Task->GetTask().Result(),
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

    TSharedPtr<FAsyncTask<FEzNamespaceDomain::FCreateTask>> FEzNamespaceDomain::Create(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCreateTask>>(
            this->AsShared()
        );
    }

    FEzNamespaceDomain::FDoTakeOverTask::FDoTakeOverTask(
        TSharedPtr<FEzNamespaceDomain> Self,
        int32 Type,
        FString UserIdentifier,
        FString Password
    ): Self(Self), Type(Type), UserIdentifier(UserIdentifier), Password(Password)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzNamespaceDomain::FDoTakeOverTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->DoTakeOver(
                    MakeShared<Gs2::Account::Request::FDoTakeOverRequest>()
                        ->WithType(Type)
                        ->WithUserIdentifier(UserIdentifier)
                        ->WithPassword(Password)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>(
                    Task->GetTask().Result(),
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

    TSharedPtr<FAsyncTask<FEzNamespaceDomain::FDoTakeOverTask>> FEzNamespaceDomain::DoTakeOver(
        int32 Type,
        FString UserIdentifier,
        FString Password
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDoTakeOverTask>>(
            this->AsShared(),
            Type,
            UserIdentifier,
            Password
        );
    }

    Gs2::UE5::Account::Domain::Model::FEzAccountDomainPtr FEzNamespaceDomain::Account(
        const FString UserId
    ) const
    {
        return MakeShared<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>(
            Domain->Account(
                UserId
            ),
            ConnectionValue
        );
    }

    Gs2::UE5::Account::Domain::Model::FEzAccountGameSessionDomainPtr FEzNamespaceDomain::Me(
        Gs2::UE5::Util::FGameSessionPtr GameSession
    ) const
    {
        return MakeShared<Gs2::UE5::Account::Domain::Model::FEzAccountGameSessionDomain>(
            Domain->AccessToken(
                GameSession->AccessToken()->ToModel()
            ),
            GameSession,
            ConnectionValue
        );
    }
}
