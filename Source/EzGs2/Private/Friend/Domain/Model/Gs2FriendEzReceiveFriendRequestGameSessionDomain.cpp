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

#include "Friend/Domain/Model/Gs2FriendEzReceiveFriendRequestGameSessionDomain.h"

namespace Gs2::UE5::Friend::Domain::Model
{

    TOptional<FString> FEzReceiveFriendRequestGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzReceiveFriendRequestGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzReceiveFriendRequestGameSessionDomain::FromUserId() const
    {
        return Domain->FromUserId;
    }

    FEzReceiveFriendRequestGameSessionDomain::FEzReceiveFriendRequestGameSessionDomain(
        Gs2::Friend::Domain::Model::FReceiveFriendRequestAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::FGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzReceiveFriendRequestGameSessionDomain::FAcceptTask::FAcceptTask(
        TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzReceiveFriendRequestGameSessionDomain::FAcceptTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Accept(
                    MakeShared<Gs2::Friend::Request::FAcceptRequestRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzReceiveFriendRequestGameSessionDomain::FAcceptTask>> FEzReceiveFriendRequestGameSessionDomain::Accept(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FAcceptTask>>(
            this->AsShared()
        );
    }

    FEzReceiveFriendRequestGameSessionDomain::FRejectTask::FRejectTask(
        TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzReceiveFriendRequestGameSessionDomain::FRejectTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Reject(
                    MakeShared<Gs2::Friend::Request::FRejectRequestRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Friend::Domain::Model::FEzReceiveFriendRequestGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzReceiveFriendRequestGameSessionDomain::FRejectTask>> FEzReceiveFriendRequestGameSessionDomain::Reject(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FRejectTask>>(
            this->AsShared()
        );
    }

    FEzReceiveFriendRequestGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzReceiveFriendRequestGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzReceiveFriendRequestGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Friend::Model::FEzFriendRequestPtr> Result
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

    TSharedPtr<FAsyncTask<FEzReceiveFriendRequestGameSessionDomain::FModelTask>> FEzReceiveFriendRequestGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzReceiveFriendRequestGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Friend::Model::FEzFriendRequestPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Friend::Model::FFriendRequestPtr Item)
            {
                Callback(Gs2::UE5::Friend::Model::FEzFriendRequest::FromModel(Item));
            }
        );
    }

    void FEzReceiveFriendRequestGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
