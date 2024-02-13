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
#include "Request/DescribeNodeModelsRequest.h"
#include "Task/Rest/DescribeNodeModelsTask.h"
#include "Request/GetNodeModelRequest.h"
#include "Task/Rest/GetNodeModelTask.h"
#include "Request/DescribeNodeModelMastersRequest.h"
#include "Task/Rest/DescribeNodeModelMastersTask.h"
#include "Request/CreateNodeModelMasterRequest.h"
#include "Task/Rest/CreateNodeModelMasterTask.h"
#include "Request/GetNodeModelMasterRequest.h"
#include "Task/Rest/GetNodeModelMasterTask.h"
#include "Request/UpdateNodeModelMasterRequest.h"
#include "Task/Rest/UpdateNodeModelMasterTask.h"
#include "Request/DeleteNodeModelMasterRequest.h"
#include "Task/Rest/DeleteNodeModelMasterTask.h"
#include "Request/MarkReleaseByUserIdRequest.h"
#include "Task/Rest/MarkReleaseByUserIdTask.h"
#include "Request/ReleaseRequest.h"
#include "Task/Rest/ReleaseTask.h"
#include "Request/ReleaseByUserIdRequest.h"
#include "Task/Rest/ReleaseByUserIdTask.h"
#include "Request/MarkRestrainByUserIdRequest.h"
#include "Task/Rest/MarkRestrainByUserIdTask.h"
#include "Request/RestrainRequest.h"
#include "Task/Rest/RestrainTask.h"
#include "Request/RestrainByUserIdRequest.h"
#include "Task/Rest/RestrainByUserIdTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/Rest/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Request/ResetRequest.h"
#include "Task/Rest/ResetTask.h"
#include "Request/ResetByUserIdRequest.h"
#include "Task/Rest/ResetByUserIdTask.h"
#include "Request/MarkReleaseByStampSheetRequest.h"
#include "Task/Rest/MarkReleaseByStampSheetTask.h"
#include "Request/MarkRestrainByStampTaskRequest.h"
#include "Task/Rest/MarkRestrainByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentTreeMasterRequest.h"
#include "Task/Rest/GetCurrentTreeMasterTask.h"
#include "Request/UpdateCurrentTreeMasterRequest.h"
#include "Task/Rest/UpdateCurrentTreeMasterTask.h"
#include "Request/UpdateCurrentTreeMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentTreeMasterFromGitHubTask.h"

namespace Gs2::SkillTree
{
    class GS2SKILLTREE_API FGs2SkillTreeRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2SkillTreeRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNodeModelsTask>> DescribeNodeModels(
            const Request::FDescribeNodeModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNodeModelTask>> GetNodeModel(
            const Request::FGetNodeModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNodeModelMastersTask>> DescribeNodeModelMasters(
            const Request::FDescribeNodeModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateNodeModelMasterTask>> CreateNodeModelMaster(
            const Request::FCreateNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetNodeModelMasterTask>> GetNodeModelMaster(
            const Request::FGetNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNodeModelMasterTask>> UpdateNodeModelMaster(
            const Request::FUpdateNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteNodeModelMasterTask>> DeleteNodeModelMaster(
            const Request::FDeleteNodeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkReleaseByUserIdTask>> MarkReleaseByUserId(
            const Request::FMarkReleaseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReleaseTask>> Release(
            const Request::FReleaseRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReleaseByUserIdTask>> ReleaseByUserId(
            const Request::FReleaseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkRestrainByUserIdTask>> MarkRestrainByUserId(
            const Request::FMarkRestrainByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRestrainTask>> Restrain(
            const Request::FRestrainRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRestrainByUserIdTask>> RestrainByUserId(
            const Request::FRestrainByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FResetTask>> Reset(
            const Request::FResetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FResetByUserIdTask>> ResetByUserId(
            const Request::FResetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkReleaseByStampSheetTask>> MarkReleaseByStampSheet(
            const Request::FMarkReleaseByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FMarkRestrainByStampTaskTask>> MarkRestrainByStampTask(
            const Request::FMarkRestrainByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentTreeMasterTask>> GetCurrentTreeMaster(
            const Request::FGetCurrentTreeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentTreeMasterTask>> UpdateCurrentTreeMaster(
            const Request::FUpdateCurrentTreeMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentTreeMasterFromGitHubTask>> UpdateCurrentTreeMasterFromGitHub(
            const Request::FUpdateCurrentTreeMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2SkillTreeRestClient, ESPMode::ThreadSafe> FGs2SkillTreeRestClientPtr;
}