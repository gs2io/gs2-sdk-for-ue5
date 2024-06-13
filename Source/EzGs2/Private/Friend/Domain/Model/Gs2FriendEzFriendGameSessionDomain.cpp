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

#include "Friend/Domain/Model/Gs2FriendEzFriendGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzFriendGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFriendGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<bool> FEzFriendGameSessionDomain::WithProfile() const
    {
        return Domain->WithProfile;
    }

    FEzFriendGameSessionDomain::FEzFriendGameSessionDomain(
        Gs2::Friend::Domain::Model::FFriendAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzFriendGameSessionDomain::FDeleteFriendTask::FDeleteFriendTask(
        TSharedPtr<FEzFriendGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFriendGameSessionDomain::FDeleteFriendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->DeleteFriend(
                    MakeShared<Gs2::Friend::Request::FDeleteFriendRequest>()
                        ->WithTargetUserId(TargetUserId)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomain>(
                    Task->GetTask().Result(),
                    Self->GameSession,
                    Self->ConnectionValue
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

    TSharedPtr<FAsyncTask<FEzFriendGameSessionDomain::FDeleteFriendTask>> FEzFriendGameSessionDomain::DeleteFriend(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFriendTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomainPtr FEzFriendGameSessionDomain::FriendUser(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomain>(
            Domain->FriendUser(
                TargetUserId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
