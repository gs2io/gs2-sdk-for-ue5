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
#include "Request/DescribeAccountsRequest.h"
#include "Task/Rest/DescribeAccountsTask.h"
#include "Request/CreateAccountRequest.h"
#include "Task/Rest/CreateAccountTask.h"
#include "Request/UpdateTimeOffsetRequest.h"
#include "Task/Rest/UpdateTimeOffsetTask.h"
#include "Request/UpdateBannedRequest.h"
#include "Task/Rest/UpdateBannedTask.h"
#include "Request/AddBanRequest.h"
#include "Task/Rest/AddBanTask.h"
#include "Request/RemoveBanRequest.h"
#include "Task/Rest/RemoveBanTask.h"
#include "Request/GetAccountRequest.h"
#include "Task/Rest/GetAccountTask.h"
#include "Request/DeleteAccountRequest.h"
#include "Task/Rest/DeleteAccountTask.h"
#include "Request/AuthenticationRequest.h"
#include "Task/Rest/AuthenticationTask.h"
#include "Request/DescribeTakeOversRequest.h"
#include "Task/Rest/DescribeTakeOversTask.h"
#include "Request/DescribeTakeOversByUserIdRequest.h"
#include "Task/Rest/DescribeTakeOversByUserIdTask.h"
#include "Request/CreateTakeOverRequest.h"
#include "Task/Rest/CreateTakeOverTask.h"
#include "Request/CreateTakeOverByUserIdRequest.h"
#include "Task/Rest/CreateTakeOverByUserIdTask.h"
#include "Request/GetTakeOverRequest.h"
#include "Task/Rest/GetTakeOverTask.h"
#include "Request/GetTakeOverByUserIdRequest.h"
#include "Task/Rest/GetTakeOverByUserIdTask.h"
#include "Request/UpdateTakeOverRequest.h"
#include "Task/Rest/UpdateTakeOverTask.h"
#include "Request/UpdateTakeOverByUserIdRequest.h"
#include "Task/Rest/UpdateTakeOverByUserIdTask.h"
#include "Request/DeleteTakeOverRequest.h"
#include "Task/Rest/DeleteTakeOverTask.h"
#include "Request/DeleteTakeOverByUserIdentifierRequest.h"
#include "Task/Rest/DeleteTakeOverByUserIdentifierTask.h"
#include "Request/DoTakeOverRequest.h"
#include "Task/Rest/DoTakeOverTask.h"
#include "Request/GetDataOwnerByUserIdRequest.h"
#include "Task/Rest/GetDataOwnerByUserIdTask.h"
#include "Request/DeleteDataOwnerByUserIdRequest.h"
#include "Task/Rest/DeleteDataOwnerByUserIdTask.h"

namespace Gs2::Account
{
    class GS2ACCOUNT_API FGs2AccountRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2AccountRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeAccountsTask>> DescribeAccounts(
            const Request::FDescribeAccountsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateAccountTask>> CreateAccount(
            const Request::FCreateAccountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateTimeOffsetTask>> UpdateTimeOffset(
            const Request::FUpdateTimeOffsetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateBannedTask>> UpdateBanned(
            const Request::FUpdateBannedRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddBanTask>> AddBan(
            const Request::FAddBanRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRemoveBanTask>> RemoveBan(
            const Request::FRemoveBanRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetAccountTask>> GetAccount(
            const Request::FGetAccountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteAccountTask>> DeleteAccount(
            const Request::FDeleteAccountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAuthenticationTask>> Authentication(
            const Request::FAuthenticationRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeTakeOversTask>> DescribeTakeOvers(
            const Request::FDescribeTakeOversRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeTakeOversByUserIdTask>> DescribeTakeOversByUserId(
            const Request::FDescribeTakeOversByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateTakeOverTask>> CreateTakeOver(
            const Request::FCreateTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateTakeOverByUserIdTask>> CreateTakeOverByUserId(
            const Request::FCreateTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetTakeOverTask>> GetTakeOver(
            const Request::FGetTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetTakeOverByUserIdTask>> GetTakeOverByUserId(
            const Request::FGetTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateTakeOverTask>> UpdateTakeOver(
            const Request::FUpdateTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateTakeOverByUserIdTask>> UpdateTakeOverByUserId(
            const Request::FUpdateTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteTakeOverTask>> DeleteTakeOver(
            const Request::FDeleteTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteTakeOverByUserIdentifierTask>> DeleteTakeOverByUserIdentifier(
            const Request::FDeleteTakeOverByUserIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDoTakeOverTask>> DoTakeOver(
            const Request::FDoTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetDataOwnerByUserIdTask>> GetDataOwnerByUserId(
            const Request::FGetDataOwnerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteDataOwnerByUserIdTask>> DeleteDataOwnerByUserId(
            const Request::FDeleteDataOwnerByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2AccountRestClient, ESPMode::ThreadSafe> FGs2AccountRestClientPtr;
}