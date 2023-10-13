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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeBonusModelMastersRequest.h"
#include "Task/Rest/DescribeBonusModelMastersTask.h"
#include "Request/CreateBonusModelMasterRequest.h"
#include "Task/Rest/CreateBonusModelMasterTask.h"
#include "Request/GetBonusModelMasterRequest.h"
#include "Task/Rest/GetBonusModelMasterTask.h"
#include "Request/UpdateBonusModelMasterRequest.h"
#include "Task/Rest/UpdateBonusModelMasterTask.h"
#include "Request/DeleteBonusModelMasterRequest.h"
#include "Task/Rest/DeleteBonusModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentBonusMasterRequest.h"
#include "Task/Rest/GetCurrentBonusMasterTask.h"
#include "Request/UpdateCurrentBonusMasterRequest.h"
#include "Task/Rest/UpdateCurrentBonusMasterTask.h"
#include "Request/UpdateCurrentBonusMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentBonusMasterFromGitHubTask.h"
#include "Request/DescribeBonusModelsRequest.h"
#include "Task/Rest/DescribeBonusModelsTask.h"
#include "Request/GetBonusModelRequest.h"
#include "Task/Rest/GetBonusModelTask.h"
#include "Request/ReceiveRequest.h"
#include "Task/Rest/ReceiveTask.h"
#include "Request/ReceiveByUserIdRequest.h"
#include "Task/Rest/ReceiveByUserIdTask.h"
#include "Request/MissedReceiveRequest.h"
#include "Task/Rest/MissedReceiveTask.h"
#include "Request/MissedReceiveByUserIdRequest.h"
#include "Task/Rest/MissedReceiveByUserIdTask.h"
#include "Request/DescribeReceiveStatusesRequest.h"
#include "Task/Rest/DescribeReceiveStatusesTask.h"
#include "Request/DescribeReceiveStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeReceiveStatusesByUserIdTask.h"
#include "Request/GetReceiveStatusRequest.h"
#include "Task/Rest/GetReceiveStatusTask.h"
#include "Request/GetReceiveStatusByUserIdRequest.h"
#include "Task/Rest/GetReceiveStatusByUserIdTask.h"
#include "Request/DeleteReceiveStatusByUserIdRequest.h"
#include "Task/Rest/DeleteReceiveStatusByUserIdTask.h"
#include "Request/DeleteReceiveStatusByStampSheetRequest.h"
#include "Task/Rest/DeleteReceiveStatusByStampSheetTask.h"
#include "Request/MarkReceivedRequest.h"
#include "Task/Rest/MarkReceivedTask.h"
#include "Request/MarkReceivedByUserIdRequest.h"
#include "Task/Rest/MarkReceivedByUserIdTask.h"
#include "Request/UnmarkReceivedByUserIdRequest.h"
#include "Task/Rest/UnmarkReceivedByUserIdTask.h"
#include "Request/MarkReceivedByStampTaskRequest.h"
#include "Task/Rest/MarkReceivedByStampTaskTask.h"
#include "Request/UnmarkReceivedByStampSheetRequest.h"
#include "Task/Rest/UnmarkReceivedByStampSheetTask.h"

namespace Gs2::LoginReward
{
    class GS2LOGINREWARD_API FGs2LoginRewardRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2LoginRewardRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBonusModelMastersTask>> DescribeBonusModelMasters(
            const Request::FDescribeBonusModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateBonusModelMasterTask>> CreateBonusModelMaster(
            const Request::FCreateBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBonusModelMasterTask>> GetBonusModelMaster(
            const Request::FGetBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateBonusModelMasterTask>> UpdateBonusModelMaster(
            const Request::FUpdateBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteBonusModelMasterTask>> DeleteBonusModelMaster(
            const Request::FDeleteBonusModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentBonusMasterTask>> GetCurrentBonusMaster(
            const Request::FGetCurrentBonusMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentBonusMasterTask>> UpdateCurrentBonusMaster(
            const Request::FUpdateCurrentBonusMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentBonusMasterFromGitHubTask>> UpdateCurrentBonusMasterFromGitHub(
            const Request::FUpdateCurrentBonusMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBonusModelsTask>> DescribeBonusModels(
            const Request::FDescribeBonusModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBonusModelTask>> GetBonusModel(
            const Request::FGetBonusModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveTask>> Receive(
            const Request::FReceiveRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveByUserIdTask>> ReceiveByUserId(
            const Request::FReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMissedReceiveTask>> MissedReceive(
            const Request::FMissedReceiveRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMissedReceiveByUserIdTask>> MissedReceiveByUserId(
            const Request::FMissedReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveStatusesTask>> DescribeReceiveStatuses(
            const Request::FDescribeReceiveStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveStatusesByUserIdTask>> DescribeReceiveStatusesByUserId(
            const Request::FDescribeReceiveStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveStatusTask>> GetReceiveStatus(
            const Request::FGetReceiveStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveStatusByUserIdTask>> GetReceiveStatusByUserId(
            const Request::FGetReceiveStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteReceiveStatusByUserIdTask>> DeleteReceiveStatusByUserId(
            const Request::FDeleteReceiveStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteReceiveStatusByStampSheetTask>> DeleteReceiveStatusByStampSheet(
            const Request::FDeleteReceiveStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkReceivedTask>> MarkReceived(
            const Request::FMarkReceivedRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkReceivedByUserIdTask>> MarkReceivedByUserId(
            const Request::FMarkReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnmarkReceivedByUserIdTask>> UnmarkReceivedByUserId(
            const Request::FUnmarkReceivedByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkReceivedByStampTaskTask>> MarkReceivedByStampTask(
            const Request::FMarkReceivedByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnmarkReceivedByStampSheetTask>> UnmarkReceivedByStampSheet(
            const Request::FUnmarkReceivedByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LoginRewardRestClient, ESPMode::ThreadSafe> FGs2LoginRewardRestClientPtr;
}