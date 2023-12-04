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

#include "SerialKey/Domain/Model/Gs2SerialKeyEzUserDomain.h"

namespace Gs2::UE5::SerialKey::Domain::Model
{

    TOptional<FString> FEzUserDomain::Url() const
    {
        return Domain->Url;
    }

    TOptional<FString> FEzUserDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    FEzUserDomain::FEzUserDomain(
        Gs2::SerialKey::Domain::Model::FUserDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ): Domain(Domain), ConnectionValue(Connection) {

    }

    FEzUserDomain::FModelTask::FModelTask(
        TSharedPtr<FEzUserDomain> Self,
        FString Code
    ): Self(Self), Code(Code)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserDomain::FModelTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::SerialKey::Model::FEzSerialKey>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->GetSerialKey(
                    MakeShared<Gs2::SerialKey::Request::FGetSerialKeyRequest>()
                        ->WithCode(Code)
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

    TSharedPtr<FAsyncTask<FEzUserDomain::FModelTask>> FEzUserDomain::Model(
        FString Code
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(
            this->AsShared(),
            Code
        );
    }

    Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyDomainPtr FEzUserDomain::SerialKey(
        const FString SerialKeyCode
    ) const
    {
        return MakeShared<Gs2::UE5::SerialKey::Domain::Model::FEzSerialKeyDomain>(
            Domain->SerialKey(
                SerialKeyCode
            ),
            ConnectionValue
        );
    }
}
