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

#include "Distributor/Gs2DistributorWebSocketClient.h"

namespace Gs2::Distributor
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2DistributorWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2DistributorWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2DistributorWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2DistributorWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2DistributorWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2DistributorWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> FGs2DistributorWebSocketClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDistributorModelMastersTask>> FGs2DistributorWebSocketClient::DescribeDistributorModelMasters(
        const Request::FDescribeDistributorModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDistributorModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateDistributorModelMasterTask>> FGs2DistributorWebSocketClient::CreateDistributorModelMaster(
        const Request::FCreateDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetDistributorModelMasterTask>> FGs2DistributorWebSocketClient::GetDistributorModelMaster(
        const Request::FGetDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateDistributorModelMasterTask>> FGs2DistributorWebSocketClient::UpdateDistributorModelMaster(
        const Request::FUpdateDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteDistributorModelMasterTask>> FGs2DistributorWebSocketClient::DeleteDistributorModelMaster(
        const Request::FDeleteDistributorModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteDistributorModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeDistributorModelsTask>> FGs2DistributorWebSocketClient::DescribeDistributorModels(
        const Request::FDescribeDistributorModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeDistributorModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetDistributorModelTask>> FGs2DistributorWebSocketClient::GetDistributorModel(
        const Request::FGetDistributorModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetDistributorModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2DistributorWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentDistributorMasterTask>> FGs2DistributorWebSocketClient::GetCurrentDistributorMaster(
        const Request::FGetCurrentDistributorMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentDistributorMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentDistributorMasterTask>> FGs2DistributorWebSocketClient::PreUpdateCurrentDistributorMaster(
        const Request::FPreUpdateCurrentDistributorMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPreUpdateCurrentDistributorMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentDistributorMasterTask>> FGs2DistributorWebSocketClient::UpdateCurrentDistributorMaster(
        const Request::FUpdateCurrentDistributorMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentDistributorMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentDistributorMasterFromGitHubTask>> FGs2DistributorWebSocketClient::UpdateCurrentDistributorMasterFromGitHub(
        const Request::FUpdateCurrentDistributorMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentDistributorMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDistributeTask>> FGs2DistributorWebSocketClient::Distribute(
        const Request::FDistributeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDistributeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDistributeWithoutOverflowProcessTask>> FGs2DistributorWebSocketClient::DistributeWithoutOverflowProcess(
        const Request::FDistributeWithoutOverflowProcessRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDistributeWithoutOverflowProcessTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunVerifyTaskTask>> FGs2DistributorWebSocketClient::RunVerifyTask(
        const Request::FRunVerifyTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunVerifyTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampTaskTask>> FGs2DistributorWebSocketClient::RunStampTask(
        const Request::FRunStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetTask>> FGs2DistributorWebSocketClient::RunStampSheet(
        const Request::FRunStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetExpressTask>> FGs2DistributorWebSocketClient::RunStampSheetExpress(
        const Request::FRunStampSheetExpressRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunStampSheetExpressTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunVerifyTaskWithoutNamespaceTask>> FGs2DistributorWebSocketClient::RunVerifyTaskWithoutNamespace(
        const Request::FRunVerifyTaskWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunVerifyTaskWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampTaskWithoutNamespaceTask>> FGs2DistributorWebSocketClient::RunStampTaskWithoutNamespace(
        const Request::FRunStampTaskWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunStampTaskWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetWithoutNamespaceTask>> FGs2DistributorWebSocketClient::RunStampSheetWithoutNamespace(
        const Request::FRunStampSheetWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunStampSheetWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunStampSheetExpressWithoutNamespaceTask>> FGs2DistributorWebSocketClient::RunStampSheetExpressWithoutNamespace(
        const Request::FRunStampSheetExpressWithoutNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunStampSheetExpressWithoutNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetTransactionDefaultConfigTask>> FGs2DistributorWebSocketClient::SetTransactionDefaultConfig(
        const Request::FSetTransactionDefaultConfigRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetTransactionDefaultConfigTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetTransactionDefaultConfigByUserIdTask>> FGs2DistributorWebSocketClient::SetTransactionDefaultConfigByUserId(
        const Request::FSetTransactionDefaultConfigByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetTransactionDefaultConfigByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FFreezeMasterDataTask>> FGs2DistributorWebSocketClient::FreezeMasterData(
        const Request::FFreezeMasterDataRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FFreezeMasterDataTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FFreezeMasterDataByUserIdTask>> FGs2DistributorWebSocketClient::FreezeMasterDataByUserId(
        const Request::FFreezeMasterDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FFreezeMasterDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSignFreezeMasterDataTimestampTask>> FGs2DistributorWebSocketClient::SignFreezeMasterDataTimestamp(
        const Request::FSignFreezeMasterDataTimestampRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSignFreezeMasterDataTimestampTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FFreezeMasterDataBySignedTimestampTask>> FGs2DistributorWebSocketClient::FreezeMasterDataBySignedTimestamp(
        const Request::FFreezeMasterDataBySignedTimestampRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FFreezeMasterDataBySignedTimestampTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FFreezeMasterDataByTimestampTask>> FGs2DistributorWebSocketClient::FreezeMasterDataByTimestamp(
        const Request::FFreezeMasterDataByTimestampRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FFreezeMasterDataByTimestampTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FBatchExecuteApiTask>> FGs2DistributorWebSocketClient::BatchExecuteApi(
        const Request::FBatchExecuteApiRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FBatchExecuteApiTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIfExpressionByUserIdTask>> FGs2DistributorWebSocketClient::IfExpressionByUserId(
        const Request::FIfExpressionByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIfExpressionByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAndExpressionByUserIdTask>> FGs2DistributorWebSocketClient::AndExpressionByUserId(
        const Request::FAndExpressionByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAndExpressionByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FOrExpressionByUserIdTask>> FGs2DistributorWebSocketClient::OrExpressionByUserId(
        const Request::FOrExpressionByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FOrExpressionByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIfExpressionByStampTaskTask>> FGs2DistributorWebSocketClient::IfExpressionByStampTask(
        const Request::FIfExpressionByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIfExpressionByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAndExpressionByStampTaskTask>> FGs2DistributorWebSocketClient::AndExpressionByStampTask(
        const Request::FAndExpressionByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAndExpressionByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FOrExpressionByStampTaskTask>> FGs2DistributorWebSocketClient::OrExpressionByStampTask(
        const Request::FOrExpressionByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FOrExpressionByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStampSheetResultTask>> FGs2DistributorWebSocketClient::GetStampSheetResult(
        const Request::FGetStampSheetResultRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStampSheetResultTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStampSheetResultByUserIdTask>> FGs2DistributorWebSocketClient::GetStampSheetResultByUserId(
        const Request::FGetStampSheetResultByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStampSheetResultByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRunTransactionTask>> FGs2DistributorWebSocketClient::RunTransaction(
        const Request::FRunTransactionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRunTransactionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetTransactionResultTask>> FGs2DistributorWebSocketClient::GetTransactionResult(
        const Request::FGetTransactionResultRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetTransactionResultTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetTransactionResultByUserIdTask>> FGs2DistributorWebSocketClient::GetTransactionResultByUserId(
        const Request::FGetTransactionResultByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetTransactionResultByUserIdTask>>(
            Session,
            Request
        );
    }
}