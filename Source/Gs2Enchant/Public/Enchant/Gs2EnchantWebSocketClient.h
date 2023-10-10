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
#include "Request/DescribeBalanceParameterModelsRequest.h"
#include "Task/WebSocket/DescribeBalanceParameterModelsTask.h"
#include "Request/GetBalanceParameterModelRequest.h"
#include "Task/WebSocket/GetBalanceParameterModelTask.h"
#include "Request/DescribeBalanceParameterModelMastersRequest.h"
#include "Task/WebSocket/DescribeBalanceParameterModelMastersTask.h"
#include "Request/CreateBalanceParameterModelMasterRequest.h"
#include "Task/WebSocket/CreateBalanceParameterModelMasterTask.h"
#include "Request/GetBalanceParameterModelMasterRequest.h"
#include "Task/WebSocket/GetBalanceParameterModelMasterTask.h"
#include "Request/UpdateBalanceParameterModelMasterRequest.h"
#include "Task/WebSocket/UpdateBalanceParameterModelMasterTask.h"
#include "Request/DeleteBalanceParameterModelMasterRequest.h"
#include "Task/WebSocket/DeleteBalanceParameterModelMasterTask.h"
#include "Request/DescribeRarityParameterModelsRequest.h"
#include "Task/WebSocket/DescribeRarityParameterModelsTask.h"
#include "Request/GetRarityParameterModelRequest.h"
#include "Task/WebSocket/GetRarityParameterModelTask.h"
#include "Request/DescribeRarityParameterModelMastersRequest.h"
#include "Task/WebSocket/DescribeRarityParameterModelMastersTask.h"
#include "Request/CreateRarityParameterModelMasterRequest.h"
#include "Task/WebSocket/CreateRarityParameterModelMasterTask.h"
#include "Request/GetRarityParameterModelMasterRequest.h"
#include "Task/WebSocket/GetRarityParameterModelMasterTask.h"
#include "Request/UpdateRarityParameterModelMasterRequest.h"
#include "Task/WebSocket/UpdateRarityParameterModelMasterTask.h"
#include "Request/DeleteRarityParameterModelMasterRequest.h"
#include "Task/WebSocket/DeleteRarityParameterModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentParameterMasterRequest.h"
#include "Task/WebSocket/GetCurrentParameterMasterTask.h"
#include "Request/UpdateCurrentParameterMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentParameterMasterTask.h"
#include "Request/UpdateCurrentParameterMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentParameterMasterFromGitHubTask.h"
#include "Request/DescribeBalanceParameterStatusesRequest.h"
#include "Task/WebSocket/DescribeBalanceParameterStatusesTask.h"
#include "Request/DescribeBalanceParameterStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeBalanceParameterStatusesByUserIdTask.h"
#include "Request/GetBalanceParameterStatusRequest.h"
#include "Task/WebSocket/GetBalanceParameterStatusTask.h"
#include "Request/GetBalanceParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/GetBalanceParameterStatusByUserIdTask.h"
#include "Request/DeleteBalanceParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/DeleteBalanceParameterStatusByUserIdTask.h"
#include "Request/ReDrawBalanceParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/ReDrawBalanceParameterStatusByUserIdTask.h"
#include "Request/ReDrawBalanceParameterStatusByStampSheetRequest.h"
#include "Task/WebSocket/ReDrawBalanceParameterStatusByStampSheetTask.h"
#include "Request/SetBalanceParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/SetBalanceParameterStatusByUserIdTask.h"
#include "Request/SetBalanceParameterStatusByStampSheetRequest.h"
#include "Task/WebSocket/SetBalanceParameterStatusByStampSheetTask.h"
#include "Request/DescribeRarityParameterStatusesRequest.h"
#include "Task/WebSocket/DescribeRarityParameterStatusesTask.h"
#include "Request/DescribeRarityParameterStatusesByUserIdRequest.h"
#include "Task/WebSocket/DescribeRarityParameterStatusesByUserIdTask.h"
#include "Request/GetRarityParameterStatusRequest.h"
#include "Task/WebSocket/GetRarityParameterStatusTask.h"
#include "Request/GetRarityParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/GetRarityParameterStatusByUserIdTask.h"
#include "Request/DeleteRarityParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/DeleteRarityParameterStatusByUserIdTask.h"
#include "Request/ReDrawRarityParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/ReDrawRarityParameterStatusByUserIdTask.h"
#include "Request/ReDrawRarityParameterStatusByStampSheetRequest.h"
#include "Task/WebSocket/ReDrawRarityParameterStatusByStampSheetTask.h"
#include "Request/AddRarityParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/AddRarityParameterStatusByUserIdTask.h"
#include "Request/AddRarityParameterStatusByStampSheetRequest.h"
#include "Task/WebSocket/AddRarityParameterStatusByStampSheetTask.h"
#include "Request/VerifyRarityParameterStatusRequest.h"
#include "Task/WebSocket/VerifyRarityParameterStatusTask.h"
#include "Request/VerifyRarityParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/VerifyRarityParameterStatusByUserIdTask.h"
#include "Request/VerifyRarityParameterStatusByStampTaskRequest.h"
#include "Task/WebSocket/VerifyRarityParameterStatusByStampTaskTask.h"
#include "Request/SetRarityParameterStatusByUserIdRequest.h"
#include "Task/WebSocket/SetRarityParameterStatusByUserIdTask.h"
#include "Request/SetRarityParameterStatusByStampSheetRequest.h"
#include "Task/WebSocket/SetRarityParameterStatusByStampSheetTask.h"

namespace Gs2::Enchant
{
    class GS2ENCHANT_API FGs2EnchantWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2EnchantWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterModelsTask>> DescribeBalanceParameterModels(
            const Request::FDescribeBalanceParameterModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterModelTask>> GetBalanceParameterModel(
            const Request::FGetBalanceParameterModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterModelMastersTask>> DescribeBalanceParameterModelMasters(
            const Request::FDescribeBalanceParameterModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBalanceParameterModelMasterTask>> CreateBalanceParameterModelMaster(
            const Request::FCreateBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterModelMasterTask>> GetBalanceParameterModelMaster(
            const Request::FGetBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBalanceParameterModelMasterTask>> UpdateBalanceParameterModelMaster(
            const Request::FUpdateBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBalanceParameterModelMasterTask>> DeleteBalanceParameterModelMaster(
            const Request::FDeleteBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterModelsTask>> DescribeRarityParameterModels(
            const Request::FDescribeRarityParameterModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterModelTask>> GetRarityParameterModel(
            const Request::FGetRarityParameterModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterModelMastersTask>> DescribeRarityParameterModelMasters(
            const Request::FDescribeRarityParameterModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRarityParameterModelMasterTask>> CreateRarityParameterModelMaster(
            const Request::FCreateRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterModelMasterTask>> GetRarityParameterModelMaster(
            const Request::FGetRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRarityParameterModelMasterTask>> UpdateRarityParameterModelMaster(
            const Request::FUpdateRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRarityParameterModelMasterTask>> DeleteRarityParameterModelMaster(
            const Request::FDeleteRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentParameterMasterTask>> GetCurrentParameterMaster(
            const Request::FGetCurrentParameterMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentParameterMasterTask>> UpdateCurrentParameterMaster(
            const Request::FUpdateCurrentParameterMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentParameterMasterFromGitHubTask>> UpdateCurrentParameterMasterFromGitHub(
            const Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterStatusesTask>> DescribeBalanceParameterStatuses(
            const Request::FDescribeBalanceParameterStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterStatusesByUserIdTask>> DescribeBalanceParameterStatusesByUserId(
            const Request::FDescribeBalanceParameterStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterStatusTask>> GetBalanceParameterStatus(
            const Request::FGetBalanceParameterStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterStatusByUserIdTask>> GetBalanceParameterStatusByUserId(
            const Request::FGetBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBalanceParameterStatusByUserIdTask>> DeleteBalanceParameterStatusByUserId(
            const Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawBalanceParameterStatusByUserIdTask>> ReDrawBalanceParameterStatusByUserId(
            const Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawBalanceParameterStatusByStampSheetTask>> ReDrawBalanceParameterStatusByStampSheet(
            const Request::FReDrawBalanceParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetBalanceParameterStatusByUserIdTask>> SetBalanceParameterStatusByUserId(
            const Request::FSetBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetBalanceParameterStatusByStampSheetTask>> SetBalanceParameterStatusByStampSheet(
            const Request::FSetBalanceParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterStatusesTask>> DescribeRarityParameterStatuses(
            const Request::FDescribeRarityParameterStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterStatusesByUserIdTask>> DescribeRarityParameterStatusesByUserId(
            const Request::FDescribeRarityParameterStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterStatusTask>> GetRarityParameterStatus(
            const Request::FGetRarityParameterStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterStatusByUserIdTask>> GetRarityParameterStatusByUserId(
            const Request::FGetRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRarityParameterStatusByUserIdTask>> DeleteRarityParameterStatusByUserId(
            const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawRarityParameterStatusByUserIdTask>> ReDrawRarityParameterStatusByUserId(
            const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawRarityParameterStatusByStampSheetTask>> ReDrawRarityParameterStatusByStampSheet(
            const Request::FReDrawRarityParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddRarityParameterStatusByUserIdTask>> AddRarityParameterStatusByUserId(
            const Request::FAddRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddRarityParameterStatusByStampSheetTask>> AddRarityParameterStatusByStampSheet(
            const Request::FAddRarityParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusTask>> VerifyRarityParameterStatus(
            const Request::FVerifyRarityParameterStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusByUserIdTask>> VerifyRarityParameterStatusByUserId(
            const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusByStampTaskTask>> VerifyRarityParameterStatusByStampTask(
            const Request::FVerifyRarityParameterStatusByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRarityParameterStatusByUserIdTask>> SetRarityParameterStatusByUserId(
            const Request::FSetRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRarityParameterStatusByStampSheetTask>> SetRarityParameterStatusByStampSheet(
            const Request::FSetRarityParameterStatusByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2EnchantWebSocketClient, ESPMode::ThreadSafe> FGs2EnchantWebSocketClientPtr;
}