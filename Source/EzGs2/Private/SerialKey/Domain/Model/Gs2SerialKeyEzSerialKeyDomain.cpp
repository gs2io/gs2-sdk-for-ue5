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

#include "SerialKey/Domain/Model/Gs2SerialKeyEzSerialKeyDomain.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    TOptional<FString> FEzSerialKeyDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzSerialKeyDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSerialKeyDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSerialKeyDomain::Code() const
    {
        return Domain->Code;
    }

    FEzSerialKeyDomain::FEzSerialKeyDomain(
        Gs2::SerialKey::Domain::Model::FSerialKeyDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSerialKeyDomain::FGetTask::FGetTask(
        TSharedPtr<FEzSerialKeyDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSerialKeyDomain::FGetTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Model::FEzSerialKey>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FGetTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Get(
                    MakeShared<Gs2::SerialKey::Request::FGetSerialKeyRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = Gs2::UE5::SerialKey::Model::FEzSerialKey::FromModel(
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

    TSharedPtr<FAsyncTask<FEzSerialKeyDomain::FGetTask>> FEzSerialKeyDomain::Get(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FGetTask>>(
            this->AsShared()
        );
    }

    FEzSerialKeyDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSerialKeyDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSerialKeyDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FEzSerialKeyDomain::FModelTask>> FEzSerialKeyDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
