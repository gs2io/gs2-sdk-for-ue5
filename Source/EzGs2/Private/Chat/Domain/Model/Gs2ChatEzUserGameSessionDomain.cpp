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

#include "Chat/Domain/Model/Gs2ChatEzUserGameSessionDomain.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    TOptional<FString> FEzUserGameSessionDomain::NextPageToken() const
    {
        return Domain->NextPageToken;
    }

    TOptional<FString> FEzUserGameSessionDomain::NamespaceName() const
    {
        return Domain->NamespaceName;
    }

    TOptional<FString> FEzUserGameSessionDomain::UserId() const
    {
        return Domain->UserId();
    }

    FEzUserGameSessionDomain::FEzUserGameSessionDomain(
        Gs2::Chat::Domain::Model::FUserAccessTokenDomainPtr Domain,
        Gs2::UE5::Util::IGameSessionPtr GameSession,
        Gs2::UE5::Util::FGs2ConnectionPtr Connection
    ):
        Domain(Domain),
        GameSession(GameSession),
        ConnectionValue(Connection)
    {

    }

    FEzUserGameSessionDomain::FCreateRoomTask::FCreateRoomTask(
        TSharedPtr<FEzUserGameSessionDomain> Self,
        TOptional<FString> Name,
        TOptional<FString> Metadata,
        TOptional<FString> Password,
        TOptional<TArray<FString>> WhiteListUserIds
    ): Self(Self), Name(Name), Metadata(Metadata), Password(Password), WhiteListUserIds(WhiteListUserIds)
    {

    }

    Gs2::Core::Model::FGs2ErrorPtr FEzUserGameSessionDomain::FCreateRoomTask::Action(
        TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>> Result
    )
    {
        const auto Future = Self->ConnectionValue->Run(
            [&]() -> Gs2::Core::Model::FGs2ErrorPtr {
                const auto Task = Self->Domain->CreateRoom(
                    MakeShared<Gs2::Chat::Request::FCreateRoomRequest>()
                        ->WithName(Name)
                        ->WithMetadata(Metadata)
                        ->WithPassword(Password)
                        ->WithWhiteListUserIds([&]{
                            auto Arr = MakeShared<TArray<FString>>();
                            if (!WhiteListUserIds.IsSet()) {
                                return Arr;
                            }
                            for (auto Value : *WhiteListUserIds) {
                                Arr->Add(Value);
                            }
                            return Arr;
                        }())
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

    TSharedPtr<FAsyncTask<FEzUserGameSessionDomain::FCreateRoomTask>> FEzUserGameSessionDomain::CreateRoom(
        TOptional<FString> Name,
        TOptional<FString> Metadata,
        TOptional<FString> Password,
        TOptional<TArray<FString>> WhiteListUserIds
    )
    {
        return Gs2::Core::Util::New<FAsyncTask<FCreateRoomTask>>(
            this->AsShared(),
            Name,
            Metadata,
            Password,
            WhiteListUserIds
        );
    }

    Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomainPtr FEzUserGameSessionDomain::Room(
        const FString RoomName,
        const TOptional<FString> Password
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>(
            Domain->Room(
                RoomName,
                Password
            ),
            GameSession,
            ConnectionValue
        );
    }

    Gs2::UE5::Chat::Domain::Iterator::FEzDescribeSubscribesIteratorPtr FEzUserGameSessionDomain::Subscribes(
          const TOptional<FString> RoomNamePrefix
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Iterator::FEzDescribeSubscribesIterator>(
            Domain,
            GameSession,
            ConnectionValue,
            RoomNamePrefix
        );
    }

    Gs2::Core::Domain::CallbackID FEzUserGameSessionDomain::SubscribeSubscribes(TFunction<void()> Callback)
    {
        return Domain->SubscribeSubscribes(
            Callback
        );
    }

    void FEzUserGameSessionDomain::UnsubscribeSubscribes(Gs2::Core::Domain::CallbackID CallbackId)
    {
        Domain->UnsubscribeSubscribes(
            CallbackId
        );
    }

    Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomainPtr FEzUserGameSessionDomain::Subscribe(
        const FString RoomName
    ) const
    {
        return MakeShared<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>(
            Domain->Subscribe(
                RoomName
            ),
            GameSession,
            ConnectionValue
        );
    }
}
