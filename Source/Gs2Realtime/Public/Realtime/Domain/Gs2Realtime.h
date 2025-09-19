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

#include "Core/Domain/Gs2Core.h"
#include "Core/Domain/Model/IssueTransactionEvent.h"
#include "JobQueue/Gs2JobQueue.h"
#include "Realtime/Gs2Realtime.h"

// Model
#include "Realtime/Domain/Model/Namespace.h"
#include "Realtime/Domain/Model/Room.h"

// Iterator
#include "Realtime/Domain/Iterator/DescribeNamespacesIterator.h"
#include "Realtime/Domain/Iterator/DescribeRoomsIterator.h"

// Notification
#include "Realtime/Model/CreateNotification.h"

namespace Gs2::Core::Domain
{
    class FGs2;
    typedef TSharedPtr<FGs2> FGs2Ptr;
}

namespace Gs2::Realtime::Domain
{
    DECLARE_EVENT_OneParam(FGs2RealtimeDomain, FCreateNotificationEvent, Gs2::Realtime::Model::FCreateNotificationPtr);

    class GS2REALTIME_API FGs2RealtimeDomain:
        public TSharedFromThis<FGs2RealtimeDomain>
    {
        FCreateNotificationEvent CreateNotificationEvent;
        const Core::Domain::FGs2Ptr Gs2;
        const Gs2::Realtime::FGs2RealtimeRestClientPtr Client;

        public:
        TOptional<int64> Timestamp;
        TOptional<int64> GetTimestamp() const
        {
            return Timestamp;
        }
    private:

        FString ParentKey;

    public:

        FGs2RealtimeDomain(
            const Core::Domain::FGs2Ptr& Gs2
            // ReSharper disable once CppMemberInitializersOrder
        );

        FGs2RealtimeDomain(
            const FGs2RealtimeDomain& From
        );

        class GS2REALTIME_API FCreateNamespaceTask final :
            public Gs2::Core::Util::TGs2Future<Gs2::Realtime::Domain::Model::FNamespaceDomain>,
            public TSharedFromThis<FCreateNamespaceTask>
        {
            const TSharedPtr<FGs2RealtimeDomain> Self;
            const Request::FCreateNamespaceRequestPtr Request;
        public:
            explicit FCreateNamespaceTask(
                const TSharedPtr<FGs2RealtimeDomain>& Self,
                const Request::FCreateNamespaceRequestPtr Request
            );

            FCreateNamespaceTask(
                const FCreateNamespaceTask& From
            );

            virtual Gs2::Core::Model::FGs2ErrorPtr Action(
                TSharedPtr<TSharedPtr<Gs2::Realtime::Domain::Model::FNamespaceDomain>> Result
            ) override;
        };
        friend FCreateNamespaceTask;

        TSharedPtr<FAsyncTask<FCreateNamespaceTask>> CreateNamespace(
            Request::FCreateNamespaceRequestPtr Request
        );

        Gs2::Realtime::Domain::Iterator::FDescribeNamespacesIteratorPtr Namespaces(
            const TOptional<FString> NamePrefix = TOptional<FString>()
        ) const;

        Gs2::Core::Domain::CallbackID SubscribeNamespaces(
            TFunction<void()> Callback
        );

        void UnsubscribeNamespaces(
            Gs2::Core::Domain::CallbackID CallbackID
        );

        TSharedPtr<Gs2::Realtime::Domain::Model::FNamespaceDomain> Namespace(
            const FString NamespaceName
        );

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
        FCreateNotificationEvent& OnCreateNotification();

        void HandleNotification(
            const FString Action,
            const FString Payload
        );

        DECLARE_MULTICAST_DELEGATE_OneParam(FIssueTransactionDelegate, Gs2::Core::Domain::Model::FIssueTransactionEventPtr);
        FIssueTransactionDelegate OnIssueTransaction;
    };
    typedef TSharedPtr<FGs2RealtimeDomain> FGs2RealtimeDomainPtr;
}
