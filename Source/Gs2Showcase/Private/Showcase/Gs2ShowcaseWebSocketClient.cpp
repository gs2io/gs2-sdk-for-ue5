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

#include "Showcase/Gs2ShowcaseWebSocketClient.h"

namespace Gs2::Showcase
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2ShowcaseWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2ShowcaseWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2ShowcaseWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2ShowcaseWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2ShowcaseWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2ShowcaseWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2ShowcaseWebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSalesItemMastersTask>> FGs2ShowcaseWebSocketClient::DescribeSalesItemMasters(
        const Request::FDescribeSalesItemMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSalesItemMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSalesItemMasterTask>> FGs2ShowcaseWebSocketClient::CreateSalesItemMaster(
        const Request::FCreateSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSalesItemMasterTask>> FGs2ShowcaseWebSocketClient::GetSalesItemMaster(
        const Request::FGetSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSalesItemMasterTask>> FGs2ShowcaseWebSocketClient::UpdateSalesItemMaster(
        const Request::FUpdateSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSalesItemMasterTask>> FGs2ShowcaseWebSocketClient::DeleteSalesItemMaster(
        const Request::FDeleteSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSalesItemGroupMastersTask>> FGs2ShowcaseWebSocketClient::DescribeSalesItemGroupMasters(
        const Request::FDescribeSalesItemGroupMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSalesItemGroupMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSalesItemGroupMasterTask>> FGs2ShowcaseWebSocketClient::CreateSalesItemGroupMaster(
        const Request::FCreateSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSalesItemGroupMasterTask>> FGs2ShowcaseWebSocketClient::GetSalesItemGroupMaster(
        const Request::FGetSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSalesItemGroupMasterTask>> FGs2ShowcaseWebSocketClient::UpdateSalesItemGroupMaster(
        const Request::FUpdateSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSalesItemGroupMasterTask>> FGs2ShowcaseWebSocketClient::DeleteSalesItemGroupMaster(
        const Request::FDeleteSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeShowcaseMastersTask>> FGs2ShowcaseWebSocketClient::DescribeShowcaseMasters(
        const Request::FDescribeShowcaseMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeShowcaseMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::CreateShowcaseMaster(
        const Request::FCreateShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::GetShowcaseMaster(
        const Request::FGetShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::UpdateShowcaseMaster(
        const Request::FUpdateShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::DeleteShowcaseMaster(
        const Request::FDeleteShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2ShowcaseWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::GetCurrentShowcaseMaster(
        const Request::FGetCurrentShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::UpdateCurrentShowcaseMaster(
        const Request::FUpdateCurrentShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentShowcaseMasterFromGitHubTask>> FGs2ShowcaseWebSocketClient::UpdateCurrentShowcaseMasterFromGitHub(
        const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentShowcaseMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeShowcasesTask>> FGs2ShowcaseWebSocketClient::DescribeShowcases(
        const Request::FDescribeShowcasesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeShowcasesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeShowcasesByUserIdTask>> FGs2ShowcaseWebSocketClient::DescribeShowcasesByUserId(
        const Request::FDescribeShowcasesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeShowcasesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetShowcaseTask>> FGs2ShowcaseWebSocketClient::GetShowcase(
        const Request::FGetShowcaseRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetShowcaseTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetShowcaseByUserIdTask>> FGs2ShowcaseWebSocketClient::GetShowcaseByUserId(
        const Request::FGetShowcaseByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetShowcaseByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FBuyTask>> FGs2ShowcaseWebSocketClient::Buy(
        const Request::FBuyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FBuyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FBuyByUserIdTask>> FGs2ShowcaseWebSocketClient::BuyByUserId(
        const Request::FBuyByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FBuyByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRandomShowcaseMastersTask>> FGs2ShowcaseWebSocketClient::DescribeRandomShowcaseMasters(
        const Request::FDescribeRandomShowcaseMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRandomShowcaseMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRandomShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::CreateRandomShowcaseMaster(
        const Request::FCreateRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRandomShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::GetRandomShowcaseMaster(
        const Request::FGetRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRandomShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::UpdateRandomShowcaseMaster(
        const Request::FUpdateRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRandomShowcaseMasterTask>> FGs2ShowcaseWebSocketClient::DeleteRandomShowcaseMaster(
        const Request::FDeleteRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountTask>> FGs2ShowcaseWebSocketClient::IncrementPurchaseCount(
        const Request::FIncrementPurchaseCountRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountByUserIdTask>> FGs2ShowcaseWebSocketClient::IncrementPurchaseCountByUserId(
        const Request::FIncrementPurchaseCountByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecrementPurchaseCountByUserIdTask>> FGs2ShowcaseWebSocketClient::DecrementPurchaseCountByUserId(
        const Request::FDecrementPurchaseCountByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecrementPurchaseCountByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountByStampTaskTask>> FGs2ShowcaseWebSocketClient::IncrementPurchaseCountByStampTask(
        const Request::FIncrementPurchaseCountByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecrementPurchaseCountByStampSheetTask>> FGs2ShowcaseWebSocketClient::DecrementPurchaseCountByStampSheet(
        const Request::FDecrementPurchaseCountByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecrementPurchaseCountByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FForceReDrawByUserIdTask>> FGs2ShowcaseWebSocketClient::ForceReDrawByUserId(
        const Request::FForceReDrawByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FForceReDrawByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FForceReDrawByUserIdByStampSheetTask>> FGs2ShowcaseWebSocketClient::ForceReDrawByUserIdByStampSheet(
        const Request::FForceReDrawByUserIdByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FForceReDrawByUserIdByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRandomDisplayItemsTask>> FGs2ShowcaseWebSocketClient::DescribeRandomDisplayItems(
        const Request::FDescribeRandomDisplayItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRandomDisplayItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRandomDisplayItemsByUserIdTask>> FGs2ShowcaseWebSocketClient::DescribeRandomDisplayItemsByUserId(
        const Request::FDescribeRandomDisplayItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRandomDisplayItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRandomDisplayItemTask>> FGs2ShowcaseWebSocketClient::GetRandomDisplayItem(
        const Request::FGetRandomDisplayItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRandomDisplayItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRandomDisplayItemByUserIdTask>> FGs2ShowcaseWebSocketClient::GetRandomDisplayItemByUserId(
        const Request::FGetRandomDisplayItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRandomDisplayItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRandomShowcaseBuyTask>> FGs2ShowcaseWebSocketClient::RandomShowcaseBuy(
        const Request::FRandomShowcaseBuyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRandomShowcaseBuyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRandomShowcaseBuyByUserIdTask>> FGs2ShowcaseWebSocketClient::RandomShowcaseBuyByUserId(
        const Request::FRandomShowcaseBuyByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRandomShowcaseBuyByUserIdTask>>(
            Session,
            Request
        );
    }
}