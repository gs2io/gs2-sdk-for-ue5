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
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
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
#include "Request/DescribeBalanceParameterModelsRequest.h"
#include "Task/Rest/DescribeBalanceParameterModelsTask.h"
#include "Request/GetBalanceParameterModelRequest.h"
#include "Task/Rest/GetBalanceParameterModelTask.h"
#include "Request/DescribeBalanceParameterModelMastersRequest.h"
#include "Task/Rest/DescribeBalanceParameterModelMastersTask.h"
#include "Request/CreateBalanceParameterModelMasterRequest.h"
#include "Task/Rest/CreateBalanceParameterModelMasterTask.h"
#include "Request/GetBalanceParameterModelMasterRequest.h"
#include "Task/Rest/GetBalanceParameterModelMasterTask.h"
#include "Request/UpdateBalanceParameterModelMasterRequest.h"
#include "Task/Rest/UpdateBalanceParameterModelMasterTask.h"
#include "Request/DeleteBalanceParameterModelMasterRequest.h"
#include "Task/Rest/DeleteBalanceParameterModelMasterTask.h"
#include "Request/DescribeRarityParameterModelsRequest.h"
#include "Task/Rest/DescribeRarityParameterModelsTask.h"
#include "Request/GetRarityParameterModelRequest.h"
#include "Task/Rest/GetRarityParameterModelTask.h"
#include "Request/DescribeRarityParameterModelMastersRequest.h"
#include "Task/Rest/DescribeRarityParameterModelMastersTask.h"
#include "Request/CreateRarityParameterModelMasterRequest.h"
#include "Task/Rest/CreateRarityParameterModelMasterTask.h"
#include "Request/GetRarityParameterModelMasterRequest.h"
#include "Task/Rest/GetRarityParameterModelMasterTask.h"
#include "Request/UpdateRarityParameterModelMasterRequest.h"
#include "Task/Rest/UpdateRarityParameterModelMasterTask.h"
#include "Request/DeleteRarityParameterModelMasterRequest.h"
#include "Task/Rest/DeleteRarityParameterModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentParameterMasterRequest.h"
#include "Task/Rest/GetCurrentParameterMasterTask.h"
#include "Request/PreUpdateCurrentParameterMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentParameterMasterTask.h"
#include "Request/UpdateCurrentParameterMasterRequest.h"
#include "Task/Rest/UpdateCurrentParameterMasterTask.h"
#include "Request/UpdateCurrentParameterMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentParameterMasterFromGitHubTask.h"
#include "Request/DescribeBalanceParameterStatusesRequest.h"
#include "Task/Rest/DescribeBalanceParameterStatusesTask.h"
#include "Request/DescribeBalanceParameterStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeBalanceParameterStatusesByUserIdTask.h"
#include "Request/GetBalanceParameterStatusRequest.h"
#include "Task/Rest/GetBalanceParameterStatusTask.h"
#include "Request/GetBalanceParameterStatusByUserIdRequest.h"
#include "Task/Rest/GetBalanceParameterStatusByUserIdTask.h"
#include "Request/DeleteBalanceParameterStatusByUserIdRequest.h"
#include "Task/Rest/DeleteBalanceParameterStatusByUserIdTask.h"
#include "Request/ReDrawBalanceParameterStatusByUserIdRequest.h"
#include "Task/Rest/ReDrawBalanceParameterStatusByUserIdTask.h"
#include "Request/ReDrawBalanceParameterStatusByStampSheetRequest.h"
#include "Task/Rest/ReDrawBalanceParameterStatusByStampSheetTask.h"
#include "Request/SetBalanceParameterStatusByUserIdRequest.h"
#include "Task/Rest/SetBalanceParameterStatusByUserIdTask.h"
#include "Request/SetBalanceParameterStatusByStampSheetRequest.h"
#include "Task/Rest/SetBalanceParameterStatusByStampSheetTask.h"
#include "Request/DescribeRarityParameterStatusesRequest.h"
#include "Task/Rest/DescribeRarityParameterStatusesTask.h"
#include "Request/DescribeRarityParameterStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeRarityParameterStatusesByUserIdTask.h"
#include "Request/GetRarityParameterStatusRequest.h"
#include "Task/Rest/GetRarityParameterStatusTask.h"
#include "Request/GetRarityParameterStatusByUserIdRequest.h"
#include "Task/Rest/GetRarityParameterStatusByUserIdTask.h"
#include "Request/DeleteRarityParameterStatusByUserIdRequest.h"
#include "Task/Rest/DeleteRarityParameterStatusByUserIdTask.h"
#include "Request/ReDrawRarityParameterStatusByUserIdRequest.h"
#include "Task/Rest/ReDrawRarityParameterStatusByUserIdTask.h"
#include "Request/ReDrawRarityParameterStatusByStampSheetRequest.h"
#include "Task/Rest/ReDrawRarityParameterStatusByStampSheetTask.h"
#include "Request/AddRarityParameterStatusByUserIdRequest.h"
#include "Task/Rest/AddRarityParameterStatusByUserIdTask.h"
#include "Request/AddRarityParameterStatusByStampSheetRequest.h"
#include "Task/Rest/AddRarityParameterStatusByStampSheetTask.h"
#include "Request/VerifyRarityParameterStatusRequest.h"
#include "Task/Rest/VerifyRarityParameterStatusTask.h"
#include "Request/VerifyRarityParameterStatusByUserIdRequest.h"
#include "Task/Rest/VerifyRarityParameterStatusByUserIdTask.h"
#include "Request/VerifyRarityParameterStatusByStampTaskRequest.h"
#include "Task/Rest/VerifyRarityParameterStatusByStampTaskTask.h"
#include "Request/SetRarityParameterStatusByUserIdRequest.h"
#include "Task/Rest/SetRarityParameterStatusByUserIdTask.h"
#include "Request/SetRarityParameterStatusByStampSheetRequest.h"
#include "Task/Rest/SetRarityParameterStatusByStampSheetTask.h"

namespace Gs2::Enchant
{
    class GS2ENCHANT_API FGs2EnchantRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2EnchantRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterModelsTask>> DescribeBalanceParameterModels(
            const Request::FDescribeBalanceParameterModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterModelTask>> GetBalanceParameterModel(
            const Request::FGetBalanceParameterModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterModelMastersTask>> DescribeBalanceParameterModelMasters(
            const Request::FDescribeBalanceParameterModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateBalanceParameterModelMasterTask>> CreateBalanceParameterModelMaster(
            const Request::FCreateBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterModelMasterTask>> GetBalanceParameterModelMaster(
            const Request::FGetBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateBalanceParameterModelMasterTask>> UpdateBalanceParameterModelMaster(
            const Request::FUpdateBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteBalanceParameterModelMasterTask>> DeleteBalanceParameterModelMaster(
            const Request::FDeleteBalanceParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterModelsTask>> DescribeRarityParameterModels(
            const Request::FDescribeRarityParameterModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterModelTask>> GetRarityParameterModel(
            const Request::FGetRarityParameterModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterModelMastersTask>> DescribeRarityParameterModelMasters(
            const Request::FDescribeRarityParameterModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRarityParameterModelMasterTask>> CreateRarityParameterModelMaster(
            const Request::FCreateRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterModelMasterTask>> GetRarityParameterModelMaster(
            const Request::FGetRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRarityParameterModelMasterTask>> UpdateRarityParameterModelMaster(
            const Request::FUpdateRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRarityParameterModelMasterTask>> DeleteRarityParameterModelMaster(
            const Request::FDeleteRarityParameterModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentParameterMasterTask>> GetCurrentParameterMaster(
            const Request::FGetCurrentParameterMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentParameterMasterTask>> PreUpdateCurrentParameterMaster(
            const Request::FPreUpdateCurrentParameterMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentParameterMasterTask>> UpdateCurrentParameterMaster(
            const Request::FUpdateCurrentParameterMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentParameterMasterFromGitHubTask>> UpdateCurrentParameterMasterFromGitHub(
            const Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterStatusesTask>> DescribeBalanceParameterStatuses(
            const Request::FDescribeBalanceParameterStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterStatusesByUserIdTask>> DescribeBalanceParameterStatusesByUserId(
            const Request::FDescribeBalanceParameterStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterStatusTask>> GetBalanceParameterStatus(
            const Request::FGetBalanceParameterStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterStatusByUserIdTask>> GetBalanceParameterStatusByUserId(
            const Request::FGetBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteBalanceParameterStatusByUserIdTask>> DeleteBalanceParameterStatusByUserId(
            const Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReDrawBalanceParameterStatusByUserIdTask>> ReDrawBalanceParameterStatusByUserId(
            const Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReDrawBalanceParameterStatusByStampSheetTask>> ReDrawBalanceParameterStatusByStampSheet(
            const Request::FReDrawBalanceParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetBalanceParameterStatusByUserIdTask>> SetBalanceParameterStatusByUserId(
            const Request::FSetBalanceParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetBalanceParameterStatusByStampSheetTask>> SetBalanceParameterStatusByStampSheet(
            const Request::FSetBalanceParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterStatusesTask>> DescribeRarityParameterStatuses(
            const Request::FDescribeRarityParameterStatusesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterStatusesByUserIdTask>> DescribeRarityParameterStatusesByUserId(
            const Request::FDescribeRarityParameterStatusesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterStatusTask>> GetRarityParameterStatus(
            const Request::FGetRarityParameterStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterStatusByUserIdTask>> GetRarityParameterStatusByUserId(
            const Request::FGetRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRarityParameterStatusByUserIdTask>> DeleteRarityParameterStatusByUserId(
            const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReDrawRarityParameterStatusByUserIdTask>> ReDrawRarityParameterStatusByUserId(
            const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FReDrawRarityParameterStatusByStampSheetTask>> ReDrawRarityParameterStatusByStampSheet(
            const Request::FReDrawRarityParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddRarityParameterStatusByUserIdTask>> AddRarityParameterStatusByUserId(
            const Request::FAddRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddRarityParameterStatusByStampSheetTask>> AddRarityParameterStatusByStampSheet(
            const Request::FAddRarityParameterStatusByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusTask>> VerifyRarityParameterStatus(
            const Request::FVerifyRarityParameterStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusByUserIdTask>> VerifyRarityParameterStatusByUserId(
            const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusByStampTaskTask>> VerifyRarityParameterStatusByStampTask(
            const Request::FVerifyRarityParameterStatusByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRarityParameterStatusByUserIdTask>> SetRarityParameterStatusByUserId(
            const Request::FSetRarityParameterStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetRarityParameterStatusByStampSheetTask>> SetRarityParameterStatusByStampSheet(
            const Request::FSetRarityParameterStatusByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2EnchantRestClient, ESPMode::ThreadSafe> FGs2EnchantRestClientPtr;
}