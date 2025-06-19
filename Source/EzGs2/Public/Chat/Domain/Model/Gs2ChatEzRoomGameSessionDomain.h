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
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Model/Gs2ChatEzRoom.h"
#include "Chat/Model/Gs2ChatEzMessage.h"
#include "Chat/Model/Gs2ChatEzSubscribe.h"
#include "Chat/Model/Gs2ChatEzNotificationType.h"
#include "Gs2ChatEzMessageGameSessionDomain.h"
#include "Chat/Domain/Iterator/Gs2ChatEzDescribeMessagesIterator.h"
#include "Chat/Domain/Iterator/Gs2ChatEzDescribeLatestMessagesIterator.h"
#include "Gs2ChatEzRoomGameSessionDomain.h"
#include "Core/EzTransactionGameSessionDomain.h"
#include "Util/Net/GameSession.h"
#include "Util/Net/Gs2Connection.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    class EZGS2_API FEzRoomGameSessionDomain final :
        public TSharedFromThis<FEzRoomGameSessionDomain>
    {
        Gs2::Chat::Domain::Model::FRoomAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::IGameSessionPtr GameSession;
        Gs2::UE5::Util::FGs2ConnectionPtr ConnectionValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RoomName() const;
        TOptional<FString> Password() const;

        FEzRoomGameSessionDomain(
            Gs2::Chat::Domain::Model::FRoomAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::IGameSessionPtr GameSession,
            Gs2::UE5::Util::FGs2ConnectionPtr Connection
        );

        class EZGS2_API FDeleteRoomTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>,
            public TSharedFromThis<FDeleteRoomTask>
        {
            TSharedPtr<FEzRoomGameSessionDomain> Self;

        public:
            explicit FDeleteRoomTask(
                TSharedPtr<FEzRoomGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzRoomGameSessionDomain>> Result
            ) override;
        };
        friend FDeleteRoomTask;

        TSharedPtr<FAsyncTask<FDeleteRoomTask>> DeleteRoom(
        );

        class EZGS2_API FPostTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomain>,
            public TSharedFromThis<FPostTask>
        {
            TSharedPtr<FEzRoomGameSessionDomain> Self;
            FString Metadata;
            TOptional<int32> Category;

        public:
            explicit FPostTask(
                TSharedPtr<FEzRoomGameSessionDomain> Self,
                FString Metadata,
                TOptional<int32> Category = TOptional<int32>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomain>> Result
            ) override;
        };
        friend FPostTask;

        TSharedPtr<FAsyncTask<FPostTask>> Post(
            FString Metadata,
            TOptional<int32> Category = TOptional<int32>()
        );

        Gs2::UE5::Chat::Domain::Iterator::FEzDescribeMessagesIteratorPtr Messages(
            const TOptional<int32> Category = TOptional<int32>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeMessages(TFunction<void()> Callback);

        void UnsubscribeMessages(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Chat::Domain::Iterator::FEzDescribeLatestMessagesIteratorPtr LatestMessages(
            const TOptional<int32> Category = TOptional<int32>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeLatestMessages(TFunction<void()> Callback);

        void UnsubscribeLatestMessages(Gs2::Core::Domain::CallbackID CallbackId);

        Gs2::UE5::Chat::Domain::Model::FEzMessageGameSessionDomainPtr Message(
            const FString MessageName
        ) const;

        class EZGS2_API FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Model::FEzRoom>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzRoomGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzRoomGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Chat::Model::FEzRoomPtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Chat::Model::FEzRoomPtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzRoomGameSessionDomain> FEzRoomGameSessionDomainPtr;
}
