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

// ReSharper disable CppUnusedIncludeDirective

#pragma once

#include "Core/Gs2Core.h"
#include "Core/Domain/Gs2Core.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Chat/Gs2Chat.h"

// Model
#include "Chat/Domain/Model/Namespace.h"
#include "Chat/Domain/Model/Room.h"
#include "Chat/Domain/Model/RoomAccessToken.h"
#include "Chat/Domain/Model/Message.h"
#include "Chat/Domain/Model/MessageAccessToken.h"
#include "Chat/Domain/Model/Subscribe.h"
#include "Chat/Domain/Model/SubscribeAccessToken.h"
#include "Chat/Domain/Model/User.h"
#include "Chat/Domain/Model/UserAccessToken.h"

// Iterator
#include "Chat/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Chat/Domain/Iterator/DescribeRoomsIterator.h"
#include "Chat/Domain/Iterator/DescribeMessagesIterator.h"
#include "Chat/Domain/Iterator/DescribeMessagesByUserIdIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesByUserIdIterator.h"
#include "Chat/Domain/Iterator/DescribeSubscribesByRoomNameIterator.h"

// Notification
#include "Chat/Model/PostNotification.h"

namespace Gs2::Chat::Domain
{
    DECLARE_EVENT_OneParam(FGs2ChatDomain, FPostNotificationEvent, Gs2::Chat::Model::FPostNotificationPtr);

    class GS2CHAT_API FGs2ChatDomain:
        public TSharedFromThis<FGs2ChatDomain>
    {
        FPostNotificationEvent PostNotificationEvent;
        Core::Domain::FCacheDatabasePtr Cache;
        Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain;
        Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration;
        Gs2::Core::Net::Rest::FGs2RestSessionPtr Session;
        Gs2::Chat::FGs2ChatRestClientPtr Client;

        public:
    private:

        FString ParentKey;

    public:

        FGs2ChatDomain(
            const Core::Domain::FCacheDatabasePtr Cache,
            const Gs2::Core::Domain::Model::FJobQueueDomainPtr JobQueueDomain,
            const Gs2::Core::Domain::Model::FStampSheetConfigurationPtr StampSheetConfiguration,
            const Gs2::Core::Net::Rest::FGs2RestSessionPtr Session
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2ChatDomain(
            const FGs2ChatDomain& From
        );

        class GS2CHAT_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Chat::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2ChatDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2ChatDomain> Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Chat::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Chat::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
        ) const;

        TSharedPtr<Gs2::Chat::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        ) const;

        void UpdateCacheFromStampSheet(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromStampTask(
            const FString Method,
            const FString Request,
            const FString Result
        );

        void UpdateCacheFromJobResult(
            const FString Method,
            const Gs2::JobQueue::Model::FJobPtr Job,
            const Gs2::JobQueue::Model::FJobResultBodyPtr Result
        );
        FPostNotificationEvent& OnPostNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );
    };
    typedef TSharedPtr<FGs2ChatDomain> FGs2ChatDomainPtr;
}
