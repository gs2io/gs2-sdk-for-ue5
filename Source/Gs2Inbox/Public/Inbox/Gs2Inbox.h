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
#include "Model/Message.h"
#include "Model/CurrentMessageMaster.h"
#include "Model/GlobalMessageMaster.h"
#include "Model/GlobalMessage.h"
#include "Model/Received.h"
#include "Model/TimeSpan.h"
#include "Model/AcquireAction.h"
#include "Model/Config.h"
#include "Model/VerifyActionResult.h"
#include "Model/ConsumeActionResult.h"
#include "Model/AcquireActionResult.h"
#include "Model/TransactionResult.h"
#include "Model/ScriptSetting.h"
#include "Model/NotificationSetting.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"
#include "Model/TransactionSetting.h"

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

// SendMessageByUserId
#include "Request/SendMessageByUserIdRequest.h"
#include "Result/SendMessageByUserIdResult.h"
#include "Task/Rest/SendMessageByUserIdTask.h"
#include "Task/WebSocket/SendMessageByUserIdTask.h"

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

// ReceiveGlobalMessage
#include "Request/ReceiveGlobalMessageRequest.h"
#include "Result/ReceiveGlobalMessageResult.h"
#include "Task/Rest/ReceiveGlobalMessageTask.h"
#include "Task/WebSocket/ReceiveGlobalMessageTask.h"

// ReceiveGlobalMessageByUserId
#include "Request/ReceiveGlobalMessageByUserIdRequest.h"
#include "Result/ReceiveGlobalMessageByUserIdResult.h"
#include "Task/Rest/ReceiveGlobalMessageByUserIdTask.h"
#include "Task/WebSocket/ReceiveGlobalMessageByUserIdTask.h"

// OpenMessage
#include "Request/OpenMessageRequest.h"
#include "Result/OpenMessageResult.h"
#include "Task/Rest/OpenMessageTask.h"
#include "Task/WebSocket/OpenMessageTask.h"

// OpenMessageByUserId
#include "Request/OpenMessageByUserIdRequest.h"
#include "Result/OpenMessageByUserIdResult.h"
#include "Task/Rest/OpenMessageByUserIdTask.h"
#include "Task/WebSocket/OpenMessageByUserIdTask.h"

// CloseMessageByUserId
#include "Request/CloseMessageByUserIdRequest.h"
#include "Result/CloseMessageByUserIdResult.h"
#include "Task/Rest/CloseMessageByUserIdTask.h"
#include "Task/WebSocket/CloseMessageByUserIdTask.h"

// ReadMessage
#include "Request/ReadMessageRequest.h"
#include "Result/ReadMessageResult.h"
#include "Task/Rest/ReadMessageTask.h"
#include "Task/WebSocket/ReadMessageTask.h"

// ReadMessageByUserId
#include "Request/ReadMessageByUserIdRequest.h"
#include "Result/ReadMessageByUserIdResult.h"
#include "Task/Rest/ReadMessageByUserIdTask.h"
#include "Task/WebSocket/ReadMessageByUserIdTask.h"

// BatchReadMessages
#include "Request/BatchReadMessagesRequest.h"
#include "Result/BatchReadMessagesResult.h"
#include "Task/Rest/BatchReadMessagesTask.h"
#include "Task/WebSocket/BatchReadMessagesTask.h"

// BatchReadMessagesByUserId
#include "Request/BatchReadMessagesByUserIdRequest.h"
#include "Result/BatchReadMessagesByUserIdResult.h"
#include "Task/Rest/BatchReadMessagesByUserIdTask.h"
#include "Task/WebSocket/BatchReadMessagesByUserIdTask.h"

// DeleteMessage
#include "Request/DeleteMessageRequest.h"
#include "Result/DeleteMessageResult.h"
#include "Task/Rest/DeleteMessageTask.h"
#include "Task/WebSocket/DeleteMessageTask.h"

// DeleteMessageByUserId
#include "Request/DeleteMessageByUserIdRequest.h"
#include "Result/DeleteMessageByUserIdResult.h"
#include "Task/Rest/DeleteMessageByUserIdTask.h"
#include "Task/WebSocket/DeleteMessageByUserIdTask.h"

// SendByStampSheet
#include "Request/SendByStampSheetRequest.h"
#include "Result/SendByStampSheetResult.h"
#include "Task/Rest/SendByStampSheetTask.h"
#include "Task/WebSocket/SendByStampSheetTask.h"

// OpenByStampTask
#include "Request/OpenByStampTaskRequest.h"
#include "Result/OpenByStampTaskResult.h"
#include "Task/Rest/OpenByStampTaskTask.h"
#include "Task/WebSocket/OpenByStampTaskTask.h"

// DeleteMessageByStampTask
#include "Request/DeleteMessageByStampTaskRequest.h"
#include "Result/DeleteMessageByStampTaskResult.h"
#include "Task/Rest/DeleteMessageByStampTaskTask.h"
#include "Task/WebSocket/DeleteMessageByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentMessageMaster
#include "Request/GetCurrentMessageMasterRequest.h"
#include "Result/GetCurrentMessageMasterResult.h"
#include "Task/Rest/GetCurrentMessageMasterTask.h"
#include "Task/WebSocket/GetCurrentMessageMasterTask.h"

// PreUpdateCurrentMessageMaster
#include "Request/PreUpdateCurrentMessageMasterRequest.h"
#include "Result/PreUpdateCurrentMessageMasterResult.h"
#include "Task/Rest/PreUpdateCurrentMessageMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentMessageMasterTask.h"

// UpdateCurrentMessageMaster
#include "Request/UpdateCurrentMessageMasterRequest.h"
#include "Result/UpdateCurrentMessageMasterResult.h"
#include "Task/Rest/UpdateCurrentMessageMasterTask.h"
#include "Task/WebSocket/UpdateCurrentMessageMasterTask.h"

// UpdateCurrentMessageMasterFromGitHub
#include "Request/UpdateCurrentMessageMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentMessageMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentMessageMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentMessageMasterFromGitHubTask.h"

// DescribeGlobalMessageMasters
#include "Request/DescribeGlobalMessageMastersRequest.h"
#include "Result/DescribeGlobalMessageMastersResult.h"
#include "Task/Rest/DescribeGlobalMessageMastersTask.h"
#include "Task/WebSocket/DescribeGlobalMessageMastersTask.h"

// CreateGlobalMessageMaster
#include "Request/CreateGlobalMessageMasterRequest.h"
#include "Result/CreateGlobalMessageMasterResult.h"
#include "Task/Rest/CreateGlobalMessageMasterTask.h"
#include "Task/WebSocket/CreateGlobalMessageMasterTask.h"

// GetGlobalMessageMaster
#include "Request/GetGlobalMessageMasterRequest.h"
#include "Result/GetGlobalMessageMasterResult.h"
#include "Task/Rest/GetGlobalMessageMasterTask.h"
#include "Task/WebSocket/GetGlobalMessageMasterTask.h"

// UpdateGlobalMessageMaster
#include "Request/UpdateGlobalMessageMasterRequest.h"
#include "Result/UpdateGlobalMessageMasterResult.h"
#include "Task/Rest/UpdateGlobalMessageMasterTask.h"
#include "Task/WebSocket/UpdateGlobalMessageMasterTask.h"

// DeleteGlobalMessageMaster
#include "Request/DeleteGlobalMessageMasterRequest.h"
#include "Result/DeleteGlobalMessageMasterResult.h"
#include "Task/Rest/DeleteGlobalMessageMasterTask.h"
#include "Task/WebSocket/DeleteGlobalMessageMasterTask.h"

// DescribeGlobalMessages
#include "Request/DescribeGlobalMessagesRequest.h"
#include "Result/DescribeGlobalMessagesResult.h"
#include "Task/Rest/DescribeGlobalMessagesTask.h"
#include "Task/WebSocket/DescribeGlobalMessagesTask.h"

// GetGlobalMessage
#include "Request/GetGlobalMessageRequest.h"
#include "Result/GetGlobalMessageResult.h"
#include "Task/Rest/GetGlobalMessageTask.h"
#include "Task/WebSocket/GetGlobalMessageTask.h"

// GetReceivedByUserId
#include "Request/GetReceivedByUserIdRequest.h"
#include "Result/GetReceivedByUserIdResult.h"
#include "Task/Rest/GetReceivedByUserIdTask.h"
#include "Task/WebSocket/GetReceivedByUserIdTask.h"

// UpdateReceivedByUserId
#include "Request/UpdateReceivedByUserIdRequest.h"
#include "Result/UpdateReceivedByUserIdResult.h"
#include "Task/Rest/UpdateReceivedByUserIdTask.h"
#include "Task/WebSocket/UpdateReceivedByUserIdTask.h"

// DeleteReceivedByUserId
#include "Request/DeleteReceivedByUserIdRequest.h"
#include "Result/DeleteReceivedByUserIdResult.h"
#include "Task/Rest/DeleteReceivedByUserIdTask.h"
#include "Task/WebSocket/DeleteReceivedByUserIdTask.h"

// Client
#include "Gs2InboxRestClient.h"
#include "Gs2InboxWebSocketClient.h"