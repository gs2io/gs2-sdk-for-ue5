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
#include "Model/IssueJob.h"
#include "Model/SerialKey.h"
#include "Model/CampaignModel.h"
#include "Model/CampaignModelMaster.h"
#include "Model/CurrentCampaignMaster.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"

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

// DescribeIssueJobs
#include "Request/DescribeIssueJobsRequest.h"
#include "Result/DescribeIssueJobsResult.h"
#include "Task/Rest/DescribeIssueJobsTask.h"
#include "Task/WebSocket/DescribeIssueJobsTask.h"

// GetIssueJob
#include "Request/GetIssueJobRequest.h"
#include "Result/GetIssueJobResult.h"
#include "Task/Rest/GetIssueJobTask.h"
#include "Task/WebSocket/GetIssueJobTask.h"

// Issue
#include "Request/IssueRequest.h"
#include "Result/IssueResult.h"
#include "Task/Rest/IssueTask.h"
#include "Task/WebSocket/IssueTask.h"

// DescribeSerialKeys
#include "Request/DescribeSerialKeysRequest.h"
#include "Result/DescribeSerialKeysResult.h"
#include "Task/Rest/DescribeSerialKeysTask.h"
#include "Task/WebSocket/DescribeSerialKeysTask.h"

// DownloadSerialCodes
#include "Request/DownloadSerialCodesRequest.h"
#include "Result/DownloadSerialCodesResult.h"
#include "Task/Rest/DownloadSerialCodesTask.h"
#include "Task/WebSocket/DownloadSerialCodesTask.h"

// IssueOnce
#include "Request/IssueOnceRequest.h"
#include "Result/IssueOnceResult.h"
#include "Task/Rest/IssueOnceTask.h"
#include "Task/WebSocket/IssueOnceTask.h"

// GetSerialKey
#include "Request/GetSerialKeyRequest.h"
#include "Result/GetSerialKeyResult.h"
#include "Task/Rest/GetSerialKeyTask.h"
#include "Task/WebSocket/GetSerialKeyTask.h"

// VerifyCode
#include "Request/VerifyCodeRequest.h"
#include "Result/VerifyCodeResult.h"
#include "Task/Rest/VerifyCodeTask.h"
#include "Task/WebSocket/VerifyCodeTask.h"

// VerifyCodeByUserId
#include "Request/VerifyCodeByUserIdRequest.h"
#include "Result/VerifyCodeByUserIdResult.h"
#include "Task/Rest/VerifyCodeByUserIdTask.h"
#include "Task/WebSocket/VerifyCodeByUserIdTask.h"

// Use
#include "Request/UseRequest.h"
#include "Result/UseResult.h"
#include "Task/Rest/UseTask.h"
#include "Task/WebSocket/UseTask.h"

// UseByUserId
#include "Request/UseByUserIdRequest.h"
#include "Result/UseByUserIdResult.h"
#include "Task/Rest/UseByUserIdTask.h"
#include "Task/WebSocket/UseByUserIdTask.h"

// RevertUseByUserId
#include "Request/RevertUseByUserIdRequest.h"
#include "Result/RevertUseByUserIdResult.h"
#include "Task/Rest/RevertUseByUserIdTask.h"
#include "Task/WebSocket/RevertUseByUserIdTask.h"

// UseByStampTask
#include "Request/UseByStampTaskRequest.h"
#include "Result/UseByStampTaskResult.h"
#include "Task/Rest/UseByStampTaskTask.h"
#include "Task/WebSocket/UseByStampTaskTask.h"

// RevertUseByStampSheet
#include "Request/RevertUseByStampSheetRequest.h"
#include "Result/RevertUseByStampSheetResult.h"
#include "Task/Rest/RevertUseByStampSheetTask.h"
#include "Task/WebSocket/RevertUseByStampSheetTask.h"

// VerifyByStampTask
#include "Request/VerifyByStampTaskRequest.h"
#include "Result/VerifyByStampTaskResult.h"
#include "Task/Rest/VerifyByStampTaskTask.h"
#include "Task/WebSocket/VerifyByStampTaskTask.h"

// DescribeCampaignModels
#include "Request/DescribeCampaignModelsRequest.h"
#include "Result/DescribeCampaignModelsResult.h"
#include "Task/Rest/DescribeCampaignModelsTask.h"
#include "Task/WebSocket/DescribeCampaignModelsTask.h"

// GetCampaignModel
#include "Request/GetCampaignModelRequest.h"
#include "Result/GetCampaignModelResult.h"
#include "Task/Rest/GetCampaignModelTask.h"
#include "Task/WebSocket/GetCampaignModelTask.h"

// DescribeCampaignModelMasters
#include "Request/DescribeCampaignModelMastersRequest.h"
#include "Result/DescribeCampaignModelMastersResult.h"
#include "Task/Rest/DescribeCampaignModelMastersTask.h"
#include "Task/WebSocket/DescribeCampaignModelMastersTask.h"

// CreateCampaignModelMaster
#include "Request/CreateCampaignModelMasterRequest.h"
#include "Result/CreateCampaignModelMasterResult.h"
#include "Task/Rest/CreateCampaignModelMasterTask.h"
#include "Task/WebSocket/CreateCampaignModelMasterTask.h"

// GetCampaignModelMaster
#include "Request/GetCampaignModelMasterRequest.h"
#include "Result/GetCampaignModelMasterResult.h"
#include "Task/Rest/GetCampaignModelMasterTask.h"
#include "Task/WebSocket/GetCampaignModelMasterTask.h"

// UpdateCampaignModelMaster
#include "Request/UpdateCampaignModelMasterRequest.h"
#include "Result/UpdateCampaignModelMasterResult.h"
#include "Task/Rest/UpdateCampaignModelMasterTask.h"
#include "Task/WebSocket/UpdateCampaignModelMasterTask.h"

// DeleteCampaignModelMaster
#include "Request/DeleteCampaignModelMasterRequest.h"
#include "Result/DeleteCampaignModelMasterResult.h"
#include "Task/Rest/DeleteCampaignModelMasterTask.h"
#include "Task/WebSocket/DeleteCampaignModelMasterTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentCampaignMaster
#include "Request/GetCurrentCampaignMasterRequest.h"
#include "Result/GetCurrentCampaignMasterResult.h"
#include "Task/Rest/GetCurrentCampaignMasterTask.h"
#include "Task/WebSocket/GetCurrentCampaignMasterTask.h"

// UpdateCurrentCampaignMaster
#include "Request/UpdateCurrentCampaignMasterRequest.h"
#include "Result/UpdateCurrentCampaignMasterResult.h"
#include "Task/Rest/UpdateCurrentCampaignMasterTask.h"
#include "Task/WebSocket/UpdateCurrentCampaignMasterTask.h"

// UpdateCurrentCampaignMasterFromGitHub
#include "Request/UpdateCurrentCampaignMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentCampaignMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentCampaignMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentCampaignMasterFromGitHubTask.h"

// Client
#include "Gs2SerialKeyRestClient.h"
#include "Gs2SerialKeyWebSocketClient.h"