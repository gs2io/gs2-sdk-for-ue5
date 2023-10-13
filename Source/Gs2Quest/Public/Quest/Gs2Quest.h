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
#include "Model/QuestGroupModelMaster.h"
#include "Model/QuestModelMaster.h"
#include "Model/CurrentQuestMaster.h"
#include "Model/Contents.h"
#include "Model/Reward.h"
#include "Model/Progress.h"
#include "Model/CompletedQuestList.h"
#include "Model/QuestGroupModel.h"
#include "Model/QuestModel.h"
#include "Model/AcquireAction.h"
#include "Model/ConsumeAction.h"
#include "Model/Config.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
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

// DescribeQuestGroupModelMasters
#include "Request/DescribeQuestGroupModelMastersRequest.h"
#include "Result/DescribeQuestGroupModelMastersResult.h"
#include "Task/Rest/DescribeQuestGroupModelMastersTask.h"
#include "Task/WebSocket/DescribeQuestGroupModelMastersTask.h"

// CreateQuestGroupModelMaster
#include "Request/CreateQuestGroupModelMasterRequest.h"
#include "Result/CreateQuestGroupModelMasterResult.h"
#include "Task/Rest/CreateQuestGroupModelMasterTask.h"
#include "Task/WebSocket/CreateQuestGroupModelMasterTask.h"

// GetQuestGroupModelMaster
#include "Request/GetQuestGroupModelMasterRequest.h"
#include "Result/GetQuestGroupModelMasterResult.h"
#include "Task/Rest/GetQuestGroupModelMasterTask.h"
#include "Task/WebSocket/GetQuestGroupModelMasterTask.h"

// UpdateQuestGroupModelMaster
#include "Request/UpdateQuestGroupModelMasterRequest.h"
#include "Result/UpdateQuestGroupModelMasterResult.h"
#include "Task/Rest/UpdateQuestGroupModelMasterTask.h"
#include "Task/WebSocket/UpdateQuestGroupModelMasterTask.h"

// DeleteQuestGroupModelMaster
#include "Request/DeleteQuestGroupModelMasterRequest.h"
#include "Result/DeleteQuestGroupModelMasterResult.h"
#include "Task/Rest/DeleteQuestGroupModelMasterTask.h"
#include "Task/WebSocket/DeleteQuestGroupModelMasterTask.h"

// DescribeQuestModelMasters
#include "Request/DescribeQuestModelMastersRequest.h"
#include "Result/DescribeQuestModelMastersResult.h"
#include "Task/Rest/DescribeQuestModelMastersTask.h"
#include "Task/WebSocket/DescribeQuestModelMastersTask.h"

// CreateQuestModelMaster
#include "Request/CreateQuestModelMasterRequest.h"
#include "Result/CreateQuestModelMasterResult.h"
#include "Task/Rest/CreateQuestModelMasterTask.h"
#include "Task/WebSocket/CreateQuestModelMasterTask.h"

// GetQuestModelMaster
#include "Request/GetQuestModelMasterRequest.h"
#include "Result/GetQuestModelMasterResult.h"
#include "Task/Rest/GetQuestModelMasterTask.h"
#include "Task/WebSocket/GetQuestModelMasterTask.h"

// UpdateQuestModelMaster
#include "Request/UpdateQuestModelMasterRequest.h"
#include "Result/UpdateQuestModelMasterResult.h"
#include "Task/Rest/UpdateQuestModelMasterTask.h"
#include "Task/WebSocket/UpdateQuestModelMasterTask.h"

// DeleteQuestModelMaster
#include "Request/DeleteQuestModelMasterRequest.h"
#include "Result/DeleteQuestModelMasterResult.h"
#include "Task/Rest/DeleteQuestModelMasterTask.h"
#include "Task/WebSocket/DeleteQuestModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentQuestMaster
#include "Request/GetCurrentQuestMasterRequest.h"
#include "Result/GetCurrentQuestMasterResult.h"
#include "Task/Rest/GetCurrentQuestMasterTask.h"
#include "Task/WebSocket/GetCurrentQuestMasterTask.h"

// UpdateCurrentQuestMaster
#include "Request/UpdateCurrentQuestMasterRequest.h"
#include "Result/UpdateCurrentQuestMasterResult.h"
#include "Task/Rest/UpdateCurrentQuestMasterTask.h"
#include "Task/WebSocket/UpdateCurrentQuestMasterTask.h"

// UpdateCurrentQuestMasterFromGitHub
#include "Request/UpdateCurrentQuestMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentQuestMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentQuestMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentQuestMasterFromGitHubTask.h"

// DescribeProgressesByUserId
#include "Request/DescribeProgressesByUserIdRequest.h"
#include "Result/DescribeProgressesByUserIdResult.h"
#include "Task/Rest/DescribeProgressesByUserIdTask.h"
#include "Task/WebSocket/DescribeProgressesByUserIdTask.h"

// CreateProgressByUserId
#include "Request/CreateProgressByUserIdRequest.h"
#include "Result/CreateProgressByUserIdResult.h"
#include "Task/Rest/CreateProgressByUserIdTask.h"
#include "Task/WebSocket/CreateProgressByUserIdTask.h"

// GetProgress
#include "Request/GetProgressRequest.h"
#include "Result/GetProgressResult.h"
#include "Task/Rest/GetProgressTask.h"
#include "Task/WebSocket/GetProgressTask.h"

// GetProgressByUserId
#include "Request/GetProgressByUserIdRequest.h"
#include "Result/GetProgressByUserIdResult.h"
#include "Task/Rest/GetProgressByUserIdTask.h"
#include "Task/WebSocket/GetProgressByUserIdTask.h"

// Start
#include "Request/StartRequest.h"
#include "Result/StartResult.h"
#include "Task/Rest/StartTask.h"
#include "Task/WebSocket/StartTask.h"

// StartByUserId
#include "Request/StartByUserIdRequest.h"
#include "Result/StartByUserIdResult.h"
#include "Task/Rest/StartByUserIdTask.h"
#include "Task/WebSocket/StartByUserIdTask.h"

// End
#include "Request/EndRequest.h"
#include "Result/EndResult.h"
#include "Task/Rest/EndTask.h"
#include "Task/WebSocket/EndTask.h"

// EndByUserId
#include "Request/EndByUserIdRequest.h"
#include "Result/EndByUserIdResult.h"
#include "Task/Rest/EndByUserIdTask.h"
#include "Task/WebSocket/EndByUserIdTask.h"

// DeleteProgress
#include "Request/DeleteProgressRequest.h"
#include "Result/DeleteProgressResult.h"
#include "Task/Rest/DeleteProgressTask.h"
#include "Task/WebSocket/DeleteProgressTask.h"

// DeleteProgressByUserId
#include "Request/DeleteProgressByUserIdRequest.h"
#include "Result/DeleteProgressByUserIdResult.h"
#include "Task/Rest/DeleteProgressByUserIdTask.h"
#include "Task/WebSocket/DeleteProgressByUserIdTask.h"

// CreateProgressByStampSheet
#include "Request/CreateProgressByStampSheetRequest.h"
#include "Result/CreateProgressByStampSheetResult.h"
#include "Task/Rest/CreateProgressByStampSheetTask.h"
#include "Task/WebSocket/CreateProgressByStampSheetTask.h"

// DeleteProgressByStampTask
#include "Request/DeleteProgressByStampTaskRequest.h"
#include "Result/DeleteProgressByStampTaskResult.h"
#include "Task/Rest/DeleteProgressByStampTaskTask.h"
#include "Task/WebSocket/DeleteProgressByStampTaskTask.h"

// DescribeCompletedQuestLists
#include "Request/DescribeCompletedQuestListsRequest.h"
#include "Result/DescribeCompletedQuestListsResult.h"
#include "Task/Rest/DescribeCompletedQuestListsTask.h"
#include "Task/WebSocket/DescribeCompletedQuestListsTask.h"

// DescribeCompletedQuestListsByUserId
#include "Request/DescribeCompletedQuestListsByUserIdRequest.h"
#include "Result/DescribeCompletedQuestListsByUserIdResult.h"
#include "Task/Rest/DescribeCompletedQuestListsByUserIdTask.h"
#include "Task/WebSocket/DescribeCompletedQuestListsByUserIdTask.h"

// GetCompletedQuestList
#include "Request/GetCompletedQuestListRequest.h"
#include "Result/GetCompletedQuestListResult.h"
#include "Task/Rest/GetCompletedQuestListTask.h"
#include "Task/WebSocket/GetCompletedQuestListTask.h"

// GetCompletedQuestListByUserId
#include "Request/GetCompletedQuestListByUserIdRequest.h"
#include "Result/GetCompletedQuestListByUserIdResult.h"
#include "Task/Rest/GetCompletedQuestListByUserIdTask.h"
#include "Task/WebSocket/GetCompletedQuestListByUserIdTask.h"

// DeleteCompletedQuestListByUserId
#include "Request/DeleteCompletedQuestListByUserIdRequest.h"
#include "Result/DeleteCompletedQuestListByUserIdResult.h"
#include "Task/Rest/DeleteCompletedQuestListByUserIdTask.h"
#include "Task/WebSocket/DeleteCompletedQuestListByUserIdTask.h"

// DescribeQuestGroupModels
#include "Request/DescribeQuestGroupModelsRequest.h"
#include "Result/DescribeQuestGroupModelsResult.h"
#include "Task/Rest/DescribeQuestGroupModelsTask.h"
#include "Task/WebSocket/DescribeQuestGroupModelsTask.h"

// GetQuestGroupModel
#include "Request/GetQuestGroupModelRequest.h"
#include "Result/GetQuestGroupModelResult.h"
#include "Task/Rest/GetQuestGroupModelTask.h"
#include "Task/WebSocket/GetQuestGroupModelTask.h"

// DescribeQuestModels
#include "Request/DescribeQuestModelsRequest.h"
#include "Result/DescribeQuestModelsResult.h"
#include "Task/Rest/DescribeQuestModelsTask.h"
#include "Task/WebSocket/DescribeQuestModelsTask.h"

// GetQuestModel
#include "Request/GetQuestModelRequest.h"
#include "Result/GetQuestModelResult.h"
#include "Task/Rest/GetQuestModelTask.h"
#include "Task/WebSocket/GetQuestModelTask.h"

// Client
#include "Gs2QuestRestClient.h"
#include "Gs2QuestWebSocketClient.h"