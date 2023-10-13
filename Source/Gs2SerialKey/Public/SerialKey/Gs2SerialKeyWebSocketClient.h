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

#include "CoreMinimal.h"
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/WebSocket/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/WebSocket/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeIssueJobsRequest.h"
#include "Task/WebSocket/DescribeIssueJobsTask.h"
#include "Request/GetIssueJobRequest.h"
#include "Task/WebSocket/GetIssueJobTask.h"
#include "Request/IssueRequest.h"
#include "Task/WebSocket/IssueTask.h"
#include "Request/DescribeSerialKeysRequest.h"
#include "Task/WebSocket/DescribeSerialKeysTask.h"
#include "Request/DownloadSerialCodesRequest.h"
#include "Task/WebSocket/DownloadSerialCodesTask.h"
#include "Request/GetSerialKeyRequest.h"
#include "Task/WebSocket/GetSerialKeyTask.h"
#include "Request/UseRequest.h"
#include "Task/WebSocket/UseTask.h"
#include "Request/UseByUserIdRequest.h"
#include "Task/WebSocket/UseByUserIdTask.h"
#include "Request/RevertUseByUserIdRequest.h"
#include "Task/WebSocket/RevertUseByUserIdTask.h"
#include "Request/UseByStampTaskRequest.h"
#include "Task/WebSocket/UseByStampTaskTask.h"
#include "Request/RevertUseByStampSheetRequest.h"
#include "Task/WebSocket/RevertUseByStampSheetTask.h"
#include "Request/DescribeCampaignModelsRequest.h"
#include "Task/WebSocket/DescribeCampaignModelsTask.h"
#include "Request/GetCampaignModelRequest.h"
#include "Task/WebSocket/GetCampaignModelTask.h"
#include "Request/DescribeCampaignModelMastersRequest.h"
#include "Task/WebSocket/DescribeCampaignModelMastersTask.h"
#include "Request/CreateCampaignModelMasterRequest.h"
#include "Task/WebSocket/CreateCampaignModelMasterTask.h"
#include "Request/GetCampaignModelMasterRequest.h"
#include "Task/WebSocket/GetCampaignModelMasterTask.h"
#include "Request/UpdateCampaignModelMasterRequest.h"
#include "Task/WebSocket/UpdateCampaignModelMasterTask.h"
#include "Request/DeleteCampaignModelMasterRequest.h"
#include "Task/WebSocket/DeleteCampaignModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentCampaignMasterRequest.h"
#include "Task/WebSocket/GetCurrentCampaignMasterTask.h"
#include "Request/UpdateCurrentCampaignMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentCampaignMasterTask.h"
#include "Request/UpdateCurrentCampaignMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentCampaignMasterFromGitHubTask.h"

namespace Gs2::SerialKey
{
    class GS2SERIALKEY_API FGs2SerialKeyWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2SerialKeyWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIssueJobsTask>> DescribeIssueJobs(
            const Request::FDescribeIssueJobsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetIssueJobTask>> GetIssueJob(
            const Request::FGetIssueJobRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIssueTask>> Issue(
            const Request::FIssueRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSerialKeysTask>> DescribeSerialKeys(
            const Request::FDescribeSerialKeysRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDownloadSerialCodesTask>> DownloadSerialCodes(
            const Request::FDownloadSerialCodesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSerialKeyTask>> GetSerialKey(
            const Request::FGetSerialKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUseTask>> Use(
            const Request::FUseRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUseByUserIdTask>> UseByUserId(
            const Request::FUseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRevertUseByUserIdTask>> RevertUseByUserId(
            const Request::FRevertUseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUseByStampTaskTask>> UseByStampTask(
            const Request::FUseByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRevertUseByStampSheetTask>> RevertUseByStampSheet(
            const Request::FRevertUseByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCampaignModelsTask>> DescribeCampaignModels(
            const Request::FDescribeCampaignModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCampaignModelTask>> GetCampaignModel(
            const Request::FGetCampaignModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCampaignModelMastersTask>> DescribeCampaignModelMasters(
            const Request::FDescribeCampaignModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateCampaignModelMasterTask>> CreateCampaignModelMaster(
            const Request::FCreateCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCampaignModelMasterTask>> GetCampaignModelMaster(
            const Request::FGetCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCampaignModelMasterTask>> UpdateCampaignModelMaster(
            const Request::FUpdateCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCampaignModelMasterTask>> DeleteCampaignModelMaster(
            const Request::FDeleteCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentCampaignMasterTask>> GetCurrentCampaignMaster(
            const Request::FGetCurrentCampaignMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentCampaignMasterTask>> UpdateCurrentCampaignMaster(
            const Request::FUpdateCurrentCampaignMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentCampaignMasterFromGitHubTask>> UpdateCurrentCampaignMasterFromGitHub(
            const Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2SerialKeyWebSocketClient, ESPMode::ThreadSafe> FGs2SerialKeyWebSocketClientPtr;
}