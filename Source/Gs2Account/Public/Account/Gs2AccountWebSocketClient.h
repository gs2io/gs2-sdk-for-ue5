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
#include "Core/Net/AbstractWebSocketGs2Client.h"
#include "Request/DescribeNamespacesRequest.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"
#include "Request/CreateNamespaceRequest.h"
#include "Task/WebSocket/CreateNamespaceTask.h"
#include "Request/GetNamespaceStatusRequest.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"
#include "Request/GetNamespaceRequest.h"
#include "Task/WebSocket/GetNamespaceTask.h"
#include "Request/UpdateNamespaceRequest.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"
#include "Request/DeleteNamespaceRequest.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"
#include "Request/DescribeAccountsRequest.h"
#include "Task/WebSocket/DescribeAccountsTask.h"
#include "Request/CreateAccountRequest.h"
#include "Task/WebSocket/CreateAccountTask.h"
#include "Request/UpdateTimeOffsetRequest.h"
#include "Task/WebSocket/UpdateTimeOffsetTask.h"
#include "Request/UpdateBannedRequest.h"
#include "Task/WebSocket/UpdateBannedTask.h"
#include "Request/AddBanRequest.h"
#include "Task/WebSocket/AddBanTask.h"
#include "Request/RemoveBanRequest.h"
#include "Task/WebSocket/RemoveBanTask.h"
#include "Request/GetAccountRequest.h"
#include "Task/WebSocket/GetAccountTask.h"
#include "Request/DeleteAccountRequest.h"
#include "Task/WebSocket/DeleteAccountTask.h"
#include "Request/AuthenticationRequest.h"
#include "Task/WebSocket/AuthenticationTask.h"
#include "Request/DescribeTakeOversRequest.h"
#include "Task/WebSocket/DescribeTakeOversTask.h"
#include "Request/DescribeTakeOversByUserIdRequest.h"
#include "Task/WebSocket/DescribeTakeOversByUserIdTask.h"
#include "Request/CreateTakeOverRequest.h"
#include "Task/WebSocket/CreateTakeOverTask.h"
#include "Request/CreateTakeOverByUserIdRequest.h"
#include "Task/WebSocket/CreateTakeOverByUserIdTask.h"
#include "Request/GetTakeOverRequest.h"
#include "Task/WebSocket/GetTakeOverTask.h"
#include "Request/GetTakeOverByUserIdRequest.h"
#include "Task/WebSocket/GetTakeOverByUserIdTask.h"
#include "Request/UpdateTakeOverRequest.h"
#include "Task/WebSocket/UpdateTakeOverTask.h"
#include "Request/UpdateTakeOverByUserIdRequest.h"
#include "Task/WebSocket/UpdateTakeOverByUserIdTask.h"
#include "Request/DeleteTakeOverRequest.h"
#include "Task/WebSocket/DeleteTakeOverTask.h"
#include "Request/DeleteTakeOverByUserIdentifierRequest.h"
#include "Task/WebSocket/DeleteTakeOverByUserIdentifierTask.h"
#include "Request/DoTakeOverRequest.h"
#include "Task/WebSocket/DoTakeOverTask.h"
#include "Request/GetDataOwnerByUserIdRequest.h"
#include "Task/WebSocket/GetDataOwnerByUserIdTask.h"
#include "Request/DeleteDataOwnerByUserIdRequest.h"
#include "Task/WebSocket/DeleteDataOwnerByUserIdTask.h"

namespace Gs2::Account
{
    class GS2ACCOUNT_API FGs2AccountWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2AccountWebSocketClient(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session
        ): FAbstractWebSocketGs2Client(Session)
        {
        }

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> DescribeNamespaces(
            const Request::FDescribeNamespacesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> CreateNamespace(
            const Request::FCreateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> GetNamespaceStatus(
            const Request::FGetNamespaceStatusRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> GetNamespace(
            const Request::FGetNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> UpdateNamespace(
            const Request::FUpdateNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> DeleteNamespace(
            const Request::FDeleteNamespaceRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAccountsTask>> DescribeAccounts(
            const Request::FDescribeAccountsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateAccountTask>> CreateAccount(
            const Request::FCreateAccountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateTimeOffsetTask>> UpdateTimeOffset(
            const Request::FUpdateTimeOffsetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBannedTask>> UpdateBanned(
            const Request::FUpdateBannedRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddBanTask>> AddBan(
            const Request::FAddBanRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRemoveBanTask>> RemoveBan(
            const Request::FRemoveBanRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAccountTask>> GetAccount(
            const Request::FGetAccountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAccountTask>> DeleteAccount(
            const Request::FDeleteAccountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAuthenticationTask>> Authentication(
            const Request::FAuthenticationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeTakeOversTask>> DescribeTakeOvers(
            const Request::FDescribeTakeOversRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeTakeOversByUserIdTask>> DescribeTakeOversByUserId(
            const Request::FDescribeTakeOversByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateTakeOverTask>> CreateTakeOver(
            const Request::FCreateTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateTakeOverByUserIdTask>> CreateTakeOverByUserId(
            const Request::FCreateTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetTakeOverTask>> GetTakeOver(
            const Request::FGetTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetTakeOverByUserIdTask>> GetTakeOverByUserId(
            const Request::FGetTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateTakeOverTask>> UpdateTakeOver(
            const Request::FUpdateTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateTakeOverByUserIdTask>> UpdateTakeOverByUserId(
            const Request::FUpdateTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTakeOverTask>> DeleteTakeOver(
            const Request::FDeleteTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTakeOverByUserIdentifierTask>> DeleteTakeOverByUserIdentifier(
            const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoTakeOverTask>> DoTakeOver(
            const Request::FDoTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDataOwnerByUserIdTask>> GetDataOwnerByUserId(
            const Request::FGetDataOwnerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDataOwnerByUserIdTask>> DeleteDataOwnerByUserId(
            const Request::FDeleteDataOwnerByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2AccountWebSocketClient, ESPMode::ThreadSafe> FGs2AccountWebSocketClientPtr;
}