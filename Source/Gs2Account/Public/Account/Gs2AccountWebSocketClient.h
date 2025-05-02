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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
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
#include "Request/CreateTakeOverOpenIdConnectRequest.h"
#include "Task/WebSocket/CreateTakeOverOpenIdConnectTask.h"
#include "Request/CreateTakeOverOpenIdConnectAndByUserIdRequest.h"
#include "Task/WebSocket/CreateTakeOverOpenIdConnectAndByUserIdTask.h"
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
#include "Request/DeleteTakeOverByUserIdRequest.h"
#include "Task/WebSocket/DeleteTakeOverByUserIdTask.h"
#include "Request/DoTakeOverRequest.h"
#include "Task/WebSocket/DoTakeOverTask.h"
#include "Request/DoTakeOverOpenIdConnectRequest.h"
#include "Task/WebSocket/DoTakeOverOpenIdConnectTask.h"
#include "Request/GetAuthorizationUrlRequest.h"
#include "Task/WebSocket/GetAuthorizationUrlTask.h"
#include "Request/DescribePlatformIdsRequest.h"
#include "Task/WebSocket/DescribePlatformIdsTask.h"
#include "Request/DescribePlatformIdsByUserIdRequest.h"
#include "Task/WebSocket/DescribePlatformIdsByUserIdTask.h"
#include "Request/CreatePlatformIdRequest.h"
#include "Task/WebSocket/CreatePlatformIdTask.h"
#include "Request/CreatePlatformIdByUserIdRequest.h"
#include "Task/WebSocket/CreatePlatformIdByUserIdTask.h"
#include "Request/GetPlatformIdRequest.h"
#include "Task/WebSocket/GetPlatformIdTask.h"
#include "Request/GetPlatformIdByUserIdRequest.h"
#include "Task/WebSocket/GetPlatformIdByUserIdTask.h"
#include "Request/FindPlatformIdRequest.h"
#include "Task/WebSocket/FindPlatformIdTask.h"
#include "Request/FindPlatformIdByUserIdRequest.h"
#include "Task/WebSocket/FindPlatformIdByUserIdTask.h"
#include "Request/DeletePlatformIdRequest.h"
#include "Task/WebSocket/DeletePlatformIdTask.h"
#include "Request/DeletePlatformIdByUserIdentifierRequest.h"
#include "Task/WebSocket/DeletePlatformIdByUserIdentifierTask.h"
#include "Request/DeletePlatformIdByUserIdRequest.h"
#include "Task/WebSocket/DeletePlatformIdByUserIdTask.h"
#include "Request/GetDataOwnerByUserIdRequest.h"
#include "Task/WebSocket/GetDataOwnerByUserIdTask.h"
#include "Request/UpdateDataOwnerByUserIdRequest.h"
#include "Task/WebSocket/UpdateDataOwnerByUserIdTask.h"
#include "Request/DeleteDataOwnerByUserIdRequest.h"
#include "Task/WebSocket/DeleteDataOwnerByUserIdTask.h"
#include "Request/DescribeTakeOverTypeModelsRequest.h"
#include "Task/WebSocket/DescribeTakeOverTypeModelsTask.h"
#include "Request/GetTakeOverTypeModelRequest.h"
#include "Task/WebSocket/GetTakeOverTypeModelTask.h"
#include "Request/DescribeTakeOverTypeModelMastersRequest.h"
#include "Task/WebSocket/DescribeTakeOverTypeModelMastersTask.h"
#include "Request/CreateTakeOverTypeModelMasterRequest.h"
#include "Task/WebSocket/CreateTakeOverTypeModelMasterTask.h"
#include "Request/GetTakeOverTypeModelMasterRequest.h"
#include "Task/WebSocket/GetTakeOverTypeModelMasterTask.h"
#include "Request/UpdateTakeOverTypeModelMasterRequest.h"
#include "Task/WebSocket/UpdateTakeOverTypeModelMasterTask.h"
#include "Request/DeleteTakeOverTypeModelMasterRequest.h"
#include "Task/WebSocket/DeleteTakeOverTypeModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentModelMasterRequest.h"
#include "Task/WebSocket/GetCurrentModelMasterTask.h"
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Task/WebSocket/PreUpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentModelMasterFromGitHubTask.h"

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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateTakeOverOpenIdConnectTask>> CreateTakeOverOpenIdConnect(
            const Request::FCreateTakeOverOpenIdConnectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateTakeOverOpenIdConnectAndByUserIdTask>> CreateTakeOverOpenIdConnectAndByUserId(
            const Request::FCreateTakeOverOpenIdConnectAndByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTakeOverByUserIdTask>> DeleteTakeOverByUserId(
            const Request::FDeleteTakeOverByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoTakeOverTask>> DoTakeOver(
            const Request::FDoTakeOverRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDoTakeOverOpenIdConnectTask>> DoTakeOverOpenIdConnect(
            const Request::FDoTakeOverOpenIdConnectRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetAuthorizationUrlTask>> GetAuthorizationUrl(
            const Request::FGetAuthorizationUrlRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePlatformIdsTask>> DescribePlatformIds(
            const Request::FDescribePlatformIdsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePlatformIdsByUserIdTask>> DescribePlatformIdsByUserId(
            const Request::FDescribePlatformIdsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreatePlatformIdTask>> CreatePlatformId(
            const Request::FCreatePlatformIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreatePlatformIdByUserIdTask>> CreatePlatformIdByUserId(
            const Request::FCreatePlatformIdByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPlatformIdTask>> GetPlatformId(
            const Request::FGetPlatformIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPlatformIdByUserIdTask>> GetPlatformIdByUserId(
            const Request::FGetPlatformIdByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFindPlatformIdTask>> FindPlatformId(
            const Request::FFindPlatformIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFindPlatformIdByUserIdTask>> FindPlatformIdByUserId(
            const Request::FFindPlatformIdByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePlatformIdTask>> DeletePlatformId(
            const Request::FDeletePlatformIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePlatformIdByUserIdentifierTask>> DeletePlatformIdByUserIdentifier(
            const Request::FDeletePlatformIdByUserIdentifierRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePlatformIdByUserIdTask>> DeletePlatformIdByUserId(
            const Request::FDeletePlatformIdByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetDataOwnerByUserIdTask>> GetDataOwnerByUserId(
            const Request::FGetDataOwnerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDataOwnerByUserIdTask>> UpdateDataOwnerByUserId(
            const Request::FUpdateDataOwnerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDataOwnerByUserIdTask>> DeleteDataOwnerByUserId(
            const Request::FDeleteDataOwnerByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeTakeOverTypeModelsTask>> DescribeTakeOverTypeModels(
            const Request::FDescribeTakeOverTypeModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetTakeOverTypeModelTask>> GetTakeOverTypeModel(
            const Request::FGetTakeOverTypeModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeTakeOverTypeModelMastersTask>> DescribeTakeOverTypeModelMasters(
            const Request::FDescribeTakeOverTypeModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateTakeOverTypeModelMasterTask>> CreateTakeOverTypeModelMaster(
            const Request::FCreateTakeOverTypeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetTakeOverTypeModelMasterTask>> GetTakeOverTypeModelMaster(
            const Request::FGetTakeOverTypeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateTakeOverTypeModelMasterTask>> UpdateTakeOverTypeModelMaster(
            const Request::FUpdateTakeOverTypeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteTakeOverTypeModelMasterTask>> DeleteTakeOverTypeModelMaster(
            const Request::FDeleteTakeOverTypeModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentModelMasterTask>> GetCurrentModelMaster(
            const Request::FGetCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentModelMasterTask>> PreUpdateCurrentModelMaster(
            const Request::FPreUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterTask>> UpdateCurrentModelMaster(
            const Request::FUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentModelMasterFromGitHubTask>> UpdateCurrentModelMasterFromGitHub(
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2AccountWebSocketClient, ESPMode::ThreadSafe> FGs2AccountWebSocketClientPtr;
}