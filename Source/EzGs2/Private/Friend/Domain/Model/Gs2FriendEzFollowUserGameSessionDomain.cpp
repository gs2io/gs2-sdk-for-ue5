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

#include "Friend/Domain/Model/Gs2FriendEzFollowUserGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzFollowUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFollowUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<bool> FEzFollowUserGameSessionDomain::WithProfile() const
    {
        return Domain->WithProfile;
    }

    TOptional<FString> FEzFollowUserGameSessionDomain::TargetUserId() const
    {
        return Domain->TargetUserId;
    }

    FEzFollowUserGameSessionDomain::FEzFollowUserGameSessionDomain(
        Gs2::Friend::Domain::Model::FFollowUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzFollowUserGameSessionDomain::FUnfollowTask::FUnfollowTask(
        TSharedPtr<FEzFollowUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFollowUserGameSessionDomain::FUnfollowTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Unfollow(
                    MakeShared<Gs2::Friend::Request::FUnfollowRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzFollowUserGameSessionDomain::FUnfollowTask>> FEzFollowUserGameSessionDomain::Unfollow(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FUnfollowTask>>(
            this->AsShared()
        );
    }

    FEzFollowUserGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzFollowUserGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFollowUserGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzFollowUserPtr> Result
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

    TSharedPtr<FAsyncTask<FEzFollowUserGameSessionDomain::FModelTask>> FEzFollowUserGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzFollowUserGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFollowUserPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FFollowUserPtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzFollowUser::FromModel(Item));
            }
        );
    }

    void FEzFollowUserGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
