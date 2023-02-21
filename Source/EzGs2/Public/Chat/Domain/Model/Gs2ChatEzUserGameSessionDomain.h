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

#pragma once

#include "CoreMinimal.h"
#include "Chat/Domain/Model/UserAccessToken.h"
#include "Chat/Model/Gs2ChatEzRoom.h"
#include "Chat/Model/Gs2ChatEzMessage.h"
#include "Chat/Model/Gs2ChatEzSubscribe.h"
#include "Chat/Model/Gs2ChatEzNotificationType.h"
#include "Gs2ChatEzRoomGameSessionDomain.h"
#include "Gs2ChatEzSubscribeGameSessionDomain.h"
#include "Chat/Domain/Iterator/Gs2ChatEzDescribeSubscribesIterator.h"
#include "Gs2ChatEzUserGameSessionDomain.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    class EZGS2_API FEzUserGameSessionDomain final :
        public TSharedFromThis<FEzUserGameSessionDomain>
    {
        Gs2::Chat::Domain::Model::FUserAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NextPageToken() const;
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;

        FEzUserGameSessionDomain(
            Gs2::Chat::Domain::Model::FUserAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FCreateRoomTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>,
            public TSharedFromThis<FCreateRoomTask>
        {
            TSharedPtr<FEzUserGameSessionDomain> Self;
            TOptional<FString> Name;
            TOptional<FString> Metadata;
            TOptional<FString> Password;
            TOptional<TArray<FString>> WhiteListUserIds;

        public:
            explicit FCreateRoomTask(
                TSharedPtr<FEzUserGameSessionDomain> Self,
                TOptional<FString> Name = TOptional<FString>(),
                TOptional<FString> Metadata = TOptional<FString>(),
                TOptional<FString> Password = TOptional<FString>(),
                TOptional<TArray<FString>> WhiteListUserIds = TOptional<TArray<FString>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>> Result
            ) override;
        };
        friend FCreateRoomTask;

        TSharedPtr<FAsyncTask<FCreateRoomTask>> CreateRoom(
            TOptional<FString> Name = TOptional<FString>(),
            TOptional<FString> Metadata = TOptional<FString>(),
            TOptional<FString> Password = TOptional<FString>(),
            TOptional<TArray<FString>> WhiteListUserIds = TOptional<TArray<FString>>()
        );

        Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomainPtr Room(
            const FString RoomName,
            const TOptional<FString> Password = TOptional<FString>()
        ) const;

        Gs2::UE5::Chat::Domain::Iterator::FEzDescribeSubscribesIteratorPtr Subscribes(
        ) const;

        Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomainPtr Subscribe(
            const FString RoomName
        ) const;

    };
    typedef TSharedPtr<FEzUserGameSessionDomain> FEzUserGameSessionDomainPtr;
}
