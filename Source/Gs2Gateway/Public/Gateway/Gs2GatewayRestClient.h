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
#include "Request/DescribeWebSocketSessionsRequest.h"
#include "Task/Rest/DescribeWebSocketSessionsTask.h"
#include "Request/DescribeWebSocketSessionsByUserIdRequest.h"
#include "Task/Rest/DescribeWebSocketSessionsByUserIdTask.h"
#include "Request/SetUserIdRequest.h"
#include "Task/Rest/SetUserIdTask.h"
#include "Request/SetUserIdByUserIdRequest.h"
#include "Task/Rest/SetUserIdByUserIdTask.h"
#include "Request/SendNotificationRequest.h"
#include "Task/Rest/SendNotificationTask.h"
#include "Request/DisconnectByUserIdRequest.h"
#include "Task/Rest/DisconnectByUserIdTask.h"
#include "Request/DisconnectAllRequest.h"
#include "Task/Rest/DisconnectAllTask.h"
#include "Request/SetFirebaseTokenRequest.h"
#include "Task/Rest/SetFirebaseTokenTask.h"
#include "Request/SetFirebaseTokenByUserIdRequest.h"
#include "Task/Rest/SetFirebaseTokenByUserIdTask.h"
#include "Request/GetFirebaseTokenRequest.h"
#include "Task/Rest/GetFirebaseTokenTask.h"
#include "Request/GetFirebaseTokenByUserIdRequest.h"
#include "Task/Rest/GetFirebaseTokenByUserIdTask.h"
#include "Request/DeleteFirebaseTokenRequest.h"
#include "Task/Rest/DeleteFirebaseTokenTask.h"
#include "Request/DeleteFirebaseTokenByUserIdRequest.h"
#include "Task/Rest/DeleteFirebaseTokenByUserIdTask.h"
#include "Request/SendMobileNotificationByUserIdRequest.h"
#include "Task/Rest/SendMobileNotificationByUserIdTask.h"

namespace Gs2::Gateway
{
    class GS2GATEWAY_API FGs2GatewayRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2GatewayRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeWebSocketSessionsTask>> DescribeWebSocketSessions(
            const Request::FDescribeWebSocketSessionsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeWebSocketSessionsByUserIdTask>> DescribeWebSocketSessionsByUserId(
            const Request::FDescribeWebSocketSessionsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetUserIdTask>> SetUserId(
            const Request::FSetUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetUserIdByUserIdTask>> SetUserIdByUserId(
            const Request::FSetUserIdByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendNotificationTask>> SendNotification(
            const Request::FSendNotificationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDisconnectByUserIdTask>> DisconnectByUserId(
            const Request::FDisconnectByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDisconnectAllTask>> DisconnectAll(
            const Request::FDisconnectAllRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetFirebaseTokenTask>> SetFirebaseToken(
            const Request::FSetFirebaseTokenRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetFirebaseTokenByUserIdTask>> SetFirebaseTokenByUserId(
            const Request::FSetFirebaseTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFirebaseTokenTask>> GetFirebaseToken(
            const Request::FGetFirebaseTokenRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFirebaseTokenByUserIdTask>> GetFirebaseTokenByUserId(
            const Request::FGetFirebaseTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFirebaseTokenTask>> DeleteFirebaseToken(
            const Request::FDeleteFirebaseTokenRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFirebaseTokenByUserIdTask>> DeleteFirebaseTokenByUserId(
            const Request::FDeleteFirebaseTokenByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendMobileNotificationByUserIdTask>> SendMobileNotificationByUserId(
            const Request::FSendMobileNotificationByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2GatewayRestClient, ESPMode::ThreadSafe> FGs2GatewayRestClientPtr;
}