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

#include "Account/Domain/Model/Gs2AccountEzAccountDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TOptional<FString> FEzAccountDomain::Body() const
    {
        return Domain->Body;
    }

    TOptional<FString> FEzAccountDomain::Signature() const
    {
        return Domain->Signature;
    }

    TOptional<FString> FEzAccountDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzAccountDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzAccountDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzAccountDomain::FEzAccountDomain(
        Gs2::Account::Domain::Model::FAccountDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzAccountDomain::FAuthenticationTask::FAuthenticationTask(
        TSharedPtr<FEzAccountDomain> Self,
        FString KeyId,
        FString Password
    ): Self(Self), KeyId(KeyId), Password(Password)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAccountDomain::FAuthenticationTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Account::Domain::Model::FEzAccountDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FAuthenticationTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Authentication(
                    MakeShared<Gs2::Account::Request::FAuthenticationRequest>()
                        ->WithKeyId(KeyId)
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

    TSharedPtr<FAsyncTask<FEzAccountDomain::FAuthenticationTask>> FEzAccountDomain::Authentication(
        FString KeyId,
        FString Password
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAuthenticationTask>>(
            this->AsShared(),
            KeyId,
            Password
        );
    }

    Gs2::UE5::Account::Domain::Model::FEzTakeOverDomainPtr FEzAccountDomain::TakeOver(
        const int32 Type
    ) const
    {
        return MakeShared<Gs2::UE5::Account::Domain::Model::FEzTakeOverDomain>(
            Domain->TakeOver(
                Type
            ),
            ProfileValue
        );
    }

    FEzAccountDomain::FModelTask::FModelTask(
        TSharedPtr<FEzAccountDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzAccountDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Account::Model::FEzAccountPtr> Result
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
                *Result = Gs2::UE5::Account::Model::FEzAccount::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzAccountDomain::FModelTask>> FEzAccountDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
