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

#include "Experience/Gs2ExperienceRestClient.h"

namespace Gs2::Experience
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2ExperienceRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2ExperienceRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2ExperienceRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2ExperienceRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2ExperienceRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2ExperienceRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeExperienceModelMastersTask>> FGs2ExperienceRestClient::DescribeExperienceModelMasters(
        const Request::FDescribeExperienceModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeExperienceModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateExperienceModelMasterTask>> FGs2ExperienceRestClient::CreateExperienceModelMaster(
        const Request::FCreateExperienceModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateExperienceModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetExperienceModelMasterTask>> FGs2ExperienceRestClient::GetExperienceModelMaster(
        const Request::FGetExperienceModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetExperienceModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateExperienceModelMasterTask>> FGs2ExperienceRestClient::UpdateExperienceModelMaster(
        const Request::FUpdateExperienceModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateExperienceModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteExperienceModelMasterTask>> FGs2ExperienceRestClient::DeleteExperienceModelMaster(
        const Request::FDeleteExperienceModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteExperienceModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeExperienceModelsTask>> FGs2ExperienceRestClient::DescribeExperienceModels(
        const Request::FDescribeExperienceModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeExperienceModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetExperienceModelTask>> FGs2ExperienceRestClient::GetExperienceModel(
        const Request::FGetExperienceModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetExperienceModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeThresholdMastersTask>> FGs2ExperienceRestClient::DescribeThresholdMasters(
        const Request::FDescribeThresholdMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeThresholdMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateThresholdMasterTask>> FGs2ExperienceRestClient::CreateThresholdMaster(
        const Request::FCreateThresholdMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateThresholdMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetThresholdMasterTask>> FGs2ExperienceRestClient::GetThresholdMaster(
        const Request::FGetThresholdMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetThresholdMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateThresholdMasterTask>> FGs2ExperienceRestClient::UpdateThresholdMaster(
        const Request::FUpdateThresholdMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateThresholdMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteThresholdMasterTask>> FGs2ExperienceRestClient::DeleteThresholdMaster(
        const Request::FDeleteThresholdMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteThresholdMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2ExperienceRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentExperienceMasterTask>> FGs2ExperienceRestClient::GetCurrentExperienceMaster(
        const Request::FGetCurrentExperienceMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentExperienceMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentExperienceMasterTask>> FGs2ExperienceRestClient::UpdateCurrentExperienceMaster(
        const Request::FUpdateCurrentExperienceMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentExperienceMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentExperienceMasterFromGitHubTask>> FGs2ExperienceRestClient::UpdateCurrentExperienceMasterFromGitHub(
        const Request::FUpdateCurrentExperienceMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentExperienceMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStatusesTask>> FGs2ExperienceRestClient::DescribeStatuses(
        const Request::FDescribeStatusesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStatusesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeStatusesByUserIdTask>> FGs2ExperienceRestClient::DescribeStatusesByUserId(
        const Request::FDescribeStatusesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeStatusesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStatusTask>> FGs2ExperienceRestClient::GetStatus(
        const Request::FGetStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStatusByUserIdTask>> FGs2ExperienceRestClient::GetStatusByUserId(
        const Request::FGetStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStatusWithSignatureTask>> FGs2ExperienceRestClient::GetStatusWithSignature(
        const Request::FGetStatusWithSignatureRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStatusWithSignatureTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetStatusWithSignatureByUserIdTask>> FGs2ExperienceRestClient::GetStatusWithSignatureByUserId(
        const Request::FGetStatusWithSignatureByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetStatusWithSignatureByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddExperienceByUserIdTask>> FGs2ExperienceRestClient::AddExperienceByUserId(
        const Request::FAddExperienceByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddExperienceByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSubExperienceByUserIdTask>> FGs2ExperienceRestClient::SubExperienceByUserId(
        const Request::FSubExperienceByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSubExperienceByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetExperienceByUserIdTask>> FGs2ExperienceRestClient::SetExperienceByUserId(
        const Request::FSetExperienceByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetExperienceByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddRankCapByUserIdTask>> FGs2ExperienceRestClient::AddRankCapByUserId(
        const Request::FAddRankCapByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddRankCapByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSubRankCapByUserIdTask>> FGs2ExperienceRestClient::SubRankCapByUserId(
        const Request::FSubRankCapByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSubRankCapByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRankCapByUserIdTask>> FGs2ExperienceRestClient::SetRankCapByUserId(
        const Request::FSetRankCapByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRankCapByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteStatusByUserIdTask>> FGs2ExperienceRestClient::DeleteStatusByUserId(
        const Request::FDeleteStatusByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteStatusByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddExperienceByStampSheetTask>> FGs2ExperienceRestClient::AddExperienceByStampSheet(
        const Request::FAddExperienceByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddExperienceByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSubExperienceByStampTaskTask>> FGs2ExperienceRestClient::SubExperienceByStampTask(
        const Request::FSubExperienceByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSubExperienceByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAddRankCapByStampSheetTask>> FGs2ExperienceRestClient::AddRankCapByStampSheet(
        const Request::FAddRankCapByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAddRankCapByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSubRankCapByStampTaskTask>> FGs2ExperienceRestClient::SubRankCapByStampTask(
        const Request::FSubRankCapByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSubRankCapByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetRankCapByStampSheetTask>> FGs2ExperienceRestClient::SetRankCapByStampSheet(
        const Request::FSetRankCapByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetRankCapByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByUserIdTask>> FGs2ExperienceRestClient::MultiplyAcquireActionsByUserId(
        const Request::FMultiplyAcquireActionsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByStampSheetTask>> FGs2ExperienceRestClient::MultiplyAcquireActionsByStampSheet(
        const Request::FMultiplyAcquireActionsByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FMultiplyAcquireActionsByStampSheetTask>>(
            Session,
            Request
        );
    }
}