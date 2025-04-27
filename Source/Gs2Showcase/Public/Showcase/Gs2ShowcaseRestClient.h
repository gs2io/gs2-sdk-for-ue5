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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeSalesItemMastersRequest.h"
#include "Task/Rest/DescribeSalesItemMastersTask.h"
#include "Request/CreateSalesItemMasterRequest.h"
#include "Task/Rest/CreateSalesItemMasterTask.h"
#include "Request/GetSalesItemMasterRequest.h"
#include "Task/Rest/GetSalesItemMasterTask.h"
#include "Request/UpdateSalesItemMasterRequest.h"
#include "Task/Rest/UpdateSalesItemMasterTask.h"
#include "Request/DeleteSalesItemMasterRequest.h"
#include "Task/Rest/DeleteSalesItemMasterTask.h"
#include "Request/DescribeSalesItemGroupMastersRequest.h"
#include "Task/Rest/DescribeSalesItemGroupMastersTask.h"
#include "Request/CreateSalesItemGroupMasterRequest.h"
#include "Task/Rest/CreateSalesItemGroupMasterTask.h"
#include "Request/GetSalesItemGroupMasterRequest.h"
#include "Task/Rest/GetSalesItemGroupMasterTask.h"
#include "Request/UpdateSalesItemGroupMasterRequest.h"
#include "Task/Rest/UpdateSalesItemGroupMasterTask.h"
#include "Request/DeleteSalesItemGroupMasterRequest.h"
#include "Task/Rest/DeleteSalesItemGroupMasterTask.h"
#include "Request/DescribeShowcaseMastersRequest.h"
#include "Task/Rest/DescribeShowcaseMastersTask.h"
#include "Request/CreateShowcaseMasterRequest.h"
#include "Task/Rest/CreateShowcaseMasterTask.h"
#include "Request/GetShowcaseMasterRequest.h"
#include "Task/Rest/GetShowcaseMasterTask.h"
#include "Request/UpdateShowcaseMasterRequest.h"
#include "Task/Rest/UpdateShowcaseMasterTask.h"
#include "Request/DeleteShowcaseMasterRequest.h"
#include "Task/Rest/DeleteShowcaseMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentShowcaseMasterRequest.h"
#include "Task/Rest/GetCurrentShowcaseMasterTask.h"
#include "Request/PreUpdateCurrentShowcaseMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentShowcaseMasterTask.h"
#include "Request/UpdateCurrentShowcaseMasterRequest.h"
#include "Task/Rest/UpdateCurrentShowcaseMasterTask.h"
#include "Request/UpdateCurrentShowcaseMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentShowcaseMasterFromGitHubTask.h"
#include "Request/DescribeShowcasesRequest.h"
#include "Task/Rest/DescribeShowcasesTask.h"
#include "Request/DescribeShowcasesByUserIdRequest.h"
#include "Task/Rest/DescribeShowcasesByUserIdTask.h"
#include "Request/GetShowcaseRequest.h"
#include "Task/Rest/GetShowcaseTask.h"
#include "Request/GetShowcaseByUserIdRequest.h"
#include "Task/Rest/GetShowcaseByUserIdTask.h"
#include "Request/BuyRequest.h"
#include "Task/Rest/BuyTask.h"
#include "Request/BuyByUserIdRequest.h"
#include "Task/Rest/BuyByUserIdTask.h"
#include "Request/DescribeRandomShowcaseMastersRequest.h"
#include "Task/Rest/DescribeRandomShowcaseMastersTask.h"
#include "Request/CreateRandomShowcaseMasterRequest.h"
#include "Task/Rest/CreateRandomShowcaseMasterTask.h"
#include "Request/GetRandomShowcaseMasterRequest.h"
#include "Task/Rest/GetRandomShowcaseMasterTask.h"
#include "Request/UpdateRandomShowcaseMasterRequest.h"
#include "Task/Rest/UpdateRandomShowcaseMasterTask.h"
#include "Request/DeleteRandomShowcaseMasterRequest.h"
#include "Task/Rest/DeleteRandomShowcaseMasterTask.h"
#include "Request/IncrementPurchaseCountRequest.h"
#include "Task/Rest/IncrementPurchaseCountTask.h"
#include "Request/IncrementPurchaseCountByUserIdRequest.h"
#include "Task/Rest/IncrementPurchaseCountByUserIdTask.h"
#include "Request/DecrementPurchaseCountByUserIdRequest.h"
#include "Task/Rest/DecrementPurchaseCountByUserIdTask.h"
#include "Request/IncrementPurchaseCountByStampTaskRequest.h"
#include "Task/Rest/IncrementPurchaseCountByStampTaskTask.h"
#include "Request/DecrementPurchaseCountByStampSheetRequest.h"
#include "Task/Rest/DecrementPurchaseCountByStampSheetTask.h"
#include "Request/ForceReDrawByUserIdRequest.h"
#include "Task/Rest/ForceReDrawByUserIdTask.h"
#include "Request/ForceReDrawByUserIdByStampSheetRequest.h"
#include "Task/Rest/ForceReDrawByUserIdByStampSheetTask.h"
#include "Request/DescribeRandomDisplayItemsRequest.h"
#include "Task/Rest/DescribeRandomDisplayItemsTask.h"
#include "Request/DescribeRandomDisplayItemsByUserIdRequest.h"
#include "Task/Rest/DescribeRandomDisplayItemsByUserIdTask.h"
#include "Request/GetRandomDisplayItemRequest.h"
#include "Task/Rest/GetRandomDisplayItemTask.h"
#include "Request/GetRandomDisplayItemByUserIdRequest.h"
#include "Task/Rest/GetRandomDisplayItemByUserIdTask.h"
#include "Request/RandomShowcaseBuyRequest.h"
#include "Task/Rest/RandomShowcaseBuyTask.h"
#include "Request/RandomShowcaseBuyByUserIdRequest.h"
#include "Task/Rest/RandomShowcaseBuyByUserIdTask.h"

namespace Gs2::Showcase
{
    class GS2SHOWCASE_API FGs2ShowcaseRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ShowcaseRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSalesItemMastersTask>> DescribeSalesItemMasters(
            const Request::FDescribeSalesItemMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSalesItemMasterTask>> CreateSalesItemMaster(
            const Request::FCreateSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSalesItemMasterTask>> GetSalesItemMaster(
            const Request::FGetSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSalesItemMasterTask>> UpdateSalesItemMaster(
            const Request::FUpdateSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSalesItemMasterTask>> DeleteSalesItemMaster(
            const Request::FDeleteSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSalesItemGroupMastersTask>> DescribeSalesItemGroupMasters(
            const Request::FDescribeSalesItemGroupMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateSalesItemGroupMasterTask>> CreateSalesItemGroupMaster(
            const Request::FCreateSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSalesItemGroupMasterTask>> GetSalesItemGroupMaster(
            const Request::FGetSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateSalesItemGroupMasterTask>> UpdateSalesItemGroupMaster(
            const Request::FUpdateSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteSalesItemGroupMasterTask>> DeleteSalesItemGroupMaster(
            const Request::FDeleteSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeShowcaseMastersTask>> DescribeShowcaseMasters(
            const Request::FDescribeShowcaseMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateShowcaseMasterTask>> CreateShowcaseMaster(
            const Request::FCreateShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetShowcaseMasterTask>> GetShowcaseMaster(
            const Request::FGetShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateShowcaseMasterTask>> UpdateShowcaseMaster(
            const Request::FUpdateShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteShowcaseMasterTask>> DeleteShowcaseMaster(
            const Request::FDeleteShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentShowcaseMasterTask>> GetCurrentShowcaseMaster(
            const Request::FGetCurrentShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentShowcaseMasterTask>> PreUpdateCurrentShowcaseMaster(
            const Request::FPreUpdateCurrentShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentShowcaseMasterTask>> UpdateCurrentShowcaseMaster(
            const Request::FUpdateCurrentShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentShowcaseMasterFromGitHubTask>> UpdateCurrentShowcaseMasterFromGitHub(
            const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeShowcasesTask>> DescribeShowcases(
            const Request::FDescribeShowcasesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeShowcasesByUserIdTask>> DescribeShowcasesByUserId(
            const Request::FDescribeShowcasesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetShowcaseTask>> GetShowcase(
            const Request::FGetShowcaseRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetShowcaseByUserIdTask>> GetShowcaseByUserId(
            const Request::FGetShowcaseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBuyTask>> Buy(
            const Request::FBuyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FBuyByUserIdTask>> BuyByUserId(
            const Request::FBuyByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRandomShowcaseMastersTask>> DescribeRandomShowcaseMasters(
            const Request::FDescribeRandomShowcaseMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRandomShowcaseMasterTask>> CreateRandomShowcaseMaster(
            const Request::FCreateRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRandomShowcaseMasterTask>> GetRandomShowcaseMaster(
            const Request::FGetRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRandomShowcaseMasterTask>> UpdateRandomShowcaseMaster(
            const Request::FUpdateRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRandomShowcaseMasterTask>> DeleteRandomShowcaseMaster(
            const Request::FDeleteRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncrementPurchaseCountTask>> IncrementPurchaseCount(
            const Request::FIncrementPurchaseCountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncrementPurchaseCountByUserIdTask>> IncrementPurchaseCountByUserId(
            const Request::FIncrementPurchaseCountByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecrementPurchaseCountByUserIdTask>> DecrementPurchaseCountByUserId(
            const Request::FDecrementPurchaseCountByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncrementPurchaseCountByStampTaskTask>> IncrementPurchaseCountByStampTask(
            const Request::FIncrementPurchaseCountByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecrementPurchaseCountByStampSheetTask>> DecrementPurchaseCountByStampSheet(
            const Request::FDecrementPurchaseCountByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FForceReDrawByUserIdTask>> ForceReDrawByUserId(
            const Request::FForceReDrawByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FForceReDrawByUserIdByStampSheetTask>> ForceReDrawByUserIdByStampSheet(
            const Request::FForceReDrawByUserIdByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRandomDisplayItemsTask>> DescribeRandomDisplayItems(
            const Request::FDescribeRandomDisplayItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRandomDisplayItemsByUserIdTask>> DescribeRandomDisplayItemsByUserId(
            const Request::FDescribeRandomDisplayItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRandomDisplayItemTask>> GetRandomDisplayItem(
            const Request::FGetRandomDisplayItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRandomDisplayItemByUserIdTask>> GetRandomDisplayItemByUserId(
            const Request::FGetRandomDisplayItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRandomShowcaseBuyTask>> RandomShowcaseBuy(
            const Request::FRandomShowcaseBuyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRandomShowcaseBuyByUserIdTask>> RandomShowcaseBuyByUserId(
            const Request::FRandomShowcaseBuyByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ShowcaseRestClient, ESPMode::ThreadSafe> FGs2ShowcaseRestClientPtr;
}