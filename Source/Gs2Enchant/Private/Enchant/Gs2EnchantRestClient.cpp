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

#include "Enchant/Gs2EnchantRestClient.h"

namespace Gs2::Enchant
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2EnchantRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2EnchantRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2EnchantRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2EnchantRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2EnchantRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2EnchantRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterModelsTask>> FGs2EnchantRestClient::DescribeBalanceParameterModels(
        const Request::FDescribeBalanceParameterModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBalanceParameterModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterModelTask>> FGs2EnchantRestClient::GetBalanceParameterModel(
        const Request::FGetBalanceParameterModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBalanceParameterModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterModelMastersTask>> FGs2EnchantRestClient::DescribeBalanceParameterModelMasters(
        const Request::FDescribeBalanceParameterModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBalanceParameterModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateBalanceParameterModelMasterTask>> FGs2EnchantRestClient::CreateBalanceParameterModelMaster(
        const Request::FCreateBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterModelMasterTask>> FGs2EnchantRestClient::GetBalanceParameterModelMaster(
        const Request::FGetBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateBalanceParameterModelMasterTask>> FGs2EnchantRestClient::UpdateBalanceParameterModelMaster(
        const Request::FUpdateBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteBalanceParameterModelMasterTask>> FGs2EnchantRestClient::DeleteBalanceParameterModelMaster(
        const Request::FDeleteBalanceParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteBalanceParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterModelsTask>> FGs2EnchantRestClient::DescribeRarityParameterModels(
        const Request::FDescribeRarityParameterModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRarityParameterModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterModelTask>> FGs2EnchantRestClient::GetRarityParameterModel(
        const Request::FGetRarityParameterModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRarityParameterModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterModelMastersTask>> FGs2EnchantRestClient::DescribeRarityParameterModelMasters(
        const Request::FDescribeRarityParameterModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRarityParameterModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateRarityParameterModelMasterTask>> FGs2EnchantRestClient::CreateRarityParameterModelMaster(
        const Request::FCreateRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterModelMasterTask>> FGs2EnchantRestClient::GetRarityParameterModelMaster(
        const Request::FGetRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateRarityParameterModelMasterTask>> FGs2EnchantRestClient::UpdateRarityParameterModelMaster(
        const Request::FUpdateRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRarityParameterModelMasterTask>> FGs2EnchantRestClient::DeleteRarityParameterModelMaster(
        const Request::FDeleteRarityParameterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRarityParameterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2EnchantRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentParameterMasterTask>> FGs2EnchantRestClient::GetCurrentParameterMaster(
        const Request::FGetCurrentParameterMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentParameterMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentParameterMasterTask>> FGs2EnchantRestClient::UpdateCurrentParameterMaster(
        const Request::FUpdateCurrentParameterMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentParameterMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentParameterMasterFromGitHubTask>> FGs2EnchantRestClient::UpdateCurrentParameterMasterFromGitHub(
        const Request::FUpdateCurrentParameterMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentParameterMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterStatusesTask>> FGs2EnchantRestClient::DescribeBalanceParameterStatuses(
        const Request::FDescribeBalanceParameterStatusesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBalanceParameterStatusesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBalanceParameterStatusesByUserIdTask>> FGs2EnchantRestClient::DescribeBalanceParameterStatusesByUserId(
        const Request::FDescribeBalanceParameterStatusesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBalanceParameterStatusesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterStatusTask>> FGs2EnchantRestClient::GetBalanceParameterStatus(
        const Request::FGetBalanceParameterStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBalanceParameterStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBalanceParameterStatusByUserIdTask>> FGs2EnchantRestClient::GetBalanceParameterStatusByUserId(
        const Request::FGetBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteBalanceParameterStatusByUserIdTask>> FGs2EnchantRestClient::DeleteBalanceParameterStatusByUserId(
        const Request::FDeleteBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReDrawBalanceParameterStatusByUserIdTask>> FGs2EnchantRestClient::ReDrawBalanceParameterStatusByUserId(
        const Request::FReDrawBalanceParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReDrawBalanceParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReDrawBalanceParameterStatusByStampSheetTask>> FGs2EnchantRestClient::ReDrawBalanceParameterStatusByStampSheet(
        const Request::FReDrawBalanceParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReDrawBalanceParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterStatusesTask>> FGs2EnchantRestClient::DescribeRarityParameterStatuses(
        const Request::FDescribeRarityParameterStatusesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRarityParameterStatusesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRarityParameterStatusesByUserIdTask>> FGs2EnchantRestClient::DescribeRarityParameterStatusesByUserId(
        const Request::FDescribeRarityParameterStatusesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRarityParameterStatusesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterStatusTask>> FGs2EnchantRestClient::GetRarityParameterStatus(
        const Request::FGetRarityParameterStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRarityParameterStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRarityParameterStatusByUserIdTask>> FGs2EnchantRestClient::GetRarityParameterStatusByUserId(
        const Request::FGetRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRarityParameterStatusByUserIdTask>> FGs2EnchantRestClient::DeleteRarityParameterStatusByUserId(
        const Request::FDeleteRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReDrawRarityParameterStatusByUserIdTask>> FGs2EnchantRestClient::ReDrawRarityParameterStatusByUserId(
        const Request::FReDrawRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReDrawRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FReDrawRarityParameterStatusByStampSheetTask>> FGs2EnchantRestClient::ReDrawRarityParameterStatusByStampSheet(
        const Request::FReDrawRarityParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FReDrawRarityParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddRarityParameterStatusByUserIdTask>> FGs2EnchantRestClient::AddRarityParameterStatusByUserId(
        const Request::FAddRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddRarityParameterStatusByStampSheetTask>> FGs2EnchantRestClient::AddRarityParameterStatusByStampSheet(
        const Request::FAddRarityParameterStatusByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddRarityParameterStatusByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusTask>> FGs2EnchantRestClient::VerifyRarityParameterStatus(
        const Request::FVerifyRarityParameterStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusByUserIdTask>> FGs2EnchantRestClient::VerifyRarityParameterStatusByUserId(
        const Request::FVerifyRarityParameterStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusByStampTaskTask>> FGs2EnchantRestClient::VerifyRarityParameterStatusByStampTask(
        const Request::FVerifyRarityParameterStatusByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyRarityParameterStatusByStampTaskTask>>(
            Session,
            Request
        );
    }
}