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
#include "Model/EntryModel.h"
#include "Model/EntryModelMaster.h"
#include "Model/Entry.h"
#include "Model/CurrentEntryMaster.h"
#include "Model/Config.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
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

// DescribeEntryModels
#include "Request/DescribeEntryModelsRequest.h"
#include "Result/DescribeEntryModelsResult.h"
#include "Task/Rest/DescribeEntryModelsTask.h"
#include "Task/WebSocket/DescribeEntryModelsTask.h"

// GetEntryModel
#include "Request/GetEntryModelRequest.h"
#include "Result/GetEntryModelResult.h"
#include "Task/Rest/GetEntryModelTask.h"
#include "Task/WebSocket/GetEntryModelTask.h"

// DescribeEntryModelMasters
#include "Request/DescribeEntryModelMastersRequest.h"
#include "Result/DescribeEntryModelMastersResult.h"
#include "Task/Rest/DescribeEntryModelMastersTask.h"
#include "Task/WebSocket/DescribeEntryModelMastersTask.h"

// CreateEntryModelMaster
#include "Request/CreateEntryModelMasterRequest.h"
#include "Result/CreateEntryModelMasterResult.h"
#include "Task/Rest/CreateEntryModelMasterTask.h"
#include "Task/WebSocket/CreateEntryModelMasterTask.h"

// GetEntryModelMaster
#include "Request/GetEntryModelMasterRequest.h"
#include "Result/GetEntryModelMasterResult.h"
#include "Task/Rest/GetEntryModelMasterTask.h"
#include "Task/WebSocket/GetEntryModelMasterTask.h"

// UpdateEntryModelMaster
#include "Request/UpdateEntryModelMasterRequest.h"
#include "Result/UpdateEntryModelMasterResult.h"
#include "Task/Rest/UpdateEntryModelMasterTask.h"
#include "Task/WebSocket/UpdateEntryModelMasterTask.h"

// DeleteEntryModelMaster
#include "Request/DeleteEntryModelMasterRequest.h"
#include "Result/DeleteEntryModelMasterResult.h"
#include "Task/Rest/DeleteEntryModelMasterTask.h"
#include "Task/WebSocket/DeleteEntryModelMasterTask.h"

// DescribeEntries
#include "Request/DescribeEntriesRequest.h"
#include "Result/DescribeEntriesResult.h"
#include "Task/Rest/DescribeEntriesTask.h"
#include "Task/WebSocket/DescribeEntriesTask.h"

// DescribeEntriesByUserId
#include "Request/DescribeEntriesByUserIdRequest.h"
#include "Result/DescribeEntriesByUserIdResult.h"
#include "Task/Rest/DescribeEntriesByUserIdTask.h"
#include "Task/WebSocket/DescribeEntriesByUserIdTask.h"

// AddEntriesByUserId
#include "Request/AddEntriesByUserIdRequest.h"
#include "Result/AddEntriesByUserIdResult.h"
#include "Task/Rest/AddEntriesByUserIdTask.h"
#include "Task/WebSocket/AddEntriesByUserIdTask.h"

// GetEntry
#include "Request/GetEntryRequest.h"
#include "Result/GetEntryResult.h"
#include "Task/Rest/GetEntryTask.h"
#include "Task/WebSocket/GetEntryTask.h"

// GetEntryByUserId
#include "Request/GetEntryByUserIdRequest.h"
#include "Result/GetEntryByUserIdResult.h"
#include "Task/Rest/GetEntryByUserIdTask.h"
#include "Task/WebSocket/GetEntryByUserIdTask.h"

// GetEntryWithSignature
#include "Request/GetEntryWithSignatureRequest.h"
#include "Result/GetEntryWithSignatureResult.h"
#include "Task/Rest/GetEntryWithSignatureTask.h"
#include "Task/WebSocket/GetEntryWithSignatureTask.h"

// GetEntryWithSignatureByUserId
#include "Request/GetEntryWithSignatureByUserIdRequest.h"
#include "Result/GetEntryWithSignatureByUserIdResult.h"
#include "Task/Rest/GetEntryWithSignatureByUserIdTask.h"
#include "Task/WebSocket/GetEntryWithSignatureByUserIdTask.h"

// ResetByUserId
#include "Request/ResetByUserIdRequest.h"
#include "Result/ResetByUserIdResult.h"
#include "Task/Rest/ResetByUserIdTask.h"
#include "Task/WebSocket/ResetByUserIdTask.h"

// VerifyEntry
#include "Request/VerifyEntryRequest.h"
#include "Result/VerifyEntryResult.h"
#include "Task/Rest/VerifyEntryTask.h"
#include "Task/WebSocket/VerifyEntryTask.h"

// VerifyEntryByUserId
#include "Request/VerifyEntryByUserIdRequest.h"
#include "Result/VerifyEntryByUserIdResult.h"
#include "Task/Rest/VerifyEntryByUserIdTask.h"
#include "Task/WebSocket/VerifyEntryByUserIdTask.h"

// DeleteEntriesByUserId
#include "Request/DeleteEntriesByUserIdRequest.h"
#include "Result/DeleteEntriesByUserIdResult.h"
#include "Task/Rest/DeleteEntriesByUserIdTask.h"
#include "Task/WebSocket/DeleteEntriesByUserIdTask.h"

// AddEntriesByStampSheet
#include "Request/AddEntriesByStampSheetRequest.h"
#include "Result/AddEntriesByStampSheetResult.h"
#include "Task/Rest/AddEntriesByStampSheetTask.h"
#include "Task/WebSocket/AddEntriesByStampSheetTask.h"

// DeleteEntriesByStampTask
#include "Request/DeleteEntriesByStampTaskRequest.h"
#include "Result/DeleteEntriesByStampTaskResult.h"
#include "Task/Rest/DeleteEntriesByStampTaskTask.h"
#include "Task/WebSocket/DeleteEntriesByStampTaskTask.h"

// VerifyEntryByStampTask
#include "Request/VerifyEntryByStampTaskRequest.h"
#include "Result/VerifyEntryByStampTaskResult.h"
#include "Task/Rest/VerifyEntryByStampTaskTask.h"
#include "Task/WebSocket/VerifyEntryByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentEntryMaster
#include "Request/GetCurrentEntryMasterRequest.h"
#include "Result/GetCurrentEntryMasterResult.h"
#include "Task/Rest/GetCurrentEntryMasterTask.h"
#include "Task/WebSocket/GetCurrentEntryMasterTask.h"

// UpdateCurrentEntryMaster
#include "Request/UpdateCurrentEntryMasterRequest.h"
#include "Result/UpdateCurrentEntryMasterResult.h"
#include "Task/Rest/UpdateCurrentEntryMasterTask.h"
#include "Task/WebSocket/UpdateCurrentEntryMasterTask.h"

// UpdateCurrentEntryMasterFromGitHub
#include "Request/UpdateCurrentEntryMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentEntryMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentEntryMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentEntryMasterFromGitHubTask.h"

// Client
#include "Gs2DictionaryRestClient.h"
#include "Gs2DictionaryWebSocketClient.h"