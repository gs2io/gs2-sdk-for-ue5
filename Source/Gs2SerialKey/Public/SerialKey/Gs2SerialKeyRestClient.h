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
#include "Core/Net/AbstractGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Request/DescribeIssueJobsRequest.h"
#include "Task/Rest/DescribeIssueJobsTask.h"
#include "Request/GetIssueJobRequest.h"
#include "Task/Rest/GetIssueJobTask.h"
#include "Request/IssueRequest.h"
#include "Task/Rest/IssueTask.h"
#include "Request/DescribeSerialKeysRequest.h"
#include "Task/Rest/DescribeSerialKeysTask.h"
#include "Request/DownloadSerialCodesRequest.h"
#include "Task/Rest/DownloadSerialCodesTask.h"
#include "Request/GetSerialKeyRequest.h"
#include "Task/Rest/GetSerialKeyTask.h"
#include "Request/UseRequest.h"
#include "Task/Rest/UseTask.h"
#include "Request/UseByUserIdRequest.h"
#include "Task/Rest/UseByUserIdTask.h"
#include "Request/RevertUseByUserIdRequest.h"
#include "Task/Rest/RevertUseByUserIdTask.h"
#include "Request/UseByStampTaskRequest.h"
#include "Task/Rest/UseByStampTaskTask.h"
#include "Request/RevertUseByStampSheetRequest.h"
#include "Task/Rest/RevertUseByStampSheetTask.h"
#include "Request/DescribeCampaignModelsRequest.h"
#include "Task/Rest/DescribeCampaignModelsTask.h"
#include "Request/GetCampaignModelRequest.h"
#include "Task/Rest/GetCampaignModelTask.h"
#include "Request/DescribeCampaignModelMastersRequest.h"
#include "Task/Rest/DescribeCampaignModelMastersTask.h"
#include "Request/CreateCampaignModelMasterRequest.h"
#include "Task/Rest/CreateCampaignModelMasterTask.h"
#include "Request/GetCampaignModelMasterRequest.h"
#include "Task/Rest/GetCampaignModelMasterTask.h"
#include "Request/UpdateCampaignModelMasterRequest.h"
#include "Task/Rest/UpdateCampaignModelMasterTask.h"
#include "Request/DeleteCampaignModelMasterRequest.h"
#include "Task/Rest/DeleteCampaignModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentCampaignMasterRequest.h"
#include "Task/Rest/GetCurrentCampaignMasterTask.h"
#include "Request/UpdateCurrentCampaignMasterRequest.h"
#include "Task/Rest/UpdateCurrentCampaignMasterTask.h"
#include "Request/UpdateCurrentCampaignMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentCampaignMasterFromGitHubTask.h"

namespace Gs2::SerialKey
{
    class GS2SERIALKEY_API FGs2SerialKeyRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2SerialKeyRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeIssueJobsTask>> DescribeIssueJobs(
            const Request::FDescribeIssueJobsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetIssueJobTask>> GetIssueJob(
            const Request::FGetIssueJobRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIssueTask>> Issue(
            const Request::FIssueRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSerialKeysTask>> DescribeSerialKeys(
            const Request::FDescribeSerialKeysRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDownloadSerialCodesTask>> DownloadSerialCodes(
            const Request::FDownloadSerialCodesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSerialKeyTask>> GetSerialKey(
            const Request::FGetSerialKeyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUseTask>> Use(
            const Request::FUseRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUseByUserIdTask>> UseByUserId(
            const Request::FUseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRevertUseByUserIdTask>> RevertUseByUserId(
            const Request::FRevertUseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUseByStampTaskTask>> UseByStampTask(
            const Request::FUseByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRevertUseByStampSheetTask>> RevertUseByStampSheet(
            const Request::FRevertUseByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCampaignModelsTask>> DescribeCampaignModels(
            const Request::FDescribeCampaignModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCampaignModelTask>> GetCampaignModel(
            const Request::FGetCampaignModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCampaignModelMastersTask>> DescribeCampaignModelMasters(
            const Request::FDescribeCampaignModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateCampaignModelMasterTask>> CreateCampaignModelMaster(
            const Request::FCreateCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCampaignModelMasterTask>> GetCampaignModelMaster(
            const Request::FGetCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCampaignModelMasterTask>> UpdateCampaignModelMaster(
            const Request::FUpdateCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCampaignModelMasterTask>> DeleteCampaignModelMaster(
            const Request::FDeleteCampaignModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentCampaignMasterTask>> GetCurrentCampaignMaster(
            const Request::FGetCurrentCampaignMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentCampaignMasterTask>> UpdateCurrentCampaignMaster(
            const Request::FUpdateCurrentCampaignMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentCampaignMasterFromGitHubTask>> UpdateCurrentCampaignMasterFromGitHub(
            const Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2SerialKeyRestClient, ESPMode::ThreadSafe> FGs2SerialKeyRestClientPtr;
}