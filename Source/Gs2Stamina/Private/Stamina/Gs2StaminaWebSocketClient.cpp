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

#include "Stamina/Gs2StaminaWebSocketClient.h"

namespace Gs2::Stamina
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2StaminaWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2StaminaWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2StaminaWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2StaminaWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2StaminaWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2StaminaWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> FGs2StaminaWebSocketClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2StaminaWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2StaminaWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2StaminaWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2StaminaWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2StaminaWebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2StaminaWebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2StaminaWebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminaModelMastersTask>> FGs2StaminaWebSocketClient::DescribeStaminaModelMasters(
        const Request::FDescribeStaminaModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeStaminaModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateStaminaModelMasterTask>> FGs2StaminaWebSocketClient::CreateStaminaModelMaster(
        const Request::FCreateStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaModelMasterTask>> FGs2StaminaWebSocketClient::GetStaminaModelMaster(
        const Request::FGetStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStaminaModelMasterTask>> FGs2StaminaWebSocketClient::UpdateStaminaModelMaster(
        const Request::FUpdateStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStaminaModelMasterTask>> FGs2StaminaWebSocketClient::DeleteStaminaModelMaster(
        const Request::FDeleteStaminaModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteStaminaModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMaxStaminaTableMastersTask>> FGs2StaminaWebSocketClient::DescribeMaxStaminaTableMasters(
        const Request::FDescribeMaxStaminaTableMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMaxStaminaTableMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMaxStaminaTableMasterTask>> FGs2StaminaWebSocketClient::CreateMaxStaminaTableMaster(
        const Request::FCreateMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetMaxStaminaTableMasterTask>> FGs2StaminaWebSocketClient::GetMaxStaminaTableMaster(
        const Request::FGetMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMaxStaminaTableMasterTask>> FGs2StaminaWebSocketClient::UpdateMaxStaminaTableMaster(
        const Request::FUpdateMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMaxStaminaTableMasterTask>> FGs2StaminaWebSocketClient::DeleteMaxStaminaTableMaster(
        const Request::FDeleteMaxStaminaTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteMaxStaminaTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRecoverIntervalTableMastersTask>> FGs2StaminaWebSocketClient::DescribeRecoverIntervalTableMasters(
        const Request::FDescribeRecoverIntervalTableMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRecoverIntervalTableMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRecoverIntervalTableMasterTask>> FGs2StaminaWebSocketClient::CreateRecoverIntervalTableMaster(
        const Request::FCreateRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRecoverIntervalTableMasterTask>> FGs2StaminaWebSocketClient::GetRecoverIntervalTableMaster(
        const Request::FGetRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRecoverIntervalTableMasterTask>> FGs2StaminaWebSocketClient::UpdateRecoverIntervalTableMaster(
        const Request::FUpdateRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRecoverIntervalTableMasterTask>> FGs2StaminaWebSocketClient::DeleteRecoverIntervalTableMaster(
        const Request::FDeleteRecoverIntervalTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRecoverIntervalTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeRecoverValueTableMastersTask>> FGs2StaminaWebSocketClient::DescribeRecoverValueTableMasters(
        const Request::FDescribeRecoverValueTableMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeRecoverValueTableMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateRecoverValueTableMasterTask>> FGs2StaminaWebSocketClient::CreateRecoverValueTableMaster(
        const Request::FCreateRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetRecoverValueTableMasterTask>> FGs2StaminaWebSocketClient::GetRecoverValueTableMaster(
        const Request::FGetRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateRecoverValueTableMasterTask>> FGs2StaminaWebSocketClient::UpdateRecoverValueTableMaster(
        const Request::FUpdateRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRecoverValueTableMasterTask>> FGs2StaminaWebSocketClient::DeleteRecoverValueTableMaster(
        const Request::FDeleteRecoverValueTableMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRecoverValueTableMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2StaminaWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentStaminaMasterTask>> FGs2StaminaWebSocketClient::GetCurrentStaminaMaster(
        const Request::FGetCurrentStaminaMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentStaminaMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPreUpdateCurrentStaminaMasterTask>> FGs2StaminaWebSocketClient::PreUpdateCurrentStaminaMaster(
        const Request::FPreUpdateCurrentStaminaMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPreUpdateCurrentStaminaMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentStaminaMasterTask>> FGs2StaminaWebSocketClient::UpdateCurrentStaminaMaster(
        const Request::FUpdateCurrentStaminaMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentStaminaMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentStaminaMasterFromGitHubTask>> FGs2StaminaWebSocketClient::UpdateCurrentStaminaMasterFromGitHub(
        const Request::FUpdateCurrentStaminaMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentStaminaMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminaModelsTask>> FGs2StaminaWebSocketClient::DescribeStaminaModels(
        const Request::FDescribeStaminaModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeStaminaModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaModelTask>> FGs2StaminaWebSocketClient::GetStaminaModel(
        const Request::FGetStaminaModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStaminaModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminasTask>> FGs2StaminaWebSocketClient::DescribeStaminas(
        const Request::FDescribeStaminasRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeStaminasTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeStaminasByUserIdTask>> FGs2StaminaWebSocketClient::DescribeStaminasByUserId(
        const Request::FDescribeStaminasByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeStaminasByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaTask>> FGs2StaminaWebSocketClient::GetStamina(
        const Request::FGetStaminaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStaminaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetStaminaByUserIdTask>> FGs2StaminaWebSocketClient::GetStaminaByUserId(
        const Request::FGetStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateStaminaByUserIdTask>> FGs2StaminaWebSocketClient::UpdateStaminaByUserId(
        const Request::FUpdateStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeStaminaTask>> FGs2StaminaWebSocketClient::ConsumeStamina(
        const Request::FConsumeStaminaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeStaminaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeStaminaByUserIdTask>> FGs2StaminaWebSocketClient::ConsumeStaminaByUserId(
        const Request::FConsumeStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FApplyStaminaTask>> FGs2StaminaWebSocketClient::ApplyStamina(
        const Request::FApplyStaminaRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FApplyStaminaTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FApplyStaminaByUserIdTask>> FGs2StaminaWebSocketClient::ApplyStaminaByUserId(
        const Request::FApplyStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FApplyStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRecoverStaminaByUserIdTask>> FGs2StaminaWebSocketClient::RecoverStaminaByUserId(
        const Request::FRecoverStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRecoverStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRaiseMaxValueByUserIdTask>> FGs2StaminaWebSocketClient::RaiseMaxValueByUserId(
        const Request::FRaiseMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRaiseMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaxValueTask>> FGs2StaminaWebSocketClient::DecreaseMaxValue(
        const Request::FDecreaseMaxValueRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecreaseMaxValueTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaxValueByUserIdTask>> FGs2StaminaWebSocketClient::DecreaseMaxValueByUserId(
        const Request::FDecreaseMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecreaseMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaxValueByUserIdTask>> FGs2StaminaWebSocketClient::SetMaxValueByUserId(
        const Request::FSetMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByUserIdTask>> FGs2StaminaWebSocketClient::SetRecoverIntervalByUserId(
        const Request::FSetRecoverIntervalByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverValueByUserIdTask>> FGs2StaminaWebSocketClient::SetRecoverValueByUserId(
        const Request::FSetRecoverValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRecoverValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaxValueByStatusTask>> FGs2StaminaWebSocketClient::SetMaxValueByStatus(
        const Request::FSetMaxValueByStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetMaxValueByStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByStatusTask>> FGs2StaminaWebSocketClient::SetRecoverIntervalByStatus(
        const Request::FSetRecoverIntervalByStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverValueByStatusTask>> FGs2StaminaWebSocketClient::SetRecoverValueByStatus(
        const Request::FSetRecoverValueByStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRecoverValueByStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteStaminaByUserIdTask>> FGs2StaminaWebSocketClient::DeleteStaminaByUserId(
        const Request::FDeleteStaminaByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteStaminaByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaValueTask>> FGs2StaminaWebSocketClient::VerifyStaminaValue(
        const Request::FVerifyStaminaValueRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaValueTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaValueByUserIdTask>> FGs2StaminaWebSocketClient::VerifyStaminaValueByUserId(
        const Request::FVerifyStaminaValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaMaxValueTask>> FGs2StaminaWebSocketClient::VerifyStaminaMaxValue(
        const Request::FVerifyStaminaMaxValueRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaMaxValueTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaMaxValueByUserIdTask>> FGs2StaminaWebSocketClient::VerifyStaminaMaxValueByUserId(
        const Request::FVerifyStaminaMaxValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaMaxValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverIntervalMinutesTask>> FGs2StaminaWebSocketClient::VerifyStaminaRecoverIntervalMinutes(
        const Request::FVerifyStaminaRecoverIntervalMinutesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverIntervalMinutesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverIntervalMinutesByUserIdTask>> FGs2StaminaWebSocketClient::VerifyStaminaRecoverIntervalMinutesByUserId(
        const Request::FVerifyStaminaRecoverIntervalMinutesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverIntervalMinutesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverValueTask>> FGs2StaminaWebSocketClient::VerifyStaminaRecoverValue(
        const Request::FVerifyStaminaRecoverValueRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverValueTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverValueByUserIdTask>> FGs2StaminaWebSocketClient::VerifyStaminaRecoverValueByUserId(
        const Request::FVerifyStaminaRecoverValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaOverflowValueTask>> FGs2StaminaWebSocketClient::VerifyStaminaOverflowValue(
        const Request::FVerifyStaminaOverflowValueRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaOverflowValueTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaOverflowValueByUserIdTask>> FGs2StaminaWebSocketClient::VerifyStaminaOverflowValueByUserId(
        const Request::FVerifyStaminaOverflowValueByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaOverflowValueByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRecoverStaminaByStampSheetTask>> FGs2StaminaWebSocketClient::RecoverStaminaByStampSheet(
        const Request::FRecoverStaminaByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRecoverStaminaByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRaiseMaxValueByStampSheetTask>> FGs2StaminaWebSocketClient::RaiseMaxValueByStampSheet(
        const Request::FRaiseMaxValueByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRaiseMaxValueByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaxValueByStampTaskTask>> FGs2StaminaWebSocketClient::DecreaseMaxValueByStampTask(
        const Request::FDecreaseMaxValueByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecreaseMaxValueByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaxValueByStampSheetTask>> FGs2StaminaWebSocketClient::SetMaxValueByStampSheet(
        const Request::FSetMaxValueByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetMaxValueByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByStampSheetTask>> FGs2StaminaWebSocketClient::SetRecoverIntervalByStampSheet(
        const Request::FSetRecoverIntervalByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRecoverIntervalByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetRecoverValueByStampSheetTask>> FGs2StaminaWebSocketClient::SetRecoverValueByStampSheet(
        const Request::FSetRecoverValueByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetRecoverValueByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FConsumeStaminaByStampTaskTask>> FGs2StaminaWebSocketClient::ConsumeStaminaByStampTask(
        const Request::FConsumeStaminaByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FConsumeStaminaByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaValueByStampTaskTask>> FGs2StaminaWebSocketClient::VerifyStaminaValueByStampTask(
        const Request::FVerifyStaminaValueByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaValueByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaMaxValueByStampTaskTask>> FGs2StaminaWebSocketClient::VerifyStaminaMaxValueByStampTask(
        const Request::FVerifyStaminaMaxValueByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaMaxValueByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverIntervalMinutesByStampTaskTask>> FGs2StaminaWebSocketClient::VerifyStaminaRecoverIntervalMinutesByStampTask(
        const Request::FVerifyStaminaRecoverIntervalMinutesByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverIntervalMinutesByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverValueByStampTaskTask>> FGs2StaminaWebSocketClient::VerifyStaminaRecoverValueByStampTask(
        const Request::FVerifyStaminaRecoverValueByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaRecoverValueByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyStaminaOverflowValueByStampTaskTask>> FGs2StaminaWebSocketClient::VerifyStaminaOverflowValueByStampTask(
        const Request::FVerifyStaminaOverflowValueByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyStaminaOverflowValueByStampTaskTask>>(
            Session,
            Request
        );
    }
}