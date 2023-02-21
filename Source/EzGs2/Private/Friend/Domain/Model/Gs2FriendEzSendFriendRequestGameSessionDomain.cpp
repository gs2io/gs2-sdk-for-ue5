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

#include "Friend/Domain/Model/Gs2FriendEzSendFriendRequestGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzSendFriendRequestGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzSendFriendRequestGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzSendFriendRequestGameSessionDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzSendFriendRequestGameSessionDomain::FEzSendFriendRequestGameSessionDomain(
        Gs2::Friend::Domain::Model::FSendFriendRequestAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FProfilePtr Profile
    ): Domain(Domain), ProfileValue(Profile) {

    }

    FEzSendFriendRequestGameSessionDomain::FDeleteRequestTask::FDeleteRequestTask(
        TSharedPtr<FEzSendFriendRequestGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzSendFriendRequestGameSessionDomain::FDeleteRequestTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ProfileValue->Run<FDeleteRequestTask>(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Friend::Request::FDeleteRequestRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzSendFriendRequestGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzSendFriendRequestGameSessionDomain::FDeleteRequestTask>> FEzSendFriendRequestGameSessionDomain::DeleteRequest(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteRequestTask>>(
            this->AsShared()
        );
    }
}
