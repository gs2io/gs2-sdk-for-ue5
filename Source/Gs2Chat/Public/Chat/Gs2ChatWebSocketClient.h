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
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/WebSocket/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/WebSocket/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/DescribeRoomsRequest.h"
#include "Task/WebSocket/DescribeRoomsTask.h"
#include "Request/CreateRoomRequest.h"
#include "Task/WebSocket/CreateRoomTask.h"
#include "Request/CreateRoomFromBackendRequest.h"
#include "Task/WebSocket/CreateRoomFromBackendTask.h"
#include "Request/GetRoomRequest.h"
#include "Task/WebSocket/GetRoomTask.h"
#include "Request/UpdateRoomRequest.h"
#include "Task/WebSocket/UpdateRoomTask.h"
#include "Request/UpdateRoomFromBackendRequest.h"
#include "Task/WebSocket/UpdateRoomFromBackendTask.h"
#include "Request/DeleteRoomRequest.h"
#include "Task/WebSocket/DeleteRoomTask.h"
#include "Request/DeleteRoomFromBackendRequest.h"
#include "Task/WebSocket/DeleteRoomFromBackendTask.h"
#include "Request/DescribeMessagesRequest.h"
#include "Task/WebSocket/DescribeMessagesTask.h"
#include "Request/DescribeMessagesByUserIdRequest.h"
#include "Task/WebSocket/DescribeMessagesByUserIdTask.h"
#include "Request/PostRequest.h"
#include "Task/WebSocket/PostTask.h"
#include "Request/PostByUserIdRequest.h"
#include "Task/WebSocket/PostByUserIdTask.h"
#include "Request/GetMessageRequest.h"
#include "Task/WebSocket/GetMessageTask.h"
#include "Request/GetMessageByUserIdRequest.h"
#include "Task/WebSocket/GetMessageByUserIdTask.h"
#include "Request/DeleteMessageRequest.h"
#include "Task/WebSocket/DeleteMessageTask.h"
#include "Request/DescribeSubscribesRequest.h"
#include "Task/WebSocket/DescribeSubscribesTask.h"
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Task/WebSocket/DescribeSubscribesByUserIdTask.h"
#include "Request/DescribeSubscribesByRoomNameRequest.h"
#include "Task/WebSocket/DescribeSubscribesByRoomNameTask.h"
#include "Request/SubscribeRequest.h"
#include "Task/WebSocket/SubscribeTask.h"
#include "Request/SubscribeByUserIdRequest.h"
#include "Task/WebSocket/SubscribeByUserIdTask.h"
#include "Request/GetSubscribeRequest.h"
#include "Task/WebSocket/GetSubscribeTask.h"
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Task/WebSocket/GetSubscribeByUserIdTask.h"
#include "Request/UpdateNotificationTypeRequest.h"
#include "Task/WebSocket/UpdateNotificationTypeTask.h"
#include "Request/UpdateNotificationTypeByUserIdRequest.h"
#include "Task/WebSocket/UpdateNotificationTypeByUserIdTask.h"
#include "Request/UnsubscribeRequest.h"
#include "Task/WebSocket/UnsubscribeTask.h"
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Task/WebSocket/UnsubscribeByUserIdTask.h"

namespace Gs2::Chat
{
    class GS2CHAT_API FGs2ChatWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2ChatWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRoomsTask>> DescribeRooms(
            const Request::FDescribeRoomsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRoomTask>> CreateRoom(
            const Request::FCreateRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRoomFromBackendTask>> CreateRoomFromBackend(
            const Request::FCreateRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRoomTask>> GetRoom(
            const Request::FGetRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRoomTask>> UpdateRoom(
            const Request::FUpdateRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRoomFromBackendTask>> UpdateRoomFromBackend(
            const Request::FUpdateRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRoomTask>> DeleteRoom(
            const Request::FDeleteRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRoomFromBackendTask>> DeleteRoomFromBackend(
            const Request::FDeleteRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMessagesTask>> DescribeMessages(
            const Request::FDescribeMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMessagesByUserIdTask>> DescribeMessagesByUserId(
            const Request::FDescribeMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPostTask>> Post(
            const Request::FPostRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPostByUserIdTask>> PostByUserId(
            const Request::FPostByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMessageTask>> GetMessage(
            const Request::FGetMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMessageByUserIdTask>> GetMessageByUserId(
            const Request::FGetMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMessageTask>> DeleteMessage(
            const Request::FDeleteMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesTask>> DescribeSubscribes(
            const Request::FDescribeSubscribesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByUserIdTask>> DescribeSubscribesByUserId(
            const Request::FDescribeSubscribesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSubscribesByRoomNameTask>> DescribeSubscribesByRoomName(
            const Request::FDescribeSubscribesByRoomNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubscribeTask>> Subscribe(
            const Request::FSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubscribeByUserIdTask>> SubscribeByUserId(
            const Request::FSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeTask>> GetSubscribe(
            const Request::FGetSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSubscribeByUserIdTask>> GetSubscribeByUserId(
            const Request::FGetSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNotificationTypeTask>> UpdateNotificationType(
            const Request::FUpdateNotificationTypeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNotificationTypeByUserIdTask>> UpdateNotificationTypeByUserId(
            const Request::FUpdateNotificationTypeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnsubscribeTask>> Unsubscribe(
            const Request::FUnsubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnsubscribeByUserIdTask>> UnsubscribeByUserId(
            const Request::FUnsubscribeByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ChatWebSocketClient, ESPMode::ThreadSafe> FGs2ChatWebSocketClientPtr;
}