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

// ApplyStamina
#include "Request/ApplyStaminaRequest.h"
#include "Result/ApplyStaminaResult.h"
#include "Task/Rest/ApplyStaminaTask.h"
#include "Task/WebSocket/ApplyStaminaTask.h"

// ApplyStaminaByUserId
#include "Request/ApplyStaminaByUserIdRequest.h"
#include "Result/ApplyStaminaByUserIdResult.h"
#include "Task/Rest/ApplyStaminaByUserIdTask.h"
#include "Task/WebSocket/ApplyStaminaByUserIdTask.h"

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

// DecreaseMaxValue
#include "Request/DecreaseMaxValueRequest.h"
#include "Result/DecreaseMaxValueResult.h"
#include "Task/Rest/DecreaseMaxValueTask.h"
#include "Task/WebSocket/DecreaseMaxValueTask.h"

// DecreaseMaxValueByUserId
#include "Request/DecreaseMaxValueByUserIdRequest.h"
#include "Result/DecreaseMaxValueByUserIdResult.h"
#include "Task/Rest/DecreaseMaxValueByUserIdTask.h"
#include "Task/WebSocket/DecreaseMaxValueByUserIdTask.h"

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

// VerifyStaminaValue
#include "Request/VerifyStaminaValueRequest.h"
#include "Result/VerifyStaminaValueResult.h"
#include "Task/Rest/VerifyStaminaValueTask.h"
#include "Task/WebSocket/VerifyStaminaValueTask.h"

// VerifyStaminaValueByUserId
#include "Request/VerifyStaminaValueByUserIdRequest.h"
#include "Result/VerifyStaminaValueByUserIdResult.h"
#include "Task/Rest/VerifyStaminaValueByUserIdTask.h"
#include "Task/WebSocket/VerifyStaminaValueByUserIdTask.h"

// VerifyStaminaMaxValue
#include "Request/VerifyStaminaMaxValueRequest.h"
#include "Result/VerifyStaminaMaxValueResult.h"
#include "Task/Rest/VerifyStaminaMaxValueTask.h"
#include "Task/WebSocket/VerifyStaminaMaxValueTask.h"

// VerifyStaminaMaxValueByUserId
#include "Request/VerifyStaminaMaxValueByUserIdRequest.h"
#include "Result/VerifyStaminaMaxValueByUserIdResult.h"
#include "Task/Rest/VerifyStaminaMaxValueByUserIdTask.h"
#include "Task/WebSocket/VerifyStaminaMaxValueByUserIdTask.h"

// VerifyStaminaRecoverIntervalMinutes
#include "Request/VerifyStaminaRecoverIntervalMinutesRequest.h"
#include "Result/VerifyStaminaRecoverIntervalMinutesResult.h"
#include "Task/Rest/VerifyStaminaRecoverIntervalMinutesTask.h"
#include "Task/WebSocket/VerifyStaminaRecoverIntervalMinutesTask.h"

// VerifyStaminaRecoverIntervalMinutesByUserId
#include "Request/VerifyStaminaRecoverIntervalMinutesByUserIdRequest.h"
#include "Result/VerifyStaminaRecoverIntervalMinutesByUserIdResult.h"
#include "Task/Rest/VerifyStaminaRecoverIntervalMinutesByUserIdTask.h"
#include "Task/WebSocket/VerifyStaminaRecoverIntervalMinutesByUserIdTask.h"

// VerifyStaminaRecoverValue
#include "Request/VerifyStaminaRecoverValueRequest.h"
#include "Result/VerifyStaminaRecoverValueResult.h"
#include "Task/Rest/VerifyStaminaRecoverValueTask.h"
#include "Task/WebSocket/VerifyStaminaRecoverValueTask.h"

// VerifyStaminaRecoverValueByUserId
#include "Request/VerifyStaminaRecoverValueByUserIdRequest.h"
#include "Result/VerifyStaminaRecoverValueByUserIdResult.h"
#include "Task/Rest/VerifyStaminaRecoverValueByUserIdTask.h"
#include "Task/WebSocket/VerifyStaminaRecoverValueByUserIdTask.h"

// VerifyStaminaOverflowValue
#include "Request/VerifyStaminaOverflowValueRequest.h"
#include "Result/VerifyStaminaOverflowValueResult.h"
#include "Task/Rest/VerifyStaminaOverflowValueTask.h"
#include "Task/WebSocket/VerifyStaminaOverflowValueTask.h"

// VerifyStaminaOverflowValueByUserId
#include "Request/VerifyStaminaOverflowValueByUserIdRequest.h"
#include "Result/VerifyStaminaOverflowValueByUserIdResult.h"
#include "Task/Rest/VerifyStaminaOverflowValueByUserIdTask.h"
#include "Task/WebSocket/VerifyStaminaOverflowValueByUserIdTask.h"

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

// DecreaseMaxValueByStampTask
#include "Request/DecreaseMaxValueByStampTaskRequest.h"
#include "Result/DecreaseMaxValueByStampTaskResult.h"
#include "Task/Rest/DecreaseMaxValueByStampTaskTask.h"
#include "Task/WebSocket/DecreaseMaxValueByStampTaskTask.h"

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

// VerifyStaminaValueByStampTask
#include "Request/VerifyStaminaValueByStampTaskRequest.h"
#include "Result/VerifyStaminaValueByStampTaskResult.h"
#include "Task/Rest/VerifyStaminaValueByStampTaskTask.h"
#include "Task/WebSocket/VerifyStaminaValueByStampTaskTask.h"

// VerifyStaminaMaxValueByStampTask
#include "Request/VerifyStaminaMaxValueByStampTaskRequest.h"
#include "Result/VerifyStaminaMaxValueByStampTaskResult.h"
#include "Task/Rest/VerifyStaminaMaxValueByStampTaskTask.h"
#include "Task/WebSocket/VerifyStaminaMaxValueByStampTaskTask.h"

// VerifyStaminaRecoverIntervalMinutesByStampTask
#include "Request/VerifyStaminaRecoverIntervalMinutesByStampTaskRequest.h"
#include "Result/VerifyStaminaRecoverIntervalMinutesByStampTaskResult.h"
#include "Task/Rest/VerifyStaminaRecoverIntervalMinutesByStampTaskTask.h"
#include "Task/WebSocket/VerifyStaminaRecoverIntervalMinutesByStampTaskTask.h"

// VerifyStaminaRecoverValueByStampTask
#include "Request/VerifyStaminaRecoverValueByStampTaskRequest.h"
#include "Result/VerifyStaminaRecoverValueByStampTaskResult.h"
#include "Task/Rest/VerifyStaminaRecoverValueByStampTaskTask.h"
#include "Task/WebSocket/VerifyStaminaRecoverValueByStampTaskTask.h"

// VerifyStaminaOverflowValueByStampTask
#include "Request/VerifyStaminaOverflowValueByStampTaskRequest.h"
#include "Result/VerifyStaminaOverflowValueByStampTaskResult.h"
#include "Task/Rest/VerifyStaminaOverflowValueByStampTaskTask.h"
#include "Task/WebSocket/VerifyStaminaOverflowValueByStampTaskTask.h"

// Client
#include "Gs2StaminaRestClient.h"
#include "Gs2StaminaWebSocketClient.h"