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

#include "Inventory/Gs2InventoryRestClient.h"

namespace Gs2::Inventory
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2InventoryRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2InventoryRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2InventoryRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2InventoryRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2InventoryRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2InventoryRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> FGs2InventoryRestClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> FGs2InventoryRestClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> FGs2InventoryRestClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> FGs2InventoryRestClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> FGs2InventoryRestClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> FGs2InventoryRestClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> FGs2InventoryRestClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoryModelMastersTask>> FGs2InventoryRestClient::DescribeInventoryModelMasters(
        const Request::FDescribeInventoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeInventoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateInventoryModelMasterTask>> FGs2InventoryRestClient::CreateInventoryModelMaster(
        const Request::FCreateInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryModelMasterTask>> FGs2InventoryRestClient::GetInventoryModelMaster(
        const Request::FGetInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateInventoryModelMasterTask>> FGs2InventoryRestClient::UpdateInventoryModelMaster(
        const Request::FUpdateInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteInventoryModelMasterTask>> FGs2InventoryRestClient::DeleteInventoryModelMaster(
        const Request::FDeleteInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoryModelsTask>> FGs2InventoryRestClient::DescribeInventoryModels(
        const Request::FDescribeInventoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeInventoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryModelTask>> FGs2InventoryRestClient::GetInventoryModel(
        const Request::FGetInventoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetInventoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemModelMastersTask>> FGs2InventoryRestClient::DescribeItemModelMasters(
        const Request::FDescribeItemModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeItemModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateItemModelMasterTask>> FGs2InventoryRestClient::CreateItemModelMaster(
        const Request::FCreateItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetItemModelMasterTask>> FGs2InventoryRestClient::GetItemModelMaster(
        const Request::FGetItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateItemModelMasterTask>> FGs2InventoryRestClient::UpdateItemModelMaster(
        const Request::FUpdateItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteItemModelMasterTask>> FGs2InventoryRestClient::DeleteItemModelMaster(
        const Request::FDeleteItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemModelsTask>> FGs2InventoryRestClient::DescribeItemModels(
        const Request::FDescribeItemModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeItemModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetItemModelTask>> FGs2InventoryRestClient::GetItemModel(
        const Request::FGetItemModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetItemModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleInventoryModelMastersTask>> FGs2InventoryRestClient::DescribeSimpleInventoryModelMasters(
        const Request::FDescribeSimpleInventoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSimpleInventoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateSimpleInventoryModelMasterTask>> FGs2InventoryRestClient::CreateSimpleInventoryModelMaster(
        const Request::FCreateSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleInventoryModelMasterTask>> FGs2InventoryRestClient::GetSimpleInventoryModelMaster(
        const Request::FGetSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateSimpleInventoryModelMasterTask>> FGs2InventoryRestClient::UpdateSimpleInventoryModelMaster(
        const Request::FUpdateSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleInventoryModelMasterTask>> FGs2InventoryRestClient::DeleteSimpleInventoryModelMaster(
        const Request::FDeleteSimpleInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSimpleInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleInventoryModelsTask>> FGs2InventoryRestClient::DescribeSimpleInventoryModels(
        const Request::FDescribeSimpleInventoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSimpleInventoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleInventoryModelTask>> FGs2InventoryRestClient::GetSimpleInventoryModel(
        const Request::FGetSimpleInventoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleInventoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemModelMastersTask>> FGs2InventoryRestClient::DescribeSimpleItemModelMasters(
        const Request::FDescribeSimpleItemModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSimpleItemModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateSimpleItemModelMasterTask>> FGs2InventoryRestClient::CreateSimpleItemModelMaster(
        const Request::FCreateSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemModelMasterTask>> FGs2InventoryRestClient::GetSimpleItemModelMaster(
        const Request::FGetSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateSimpleItemModelMasterTask>> FGs2InventoryRestClient::UpdateSimpleItemModelMaster(
        const Request::FUpdateSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleItemModelMasterTask>> FGs2InventoryRestClient::DeleteSimpleItemModelMaster(
        const Request::FDeleteSimpleItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSimpleItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemModelsTask>> FGs2InventoryRestClient::DescribeSimpleItemModels(
        const Request::FDescribeSimpleItemModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSimpleItemModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemModelTask>> FGs2InventoryRestClient::GetSimpleItemModel(
        const Request::FGetSimpleItemModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleItemModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBigInventoryModelMastersTask>> FGs2InventoryRestClient::DescribeBigInventoryModelMasters(
        const Request::FDescribeBigInventoryModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBigInventoryModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateBigInventoryModelMasterTask>> FGs2InventoryRestClient::CreateBigInventoryModelMaster(
        const Request::FCreateBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBigInventoryModelMasterTask>> FGs2InventoryRestClient::GetBigInventoryModelMaster(
        const Request::FGetBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateBigInventoryModelMasterTask>> FGs2InventoryRestClient::UpdateBigInventoryModelMaster(
        const Request::FUpdateBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteBigInventoryModelMasterTask>> FGs2InventoryRestClient::DeleteBigInventoryModelMaster(
        const Request::FDeleteBigInventoryModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteBigInventoryModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBigInventoryModelsTask>> FGs2InventoryRestClient::DescribeBigInventoryModels(
        const Request::FDescribeBigInventoryModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBigInventoryModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBigInventoryModelTask>> FGs2InventoryRestClient::GetBigInventoryModel(
        const Request::FGetBigInventoryModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBigInventoryModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBigItemModelMastersTask>> FGs2InventoryRestClient::DescribeBigItemModelMasters(
        const Request::FDescribeBigItemModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBigItemModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateBigItemModelMasterTask>> FGs2InventoryRestClient::CreateBigItemModelMaster(
        const Request::FCreateBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBigItemModelMasterTask>> FGs2InventoryRestClient::GetBigItemModelMaster(
        const Request::FGetBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateBigItemModelMasterTask>> FGs2InventoryRestClient::UpdateBigItemModelMaster(
        const Request::FUpdateBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteBigItemModelMasterTask>> FGs2InventoryRestClient::DeleteBigItemModelMaster(
        const Request::FDeleteBigItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteBigItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBigItemModelsTask>> FGs2InventoryRestClient::DescribeBigItemModels(
        const Request::FDescribeBigItemModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBigItemModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBigItemModelTask>> FGs2InventoryRestClient::GetBigItemModel(
        const Request::FGetBigItemModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBigItemModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2InventoryRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentItemModelMasterTask>> FGs2InventoryRestClient::GetCurrentItemModelMaster(
        const Request::FGetCurrentItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentItemModelMasterTask>> FGs2InventoryRestClient::UpdateCurrentItemModelMaster(
        const Request::FUpdateCurrentItemModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentItemModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentItemModelMasterFromGitHubTask>> FGs2InventoryRestClient::UpdateCurrentItemModelMasterFromGitHub(
        const Request::FUpdateCurrentItemModelMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentItemModelMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoriesTask>> FGs2InventoryRestClient::DescribeInventories(
        const Request::FDescribeInventoriesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeInventoriesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeInventoriesByUserIdTask>> FGs2InventoryRestClient::DescribeInventoriesByUserId(
        const Request::FDescribeInventoriesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeInventoriesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryTask>> FGs2InventoryRestClient::GetInventory(
        const Request::FGetInventoryRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetInventoryTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetInventoryByUserIdTask>> FGs2InventoryRestClient::GetInventoryByUserId(
        const Request::FGetInventoryByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetInventoryByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddCapacityByUserIdTask>> FGs2InventoryRestClient::AddCapacityByUserId(
        const Request::FAddCapacityByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddCapacityByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetCapacityByUserIdTask>> FGs2InventoryRestClient::SetCapacityByUserId(
        const Request::FSetCapacityByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetCapacityByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteInventoryByUserIdTask>> FGs2InventoryRestClient::DeleteInventoryByUserId(
        const Request::FDeleteInventoryByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteInventoryByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyInventoryCurrentMaxCapacityTask>> FGs2InventoryRestClient::VerifyInventoryCurrentMaxCapacity(
        const Request::FVerifyInventoryCurrentMaxCapacityRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyInventoryCurrentMaxCapacityTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyInventoryCurrentMaxCapacityByUserIdTask>> FGs2InventoryRestClient::VerifyInventoryCurrentMaxCapacityByUserId(
        const Request::FVerifyInventoryCurrentMaxCapacityByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyInventoryCurrentMaxCapacityByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyInventoryCurrentMaxCapacityByStampTaskTask>> FGs2InventoryRestClient::VerifyInventoryCurrentMaxCapacityByStampTask(
        const Request::FVerifyInventoryCurrentMaxCapacityByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyInventoryCurrentMaxCapacityByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddCapacityByStampSheetTask>> FGs2InventoryRestClient::AddCapacityByStampSheet(
        const Request::FAddCapacityByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddCapacityByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetCapacityByStampSheetTask>> FGs2InventoryRestClient::SetCapacityByStampSheet(
        const Request::FSetCapacityByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetCapacityByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemSetsTask>> FGs2InventoryRestClient::DescribeItemSets(
        const Request::FDescribeItemSetsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeItemSetsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeItemSetsByUserIdTask>> FGs2InventoryRestClient::DescribeItemSetsByUserId(
        const Request::FDescribeItemSetsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeItemSetsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetItemSetTask>> FGs2InventoryRestClient::GetItemSet(
        const Request::FGetItemSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetItemSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetItemSetByUserIdTask>> FGs2InventoryRestClient::GetItemSetByUserId(
        const Request::FGetItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetItemWithSignatureTask>> FGs2InventoryRestClient::GetItemWithSignature(
        const Request::FGetItemWithSignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetItemWithSignatureTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetItemWithSignatureByUserIdTask>> FGs2InventoryRestClient::GetItemWithSignatureByUserId(
        const Request::FGetItemWithSignatureByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetItemWithSignatureByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetByUserIdTask>> FGs2InventoryRestClient::AcquireItemSetByUserId(
        const Request::FAcquireItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetWithGradeByUserIdTask>> FGs2InventoryRestClient::AcquireItemSetWithGradeByUserId(
        const Request::FAcquireItemSetWithGradeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireItemSetWithGradeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeItemSetTask>> FGs2InventoryRestClient::ConsumeItemSet(
        const Request::FConsumeItemSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeItemSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeItemSetByUserIdTask>> FGs2InventoryRestClient::ConsumeItemSetByUserId(
        const Request::FConsumeItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteItemSetByUserIdTask>> FGs2InventoryRestClient::DeleteItemSetByUserId(
        const Request::FDeleteItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyItemSetTask>> FGs2InventoryRestClient::VerifyItemSet(
        const Request::FVerifyItemSetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyItemSetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyItemSetByUserIdTask>> FGs2InventoryRestClient::VerifyItemSetByUserId(
        const Request::FVerifyItemSetByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyItemSetByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetByStampSheetTask>> FGs2InventoryRestClient::AcquireItemSetByStampSheet(
        const Request::FAcquireItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireItemSetByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetWithGradeByStampSheetTask>> FGs2InventoryRestClient::AcquireItemSetWithGradeByStampSheet(
        const Request::FAcquireItemSetWithGradeByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireItemSetWithGradeByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeItemSetByStampTaskTask>> FGs2InventoryRestClient::ConsumeItemSetByStampTask(
        const Request::FConsumeItemSetByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeItemSetByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyItemSetByStampTaskTask>> FGs2InventoryRestClient::VerifyItemSetByStampTask(
        const Request::FVerifyItemSetByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyItemSetByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeReferenceOfTask>> FGs2InventoryRestClient::DescribeReferenceOf(
        const Request::FDescribeReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeReferenceOfByUserIdTask>> FGs2InventoryRestClient::DescribeReferenceOfByUserId(
        const Request::FDescribeReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetReferenceOfTask>> FGs2InventoryRestClient::GetReferenceOf(
        const Request::FGetReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetReferenceOfByUserIdTask>> FGs2InventoryRestClient::GetReferenceOfByUserId(
        const Request::FGetReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyReferenceOfTask>> FGs2InventoryRestClient::VerifyReferenceOf(
        const Request::FVerifyReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyReferenceOfByUserIdTask>> FGs2InventoryRestClient::VerifyReferenceOfByUserId(
        const Request::FVerifyReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddReferenceOfTask>> FGs2InventoryRestClient::AddReferenceOf(
        const Request::FAddReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddReferenceOfByUserIdTask>> FGs2InventoryRestClient::AddReferenceOfByUserId(
        const Request::FAddReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteReferenceOfTask>> FGs2InventoryRestClient::DeleteReferenceOf(
        const Request::FDeleteReferenceOfRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteReferenceOfTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteReferenceOfByUserIdTask>> FGs2InventoryRestClient::DeleteReferenceOfByUserId(
        const Request::FDeleteReferenceOfByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteReferenceOfByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddReferenceOfItemSetByStampSheetTask>> FGs2InventoryRestClient::AddReferenceOfItemSetByStampSheet(
        const Request::FAddReferenceOfItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddReferenceOfItemSetByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteReferenceOfItemSetByStampSheetTask>> FGs2InventoryRestClient::DeleteReferenceOfItemSetByStampSheet(
        const Request::FDeleteReferenceOfItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteReferenceOfItemSetByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyReferenceOfByStampTaskTask>> FGs2InventoryRestClient::VerifyReferenceOfByStampTask(
        const Request::FVerifyReferenceOfByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyReferenceOfByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemsTask>> FGs2InventoryRestClient::DescribeSimpleItems(
        const Request::FDescribeSimpleItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSimpleItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSimpleItemsByUserIdTask>> FGs2InventoryRestClient::DescribeSimpleItemsByUserId(
        const Request::FDescribeSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemTask>> FGs2InventoryRestClient::GetSimpleItem(
        const Request::FGetSimpleItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemByUserIdTask>> FGs2InventoryRestClient::GetSimpleItemByUserId(
        const Request::FGetSimpleItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemWithSignatureTask>> FGs2InventoryRestClient::GetSimpleItemWithSignature(
        const Request::FGetSimpleItemWithSignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleItemWithSignatureTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSimpleItemWithSignatureByUserIdTask>> FGs2InventoryRestClient::GetSimpleItemWithSignatureByUserId(
        const Request::FGetSimpleItemWithSignatureByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSimpleItemWithSignatureByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireSimpleItemsByUserIdTask>> FGs2InventoryRestClient::AcquireSimpleItemsByUserId(
        const Request::FAcquireSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeSimpleItemsTask>> FGs2InventoryRestClient::ConsumeSimpleItems(
        const Request::FConsumeSimpleItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeSimpleItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeSimpleItemsByUserIdTask>> FGs2InventoryRestClient::ConsumeSimpleItemsByUserId(
        const Request::FConsumeSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetSimpleItemsByUserIdTask>> FGs2InventoryRestClient::SetSimpleItemsByUserId(
        const Request::FSetSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleItemsByUserIdTask>> FGs2InventoryRestClient::DeleteSimpleItemsByUserId(
        const Request::FDeleteSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSimpleItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifySimpleItemTask>> FGs2InventoryRestClient::VerifySimpleItem(
        const Request::FVerifySimpleItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifySimpleItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifySimpleItemByUserIdTask>> FGs2InventoryRestClient::VerifySimpleItemByUserId(
        const Request::FVerifySimpleItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifySimpleItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireSimpleItemsByStampSheetTask>> FGs2InventoryRestClient::AcquireSimpleItemsByStampSheet(
        const Request::FAcquireSimpleItemsByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireSimpleItemsByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeSimpleItemsByStampTaskTask>> FGs2InventoryRestClient::ConsumeSimpleItemsByStampTask(
        const Request::FConsumeSimpleItemsByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeSimpleItemsByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetSimpleItemsByStampSheetTask>> FGs2InventoryRestClient::SetSimpleItemsByStampSheet(
        const Request::FSetSimpleItemsByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetSimpleItemsByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifySimpleItemByStampTaskTask>> FGs2InventoryRestClient::VerifySimpleItemByStampTask(
        const Request::FVerifySimpleItemByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifySimpleItemByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBigItemsTask>> FGs2InventoryRestClient::DescribeBigItems(
        const Request::FDescribeBigItemsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBigItemsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeBigItemsByUserIdTask>> FGs2InventoryRestClient::DescribeBigItemsByUserId(
        const Request::FDescribeBigItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeBigItemsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBigItemTask>> FGs2InventoryRestClient::GetBigItem(
        const Request::FGetBigItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBigItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetBigItemByUserIdTask>> FGs2InventoryRestClient::GetBigItemByUserId(
        const Request::FGetBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireBigItemByUserIdTask>> FGs2InventoryRestClient::AcquireBigItemByUserId(
        const Request::FAcquireBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeBigItemTask>> FGs2InventoryRestClient::ConsumeBigItem(
        const Request::FConsumeBigItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeBigItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeBigItemByUserIdTask>> FGs2InventoryRestClient::ConsumeBigItemByUserId(
        const Request::FConsumeBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetBigItemByUserIdTask>> FGs2InventoryRestClient::SetBigItemByUserId(
        const Request::FSetBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteBigItemByUserIdTask>> FGs2InventoryRestClient::DeleteBigItemByUserId(
        const Request::FDeleteBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyBigItemTask>> FGs2InventoryRestClient::VerifyBigItem(
        const Request::FVerifyBigItemRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyBigItemTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyBigItemByUserIdTask>> FGs2InventoryRestClient::VerifyBigItemByUserId(
        const Request::FVerifyBigItemByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyBigItemByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireBigItemByStampSheetTask>> FGs2InventoryRestClient::AcquireBigItemByStampSheet(
        const Request::FAcquireBigItemByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireBigItemByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeBigItemByStampTaskTask>> FGs2InventoryRestClient::ConsumeBigItemByStampTask(
        const Request::FConsumeBigItemByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeBigItemByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetBigItemByStampSheetTask>> FGs2InventoryRestClient::SetBigItemByStampSheet(
        const Request::FSetBigItemByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetBigItemByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyBigItemByStampTaskTask>> FGs2InventoryRestClient::VerifyBigItemByStampTask(
        const Request::FVerifyBigItemByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyBigItemByStampTaskTask>>(
            Session,
            Request
        );
    }
}