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

#include "Enchant/Gs2EnchantWebSocketClient.h"

namespace Gs2::Enchant
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2EnchantWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2EnchantWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2EnchantWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2EnchantWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2EnchantWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2EnchantWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> FGs2EnchantWebSocketClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2EnchantWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2EnchantWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2EnchantWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2EnchantWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2EnchantWebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2EnchantWebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2EnchantWebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterModelsTask>> FGs2EnchantWebSocketClient::DescribeBalanceParameterModels(
        const Request::FDescribeBalanceParameterModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterModelTask>> FGs2EnchantWebSocketClient::GetBalanceParameterModel(
        const Request::FGetBalanceParameterModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBalanceParameterModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterModelMastersTask>> FGs2EnchantWebSocketClient::DescribeBalanceParameterModelMasters(
        const Request::FDescribeBalanceParameterModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBalanceParameterModelMasterTask>> FGs2EnchantWebSocketClient::CreateBalanceParameterModelMaster(
        const Request::FCreateBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterModelMasterTask>> FGs2EnchantWebSocketClient::GetBalanceParameterModelMaster(
        const Request::FGetBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBalanceParameterModelMasterTask>> FGs2EnchantWebSocketClient::UpdateBalanceParameterModelMaster(
        const Request::FUpdateBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBalanceParameterModelMasterTask>> FGs2EnchantWebSocketClient::DeleteBalanceParameterModelMaster(
        const Request::FDeleteBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterModelsTask>> FGs2EnchantWebSocketClient::DescribeRarityParameterModels(
        const Request::FDescribeRarityParameterModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRarityParameterModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterModelTask>> FGs2EnchantWebSocketClient::GetRarityParameterModel(
        const Request::FGetRarityParameterModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRarityParameterModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterModelMastersTask>> FGs2EnchantWebSocketClient::DescribeRarityParameterModelMasters(
        const Request::FDescribeRarityParameterModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRarityParameterModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRarityParameterModelMasterTask>> FGs2EnchantWebSocketClient::CreateRarityParameterModelMaster(
        const Request::FCreateRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterModelMasterTask>> FGs2EnchantWebSocketClient::GetRarityParameterModelMaster(
        const Request::FGetRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRarityParameterModelMasterTask>> FGs2EnchantWebSocketClient::UpdateRarityParameterModelMaster(
        const Request::FUpdateRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRarityParameterModelMasterTask>> FGs2EnchantWebSocketClient::DeleteRarityParameterModelMaster(
        const Request::FDeleteRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2EnchantWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentParameterMasterTask>> FGs2EnchantWebSocketClient::GetCurrentParameterMaster(
        const Request::FGetCurrentParameterMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentParameterMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentParameterMasterTask>> FGs2EnchantWebSocketClient::PreUpdateCurrentParameterMaster(
        const Request::FPreUpdateCurrentParameterMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPreUpdateCurrentParameterMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentParameterMasterTask>> FGs2EnchantWebSocketClient::UpdateCurrentParameterMaster(
        const Request::FUpdateCurrentParameterMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentParameterMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentParameterMasterFromGitHubTask>> FGs2EnchantWebSocketClient::UpdateCurrentParameterMasterFromGitHub(
        const Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentParameterMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterStatusesTask>> FGs2EnchantWebSocketClient::DescribeBalanceParameterStatuses(
        const Request::FDescribeBalanceParameterStatusesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterStatusesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterStatusesByUserIdTask>> FGs2EnchantWebSocketClient::DescribeBalanceParameterStatusesByUserId(
        const Request::FDescribeBalanceParameterStatusesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBalanceParameterStatusesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterStatusTask>> FGs2EnchantWebSocketClient::GetBalanceParameterStatus(
        const Request::FGetBalanceParameterStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBalanceParameterStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBalanceParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::GetBalanceParameterStatusByUserId(
        const Request::FGetBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBalanceParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::DeleteBalanceParameterStatusByUserId(
        const Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawBalanceParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::ReDrawBalanceParameterStatusByUserId(
        const Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReDrawBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawBalanceParameterStatusByStampSheetTask>> FGs2EnchantWebSocketClient::ReDrawBalanceParameterStatusByStampSheet(
        const Request::FReDrawBalanceParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReDrawBalanceParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetBalanceParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::SetBalanceParameterStatusByUserId(
        const Request::FSetBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetBalanceParameterStatusByStampSheetTask>> FGs2EnchantWebSocketClient::SetBalanceParameterStatusByStampSheet(
        const Request::FSetBalanceParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetBalanceParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterStatusesTask>> FGs2EnchantWebSocketClient::DescribeRarityParameterStatuses(
        const Request::FDescribeRarityParameterStatusesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRarityParameterStatusesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRarityParameterStatusesByUserIdTask>> FGs2EnchantWebSocketClient::DescribeRarityParameterStatusesByUserId(
        const Request::FDescribeRarityParameterStatusesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRarityParameterStatusesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterStatusTask>> FGs2EnchantWebSocketClient::GetRarityParameterStatus(
        const Request::FGetRarityParameterStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRarityParameterStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRarityParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::GetRarityParameterStatusByUserId(
        const Request::FGetRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRarityParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::DeleteRarityParameterStatusByUserId(
        const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawRarityParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::ReDrawRarityParameterStatusByUserId(
        const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReDrawRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReDrawRarityParameterStatusByStampSheetTask>> FGs2EnchantWebSocketClient::ReDrawRarityParameterStatusByStampSheet(
        const Request::FReDrawRarityParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReDrawRarityParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddRarityParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::AddRarityParameterStatusByUserId(
        const Request::FAddRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddRarityParameterStatusByStampSheetTask>> FGs2EnchantWebSocketClient::AddRarityParameterStatusByStampSheet(
        const Request::FAddRarityParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddRarityParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusTask>> FGs2EnchantWebSocketClient::VerifyRarityParameterStatus(
        const Request::FVerifyRarityParameterStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::VerifyRarityParameterStatusByUserId(
        const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusByStampTaskTask>> FGs2EnchantWebSocketClient::VerifyRarityParameterStatusByStampTask(
        const Request::FVerifyRarityParameterStatusByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyRarityParameterStatusByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRarityParameterStatusByUserIdTask>> FGs2EnchantWebSocketClient::SetRarityParameterStatusByUserId(
        const Request::FSetRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRarityParameterStatusByStampSheetTask>> FGs2EnchantWebSocketClient::SetRarityParameterStatusByStampSheet(
        const Request::FSetRarityParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRarityParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }
}