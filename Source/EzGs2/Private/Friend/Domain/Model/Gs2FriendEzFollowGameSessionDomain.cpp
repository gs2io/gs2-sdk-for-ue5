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

#include "Friend/Domain/Model/Gs2FriendEzFollowGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzFollowGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzFollowGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzFollowGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<bool> FEzFollowGameSessionDomain::WithProfile() const
    {
        return Domain->WithProfile;
    }

    FEzFollowGameSessionDomain::FEzFollowGameSessionDomain(
        Gs2::Friend::Domain::Model::FFollowAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzFollowGameSessionDomain::FFollowTask::FFollowTask(
        TSharedPtr<FEzFollowGameSessionDomain> Self,
        FString TargetUserId
    ): Self(Self), TargetUserId(TargetUserId)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzFollowGameSessionDomain::FFollowTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Follow(
                    MakeShared<Gs2::Friend::Request::FFollowRequest>()
                        ->WithTargetUserId(TargetUserId)
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

    TSharedPtr<FAsyncTask<FEzFollowGameSessionDomain::FFollowTask>> FEzFollowGameSessionDomain::Follow(
        FString TargetUserId
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FFollowTask>>(
            this->AsShared(),
            TargetUserId
        );
    }

    Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFollowsIteratorPtr FEzFollowGameSessionDomain::Follows(
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Iterator::FEzDescribeFollowsIterator>(
            Domain,
            GameSession,
            ConnectionValue
        );
    }

    Gs2::Core::Domain::CallbackID FEzFollowGameSessionDomain::SubscribeFollows(TFunction<void()> Callback)
    {
        return Domain->SubscribeFollows(
            Callback
        );
    }

    void FEzFollowGameSessionDomain::UnsubscribeFollows(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeFollows(
            CallbackId
        );
    }

    Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomainPtr FEzFollowGameSessionDomain::FollowUser(
        const FString TargetUserId
    ) const
    {
        return MakeShared<Gs2::UE5::Friend::Domain::Model::FEzFollowUserGameSessionDomain>(
            Domain->FollowUser(
                TargetUserId
            ),
            GameSession,
            ConnectionValue
        );
    }
}
