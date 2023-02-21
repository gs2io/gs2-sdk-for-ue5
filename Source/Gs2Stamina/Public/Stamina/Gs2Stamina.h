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
#include "Model/StaminaModelMaster.h"
#include "Model/MaxStaminaTableMaster.h"
#include "Model/RecoverIntervalTableMaster.h"
#include "Model/RecoverValueTableMaster.h"
#include "Model/CurrentStaminaMaster.h"
#include "Model/StaminaModel.h"
#include "Model/MaxStaminaTable.h"
#include "Model/RecoverIntervalTable.h"
#include "Model/RecoverValueTable.h"
#include "Model/Stamina.h"
#include "Model/GitHubCheckoutSetting.h"
#include "Model/LogSetting.h"
#include "Model/ScriptSetting.h"

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

// DescribeStaminaModelMasters
#include "Request/DescribeStaminaModelMastersRequest.h"
#include "Result/DescribeStaminaModelMastersResult.h"
#include "Task/Rest/DescribeStaminaModelMastersTask.h"
#include "Task/WebSocket/DescribeStaminaModelMastersTask.h"

// CreateStaminaModelMaster
#include "Request/CreateStaminaModelMasterRequest.h"
#include "Result/CreateStaminaModelMasterResult.h"
#include "Task/Rest/CreateStaminaModelMasterTask.h"
#include "Task/WebSocket/CreateStaminaModelMasterTask.h"

// GetStaminaModelMaster
#include "Request/GetStaminaModelMasterRequest.h"
#include "Result/GetStaminaModelMasterResult.h"
#include "Task/Rest/GetStaminaModelMasterTask.h"
#include "Task/WebSocket/GetStaminaModelMasterTask.h"

// UpdateStaminaModelMaster
#include "Request/UpdateStaminaModelMasterRequest.h"
#include "Result/UpdateStaminaModelMasterResult.h"
#include "Task/Rest/UpdateStaminaModelMasterTask.h"
#include "Task/WebSocket/UpdateStaminaModelMasterTask.h"

// DeleteStaminaModelMaster
#include "Request/DeleteStaminaModelMasterRequest.h"
#include "Result/DeleteStaminaModelMasterResult.h"
#include "Task/Rest/DeleteStaminaModelMasterTask.h"
#include "Task/WebSocket/DeleteStaminaModelMasterTask.h"

// DescribeMaxStaminaTableMasters
#include "Request/DescribeMaxStaminaTableMastersRequest.h"
#include "Result/DescribeMaxStaminaTableMastersResult.h"
#include "Task/Rest/DescribeMaxStaminaTableMastersTask.h"
#include "Task/WebSocket/DescribeMaxStaminaTableMastersTask.h"

// CreateMaxStaminaTableMaster
#include "Request/CreateMaxStaminaTableMasterRequest.h"
#include "Result/CreateMaxStaminaTableMasterResult.h"
#include "Task/Rest/CreateMaxStaminaTableMasterTask.h"
#include "Task/WebSocket/CreateMaxStaminaTableMasterTask.h"

// GetMaxStaminaTableMaster
#include "Request/GetMaxStaminaTableMasterRequest.h"
#include "Result/GetMaxStaminaTableMasterResult.h"
#include "Task/Rest/GetMaxStaminaTableMasterTask.h"
#include "Task/WebSocket/GetMaxStaminaTableMasterTask.h"

// UpdateMaxStaminaTableMaster
#include "Request/UpdateMaxStaminaTableMasterRequest.h"
#include "Result/UpdateMaxStaminaTableMasterResult.h"
#include "Task/Rest/UpdateMaxStaminaTableMasterTask.h"
#include "Task/WebSocket/UpdateMaxStaminaTableMasterTask.h"

// DeleteMaxStaminaTableMaster
#include "Request/DeleteMaxStaminaTableMasterRequest.h"
#include "Result/DeleteMaxStaminaTableMasterResult.h"
#include "Task/Rest/DeleteMaxStaminaTableMasterTask.h"
#include "Task/WebSocket/DeleteMaxStaminaTableMasterTask.h"

// DescribeRecoverIntervalTableMasters
#include "Request/DescribeRecoverIntervalTableMastersRequest.h"
#include "Result/DescribeRecoverIntervalTableMastersResult.h"
#include "Task/Rest/DescribeRecoverIntervalTableMastersTask.h"
#include "Task/WebSocket/DescribeRecoverIntervalTableMastersTask.h"

// CreateRecoverIntervalTableMaster
#include "Request/CreateRecoverIntervalTableMasterRequest.h"
#include "Result/CreateRecoverIntervalTableMasterResult.h"
#include "Task/Rest/CreateRecoverIntervalTableMasterTask.h"
#include "Task/WebSocket/CreateRecoverIntervalTableMasterTask.h"

// GetRecoverIntervalTableMaster
#include "Request/GetRecoverIntervalTableMasterRequest.h"
#include "Result/GetRecoverIntervalTableMasterResult.h"
#include "Task/Rest/GetRecoverIntervalTableMasterTask.h"
#include "Task/WebSocket/GetRecoverIntervalTableMasterTask.h"

// UpdateRecoverIntervalTableMaster
#include "Request/UpdateRecoverIntervalTableMasterRequest.h"
#include "Result/UpdateRecoverIntervalTableMasterResult.h"
#include "Task/Rest/UpdateRecoverIntervalTableMasterTask.h"
#include "Task/WebSocket/UpdateRecoverIntervalTableMasterTask.h"

// DeleteRecoverIntervalTableMaster
#include "Request/DeleteRecoverIntervalTableMasterRequest.h"
#include "Result/DeleteRecoverIntervalTableMasterResult.h"
#include "Task/Rest/DeleteRecoverIntervalTableMasterTask.h"
#include "Task/WebSocket/DeleteRecoverIntervalTableMasterTask.h"

// DescribeRecoverValueTableMasters
#include "Request/DescribeRecoverValueTableMastersRequest.h"
#include "Result/DescribeRecoverValueTableMastersResult.h"
#include "Task/Rest/DescribeRecoverValueTableMastersTask.h"
#include "Task/WebSocket/DescribeRecoverValueTableMastersTask.h"

// CreateRecoverValueTableMaster
#include "Request/CreateRecoverValueTableMasterRequest.h"
#include "Result/CreateRecoverValueTableMasterResult.h"
#include "Task/Rest/CreateRecoverValueTableMasterTask.h"
#include "Task/WebSocket/CreateRecoverValueTableMasterTask.h"

// GetRecoverValueTableMaster
#include "Request/GetRecoverValueTableMasterRequest.h"
#include "Result/GetRecoverValueTableMasterResult.h"
#include "Task/Rest/GetRecoverValueTableMasterTask.h"
#include "Task/WebSocket/GetRecoverValueTableMasterTask.h"

// UpdateRecoverValueTableMaster
#include "Request/UpdateRecoverValueTableMasterRequest.h"
#include "Result/UpdateRecoverValueTableMasterResult.h"
#include "Task/Rest/UpdateRecoverValueTableMasterTask.h"
#include "Task/WebSocket/UpdateRecoverValueTableMasterTask.h"

// DeleteRecoverValueTableMaster
#include "Request/DeleteRecoverValueTableMasterRequest.h"
#include "Result/DeleteRecoverValueTableMasterResult.h"
#include "Task/Rest/DeleteRecoverValueTableMasterTask.h"
#include "Task/WebSocket/DeleteRecoverValueTableMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentStaminaMaster
#include "Request/GetCurrentStaminaMasterRequest.h"
#include "Result/GetCurrentStaminaMasterResult.h"
#include "Task/Rest/GetCurrentStaminaMasterTask.h"
#include "Task/WebSocket/GetCurrentStaminaMasterTask.h"

// UpdateCurrentStaminaMaster
#include "Request/UpdateCurrentStaminaMasterRequest.h"
#include "Result/UpdateCurrentStaminaMasterResult.h"
#include "Task/Rest/UpdateCurrentStaminaMasterTask.h"
#include "Task/WebSocket/UpdateCurrentStaminaMasterTask.h"

// UpdateCurrentStaminaMasterFromGitHub
#include "Request/UpdateCurrentStaminaMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentStaminaMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentStaminaMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentStaminaMasterFromGitHubTask.h"

// DescribeStaminaModels
#include "Request/DescribeStaminaModelsRequest.h"
#include "Result/DescribeStaminaModelsResult.h"
#include "Task/Rest/DescribeStaminaModelsTask.h"
#include "Task/WebSocket/DescribeStaminaModelsTask.h"

// GetStaminaModel
#include "Request/GetStaminaModelRequest.h"
#include "Result/GetStaminaModelResult.h"
#include "Task/Rest/GetStaminaModelTask.h"
#include "Task/WebSocket/GetStaminaModelTask.h"

// DescribeStaminas
#include "Request/DescribeStaminasRequest.h"
#include "Result/DescribeStaminasResult.h"
#include "Task/Rest/DescribeStaminasTask.h"
#include "Task/WebSocket/DescribeStaminasTask.h"

// DescribeStaminasByUserId
#include "Request/DescribeStaminasByUserIdRequest.h"
#include "Result/DescribeStaminasByUserIdResult.h"
#include "Task/Rest/DescribeStaminasByUserIdTask.h"
#include "Task/WebSocket/DescribeStaminasByUserIdTask.h"

// GetStamina
#include "Request/GetStaminaRequest.h"
#include "Result/GetStaminaResult.h"
#include "Task/Rest/GetStaminaTask.h"
#include "Task/WebSocket/GetStaminaTask.h"

// GetStaminaByUserId
#include "Request/GetStaminaByUserIdRequest.h"
#include "Result/GetStaminaByUserIdResult.h"
#include "Task/Rest/GetStaminaByUserIdTask.h"
#include "Task/WebSocket/GetStaminaByUserIdTask.h"

// UpdateStaminaByUserId
#include "Request/UpdateStaminaByUserIdRequest.h"
#include "Result/UpdateStaminaByUserIdResult.h"
#include "Task/Rest/UpdateStaminaByUserIdTask.h"
#include "Task/WebSocket/UpdateStaminaByUserIdTask.h"

// ConsumeStamina
#include "Request/ConsumeStaminaRequest.h"
#include "Result/ConsumeStaminaResult.h"
#include "Task/Rest/ConsumeStaminaTask.h"
#include "Task/WebSocket/ConsumeStaminaTask.h"

// ConsumeStaminaByUserId
#include "Request/ConsumeStaminaByUserIdRequest.h"
#include "Result/ConsumeStaminaByUserIdResult.h"
#include "Task/Rest/ConsumeStaminaByUserIdTask.h"
#include "Task/WebSocket/ConsumeStaminaByUserIdTask.h"

// RecoverStaminaByUserId
#include "Request/RecoverStaminaByUserIdRequest.h"
#include "Result/RecoverStaminaByUserIdResult.h"
#include "Task/Rest/RecoverStaminaByUserIdTask.h"
#include "Task/WebSocket/RecoverStaminaByUserIdTask.h"

// RaiseMaxValueByUserId
#include "Request/RaiseMaxValueByUserIdRequest.h"
#include "Result/RaiseMaxValueByUserIdResult.h"
#include "Task/Rest/RaiseMaxValueByUserIdTask.h"
#include "Task/WebSocket/RaiseMaxValueByUserIdTask.h"

// SetMaxValueByUserId
#include "Request/SetMaxValueByUserIdRequest.h"
#include "Result/SetMaxValueByUserIdResult.h"
#include "Task/Rest/SetMaxValueByUserIdTask.h"
#include "Task/WebSocket/SetMaxValueByUserIdTask.h"

// SetRecoverIntervalByUserId
#include "Request/SetRecoverIntervalByUserIdRequest.h"
#include "Result/SetRecoverIntervalByUserIdResult.h"
#include "Task/Rest/SetRecoverIntervalByUserIdTask.h"
#include "Task/WebSocket/SetRecoverIntervalByUserIdTask.h"

// SetRecoverValueByUserId
#include "Request/SetRecoverValueByUserIdRequest.h"
#include "Result/SetRecoverValueByUserIdResult.h"
#include "Task/Rest/SetRecoverValueByUserIdTask.h"
#include "Task/WebSocket/SetRecoverValueByUserIdTask.h"

// SetMaxValueByStatus
#include "Request/SetMaxValueByStatusRequest.h"
#include "Result/SetMaxValueByStatusResult.h"
#include "Task/Rest/SetMaxValueByStatusTask.h"
#include "Task/WebSocket/SetMaxValueByStatusTask.h"

// SetRecoverIntervalByStatus
#include "Request/SetRecoverIntervalByStatusRequest.h"
#include "Result/SetRecoverIntervalByStatusResult.h"
#include "Task/Rest/SetRecoverIntervalByStatusTask.h"
#include "Task/WebSocket/SetRecoverIntervalByStatusTask.h"

// SetRecoverValueByStatus
#include "Request/SetRecoverValueByStatusRequest.h"
#include "Result/SetRecoverValueByStatusResult.h"
#include "Task/Rest/SetRecoverValueByStatusTask.h"
#include "Task/WebSocket/SetRecoverValueByStatusTask.h"

// DeleteStaminaByUserId
#include "Request/DeleteStaminaByUserIdRequest.h"
#include "Result/DeleteStaminaByUserIdResult.h"
#include "Task/Rest/DeleteStaminaByUserIdTask.h"
#include "Task/WebSocket/DeleteStaminaByUserIdTask.h"

// RecoverStaminaByStampSheet
#include "Request/RecoverStaminaByStampSheetRequest.h"
#include "Result/RecoverStaminaByStampSheetResult.h"
#include "Task/Rest/RecoverStaminaByStampSheetTask.h"
#include "Task/WebSocket/RecoverStaminaByStampSheetTask.h"

// RaiseMaxValueByStampSheet
#include "Request/RaiseMaxValueByStampSheetRequest.h"
#include "Result/RaiseMaxValueByStampSheetResult.h"
#include "Task/Rest/RaiseMaxValueByStampSheetTask.h"
#include "Task/WebSocket/RaiseMaxValueByStampSheetTask.h"

// SetMaxValueByStampSheet
#include "Request/SetMaxValueByStampSheetRequest.h"
#include "Result/SetMaxValueByStampSheetResult.h"
#include "Task/Rest/SetMaxValueByStampSheetTask.h"
#include "Task/WebSocket/SetMaxValueByStampSheetTask.h"

// SetRecoverIntervalByStampSheet
#include "Request/SetRecoverIntervalByStampSheetRequest.h"
#include "Result/SetRecoverIntervalByStampSheetResult.h"
#include "Task/Rest/SetRecoverIntervalByStampSheetTask.h"
#include "Task/WebSocket/SetRecoverIntervalByStampSheetTask.h"

// SetRecoverValueByStampSheet
#include "Request/SetRecoverValueByStampSheetRequest.h"
#include "Result/SetRecoverValueByStampSheetResult.h"
#include "Task/Rest/SetRecoverValueByStampSheetTask.h"
#include "Task/WebSocket/SetRecoverValueByStampSheetTask.h"

// ConsumeStaminaByStampTask
#include "Request/ConsumeStaminaByStampTaskRequest.h"
#include "Result/ConsumeStaminaByStampTaskResult.h"
#include "Task/Rest/ConsumeStaminaByStampTaskTask.h"
#include "Task/WebSocket/ConsumeStaminaByStampTaskTask.h"

// Client
#include "Gs2StaminaRestClient.h"
#include "Gs2StaminaWebSocketClient.h"