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
#include "Request/DescribeProgressesRequest.h"
#include "Task/Rest/DescribeProgressesTask.h"
#include "Request/GetProgressRequest.h"
#include "Task/Rest/GetProgressTask.h"
#include "Request/DescribeOutputsRequest.h"
#include "Task/Rest/DescribeOutputsTask.h"
#include "Request/GetOutputRequest.h"
#include "Task/Rest/GetOutputTask.h"
#include "Request/PrepareUpdateCurrentNewsMasterRequest.h"
#include "Task/Rest/PrepareUpdateCurrentNewsMasterTask.h"
#include "Request/UpdateCurrentNewsMasterRequest.h"
#include "Task/Rest/UpdateCurrentNewsMasterTask.h"
#include "Request/PrepareUpdateCurrentNewsMasterFromGitHubRequest.h"
#include "Task/Rest/PrepareUpdateCurrentNewsMasterFromGitHubTask.h"
#include "Request/DescribeNewsRequest.h"
#include "Task/Rest/DescribeNewsTask.h"
#include "Request/DescribeNewsByUserIdRequest.h"
#include "Task/Rest/DescribeNewsByUserIdTask.h"
#include "Request/WantGrantRequest.h"
#include "Task/Rest/WantGrantTask.h"
#include "Request/WantGrantByUserIdRequest.h"
#include "Task/Rest/WantGrantByUserIdTask.h"

namespace Gs2::News
{
    class GS2NEWS_API FGs2NewsRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2NewsRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeProgressesTask>> DescribeProgresses(
            const Request::FDescribeProgressesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetProgressTask>> GetProgress(
            const Request::FGetProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeOutputsTask>> DescribeOutputs(
            const Request::FDescribeOutputsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetOutputTask>> GetOutput(
            const Request::FGetOutputRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareUpdateCurrentNewsMasterTask>> PrepareUpdateCurrentNewsMaster(
            const Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentNewsMasterTask>> UpdateCurrentNewsMaster(
            const Request::FUpdateCurrentNewsMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareUpdateCurrentNewsMasterFromGitHubTask>> PrepareUpdateCurrentNewsMasterFromGitHub(
            const Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNewsTask>> DescribeNews(
            const Request::FDescribeNewsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeNewsByUserIdTask>> DescribeNewsByUserId(
            const Request::FDescribeNewsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWantGrantTask>> WantGrant(
            const Request::FWantGrantRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWantGrantByUserIdTask>> WantGrantByUserId(
            const Request::FWantGrantByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2NewsRestClient, ESPMode::ThreadSafe> FGs2NewsRestClientPtr;
}