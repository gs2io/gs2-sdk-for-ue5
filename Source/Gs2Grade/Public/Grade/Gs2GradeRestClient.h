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
#include "Request/DescribeGradeModelMastersRequest.h"
#include "Task/Rest/DescribeGradeModelMastersTask.h"
#include "Request/CreateGradeModelMasterRequest.h"
#include "Task/Rest/CreateGradeModelMasterTask.h"
#include "Request/GetGradeModelMasterRequest.h"
#include "Task/Rest/GetGradeModelMasterTask.h"
#include "Request/UpdateGradeModelMasterRequest.h"
#include "Task/Rest/UpdateGradeModelMasterTask.h"
#include "Request/DeleteGradeModelMasterRequest.h"
#include "Task/Rest/DeleteGradeModelMasterTask.h"
#include "Request/DescribeGradeModelsRequest.h"
#include "Task/Rest/DescribeGradeModelsTask.h"
#include "Request/GetGradeModelRequest.h"
#include "Task/Rest/GetGradeModelTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/Rest/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Request/AddGradeByUserIdRequest.h"
#include "Task/Rest/AddGradeByUserIdTask.h"
#include "Request/SubGradeRequest.h"
#include "Task/Rest/SubGradeTask.h"
#include "Request/SubGradeByUserIdRequest.h"
#include "Task/Rest/SubGradeByUserIdTask.h"
#include "Request/SetGradeByUserIdRequest.h"
#include "Task/Rest/SetGradeByUserIdTask.h"
#include "Request/ApplyRankCapRequest.h"
#include "Task/Rest/ApplyRankCapTask.h"
#include "Request/ApplyRankCapByUserIdRequest.h"
#include "Task/Rest/ApplyRankCapByUserIdTask.h"
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Task/Rest/DeleteStatusByUserIdTask.h"
#include "Request/VerifyGradeRequest.h"
#include "Task/Rest/VerifyGradeTask.h"
#include "Request/VerifyGradeByUserIdRequest.h"
#include "Task/Rest/VerifyGradeByUserIdTask.h"
#include "Request/VerifyGradeUpMaterialRequest.h"
#include "Task/Rest/VerifyGradeUpMaterialTask.h"
#include "Request/VerifyGradeUpMaterialByUserIdRequest.h"
#include "Task/Rest/VerifyGradeUpMaterialByUserIdTask.h"
#include "Request/AddGradeByStampSheetRequest.h"
#include "Task/Rest/AddGradeByStampSheetTask.h"
#include "Request/ApplyRankCapByStampSheetRequest.h"
#include "Task/Rest/ApplyRankCapByStampSheetTask.h"
#include "Request/SubGradeByStampTaskRequest.h"
#include "Task/Rest/SubGradeByStampTaskTask.h"
#include "Request/MultiplyAcquireActionsByUserIdRequest.h"
#include "Task/Rest/MultiplyAcquireActionsByUserIdTask.h"
#include "Request/MultiplyAcquireActionsByStampSheetRequest.h"
#include "Task/Rest/MultiplyAcquireActionsByStampSheetTask.h"
#include "Request/VerifyGradeByStampTaskRequest.h"
#include "Task/Rest/VerifyGradeByStampTaskTask.h"
#include "Request/VerifyGradeUpMaterialByStampTaskRequest.h"
#include "Task/Rest/VerifyGradeUpMaterialByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentGradeMasterRequest.h"
#include "Task/Rest/GetCurrentGradeMasterTask.h"
#include "Request/UpdateCurrentGradeMasterRequest.h"
#include "Task/Rest/UpdateCurrentGradeMasterTask.h"
#include "Request/UpdateCurrentGradeMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentGradeMasterFromGitHubTask.h"

namespace Gs2::Grade
{
    class GS2GRADE_API FGs2GradeRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2GradeRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGradeModelMastersTask>> DescribeGradeModelMasters(
            const Request::FDescribeGradeModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGradeModelMasterTask>> CreateGradeModelMaster(
            const Request::FCreateGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGradeModelMasterTask>> GetGradeModelMaster(
            const Request::FGetGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGradeModelMasterTask>> UpdateGradeModelMaster(
            const Request::FUpdateGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGradeModelMasterTask>> DeleteGradeModelMaster(
            const Request::FDeleteGradeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGradeModelsTask>> DescribeGradeModels(
            const Request::FDescribeGradeModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGradeModelTask>> GetGradeModel(
            const Request::FGetGradeModelRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FAddGradeByUserIdTask>> AddGradeByUserId(
            const Request::FAddGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubGradeTask>> SubGrade(
            const Request::FSubGradeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubGradeByUserIdTask>> SubGradeByUserId(
            const Request::FSubGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetGradeByUserIdTask>> SetGradeByUserId(
            const Request::FSetGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FApplyRankCapTask>> ApplyRankCap(
            const Request::FApplyRankCapRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FApplyRankCapByUserIdTask>> ApplyRankCapByUserId(
            const Request::FApplyRankCapByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStatusByUserIdTask>> DeleteStatusByUserId(
            const Request::FDeleteStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGradeTask>> VerifyGrade(
            const Request::FVerifyGradeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGradeByUserIdTask>> VerifyGradeByUserId(
            const Request::FVerifyGradeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGradeUpMaterialTask>> VerifyGradeUpMaterial(
            const Request::FVerifyGradeUpMaterialRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGradeUpMaterialByUserIdTask>> VerifyGradeUpMaterialByUserId(
            const Request::FVerifyGradeUpMaterialByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddGradeByStampSheetTask>> AddGradeByStampSheet(
            const Request::FAddGradeByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FApplyRankCapByStampSheetTask>> ApplyRankCapByStampSheet(
            const Request::FApplyRankCapByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubGradeByStampTaskTask>> SubGradeByStampTask(
            const Request::FSubGradeByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByUserIdTask>> MultiplyAcquireActionsByUserId(
            const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByStampSheetTask>> MultiplyAcquireActionsByStampSheet(
            const Request::FMultiplyAcquireActionsByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGradeByStampTaskTask>> VerifyGradeByStampTask(
            const Request::FVerifyGradeByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyGradeUpMaterialByStampTaskTask>> VerifyGradeUpMaterialByStampTask(
            const Request::FVerifyGradeUpMaterialByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentGradeMasterTask>> GetCurrentGradeMaster(
            const Request::FGetCurrentGradeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentGradeMasterTask>> UpdateCurrentGradeMaster(
            const Request::FUpdateCurrentGradeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentGradeMasterFromGitHubTask>> UpdateCurrentGradeMasterFromGitHub(
            const Request::FUpdateCurrentGradeMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2GradeRestClient, ESPMode::ThreadSafe> FGs2GradeRestClientPtr;
}