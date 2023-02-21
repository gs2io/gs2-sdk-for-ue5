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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Request/DescribeRoomsRequest.h"
#include "Task/Rest/DescribeRoomsTask.h"
#include "Request/CreateRoomRequest.h"
#include "Task/Rest/CreateRoomTask.h"
#include "Request/CreateRoomFromBackendRequest.h"
#include "Task/Rest/CreateRoomFromBackendTask.h"
#include "Request/GetRoomRequest.h"
#include "Task/Rest/GetRoomTask.h"
#include "Request/UpdateRoomRequest.h"
#include "Task/Rest/UpdateRoomTask.h"
#include "Request/UpdateRoomFromBackendRequest.h"
#include "Task/Rest/UpdateRoomFromBackendTask.h"
#include "Request/DeleteRoomRequest.h"
#include "Task/Rest/DeleteRoomTask.h"
#include "Request/DeleteRoomFromBackendRequest.h"
#include "Task/Rest/DeleteRoomFromBackendTask.h"
#include "Request/DescribeMessagesRequest.h"
#include "Task/Rest/DescribeMessagesTask.h"
#include "Request/DescribeMessagesByUserIdRequest.h"
#include "Task/Rest/DescribeMessagesByUserIdTask.h"
#include "Request/PostRequest.h"
#include "Task/Rest/PostTask.h"
#include "Request/PostByUserIdRequest.h"
#include "Task/Rest/PostByUserIdTask.h"
#include "Request/GetMessageRequest.h"
#include "Task/Rest/GetMessageTask.h"
#include "Request/GetMessageByUserIdRequest.h"
#include "Task/Rest/GetMessageByUserIdTask.h"
#include "Request/DeleteMessageRequest.h"
#include "Task/Rest/DeleteMessageTask.h"
#include "Request/DescribeSubscribesRequest.h"
#include "Task/Rest/DescribeSubscribesTask.h"
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Task/Rest/DescribeSubscribesByUserIdTask.h"
#include "Request/DescribeSubscribesByRoomNameRequest.h"
#include "Task/Rest/DescribeSubscribesByRoomNameTask.h"
#include "Request/SubscribeRequest.h"
#include "Task/Rest/SubscribeTask.h"
#include "Request/SubscribeByUserIdRequest.h"
#include "Task/Rest/SubscribeByUserIdTask.h"
#include "Request/GetSubscribeRequest.h"
#include "Task/Rest/GetSubscribeTask.h"
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Task/Rest/GetSubscribeByUserIdTask.h"
#include "Request/UpdateNotificationTypeRequest.h"
#include "Task/Rest/UpdateNotificationTypeTask.h"
#include "Request/UpdateNotificationTypeByUserIdRequest.h"
#include "Task/Rest/UpdateNotificationTypeByUserIdTask.h"
#include "Request/UnsubscribeRequest.h"
#include "Task/Rest/UnsubscribeTask.h"
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Task/Rest/UnsubscribeByUserIdTask.h"

namespace Gs2::Chat
{
    class GS2CHAT_API FGs2ChatRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ChatRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRoomsTask>> DescribeRooms(
            const Request::FDescribeRoomsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRoomTask>> CreateRoom(
            const Request::FCreateRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRoomFromBackendTask>> CreateRoomFromBackend(
            const Request::FCreateRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRoomTask>> GetRoom(
            const Request::FGetRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRoomTask>> UpdateRoom(
            const Request::FUpdateRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRoomFromBackendTask>> UpdateRoomFromBackend(
            const Request::FUpdateRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRoomTask>> DeleteRoom(
            const Request::FDeleteRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRoomFromBackendTask>> DeleteRoomFromBackend(
            const Request::FDeleteRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMessagesTask>> DescribeMessages(
            const Request::FDescribeMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMessagesByUserIdTask>> DescribeMessagesByUserId(
            const Request::FDescribeMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPostTask>> Post(
            const Request::FPostRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPostByUserIdTask>> PostByUserId(
            const Request::FPostByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMessageTask>> GetMessage(
            const Request::FGetMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMessageByUserIdTask>> GetMessageByUserId(
            const Request::FGetMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMessageTask>> DeleteMessage(
            const Request::FDeleteMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesTask>> DescribeSubscribes(
            const Request::FDescribeSubscribesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByUserIdTask>> DescribeSubscribesByUserId(
            const Request::FDescribeSubscribesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByRoomNameTask>> DescribeSubscribesByRoomName(
            const Request::FDescribeSubscribesByRoomNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubscribeTask>> Subscribe(
            const Request::FSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubscribeByUserIdTask>> SubscribeByUserId(
            const Request::FSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeTask>> GetSubscribe(
            const Request::FGetSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeByUserIdTask>> GetSubscribeByUserId(
            const Request::FGetSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNotificationTypeTask>> UpdateNotificationType(
            const Request::FUpdateNotificationTypeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNotificationTypeByUserIdTask>> UpdateNotificationTypeByUserId(
            const Request::FUpdateNotificationTypeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnsubscribeTask>> Unsubscribe(
            const Request::FUnsubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnsubscribeByUserIdTask>> UnsubscribeByUserId(
            const Request::FUnsubscribeByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ChatRestClient, ESPMode::ThreadSafe> FGs2ChatRestClientPtr;
}