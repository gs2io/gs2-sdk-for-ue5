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
#include "Request/DescribeRateModelsRequest.h"
#include "Task/WebSocket/DescribeRateModelsTask.h"
#include "Request/GetRateModelRequest.h"
#include "Task/WebSocket/GetRateModelTask.h"
#include "Request/DescribeRateModelMastersRequest.h"
#include "Task/WebSocket/DescribeRateModelMastersTask.h"
#include "Request/CreateRateModelMasterRequest.h"
#include "Task/WebSocket/CreateRateModelMasterTask.h"
#include "Request/GetRateModelMasterRequest.h"
#include "Task/WebSocket/GetRateModelMasterTask.h"
#include "Request/UpdateRateModelMasterRequest.h"
#include "Task/WebSocket/UpdateRateModelMasterTask.h"
#include "Request/DeleteRateModelMasterRequest.h"
#include "Task/WebSocket/DeleteRateModelMasterTask.h"
#include "Request/DescribeUnleashRateModelsRequest.h"
#include "Task/WebSocket/DescribeUnleashRateModelsTask.h"
#include "Request/GetUnleashRateModelRequest.h"
#include "Task/WebSocket/GetUnleashRateModelTask.h"
#include "Request/DescribeUnleashRateModelMastersRequest.h"
#include "Task/WebSocket/DescribeUnleashRateModelMastersTask.h"
#include "Request/CreateUnleashRateModelMasterRequest.h"
#include "Task/WebSocket/CreateUnleashRateModelMasterTask.h"
#include "Request/GetUnleashRateModelMasterRequest.h"
#include "Task/WebSocket/GetUnleashRateModelMasterTask.h"
#include "Request/UpdateUnleashRateModelMasterRequest.h"
#include "Task/WebSocket/UpdateUnleashRateModelMasterTask.h"
#include "Request/DeleteUnleashRateModelMasterRequest.h"
#include "Task/WebSocket/DeleteUnleashRateModelMasterTask.h"
#include "Request/DirectEnhanceRequest.h"
#include "Task/WebSocket/DirectEnhanceTask.h"
#include "Request/DirectEnhanceByUserIdRequest.h"
#include "Task/WebSocket/DirectEnhanceByUserIdTask.h"
#include "Request/DirectEnhanceByStampSheetRequest.h"
#include "Task/WebSocket/DirectEnhanceByStampSheetTask.h"
#include "Request/UnleashRequest.h"
#include "Task/WebSocket/UnleashTask.h"
#include "Request/UnleashByUserIdRequest.h"
#include "Task/WebSocket/UnleashByUserIdTask.h"
#include "Request/UnleashByStampSheetRequest.h"
#include "Task/WebSocket/UnleashByStampSheetTask.h"
#include "Request/CreateProgressByUserIdRequest.h"
#include "Task/WebSocket/CreateProgressByUserIdTask.h"
#include "Request/GetProgressRequest.h"
#include "Task/WebSocket/GetProgressTask.h"
#include "Request/GetProgressByUserIdRequest.h"
#include "Task/WebSocket/GetProgressByUserIdTask.h"
#include "Request/StartRequest.h"
#include "Task/WebSocket/StartTask.h"
#include "Request/StartByUserIdRequest.h"
#include "Task/WebSocket/StartByUserIdTask.h"
#include "Request/EndRequest.h"
#include "Task/WebSocket/EndTask.h"
#include "Request/EndByUserIdRequest.h"
#include "Task/WebSocket/EndByUserIdTask.h"
#include "Request/DeleteProgressRequest.h"
#include "Task/WebSocket/DeleteProgressTask.h"
#include "Request/DeleteProgressByUserIdRequest.h"
#include "Task/WebSocket/DeleteProgressByUserIdTask.h"
#include "Request/CreateProgressByStampSheetRequest.h"
#include "Task/WebSocket/CreateProgressByStampSheetTask.h"
#include "Request/DeleteProgressByStampTaskRequest.h"
#include "Task/WebSocket/DeleteProgressByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentRateMasterRequest.h"
#include "Task/WebSocket/GetCurrentRateMasterTask.h"
#include "Request/PreUpdateCurrentRateMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentRateMasterTask.h"
#include "Request/UpdateCurrentRateMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentRateMasterFromGitHubTask.h"

namespace Gs2::Enhance
{
    class GS2ENHANCE_API FGs2EnhanceWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2EnhanceWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRateModelsTask>> DescribeRateModels(
            const Request::FDescribeRateModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRateModelTask>> GetRateModel(
            const Request::FGetRateModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRateModelMastersTask>> DescribeRateModelMasters(
            const Request::FDescribeRateModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRateModelMasterTask>> CreateRateModelMaster(
            const Request::FCreateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRateModelMasterTask>> GetRateModelMaster(
            const Request::FGetRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRateModelMasterTask>> UpdateRateModelMaster(
            const Request::FUpdateRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRateModelMasterTask>> DeleteRateModelMaster(
            const Request::FDeleteRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeUnleashRateModelsTask>> DescribeUnleashRateModels(
            const Request::FDescribeUnleashRateModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetUnleashRateModelTask>> GetUnleashRateModel(
            const Request::FGetUnleashRateModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeUnleashRateModelMastersTask>> DescribeUnleashRateModelMasters(
            const Request::FDescribeUnleashRateModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateUnleashRateModelMasterTask>> CreateUnleashRateModelMaster(
            const Request::FCreateUnleashRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetUnleashRateModelMasterTask>> GetUnleashRateModelMaster(
            const Request::FGetUnleashRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateUnleashRateModelMasterTask>> UpdateUnleashRateModelMaster(
            const Request::FUpdateUnleashRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteUnleashRateModelMasterTask>> DeleteUnleashRateModelMaster(
            const Request::FDeleteUnleashRateModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDirectEnhanceTask>> DirectEnhance(
            const Request::FDirectEnhanceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDirectEnhanceByUserIdTask>> DirectEnhanceByUserId(
            const Request::FDirectEnhanceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDirectEnhanceByStampSheetTask>> DirectEnhanceByStampSheet(
            const Request::FDirectEnhanceByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnleashTask>> Unleash(
            const Request::FUnleashRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnleashByUserIdTask>> UnleashByUserId(
            const Request::FUnleashByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnleashByStampSheetTask>> UnleashByStampSheet(
            const Request::FUnleashByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateProgressByUserIdTask>> CreateProgressByUserId(
            const Request::FCreateProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProgressTask>> GetProgress(
            const Request::FGetProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProgressByUserIdTask>> GetProgressByUserId(
            const Request::FGetProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FStartTask>> Start(
            const Request::FStartRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FStartByUserIdTask>> StartByUserId(
            const Request::FStartByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEndTask>> End(
            const Request::FEndRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FEndByUserIdTask>> EndByUserId(
            const Request::FEndByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProgressTask>> DeleteProgress(
            const Request::FDeleteProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProgressByUserIdTask>> DeleteProgressByUserId(
            const Request::FDeleteProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateProgressByStampSheetTask>> CreateProgressByStampSheet(
            const Request::FCreateProgressByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProgressByStampTaskTask>> DeleteProgressByStampTask(
            const Request::FDeleteProgressByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRateMasterTask>> GetCurrentRateMaster(
            const Request::FGetCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentRateMasterTask>> PreUpdateCurrentRateMaster(
            const Request::FPreUpdateCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterTask>> UpdateCurrentRateMaster(
            const Request::FUpdateCurrentRateMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterFromGitHubTask>> UpdateCurrentRateMasterFromGitHub(
            const Request::FUpdateCurrentRateMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2EnhanceWebSocketClient, ESPMode::ThreadSafe> FGs2EnhanceWebSocketClientPtr;
}