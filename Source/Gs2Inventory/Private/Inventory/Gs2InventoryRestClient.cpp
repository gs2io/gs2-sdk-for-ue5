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

    TSharedPtr<FAsyncTask<Task::Rest::FAcquireItemSetByStampSheetTask>> FGs2InventoryRestClient::AcquireItemSetByStampSheet(
        const Request::FAcquireItemSetByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcquireItemSetByStampSheetTask>>(
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

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteSimpleItemsByUserIdTask>> FGs2InventoryRestClient::DeleteSimpleItemsByUserId(
        const Request::FDeleteSimpleItemsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteSimpleItemsByUserIdTask>>(
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
}