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
#include "Request/DescribeSalesItemMastersRequest.h"
#include "Task/WebSocket/DescribeSalesItemMastersTask.h"
#include "Request/CreateSalesItemMasterRequest.h"
#include "Task/WebSocket/CreateSalesItemMasterTask.h"
#include "Request/GetSalesItemMasterRequest.h"
#include "Task/WebSocket/GetSalesItemMasterTask.h"
#include "Request/UpdateSalesItemMasterRequest.h"
#include "Task/WebSocket/UpdateSalesItemMasterTask.h"
#include "Request/DeleteSalesItemMasterRequest.h"
#include "Task/WebSocket/DeleteSalesItemMasterTask.h"
#include "Request/DescribeSalesItemGroupMastersRequest.h"
#include "Task/WebSocket/DescribeSalesItemGroupMastersTask.h"
#include "Request/CreateSalesItemGroupMasterRequest.h"
#include "Task/WebSocket/CreateSalesItemGroupMasterTask.h"
#include "Request/GetSalesItemGroupMasterRequest.h"
#include "Task/WebSocket/GetSalesItemGroupMasterTask.h"
#include "Request/UpdateSalesItemGroupMasterRequest.h"
#include "Task/WebSocket/UpdateSalesItemGroupMasterTask.h"
#include "Request/DeleteSalesItemGroupMasterRequest.h"
#include "Task/WebSocket/DeleteSalesItemGroupMasterTask.h"
#include "Request/DescribeShowcaseMastersRequest.h"
#include "Task/WebSocket/DescribeShowcaseMastersTask.h"
#include "Request/CreateShowcaseMasterRequest.h"
#include "Task/WebSocket/CreateShowcaseMasterTask.h"
#include "Request/GetShowcaseMasterRequest.h"
#include "Task/WebSocket/GetShowcaseMasterTask.h"
#include "Request/UpdateShowcaseMasterRequest.h"
#include "Task/WebSocket/UpdateShowcaseMasterTask.h"
#include "Request/DeleteShowcaseMasterRequest.h"
#include "Task/WebSocket/DeleteShowcaseMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentShowcaseMasterRequest.h"
#include "Task/WebSocket/GetCurrentShowcaseMasterTask.h"
#include "Request/UpdateCurrentShowcaseMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentShowcaseMasterTask.h"
#include "Request/UpdateCurrentShowcaseMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentShowcaseMasterFromGitHubTask.h"
#include "Request/DescribeShowcasesRequest.h"
#include "Task/WebSocket/DescribeShowcasesTask.h"
#include "Request/DescribeShowcasesByUserIdRequest.h"
#include "Task/WebSocket/DescribeShowcasesByUserIdTask.h"
#include "Request/GetShowcaseRequest.h"
#include "Task/WebSocket/GetShowcaseTask.h"
#include "Request/GetShowcaseByUserIdRequest.h"
#include "Task/WebSocket/GetShowcaseByUserIdTask.h"
#include "Request/BuyRequest.h"
#include "Task/WebSocket/BuyTask.h"
#include "Request/BuyByUserIdRequest.h"
#include "Task/WebSocket/BuyByUserIdTask.h"
#include "Request/DescribeRandomShowcaseMastersRequest.h"
#include "Task/WebSocket/DescribeRandomShowcaseMastersTask.h"
#include "Request/CreateRandomShowcaseMasterRequest.h"
#include "Task/WebSocket/CreateRandomShowcaseMasterTask.h"
#include "Request/GetRandomShowcaseMasterRequest.h"
#include "Task/WebSocket/GetRandomShowcaseMasterTask.h"
#include "Request/UpdateRandomShowcaseMasterRequest.h"
#include "Task/WebSocket/UpdateRandomShowcaseMasterTask.h"
#include "Request/DeleteRandomShowcaseMasterRequest.h"
#include "Task/WebSocket/DeleteRandomShowcaseMasterTask.h"
#include "Request/DescribeRandomShowcaseSalesItemsRequest.h"
#include "Task/WebSocket/DescribeRandomShowcaseSalesItemsTask.h"
#include "Request/DescribeRandomShowcaseSalesItemsByUserIdRequest.h"
#include "Task/WebSocket/DescribeRandomShowcaseSalesItemsByUserIdTask.h"
#include "Request/GetRandomShowcaseSalesItemRequest.h"
#include "Task/WebSocket/GetRandomShowcaseSalesItemTask.h"
#include "Request/GetRandomShowcaseSalesItemByUserIdRequest.h"
#include "Task/WebSocket/GetRandomShowcaseSalesItemByUserIdTask.h"
#include "Request/IncrementPurchaseCountByUserIdRequest.h"
#include "Task/WebSocket/IncrementPurchaseCountByUserIdTask.h"
#include "Request/IncrementPurchaseCountByStampTaskRequest.h"
#include "Task/WebSocket/IncrementPurchaseCountByStampTaskTask.h"
#include "Request/ForceReDrawByUserIdRequest.h"
#include "Task/WebSocket/ForceReDrawByUserIdTask.h"
#include "Request/ForceReDrawByUserIdByStampSheetRequest.h"
#include "Task/WebSocket/ForceReDrawByUserIdByStampSheetTask.h"
#include "Request/RandomShowcaseBuyRequest.h"
#include "Task/WebSocket/RandomShowcaseBuyTask.h"
#include "Request/RandomShowcaseBuyByUserIdRequest.h"
#include "Task/WebSocket/RandomShowcaseBuyByUserIdTask.h"

namespace Gs2::Showcase
{
    class GS2SHOWCASE_API FGs2ShowcaseWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2ShowcaseWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSalesItemMastersTask>> DescribeSalesItemMasters(
            const Request::FDescribeSalesItemMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSalesItemMasterTask>> CreateSalesItemMaster(
            const Request::FCreateSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSalesItemMasterTask>> GetSalesItemMaster(
            const Request::FGetSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSalesItemMasterTask>> UpdateSalesItemMaster(
            const Request::FUpdateSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSalesItemMasterTask>> DeleteSalesItemMaster(
            const Request::FDeleteSalesItemMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSalesItemGroupMastersTask>> DescribeSalesItemGroupMasters(
            const Request::FDescribeSalesItemGroupMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSalesItemGroupMasterTask>> CreateSalesItemGroupMaster(
            const Request::FCreateSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSalesItemGroupMasterTask>> GetSalesItemGroupMaster(
            const Request::FGetSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSalesItemGroupMasterTask>> UpdateSalesItemGroupMaster(
            const Request::FUpdateSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSalesItemGroupMasterTask>> DeleteSalesItemGroupMaster(
            const Request::FDeleteSalesItemGroupMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeShowcaseMastersTask>> DescribeShowcaseMasters(
            const Request::FDescribeShowcaseMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateShowcaseMasterTask>> CreateShowcaseMaster(
            const Request::FCreateShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetShowcaseMasterTask>> GetShowcaseMaster(
            const Request::FGetShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateShowcaseMasterTask>> UpdateShowcaseMaster(
            const Request::FUpdateShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteShowcaseMasterTask>> DeleteShowcaseMaster(
            const Request::FDeleteShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentShowcaseMasterTask>> GetCurrentShowcaseMaster(
            const Request::FGetCurrentShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentShowcaseMasterTask>> UpdateCurrentShowcaseMaster(
            const Request::FUpdateCurrentShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentShowcaseMasterFromGitHubTask>> UpdateCurrentShowcaseMasterFromGitHub(
            const Request::FUpdateCurrentShowcaseMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeShowcasesTask>> DescribeShowcases(
            const Request::FDescribeShowcasesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeShowcasesByUserIdTask>> DescribeShowcasesByUserId(
            const Request::FDescribeShowcasesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetShowcaseTask>> GetShowcase(
            const Request::FGetShowcaseRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetShowcaseByUserIdTask>> GetShowcaseByUserId(
            const Request::FGetShowcaseByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FBuyTask>> Buy(
            const Request::FBuyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FBuyByUserIdTask>> BuyByUserId(
            const Request::FBuyByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRandomShowcaseMastersTask>> DescribeRandomShowcaseMasters(
            const Request::FDescribeRandomShowcaseMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRandomShowcaseMasterTask>> CreateRandomShowcaseMaster(
            const Request::FCreateRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRandomShowcaseMasterTask>> GetRandomShowcaseMaster(
            const Request::FGetRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRandomShowcaseMasterTask>> UpdateRandomShowcaseMaster(
            const Request::FUpdateRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRandomShowcaseMasterTask>> DeleteRandomShowcaseMaster(
            const Request::FDeleteRandomShowcaseMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRandomShowcaseSalesItemsTask>> DescribeRandomShowcaseSalesItems(
            const Request::FDescribeRandomShowcaseSalesItemsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRandomShowcaseSalesItemsByUserIdTask>> DescribeRandomShowcaseSalesItemsByUserId(
            const Request::FDescribeRandomShowcaseSalesItemsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRandomShowcaseSalesItemTask>> GetRandomShowcaseSalesItem(
            const Request::FGetRandomShowcaseSalesItemRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetRandomShowcaseSalesItemByUserIdTask>> GetRandomShowcaseSalesItemByUserId(
            const Request::FGetRandomShowcaseSalesItemByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountByUserIdTask>> IncrementPurchaseCountByUserId(
            const Request::FIncrementPurchaseCountByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncrementPurchaseCountByStampTaskTask>> IncrementPurchaseCountByStampTask(
            const Request::FIncrementPurchaseCountByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FForceReDrawByUserIdTask>> ForceReDrawByUserId(
            const Request::FForceReDrawByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FForceReDrawByUserIdByStampSheetTask>> ForceReDrawByUserIdByStampSheet(
            const Request::FForceReDrawByUserIdByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRandomShowcaseBuyTask>> RandomShowcaseBuy(
            const Request::FRandomShowcaseBuyRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRandomShowcaseBuyByUserIdTask>> RandomShowcaseBuyByUserId(
            const Request::FRandomShowcaseBuyByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ShowcaseWebSocketClient, ESPMode::ThreadSafe> FGs2ShowcaseWebSocketClientPtr;
}