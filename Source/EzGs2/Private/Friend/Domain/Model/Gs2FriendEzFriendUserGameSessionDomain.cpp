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

#include "Friend/Domain/Model/Gs2FriendEzFriendUserGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzFriendUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFriendUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<bool> FEzFriendUserGameSessionDomain::WithProfile() const
    {
        return Domain->WithProfile;
    }

    TOptional<FString> FEzFriendUserGameSessionDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzFriendUserGameSessionDomain::FEzFriendUserGameSessionDomain(
        Gs2::Friend::Domain::Model::FFriendUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzFriendUserGameSessionDomain::FDeleteFriendTask::FDeleteFriendTask(
        TSharedPtr<FEzFriendUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFriendUserGameSessionDomain::FDeleteFriendTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFriendUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Friend::Request::FDeleteFriendRequest>()
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

    TSharedPtr<FAsyncTask<FEzFriendUserGameSessionDomain::FDeleteFriendTask>> FEzFriendUserGameSessionDomain::DeleteFriend(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteFriendTask>>(
            this->AsShared()
        );
    }

    FEzFriendUserGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFriendUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFriendUserGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendUserPtr> Result
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

    TSharedPtr<FAsyncTask<FEzFriendUserGameSessionDomain::FModelTask>> FEzFriendUserGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzFriendUserGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFriendUserPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FFriendUserPtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzFriendUser::FromModel(Item));
            }
        );
    }

    void FEzFriendUserGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
