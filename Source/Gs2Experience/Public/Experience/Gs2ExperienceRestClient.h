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
#include "Request/DescribeExperienceModelMastersRequest.h"
#include "Task/Rest/DescribeExperienceModelMastersTask.h"
#include "Request/CreateExperienceModelMasterRequest.h"
#include "Task/Rest/CreateExperienceModelMasterTask.h"
#include "Request/GetExperienceModelMasterRequest.h"
#include "Task/Rest/GetExperienceModelMasterTask.h"
#include "Request/UpdateExperienceModelMasterRequest.h"
#include "Task/Rest/UpdateExperienceModelMasterTask.h"
#include "Request/DeleteExperienceModelMasterRequest.h"
#include "Task/Rest/DeleteExperienceModelMasterTask.h"
#include "Request/DescribeExperienceModelsRequest.h"
#include "Task/Rest/DescribeExperienceModelsTask.h"
#include "Request/GetExperienceModelRequest.h"
#include "Task/Rest/GetExperienceModelTask.h"
#include "Request/DescribeThresholdMastersRequest.h"
#include "Task/Rest/DescribeThresholdMastersTask.h"
#include "Request/CreateThresholdMasterRequest.h"
#include "Task/Rest/CreateThresholdMasterTask.h"
#include "Request/GetThresholdMasterRequest.h"
#include "Task/Rest/GetThresholdMasterTask.h"
#include "Request/UpdateThresholdMasterRequest.h"
#include "Task/Rest/UpdateThresholdMasterTask.h"
#include "Request/DeleteThresholdMasterRequest.h"
#include "Task/Rest/DeleteThresholdMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentExperienceMasterRequest.h"
#include "Task/Rest/GetCurrentExperienceMasterTask.h"
#include "Request/UpdateCurrentExperienceMasterRequest.h"
#include "Task/Rest/UpdateCurrentExperienceMasterTask.h"
#include "Request/UpdateCurrentExperienceMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentExperienceMasterFromGitHubTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/Rest/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Request/GetStatusWithSignatureRequest.h"
#include "Task/Rest/GetStatusWithSignatureTask.h"
#include "Request/GetStatusWithSignatureByUserIdRequest.h"
#include "Task/Rest/GetStatusWithSignatureByUserIdTask.h"
#include "Request/AddExperienceByUserIdRequest.h"
#include "Task/Rest/AddExperienceByUserIdTask.h"
#include "Request/SubExperienceRequest.h"
#include "Task/Rest/SubExperienceTask.h"
#include "Request/SubExperienceByUserIdRequest.h"
#include "Task/Rest/SubExperienceByUserIdTask.h"
#include "Request/SetExperienceByUserIdRequest.h"
#include "Task/Rest/SetExperienceByUserIdTask.h"
#include "Request/AddRankCapByUserIdRequest.h"
#include "Task/Rest/AddRankCapByUserIdTask.h"
#include "Request/SubRankCapRequest.h"
#include "Task/Rest/SubRankCapTask.h"
#include "Request/SubRankCapByUserIdRequest.h"
#include "Task/Rest/SubRankCapByUserIdTask.h"
#include "Request/SetRankCapByUserIdRequest.h"
#include "Task/Rest/SetRankCapByUserIdTask.h"
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Task/Rest/DeleteStatusByUserIdTask.h"
#include "Request/VerifyRankRequest.h"
#include "Task/Rest/VerifyRankTask.h"
#include "Request/VerifyRankByUserIdRequest.h"
#include "Task/Rest/VerifyRankByUserIdTask.h"
#include "Request/VerifyRankCapRequest.h"
#include "Task/Rest/VerifyRankCapTask.h"
#include "Request/VerifyRankCapByUserIdRequest.h"
#include "Task/Rest/VerifyRankCapByUserIdTask.h"
#include "Request/AddExperienceByStampSheetRequest.h"
#include "Task/Rest/AddExperienceByStampSheetTask.h"
#include "Request/SetExperienceByStampSheetRequest.h"
#include "Task/Rest/SetExperienceByStampSheetTask.h"
#include "Request/SubExperienceByStampTaskRequest.h"
#include "Task/Rest/SubExperienceByStampTaskTask.h"
#include "Request/AddRankCapByStampSheetRequest.h"
#include "Task/Rest/AddRankCapByStampSheetTask.h"
#include "Request/SubRankCapByStampTaskRequest.h"
#include "Task/Rest/SubRankCapByStampTaskTask.h"
#include "Request/SetRankCapByStampSheetRequest.h"
#include "Task/Rest/SetRankCapByStampSheetTask.h"
#include "Request/MultiplyAcquireActionsByUserIdRequest.h"
#include "Task/Rest/MultiplyAcquireActionsByUserIdTask.h"
#include "Request/MultiplyAcquireActionsByStampSheetRequest.h"
#include "Task/Rest/MultiplyAcquireActionsByStampSheetTask.h"
#include "Request/VerifyRankByStampTaskRequest.h"
#include "Task/Rest/VerifyRankByStampTaskTask.h"
#include "Request/VerifyRankCapByStampTaskRequest.h"
#include "Task/Rest/VerifyRankCapByStampTaskTask.h"

namespace Gs2::Experience
{
    class GS2EXPERIENCE_API FGs2ExperienceRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ExperienceRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeExperienceModelMastersTask>> DescribeExperienceModelMasters(
            const Request::FDescribeExperienceModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateExperienceModelMasterTask>> CreateExperienceModelMaster(
            const Request::FCreateExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetExperienceModelMasterTask>> GetExperienceModelMaster(
            const Request::FGetExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateExperienceModelMasterTask>> UpdateExperienceModelMaster(
            const Request::FUpdateExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteExperienceModelMasterTask>> DeleteExperienceModelMaster(
            const Request::FDeleteExperienceModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeExperienceModelsTask>> DescribeExperienceModels(
            const Request::FDescribeExperienceModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetExperienceModelTask>> GetExperienceModel(
            const Request::FGetExperienceModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeThresholdMastersTask>> DescribeThresholdMasters(
            const Request::FDescribeThresholdMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateThresholdMasterTask>> CreateThresholdMaster(
            const Request::FCreateThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetThresholdMasterTask>> GetThresholdMaster(
            const Request::FGetThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateThresholdMasterTask>> UpdateThresholdMaster(
            const Request::FUpdateThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteThresholdMasterTask>> DeleteThresholdMaster(
            const Request::FDeleteThresholdMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentExperienceMasterTask>> GetCurrentExperienceMaster(
            const Request::FGetCurrentExperienceMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentExperienceMasterTask>> UpdateCurrentExperienceMaster(
            const Request::FUpdateCurrentExperienceMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentExperienceMasterFromGitHubTask>> UpdateCurrentExperienceMasterFromGitHub(
            const Request::FUpdateCurrentExperienceMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStatusesTask>> DescribeStatuses(
            const Request::FDescribeStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStatusesByUserIdTask>> DescribeStatusesByUserId(
            const Request::FDescribeStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStatusTask>> GetStatus(
            const Request::FGetStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStatusByUserIdTask>> GetStatusByUserId(
            const Request::FGetStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStatusWithSignatureTask>> GetStatusWithSignature(
            const Request::FGetStatusWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStatusWithSignatureByUserIdTask>> GetStatusWithSignatureByUserId(
            const Request::FGetStatusWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddExperienceByUserIdTask>> AddExperienceByUserId(
            const Request::FAddExperienceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubExperienceTask>> SubExperience(
            const Request::FSubExperienceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubExperienceByUserIdTask>> SubExperienceByUserId(
            const Request::FSubExperienceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetExperienceByUserIdTask>> SetExperienceByUserId(
            const Request::FSetExperienceByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddRankCapByUserIdTask>> AddRankCapByUserId(
            const Request::FAddRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubRankCapTask>> SubRankCap(
            const Request::FSubRankCapRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubRankCapByUserIdTask>> SubRankCapByUserId(
            const Request::FSubRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRankCapByUserIdTask>> SetRankCapByUserId(
            const Request::FSetRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStatusByUserIdTask>> DeleteStatusByUserId(
            const Request::FDeleteStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRankTask>> VerifyRank(
            const Request::FVerifyRankRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRankByUserIdTask>> VerifyRankByUserId(
            const Request::FVerifyRankByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRankCapTask>> VerifyRankCap(
            const Request::FVerifyRankCapRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRankCapByUserIdTask>> VerifyRankCapByUserId(
            const Request::FVerifyRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddExperienceByStampSheetTask>> AddExperienceByStampSheet(
            const Request::FAddExperienceByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetExperienceByStampSheetTask>> SetExperienceByStampSheet(
            const Request::FSetExperienceByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubExperienceByStampTaskTask>> SubExperienceByStampTask(
            const Request::FSubExperienceByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddRankCapByStampSheetTask>> AddRankCapByStampSheet(
            const Request::FAddRankCapByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubRankCapByStampTaskTask>> SubRankCapByStampTask(
            const Request::FSubRankCapByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRankCapByStampSheetTask>> SetRankCapByStampSheet(
            const Request::FSetRankCapByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByUserIdTask>> MultiplyAcquireActionsByUserId(
            const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByStampSheetTask>> MultiplyAcquireActionsByStampSheet(
            const Request::FMultiplyAcquireActionsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRankByStampTaskTask>> VerifyRankByStampTask(
            const Request::FVerifyRankByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRankCapByStampTaskTask>> VerifyRankCapByStampTask(
            const Request::FVerifyRankCapByStampTaskRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ExperienceRestClient, ESPMode::ThreadSafe> FGs2ExperienceRestClientPtr;
}