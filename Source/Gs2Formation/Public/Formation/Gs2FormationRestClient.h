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
#include "Request/GetFormModelRequest.h"
#include "Task/Rest/GetFormModelTask.h"
#include "Request/DescribeFormModelMastersRequest.h"
#include "Task/Rest/DescribeFormModelMastersTask.h"
#include "Request/CreateFormModelMasterRequest.h"
#include "Task/Rest/CreateFormModelMasterTask.h"
#include "Request/GetFormModelMasterRequest.h"
#include "Task/Rest/GetFormModelMasterTask.h"
#include "Request/UpdateFormModelMasterRequest.h"
#include "Task/Rest/UpdateFormModelMasterTask.h"
#include "Request/DeleteFormModelMasterRequest.h"
#include "Task/Rest/DeleteFormModelMasterTask.h"
#include "Request/DescribeMoldModelsRequest.h"
#include "Task/Rest/DescribeMoldModelsTask.h"
#include "Request/GetMoldModelRequest.h"
#include "Task/Rest/GetMoldModelTask.h"
#include "Request/DescribeMoldModelMastersRequest.h"
#include "Task/Rest/DescribeMoldModelMastersTask.h"
#include "Request/CreateMoldModelMasterRequest.h"
#include "Task/Rest/CreateMoldModelMasterTask.h"
#include "Request/GetMoldModelMasterRequest.h"
#include "Task/Rest/GetMoldModelMasterTask.h"
#include "Request/UpdateMoldModelMasterRequest.h"
#include "Task/Rest/UpdateMoldModelMasterTask.h"
#include "Request/DeleteMoldModelMasterRequest.h"
#include "Task/Rest/DeleteMoldModelMasterTask.h"
#include "Request/DescribePropertyFormModelsRequest.h"
#include "Task/Rest/DescribePropertyFormModelsTask.h"
#include "Request/GetPropertyFormModelRequest.h"
#include "Task/Rest/GetPropertyFormModelTask.h"
#include "Request/DescribePropertyFormModelMastersRequest.h"
#include "Task/Rest/DescribePropertyFormModelMastersTask.h"
#include "Request/CreatePropertyFormModelMasterRequest.h"
#include "Task/Rest/CreatePropertyFormModelMasterTask.h"
#include "Request/GetPropertyFormModelMasterRequest.h"
#include "Task/Rest/GetPropertyFormModelMasterTask.h"
#include "Request/UpdatePropertyFormModelMasterRequest.h"
#include "Task/Rest/UpdatePropertyFormModelMasterTask.h"
#include "Request/DeletePropertyFormModelMasterRequest.h"
#include "Task/Rest/DeletePropertyFormModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentFormMasterRequest.h"
#include "Task/Rest/GetCurrentFormMasterTask.h"
#include "Request/UpdateCurrentFormMasterRequest.h"
#include "Task/Rest/UpdateCurrentFormMasterTask.h"
#include "Request/UpdateCurrentFormMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentFormMasterFromGitHubTask.h"
#include "Request/DescribeMoldsRequest.h"
#include "Task/Rest/DescribeMoldsTask.h"
#include "Request/DescribeMoldsByUserIdRequest.h"
#include "Task/Rest/DescribeMoldsByUserIdTask.h"
#include "Request/GetMoldRequest.h"
#include "Task/Rest/GetMoldTask.h"
#include "Request/GetMoldByUserIdRequest.h"
#include "Task/Rest/GetMoldByUserIdTask.h"
#include "Request/SetMoldCapacityByUserIdRequest.h"
#include "Task/Rest/SetMoldCapacityByUserIdTask.h"
#include "Request/AddMoldCapacityByUserIdRequest.h"
#include "Task/Rest/AddMoldCapacityByUserIdTask.h"
#include "Request/SubMoldCapacityByUserIdRequest.h"
#include "Task/Rest/SubMoldCapacityByUserIdTask.h"
#include "Request/DeleteMoldRequest.h"
#include "Task/Rest/DeleteMoldTask.h"
#include "Request/DeleteMoldByUserIdRequest.h"
#include "Task/Rest/DeleteMoldByUserIdTask.h"
#include "Request/AddCapacityByStampSheetRequest.h"
#include "Task/Rest/AddCapacityByStampSheetTask.h"
#include "Request/SubCapacityByStampTaskRequest.h"
#include "Task/Rest/SubCapacityByStampTaskTask.h"
#include "Request/SetCapacityByStampSheetRequest.h"
#include "Task/Rest/SetCapacityByStampSheetTask.h"
#include "Request/DescribeFormsRequest.h"
#include "Task/Rest/DescribeFormsTask.h"
#include "Request/DescribeFormsByUserIdRequest.h"
#include "Task/Rest/DescribeFormsByUserIdTask.h"
#include "Request/GetFormRequest.h"
#include "Task/Rest/GetFormTask.h"
#include "Request/GetFormByUserIdRequest.h"
#include "Task/Rest/GetFormByUserIdTask.h"
#include "Request/GetFormWithSignatureRequest.h"
#include "Task/Rest/GetFormWithSignatureTask.h"
#include "Request/GetFormWithSignatureByUserIdRequest.h"
#include "Task/Rest/GetFormWithSignatureByUserIdTask.h"
#include "Request/SetFormByUserIdRequest.h"
#include "Task/Rest/SetFormByUserIdTask.h"
#include "Request/SetFormWithSignatureRequest.h"
#include "Task/Rest/SetFormWithSignatureTask.h"
#include "Request/AcquireActionsToFormPropertiesRequest.h"
#include "Task/Rest/AcquireActionsToFormPropertiesTask.h"
#include "Request/DeleteFormRequest.h"
#include "Task/Rest/DeleteFormTask.h"
#include "Request/DeleteFormByUserIdRequest.h"
#include "Task/Rest/DeleteFormByUserIdTask.h"
#include "Request/AcquireActionToFormPropertiesByStampSheetRequest.h"
#include "Task/Rest/AcquireActionToFormPropertiesByStampSheetTask.h"
#include "Request/DescribePropertyFormsRequest.h"
#include "Task/Rest/DescribePropertyFormsTask.h"
#include "Request/DescribePropertyFormsByUserIdRequest.h"
#include "Task/Rest/DescribePropertyFormsByUserIdTask.h"
#include "Request/GetPropertyFormRequest.h"
#include "Task/Rest/GetPropertyFormTask.h"
#include "Request/GetPropertyFormByUserIdRequest.h"
#include "Task/Rest/GetPropertyFormByUserIdTask.h"
#include "Request/GetPropertyFormWithSignatureRequest.h"
#include "Task/Rest/GetPropertyFormWithSignatureTask.h"
#include "Request/GetPropertyFormWithSignatureByUserIdRequest.h"
#include "Task/Rest/GetPropertyFormWithSignatureByUserIdTask.h"
#include "Request/SetPropertyFormByUserIdRequest.h"
#include "Task/Rest/SetPropertyFormByUserIdTask.h"
#include "Request/SetPropertyFormWithSignatureRequest.h"
#include "Task/Rest/SetPropertyFormWithSignatureTask.h"
#include "Request/AcquireActionsToPropertyFormPropertiesRequest.h"
#include "Task/Rest/AcquireActionsToPropertyFormPropertiesTask.h"
#include "Request/DeletePropertyFormRequest.h"
#include "Task/Rest/DeletePropertyFormTask.h"
#include "Request/DeletePropertyFormByUserIdRequest.h"
#include "Task/Rest/DeletePropertyFormByUserIdTask.h"
#include "Request/AcquireActionToPropertyFormPropertiesByStampSheetRequest.h"
#include "Task/Rest/AcquireActionToPropertyFormPropertiesByStampSheetTask.h"

namespace Gs2::Formation
{
    class GS2FORMATION_API FGs2FormationRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2FormationRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetFormModelTask>> GetFormModel(
            const Request::FGetFormModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFormModelMastersTask>> DescribeFormModelMasters(
            const Request::FDescribeFormModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateFormModelMasterTask>> CreateFormModelMaster(
            const Request::FCreateFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFormModelMasterTask>> GetFormModelMaster(
            const Request::FGetFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateFormModelMasterTask>> UpdateFormModelMaster(
            const Request::FUpdateFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFormModelMasterTask>> DeleteFormModelMaster(
            const Request::FDeleteFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMoldModelsTask>> DescribeMoldModels(
            const Request::FDescribeMoldModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMoldModelTask>> GetMoldModel(
            const Request::FGetMoldModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMoldModelMastersTask>> DescribeMoldModelMasters(
            const Request::FDescribeMoldModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateMoldModelMasterTask>> CreateMoldModelMaster(
            const Request::FCreateMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMoldModelMasterTask>> GetMoldModelMaster(
            const Request::FGetMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateMoldModelMasterTask>> UpdateMoldModelMaster(
            const Request::FUpdateMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMoldModelMasterTask>> DeleteMoldModelMaster(
            const Request::FDeleteMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePropertyFormModelsTask>> DescribePropertyFormModels(
            const Request::FDescribePropertyFormModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPropertyFormModelTask>> GetPropertyFormModel(
            const Request::FGetPropertyFormModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePropertyFormModelMastersTask>> DescribePropertyFormModelMasters(
            const Request::FDescribePropertyFormModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreatePropertyFormModelMasterTask>> CreatePropertyFormModelMaster(
            const Request::FCreatePropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPropertyFormModelMasterTask>> GetPropertyFormModelMaster(
            const Request::FGetPropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdatePropertyFormModelMasterTask>> UpdatePropertyFormModelMaster(
            const Request::FUpdatePropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeletePropertyFormModelMasterTask>> DeletePropertyFormModelMaster(
            const Request::FDeletePropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentFormMasterTask>> GetCurrentFormMaster(
            const Request::FGetCurrentFormMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentFormMasterTask>> UpdateCurrentFormMaster(
            const Request::FUpdateCurrentFormMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentFormMasterFromGitHubTask>> UpdateCurrentFormMasterFromGitHub(
            const Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMoldsTask>> DescribeMolds(
            const Request::FDescribeMoldsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMoldsByUserIdTask>> DescribeMoldsByUserId(
            const Request::FDescribeMoldsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMoldTask>> GetMold(
            const Request::FGetMoldRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMoldByUserIdTask>> GetMoldByUserId(
            const Request::FGetMoldByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMoldCapacityByUserIdTask>> SetMoldCapacityByUserId(
            const Request::FSetMoldCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddMoldCapacityByUserIdTask>> AddMoldCapacityByUserId(
            const Request::FAddMoldCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubMoldCapacityByUserIdTask>> SubMoldCapacityByUserId(
            const Request::FSubMoldCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMoldTask>> DeleteMold(
            const Request::FDeleteMoldRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMoldByUserIdTask>> DeleteMoldByUserId(
            const Request::FDeleteMoldByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddCapacityByStampSheetTask>> AddCapacityByStampSheet(
            const Request::FAddCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubCapacityByStampTaskTask>> SubCapacityByStampTask(
            const Request::FSubCapacityByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetCapacityByStampSheetTask>> SetCapacityByStampSheet(
            const Request::FSetCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFormsTask>> DescribeForms(
            const Request::FDescribeFormsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFormsByUserIdTask>> DescribeFormsByUserId(
            const Request::FDescribeFormsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFormTask>> GetForm(
            const Request::FGetFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFormByUserIdTask>> GetFormByUserId(
            const Request::FGetFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFormWithSignatureTask>> GetFormWithSignature(
            const Request::FGetFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFormWithSignatureByUserIdTask>> GetFormWithSignatureByUserId(
            const Request::FGetFormWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetFormByUserIdTask>> SetFormByUserId(
            const Request::FSetFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetFormWithSignatureTask>> SetFormWithSignature(
            const Request::FSetFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireActionsToFormPropertiesTask>> AcquireActionsToFormProperties(
            const Request::FAcquireActionsToFormPropertiesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFormTask>> DeleteForm(
            const Request::FDeleteFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFormByUserIdTask>> DeleteFormByUserId(
            const Request::FDeleteFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireActionToFormPropertiesByStampSheetTask>> AcquireActionToFormPropertiesByStampSheet(
            const Request::FAcquireActionToFormPropertiesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePropertyFormsTask>> DescribePropertyForms(
            const Request::FDescribePropertyFormsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribePropertyFormsByUserIdTask>> DescribePropertyFormsByUserId(
            const Request::FDescribePropertyFormsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPropertyFormTask>> GetPropertyForm(
            const Request::FGetPropertyFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPropertyFormByUserIdTask>> GetPropertyFormByUserId(
            const Request::FGetPropertyFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPropertyFormWithSignatureTask>> GetPropertyFormWithSignature(
            const Request::FGetPropertyFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPropertyFormWithSignatureByUserIdTask>> GetPropertyFormWithSignatureByUserId(
            const Request::FGetPropertyFormWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetPropertyFormByUserIdTask>> SetPropertyFormByUserId(
            const Request::FSetPropertyFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetPropertyFormWithSignatureTask>> SetPropertyFormWithSignature(
            const Request::FSetPropertyFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireActionsToPropertyFormPropertiesTask>> AcquireActionsToPropertyFormProperties(
            const Request::FAcquireActionsToPropertyFormPropertiesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeletePropertyFormTask>> DeletePropertyForm(
            const Request::FDeletePropertyFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeletePropertyFormByUserIdTask>> DeletePropertyFormByUserId(
            const Request::FDeletePropertyFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcquireActionToPropertyFormPropertiesByStampSheetTask>> AcquireActionToPropertyFormPropertiesByStampSheet(
            const Request::FAcquireActionToPropertyFormPropertiesByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2FormationRestClient, ESPMode::ThreadSafe> FGs2FormationRestClientPtr;
}