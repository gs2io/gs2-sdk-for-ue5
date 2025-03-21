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

#include "Inbox/Domain/Model/Gs2InboxEzMessageDomain.h"

namespace Gs2::UE5::Inbox::Domain::Model
{

    TOptional<FString> FEzMessageDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzMessageDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzMessageDomain::MessageName() const
    {
        return Domain->MessageName;
    }

    FEzMessageDomain::FEzMessageDomain(
        Gs2::Inbox::Domain::Model::FMessageDomainPtr Domain,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        ConnectionValue(Connection)
    {

    }

    FEzMessageDomain::FModelTask::FModelTask(
        TSharedPtr<FEzMessageDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzMessageDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Inbox::Model::FEzMessagePtr> Result
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
                *Result = Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzMessageDomain::FModelTask>> FEzMessageDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzMessageDomain::Subscribe(TFunction<void(Gs2::UE5::Inbox::Model::FEzMessagePtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Inbox::Model::FMessagePtr Item)
            {
                Callback(Gs2::UE5::Inbox::Model::FEzMessage::FromModel(Item));
            }
        );
    }

    void FEzMessageDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
