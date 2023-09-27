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

#include "Friend/Domain/Model/Gs2FriendEzFollowUserDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzFollowUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFollowUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<FString> FEzFollowUserDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzFollowUserDomain::FEzFollowUserDomain(
        Gs2::Friend::Domain::Model::FFollowUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzFollowUserDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFollowUserDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFollowUserDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzFollowUserPtr> Result
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
                *Result = Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzFollowUserDomain::FModelTask>> FEzFollowUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzFollowUserDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFollowUserPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FFollowUserPtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(Item));
            }
        );
    }

    void FEzFollowUserDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
