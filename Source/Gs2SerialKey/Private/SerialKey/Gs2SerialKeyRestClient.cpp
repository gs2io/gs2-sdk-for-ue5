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

#include "SerialKey/Gs2SerialKeyRestClient.h"

namespace Gs2::SerialKey
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2SerialKeyRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2SerialKeyRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2SerialKeyRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2SerialKeyRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2SerialKeyRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2SerialKeyRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> FGs2SerialKeyRestClient::GetServiceVersion(
        const Request::FGetServiceVersionRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetServiceVersionTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> FGs2SerialKeyRestClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> FGs2SerialKeyRestClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> FGs2SerialKeyRestClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> FGs2SerialKeyRestClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> FGs2SerialKeyRestClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> FGs2SerialKeyRestClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> FGs2SerialKeyRestClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeIssueJobsTask>> FGs2SerialKeyRestClient::DescribeIssueJobs(
        const Request::FDescribeIssueJobsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeIssueJobsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetIssueJobTask>> FGs2SerialKeyRestClient::GetIssueJob(
        const Request::FGetIssueJobRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetIssueJobTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIssueTask>> FGs2SerialKeyRestClient::Issue(
        const Request::FIssueRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIssueTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSerialKeysTask>> FGs2SerialKeyRestClient::DescribeSerialKeys(
        const Request::FDescribeSerialKeysRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSerialKeysTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDownloadSerialCodesTask>> FGs2SerialKeyRestClient::DownloadSerialCodes(
        const Request::FDownloadSerialCodesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDownloadSerialCodesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIssueOnceTask>> FGs2SerialKeyRestClient::IssueOnce(
        const Request::FIssueOnceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIssueOnceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSerialKeyTask>> FGs2SerialKeyRestClient::GetSerialKey(
        const Request::FGetSerialKeyRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSerialKeyTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyCodeTask>> FGs2SerialKeyRestClient::VerifyCode(
        const Request::FVerifyCodeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyCodeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyCodeByUserIdTask>> FGs2SerialKeyRestClient::VerifyCodeByUserId(
        const Request::FVerifyCodeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyCodeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUseTask>> FGs2SerialKeyRestClient::Use(
        const Request::FUseRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUseTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUseByUserIdTask>> FGs2SerialKeyRestClient::UseByUserId(
        const Request::FUseByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUseByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRevertUseByUserIdTask>> FGs2SerialKeyRestClient::RevertUseByUserId(
        const Request::FRevertUseByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRevertUseByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUseByStampTaskTask>> FGs2SerialKeyRestClient::UseByStampTask(
        const Request::FUseByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUseByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRevertUseByStampSheetTask>> FGs2SerialKeyRestClient::RevertUseByStampSheet(
        const Request::FRevertUseByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRevertUseByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FVerifyByStampTaskTask>> FGs2SerialKeyRestClient::VerifyByStampTask(
        const Request::FVerifyByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FVerifyByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIssueOnceByStampSheetTask>> FGs2SerialKeyRestClient::IssueOnceByStampSheet(
        const Request::FIssueOnceByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIssueOnceByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeCampaignModelsTask>> FGs2SerialKeyRestClient::DescribeCampaignModels(
        const Request::FDescribeCampaignModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeCampaignModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCampaignModelTask>> FGs2SerialKeyRestClient::GetCampaignModel(
        const Request::FGetCampaignModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCampaignModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeCampaignModelMastersTask>> FGs2SerialKeyRestClient::DescribeCampaignModelMasters(
        const Request::FDescribeCampaignModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeCampaignModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateCampaignModelMasterTask>> FGs2SerialKeyRestClient::CreateCampaignModelMaster(
        const Request::FCreateCampaignModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateCampaignModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCampaignModelMasterTask>> FGs2SerialKeyRestClient::GetCampaignModelMaster(
        const Request::FGetCampaignModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCampaignModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCampaignModelMasterTask>> FGs2SerialKeyRestClient::UpdateCampaignModelMaster(
        const Request::FUpdateCampaignModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCampaignModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteCampaignModelMasterTask>> FGs2SerialKeyRestClient::DeleteCampaignModelMaster(
        const Request::FDeleteCampaignModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteCampaignModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2SerialKeyRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentCampaignMasterTask>> FGs2SerialKeyRestClient::GetCurrentCampaignMaster(
        const Request::FGetCurrentCampaignMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentCampaignMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentCampaignMasterTask>> FGs2SerialKeyRestClient::PreUpdateCurrentCampaignMaster(
        const Request::FPreUpdateCurrentCampaignMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPreUpdateCurrentCampaignMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentCampaignMasterTask>> FGs2SerialKeyRestClient::UpdateCurrentCampaignMaster(
        const Request::FUpdateCurrentCampaignMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentCampaignMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentCampaignMasterFromGitHubTask>> FGs2SerialKeyRestClient::UpdateCurrentCampaignMasterFromGitHub(
        const Request::FUpdateCurrentCampaignMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentCampaignMasterFromGitHubTask>>(
            Session,
            Request
        );
    }
}