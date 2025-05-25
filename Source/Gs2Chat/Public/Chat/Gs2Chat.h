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

// Model
#include "Model/Namespace.h"
#include "Model/Room.h"
#include "Model/Message.h"
#include "Model/Subscribe.h"
#include "Model/NotificationType.h"
#include "Model/ScriptSetting.h"
#include "Model/NotificationSetting.h"
#include "Model/LogSetting.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

// DumpUserDataByUserId
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Result/DumpUserDataByUserIdResult.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"

// CheckDumpUserDataByUserId
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Result/CheckDumpUserDataByUserIdResult.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"

// CleanUserDataByUserId
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Result/CleanUserDataByUserIdResult.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"

// CheckCleanUserDataByUserId
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Result/CheckCleanUserDataByUserIdResult.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"

// PrepareImportUserDataByUserId
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Result/PrepareImportUserDataByUserIdResult.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"

// ImportUserDataByUserId
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Result/ImportUserDataByUserIdResult.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"

// CheckImportUserDataByUserId
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Result/CheckImportUserDataByUserIdResult.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"

// DescribeRooms
#include "Request/DescribeRoomsRequest.h"
#include "Result/DescribeRoomsResult.h"
#include "Task/Rest/DescribeRoomsTask.h"
#include "Task/WebSocket/DescribeRoomsTask.h"

// CreateRoom
#include "Request/CreateRoomRequest.h"
#include "Result/CreateRoomResult.h"
#include "Task/Rest/CreateRoomTask.h"
#include "Task/WebSocket/CreateRoomTask.h"

// CreateRoomFromBackend
#include "Request/CreateRoomFromBackendRequest.h"
#include "Result/CreateRoomFromBackendResult.h"
#include "Task/Rest/CreateRoomFromBackendTask.h"
#include "Task/WebSocket/CreateRoomFromBackendTask.h"

// GetRoom
#include "Request/GetRoomRequest.h"
#include "Result/GetRoomResult.h"
#include "Task/Rest/GetRoomTask.h"
#include "Task/WebSocket/GetRoomTask.h"

// UpdateRoom
#include "Request/UpdateRoomRequest.h"
#include "Result/UpdateRoomResult.h"
#include "Task/Rest/UpdateRoomTask.h"
#include "Task/WebSocket/UpdateRoomTask.h"

// UpdateRoomFromBackend
#include "Request/UpdateRoomFromBackendRequest.h"
#include "Result/UpdateRoomFromBackendResult.h"
#include "Task/Rest/UpdateRoomFromBackendTask.h"
#include "Task/WebSocket/UpdateRoomFromBackendTask.h"

// DeleteRoom
#include "Request/DeleteRoomRequest.h"
#include "Result/DeleteRoomResult.h"
#include "Task/Rest/DeleteRoomTask.h"
#include "Task/WebSocket/DeleteRoomTask.h"

// DeleteRoomFromBackend
#include "Request/DeleteRoomFromBackendRequest.h"
#include "Result/DeleteRoomFromBackendResult.h"
#include "Task/Rest/DeleteRoomFromBackendTask.h"
#include "Task/WebSocket/DeleteRoomFromBackendTask.h"

// DescribeMessages
#include "Request/DescribeMessagesRequest.h"
#include "Result/DescribeMessagesResult.h"
#include "Task/Rest/DescribeMessagesTask.h"
#include "Task/WebSocket/DescribeMessagesTask.h"

// DescribeMessagesByUserId
#include "Request/DescribeMessagesByUserIdRequest.h"
#include "Result/DescribeMessagesByUserIdResult.h"
#include "Task/Rest/DescribeMessagesByUserIdTask.h"
#include "Task/WebSocket/DescribeMessagesByUserIdTask.h"

// DescribeLatestMessages
#include "Request/DescribeLatestMessagesRequest.h"
#include "Result/DescribeLatestMessagesResult.h"
#include "Task/Rest/DescribeLatestMessagesTask.h"
#include "Task/WebSocket/DescribeLatestMessagesTask.h"

// DescribeLatestMessagesByUserId
#include "Request/DescribeLatestMessagesByUserIdRequest.h"
#include "Result/DescribeLatestMessagesByUserIdResult.h"
#include "Task/Rest/DescribeLatestMessagesByUserIdTask.h"
#include "Task/WebSocket/DescribeLatestMessagesByUserIdTask.h"

// Post
#include "Request/PostRequest.h"
#include "Result/PostResult.h"
#include "Task/Rest/PostTask.h"
#include "Task/WebSocket/PostTask.h"

// PostByUserId
#include "Request/PostByUserIdRequest.h"
#include "Result/PostByUserIdResult.h"
#include "Task/Rest/PostByUserIdTask.h"
#include "Task/WebSocket/PostByUserIdTask.h"

// GetMessage
#include "Request/GetMessageRequest.h"
#include "Result/GetMessageResult.h"
#include "Task/Rest/GetMessageTask.h"
#include "Task/WebSocket/GetMessageTask.h"

// GetMessageByUserId
#include "Request/GetMessageByUserIdRequest.h"
#include "Result/GetMessageByUserIdResult.h"
#include "Task/Rest/GetMessageByUserIdTask.h"
#include "Task/WebSocket/GetMessageByUserIdTask.h"

// DeleteMessage
#include "Request/DeleteMessageRequest.h"
#include "Result/DeleteMessageResult.h"
#include "Task/Rest/DeleteMessageTask.h"
#include "Task/WebSocket/DeleteMessageTask.h"

// DescribeSubscribes
#include "Request/DescribeSubscribesRequest.h"
#include "Result/DescribeSubscribesResult.h"
#include "Task/Rest/DescribeSubscribesTask.h"
#include "Task/WebSocket/DescribeSubscribesTask.h"

// DescribeSubscribesByUserId
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Result/DescribeSubscribesByUserIdResult.h"
#include "Task/Rest/DescribeSubscribesByUserIdTask.h"
#include "Task/WebSocket/DescribeSubscribesByUserIdTask.h"

// DescribeSubscribesByRoomName
#include "Request/DescribeSubscribesByRoomNameRequest.h"
#include "Result/DescribeSubscribesByRoomNameResult.h"
#include "Task/Rest/DescribeSubscribesByRoomNameTask.h"
#include "Task/WebSocket/DescribeSubscribesByRoomNameTask.h"

// Subscribe
#include "Request/SubscribeRequest.h"
#include "Result/SubscribeResult.h"
#include "Task/Rest/SubscribeTask.h"
#include "Task/WebSocket/SubscribeTask.h"

// SubscribeByUserId
#include "Request/SubscribeByUserIdRequest.h"
#include "Result/SubscribeByUserIdResult.h"
#include "Task/Rest/SubscribeByUserIdTask.h"
#include "Task/WebSocket/SubscribeByUserIdTask.h"

// GetSubscribe
#include "Request/GetSubscribeRequest.h"
#include "Result/GetSubscribeResult.h"
#include "Task/Rest/GetSubscribeTask.h"
#include "Task/WebSocket/GetSubscribeTask.h"

// GetSubscribeByUserId
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Result/GetSubscribeByUserIdResult.h"
#include "Task/Rest/GetSubscribeByUserIdTask.h"
#include "Task/WebSocket/GetSubscribeByUserIdTask.h"

// UpdateNotificationType
#include "Request/UpdateNotificationTypeRequest.h"
#include "Result/UpdateNotificationTypeResult.h"
#include "Task/Rest/UpdateNotificationTypeTask.h"
#include "Task/WebSocket/UpdateNotificationTypeTask.h"

// UpdateNotificationTypeByUserId
#include "Request/UpdateNotificationTypeByUserIdRequest.h"
#include "Result/UpdateNotificationTypeByUserIdResult.h"
#include "Task/Rest/UpdateNotificationTypeByUserIdTask.h"
#include "Task/WebSocket/UpdateNotificationTypeByUserIdTask.h"

// Unsubscribe
#include "Request/UnsubscribeRequest.h"
#include "Result/UnsubscribeResult.h"
#include "Task/Rest/UnsubscribeTask.h"
#include "Task/WebSocket/UnsubscribeTask.h"

// UnsubscribeByUserId
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Result/UnsubscribeByUserIdResult.h"
#include "Task/Rest/UnsubscribeByUserIdTask.h"
#include "Task/WebSocket/UnsubscribeByUserIdTask.h"

// Client
#include "Gs2ChatRestClient.h"
#include "Gs2ChatWebSocketClient.h"