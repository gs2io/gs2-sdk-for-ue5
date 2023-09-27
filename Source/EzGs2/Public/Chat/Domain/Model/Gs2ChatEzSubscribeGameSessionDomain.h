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
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Model/Gs2ChatEzRoom.h"
#include "Chat/Model/Gs2ChatEzMessage.h"
#include "Chat/Model/Gs2ChatEzSubscribe.h"
#include "Chat/Model/Gs2ChatEzNotificationType.h"
#include "Gs2ChatEzSubscribeGameSessionDomain.h"
#include "Chat/Domain/Iterator/Gs2ChatEzDescribeSubscribesIterator.h"
#include "Auth/Model/Gs2AuthEzAccessToken.h"
#include "Util/Profile.h"

namespace Gs2::UE5::Chat::Domain::Model
{

    class EZGS2_API FEzSubscribeGameSessionDomain final :
        public TSharedFromThis<FEzSubscribeGameSessionDomain>
    {
        Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomainPtr Domain;
        Gs2::UE5::Util::FProfilePtr ProfileValue;

        public:
        TOptional<FString> NamespaceName() const;
        TOptional<FString> UserId() const;
        TOptional<FString> RoomName() const;

        FEzSubscribeGameSessionDomain(
            Gs2::Chat::Domain::Model::FSubscribeAccessTokenDomainPtr Domain,
            Gs2::UE5::Util::FProfilePtr Profile
        );

        class FSubscribeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>,
            public TSharedFromThis<FSubscribeTask>
        {
            TSharedPtr<FEzSubscribeGameSessionDomain> Self;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes;

        public:
            explicit FSubscribeTask(
                TSharedPtr<FEzSubscribeGameSessionDomain> Self,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes = TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>> Result
            ) override;
        };
        friend FSubscribeTask;

        TSharedPtr<FAsyncTask<FSubscribeTask>> Subscribe(
            TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes = TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>>()
        );

        class FUpdateSubscribeSettingTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>,
            public TSharedFromThis<FUpdateSubscribeSettingTask>
        {
            TSharedPtr<FEzSubscribeGameSessionDomain> Self;
            TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes;

        public:
            explicit FUpdateSubscribeSettingTask(
                TSharedPtr<FEzSubscribeGameSessionDomain> Self,
                TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes = TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>>()
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>> Result
            ) override;
        };
        friend FUpdateSubscribeSettingTask;

        TSharedPtr<FAsyncTask<FUpdateSubscribeSettingTask>> UpdateSubscribeSetting(
            TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>> NotificationTypes = TOptional<TArray<TSharedPtr<Gs2::UE5::Chat::Model::FEzNotificationType>>>()
        );

        class FUnsubscribeTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>,
            public TSharedFromThis<FUnsubscribeTask>
        {
            TSharedPtr<FEzSubscribeGameSessionDomain> Self;

        public:
            explicit FUnsubscribeTask(
                TSharedPtr<FEzSubscribeGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::UE5::Chat::Domain::Model::FEzSubscribeGameSessionDomain>> Result
            ) override;
        };
        friend FUnsubscribeTask;

        TSharedPtr<FAsyncTask<FUnsubscribeTask>> Unsubscribe(
        );

        class FModelTask :
            public Gs2::Core::Util::TGs2Future<Gs2::UE5::Chat::Model::FEzSubscribe>,
            public TSharedFromThis<FModelTask>
        {
            TSharedPtr<FEzSubscribeGameSessionDomain> Self;

        public:
            explicit FModelTask(
                TSharedPtr<FEzSubscribeGameSessionDomain> Self
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<Gs2::UE5::Chat::Model::FEzSubscribePtr> Result
            ) override;
        };

        TSharedPtr<FAsyncTask<FModelTask>> Model();

        Gs2::Core::Domain::CallbackID Subscribe(TFunction<void(Gs2::UE5::Chat::Model::FEzSubscribePtr)> Callback);

        void Unsubscribe(Gs2::Core::Domain::CallbackID CallbackId);

    };
    typedef TSharedPtr<FEzSubscribeGameSessionDomain> FEzSubscribeGameSessionDomainPtr;
}
