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

#include "Friend/Domain/Model/Gs2FriendEzFriendUserDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzFriendUserDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFriendUserDomain::UserId() const
    {
        return Domain->UserId;
    }

    TOptional<bool> FEzFriendUserDomain::WithProfile() const
    {
        return Domain->WithProfile;
    }

    TOptional<FString> FEzFriendUserDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzFriendUserDomain::FEzFriendUserDomain(
        Gs2::Friend::Domain::Model::FFriendUserDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzFriendUserDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFriendUserDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFriendUserDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendUserPtr> Result
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
                *Result = Gs2::UE5::Friend::Model::FEzFriendUser::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzFriendUserDomain::FModelTask>> FEzFriendUserDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }
}
