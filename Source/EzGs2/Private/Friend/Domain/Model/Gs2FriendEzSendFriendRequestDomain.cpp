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

#include "Friend/Domain/Model/Gs2FriendEzSendFriendRequestDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzSendFriendRequestDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSendFriendRequestDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzSendFriendRequestDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzSendFriendRequestDomain::FEzSendFriendRequestDomain(
        Gs2::Friend::Domain::Model::FSendFriendRequestDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSendFriendRequestDomain::FModelTask::FModelTask(
        TSharedPtr<FEzSendFriendRequestDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSendFriendRequestDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendRequestPtr> Result
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
                *Result = Gs2::UE5::Friend::Model::FEzFriendRequest::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzSendFriendRequestDomain::FModelTask>> FEzSendFriendRequestDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzSendFriendRequestDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFriendRequestPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FFriendRequestPtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzFriendRequest::FromModel(Item));
            }
        );
    }

    void FEzSendFriendRequestDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
