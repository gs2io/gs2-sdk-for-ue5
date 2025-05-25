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
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"
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
#include "Request/DescribeExperienceModelMastersRequest.h"
#include "Task/WebSocket/DescribeExperienceModelMastersTask.h"
#include "Request/CreateExperienceModelMasterRequest.h"
#include "Task/WebSocket/CreateExperienceModelMasterTask.h"
#include "Request/GetExperienceModelMasterRequest.h"
#include "Task/WebSocket/GetExperienceModelMasterTask.h"
#include "Request/UpdateExperienceModelMasterRequest.h"
#include "Task/WebSocket/UpdateExperienceModelMasterTask.h"
#include "Request/DeleteExperienceModelMasterRequest.h"
#include "Task/WebSocket/DeleteExperienceModelMasterTask.h"
#include "Request/DescribeExperienceModelsRequest.h"
#include "Task/WebSocket/DescribeExperienceModelsTask.h"
#include "Request/GetExperienceModelRequest.h"
#include "Task/WebSocket/GetExperienceModelTask.h"
#include "Request/DescribeThresholdMastersRequest.h"
#include "Task/WebSocket/DescribeThresholdMastersTask.h"
#include "Request/CreateThresholdMasterRequest.h"
#include "Task/WebSocket/CreateThresholdMasterTask.h"
#include "Request/GetThresholdMasterRequest.h"
#include "Task/WebSocket/GetThresholdMasterTask.h"
#include "Request/UpdateThresholdMasterRequest.h"
#include "Task/WebSocket/UpdateThresholdMasterTask.h"
#include "Request/DeleteThresholdMasterRequest.h"
#include "Task/WebSocket/DeleteThresholdMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentExperienceMasterRequest.h"
#include "Task/WebSocket/GetCurrentExperienceMasterTask.h"
#include "Request/PreUpdateCurrentExperienceMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentExperienceMasterTask.h"
#include "Request/UpdateCurrentExperienceMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentExperienceMasterTask.h"
#include "Request/UpdateCurrentExperienceMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentExperienceMasterFromGitHubTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/WebSocket/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/WebSocket/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"
#include "Request/GetStatusWithSignatureRequest.h"
#include "Task/WebSocket/GetStatusWithSignatureTask.h"
#include "Request/GetStatusWithSignatureByUserIdRequest.h"
#include "Task/WebSocket/GetStatusWithSignatureByUserIdTask.h"
#include "Request/AddExperienceByUserIdRequest.h"
#include "Task/WebSocket/AddExperienceByUserIdTask.h"
#include "Request/SubExperienceRequest.h"
#include "Task/WebSocket/SubExperienceTask.h"
#include "Request/SubExperienceByUserIdRequest.h"
#include "Task/WebSocket/SubExperienceByUserIdTask.h"
#include "Request/SetExperienceByUserIdRequest.h"
#include "Task/WebSocket/SetExperienceByUserIdTask.h"
#include "Request/AddRankCapByUserIdRequest.h"
#include "Task/WebSocket/AddRankCapByUserIdTask.h"
#include "Request/SubRankCapRequest.h"
#include "Task/WebSocket/SubRankCapTask.h"
#include "Request/SubRankCapByUserIdRequest.h"
#include "Task/WebSocket/SubRankCapByUserIdTask.h"
#include "Request/SetRankCapByUserIdRequest.h"
#include "Task/WebSocket/SetRankCapByUserIdTask.h"
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Task/WebSocket/DeleteStatusByUserIdTask.h"
#include "Request/VerifyRankRequest.h"
#include "Task/WebSocket/VerifyRankTask.h"
#include "Request/VerifyRankByUserIdRequest.h"
#include "Task/WebSocket/VerifyRankByUserIdTask.h"
#include "Request/VerifyRankCapRequest.h"
#include "Task/WebSocket/VerifyRankCapTask.h"
#include "Request/VerifyRankCapByUserIdRequest.h"
#include "Task/WebSocket/VerifyRankCapByUserIdTask.h"
#include "Request/AddExperienceByStampSheetRequest.h"
#include "Task/WebSocket/AddExperienceByStampSheetTask.h"
#include "Request/SetExperienceByStampSheetRequest.h"
#include "Task/WebSocket/SetExperienceByStampSheetTask.h"
#include "Request/SubExperienceByStampTaskRequest.h"
#include "Task/WebSocket/SubExperienceByStampTaskTask.h"
#include "Request/AddRankCapByStampSheetRequest.h"
#include "Task/WebSocket/AddRankCapByStampSheetTask.h"
#include "Request/SubRankCapByStampTaskRequest.h"
#include "Task/WebSocket/SubRankCapByStampTaskTask.h"
#include "Request/SetRankCapByStampSheetRequest.h"
#include "Task/WebSocket/SetRankCapByStampSheetTask.h"
#include "Request/MultiplyAcquireActionsByUserIdRequest.h"
#include "Task/WebSocket/MultiplyAcquireActionsByUserIdTask.h"
#include "Request/MultiplyAcquireActionsByStampSheetRequest.h"
#include "Task/WebSocket/MultiplyAcquireActionsByStampSheetTask.h"
#include "Request/VerifyRankByStampTaskRequest.h"
#include "Task/WebSocket/VerifyRankByStampTaskTask.h"
#include "Request/VerifyRankCapByStampTaskRequest.h"
#include "Task/WebSocket/VerifyRankCapByStampTaskTask.h"

namespace Gs2::Experience
{
    class GS2EXPERIENCE_API FGs2ExperienceWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2ExperienceWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeExperienceModelMastersTask>> DescribeExperienceModelMasters(
            const Request::FDescribeExperienceModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateExperienceModelMasterTask>> CreateExperienceModelMaster(
            const Request::FCreateExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetExperienceModelMasterTask>> GetExperienceModelMaster(
            const Request::FGetExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateExperienceModelMasterTask>> UpdateExperienceModelMaster(
            const Request::FUpdateExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteExperienceModelMasterTask>> DeleteExperienceModelMaster(
            const Request::FDeleteExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeExperienceModelsTask>> DescribeExperienceModels(
            const Request::FDescribeExperienceModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetExperienceModelTask>> GetExperienceModel(
            const Request::FGetExperienceModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeThresholdMastersTask>> DescribeThresholdMasters(
            const Request::FDescribeThresholdMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateThresholdMasterTask>> CreateThresholdMaster(
            const Request::FCreateThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetThresholdMasterTask>> GetThresholdMaster(
            const Request::FGetThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateThresholdMasterTask>> UpdateThresholdMaster(
            const Request::FUpdateThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteThresholdMasterTask>> DeleteThresholdMaster(
            const Request::FDeleteThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentExperienceMasterTask>> GetCurrentExperienceMaster(
            const Request::FGetCurrentExperienceMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentExperienceMasterTask>> PreUpdateCurrentExperienceMaster(
            const Request::FPreUpdateCurrentExperienceMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentExperienceMasterTask>> UpdateCurrentExperienceMaster(
            const Request::FUpdateCurrentExperienceMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentExperienceMasterFromGitHubTask>> UpdateCurrentExperienceMasterFromGitHub(
            const Request::FUpdateCurrentExperienceMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesTask>> DescribeStatuses(
            const Request::FDescribeStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStatusesByUserIdTask>> DescribeStatusesByUserId(
            const Request::FDescribeStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusTask>> GetStatus(
            const Request::FGetStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusByUserIdTask>> GetStatusByUserId(
            const Request::FGetStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusWithSignatureTask>> GetStatusWithSignature(
            const Request::FGetStatusWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStatusWithSignatureByUserIdTask>> GetStatusWithSignatureByUserId(
            const Request::FGetStatusWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddExperienceByUserIdTask>> AddExperienceByUserId(
            const Request::FAddExperienceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubExperienceTask>> SubExperience(
            const Request::FSubExperienceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubExperienceByUserIdTask>> SubExperienceByUserId(
            const Request::FSubExperienceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetExperienceByUserIdTask>> SetExperienceByUserId(
            const Request::FSetExperienceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddRankCapByUserIdTask>> AddRankCapByUserId(
            const Request::FAddRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubRankCapTask>> SubRankCap(
            const Request::FSubRankCapRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubRankCapByUserIdTask>> SubRankCapByUserId(
            const Request::FSubRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRankCapByUserIdTask>> SetRankCapByUserId(
            const Request::FSetRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStatusByUserIdTask>> DeleteStatusByUserId(
            const Request::FDeleteStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRankTask>> VerifyRank(
            const Request::FVerifyRankRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRankByUserIdTask>> VerifyRankByUserId(
            const Request::FVerifyRankByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRankCapTask>> VerifyRankCap(
            const Request::FVerifyRankCapRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRankCapByUserIdTask>> VerifyRankCapByUserId(
            const Request::FVerifyRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddExperienceByStampSheetTask>> AddExperienceByStampSheet(
            const Request::FAddExperienceByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetExperienceByStampSheetTask>> SetExperienceByStampSheet(
            const Request::FSetExperienceByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubExperienceByStampTaskTask>> SubExperienceByStampTask(
            const Request::FSubExperienceByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddRankCapByStampSheetTask>> AddRankCapByStampSheet(
            const Request::FAddRankCapByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubRankCapByStampTaskTask>> SubRankCapByStampTask(
            const Request::FSubRankCapByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRankCapByStampSheetTask>> SetRankCapByStampSheet(
            const Request::FSetRankCapByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMultiplyAcquireActionsByUserIdTask>> MultiplyAcquireActionsByUserId(
            const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMultiplyAcquireActionsByStampSheetTask>> MultiplyAcquireActionsByStampSheet(
            const Request::FMultiplyAcquireActionsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRankByStampTaskTask>> VerifyRankByStampTask(
            const Request::FVerifyRankByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRankCapByStampTaskTask>> VerifyRankCapByStampTask(
            const Request::FVerifyRankCapByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ExperienceWebSocketClient, ESPMode::ThreadSafe> FGs2ExperienceWebSocketClientPtr;
}