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
#include "Request/DescribeStateMachineMastersRequest.h"
#include "Task/Rest/DescribeStateMachineMastersTask.h"
#include "Request/UpdateStateMachineMasterRequest.h"
#include "Task/Rest/UpdateStateMachineMasterTask.h"
#include "Request/GetStateMachineMasterRequest.h"
#include "Task/Rest/GetStateMachineMasterTask.h"
#include "Request/DeleteStateMachineMasterRequest.h"
#include "Task/Rest/DeleteStateMachineMasterTask.h"
#include "Request/DescribeStatusesRequest.h"
#include "Task/Rest/DescribeStatusesTask.h"
#include "Request/DescribeStatusesByUserIdRequest.h"
#include "Task/Rest/DescribeStatusesByUserIdTask.h"
#include "Request/GetStatusRequest.h"
#include "Task/Rest/GetStatusTask.h"
#include "Request/GetStatusByUserIdRequest.h"
#include "Task/Rest/GetStatusByUserIdTask.h"
#include "Request/StartStateMachineByUserIdRequest.h"
#include "Task/Rest/StartStateMachineByUserIdTask.h"
#include "Request/StartStateMachineByStampSheetRequest.h"
#include "Task/Rest/StartStateMachineByStampSheetTask.h"
#include "Request/EmitRequest.h"
#include "Task/Rest/EmitTask.h"
#include "Request/EmitByUserIdRequest.h"
#include "Task/Rest/EmitByUserIdTask.h"
#include "Request/DeleteStatusByUserIdRequest.h"
#include "Task/Rest/DeleteStatusByUserIdTask.h"
#include "Request/ExitStateMachineRequest.h"
#include "Task/Rest/ExitStateMachineTask.h"
#include "Request/ExitStateMachineByUserIdRequest.h"
#include "Task/Rest/ExitStateMachineByUserIdTask.h"

namespace Gs2::StateMachine
{
    class GS2STATEMACHINE_API FGs2StateMachineRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2StateMachineRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeStateMachineMastersTask>> DescribeStateMachineMasters(
            const Request::FDescribeStateMachineMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateStateMachineMasterTask>> UpdateStateMachineMaster(
            const Request::FUpdateStateMachineMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetStateMachineMasterTask>> GetStateMachineMaster(
            const Request::FGetStateMachineMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStateMachineMasterTask>> DeleteStateMachineMaster(
            const Request::FDeleteStateMachineMasterRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FStartStateMachineByUserIdTask>> StartStateMachineByUserId(
            const Request::FStartStateMachineByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FStartStateMachineByStampSheetTask>> StartStateMachineByStampSheet(
            const Request::FStartStateMachineByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEmitTask>> Emit(
            const Request::FEmitRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEmitByUserIdTask>> EmitByUserId(
            const Request::FEmitByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteStatusByUserIdTask>> DeleteStatusByUserId(
            const Request::FDeleteStatusByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExitStateMachineTask>> ExitStateMachine(
            const Request::FExitStateMachineRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExitStateMachineByUserIdTask>> ExitStateMachineByUserId(
            const Request::FExitStateMachineByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2StateMachineRestClient, ESPMode::ThreadSafe> FGs2StateMachineRestClientPtr;
}