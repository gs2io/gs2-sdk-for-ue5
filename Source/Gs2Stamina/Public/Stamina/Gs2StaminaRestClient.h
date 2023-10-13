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
#include "Request/DescribeStaminaModelMastersRequest.h"
#include "Task/Rest/DescribeStaminaModelMastersTask.h"
#include "Request/CreateStaminaModelMasterRequest.h"
#include "Task/Rest/CreateStaminaModelMasterTask.h"
#include "Request/GetStaminaModelMasterRequest.h"
#include "Task/Rest/GetStaminaModelMasterTask.h"
#include "Request/UpdateStaminaModelMasterRequest.h"
#include "Task/Rest/UpdateStaminaModelMasterTask.h"
#include "Request/DeleteStaminaModelMasterRequest.h"
#include "Task/Rest/DeleteStaminaModelMasterTask.h"
#include "Request/DescribeMaxStaminaTableMastersRequest.h"
#include "Task/Rest/DescribeMaxStaminaTableMastersTask.h"
#include "Request/CreateMaxStaminaTableMasterRequest.h"
#include "Task/Rest/CreateMaxStaminaTableMasterTask.h"
#include "Request/GetMaxStaminaTableMasterRequest.h"
#include "Task/Rest/GetMaxStaminaTableMasterTask.h"
#include "Request/UpdateMaxStaminaTableMasterRequest.h"
#include "Task/Rest/UpdateMaxStaminaTableMasterTask.h"
#include "Request/DeleteMaxStaminaTableMasterRequest.h"
#include "Task/Rest/DeleteMaxStaminaTableMasterTask.h"
#include "Request/DescribeRecoverIntervalTableMastersRequest.h"
#include "Task/Rest/DescribeRecoverIntervalTableMastersTask.h"
#include "Request/CreateRecoverIntervalTableMasterRequest.h"
#include "Task/Rest/CreateRecoverIntervalTableMasterTask.h"
#include "Request/GetRecoverIntervalTableMasterRequest.h"
#include "Task/Rest/GetRecoverIntervalTableMasterTask.h"
#include "Request/UpdateRecoverIntervalTableMasterRequest.h"
#include "Task/Rest/UpdateRecoverIntervalTableMasterTask.h"
#include "Request/DeleteRecoverIntervalTableMasterRequest.h"
#include "Task/Rest/DeleteRecoverIntervalTableMasterTask.h"
#include "Request/DescribeRecoverValueTableMastersRequest.h"
#include "Task/Rest/DescribeRecoverValueTableMastersTask.h"
#include "Request/CreateRecoverValueTableMasterRequest.h"
#include "Task/Rest/CreateRecoverValueTableMasterTask.h"
#include "Request/GetRecoverValueTableMasterRequest.h"
#include "Task/Rest/GetRecoverValueTableMasterTask.h"
#include "Request/UpdateRecoverValueTableMasterRequest.h"
#include "Task/Rest/UpdateRecoverValueTableMasterTask.h"
#include "Request/DeleteRecoverValueTableMasterRequest.h"
#include "Task/Rest/DeleteRecoverValueTableMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentStaminaMasterRequest.h"
#include "Task/Rest/GetCurrentStaminaMasterTask.h"
#include "Request/UpdateCurrentStaminaMasterRequest.h"
#include "Task/Rest/UpdateCurrentStaminaMasterTask.h"
#include "Request/UpdateCurrentStaminaMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentStaminaMasterFromGitHubTask.h"
#include "Request/DescribeStaminaModelsRequest.h"
#include "Task/Rest/DescribeStaminaModelsTask.h"
#include "Request/GetStaminaModelRequest.h"
#include "Task/Rest/GetStaminaModelTask.h"
#include "Request/DescribeStaminasRequest.h"
#include "Task/Rest/DescribeStaminasTask.h"
#include "Request/DescribeStaminasByUserIdRequest.h"
#include "Task/Rest/DescribeStaminasByUserIdTask.h"
#include "Request/GetStaminaRequest.h"
#include "Task/Rest/GetStaminaTask.h"
#include "Request/GetStaminaByUserIdRequest.h"
#include "Task/Rest/GetStaminaByUserIdTask.h"
#include "Request/UpdateStaminaByUserIdRequest.h"
#include "Task/Rest/UpdateStaminaByUserIdTask.h"
#include "Request/ConsumeStaminaRequest.h"
#include "Task/Rest/ConsumeStaminaTask.h"
#include "Request/ConsumeStaminaByUserIdRequest.h"
#include "Task/Rest/ConsumeStaminaByUserIdTask.h"
#include "Request/RecoverStaminaByUserIdRequest.h"
#include "Task/Rest/RecoverStaminaByUserIdTask.h"
#include "Request/RaiseMaxValueByUserIdRequest.h"
#include "Task/Rest/RaiseMaxValueByUserIdTask.h"
#include "Request/DecreaseMaxValueByUserIdRequest.h"
#include "Task/Rest/DecreaseMaxValueByUserIdTask.h"
#include "Request/SetMaxValueByUserIdRequest.h"
#include "Task/Rest/SetMaxValueByUserIdTask.h"
#include "Request/SetRecoverIntervalByUserIdRequest.h"
#include "Task/Rest/SetRecoverIntervalByUserIdTask.h"
#include "Request/SetRecoverValueByUserIdRequest.h"
#include "Task/Rest/SetRecoverValueByUserIdTask.h"
#include "Request/SetMaxValueByStatusRequest.h"
#include "Task/Rest/SetMaxValueByStatusTask.h"
#include "Request/SetRecoverIntervalByStatusRequest.h"
#include "Task/Rest/SetRecoverIntervalByStatusTask.h"
#include "Request/SetRecoverValueByStatusRequest.h"
#include "Task/Rest/SetRecoverValueByStatusTask.h"
#include "Request/DeleteStaminaByUserIdRequest.h"
#include "Task/Rest/DeleteStaminaByUserIdTask.h"
#include "Request/RecoverStaminaByStampSheetRequest.h"
#include "Task/Rest/RecoverStaminaByStampSheetTask.h"
#include "Request/RaiseMaxValueByStampSheetRequest.h"
#include "Task/Rest/RaiseMaxValueByStampSheetTask.h"
#include "Request/DecreaseMaxValueByStampTaskRequest.h"
#include "Task/Rest/DecreaseMaxValueByStampTaskTask.h"
#include "Request/SetMaxValueByStampSheetRequest.h"
#include "Task/Rest/SetMaxValueByStampSheetTask.h"
#include "Request/SetRecoverIntervalByStampSheetRequest.h"
#include "Task/Rest/SetRecoverIntervalByStampSheetTask.h"
#include "Request/SetRecoverValueByStampSheetRequest.h"
#include "Task/Rest/SetRecoverValueByStampSheetTask.h"
#include "Request/ConsumeStaminaByStampTaskRequest.h"
#include "Task/Rest/ConsumeStaminaByStampTaskTask.h"

namespace Gs2::Stamina
{
    class GS2STAMINA_API FGs2StaminaRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2StaminaRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminaModelMastersTask>> DescribeStaminaModelMasters(
            const Request::FDescribeStaminaModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateStaminaModelMasterTask>> CreateStaminaModelMaster(
            const Request::FCreateStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaModelMasterTask>> GetStaminaModelMaster(
            const Request::FGetStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStaminaModelMasterTask>> UpdateStaminaModelMaster(
            const Request::FUpdateStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStaminaModelMasterTask>> DeleteStaminaModelMaster(
            const Request::FDeleteStaminaModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMaxStaminaTableMastersTask>> DescribeMaxStaminaTableMasters(
            const Request::FDescribeMaxStaminaTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateMaxStaminaTableMasterTask>> CreateMaxStaminaTableMaster(
            const Request::FCreateMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMaxStaminaTableMasterTask>> GetMaxStaminaTableMaster(
            const Request::FGetMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateMaxStaminaTableMasterTask>> UpdateMaxStaminaTableMaster(
            const Request::FUpdateMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMaxStaminaTableMasterTask>> DeleteMaxStaminaTableMaster(
            const Request::FDeleteMaxStaminaTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRecoverIntervalTableMastersTask>> DescribeRecoverIntervalTableMasters(
            const Request::FDescribeRecoverIntervalTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRecoverIntervalTableMasterTask>> CreateRecoverIntervalTableMaster(
            const Request::FCreateRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRecoverIntervalTableMasterTask>> GetRecoverIntervalTableMaster(
            const Request::FGetRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRecoverIntervalTableMasterTask>> UpdateRecoverIntervalTableMaster(
            const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRecoverIntervalTableMasterTask>> DeleteRecoverIntervalTableMaster(
            const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRecoverValueTableMastersTask>> DescribeRecoverValueTableMasters(
            const Request::FDescribeRecoverValueTableMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRecoverValueTableMasterTask>> CreateRecoverValueTableMaster(
            const Request::FCreateRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRecoverValueTableMasterTask>> GetRecoverValueTableMaster(
            const Request::FGetRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRecoverValueTableMasterTask>> UpdateRecoverValueTableMaster(
            const Request::FUpdateRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRecoverValueTableMasterTask>> DeleteRecoverValueTableMaster(
            const Request::FDeleteRecoverValueTableMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentStaminaMasterTask>> GetCurrentStaminaMaster(
            const Request::FGetCurrentStaminaMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentStaminaMasterTask>> UpdateCurrentStaminaMaster(
            const Request::FUpdateCurrentStaminaMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentStaminaMasterFromGitHubTask>> UpdateCurrentStaminaMasterFromGitHub(
            const Request::FUpdateCurrentStaminaMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminaModelsTask>> DescribeStaminaModels(
            const Request::FDescribeStaminaModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaModelTask>> GetStaminaModel(
            const Request::FGetStaminaModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminasTask>> DescribeStaminas(
            const Request::FDescribeStaminasRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminasByUserIdTask>> DescribeStaminasByUserId(
            const Request::FDescribeStaminasByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaTask>> GetStamina(
            const Request::FGetStaminaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaByUserIdTask>> GetStaminaByUserId(
            const Request::FGetStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStaminaByUserIdTask>> UpdateStaminaByUserId(
            const Request::FUpdateStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeStaminaTask>> ConsumeStamina(
            const Request::FConsumeStaminaRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeStaminaByUserIdTask>> ConsumeStaminaByUserId(
            const Request::FConsumeStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRecoverStaminaByUserIdTask>> RecoverStaminaByUserId(
            const Request::FRecoverStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRaiseMaxValueByUserIdTask>> RaiseMaxValueByUserId(
            const Request::FRaiseMaxValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaxValueByUserIdTask>> DecreaseMaxValueByUserId(
            const Request::FDecreaseMaxValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaxValueByUserIdTask>> SetMaxValueByUserId(
            const Request::FSetMaxValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverIntervalByUserIdTask>> SetRecoverIntervalByUserId(
            const Request::FSetRecoverIntervalByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverValueByUserIdTask>> SetRecoverValueByUserId(
            const Request::FSetRecoverValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaxValueByStatusTask>> SetMaxValueByStatus(
            const Request::FSetMaxValueByStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverIntervalByStatusTask>> SetRecoverIntervalByStatus(
            const Request::FSetRecoverIntervalByStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverValueByStatusTask>> SetRecoverValueByStatus(
            const Request::FSetRecoverValueByStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStaminaByUserIdTask>> DeleteStaminaByUserId(
            const Request::FDeleteStaminaByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRecoverStaminaByStampSheetTask>> RecoverStaminaByStampSheet(
            const Request::FRecoverStaminaByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRaiseMaxValueByStampSheetTask>> RaiseMaxValueByStampSheet(
            const Request::FRaiseMaxValueByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaxValueByStampTaskTask>> DecreaseMaxValueByStampTask(
            const Request::FDecreaseMaxValueByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaxValueByStampSheetTask>> SetMaxValueByStampSheet(
            const Request::FSetMaxValueByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverIntervalByStampSheetTask>> SetRecoverIntervalByStampSheet(
            const Request::FSetRecoverIntervalByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverValueByStampSheetTask>> SetRecoverValueByStampSheet(
            const Request::FSetRecoverValueByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FConsumeStaminaByStampTaskTask>> ConsumeStaminaByStampTask(
            const Request::FConsumeStaminaByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2StaminaRestClient, ESPMode::ThreadSafe> FGs2StaminaRestClientPtr;
}