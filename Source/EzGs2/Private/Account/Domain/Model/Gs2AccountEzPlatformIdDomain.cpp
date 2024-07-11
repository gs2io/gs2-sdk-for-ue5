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

#include "Account/Domain/Model/Gs2AccountEzPlatformIdDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TOptional<FString> FEzPlatformIdDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzPlatformIdDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<int32> FEzPlatformIdDomain::Type() const
    {
        return Domain->Type;
    }

    TOptional<FString> FEzPlatformIdDomain::UserIdentifier() const
    {
        return Domain->UserIdentifier;
    }

    FEzPlatformIdDomain::FEzPlatformIdDomain(
        Gs2::Account::Domain::Model::FPlatformIdDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzPlatformIdDomain::FModelTask::FModelTask(
        TSharedPtr<FEzPlatformIdDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzPlatformIdDomain::FModelTask::Action(
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

    TSharedPtr<FAsyncTask<FEzPlatformIdDomain::FModelTask>> FEzPlatformIdDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzPlatformIdDomain::Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzPlatformIdPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Account::Model::FPlatformIdPtr Item)
            {
                Callback(Gs2::UE5::Account::Model::FEzPlatformId::FromModel(Item));
            }
        );
    }

    void FEzPlatformIdDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
