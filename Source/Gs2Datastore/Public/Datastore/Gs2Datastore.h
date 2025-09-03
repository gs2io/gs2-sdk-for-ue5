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
#include "Model/ScriptSetting.h"
#include "Model/DataObject.h"
#include "Model/DataObjectHistory.h"
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

// DescribeDataObjects
#include "Request/DescribeDataObjectsRequest.h"
#include "Result/DescribeDataObjectsResult.h"
#include "Task/Rest/DescribeDataObjectsTask.h"
#include "Task/WebSocket/DescribeDataObjectsTask.h"

// DescribeDataObjectsByUserId
#include "Request/DescribeDataObjectsByUserIdRequest.h"
#include "Result/DescribeDataObjectsByUserIdResult.h"
#include "Task/Rest/DescribeDataObjectsByUserIdTask.h"
#include "Task/WebSocket/DescribeDataObjectsByUserIdTask.h"

// PrepareUpload
#include "Request/PrepareUploadRequest.h"
#include "Result/PrepareUploadResult.h"
#include "Task/Rest/PrepareUploadTask.h"
#include "Task/WebSocket/PrepareUploadTask.h"

// PrepareUploadByUserId
#include "Request/PrepareUploadByUserIdRequest.h"
#include "Result/PrepareUploadByUserIdResult.h"
#include "Task/Rest/PrepareUploadByUserIdTask.h"
#include "Task/WebSocket/PrepareUploadByUserIdTask.h"

// UpdateDataObject
#include "Request/UpdateDataObjectRequest.h"
#include "Result/UpdateDataObjectResult.h"
#include "Task/Rest/UpdateDataObjectTask.h"
#include "Task/WebSocket/UpdateDataObjectTask.h"

// UpdateDataObjectByUserId
#include "Request/UpdateDataObjectByUserIdRequest.h"
#include "Result/UpdateDataObjectByUserIdResult.h"
#include "Task/Rest/UpdateDataObjectByUserIdTask.h"
#include "Task/WebSocket/UpdateDataObjectByUserIdTask.h"

// PrepareReUpload
#include "Request/PrepareReUploadRequest.h"
#include "Result/PrepareReUploadResult.h"
#include "Task/Rest/PrepareReUploadTask.h"
#include "Task/WebSocket/PrepareReUploadTask.h"

// PrepareReUploadByUserId
#include "Request/PrepareReUploadByUserIdRequest.h"
#include "Result/PrepareReUploadByUserIdResult.h"
#include "Task/Rest/PrepareReUploadByUserIdTask.h"
#include "Task/WebSocket/PrepareReUploadByUserIdTask.h"

// DoneUpload
#include "Request/DoneUploadRequest.h"
#include "Result/DoneUploadResult.h"
#include "Task/Rest/DoneUploadTask.h"
#include "Task/WebSocket/DoneUploadTask.h"

// DoneUploadByUserId
#include "Request/DoneUploadByUserIdRequest.h"
#include "Result/DoneUploadByUserIdResult.h"
#include "Task/Rest/DoneUploadByUserIdTask.h"
#include "Task/WebSocket/DoneUploadByUserIdTask.h"

// DeleteDataObject
#include "Request/DeleteDataObjectRequest.h"
#include "Result/DeleteDataObjectResult.h"
#include "Task/Rest/DeleteDataObjectTask.h"
#include "Task/WebSocket/DeleteDataObjectTask.h"

// DeleteDataObjectByUserId
#include "Request/DeleteDataObjectByUserIdRequest.h"
#include "Result/DeleteDataObjectByUserIdResult.h"
#include "Task/Rest/DeleteDataObjectByUserIdTask.h"
#include "Task/WebSocket/DeleteDataObjectByUserIdTask.h"

// PrepareDownload
#include "Request/PrepareDownloadRequest.h"
#include "Result/PrepareDownloadResult.h"
#include "Task/Rest/PrepareDownloadTask.h"
#include "Task/WebSocket/PrepareDownloadTask.h"

// PrepareDownloadByUserId
#include "Request/PrepareDownloadByUserIdRequest.h"
#include "Result/PrepareDownloadByUserIdResult.h"
#include "Task/Rest/PrepareDownloadByUserIdTask.h"
#include "Task/WebSocket/PrepareDownloadByUserIdTask.h"

// PrepareDownloadByGeneration
#include "Request/PrepareDownloadByGenerationRequest.h"
#include "Result/PrepareDownloadByGenerationResult.h"
#include "Task/Rest/PrepareDownloadByGenerationTask.h"
#include "Task/WebSocket/PrepareDownloadByGenerationTask.h"

// PrepareDownloadByGenerationAndUserId
#include "Request/PrepareDownloadByGenerationAndUserIdRequest.h"
#include "Result/PrepareDownloadByGenerationAndUserIdResult.h"
#include "Task/Rest/PrepareDownloadByGenerationAndUserIdTask.h"
#include "Task/WebSocket/PrepareDownloadByGenerationAndUserIdTask.h"

// PrepareDownloadOwnData
#include "Request/PrepareDownloadOwnDataRequest.h"
#include "Result/PrepareDownloadOwnDataResult.h"
#include "Task/Rest/PrepareDownloadOwnDataTask.h"
#include "Task/WebSocket/PrepareDownloadOwnDataTask.h"

// PrepareDownloadByUserIdAndDataObjectName
#include "Request/PrepareDownloadByUserIdAndDataObjectNameRequest.h"
#include "Result/PrepareDownloadByUserIdAndDataObjectNameResult.h"
#include "Task/Rest/PrepareDownloadByUserIdAndDataObjectNameTask.h"
#include "Task/WebSocket/PrepareDownloadByUserIdAndDataObjectNameTask.h"

// PrepareDownloadOwnDataByGeneration
#include "Request/PrepareDownloadOwnDataByGenerationRequest.h"
#include "Result/PrepareDownloadOwnDataByGenerationResult.h"
#include "Task/Rest/PrepareDownloadOwnDataByGenerationTask.h"
#include "Task/WebSocket/PrepareDownloadOwnDataByGenerationTask.h"

// PrepareDownloadByUserIdAndDataObjectNameAndGeneration
#include "Request/PrepareDownloadByUserIdAndDataObjectNameAndGenerationRequest.h"
#include "Result/PrepareDownloadByUserIdAndDataObjectNameAndGenerationResult.h"
#include "Task/Rest/PrepareDownloadByUserIdAndDataObjectNameAndGenerationTask.h"
#include "Task/WebSocket/PrepareDownloadByUserIdAndDataObjectNameAndGenerationTask.h"

// RestoreDataObject
#include "Request/RestoreDataObjectRequest.h"
#include "Result/RestoreDataObjectResult.h"
#include "Task/Rest/RestoreDataObjectTask.h"
#include "Task/WebSocket/RestoreDataObjectTask.h"

// DescribeDataObjectHistories
#include "Request/DescribeDataObjectHistoriesRequest.h"
#include "Result/DescribeDataObjectHistoriesResult.h"
#include "Task/Rest/DescribeDataObjectHistoriesTask.h"
#include "Task/WebSocket/DescribeDataObjectHistoriesTask.h"

// DescribeDataObjectHistoriesByUserId
#include "Request/DescribeDataObjectHistoriesByUserIdRequest.h"
#include "Result/DescribeDataObjectHistoriesByUserIdResult.h"
#include "Task/Rest/DescribeDataObjectHistoriesByUserIdTask.h"
#include "Task/WebSocket/DescribeDataObjectHistoriesByUserIdTask.h"

// GetDataObjectHistory
#include "Request/GetDataObjectHistoryRequest.h"
#include "Result/GetDataObjectHistoryResult.h"
#include "Task/Rest/GetDataObjectHistoryTask.h"
#include "Task/WebSocket/GetDataObjectHistoryTask.h"

// GetDataObjectHistoryByUserId
#include "Request/GetDataObjectHistoryByUserIdRequest.h"
#include "Result/GetDataObjectHistoryByUserIdResult.h"
#include "Task/Rest/GetDataObjectHistoryByUserIdTask.h"
#include "Task/WebSocket/GetDataObjectHistoryByUserIdTask.h"

// Client
#include "Gs2DatastoreRestClient.h"
#include "Gs2DatastoreWebSocketClient.h"