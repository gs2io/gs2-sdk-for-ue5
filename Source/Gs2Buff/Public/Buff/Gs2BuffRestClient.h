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
#include "Request/DescribeBuffEntryModelsRequest.h"
#include "Task/Rest/DescribeBuffEntryModelsTask.h"
#include "Request/GetBuffEntryModelRequest.h"
#include "Task/Rest/GetBuffEntryModelTask.h"
#include "Request/DescribeBuffEntryModelMastersRequest.h"
#include "Task/Rest/DescribeBuffEntryModelMastersTask.h"
#include "Request/CreateBuffEntryModelMasterRequest.h"
#include "Task/Rest/CreateBuffEntryModelMasterTask.h"
#include "Request/GetBuffEntryModelMasterRequest.h"
#include "Task/Rest/GetBuffEntryModelMasterTask.h"
#include "Request/UpdateBuffEntryModelMasterRequest.h"
#include "Task/Rest/UpdateBuffEntryModelMasterTask.h"
#include "Request/DeleteBuffEntryModelMasterRequest.h"
#include "Task/Rest/DeleteBuffEntryModelMasterTask.h"
#include "Request/ApplyBuffRequest.h"
#include "Task/Rest/ApplyBuffTask.h"
#include "Request/ApplyBuffByUserIdRequest.h"
#include "Task/Rest/ApplyBuffByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentBuffMasterRequest.h"
#include "Task/Rest/GetCurrentBuffMasterTask.h"
#include "Request/UpdateCurrentBuffMasterRequest.h"
#include "Task/Rest/UpdateCurrentBuffMasterTask.h"
#include "Request/UpdateCurrentBuffMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentBuffMasterFromGitHubTask.h"

namespace Gs2::Buff
{
    class GS2BUFF_API FGs2BuffRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2BuffRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBuffEntryModelsTask>> DescribeBuffEntryModels(
            const Request::FDescribeBuffEntryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBuffEntryModelTask>> GetBuffEntryModel(
            const Request::FGetBuffEntryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBuffEntryModelMastersTask>> DescribeBuffEntryModelMasters(
            const Request::FDescribeBuffEntryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateBuffEntryModelMasterTask>> CreateBuffEntryModelMaster(
            const Request::FCreateBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetBuffEntryModelMasterTask>> GetBuffEntryModelMaster(
            const Request::FGetBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateBuffEntryModelMasterTask>> UpdateBuffEntryModelMaster(
            const Request::FUpdateBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteBuffEntryModelMasterTask>> DeleteBuffEntryModelMaster(
            const Request::FDeleteBuffEntryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FApplyBuffTask>> ApplyBuff(
            const Request::FApplyBuffRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FApplyBuffByUserIdTask>> ApplyBuffByUserId(
            const Request::FApplyBuffByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentBuffMasterTask>> GetCurrentBuffMaster(
            const Request::FGetCurrentBuffMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentBuffMasterTask>> UpdateCurrentBuffMaster(
            const Request::FUpdateCurrentBuffMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentBuffMasterFromGitHubTask>> UpdateCurrentBuffMasterFromGitHub(
            const Request::FUpdateCurrentBuffMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2BuffRestClient, ESPMode::ThreadSafe> FGs2BuffRestClientPtr;
}