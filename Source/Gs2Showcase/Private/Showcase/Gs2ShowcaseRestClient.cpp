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

#include "Showcase/Gs2ShowcaseRestClient.h"

namespace Gs2::Showcase
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2ShowcaseRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2ShowcaseRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2ShowcaseRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2ShowcaseRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2ShowcaseRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2ShowcaseRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSalesItemMastersTask>> FGs2ShowcaseRestClient::DescribeSalesItemMasters(
        const Request::FDescribeSalesItemMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSalesItemMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateSalesItemMasterTask>> FGs2ShowcaseRestClient::CreateSalesItemMaster(
        const Request::FCreateSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSalesItemMasterTask>> FGs2ShowcaseRestClient::GetSalesItemMaster(
        const Request::FGetSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateSalesItemMasterTask>> FGs2ShowcaseRestClient::UpdateSalesItemMaster(
        const Request::FUpdateSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSalesItemMasterTask>> FGs2ShowcaseRestClient::DeleteSalesItemMaster(
        const Request::FDeleteSalesItemMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSalesItemMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSalesItemGroupMastersTask>> FGs2ShowcaseRestClient::DescribeSalesItemGroupMasters(
        const Request::FDescribeSalesItemGroupMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSalesItemGroupMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateSalesItemGroupMasterTask>> FGs2ShowcaseRestClient::CreateSalesItemGroupMaster(
        const Request::FCreateSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSalesItemGroupMasterTask>> FGs2ShowcaseRestClient::GetSalesItemGroupMaster(
        const Request::FGetSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateSalesItemGroupMasterTask>> FGs2ShowcaseRestClient::UpdateSalesItemGroupMaster(
        const Request::FUpdateSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSalesItemGroupMasterTask>> FGs2ShowcaseRestClient::DeleteSalesItemGroupMaster(
        const Request::FDeleteSalesItemGroupMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSalesItemGroupMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeShowcaseMastersTask>> FGs2ShowcaseRestClient::DescribeShowcaseMasters(
        const Request::FDescribeShowcaseMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeShowcaseMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateShowcaseMasterTask>> FGs2ShowcaseRestClient::CreateShowcaseMaster(
        const Request::FCreateShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetShowcaseMasterTask>> FGs2ShowcaseRestClient::GetShowcaseMaster(
        const Request::FGetShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateShowcaseMasterTask>> FGs2ShowcaseRestClient::UpdateShowcaseMaster(
        const Request::FUpdateShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteShowcaseMasterTask>> FGs2ShowcaseRestClient::DeleteShowcaseMaster(
        const Request::FDeleteShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2ShowcaseRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentShowcaseMasterTask>> FGs2ShowcaseRestClient::GetCurrentShowcaseMaster(
        const Request::FGetCurrentShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentShowcaseMasterTask>> FGs2ShowcaseRestClient::UpdateCurrentShowcaseMaster(
        const Request::FUpdateCurrentShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentShowcaseMasterFromGitHubTask>> FGs2ShowcaseRestClient::UpdateCurrentShowcaseMasterFromGitHub(
        const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentShowcaseMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeShowcasesTask>> FGs2ShowcaseRestClient::DescribeShowcases(
        const Request::FDescribeShowcasesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeShowcasesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeShowcasesByUserIdTask>> FGs2ShowcaseRestClient::DescribeShowcasesByUserId(
        const Request::FDescribeShowcasesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeShowcasesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetShowcaseTask>> FGs2ShowcaseRestClient::GetShowcase(
        const Request::FGetShowcaseRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetShowcaseTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetShowcaseByUserIdTask>> FGs2ShowcaseRestClient::GetShowcaseByUserId(
        const Request::FGetShowcaseByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetShowcaseByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FBuyTask>> FGs2ShowcaseRestClient::Buy(
        const Request::FBuyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FBuyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FBuyByUserIdTask>> FGs2ShowcaseRestClient::BuyByUserId(
        const Request::FBuyByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FBuyByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRandomShowcaseMastersTask>> FGs2ShowcaseRestClient::DescribeRandomShowcaseMasters(
        const Request::FDescribeRandomShowcaseMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRandomShowcaseMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateRandomShowcaseMasterTask>> FGs2ShowcaseRestClient::CreateRandomShowcaseMaster(
        const Request::FCreateRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRandomShowcaseMasterTask>> FGs2ShowcaseRestClient::GetRandomShowcaseMaster(
        const Request::FGetRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateRandomShowcaseMasterTask>> FGs2ShowcaseRestClient::UpdateRandomShowcaseMaster(
        const Request::FUpdateRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRandomShowcaseMasterTask>> FGs2ShowcaseRestClient::DeleteRandomShowcaseMaster(
        const Request::FDeleteRandomShowcaseMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRandomShowcaseMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRandomShowcaseSalesItemsTask>> FGs2ShowcaseRestClient::DescribeRandomShowcaseSalesItems(
        const Request::FDescribeRandomShowcaseSalesItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRandomShowcaseSalesItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRandomShowcaseSalesItemsByUserIdTask>> FGs2ShowcaseRestClient::DescribeRandomShowcaseSalesItemsByUserId(
        const Request::FDescribeRandomShowcaseSalesItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRandomShowcaseSalesItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRandomShowcaseSalesItemTask>> FGs2ShowcaseRestClient::GetRandomShowcaseSalesItem(
        const Request::FGetRandomShowcaseSalesItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRandomShowcaseSalesItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRandomShowcaseSalesItemByUserIdTask>> FGs2ShowcaseRestClient::GetRandomShowcaseSalesItemByUserId(
        const Request::FGetRandomShowcaseSalesItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRandomShowcaseSalesItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIncrementPurchaseCountByUserIdTask>> FGs2ShowcaseRestClient::IncrementPurchaseCountByUserId(
        const Request::FIncrementPurchaseCountByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIncrementPurchaseCountByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIncrementPurchaseCountByStampTaskTask>> FGs2ShowcaseRestClient::IncrementPurchaseCountByStampTask(
        const Request::FIncrementPurchaseCountByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIncrementPurchaseCountByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FForceReDrawByUserIdTask>> FGs2ShowcaseRestClient::ForceReDrawByUserId(
        const Request::FForceReDrawByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FForceReDrawByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FForceReDrawByUserIdByStampSheetTask>> FGs2ShowcaseRestClient::ForceReDrawByUserIdByStampSheet(
        const Request::FForceReDrawByUserIdByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FForceReDrawByUserIdByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRandomShowcaseBuyTask>> FGs2ShowcaseRestClient::RandomShowcaseBuy(
        const Request::FRandomShowcaseBuyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRandomShowcaseBuyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRandomShowcaseBuyByUserIdTask>> FGs2ShowcaseRestClient::RandomShowcaseBuyByUserId(
        const Request::FRandomShowcaseBuyByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRandomShowcaseBuyByUserIdTask>>(
            Session,
            Request
        );
    }
}