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
#include "Model/Account.h"
#include "Model/TakeOver.h"
#include "Model/PlatformId.h"
#include "Model/DataOwner.h"
#include "Model/TakeOverTypeModel.h"
#include "Model/TakeOverTypeModelMaster.h"
#include "Model/CurrentModelMaster.h"
#include "Model/OpenIdConnectSetting.h"
#include "Model/ScopeValue.h"
#include "Model/PlatformUser.h"
#include "Model/BanStatus.h"
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

// DescribeAccounts
#include "Request/DescribeAccountsRequest.h"
#include "Result/DescribeAccountsResult.h"
#include "Task/Rest/DescribeAccountsTask.h"
#include "Task/WebSocket/DescribeAccountsTask.h"

// CreateAccount
#include "Request/CreateAccountRequest.h"
#include "Result/CreateAccountResult.h"
#include "Task/Rest/CreateAccountTask.h"
#include "Task/WebSocket/CreateAccountTask.h"

// UpdateTimeOffset
#include "Request/UpdateTimeOffsetRequest.h"
#include "Result/UpdateTimeOffsetResult.h"
#include "Task/Rest/UpdateTimeOffsetTask.h"
#include "Task/WebSocket/UpdateTimeOffsetTask.h"

// UpdateBanned
#include "Request/UpdateBannedRequest.h"
#include "Result/UpdateBannedResult.h"
#include "Task/Rest/UpdateBannedTask.h"
#include "Task/WebSocket/UpdateBannedTask.h"

// AddBan
#include "Request/AddBanRequest.h"
#include "Result/AddBanResult.h"
#include "Task/Rest/AddBanTask.h"
#include "Task/WebSocket/AddBanTask.h"

// RemoveBan
#include "Request/RemoveBanRequest.h"
#include "Result/RemoveBanResult.h"
#include "Task/Rest/RemoveBanTask.h"
#include "Task/WebSocket/RemoveBanTask.h"

// GetAccount
#include "Request/GetAccountRequest.h"
#include "Result/GetAccountResult.h"
#include "Task/Rest/GetAccountTask.h"
#include "Task/WebSocket/GetAccountTask.h"

// DeleteAccount
#include "Request/DeleteAccountRequest.h"
#include "Result/DeleteAccountResult.h"
#include "Task/Rest/DeleteAccountTask.h"
#include "Task/WebSocket/DeleteAccountTask.h"

// Authentication
#include "Request/AuthenticationRequest.h"
#include "Result/AuthenticationResult.h"
#include "Task/Rest/AuthenticationTask.h"
#include "Task/WebSocket/AuthenticationTask.h"

// DescribeTakeOvers
#include "Request/DescribeTakeOversRequest.h"
#include "Result/DescribeTakeOversResult.h"
#include "Task/Rest/DescribeTakeOversTask.h"
#include "Task/WebSocket/DescribeTakeOversTask.h"

// DescribeTakeOversByUserId
#include "Request/DescribeTakeOversByUserIdRequest.h"
#include "Result/DescribeTakeOversByUserIdResult.h"
#include "Task/Rest/DescribeTakeOversByUserIdTask.h"
#include "Task/WebSocket/DescribeTakeOversByUserIdTask.h"

// CreateTakeOver
#include "Request/CreateTakeOverRequest.h"
#include "Result/CreateTakeOverResult.h"
#include "Task/Rest/CreateTakeOverTask.h"
#include "Task/WebSocket/CreateTakeOverTask.h"

// CreateTakeOverByUserId
#include "Request/CreateTakeOverByUserIdRequest.h"
#include "Result/CreateTakeOverByUserIdResult.h"
#include "Task/Rest/CreateTakeOverByUserIdTask.h"
#include "Task/WebSocket/CreateTakeOverByUserIdTask.h"

// CreateTakeOverOpenIdConnect
#include "Request/CreateTakeOverOpenIdConnectRequest.h"
#include "Result/CreateTakeOverOpenIdConnectResult.h"
#include "Task/Rest/CreateTakeOverOpenIdConnectTask.h"
#include "Task/WebSocket/CreateTakeOverOpenIdConnectTask.h"

// CreateTakeOverOpenIdConnectAndByUserId
#include "Request/CreateTakeOverOpenIdConnectAndByUserIdRequest.h"
#include "Result/CreateTakeOverOpenIdConnectAndByUserIdResult.h"
#include "Task/Rest/CreateTakeOverOpenIdConnectAndByUserIdTask.h"
#include "Task/WebSocket/CreateTakeOverOpenIdConnectAndByUserIdTask.h"

// GetTakeOver
#include "Request/GetTakeOverRequest.h"
#include "Result/GetTakeOverResult.h"
#include "Task/Rest/GetTakeOverTask.h"
#include "Task/WebSocket/GetTakeOverTask.h"

// GetTakeOverByUserId
#include "Request/GetTakeOverByUserIdRequest.h"
#include "Result/GetTakeOverByUserIdResult.h"
#include "Task/Rest/GetTakeOverByUserIdTask.h"
#include "Task/WebSocket/GetTakeOverByUserIdTask.h"

// UpdateTakeOver
#include "Request/UpdateTakeOverRequest.h"
#include "Result/UpdateTakeOverResult.h"
#include "Task/Rest/UpdateTakeOverTask.h"
#include "Task/WebSocket/UpdateTakeOverTask.h"

// UpdateTakeOverByUserId
#include "Request/UpdateTakeOverByUserIdRequest.h"
#include "Result/UpdateTakeOverByUserIdResult.h"
#include "Task/Rest/UpdateTakeOverByUserIdTask.h"
#include "Task/WebSocket/UpdateTakeOverByUserIdTask.h"

// DeleteTakeOver
#include "Request/DeleteTakeOverRequest.h"
#include "Result/DeleteTakeOverResult.h"
#include "Task/Rest/DeleteTakeOverTask.h"
#include "Task/WebSocket/DeleteTakeOverTask.h"

// DeleteTakeOverByUserIdentifier
#include "Request/DeleteTakeOverByUserIdentifierRequest.h"
#include "Result/DeleteTakeOverByUserIdentifierResult.h"
#include "Task/Rest/DeleteTakeOverByUserIdentifierTask.h"
#include "Task/WebSocket/DeleteTakeOverByUserIdentifierTask.h"

// DeleteTakeOverByUserId
#include "Request/DeleteTakeOverByUserIdRequest.h"
#include "Result/DeleteTakeOverByUserIdResult.h"
#include "Task/Rest/DeleteTakeOverByUserIdTask.h"
#include "Task/WebSocket/DeleteTakeOverByUserIdTask.h"

// DoTakeOver
#include "Request/DoTakeOverRequest.h"
#include "Result/DoTakeOverResult.h"
#include "Task/Rest/DoTakeOverTask.h"
#include "Task/WebSocket/DoTakeOverTask.h"

// DoTakeOverOpenIdConnect
#include "Request/DoTakeOverOpenIdConnectRequest.h"
#include "Result/DoTakeOverOpenIdConnectResult.h"
#include "Task/Rest/DoTakeOverOpenIdConnectTask.h"
#include "Task/WebSocket/DoTakeOverOpenIdConnectTask.h"

// GetAuthorizationUrl
#include "Request/GetAuthorizationUrlRequest.h"
#include "Result/GetAuthorizationUrlResult.h"
#include "Task/Rest/GetAuthorizationUrlTask.h"
#include "Task/WebSocket/GetAuthorizationUrlTask.h"

// DescribePlatformIds
#include "Request/DescribePlatformIdsRequest.h"
#include "Result/DescribePlatformIdsResult.h"
#include "Task/Rest/DescribePlatformIdsTask.h"
#include "Task/WebSocket/DescribePlatformIdsTask.h"

// DescribePlatformIdsByUserId
#include "Request/DescribePlatformIdsByUserIdRequest.h"
#include "Result/DescribePlatformIdsByUserIdResult.h"
#include "Task/Rest/DescribePlatformIdsByUserIdTask.h"
#include "Task/WebSocket/DescribePlatformIdsByUserIdTask.h"

// CreatePlatformId
#include "Request/CreatePlatformIdRequest.h"
#include "Result/CreatePlatformIdResult.h"
#include "Task/Rest/CreatePlatformIdTask.h"
#include "Task/WebSocket/CreatePlatformIdTask.h"

// CreatePlatformIdByUserId
#include "Request/CreatePlatformIdByUserIdRequest.h"
#include "Result/CreatePlatformIdByUserIdResult.h"
#include "Task/Rest/CreatePlatformIdByUserIdTask.h"
#include "Task/WebSocket/CreatePlatformIdByUserIdTask.h"

// GetPlatformId
#include "Request/GetPlatformIdRequest.h"
#include "Result/GetPlatformIdResult.h"
#include "Task/Rest/GetPlatformIdTask.h"
#include "Task/WebSocket/GetPlatformIdTask.h"

// GetPlatformIdByUserId
#include "Request/GetPlatformIdByUserIdRequest.h"
#include "Result/GetPlatformIdByUserIdResult.h"
#include "Task/Rest/GetPlatformIdByUserIdTask.h"
#include "Task/WebSocket/GetPlatformIdByUserIdTask.h"

// FindPlatformId
#include "Request/FindPlatformIdRequest.h"
#include "Result/FindPlatformIdResult.h"
#include "Task/Rest/FindPlatformIdTask.h"
#include "Task/WebSocket/FindPlatformIdTask.h"

// FindPlatformIdByUserId
#include "Request/FindPlatformIdByUserIdRequest.h"
#include "Result/FindPlatformIdByUserIdResult.h"
#include "Task/Rest/FindPlatformIdByUserIdTask.h"
#include "Task/WebSocket/FindPlatformIdByUserIdTask.h"

// DeletePlatformId
#include "Request/DeletePlatformIdRequest.h"
#include "Result/DeletePlatformIdResult.h"
#include "Task/Rest/DeletePlatformIdTask.h"
#include "Task/WebSocket/DeletePlatformIdTask.h"

// DeletePlatformIdByUserIdentifier
#include "Request/DeletePlatformIdByUserIdentifierRequest.h"
#include "Result/DeletePlatformIdByUserIdentifierResult.h"
#include "Task/Rest/DeletePlatformIdByUserIdentifierTask.h"
#include "Task/WebSocket/DeletePlatformIdByUserIdentifierTask.h"

// DeletePlatformIdByUserId
#include "Request/DeletePlatformIdByUserIdRequest.h"
#include "Result/DeletePlatformIdByUserIdResult.h"
#include "Task/Rest/DeletePlatformIdByUserIdTask.h"
#include "Task/WebSocket/DeletePlatformIdByUserIdTask.h"

// GetDataOwnerByUserId
#include "Request/GetDataOwnerByUserIdRequest.h"
#include "Result/GetDataOwnerByUserIdResult.h"
#include "Task/Rest/GetDataOwnerByUserIdTask.h"
#include "Task/WebSocket/GetDataOwnerByUserIdTask.h"

// DeleteDataOwnerByUserId
#include "Request/DeleteDataOwnerByUserIdRequest.h"
#include "Result/DeleteDataOwnerByUserIdResult.h"
#include "Task/Rest/DeleteDataOwnerByUserIdTask.h"
#include "Task/WebSocket/DeleteDataOwnerByUserIdTask.h"

// DescribeTakeOverTypeModels
#include "Request/DescribeTakeOverTypeModelsRequest.h"
#include "Result/DescribeTakeOverTypeModelsResult.h"
#include "Task/Rest/DescribeTakeOverTypeModelsTask.h"
#include "Task/WebSocket/DescribeTakeOverTypeModelsTask.h"

// GetTakeOverTypeModel
#include "Request/GetTakeOverTypeModelRequest.h"
#include "Result/GetTakeOverTypeModelResult.h"
#include "Task/Rest/GetTakeOverTypeModelTask.h"
#include "Task/WebSocket/GetTakeOverTypeModelTask.h"

// DescribeTakeOverTypeModelMasters
#include "Request/DescribeTakeOverTypeModelMastersRequest.h"
#include "Result/DescribeTakeOverTypeModelMastersResult.h"
#include "Task/Rest/DescribeTakeOverTypeModelMastersTask.h"
#include "Task/WebSocket/DescribeTakeOverTypeModelMastersTask.h"

// CreateTakeOverTypeModelMaster
#include "Request/CreateTakeOverTypeModelMasterRequest.h"
#include "Result/CreateTakeOverTypeModelMasterResult.h"
#include "Task/Rest/CreateTakeOverTypeModelMasterTask.h"
#include "Task/WebSocket/CreateTakeOverTypeModelMasterTask.h"

// GetTakeOverTypeModelMaster
#include "Request/GetTakeOverTypeModelMasterRequest.h"
#include "Result/GetTakeOverTypeModelMasterResult.h"
#include "Task/Rest/GetTakeOverTypeModelMasterTask.h"
#include "Task/WebSocket/GetTakeOverTypeModelMasterTask.h"

// UpdateTakeOverTypeModelMaster
#include "Request/UpdateTakeOverTypeModelMasterRequest.h"
#include "Result/UpdateTakeOverTypeModelMasterResult.h"
#include "Task/Rest/UpdateTakeOverTypeModelMasterTask.h"
#include "Task/WebSocket/UpdateTakeOverTypeModelMasterTask.h"

// DeleteTakeOverTypeModelMaster
#include "Request/DeleteTakeOverTypeModelMasterRequest.h"
#include "Result/DeleteTakeOverTypeModelMasterResult.h"
#include "Task/Rest/DeleteTakeOverTypeModelMasterTask.h"
#include "Task/WebSocket/DeleteTakeOverTypeModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentModelMaster
#include "Request/GetCurrentModelMasterRequest.h"
#include "Result/GetCurrentModelMasterResult.h"
#include "Task/Rest/GetCurrentModelMasterTask.h"
#include "Task/WebSocket/GetCurrentModelMasterTask.h"

// PreUpdateCurrentModelMaster
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Result/PreUpdateCurrentModelMasterResult.h"
#include "Task/Rest/PreUpdateCurrentModelMasterTask.h"
#include "Task/WebSocket/PreUpdateCurrentModelMasterTask.h"

// UpdateCurrentModelMaster
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Result/UpdateCurrentModelMasterResult.h"
#include "Task/Rest/UpdateCurrentModelMasterTask.h"
#include "Task/WebSocket/UpdateCurrentModelMasterTask.h"

// UpdateCurrentModelMasterFromGitHub
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentModelMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentModelMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentModelMasterFromGitHubTask.h"

// Client
#include "Gs2AccountRestClient.h"
#include "Gs2AccountWebSocketClient.h"