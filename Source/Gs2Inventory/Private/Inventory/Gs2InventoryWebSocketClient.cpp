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

#include "Inventory/Gs2InventoryWebSocketClient.h"

namespace Gs2::Inventory
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2InventoryWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2InventoryWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2InventoryWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2InventoryWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2InventoryWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2InventoryWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> FGs2InventoryWebSocketClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2InventoryWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2InventoryWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2InventoryWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2InventoryWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2InventoryWebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2InventoryWebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2InventoryWebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoryModelMastersTask>> FGs2InventoryWebSocketClient::DescribeInventoryModelMasters(
        const Request::FDescribeInventoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeInventoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateInventoryModelMasterTask>> FGs2InventoryWebSocketClient::CreateInventoryModelMaster(
        const Request::FCreateInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryModelMasterTask>> FGs2InventoryWebSocketClient::GetInventoryModelMaster(
        const Request::FGetInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateInventoryModelMasterTask>> FGs2InventoryWebSocketClient::UpdateInventoryModelMaster(
        const Request::FUpdateInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteInventoryModelMasterTask>> FGs2InventoryWebSocketClient::DeleteInventoryModelMaster(
        const Request::FDeleteInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoryModelsTask>> FGs2InventoryWebSocketClient::DescribeInventoryModels(
        const Request::FDescribeInventoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeInventoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryModelTask>> FGs2InventoryWebSocketClient::GetInventoryModel(
        const Request::FGetInventoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetInventoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemModelMastersTask>> FGs2InventoryWebSocketClient::DescribeItemModelMasters(
        const Request::FDescribeItemModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeItemModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateItemModelMasterTask>> FGs2InventoryWebSocketClient::CreateItemModelMaster(
        const Request::FCreateItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemModelMasterTask>> FGs2InventoryWebSocketClient::GetItemModelMaster(
        const Request::FGetItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateItemModelMasterTask>> FGs2InventoryWebSocketClient::UpdateItemModelMaster(
        const Request::FUpdateItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteItemModelMasterTask>> FGs2InventoryWebSocketClient::DeleteItemModelMaster(
        const Request::FDeleteItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemModelsTask>> FGs2InventoryWebSocketClient::DescribeItemModels(
        const Request::FDescribeItemModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeItemModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemModelTask>> FGs2InventoryWebSocketClient::GetItemModel(
        const Request::FGetItemModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetItemModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleInventoryModelMastersTask>> FGs2InventoryWebSocketClient::DescribeSimpleInventoryModelMasters(
        const Request::FDescribeSimpleInventoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSimpleInventoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSimpleInventoryModelMasterTask>> FGs2InventoryWebSocketClient::CreateSimpleInventoryModelMaster(
        const Request::FCreateSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleInventoryModelMasterTask>> FGs2InventoryWebSocketClient::GetSimpleInventoryModelMaster(
        const Request::FGetSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSimpleInventoryModelMasterTask>> FGs2InventoryWebSocketClient::UpdateSimpleInventoryModelMaster(
        const Request::FUpdateSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleInventoryModelMasterTask>> FGs2InventoryWebSocketClient::DeleteSimpleInventoryModelMaster(
        const Request::FDeleteSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleInventoryModelsTask>> FGs2InventoryWebSocketClient::DescribeSimpleInventoryModels(
        const Request::FDescribeSimpleInventoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSimpleInventoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleInventoryModelTask>> FGs2InventoryWebSocketClient::GetSimpleInventoryModel(
        const Request::FGetSimpleInventoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleInventoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemModelMastersTask>> FGs2InventoryWebSocketClient::DescribeSimpleItemModelMasters(
        const Request::FDescribeSimpleItemModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSimpleItemModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateSimpleItemModelMasterTask>> FGs2InventoryWebSocketClient::CreateSimpleItemModelMaster(
        const Request::FCreateSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemModelMasterTask>> FGs2InventoryWebSocketClient::GetSimpleItemModelMaster(
        const Request::FGetSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateSimpleItemModelMasterTask>> FGs2InventoryWebSocketClient::UpdateSimpleItemModelMaster(
        const Request::FUpdateSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleItemModelMasterTask>> FGs2InventoryWebSocketClient::DeleteSimpleItemModelMaster(
        const Request::FDeleteSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemModelsTask>> FGs2InventoryWebSocketClient::DescribeSimpleItemModels(
        const Request::FDescribeSimpleItemModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSimpleItemModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemModelTask>> FGs2InventoryWebSocketClient::GetSimpleItemModel(
        const Request::FGetSimpleItemModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleItemModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigInventoryModelMastersTask>> FGs2InventoryWebSocketClient::DescribeBigInventoryModelMasters(
        const Request::FDescribeBigInventoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBigInventoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBigInventoryModelMasterTask>> FGs2InventoryWebSocketClient::CreateBigInventoryModelMaster(
        const Request::FCreateBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigInventoryModelMasterTask>> FGs2InventoryWebSocketClient::GetBigInventoryModelMaster(
        const Request::FGetBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBigInventoryModelMasterTask>> FGs2InventoryWebSocketClient::UpdateBigInventoryModelMaster(
        const Request::FUpdateBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBigInventoryModelMasterTask>> FGs2InventoryWebSocketClient::DeleteBigInventoryModelMaster(
        const Request::FDeleteBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigInventoryModelsTask>> FGs2InventoryWebSocketClient::DescribeBigInventoryModels(
        const Request::FDescribeBigInventoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBigInventoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigInventoryModelTask>> FGs2InventoryWebSocketClient::GetBigInventoryModel(
        const Request::FGetBigInventoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBigInventoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemModelMastersTask>> FGs2InventoryWebSocketClient::DescribeBigItemModelMasters(
        const Request::FDescribeBigItemModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBigItemModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateBigItemModelMasterTask>> FGs2InventoryWebSocketClient::CreateBigItemModelMaster(
        const Request::FCreateBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemModelMasterTask>> FGs2InventoryWebSocketClient::GetBigItemModelMaster(
        const Request::FGetBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateBigItemModelMasterTask>> FGs2InventoryWebSocketClient::UpdateBigItemModelMaster(
        const Request::FUpdateBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBigItemModelMasterTask>> FGs2InventoryWebSocketClient::DeleteBigItemModelMaster(
        const Request::FDeleteBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemModelsTask>> FGs2InventoryWebSocketClient::DescribeBigItemModels(
        const Request::FDescribeBigItemModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBigItemModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemModelTask>> FGs2InventoryWebSocketClient::GetBigItemModel(
        const Request::FGetBigItemModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBigItemModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2InventoryWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentItemModelMasterTask>> FGs2InventoryWebSocketClient::GetCurrentItemModelMaster(
        const Request::FGetCurrentItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentItemModelMasterTask>> FGs2InventoryWebSocketClient::PreUpdateCurrentItemModelMaster(
        const Request::FPreUpdateCurrentItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPreUpdateCurrentItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentItemModelMasterTask>> FGs2InventoryWebSocketClient::UpdateCurrentItemModelMaster(
        const Request::FUpdateCurrentItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentItemModelMasterFromGitHubTask>> FGs2InventoryWebSocketClient::UpdateCurrentItemModelMasterFromGitHub(
        const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentItemModelMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoriesTask>> FGs2InventoryWebSocketClient::DescribeInventories(
        const Request::FDescribeInventoriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeInventoriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeInventoriesByUserIdTask>> FGs2InventoryWebSocketClient::DescribeInventoriesByUserId(
        const Request::FDescribeInventoriesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeInventoriesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryTask>> FGs2InventoryWebSocketClient::GetInventory(
        const Request::FGetInventoryRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetInventoryTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetInventoryByUserIdTask>> FGs2InventoryWebSocketClient::GetInventoryByUserId(
        const Request::FGetInventoryByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetInventoryByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddCapacityByUserIdTask>> FGs2InventoryWebSocketClient::AddCapacityByUserId(
        const Request::FAddCapacityByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddCapacityByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetCapacityByUserIdTask>> FGs2InventoryWebSocketClient::SetCapacityByUserId(
        const Request::FSetCapacityByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetCapacityByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteInventoryByUserIdTask>> FGs2InventoryWebSocketClient::DeleteInventoryByUserId(
        const Request::FDeleteInventoryByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteInventoryByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityTask>> FGs2InventoryWebSocketClient::VerifyInventoryCurrentMaxCapacity(
        const Request::FVerifyInventoryCurrentMaxCapacityRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityByUserIdTask>> FGs2InventoryWebSocketClient::VerifyInventoryCurrentMaxCapacityByUserId(
        const Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityByStampTaskTask>> FGs2InventoryWebSocketClient::VerifyInventoryCurrentMaxCapacityByStampTask(
        const Request::FVerifyInventoryCurrentMaxCapacityByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyInventoryCurrentMaxCapacityByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddCapacityByStampSheetTask>> FGs2InventoryWebSocketClient::AddCapacityByStampSheet(
        const Request::FAddCapacityByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddCapacityByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetCapacityByStampSheetTask>> FGs2InventoryWebSocketClient::SetCapacityByStampSheet(
        const Request::FSetCapacityByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetCapacityByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemSetsTask>> FGs2InventoryWebSocketClient::DescribeItemSets(
        const Request::FDescribeItemSetsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeItemSetsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeItemSetsByUserIdTask>> FGs2InventoryWebSocketClient::DescribeItemSetsByUserId(
        const Request::FDescribeItemSetsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeItemSetsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemSetTask>> FGs2InventoryWebSocketClient::GetItemSet(
        const Request::FGetItemSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetItemSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemSetByUserIdTask>> FGs2InventoryWebSocketClient::GetItemSetByUserId(
        const Request::FGetItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemWithSignatureTask>> FGs2InventoryWebSocketClient::GetItemWithSignature(
        const Request::FGetItemWithSignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetItemWithSignatureTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetItemWithSignatureByUserIdTask>> FGs2InventoryWebSocketClient::GetItemWithSignatureByUserId(
        const Request::FGetItemWithSignatureByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetItemWithSignatureByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetByUserIdTask>> FGs2InventoryWebSocketClient::AcquireItemSetByUserId(
        const Request::FAcquireItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetWithGradeByUserIdTask>> FGs2InventoryWebSocketClient::AcquireItemSetWithGradeByUserId(
        const Request::FAcquireItemSetWithGradeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireItemSetWithGradeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetTask>> FGs2InventoryWebSocketClient::ConsumeItemSet(
        const Request::FConsumeItemSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeItemSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetByUserIdTask>> FGs2InventoryWebSocketClient::ConsumeItemSetByUserId(
        const Request::FConsumeItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteItemSetByUserIdTask>> FGs2InventoryWebSocketClient::DeleteItemSetByUserId(
        const Request::FDeleteItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyItemSetTask>> FGs2InventoryWebSocketClient::VerifyItemSet(
        const Request::FVerifyItemSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyItemSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyItemSetByUserIdTask>> FGs2InventoryWebSocketClient::VerifyItemSetByUserId(
        const Request::FVerifyItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetByStampSheetTask>> FGs2InventoryWebSocketClient::AcquireItemSetByStampSheet(
        const Request::FAcquireItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireItemSetByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireItemSetWithGradeByStampSheetTask>> FGs2InventoryWebSocketClient::AcquireItemSetWithGradeByStampSheet(
        const Request::FAcquireItemSetWithGradeByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireItemSetWithGradeByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeItemSetByStampTaskTask>> FGs2InventoryWebSocketClient::ConsumeItemSetByStampTask(
        const Request::FConsumeItemSetByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeItemSetByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyItemSetByStampTaskTask>> FGs2InventoryWebSocketClient::VerifyItemSetByStampTask(
        const Request::FVerifyItemSetByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyItemSetByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReferenceOfTask>> FGs2InventoryWebSocketClient::DescribeReferenceOf(
        const Request::FDescribeReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReferenceOfByUserIdTask>> FGs2InventoryWebSocketClient::DescribeReferenceOfByUserId(
        const Request::FDescribeReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetReferenceOfTask>> FGs2InventoryWebSocketClient::GetReferenceOf(
        const Request::FGetReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetReferenceOfByUserIdTask>> FGs2InventoryWebSocketClient::GetReferenceOfByUserId(
        const Request::FGetReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReferenceOfTask>> FGs2InventoryWebSocketClient::VerifyReferenceOf(
        const Request::FVerifyReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReferenceOfByUserIdTask>> FGs2InventoryWebSocketClient::VerifyReferenceOfByUserId(
        const Request::FVerifyReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddReferenceOfTask>> FGs2InventoryWebSocketClient::AddReferenceOf(
        const Request::FAddReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddReferenceOfByUserIdTask>> FGs2InventoryWebSocketClient::AddReferenceOfByUserId(
        const Request::FAddReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReferenceOfTask>> FGs2InventoryWebSocketClient::DeleteReferenceOf(
        const Request::FDeleteReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReferenceOfByUserIdTask>> FGs2InventoryWebSocketClient::DeleteReferenceOfByUserId(
        const Request::FDeleteReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddReferenceOfItemSetByStampSheetTask>> FGs2InventoryWebSocketClient::AddReferenceOfItemSetByStampSheet(
        const Request::FAddReferenceOfItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddReferenceOfItemSetByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteReferenceOfItemSetByStampSheetTask>> FGs2InventoryWebSocketClient::DeleteReferenceOfItemSetByStampSheet(
        const Request::FDeleteReferenceOfItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteReferenceOfItemSetByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyReferenceOfByStampTaskTask>> FGs2InventoryWebSocketClient::VerifyReferenceOfByStampTask(
        const Request::FVerifyReferenceOfByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyReferenceOfByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemsTask>> FGs2InventoryWebSocketClient::DescribeSimpleItems(
        const Request::FDescribeSimpleItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSimpleItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSimpleItemsByUserIdTask>> FGs2InventoryWebSocketClient::DescribeSimpleItemsByUserId(
        const Request::FDescribeSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemTask>> FGs2InventoryWebSocketClient::GetSimpleItem(
        const Request::FGetSimpleItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemByUserIdTask>> FGs2InventoryWebSocketClient::GetSimpleItemByUserId(
        const Request::FGetSimpleItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemWithSignatureTask>> FGs2InventoryWebSocketClient::GetSimpleItemWithSignature(
        const Request::FGetSimpleItemWithSignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleItemWithSignatureTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSimpleItemWithSignatureByUserIdTask>> FGs2InventoryWebSocketClient::GetSimpleItemWithSignatureByUserId(
        const Request::FGetSimpleItemWithSignatureByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSimpleItemWithSignatureByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByUserIdTask>> FGs2InventoryWebSocketClient::AcquireSimpleItemsByUserId(
        const Request::FAcquireSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsTask>> FGs2InventoryWebSocketClient::ConsumeSimpleItems(
        const Request::FConsumeSimpleItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByUserIdTask>> FGs2InventoryWebSocketClient::ConsumeSimpleItemsByUserId(
        const Request::FConsumeSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetSimpleItemsByUserIdTask>> FGs2InventoryWebSocketClient::SetSimpleItemsByUserId(
        const Request::FSetSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteSimpleItemsByUserIdTask>> FGs2InventoryWebSocketClient::DeleteSimpleItemsByUserId(
        const Request::FDeleteSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySimpleItemTask>> FGs2InventoryWebSocketClient::VerifySimpleItem(
        const Request::FVerifySimpleItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifySimpleItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySimpleItemByUserIdTask>> FGs2InventoryWebSocketClient::VerifySimpleItemByUserId(
        const Request::FVerifySimpleItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifySimpleItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByStampSheetTask>> FGs2InventoryWebSocketClient::AcquireSimpleItemsByStampSheet(
        const Request::FAcquireSimpleItemsByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireSimpleItemsByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByStampTaskTask>> FGs2InventoryWebSocketClient::ConsumeSimpleItemsByStampTask(
        const Request::FConsumeSimpleItemsByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeSimpleItemsByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetSimpleItemsByStampSheetTask>> FGs2InventoryWebSocketClient::SetSimpleItemsByStampSheet(
        const Request::FSetSimpleItemsByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetSimpleItemsByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifySimpleItemByStampTaskTask>> FGs2InventoryWebSocketClient::VerifySimpleItemByStampTask(
        const Request::FVerifySimpleItemByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifySimpleItemByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemsTask>> FGs2InventoryWebSocketClient::DescribeBigItems(
        const Request::FDescribeBigItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBigItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBigItemsByUserIdTask>> FGs2InventoryWebSocketClient::DescribeBigItemsByUserId(
        const Request::FDescribeBigItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeBigItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemTask>> FGs2InventoryWebSocketClient::GetBigItem(
        const Request::FGetBigItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBigItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetBigItemByUserIdTask>> FGs2InventoryWebSocketClient::GetBigItemByUserId(
        const Request::FGetBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireBigItemByUserIdTask>> FGs2InventoryWebSocketClient::AcquireBigItemByUserId(
        const Request::FAcquireBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeBigItemTask>> FGs2InventoryWebSocketClient::ConsumeBigItem(
        const Request::FConsumeBigItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeBigItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeBigItemByUserIdTask>> FGs2InventoryWebSocketClient::ConsumeBigItemByUserId(
        const Request::FConsumeBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetBigItemByUserIdTask>> FGs2InventoryWebSocketClient::SetBigItemByUserId(
        const Request::FSetBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteBigItemByUserIdTask>> FGs2InventoryWebSocketClient::DeleteBigItemByUserId(
        const Request::FDeleteBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyBigItemTask>> FGs2InventoryWebSocketClient::VerifyBigItem(
        const Request::FVerifyBigItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyBigItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyBigItemByUserIdTask>> FGs2InventoryWebSocketClient::VerifyBigItemByUserId(
        const Request::FVerifyBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireBigItemByStampSheetTask>> FGs2InventoryWebSocketClient::AcquireBigItemByStampSheet(
        const Request::FAcquireBigItemByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcquireBigItemByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeBigItemByStampTaskTask>> FGs2InventoryWebSocketClient::ConsumeBigItemByStampTask(
        const Request::FConsumeBigItemByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeBigItemByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetBigItemByStampSheetTask>> FGs2InventoryWebSocketClient::SetBigItemByStampSheet(
        const Request::FSetBigItemByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetBigItemByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyBigItemByStampTaskTask>> FGs2InventoryWebSocketClient::VerifyBigItemByStampTask(
        const Request::FVerifyBigItemByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyBigItemByStampTaskTask>>(
            Session,
            Request
        );
    }
}