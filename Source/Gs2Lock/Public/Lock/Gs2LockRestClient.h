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
#include "Request/LockRequest.h"
#include "Task/Rest/LockTask.h"
#include "Request/LockByUserIdRequest.h"
#include "Task/Rest/LockByUserIdTask.h"
#include "Request/UnlockRequest.h"
#include "Task/Rest/UnlockTask.h"
#include "Request/UnlockByUserIdRequest.h"
#include "Task/Rest/UnlockByUserIdTask.h"
#include "Request/GetMutexRequest.h"
#include "Task/Rest/GetMutexTask.h"
#include "Request/GetMutexByUserIdRequest.h"
#include "Task/Rest/GetMutexByUserIdTask.h"
#include "Request/DeleteMutexByUserIdRequest.h"
#include "Task/Rest/DeleteMutexByUserIdTask.h"

namespace Gs2::Lock
{
    class GS2LOCK_API FGs2LockRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2LockRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FLockTask>> Lock(
            const Request::FLockRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FLockByUserIdTask>> LockByUserId(
            const Request::FLockByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnlockTask>> Unlock(
            const Request::FUnlockRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnlockByUserIdTask>> UnlockByUserId(
            const Request::FUnlockByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMutexTask>> GetMutex(
            const Request::FGetMutexRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMutexByUserIdTask>> GetMutexByUserId(
            const Request::FGetMutexByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMutexByUserIdTask>> DeleteMutexByUserId(
            const Request::FDeleteMutexByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2LockRestClient, ESPMode::ThreadSafe> FGs2LockRestClientPtr;
}