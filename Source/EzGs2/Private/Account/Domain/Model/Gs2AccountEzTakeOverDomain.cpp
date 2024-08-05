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

#include "Account/Domain/Model/Gs2AccountEzTakeOverDomain.h"

namespace Gs2::UE5::Account::Domain::Model
{

    TOptional<FString> FEzTakeOverDomain::AuthorizationUrl() const
    {
        return Domain->AuthorizationUrl;
    }

    TOptional<FString> FEzTakeOverDomain::Payload() const
    {
        return Domain->Payload;
    }

    TOptional<FString> FEzTakeOverDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzTakeOverDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<int32> FEzTakeOverDomain::Type() const
    {
        return Domain->Type;
    }

    FEzTakeOverDomain::FEzTakeOverDomain(
        Gs2::Account::Domain::Model::FTakeOverDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzTakeOverDomain::FModelTask::FModelTask(
        TSharedPtr<FEzTakeOverDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzTakeOverDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Account::Model::FEzTakeOverPtr> Result
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

    TSharedPtr<FAsyncTask<FEzTakeOverDomain::FModelTask>> FEzTakeOverDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzTakeOverDomain::Subscribe(TFunction<void(Gs2::UE5::Account::Model::FEzTakeOverPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Account::Model::FTakeOverPtr Item)
            {
                Callback(Gs2::UE5::Account::Model::FEzTakeOver::FromModel(Item));
            }
        );
    }

    void FEzTakeOverDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
