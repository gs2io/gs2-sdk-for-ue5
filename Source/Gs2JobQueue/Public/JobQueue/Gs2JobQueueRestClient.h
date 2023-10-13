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
#include "Request/DescribeJobsByUserIdRequest.h"
#include "Task/Rest/DescribeJobsByUserIdTask.h"
#include "Request/GetJobByUserIdRequest.h"
#include "Task/Rest/GetJobByUserIdTask.h"
#include "Request/PushByUserIdRequest.h"
#include "Task/Rest/PushByUserIdTask.h"
#include "Request/RunRequest.h"
#include "Task/Rest/RunTask.h"
#include "Request/RunByUserIdRequest.h"
#include "Task/Rest/RunByUserIdTask.h"
#include "Request/DeleteJobByUserIdRequest.h"
#include "Task/Rest/DeleteJobByUserIdTask.h"
#include "Request/PushByStampSheetRequest.h"
#include "Task/Rest/PushByStampSheetTask.h"
#include "Request/DeleteByStampTaskRequest.h"
#include "Task/Rest/DeleteByStampTaskTask.h"
#include "Request/GetJobResultRequest.h"
#include "Task/Rest/GetJobResultTask.h"
#include "Request/GetJobResultByUserIdRequest.h"
#include "Task/Rest/GetJobResultByUserIdTask.h"
#include "Request/DescribeDeadLetterJobsByUserIdRequest.h"
#include "Task/Rest/DescribeDeadLetterJobsByUserIdTask.h"
#include "Request/GetDeadLetterJobByUserIdRequest.h"
#include "Task/Rest/GetDeadLetterJobByUserIdTask.h"
#include "Request/DeleteDeadLetterJobByUserIdRequest.h"
#include "Task/Rest/DeleteDeadLetterJobByUserIdTask.h"

namespace Gs2::JobQueue
{
    class GS2JOBQUEUE_API FGs2JobQueueRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2JobQueueRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeJobsByUserIdTask>> DescribeJobsByUserId(
            const Request::FDescribeJobsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJobByUserIdTask>> GetJobByUserId(
            const Request::FGetJobByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPushByUserIdTask>> PushByUserId(
            const Request::FPushByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunTask>> Run(
            const Request::FRunRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRunByUserIdTask>> RunByUserId(
            const Request::FRunByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteJobByUserIdTask>> DeleteJobByUserId(
            const Request::FDeleteJobByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPushByStampSheetTask>> PushByStampSheet(
            const Request::FPushByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteByStampTaskTask>> DeleteByStampTask(
            const Request::FDeleteByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJobResultTask>> GetJobResult(
            const Request::FGetJobResultRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJobResultByUserIdTask>> GetJobResultByUserId(
            const Request::FGetJobResultByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeDeadLetterJobsByUserIdTask>> DescribeDeadLetterJobsByUserId(
            const Request::FDescribeDeadLetterJobsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDeadLetterJobByUserIdTask>> GetDeadLetterJobByUserId(
            const Request::FGetDeadLetterJobByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteDeadLetterJobByUserIdTask>> DeleteDeadLetterJobByUserId(
            const Request::FDeleteDeadLetterJobByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2JobQueueRestClient, ESPMode::ThreadSafe> FGs2JobQueueRestClientPtr;
}