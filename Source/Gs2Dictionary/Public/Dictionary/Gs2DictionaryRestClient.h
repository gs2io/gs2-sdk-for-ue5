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
#include "Request/DescribeEntryModelsRequest.h"
#include "Task/Rest/DescribeEntryModelsTask.h"
#include "Request/GetEntryModelRequest.h"
#include "Task/Rest/GetEntryModelTask.h"
#include "Request/DescribeEntryModelMastersRequest.h"
#include "Task/Rest/DescribeEntryModelMastersTask.h"
#include "Request/CreateEntryModelMasterRequest.h"
#include "Task/Rest/CreateEntryModelMasterTask.h"
#include "Request/GetEntryModelMasterRequest.h"
#include "Task/Rest/GetEntryModelMasterTask.h"
#include "Request/UpdateEntryModelMasterRequest.h"
#include "Task/Rest/UpdateEntryModelMasterTask.h"
#include "Request/DeleteEntryModelMasterRequest.h"
#include "Task/Rest/DeleteEntryModelMasterTask.h"
#include "Request/DescribeEntriesRequest.h"
#include "Task/Rest/DescribeEntriesTask.h"
#include "Request/DescribeEntriesByUserIdRequest.h"
#include "Task/Rest/DescribeEntriesByUserIdTask.h"
#include "Request/AddEntriesByUserIdRequest.h"
#include "Task/Rest/AddEntriesByUserIdTask.h"
#include "Request/GetEntryRequest.h"
#include "Task/Rest/GetEntryTask.h"
#include "Request/GetEntryByUserIdRequest.h"
#include "Task/Rest/GetEntryByUserIdTask.h"
#include "Request/GetEntryWithSignatureRequest.h"
#include "Task/Rest/GetEntryWithSignatureTask.h"
#include "Request/GetEntryWithSignatureByUserIdRequest.h"
#include "Task/Rest/GetEntryWithSignatureByUserIdTask.h"
#include "Request/ResetByUserIdRequest.h"
#include "Task/Rest/ResetByUserIdTask.h"
#include "Request/VerifyEntryRequest.h"
#include "Task/Rest/VerifyEntryTask.h"
#include "Request/VerifyEntryByUserIdRequest.h"
#include "Task/Rest/VerifyEntryByUserIdTask.h"
#include "Request/DeleteEntriesRequest.h"
#include "Task/Rest/DeleteEntriesTask.h"
#include "Request/DeleteEntriesByUserIdRequest.h"
#include "Task/Rest/DeleteEntriesByUserIdTask.h"
#include "Request/AddEntriesByStampSheetRequest.h"
#include "Task/Rest/AddEntriesByStampSheetTask.h"
#include "Request/DeleteEntriesByStampTaskRequest.h"
#include "Task/Rest/DeleteEntriesByStampTaskTask.h"
#include "Request/VerifyEntryByStampTaskRequest.h"
#include "Task/Rest/VerifyEntryByStampTaskTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentEntryMasterRequest.h"
#include "Task/Rest/GetCurrentEntryMasterTask.h"
#include "Request/UpdateCurrentEntryMasterRequest.h"
#include "Task/Rest/UpdateCurrentEntryMasterTask.h"
#include "Request/UpdateCurrentEntryMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentEntryMasterFromGitHubTask.h"

namespace Gs2::Dictionary
{
    class GS2DICTIONARY_API FGs2DictionaryRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2DictionaryRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEntryModelsTask>> DescribeEntryModels(
            const Request::FDescribeEntryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEntryModelTask>> GetEntryModel(
            const Request::FGetEntryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEntryModelMastersTask>> DescribeEntryModelMasters(
            const Request::FDescribeEntryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateEntryModelMasterTask>> CreateEntryModelMaster(
            const Request::FCreateEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEntryModelMasterTask>> GetEntryModelMaster(
            const Request::FGetEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateEntryModelMasterTask>> UpdateEntryModelMaster(
            const Request::FUpdateEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteEntryModelMasterTask>> DeleteEntryModelMaster(
            const Request::FDeleteEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEntriesTask>> DescribeEntries(
            const Request::FDescribeEntriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeEntriesByUserIdTask>> DescribeEntriesByUserId(
            const Request::FDescribeEntriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddEntriesByUserIdTask>> AddEntriesByUserId(
            const Request::FAddEntriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEntryTask>> GetEntry(
            const Request::FGetEntryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEntryByUserIdTask>> GetEntryByUserId(
            const Request::FGetEntryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEntryWithSignatureTask>> GetEntryWithSignature(
            const Request::FGetEntryWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetEntryWithSignatureByUserIdTask>> GetEntryWithSignatureByUserId(
            const Request::FGetEntryWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FResetByUserIdTask>> ResetByUserId(
            const Request::FResetByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyEntryTask>> VerifyEntry(
            const Request::FVerifyEntryRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyEntryByUserIdTask>> VerifyEntryByUserId(
            const Request::FVerifyEntryByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteEntriesTask>> DeleteEntries(
            const Request::FDeleteEntriesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteEntriesByUserIdTask>> DeleteEntriesByUserId(
            const Request::FDeleteEntriesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddEntriesByStampSheetTask>> AddEntriesByStampSheet(
            const Request::FAddEntriesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteEntriesByStampTaskTask>> DeleteEntriesByStampTask(
            const Request::FDeleteEntriesByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyEntryByStampTaskTask>> VerifyEntryByStampTask(
            const Request::FVerifyEntryByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentEntryMasterTask>> GetCurrentEntryMaster(
            const Request::FGetCurrentEntryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentEntryMasterTask>> UpdateCurrentEntryMaster(
            const Request::FUpdateCurrentEntryMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentEntryMasterFromGitHubTask>> UpdateCurrentEntryMasterFromGitHub(
            const Request::FUpdateCurrentEntryMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2DictionaryRestClient, ESPMode::ThreadSafe> FGs2DictionaryRestClientPtr;
}