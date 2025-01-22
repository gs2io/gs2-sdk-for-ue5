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
#include "Request/DescribeVersionModelMastersRequest.h"
#include "Task/Rest/DescribeVersionModelMastersTask.h"
#include "Request/CreateVersionModelMasterRequest.h"
#include "Task/Rest/CreateVersionModelMasterTask.h"
#include "Request/GetVersionModelMasterRequest.h"
#include "Task/Rest/GetVersionModelMasterTask.h"
#include "Request/UpdateVersionModelMasterRequest.h"
#include "Task/Rest/UpdateVersionModelMasterTask.h"
#include "Request/DeleteVersionModelMasterRequest.h"
#include "Task/Rest/DeleteVersionModelMasterTask.h"
#include "Request/DescribeVersionModelsRequest.h"
#include "Task/Rest/DescribeVersionModelsTask.h"
#include "Request/GetVersionModelRequest.h"
#include "Task/Rest/GetVersionModelTask.h"
#include "Request/DescribeAcceptVersionsRequest.h"
#include "Task/Rest/DescribeAcceptVersionsTask.h"
#include "Request/DescribeAcceptVersionsByUserIdRequest.h"
#include "Task/Rest/DescribeAcceptVersionsByUserIdTask.h"
#include "Request/AcceptRequest.h"
#include "Task/Rest/AcceptTask.h"
#include "Request/AcceptByUserIdRequest.h"
#include "Task/Rest/AcceptByUserIdTask.h"
#include "Request/RejectRequest.h"
#include "Task/Rest/RejectTask.h"
#include "Request/RejectByUserIdRequest.h"
#include "Task/Rest/RejectByUserIdTask.h"
#include "Request/GetAcceptVersionRequest.h"
#include "Task/Rest/GetAcceptVersionTask.h"
#include "Request/GetAcceptVersionByUserIdRequest.h"
#include "Task/Rest/GetAcceptVersionByUserIdTask.h"
#include "Request/DeleteAcceptVersionRequest.h"
#include "Task/Rest/DeleteAcceptVersionTask.h"
#include "Request/DeleteAcceptVersionByUserIdRequest.h"
#include "Task/Rest/DeleteAcceptVersionByUserIdTask.h"
#include "Request/CheckVersionRequest.h"
#include "Task/Rest/CheckVersionTask.h"
#include "Request/CheckVersionByUserIdRequest.h"
#include "Task/Rest/CheckVersionByUserIdTask.h"
#include "Request/CalculateSignatureRequest.h"
#include "Task/Rest/CalculateSignatureTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentVersionMasterRequest.h"
#include "Task/Rest/GetCurrentVersionMasterTask.h"
#include "Request/UpdateCurrentVersionMasterRequest.h"
#include "Task/Rest/UpdateCurrentVersionMasterTask.h"
#include "Request/UpdateCurrentVersionMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentVersionMasterFromGitHubTask.h"

namespace Gs2::Version
{
    class GS2VERSION_API FGs2VersionRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2VersionRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeVersionModelMastersTask>> DescribeVersionModelMasters(
            const Request::FDescribeVersionModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateVersionModelMasterTask>> CreateVersionModelMaster(
            const Request::FCreateVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetVersionModelMasterTask>> GetVersionModelMaster(
            const Request::FGetVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateVersionModelMasterTask>> UpdateVersionModelMaster(
            const Request::FUpdateVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteVersionModelMasterTask>> DeleteVersionModelMaster(
            const Request::FDeleteVersionModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeVersionModelsTask>> DescribeVersionModels(
            const Request::FDescribeVersionModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetVersionModelTask>> GetVersionModel(
            const Request::FGetVersionModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAcceptVersionsTask>> DescribeAcceptVersions(
            const Request::FDescribeAcceptVersionsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAcceptVersionsByUserIdTask>> DescribeAcceptVersionsByUserId(
            const Request::FDescribeAcceptVersionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcceptTask>> Accept(
            const Request::FAcceptRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcceptByUserIdTask>> AcceptByUserId(
            const Request::FAcceptByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRejectTask>> Reject(
            const Request::FRejectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRejectByUserIdTask>> RejectByUserId(
            const Request::FRejectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAcceptVersionTask>> GetAcceptVersion(
            const Request::FGetAcceptVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAcceptVersionByUserIdTask>> GetAcceptVersionByUserId(
            const Request::FGetAcceptVersionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAcceptVersionTask>> DeleteAcceptVersion(
            const Request::FDeleteAcceptVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAcceptVersionByUserIdTask>> DeleteAcceptVersionByUserId(
            const Request::FDeleteAcceptVersionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckVersionTask>> CheckVersion(
            const Request::FCheckVersionRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckVersionByUserIdTask>> CheckVersionByUserId(
            const Request::FCheckVersionByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCalculateSignatureTask>> CalculateSignature(
            const Request::FCalculateSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentVersionMasterTask>> GetCurrentVersionMaster(
            const Request::FGetCurrentVersionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentVersionMasterTask>> UpdateCurrentVersionMaster(
            const Request::FUpdateCurrentVersionMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentVersionMasterFromGitHubTask>> UpdateCurrentVersionMasterFromGitHub(
            const Request::FUpdateCurrentVersionMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2VersionRestClient, ESPMode::ThreadSafe> FGs2VersionRestClientPtr;
}