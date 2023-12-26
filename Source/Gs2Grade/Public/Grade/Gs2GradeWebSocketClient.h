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
#include "Request/DescribeGradeModelMastersRequest.h"
#include "Task/WebSocket/DescribeGradeModelMastersTask.h"
#include "Request/CreateGradeModelMasterRequest.h"
#include "Task/WebSocket/CreateGradeModelMasterTask.h"
#include "Request/GetGradeModelMasterRequest.h"
#include "Task/WebSocket/GetGradeModelMasterTask.h"
#include "Request/UpdateGradeModelMasterRequest.h"
#include "Task/WebSocket/UpdateGradeModelMasterTask.h"
#include "Request/DeleteGradeModelMasterRequest.h"
#include "Task/WebSocket/DeleteGradeModelMasterTask.h"
#include "Request/DescribeGradeModelsRequest.h"
#include "Task/WebSocket/DescribeGradeModelsTask.h"
#include "Request/GetGradeModelRequest.h"
#include "Task/WebSocket/GetGradeModelTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/WebSocket/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/WebSocket/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/WebSocket/GetStatusByUserIdTask.h"
#include "Request/AddGradeByUserIdRequest.h"
#include "Task/WebSocket/AddGradeByUserIdTask.h"
#include "Request/SubGradeByUserIdRequest.h"
#include "Task/WebSocket/SubGradeByUserIdTask.h"
#include "Request/SetGradeByUserIdRequest.h"
#include "Task/WebSocket/SetGradeByUserIdTask.h"
#include "Request/ApplyRankCapRequest.h"
#include "Task/WebSocket/ApplyRankCapTask.h"
#include "Request/ApplyRankCapByUserIdRequest.h"
#include "Task/WebSocket/ApplyRankCapByUserIdTask.h"
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Task/WebSocket/DeleteStatusByUserIdTask.h"
#include "Request/VerifyGradeRequest.h"
#include "Task/WebSocket/VerifyGradeTask.h"
#include "Request/VerifyGradeByUserIdRequest.h"
#include "Task/WebSocket/VerifyGradeByUserIdTask.h"
#include "Request/VerifyGradeUpMaterialRequest.h"
#include "Task/WebSocket/VerifyGradeUpMaterialTask.h"
#include "Request/VerifyGradeUpMaterialByUserIdRequest.h"
#include "Task/WebSocket/VerifyGradeUpMaterialByUserIdTask.h"
#include "Request/AddGradeByStampSheetRequest.h"
#include "Task/WebSocket/AddGradeByStampSheetTask.h"
#include "Request/ApplyRankCapByStampSheetRequest.h"
#include "Task/WebSocket/ApplyRankCapByStampSheetTask.h"
#include "Request/SubGradeByStampTaskRequest.h"
#include "Task/WebSocket/SubGradeByStampTaskTask.h"
#include "Request/MultiplyAcquireActionsByUserIdRequest.h"
#include "Task/WebSocket/MultiplyAcquireActionsByUserIdTask.h"
#include "Request/MultiplyAcquireActionsByStampSheetRequest.h"
#include "Task/WebSocket/MultiplyAcquireActionsByStampSheetTask.h"
#include "Request/VerifyGradeByStampTaskRequest.h"
#include "Task/WebSocket/VerifyGradeByStampTaskTask.h"
#include "Request/VerifyGradeUpMaterialByStampTaskRequest.h"
#include "Task/WebSocket/VerifyGradeUpMaterialByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentGradeMasterRequest.h"
#include "Task/WebSocket/GetCurrentGradeMasterTask.h"
#include "Request/UpdateCurrentGradeMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentGradeMasterTask.h"
#include "Request/UpdateCurrentGradeMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentGradeMasterFromGitHubTask.h"

namespace Gs2::Grade
{
    class GS2GRADE_API FGs2GradeWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2GradeWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGradeModelMastersTask>> DescribeGradeModelMasters(
            const Request::FDescribeGradeModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGradeModelMasterTask>> CreateGradeModelMaster(
            const Request::FCreateGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGradeModelMasterTask>> GetGradeModelMaster(
            const Request::FGetGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGradeModelMasterTask>> UpdateGradeModelMaster(
            const Request::FUpdateGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGradeModelMasterTask>> DeleteGradeModelMaster(
            const Request::FDeleteGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGradeModelsTask>> DescribeGradeModels(
            const Request::FDescribeGradeModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGradeModelTask>> GetGradeModel(
            const Request::FGetGradeModelRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddGradeByUserIdTask>> AddGradeByUserId(
            const Request::FAddGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubGradeByUserIdTask>> SubGradeByUserId(
            const Request::FSubGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetGradeByUserIdTask>> SetGradeByUserId(
            const Request::FSetGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FApplyRankCapTask>> ApplyRankCap(
            const Request::FApplyRankCapRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FApplyRankCapByUserIdTask>> ApplyRankCapByUserId(
            const Request::FApplyRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStatusByUserIdTask>> DeleteStatusByUserId(
            const Request::FDeleteStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGradeTask>> VerifyGrade(
            const Request::FVerifyGradeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGradeByUserIdTask>> VerifyGradeByUserId(
            const Request::FVerifyGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGradeUpMaterialTask>> VerifyGradeUpMaterial(
            const Request::FVerifyGradeUpMaterialRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGradeUpMaterialByUserIdTask>> VerifyGradeUpMaterialByUserId(
            const Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddGradeByStampSheetTask>> AddGradeByStampSheet(
            const Request::FAddGradeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FApplyRankCapByStampSheetTask>> ApplyRankCapByStampSheet(
            const Request::FApplyRankCapByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubGradeByStampTaskTask>> SubGradeByStampTask(
            const Request::FSubGradeByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMultiplyAcquireActionsByUserIdTask>> MultiplyAcquireActionsByUserId(
            const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FMultiplyAcquireActionsByStampSheetTask>> MultiplyAcquireActionsByStampSheet(
            const Request::FMultiplyAcquireActionsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGradeByStampTaskTask>> VerifyGradeByStampTask(
            const Request::FVerifyGradeByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyGradeUpMaterialByStampTaskTask>> VerifyGradeUpMaterialByStampTask(
            const Request::FVerifyGradeUpMaterialByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentGradeMasterTask>> GetCurrentGradeMaster(
            const Request::FGetCurrentGradeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentGradeMasterTask>> UpdateCurrentGradeMaster(
            const Request::FUpdateCurrentGradeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentGradeMasterFromGitHubTask>> UpdateCurrentGradeMasterFromGitHub(
            const Request::FUpdateCurrentGradeMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2GradeWebSocketClient, ESPMode::ThreadSafe> FGs2GradeWebSocketClientPtr;
}