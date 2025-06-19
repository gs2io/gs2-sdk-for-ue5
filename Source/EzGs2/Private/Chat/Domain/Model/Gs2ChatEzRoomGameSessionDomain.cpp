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

#include "Chat/Domain/Model/Gs2ChatEzRoomGameSessionDomain.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    TOptional<FString> FEzRoomGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzRoomGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    TOptional<FString> FEzRoomGameSessionDomain::RoomName() const
    {
        return Domain->RoomName;
    }

    TOptional<FString> FEzRoomGameSessionDomain::Password() const
    {
        return Domain->Password;
    }

    FEzRoomGameSessionDomain::FEzRoomGameSessionDomain(
        Gs2::Chat::Domain::Model::FRoomAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzRoomGameSessionDomain::FDeleteRoomTask::FDeleteRoomTask(
        TSharedPtr<FEzRoomGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomGameSessionDomain::FDeleteRoomTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Delete(
                    MakeShared<Gs2::Chat::Request::FDeleteRoomRequest>()
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzRoomGameSessionDomain::FDeleteRoomTask>> FEzRoomGameSessionDomain::DeleteRoom(
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FDeleteRoomTask>>(
            this->AsShared()
        );
    }

    FEzRoomGameSessionDomain::FPostTask::FPostTask(
        TSharedPtr<FEzRoomGameSessionDomain> Self,
        FString Metadata,
        TOptional<int32> Category
    ): Self(Self), Metadata(Metadata), Category(Category)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomGameSessionDomain::FPostTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->Post(
                    MakeShared<Gs2::Chat::Request::FPostRequest>()
                        ->WithCategory(Category)
                        ->WithMetadata(Metadata)
                );
                Task->StartSynchronousTask();
                if (Task->GetTask().IsError())
                {
                    Task->EnsureCompletion();
                    return Task->GetTask().Error();
                }
                *Result = MakeShared<Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomain>(
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

    TSharedPtr<FAsyncTask<FEzRoomGameSessionDomain::FPostTask>> FEzRoomGameSessionDomain::Post(
        FString Metadata,
        TOptional<int32> Category
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FPostTask>>(
            this->AsShared(),
            Metadata,
            Category
        );
    }

    Gs2::UE5::Chat::Domain::Iterator::FEzDescribeMessagesIteratorPtr FEzRoomGameSessionDomain::Messages(
          const TOptional<int32> Category
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Iterator::FEzDescribeMessagesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            Password(),
            Category
        );
    }

    Gs2::Core::Domain::CallbackID FEzRoomGameSessionDomain::SubscribeMessages(TFunction<void()> Callback)
    {
        return Domain->SubscribeMessages(
            Callback
        );
    }

    void FEzRoomGameSessionDomain::UnsubscribeMessages(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeMessages(
            CallbackId
        );
    }

    Gs2::UE5::Chat::Domain::Iterator::FEzDescribeLatestMessagesIteratorPtr FEzRoomGameSessionDomain::LatestMessages(
          const TOptional<int32> Category
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Iterator::FEzDescribeLatestMessagesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            Password(),
            Category
        );
    }

    Gs2::Core::Domain::CallbackID FEzRoomGameSessionDomain::SubscribeLatestMessages(TFunction<void()> Callback)
    {
        return Domain->SubscribeLatestMessages(
            Callback
        );
    }

    void FEzRoomGameSessionDomain::UnsubscribeLatestMessages(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeLatestMessages(
            CallbackId
        );
    }

    Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomainPtr FEzRoomGameSessionDomain::Message(
        const FString MessageName
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomain>(
            Domain->Message(
                MessageName
            ),
            GameSession,
            ConnectionValue
        );
    }

    FEzRoomGameSessionDomain::FModelTask::FModelTask(
        TSharedPtr<FEzRoomGameSessionDomain> Self
    ): Self(Self)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzRoomGameSessionDomain::FModelTask::Action(
        TSharedPtr<Gs2::UE5::Chat::Model::FEzRoomPtr> Result
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
                *Result = Gs2::UE5::Chat::Model::FEzRoom::FromModel(Task->GetTask().Result());
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

    TSharedPtr<FAsyncTask<FEzRoomGameSessionDomain::FModelTask>> FEzRoomGameSessionDomain::Model() {
        return Gs2::Core::Util::New<FAsyncTask<FModelTask>>(this->AsShared());
    }

    Gs2::Core::Domain::CallbackID FEzRoomGameSessionDomain::Subscribe(TFunction<void(Gs2::UE5::Chat::Model::FEzRoomPtr)> Callback)
    {
        return Domain->Subscribe(
            [&](Gs2::Chat::Model::FRoomPtr Item)
            {
                Callback(Gs2::UE5::Chat::Model::FEzRoom::FromModel(Item));
            }
        );
    }

    void FEzRoomGameSessionDomain::Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->Unsubscribe(
            CallbackId
        );
    }
}
