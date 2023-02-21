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
#include "Request/DescribeStaminaModelMastersRequest.h"
#include "Task/WebSocket/DescribeStaminaModelMastersTask.h"
#include "Request/CreateStaminaModelMasterRequest.h"
#include "Task/WebSocket/CreateStaminaModelMasterTask.h"
#include "Request/GetStaminaModelMasterRequest.h"
#include "Task/WebSocket/GetStaminaModelMasterTask.h"
#include "Request/UpdateStaminaModelMasterRequest.h"
#include "Task/WebSocket/UpdateStaminaModelMasterTask.h"
#include "Request/DeleteStaminaModelMasterRequest.h"
#include "Task/WebSocket/DeleteStaminaModelMasterTask.h"
#include "Request/DescribeMaxStaminaTableMastersRequest.h"
#include "Task/WebSocket/DescribeMaxStaminaTableMastersTask.h"
#include "Request/CreateMaxStaminaTableMasterRequest.h"
#include "Task/WebSocket/CreateMaxStaminaTableMasterTask.h"
#include "Request/GetMaxStaminaTableMasterRequest.h"
#include "Task/WebSocket/GetMaxStaminaTableMasterTask.h"
#include "Request/UpdateMaxStaminaTableMasterRequest.h"
#include "Task/WebSocket/UpdateMaxStaminaTableMasterTask.h"
#include "Request/DeleteMaxStaminaTableMasterRequest.h"
#include "Task/WebSocket/DeleteMaxStaminaTableMasterTask.h"
#include "Request/DescribeRecoverIntervalTableMastersRequest.h"
#include "Task/WebSocket/DescribeRecoverIntervalTableMastersTask.h"
#include "Request/CreateRecoverIntervalTableMasterRequest.h"
#include "Task/WebSocket/CreateRecoverIntervalTableMasterTask.h"
#include "Request/GetRecoverIntervalTableMasterRequest.h"
#include "Task/WebSocket/GetRecoverIntervalTableMasterTask.h"
#include "Request/UpdateRecoverIntervalTableMasterRequest.h"
#include "Task/WebSocket/UpdateRecoverIntervalTableMasterTask.h"
#include "Request/DeleteRecoverIntervalTableMasterRequest.h"
#include "Task/WebSocket/DeleteRecoverIntervalTableMasterTask.h"
#include "Request/DescribeRecoverValueTableMastersRequest.h"
#include "Task/WebSocket/DescribeRecoverValueTableMastersTask.h"
#include "Request/CreateRecoverValueTableMasterRequest.h"
#include "Task/WebSocket/CreateRecoverValueTableMasterTask.h"
#include "Request/GetRecoverValueTableMasterRequest.h"
#include "Task/WebSocket/GetRecoverValueTableMasterTask.h"
#include "Request/UpdateRecoverValueTableMasterRequest.h"
#include "Task/WebSocket/UpdateRecoverValueTableMasterTask.h"
#include "Request/DeleteRecoverValueTableMasterRequest.h"
#include "Task/WebSocket/DeleteRecoverValueTableMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentStaminaMasterRequest.h"
#include "Task/WebSocket/GetCurrentStaminaMasterTask.h"
#include "Request/UpdateCurrentStaminaMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentStaminaMasterTask.h"
#include "Request/UpdateCurrentStaminaMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentStaminaMasterFromGitHubTask.h"
#include "Request/DescribeStaminaModelsRequest.h"
#include "Task/WebSocket/DescribeStaminaModelsTask.h"
#include "Request/GetStaminaModelRequest.h"
#include "Task/WebSocket/GetStaminaModelTask.h"
#include "Request/DescribeStaminasRequest.h"
#include "Task/WebSocket/DescribeStaminasTask.h"
#include "Request/DescribeStaminasByUserIdRequest.h"
#include "Task/WebSocket/DescribeStaminasByUserIdTask.h"
#include "Request/GetStaminaRequest.h"
#include "Task/WebSocket/GetStaminaTask.h"
#include "Request/GetStaminaByUserIdRequest.h"
#include "Task/WebSocket/GetStaminaByUserIdTask.h"
#include "Request/UpdateStaminaByUserIdRequest.h"
#include "Task/WebSocket/UpdateStaminaByUserIdTask.h"
#include "Request/ConsumeStaminaRequest.h"
#include "Task/WebSocket/ConsumeStaminaTask.h"
#include "Request/ConsumeStaminaByUserIdRequest.h"
#include "Task/WebSocket/ConsumeStaminaByUserIdTask.h"
#include "Request/RecoverStaminaByUserIdRequest.h"
#include "Task/WebSocket/RecoverStaminaByUserIdTask.h"
#include "Request/RaiseMaxValueByUserIdRequest.h"
#include "Task/WebSocket/RaiseMaxValueByUserIdTask.h"
#include "Request/SetMaxValueByUserIdRequest.h"
#include "Task/WebSocket/SetMaxValueByUserIdTask.h"
#include "Request/SetRecoverIntervalByUserIdRequest.h"
#include "Task/WebSocket/SetRecoverIntervalByUserIdTask.h"
#include "Request/SetRecoverValueByUserIdRequest.h"
#include "Task/WebSocket/SetRecoverValueByUserIdTask.h"
#include "Request/SetMaxValueByStatusRequest.h"
#include "Task/WebSocket/SetMaxValueByStatusTask.h"
#include "Request/SetRecoverIntervalByStatusRequest.h"
#include "Task/WebSocket/SetRecoverIntervalByStatusTask.h"
#include "Request/SetRecoverValueByStatusRequest.h"
#include "Task/WebSocket/SetRecoverValueByStatusTask.h"
#include "Request/DeleteStaminaByUserIdRequest.h"
#include "Task/WebSocket/DeleteStaminaByUserIdTask.h"
#include "Request/RecoverStaminaByStampSheetRequest.h"
#include "Task/WebSocket/RecoverStaminaByStampSheetTask.h"
#include "Request/RaiseMaxValueByStampSheetRequest.h"
#include "Task/WebSocket/RaiseMaxValueByStampSheetTask.h"
#include "Request/SetMaxValueByStampSheetRequest.h"
#include "Task/WebSocket/SetMaxValueByStampSheetTask.h"
#include "Request/SetRecoverIntervalByStampSheetRequest.h"
#include "Task/WebSocket/SetRecoverIntervalByStampSheetTask.h"
#include "Request/SetRecoverValueByStampSheetRequest.h"
#include "Task/WebSocket/SetRecoverValueByStampSheetTask.h"
#include "Request/ConsumeStaminaByStampTaskRequest.h"
#include "Task/WebSocket/ConsumeStaminaByStampTaskTask.h"

namespace Gs2::Stamina
{
    class GS2STAMINA_API FGs2StaminaWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2StaminaWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminaModelMastersTask>> DescribeStaminaModelMasters(
            const Request::FDescribeStaminaModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateStaminaModelMasterTask>> CreateStaminaModelMaster(
            const Request::FCreateStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaModelMasterTask>> GetStaminaModelMaster(
            const Request::FGetStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStaminaModelMasterTask>> UpdateStaminaModelMaster(
            const Request::FUpdateStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStaminaModelMasterTask>> DeleteStaminaModelMaster(
            const Request::FDeleteStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMaxStaminaTableMastersTask>> DescribeMaxStaminaTableMasters(
            const Request::FDescribeMaxStaminaTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMaxStaminaTableMasterTask>> CreateMaxStaminaTableMaster(
            const Request::FCreateMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMaxStaminaTableMasterTask>> GetMaxStaminaTableMaster(
            const Request::FGetMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMaxStaminaTableMasterTask>> UpdateMaxStaminaTableMaster(
            const Request::FUpdateMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMaxStaminaTableMasterTask>> DeleteMaxStaminaTableMaster(
            const Request::FDeleteMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRecoverIntervalTableMastersTask>> DescribeRecoverIntervalTableMasters(
            const Request::FDescribeRecoverIntervalTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRecoverIntervalTableMasterTask>> CreateRecoverIntervalTableMaster(
            const Request::FCreateRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRecoverIntervalTableMasterTask>> GetRecoverIntervalTableMaster(
            const Request::FGetRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRecoverIntervalTableMasterTask>> UpdateRecoverIntervalTableMaster(
            const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRecoverIntervalTableMasterTask>> DeleteRecoverIntervalTableMaster(
            const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRecoverValueTableMastersTask>> DescribeRecoverValueTableMasters(
            const Request::FDescribeRecoverValueTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRecoverValueTableMasterTask>> CreateRecoverValueTableMaster(
            const Request::FCreateRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRecoverValueTableMasterTask>> GetRecoverValueTableMaster(
            const Request::FGetRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRecoverValueTableMasterTask>> UpdateRecoverValueTableMaster(
            const Request::FUpdateRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRecoverValueTableMasterTask>> DeleteRecoverValueTableMaster(
            const Request::FDeleteRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentStaminaMasterTask>> GetCurrentStaminaMaster(
            const Request::FGetCurrentStaminaMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentStaminaMasterTask>> UpdateCurrentStaminaMaster(
            const Request::FUpdateCurrentStaminaMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentStaminaMasterFromGitHubTask>> UpdateCurrentStaminaMasterFromGitHub(
            const Request::FUpdateCurrentStaminaMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminaModelsTask>> DescribeStaminaModels(
            const Request::FDescribeStaminaModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaModelTask>> GetStaminaModel(
            const Request::FGetStaminaModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminasTask>> DescribeStaminas(
            const Request::FDescribeStaminasRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminasByUserIdTask>> DescribeStaminasByUserId(
            const Request::FDescribeStaminasByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaTask>> GetStamina(
            const Request::FGetStaminaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaByUserIdTask>> GetStaminaByUserId(
            const Request::FGetStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStaminaByUserIdTask>> UpdateStaminaByUserId(
            const Request::FUpdateStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeStaminaTask>> ConsumeStamina(
            const Request::FConsumeStaminaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeStaminaByUserIdTask>> ConsumeStaminaByUserId(
            const Request::FConsumeStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRecoverStaminaByUserIdTask>> RecoverStaminaByUserId(
            const Request::FRecoverStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRaiseMaxValueByUserIdTask>> RaiseMaxValueByUserId(
            const Request::FRaiseMaxValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaxValueByUserIdTask>> SetMaxValueByUserId(
            const Request::FSetMaxValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByUserIdTask>> SetRecoverIntervalByUserId(
            const Request::FSetRecoverIntervalByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverValueByUserIdTask>> SetRecoverValueByUserId(
            const Request::FSetRecoverValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaxValueByStatusTask>> SetMaxValueByStatus(
            const Request::FSetMaxValueByStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByStatusTask>> SetRecoverIntervalByStatus(
            const Request::FSetRecoverIntervalByStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverValueByStatusTask>> SetRecoverValueByStatus(
            const Request::FSetRecoverValueByStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStaminaByUserIdTask>> DeleteStaminaByUserId(
            const Request::FDeleteStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRecoverStaminaByStampSheetTask>> RecoverStaminaByStampSheet(
            const Request::FRecoverStaminaByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRaiseMaxValueByStampSheetTask>> RaiseMaxValueByStampSheet(
            const Request::FRaiseMaxValueByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaxValueByStampSheetTask>> SetMaxValueByStampSheet(
            const Request::FSetMaxValueByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByStampSheetTask>> SetRecoverIntervalByStampSheet(
            const Request::FSetRecoverIntervalByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverValueByStampSheetTask>> SetRecoverValueByStampSheet(
            const Request::FSetRecoverValueByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeStaminaByStampTaskTask>> ConsumeStaminaByStampTask(
            const Request::FConsumeStaminaByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2StaminaWebSocketClient, ESPMode::ThreadSafe> FGs2StaminaWebSocketClientPtr;
}