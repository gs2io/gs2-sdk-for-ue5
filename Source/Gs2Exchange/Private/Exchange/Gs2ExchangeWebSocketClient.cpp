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

#include "Exchange/Gs2ExchangeWebSocketClient.h"

namespace Gs2::Exchange
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2ExchangeWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2ExchangeWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2ExchangeWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2ExchangeWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2ExchangeWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2ExchangeWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRateModelsTask>> FGs2ExchangeWebSocketClient::DescribeRateModels(
        const Request::FDescribeRateModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRateModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRateModelTask>> FGs2ExchangeWebSocketClient::GetRateModel(
        const Request::FGetRateModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRateModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRateModelMastersTask>> FGs2ExchangeWebSocketClient::DescribeRateModelMasters(
        const Request::FDescribeRateModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRateModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRateModelMasterTask>> FGs2ExchangeWebSocketClient::CreateRateModelMaster(
        const Request::FCreateRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRateModelMasterTask>> FGs2ExchangeWebSocketClient::GetRateModelMaster(
        const Request::FGetRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRateModelMasterTask>> FGs2ExchangeWebSocketClient::UpdateRateModelMaster(
        const Request::FUpdateRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRateModelMasterTask>> FGs2ExchangeWebSocketClient::DeleteRateModelMaster(
        const Request::FDeleteRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIncrementalRateModelsTask>> FGs2ExchangeWebSocketClient::DescribeIncrementalRateModels(
        const Request::FDescribeIncrementalRateModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeIncrementalRateModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetIncrementalRateModelTask>> FGs2ExchangeWebSocketClient::GetIncrementalRateModel(
        const Request::FGetIncrementalRateModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetIncrementalRateModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIncrementalRateModelMastersTask>> FGs2ExchangeWebSocketClient::DescribeIncrementalRateModelMasters(
        const Request::FDescribeIncrementalRateModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeIncrementalRateModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateIncrementalRateModelMasterTask>> FGs2ExchangeWebSocketClient::CreateIncrementalRateModelMaster(
        const Request::FCreateIncrementalRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateIncrementalRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetIncrementalRateModelMasterTask>> FGs2ExchangeWebSocketClient::GetIncrementalRateModelMaster(
        const Request::FGetIncrementalRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetIncrementalRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateIncrementalRateModelMasterTask>> FGs2ExchangeWebSocketClient::UpdateIncrementalRateModelMaster(
        const Request::FUpdateIncrementalRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateIncrementalRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteIncrementalRateModelMasterTask>> FGs2ExchangeWebSocketClient::DeleteIncrementalRateModelMaster(
        const Request::FDeleteIncrementalRateModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteIncrementalRateModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExchangeTask>> FGs2ExchangeWebSocketClient::Exchange(
        const Request::FExchangeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExchangeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExchangeByUserIdTask>> FGs2ExchangeWebSocketClient::ExchangeByUserId(
        const Request::FExchangeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExchangeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExchangeByStampSheetTask>> FGs2ExchangeWebSocketClient::ExchangeByStampSheet(
        const Request::FExchangeByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExchangeByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementalExchangeTask>> FGs2ExchangeWebSocketClient::IncrementalExchange(
        const Request::FIncrementalExchangeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncrementalExchangeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementalExchangeByUserIdTask>> FGs2ExchangeWebSocketClient::IncrementalExchangeByUserId(
        const Request::FIncrementalExchangeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncrementalExchangeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementalExchangeByStampSheetTask>> FGs2ExchangeWebSocketClient::IncrementalExchangeByStampSheet(
        const Request::FIncrementalExchangeByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncrementalExchangeByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUnlockIncrementalExchangeByUserIdTask>> FGs2ExchangeWebSocketClient::UnlockIncrementalExchangeByUserId(
        const Request::FUnlockIncrementalExchangeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUnlockIncrementalExchangeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUnlockIncrementalExchangeByStampSheetTask>> FGs2ExchangeWebSocketClient::UnlockIncrementalExchangeByStampSheet(
        const Request::FUnlockIncrementalExchangeByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUnlockIncrementalExchangeByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2ExchangeWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentRateMasterTask>> FGs2ExchangeWebSocketClient::GetCurrentRateMaster(
        const Request::FGetCurrentRateMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentRateMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterTask>> FGs2ExchangeWebSocketClient::UpdateCurrentRateMaster(
        const Request::FUpdateCurrentRateMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterFromGitHubTask>> FGs2ExchangeWebSocketClient::UpdateCurrentRateMasterFromGitHub(
        const Request::FUpdateCurrentRateMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentRateMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateAwaitByUserIdTask>> FGs2ExchangeWebSocketClient::CreateAwaitByUserId(
        const Request::FCreateAwaitByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateAwaitByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAwaitsTask>> FGs2ExchangeWebSocketClient::DescribeAwaits(
        const Request::FDescribeAwaitsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeAwaitsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeAwaitsByUserIdTask>> FGs2ExchangeWebSocketClient::DescribeAwaitsByUserId(
        const Request::FDescribeAwaitsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeAwaitsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetAwaitTask>> FGs2ExchangeWebSocketClient::GetAwait(
        const Request::FGetAwaitRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetAwaitTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetAwaitByUserIdTask>> FGs2ExchangeWebSocketClient::GetAwaitByUserId(
        const Request::FGetAwaitByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetAwaitByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireTask>> FGs2ExchangeWebSocketClient::Acquire(
        const Request::FAcquireRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireByUserIdTask>> FGs2ExchangeWebSocketClient::AcquireByUserId(
        const Request::FAcquireByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireForceByUserIdTask>> FGs2ExchangeWebSocketClient::AcquireForceByUserId(
        const Request::FAcquireForceByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireForceByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSkipTask>> FGs2ExchangeWebSocketClient::Skip(
        const Request::FSkipRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSkipTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSkipByUserIdTask>> FGs2ExchangeWebSocketClient::SkipByUserId(
        const Request::FSkipByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSkipByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAwaitTask>> FGs2ExchangeWebSocketClient::DeleteAwait(
        const Request::FDeleteAwaitRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteAwaitTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAwaitByUserIdTask>> FGs2ExchangeWebSocketClient::DeleteAwaitByUserId(
        const Request::FDeleteAwaitByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteAwaitByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateAwaitByStampSheetTask>> FGs2ExchangeWebSocketClient::CreateAwaitByStampSheet(
        const Request::FCreateAwaitByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateAwaitByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteAwaitByStampTaskTask>> FGs2ExchangeWebSocketClient::DeleteAwaitByStampTask(
        const Request::FDeleteAwaitByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteAwaitByStampTaskTask>>(
            Session,
            Request
        );
    }
}