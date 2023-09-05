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

#include "Stamina/Gs2StaminaRestClient.h"

namespace Gs2::Stamina
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2StaminaRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2StaminaRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2StaminaRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2StaminaRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2StaminaRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2StaminaRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminaModelMastersTask>> FGs2StaminaRestClient::DescribeStaminaModelMasters(
        const Request::FDescribeStaminaModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStaminaModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateStaminaModelMasterTask>> FGs2StaminaRestClient::CreateStaminaModelMaster(
        const Request::FCreateStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaModelMasterTask>> FGs2StaminaRestClient::GetStaminaModelMaster(
        const Request::FGetStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateStaminaModelMasterTask>> FGs2StaminaRestClient::UpdateStaminaModelMaster(
        const Request::FUpdateStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteStaminaModelMasterTask>> FGs2StaminaRestClient::DeleteStaminaModelMaster(
        const Request::FDeleteStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeMaxStaminaTableMastersTask>> FGs2StaminaRestClient::DescribeMaxStaminaTableMasters(
        const Request::FDescribeMaxStaminaTableMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeMaxStaminaTableMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateMaxStaminaTableMasterTask>> FGs2StaminaRestClient::CreateMaxStaminaTableMaster(
        const Request::FCreateMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetMaxStaminaTableMasterTask>> FGs2StaminaRestClient::GetMaxStaminaTableMaster(
        const Request::FGetMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateMaxStaminaTableMasterTask>> FGs2StaminaRestClient::UpdateMaxStaminaTableMaster(
        const Request::FUpdateMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteMaxStaminaTableMasterTask>> FGs2StaminaRestClient::DeleteMaxStaminaTableMaster(
        const Request::FDeleteMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRecoverIntervalTableMastersTask>> FGs2StaminaRestClient::DescribeRecoverIntervalTableMasters(
        const Request::FDescribeRecoverIntervalTableMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRecoverIntervalTableMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateRecoverIntervalTableMasterTask>> FGs2StaminaRestClient::CreateRecoverIntervalTableMaster(
        const Request::FCreateRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRecoverIntervalTableMasterTask>> FGs2StaminaRestClient::GetRecoverIntervalTableMaster(
        const Request::FGetRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateRecoverIntervalTableMasterTask>> FGs2StaminaRestClient::UpdateRecoverIntervalTableMaster(
        const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRecoverIntervalTableMasterTask>> FGs2StaminaRestClient::DeleteRecoverIntervalTableMaster(
        const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRecoverValueTableMastersTask>> FGs2StaminaRestClient::DescribeRecoverValueTableMasters(
        const Request::FDescribeRecoverValueTableMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRecoverValueTableMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateRecoverValueTableMasterTask>> FGs2StaminaRestClient::CreateRecoverValueTableMaster(
        const Request::FCreateRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRecoverValueTableMasterTask>> FGs2StaminaRestClient::GetRecoverValueTableMaster(
        const Request::FGetRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateRecoverValueTableMasterTask>> FGs2StaminaRestClient::UpdateRecoverValueTableMaster(
        const Request::FUpdateRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRecoverValueTableMasterTask>> FGs2StaminaRestClient::DeleteRecoverValueTableMaster(
        const Request::FDeleteRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2StaminaRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentStaminaMasterTask>> FGs2StaminaRestClient::GetCurrentStaminaMaster(
        const Request::FGetCurrentStaminaMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentStaminaMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentStaminaMasterTask>> FGs2StaminaRestClient::UpdateCurrentStaminaMaster(
        const Request::FUpdateCurrentStaminaMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentStaminaMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentStaminaMasterFromGitHubTask>> FGs2StaminaRestClient::UpdateCurrentStaminaMasterFromGitHub(
        const Request::FUpdateCurrentStaminaMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentStaminaMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminaModelsTask>> FGs2StaminaRestClient::DescribeStaminaModels(
        const Request::FDescribeStaminaModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStaminaModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaModelTask>> FGs2StaminaRestClient::GetStaminaModel(
        const Request::FGetStaminaModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStaminaModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminasTask>> FGs2StaminaRestClient::DescribeStaminas(
        const Request::FDescribeStaminasRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStaminasTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStaminasByUserIdTask>> FGs2StaminaRestClient::DescribeStaminasByUserId(
        const Request::FDescribeStaminasByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStaminasByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaTask>> FGs2StaminaRestClient::GetStamina(
        const Request::FGetStaminaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStaminaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStaminaByUserIdTask>> FGs2StaminaRestClient::GetStaminaByUserId(
        const Request::FGetStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateStaminaByUserIdTask>> FGs2StaminaRestClient::UpdateStaminaByUserId(
        const Request::FUpdateStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeStaminaTask>> FGs2StaminaRestClient::ConsumeStamina(
        const Request::FConsumeStaminaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeStaminaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeStaminaByUserIdTask>> FGs2StaminaRestClient::ConsumeStaminaByUserId(
        const Request::FConsumeStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRecoverStaminaByUserIdTask>> FGs2StaminaRestClient::RecoverStaminaByUserId(
        const Request::FRecoverStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRecoverStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRaiseMaxValueByUserIdTask>> FGs2StaminaRestClient::RaiseMaxValueByUserId(
        const Request::FRaiseMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRaiseMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaxValueByUserIdTask>> FGs2StaminaRestClient::DecreaseMaxValueByUserId(
        const Request::FDecreaseMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDecreaseMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetMaxValueByUserIdTask>> FGs2StaminaRestClient::SetMaxValueByUserId(
        const Request::FSetMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverIntervalByUserIdTask>> FGs2StaminaRestClient::SetRecoverIntervalByUserId(
        const Request::FSetRecoverIntervalByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRecoverIntervalByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverValueByUserIdTask>> FGs2StaminaRestClient::SetRecoverValueByUserId(
        const Request::FSetRecoverValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRecoverValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetMaxValueByStatusTask>> FGs2StaminaRestClient::SetMaxValueByStatus(
        const Request::FSetMaxValueByStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetMaxValueByStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverIntervalByStatusTask>> FGs2StaminaRestClient::SetRecoverIntervalByStatus(
        const Request::FSetRecoverIntervalByStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRecoverIntervalByStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverValueByStatusTask>> FGs2StaminaRestClient::SetRecoverValueByStatus(
        const Request::FSetRecoverValueByStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRecoverValueByStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteStaminaByUserIdTask>> FGs2StaminaRestClient::DeleteStaminaByUserId(
        const Request::FDeleteStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRecoverStaminaByStampSheetTask>> FGs2StaminaRestClient::RecoverStaminaByStampSheet(
        const Request::FRecoverStaminaByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRecoverStaminaByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRaiseMaxValueByStampSheetTask>> FGs2StaminaRestClient::RaiseMaxValueByStampSheet(
        const Request::FRaiseMaxValueByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRaiseMaxValueByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaxValueByStampTaskTask>> FGs2StaminaRestClient::DecreaseMaxValueByStampTask(
        const Request::FDecreaseMaxValueByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDecreaseMaxValueByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetMaxValueByStampSheetTask>> FGs2StaminaRestClient::SetMaxValueByStampSheet(
        const Request::FSetMaxValueByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetMaxValueByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverIntervalByStampSheetTask>> FGs2StaminaRestClient::SetRecoverIntervalByStampSheet(
        const Request::FSetRecoverIntervalByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRecoverIntervalByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRecoverValueByStampSheetTask>> FGs2StaminaRestClient::SetRecoverValueByStampSheet(
        const Request::FSetRecoverValueByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRecoverValueByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FConsumeStaminaByStampTaskTask>> FGs2StaminaRestClient::ConsumeStaminaByStampTask(
        const Request::FConsumeStaminaByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FConsumeStaminaByStampTaskTask>>(
            Session,
            Request
        );
    }
}