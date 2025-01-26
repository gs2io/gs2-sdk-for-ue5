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
#include "Request/DescribeCompletesRequest.h"
#include "Task/Rest/DescribeCompletesTask.h"
#include "Request/DescribeCompletesByUserIdRequest.h"
#include "Task/Rest/DescribeCompletesByUserIdTask.h"
#include "Request/CompleteRequest.h"
#include "Task/Rest/CompleteTask.h"
#include "Request/CompleteByUserIdRequest.h"
#include "Task/Rest/CompleteByUserIdTask.h"
#include "Request/BatchCompleteRequest.h"
#include "Task/Rest/BatchCompleteTask.h"
#include "Request/BatchCompleteByUserIdRequest.h"
#include "Task/Rest/BatchCompleteByUserIdTask.h"
#include "Request/ReceiveByUserIdRequest.h"
#include "Task/Rest/ReceiveByUserIdTask.h"
#include "Request/BatchReceiveByUserIdRequest.h"
#include "Task/Rest/BatchReceiveByUserIdTask.h"
#include "Request/RevertReceiveByUserIdRequest.h"
#include "Task/Rest/RevertReceiveByUserIdTask.h"
#include "Request/GetCompleteRequest.h"
#include "Task/Rest/GetCompleteTask.h"
#include "Request/GetCompleteByUserIdRequest.h"
#include "Task/Rest/GetCompleteByUserIdTask.h"
#include "Request/EvaluateCompleteRequest.h"
#include "Task/Rest/EvaluateCompleteTask.h"
#include "Request/EvaluateCompleteByUserIdRequest.h"
#include "Task/Rest/EvaluateCompleteByUserIdTask.h"
#include "Request/DeleteCompleteByUserIdRequest.h"
#include "Task/Rest/DeleteCompleteByUserIdTask.h"
#include "Request/VerifyCompleteRequest.h"
#include "Task/Rest/VerifyCompleteTask.h"
#include "Request/VerifyCompleteByUserIdRequest.h"
#include "Task/Rest/VerifyCompleteByUserIdTask.h"
#include "Request/ReceiveByStampTaskRequest.h"
#include "Task/Rest/ReceiveByStampTaskTask.h"
#include "Request/BatchReceiveByStampTaskRequest.h"
#include "Task/Rest/BatchReceiveByStampTaskTask.h"
#include "Request/RevertReceiveByStampSheetRequest.h"
#include "Task/Rest/RevertReceiveByStampSheetTask.h"
#include "Request/VerifyCompleteByStampTaskRequest.h"
#include "Task/Rest/VerifyCompleteByStampTaskTask.h"
#include "Request/DescribeCounterModelMastersRequest.h"
#include "Task/Rest/DescribeCounterModelMastersTask.h"
#include "Request/CreateCounterModelMasterRequest.h"
#include "Task/Rest/CreateCounterModelMasterTask.h"
#include "Request/GetCounterModelMasterRequest.h"
#include "Task/Rest/GetCounterModelMasterTask.h"
#include "Request/UpdateCounterModelMasterRequest.h"
#include "Task/Rest/UpdateCounterModelMasterTask.h"
#include "Request/DeleteCounterModelMasterRequest.h"
#include "Task/Rest/DeleteCounterModelMasterTask.h"
#include "Request/DescribeMissionGroupModelMastersRequest.h"
#include "Task/Rest/DescribeMissionGroupModelMastersTask.h"
#include "Request/CreateMissionGroupModelMasterRequest.h"
#include "Task/Rest/CreateMissionGroupModelMasterTask.h"
#include "Request/GetMissionGroupModelMasterRequest.h"
#include "Task/Rest/GetMissionGroupModelMasterTask.h"
#include "Request/UpdateMissionGroupModelMasterRequest.h"
#include "Task/Rest/UpdateMissionGroupModelMasterTask.h"
#include "Request/DeleteMissionGroupModelMasterRequest.h"
#include "Task/Rest/DeleteMissionGroupModelMasterTask.h"
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
#include "Request/DescribeCountersRequest.h"
#include "Task/Rest/DescribeCountersTask.h"
#include "Request/DescribeCountersByUserIdRequest.h"
#include "Task/Rest/DescribeCountersByUserIdTask.h"
#include "Request/IncreaseCounterByUserIdRequest.h"
#include "Task/Rest/IncreaseCounterByUserIdTask.h"
#include "Request/SetCounterByUserIdRequest.h"
#include "Task/Rest/SetCounterByUserIdTask.h"
#include "Request/DecreaseCounterRequest.h"
#include "Task/Rest/DecreaseCounterTask.h"
#include "Request/DecreaseCounterByUserIdRequest.h"
#include "Task/Rest/DecreaseCounterByUserIdTask.h"
#include "Request/GetCounterRequest.h"
#include "Task/Rest/GetCounterTask.h"
#include "Request/GetCounterByUserIdRequest.h"
#include "Task/Rest/GetCounterByUserIdTask.h"
#include "Request/VerifyCounterValueRequest.h"
#include "Task/Rest/VerifyCounterValueTask.h"
#include "Request/VerifyCounterValueByUserIdRequest.h"
#include "Task/Rest/VerifyCounterValueByUserIdTask.h"
#include "Request/DeleteCounterRequest.h"
#include "Task/Rest/DeleteCounterTask.h"
#include "Request/DeleteCounterByUserIdRequest.h"
#include "Task/Rest/DeleteCounterByUserIdTask.h"
#include "Request/IncreaseByStampSheetRequest.h"
#include "Task/Rest/IncreaseByStampSheetTask.h"
#include "Request/SetByStampSheetRequest.h"
#include "Task/Rest/SetByStampSheetTask.h"
#include "Request/DecreaseByStampTaskRequest.h"
#include "Task/Rest/DecreaseByStampTaskTask.h"
#include "Request/VerifyCounterValueByStampTaskRequest.h"
#include "Task/Rest/VerifyCounterValueByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentMissionMasterRequest.h"
#include "Task/Rest/GetCurrentMissionMasterTask.h"
#include "Request/UpdateCurrentMissionMasterRequest.h"
#include "Task/Rest/UpdateCurrentMissionMasterTask.h"
#include "Request/UpdateCurrentMissionMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentMissionMasterFromGitHubTask.h"
#include "Request/DescribeCounterModelsRequest.h"
#include "Task/Rest/DescribeCounterModelsTask.h"
#include "Request/GetCounterModelRequest.h"
#include "Task/Rest/GetCounterModelTask.h"
#include "Request/DescribeMissionGroupModelsRequest.h"
#include "Task/Rest/DescribeMissionGroupModelsTask.h"
#include "Request/GetMissionGroupModelRequest.h"
#include "Task/Rest/GetMissionGroupModelTask.h"
#include "Request/DescribeMissionTaskModelsRequest.h"
#include "Task/Rest/DescribeMissionTaskModelsTask.h"
#include "Request/GetMissionTaskModelRequest.h"
#include "Task/Rest/GetMissionTaskModelTask.h"
#include "Request/DescribeMissionTaskModelMastersRequest.h"
#include "Task/Rest/DescribeMissionTaskModelMastersTask.h"
#include "Request/CreateMissionTaskModelMasterRequest.h"
#include "Task/Rest/CreateMissionTaskModelMasterTask.h"
#include "Request/GetMissionTaskModelMasterRequest.h"
#include "Task/Rest/GetMissionTaskModelMasterTask.h"
#include "Request/UpdateMissionTaskModelMasterRequest.h"
#include "Task/Rest/UpdateMissionTaskModelMasterTask.h"
#include "Request/DeleteMissionTaskModelMasterRequest.h"
#include "Task/Rest/DeleteMissionTaskModelMasterTask.h"

namespace Gs2::Mission
{
    class GS2MISSION_API FGs2MissionRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2MissionRestClient(
            const Core::Net::Rest::FGs2RestSessionPtr Session
        ): FAbstractGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCompletesTask>> DescribeCompletes(
            const Request::FDescribeCompletesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCompletesByUserIdTask>> DescribeCompletesByUserId(
            const Request::FDescribeCompletesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCompleteTask>> Complete(
            const Request::FCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCompleteByUserIdTask>> CompleteByUserId(
            const Request::FCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBatchCompleteTask>> BatchComplete(
            const Request::FBatchCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBatchCompleteByUserIdTask>> BatchCompleteByUserId(
            const Request::FBatchCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveByUserIdTask>> ReceiveByUserId(
            const Request::FReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBatchReceiveByUserIdTask>> BatchReceiveByUserId(
            const Request::FBatchReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRevertReceiveByUserIdTask>> RevertReceiveByUserId(
            const Request::FRevertReceiveByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCompleteTask>> GetComplete(
            const Request::FGetCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCompleteByUserIdTask>> GetCompleteByUserId(
            const Request::FGetCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEvaluateCompleteTask>> EvaluateComplete(
            const Request::FEvaluateCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEvaluateCompleteByUserIdTask>> EvaluateCompleteByUserId(
            const Request::FEvaluateCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCompleteByUserIdTask>> DeleteCompleteByUserId(
            const Request::FDeleteCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCompleteTask>> VerifyComplete(
            const Request::FVerifyCompleteRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCompleteByUserIdTask>> VerifyCompleteByUserId(
            const Request::FVerifyCompleteByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReceiveByStampTaskTask>> ReceiveByStampTask(
            const Request::FReceiveByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBatchReceiveByStampTaskTask>> BatchReceiveByStampTask(
            const Request::FBatchReceiveByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRevertReceiveByStampSheetTask>> RevertReceiveByStampSheet(
            const Request::FRevertReceiveByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCompleteByStampTaskTask>> VerifyCompleteByStampTask(
            const Request::FVerifyCompleteByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCounterModelMastersTask>> DescribeCounterModelMasters(
            const Request::FDescribeCounterModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateCounterModelMasterTask>> CreateCounterModelMaster(
            const Request::FCreateCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCounterModelMasterTask>> GetCounterModelMaster(
            const Request::FGetCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCounterModelMasterTask>> UpdateCounterModelMaster(
            const Request::FUpdateCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCounterModelMasterTask>> DeleteCounterModelMaster(
            const Request::FDeleteCounterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMissionGroupModelMastersTask>> DescribeMissionGroupModelMasters(
            const Request::FDescribeMissionGroupModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateMissionGroupModelMasterTask>> CreateMissionGroupModelMaster(
            const Request::FCreateMissionGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMissionGroupModelMasterTask>> GetMissionGroupModelMaster(
            const Request::FGetMissionGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateMissionGroupModelMasterTask>> UpdateMissionGroupModelMaster(
            const Request::FUpdateMissionGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMissionGroupModelMasterTask>> DeleteMissionGroupModelMaster(
            const Request::FDeleteMissionGroupModelMasterRequestPtr Request
        ) const;

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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCountersTask>> DescribeCounters(
            const Request::FDescribeCountersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCountersByUserIdTask>> DescribeCountersByUserId(
            const Request::FDescribeCountersByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncreaseCounterByUserIdTask>> IncreaseCounterByUserId(
            const Request::FIncreaseCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetCounterByUserIdTask>> SetCounterByUserId(
            const Request::FSetCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseCounterTask>> DecreaseCounter(
            const Request::FDecreaseCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseCounterByUserIdTask>> DecreaseCounterByUserId(
            const Request::FDecreaseCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCounterTask>> GetCounter(
            const Request::FGetCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCounterByUserIdTask>> GetCounterByUserId(
            const Request::FGetCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCounterValueTask>> VerifyCounterValue(
            const Request::FVerifyCounterValueRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCounterValueByUserIdTask>> VerifyCounterValueByUserId(
            const Request::FVerifyCounterValueByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCounterTask>> DeleteCounter(
            const Request::FDeleteCounterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCounterByUserIdTask>> DeleteCounterByUserId(
            const Request::FDeleteCounterByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncreaseByStampSheetTask>> IncreaseByStampSheet(
            const Request::FIncreaseByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetByStampSheetTask>> SetByStampSheet(
            const Request::FSetByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseByStampTaskTask>> DecreaseByStampTask(
            const Request::FDecreaseByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCounterValueByStampTaskTask>> VerifyCounterValueByStampTask(
            const Request::FVerifyCounterValueByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentMissionMasterTask>> GetCurrentMissionMaster(
            const Request::FGetCurrentMissionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentMissionMasterTask>> UpdateCurrentMissionMaster(
            const Request::FUpdateCurrentMissionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentMissionMasterFromGitHubTask>> UpdateCurrentMissionMasterFromGitHub(
            const Request::FUpdateCurrentMissionMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCounterModelsTask>> DescribeCounterModels(
            const Request::FDescribeCounterModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCounterModelTask>> GetCounterModel(
            const Request::FGetCounterModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMissionGroupModelsTask>> DescribeMissionGroupModels(
            const Request::FDescribeMissionGroupModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMissionGroupModelTask>> GetMissionGroupModel(
            const Request::FGetMissionGroupModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMissionTaskModelsTask>> DescribeMissionTaskModels(
            const Request::FDescribeMissionTaskModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMissionTaskModelTask>> GetMissionTaskModel(
            const Request::FGetMissionTaskModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMissionTaskModelMastersTask>> DescribeMissionTaskModelMasters(
            const Request::FDescribeMissionTaskModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateMissionTaskModelMasterTask>> CreateMissionTaskModelMaster(
            const Request::FCreateMissionTaskModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMissionTaskModelMasterTask>> GetMissionTaskModelMaster(
            const Request::FGetMissionTaskModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateMissionTaskModelMasterTask>> UpdateMissionTaskModelMaster(
            const Request::FUpdateMissionTaskModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMissionTaskModelMasterTask>> DeleteMissionTaskModelMaster(
            const Request::FDeleteMissionTaskModelMasterRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2MissionRestClient, ESPMode::ThreadSafe> FGs2MissionRestClientPtr;
}