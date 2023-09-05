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
#include "Model/Complete.h"
#include "Model/NotificationSetting.h"
#include "Model/CounterModelMaster.h"
#include "Model/CounterScopeModel.h"
#include "Model/MissionGroupModelMaster.h"
#include "Model/Namespace.h"
#include "Model/Counter.h"
#include "Model/CurrentMissionMaster.h"
#include "Model/CounterModel.h"
#include "Model/MissionGroupModel.h"
#include "Model/MissionTaskModel.h"
#include "Model/ScopedValue.h"
#include "Model/MissionTaskModelMaster.h"
#include "Model/AcquireAction.h"
#include "Model/Config.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/TransactionSetting.h"

// DescribeCompletes
#include "Request/DescribeCompletesRequest.h"
#include "Result/DescribeCompletesResult.h"
#include "Task/Rest/DescribeCompletesTask.h"
#include "Task/WebSocket/DescribeCompletesTask.h"

// DescribeCompletesByUserId
#include "Request/DescribeCompletesByUserIdRequest.h"
#include "Result/DescribeCompletesByUserIdResult.h"
#include "Task/Rest/DescribeCompletesByUserIdTask.h"
#include "Task/WebSocket/DescribeCompletesByUserIdTask.h"

// Complete
#include "Request/CompleteRequest.h"
#include "Result/CompleteResult.h"
#include "Task/Rest/CompleteTask.h"
#include "Task/WebSocket/CompleteTask.h"

// CompleteByUserId
#include "Request/CompleteByUserIdRequest.h"
#include "Result/CompleteByUserIdResult.h"
#include "Task/Rest/CompleteByUserIdTask.h"
#include "Task/WebSocket/CompleteByUserIdTask.h"

// ReceiveByUserId
#include "Request/ReceiveByUserIdRequest.h"
#include "Result/ReceiveByUserIdResult.h"
#include "Task/Rest/ReceiveByUserIdTask.h"
#include "Task/WebSocket/ReceiveByUserIdTask.h"

// RevertReceiveByUserId
#include "Request/RevertReceiveByUserIdRequest.h"
#include "Result/RevertReceiveByUserIdResult.h"
#include "Task/Rest/RevertReceiveByUserIdTask.h"
#include "Task/WebSocket/RevertReceiveByUserIdTask.h"

// GetComplete
#include "Request/GetCompleteRequest.h"
#include "Result/GetCompleteResult.h"
#include "Task/Rest/GetCompleteTask.h"
#include "Task/WebSocket/GetCompleteTask.h"

// GetCompleteByUserId
#include "Request/GetCompleteByUserIdRequest.h"
#include "Result/GetCompleteByUserIdResult.h"
#include "Task/Rest/GetCompleteByUserIdTask.h"
#include "Task/WebSocket/GetCompleteByUserIdTask.h"

// DeleteCompleteByUserId
#include "Request/DeleteCompleteByUserIdRequest.h"
#include "Result/DeleteCompleteByUserIdResult.h"
#include "Task/Rest/DeleteCompleteByUserIdTask.h"
#include "Task/WebSocket/DeleteCompleteByUserIdTask.h"

// ReceiveByStampTask
#include "Request/ReceiveByStampTaskRequest.h"
#include "Result/ReceiveByStampTaskResult.h"
#include "Task/Rest/ReceiveByStampTaskTask.h"
#include "Task/WebSocket/ReceiveByStampTaskTask.h"

// RevertReceiveByStampSheet
#include "Request/RevertReceiveByStampSheetRequest.h"
#include "Result/RevertReceiveByStampSheetResult.h"
#include "Task/Rest/RevertReceiveByStampSheetTask.h"
#include "Task/WebSocket/RevertReceiveByStampSheetTask.h"

// DescribeCounterModelMasters
#include "Request/DescribeCounterModelMastersRequest.h"
#include "Result/DescribeCounterModelMastersResult.h"
#include "Task/Rest/DescribeCounterModelMastersTask.h"
#include "Task/WebSocket/DescribeCounterModelMastersTask.h"

// CreateCounterModelMaster
#include "Request/CreateCounterModelMasterRequest.h"
#include "Result/CreateCounterModelMasterResult.h"
#include "Task/Rest/CreateCounterModelMasterTask.h"
#include "Task/WebSocket/CreateCounterModelMasterTask.h"

// GetCounterModelMaster
#include "Request/GetCounterModelMasterRequest.h"
#include "Result/GetCounterModelMasterResult.h"
#include "Task/Rest/GetCounterModelMasterTask.h"
#include "Task/WebSocket/GetCounterModelMasterTask.h"

// UpdateCounterModelMaster
#include "Request/UpdateCounterModelMasterRequest.h"
#include "Result/UpdateCounterModelMasterResult.h"
#include "Task/Rest/UpdateCounterModelMasterTask.h"
#include "Task/WebSocket/UpdateCounterModelMasterTask.h"

// DeleteCounterModelMaster
#include "Request/DeleteCounterModelMasterRequest.h"
#include "Result/DeleteCounterModelMasterResult.h"
#include "Task/Rest/DeleteCounterModelMasterTask.h"
#include "Task/WebSocket/DeleteCounterModelMasterTask.h"

// DescribeMissionGroupModelMasters
#include "Request/DescribeMissionGroupModelMastersRequest.h"
#include "Result/DescribeMissionGroupModelMastersResult.h"
#include "Task/Rest/DescribeMissionGroupModelMastersTask.h"
#include "Task/WebSocket/DescribeMissionGroupModelMastersTask.h"

// CreateMissionGroupModelMaster
#include "Request/CreateMissionGroupModelMasterRequest.h"
#include "Result/CreateMissionGroupModelMasterResult.h"
#include "Task/Rest/CreateMissionGroupModelMasterTask.h"
#include "Task/WebSocket/CreateMissionGroupModelMasterTask.h"

// GetMissionGroupModelMaster
#include "Request/GetMissionGroupModelMasterRequest.h"
#include "Result/GetMissionGroupModelMasterResult.h"
#include "Task/Rest/GetMissionGroupModelMasterTask.h"
#include "Task/WebSocket/GetMissionGroupModelMasterTask.h"

// UpdateMissionGroupModelMaster
#include "Request/UpdateMissionGroupModelMasterRequest.h"
#include "Result/UpdateMissionGroupModelMasterResult.h"
#include "Task/Rest/UpdateMissionGroupModelMasterTask.h"
#include "Task/WebSocket/UpdateMissionGroupModelMasterTask.h"

// DeleteMissionGroupModelMaster
#include "Request/DeleteMissionGroupModelMasterRequest.h"
#include "Result/DeleteMissionGroupModelMasterResult.h"
#include "Task/Rest/DeleteMissionGroupModelMasterTask.h"
#include "Task/WebSocket/DeleteMissionGroupModelMasterTask.h"

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

// DescribeCounters
#include "Request/DescribeCountersRequest.h"
#include "Result/DescribeCountersResult.h"
#include "Task/Rest/DescribeCountersTask.h"
#include "Task/WebSocket/DescribeCountersTask.h"

// DescribeCountersByUserId
#include "Request/DescribeCountersByUserIdRequest.h"
#include "Result/DescribeCountersByUserIdResult.h"
#include "Task/Rest/DescribeCountersByUserIdTask.h"
#include "Task/WebSocket/DescribeCountersByUserIdTask.h"

// IncreaseCounterByUserId
#include "Request/IncreaseCounterByUserIdRequest.h"
#include "Result/IncreaseCounterByUserIdResult.h"
#include "Task/Rest/IncreaseCounterByUserIdTask.h"
#include "Task/WebSocket/IncreaseCounterByUserIdTask.h"

// DecreaseCounterByUserId
#include "Request/DecreaseCounterByUserIdRequest.h"
#include "Result/DecreaseCounterByUserIdResult.h"
#include "Task/Rest/DecreaseCounterByUserIdTask.h"
#include "Task/WebSocket/DecreaseCounterByUserIdTask.h"

// GetCounter
#include "Request/GetCounterRequest.h"
#include "Result/GetCounterResult.h"
#include "Task/Rest/GetCounterTask.h"
#include "Task/WebSocket/GetCounterTask.h"

// GetCounterByUserId
#include "Request/GetCounterByUserIdRequest.h"
#include "Result/GetCounterByUserIdResult.h"
#include "Task/Rest/GetCounterByUserIdTask.h"
#include "Task/WebSocket/GetCounterByUserIdTask.h"

// DeleteCounterByUserId
#include "Request/DeleteCounterByUserIdRequest.h"
#include "Result/DeleteCounterByUserIdResult.h"
#include "Task/Rest/DeleteCounterByUserIdTask.h"
#include "Task/WebSocket/DeleteCounterByUserIdTask.h"

// IncreaseByStampSheet
#include "Request/IncreaseByStampSheetRequest.h"
#include "Result/IncreaseByStampSheetResult.h"
#include "Task/Rest/IncreaseByStampSheetTask.h"
#include "Task/WebSocket/IncreaseByStampSheetTask.h"

// DecreaseByStampTask
#include "Request/DecreaseByStampTaskRequest.h"
#include "Result/DecreaseByStampTaskResult.h"
#include "Task/Rest/DecreaseByStampTaskTask.h"
#include "Task/WebSocket/DecreaseByStampTaskTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentMissionMaster
#include "Request/GetCurrentMissionMasterRequest.h"
#include "Result/GetCurrentMissionMasterResult.h"
#include "Task/Rest/GetCurrentMissionMasterTask.h"
#include "Task/WebSocket/GetCurrentMissionMasterTask.h"

// UpdateCurrentMissionMaster
#include "Request/UpdateCurrentMissionMasterRequest.h"
#include "Result/UpdateCurrentMissionMasterResult.h"
#include "Task/Rest/UpdateCurrentMissionMasterTask.h"
#include "Task/WebSocket/UpdateCurrentMissionMasterTask.h"

// UpdateCurrentMissionMasterFromGitHub
#include "Request/UpdateCurrentMissionMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentMissionMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentMissionMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentMissionMasterFromGitHubTask.h"

// DescribeCounterModels
#include "Request/DescribeCounterModelsRequest.h"
#include "Result/DescribeCounterModelsResult.h"
#include "Task/Rest/DescribeCounterModelsTask.h"
#include "Task/WebSocket/DescribeCounterModelsTask.h"

// GetCounterModel
#include "Request/GetCounterModelRequest.h"
#include "Result/GetCounterModelResult.h"
#include "Task/Rest/GetCounterModelTask.h"
#include "Task/WebSocket/GetCounterModelTask.h"

// DescribeMissionGroupModels
#include "Request/DescribeMissionGroupModelsRequest.h"
#include "Result/DescribeMissionGroupModelsResult.h"
#include "Task/Rest/DescribeMissionGroupModelsTask.h"
#include "Task/WebSocket/DescribeMissionGroupModelsTask.h"

// GetMissionGroupModel
#include "Request/GetMissionGroupModelRequest.h"
#include "Result/GetMissionGroupModelResult.h"
#include "Task/Rest/GetMissionGroupModelTask.h"
#include "Task/WebSocket/GetMissionGroupModelTask.h"

// DescribeMissionTaskModels
#include "Request/DescribeMissionTaskModelsRequest.h"
#include "Result/DescribeMissionTaskModelsResult.h"
#include "Task/Rest/DescribeMissionTaskModelsTask.h"
#include "Task/WebSocket/DescribeMissionTaskModelsTask.h"

// GetMissionTaskModel
#include "Request/GetMissionTaskModelRequest.h"
#include "Result/GetMissionTaskModelResult.h"
#include "Task/Rest/GetMissionTaskModelTask.h"
#include "Task/WebSocket/GetMissionTaskModelTask.h"

// DescribeMissionTaskModelMasters
#include "Request/DescribeMissionTaskModelMastersRequest.h"
#include "Result/DescribeMissionTaskModelMastersResult.h"
#include "Task/Rest/DescribeMissionTaskModelMastersTask.h"
#include "Task/WebSocket/DescribeMissionTaskModelMastersTask.h"

// CreateMissionTaskModelMaster
#include "Request/CreateMissionTaskModelMasterRequest.h"
#include "Result/CreateMissionTaskModelMasterResult.h"
#include "Task/Rest/CreateMissionTaskModelMasterTask.h"
#include "Task/WebSocket/CreateMissionTaskModelMasterTask.h"

// GetMissionTaskModelMaster
#include "Request/GetMissionTaskModelMasterRequest.h"
#include "Result/GetMissionTaskModelMasterResult.h"
#include "Task/Rest/GetMissionTaskModelMasterTask.h"
#include "Task/WebSocket/GetMissionTaskModelMasterTask.h"

// UpdateMissionTaskModelMaster
#include "Request/UpdateMissionTaskModelMasterRequest.h"
#include "Result/UpdateMissionTaskModelMasterResult.h"
#include "Task/Rest/UpdateMissionTaskModelMasterTask.h"
#include "Task/WebSocket/UpdateMissionTaskModelMasterTask.h"

// DeleteMissionTaskModelMaster
#include "Request/DeleteMissionTaskModelMasterRequest.h"
#include "Result/DeleteMissionTaskModelMasterResult.h"
#include "Task/Rest/DeleteMissionTaskModelMasterTask.h"
#include "Task/WebSocket/DeleteMissionTaskModelMasterTask.h"

// Client
#include "Gs2MissionRestClient.h"
#include "Gs2MissionWebSocketClient.h"