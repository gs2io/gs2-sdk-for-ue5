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

#include "SerialKey/Domain/Model/Gs2SerialKeyEzSerialKeyGameSessionDomain.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    TOptional<FString> FEzSerialKeyGameSessionDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzSerialKeyGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSerialKeyGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSerialKeyGameSessionDomain::Code() const
    {
        return Domain->Code;
    }

    FEzSerialKeyGameSessionDomain::FEzSerialKeyGameSessionDomain(
        Gs2::SerialKey::Domain::Model::FSerialKeyAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSerialKeyGameSessionDomain::FUseSerialCodeTask::FUseSerialCodeTask(
        TSharedPtr<FEzSerialKeyGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSerialKeyGameSessionDomain::FUseSerialCodeTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FUseSerialCodeTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Use(
                    MakeShared<Gs2::SerialKey::Request::FUseRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSerialKeyGameSessionDomain::FUseSerialCodeTask>> FEzSerialKeyGameSessionDomain::UseSerialCode(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUseSerialCodeTask>>(
            this->AsShared()
        );
    }

    FEzSerialKeyGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSerialKeyGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSerialKeyGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::SerialKey::Model::FEzSerialKeyPtr> Result
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
                *Result = Gs2::UE5::SerialKey::Model::FEzSerialKey::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSerialKeyGameSessionDomain::FModelTask>> FEzSerialKeyGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
