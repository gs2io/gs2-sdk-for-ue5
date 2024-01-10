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
#include "Model/FormModel.h"
#include "Model/FormModelMaster.h"
#include "Model/MoldModel.h"
#include "Model/MoldModelMaster.h"
#include "Model/PropertyFormModel.h"
#include "Model/PropertyFormModelMaster.h"
#include "Model/CurrentFormMaster.h"
#include "Model/Mold.h"
#include "Model/Form.h"
#include "Model/PropertyForm.h"
#include "Model/Slot.h"
#include "Model/SlotModel.h"
#include "Model/SlotWithSignature.h"
#include "Model/AcquireAction.h"
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

// GetFormModel
#include "Request/GetFormModelRequest.h"
#include "Result/GetFormModelResult.h"
#include "Task/Rest/GetFormModelTask.h"
#include "Task/WebSocket/GetFormModelTask.h"

// DescribeFormModelMasters
#include "Request/DescribeFormModelMastersRequest.h"
#include "Result/DescribeFormModelMastersResult.h"
#include "Task/Rest/DescribeFormModelMastersTask.h"
#include "Task/WebSocket/DescribeFormModelMastersTask.h"

// CreateFormModelMaster
#include "Request/CreateFormModelMasterRequest.h"
#include "Result/CreateFormModelMasterResult.h"
#include "Task/Rest/CreateFormModelMasterTask.h"
#include "Task/WebSocket/CreateFormModelMasterTask.h"

// GetFormModelMaster
#include "Request/GetFormModelMasterRequest.h"
#include "Result/GetFormModelMasterResult.h"
#include "Task/Rest/GetFormModelMasterTask.h"
#include "Task/WebSocket/GetFormModelMasterTask.h"

// UpdateFormModelMaster
#include "Request/UpdateFormModelMasterRequest.h"
#include "Result/UpdateFormModelMasterResult.h"
#include "Task/Rest/UpdateFormModelMasterTask.h"
#include "Task/WebSocket/UpdateFormModelMasterTask.h"

// DeleteFormModelMaster
#include "Request/DeleteFormModelMasterRequest.h"
#include "Result/DeleteFormModelMasterResult.h"
#include "Task/Rest/DeleteFormModelMasterTask.h"
#include "Task/WebSocket/DeleteFormModelMasterTask.h"

// DescribeMoldModels
#include "Request/DescribeMoldModelsRequest.h"
#include "Result/DescribeMoldModelsResult.h"
#include "Task/Rest/DescribeMoldModelsTask.h"
#include "Task/WebSocket/DescribeMoldModelsTask.h"

// GetMoldModel
#include "Request/GetMoldModelRequest.h"
#include "Result/GetMoldModelResult.h"
#include "Task/Rest/GetMoldModelTask.h"
#include "Task/WebSocket/GetMoldModelTask.h"

// DescribeMoldModelMasters
#include "Request/DescribeMoldModelMastersRequest.h"
#include "Result/DescribeMoldModelMastersResult.h"
#include "Task/Rest/DescribeMoldModelMastersTask.h"
#include "Task/WebSocket/DescribeMoldModelMastersTask.h"

// CreateMoldModelMaster
#include "Request/CreateMoldModelMasterRequest.h"
#include "Result/CreateMoldModelMasterResult.h"
#include "Task/Rest/CreateMoldModelMasterTask.h"
#include "Task/WebSocket/CreateMoldModelMasterTask.h"

// GetMoldModelMaster
#include "Request/GetMoldModelMasterRequest.h"
#include "Result/GetMoldModelMasterResult.h"
#include "Task/Rest/GetMoldModelMasterTask.h"
#include "Task/WebSocket/GetMoldModelMasterTask.h"

// UpdateMoldModelMaster
#include "Request/UpdateMoldModelMasterRequest.h"
#include "Result/UpdateMoldModelMasterResult.h"
#include "Task/Rest/UpdateMoldModelMasterTask.h"
#include "Task/WebSocket/UpdateMoldModelMasterTask.h"

// DeleteMoldModelMaster
#include "Request/DeleteMoldModelMasterRequest.h"
#include "Result/DeleteMoldModelMasterResult.h"
#include "Task/Rest/DeleteMoldModelMasterTask.h"
#include "Task/WebSocket/DeleteMoldModelMasterTask.h"

// DescribePropertyFormModels
#include "Request/DescribePropertyFormModelsRequest.h"
#include "Result/DescribePropertyFormModelsResult.h"
#include "Task/Rest/DescribePropertyFormModelsTask.h"
#include "Task/WebSocket/DescribePropertyFormModelsTask.h"

// GetPropertyFormModel
#include "Request/GetPropertyFormModelRequest.h"
#include "Result/GetPropertyFormModelResult.h"
#include "Task/Rest/GetPropertyFormModelTask.h"
#include "Task/WebSocket/GetPropertyFormModelTask.h"

// DescribePropertyFormModelMasters
#include "Request/DescribePropertyFormModelMastersRequest.h"
#include "Result/DescribePropertyFormModelMastersResult.h"
#include "Task/Rest/DescribePropertyFormModelMastersTask.h"
#include "Task/WebSocket/DescribePropertyFormModelMastersTask.h"

// CreatePropertyFormModelMaster
#include "Request/CreatePropertyFormModelMasterRequest.h"
#include "Result/CreatePropertyFormModelMasterResult.h"
#include "Task/Rest/CreatePropertyFormModelMasterTask.h"
#include "Task/WebSocket/CreatePropertyFormModelMasterTask.h"

// GetPropertyFormModelMaster
#include "Request/GetPropertyFormModelMasterRequest.h"
#include "Result/GetPropertyFormModelMasterResult.h"
#include "Task/Rest/GetPropertyFormModelMasterTask.h"
#include "Task/WebSocket/GetPropertyFormModelMasterTask.h"

// UpdatePropertyFormModelMaster
#include "Request/UpdatePropertyFormModelMasterRequest.h"
#include "Result/UpdatePropertyFormModelMasterResult.h"
#include "Task/Rest/UpdatePropertyFormModelMasterTask.h"
#include "Task/WebSocket/UpdatePropertyFormModelMasterTask.h"

// DeletePropertyFormModelMaster
#include "Request/DeletePropertyFormModelMasterRequest.h"
#include "Result/DeletePropertyFormModelMasterResult.h"
#include "Task/Rest/DeletePropertyFormModelMasterTask.h"
#include "Task/WebSocket/DeletePropertyFormModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentFormMaster
#include "Request/GetCurrentFormMasterRequest.h"
#include "Result/GetCurrentFormMasterResult.h"
#include "Task/Rest/GetCurrentFormMasterTask.h"
#include "Task/WebSocket/GetCurrentFormMasterTask.h"

// UpdateCurrentFormMaster
#include "Request/UpdateCurrentFormMasterRequest.h"
#include "Result/UpdateCurrentFormMasterResult.h"
#include "Task/Rest/UpdateCurrentFormMasterTask.h"
#include "Task/WebSocket/UpdateCurrentFormMasterTask.h"

// UpdateCurrentFormMasterFromGitHub
#include "Request/UpdateCurrentFormMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentFormMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentFormMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentFormMasterFromGitHubTask.h"

// DescribeMolds
#include "Request/DescribeMoldsRequest.h"
#include "Result/DescribeMoldsResult.h"
#include "Task/Rest/DescribeMoldsTask.h"
#include "Task/WebSocket/DescribeMoldsTask.h"

// DescribeMoldsByUserId
#include "Request/DescribeMoldsByUserIdRequest.h"
#include "Result/DescribeMoldsByUserIdResult.h"
#include "Task/Rest/DescribeMoldsByUserIdTask.h"
#include "Task/WebSocket/DescribeMoldsByUserIdTask.h"

// GetMold
#include "Request/GetMoldRequest.h"
#include "Result/GetMoldResult.h"
#include "Task/Rest/GetMoldTask.h"
#include "Task/WebSocket/GetMoldTask.h"

// GetMoldByUserId
#include "Request/GetMoldByUserIdRequest.h"
#include "Result/GetMoldByUserIdResult.h"
#include "Task/Rest/GetMoldByUserIdTask.h"
#include "Task/WebSocket/GetMoldByUserIdTask.h"

// SetMoldCapacityByUserId
#include "Request/SetMoldCapacityByUserIdRequest.h"
#include "Result/SetMoldCapacityByUserIdResult.h"
#include "Task/Rest/SetMoldCapacityByUserIdTask.h"
#include "Task/WebSocket/SetMoldCapacityByUserIdTask.h"

// AddMoldCapacityByUserId
#include "Request/AddMoldCapacityByUserIdRequest.h"
#include "Result/AddMoldCapacityByUserIdResult.h"
#include "Task/Rest/AddMoldCapacityByUserIdTask.h"
#include "Task/WebSocket/AddMoldCapacityByUserIdTask.h"

// SubMoldCapacityByUserId
#include "Request/SubMoldCapacityByUserIdRequest.h"
#include "Result/SubMoldCapacityByUserIdResult.h"
#include "Task/Rest/SubMoldCapacityByUserIdTask.h"
#include "Task/WebSocket/SubMoldCapacityByUserIdTask.h"

// DeleteMold
#include "Request/DeleteMoldRequest.h"
#include "Result/DeleteMoldResult.h"
#include "Task/Rest/DeleteMoldTask.h"
#include "Task/WebSocket/DeleteMoldTask.h"

// DeleteMoldByUserId
#include "Request/DeleteMoldByUserIdRequest.h"
#include "Result/DeleteMoldByUserIdResult.h"
#include "Task/Rest/DeleteMoldByUserIdTask.h"
#include "Task/WebSocket/DeleteMoldByUserIdTask.h"

// AddCapacityByStampSheet
#include "Request/AddCapacityByStampSheetRequest.h"
#include "Result/AddCapacityByStampSheetResult.h"
#include "Task/Rest/AddCapacityByStampSheetTask.h"
#include "Task/WebSocket/AddCapacityByStampSheetTask.h"

// SubCapacityByStampTask
#include "Request/SubCapacityByStampTaskRequest.h"
#include "Result/SubCapacityByStampTaskResult.h"
#include "Task/Rest/SubCapacityByStampTaskTask.h"
#include "Task/WebSocket/SubCapacityByStampTaskTask.h"

// SetCapacityByStampSheet
#include "Request/SetCapacityByStampSheetRequest.h"
#include "Result/SetCapacityByStampSheetResult.h"
#include "Task/Rest/SetCapacityByStampSheetTask.h"
#include "Task/WebSocket/SetCapacityByStampSheetTask.h"

// DescribeForms
#include "Request/DescribeFormsRequest.h"
#include "Result/DescribeFormsResult.h"
#include "Task/Rest/DescribeFormsTask.h"
#include "Task/WebSocket/DescribeFormsTask.h"

// DescribeFormsByUserId
#include "Request/DescribeFormsByUserIdRequest.h"
#include "Result/DescribeFormsByUserIdResult.h"
#include "Task/Rest/DescribeFormsByUserIdTask.h"
#include "Task/WebSocket/DescribeFormsByUserIdTask.h"

// GetForm
#include "Request/GetFormRequest.h"
#include "Result/GetFormResult.h"
#include "Task/Rest/GetFormTask.h"
#include "Task/WebSocket/GetFormTask.h"

// GetFormByUserId
#include "Request/GetFormByUserIdRequest.h"
#include "Result/GetFormByUserIdResult.h"
#include "Task/Rest/GetFormByUserIdTask.h"
#include "Task/WebSocket/GetFormByUserIdTask.h"

// GetFormWithSignature
#include "Request/GetFormWithSignatureRequest.h"
#include "Result/GetFormWithSignatureResult.h"
#include "Task/Rest/GetFormWithSignatureTask.h"
#include "Task/WebSocket/GetFormWithSignatureTask.h"

// GetFormWithSignatureByUserId
#include "Request/GetFormWithSignatureByUserIdRequest.h"
#include "Result/GetFormWithSignatureByUserIdResult.h"
#include "Task/Rest/GetFormWithSignatureByUserIdTask.h"
#include "Task/WebSocket/GetFormWithSignatureByUserIdTask.h"

// SetFormByUserId
#include "Request/SetFormByUserIdRequest.h"
#include "Result/SetFormByUserIdResult.h"
#include "Task/Rest/SetFormByUserIdTask.h"
#include "Task/WebSocket/SetFormByUserIdTask.h"

// SetFormWithSignature
#include "Request/SetFormWithSignatureRequest.h"
#include "Result/SetFormWithSignatureResult.h"
#include "Task/Rest/SetFormWithSignatureTask.h"
#include "Task/WebSocket/SetFormWithSignatureTask.h"

// AcquireActionsToFormProperties
#include "Request/AcquireActionsToFormPropertiesRequest.h"
#include "Result/AcquireActionsToFormPropertiesResult.h"
#include "Task/Rest/AcquireActionsToFormPropertiesTask.h"
#include "Task/WebSocket/AcquireActionsToFormPropertiesTask.h"

// DeleteForm
#include "Request/DeleteFormRequest.h"
#include "Result/DeleteFormResult.h"
#include "Task/Rest/DeleteFormTask.h"
#include "Task/WebSocket/DeleteFormTask.h"

// DeleteFormByUserId
#include "Request/DeleteFormByUserIdRequest.h"
#include "Result/DeleteFormByUserIdResult.h"
#include "Task/Rest/DeleteFormByUserIdTask.h"
#include "Task/WebSocket/DeleteFormByUserIdTask.h"

// AcquireActionToFormPropertiesByStampSheet
#include "Request/AcquireActionToFormPropertiesByStampSheetRequest.h"
#include "Result/AcquireActionToFormPropertiesByStampSheetResult.h"
#include "Task/Rest/AcquireActionToFormPropertiesByStampSheetTask.h"
#include "Task/WebSocket/AcquireActionToFormPropertiesByStampSheetTask.h"

// DescribePropertyForms
#include "Request/DescribePropertyFormsRequest.h"
#include "Result/DescribePropertyFormsResult.h"
#include "Task/Rest/DescribePropertyFormsTask.h"
#include "Task/WebSocket/DescribePropertyFormsTask.h"

// DescribePropertyFormsByUserId
#include "Request/DescribePropertyFormsByUserIdRequest.h"
#include "Result/DescribePropertyFormsByUserIdResult.h"
#include "Task/Rest/DescribePropertyFormsByUserIdTask.h"
#include "Task/WebSocket/DescribePropertyFormsByUserIdTask.h"

// GetPropertyForm
#include "Request/GetPropertyFormRequest.h"
#include "Result/GetPropertyFormResult.h"
#include "Task/Rest/GetPropertyFormTask.h"
#include "Task/WebSocket/GetPropertyFormTask.h"

// GetPropertyFormByUserId
#include "Request/GetPropertyFormByUserIdRequest.h"
#include "Result/GetPropertyFormByUserIdResult.h"
#include "Task/Rest/GetPropertyFormByUserIdTask.h"
#include "Task/WebSocket/GetPropertyFormByUserIdTask.h"

// GetPropertyFormWithSignature
#include "Request/GetPropertyFormWithSignatureRequest.h"
#include "Result/GetPropertyFormWithSignatureResult.h"
#include "Task/Rest/GetPropertyFormWithSignatureTask.h"
#include "Task/WebSocket/GetPropertyFormWithSignatureTask.h"

// GetPropertyFormWithSignatureByUserId
#include "Request/GetPropertyFormWithSignatureByUserIdRequest.h"
#include "Result/GetPropertyFormWithSignatureByUserIdResult.h"
#include "Task/Rest/GetPropertyFormWithSignatureByUserIdTask.h"
#include "Task/WebSocket/GetPropertyFormWithSignatureByUserIdTask.h"

// SetPropertyFormByUserId
#include "Request/SetPropertyFormByUserIdRequest.h"
#include "Result/SetPropertyFormByUserIdResult.h"
#include "Task/Rest/SetPropertyFormByUserIdTask.h"
#include "Task/WebSocket/SetPropertyFormByUserIdTask.h"

// SetPropertyFormWithSignature
#include "Request/SetPropertyFormWithSignatureRequest.h"
#include "Result/SetPropertyFormWithSignatureResult.h"
#include "Task/Rest/SetPropertyFormWithSignatureTask.h"
#include "Task/WebSocket/SetPropertyFormWithSignatureTask.h"

// AcquireActionsToPropertyFormProperties
#include "Request/AcquireActionsToPropertyFormPropertiesRequest.h"
#include "Result/AcquireActionsToPropertyFormPropertiesResult.h"
#include "Task/Rest/AcquireActionsToPropertyFormPropertiesTask.h"
#include "Task/WebSocket/AcquireActionsToPropertyFormPropertiesTask.h"

// DeletePropertyForm
#include "Request/DeletePropertyFormRequest.h"
#include "Result/DeletePropertyFormResult.h"
#include "Task/Rest/DeletePropertyFormTask.h"
#include "Task/WebSocket/DeletePropertyFormTask.h"

// DeletePropertyFormByUserId
#include "Request/DeletePropertyFormByUserIdRequest.h"
#include "Result/DeletePropertyFormByUserIdResult.h"
#include "Task/Rest/DeletePropertyFormByUserIdTask.h"
#include "Task/WebSocket/DeletePropertyFormByUserIdTask.h"

// AcquireActionToPropertyFormPropertiesByStampSheet
#include "Request/AcquireActionToPropertyFormPropertiesByStampSheetRequest.h"
#include "Result/AcquireActionToPropertyFormPropertiesByStampSheetResult.h"
#include "Task/Rest/AcquireActionToPropertyFormPropertiesByStampSheetTask.h"
#include "Task/WebSocket/AcquireActionToPropertyFormPropertiesByStampSheetTask.h"

// Client
#include "Gs2FormationRestClient.h"
#include "Gs2FormationWebSocketClient.h"