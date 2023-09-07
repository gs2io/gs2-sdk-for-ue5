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
#include "Request/GetFormModelRequest.h"
#include "Task/WebSocket/GetFormModelTask.h"
#include "Request/DescribeFormModelMastersRequest.h"
#include "Task/WebSocket/DescribeFormModelMastersTask.h"
#include "Request/CreateFormModelMasterRequest.h"
#include "Task/WebSocket/CreateFormModelMasterTask.h"
#include "Request/GetFormModelMasterRequest.h"
#include "Task/WebSocket/GetFormModelMasterTask.h"
#include "Request/UpdateFormModelMasterRequest.h"
#include "Task/WebSocket/UpdateFormModelMasterTask.h"
#include "Request/DeleteFormModelMasterRequest.h"
#include "Task/WebSocket/DeleteFormModelMasterTask.h"
#include "Request/DescribeMoldModelsRequest.h"
#include "Task/WebSocket/DescribeMoldModelsTask.h"
#include "Request/GetMoldModelRequest.h"
#include "Task/WebSocket/GetMoldModelTask.h"
#include "Request/DescribeMoldModelMastersRequest.h"
#include "Task/WebSocket/DescribeMoldModelMastersTask.h"
#include "Request/CreateMoldModelMasterRequest.h"
#include "Task/WebSocket/CreateMoldModelMasterTask.h"
#include "Request/GetMoldModelMasterRequest.h"
#include "Task/WebSocket/GetMoldModelMasterTask.h"
#include "Request/UpdateMoldModelMasterRequest.h"
#include "Task/WebSocket/UpdateMoldModelMasterTask.h"
#include "Request/DeleteMoldModelMasterRequest.h"
#include "Task/WebSocket/DeleteMoldModelMasterTask.h"
#include "Request/DescribePropertyFormModelsRequest.h"
#include "Task/WebSocket/DescribePropertyFormModelsTask.h"
#include "Request/GetPropertyFormModelRequest.h"
#include "Task/WebSocket/GetPropertyFormModelTask.h"
#include "Request/DescribePropertyFormModelMastersRequest.h"
#include "Task/WebSocket/DescribePropertyFormModelMastersTask.h"
#include "Request/CreatePropertyFormModelMasterRequest.h"
#include "Task/WebSocket/CreatePropertyFormModelMasterTask.h"
#include "Request/GetPropertyFormModelMasterRequest.h"
#include "Task/WebSocket/GetPropertyFormModelMasterTask.h"
#include "Request/UpdatePropertyFormModelMasterRequest.h"
#include "Task/WebSocket/UpdatePropertyFormModelMasterTask.h"
#include "Request/DeletePropertyFormModelMasterRequest.h"
#include "Task/WebSocket/DeletePropertyFormModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentFormMasterRequest.h"
#include "Task/WebSocket/GetCurrentFormMasterTask.h"
#include "Request/UpdateCurrentFormMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentFormMasterTask.h"
#include "Request/UpdateCurrentFormMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentFormMasterFromGitHubTask.h"
#include "Request/DescribeMoldsRequest.h"
#include "Task/WebSocket/DescribeMoldsTask.h"
#include "Request/DescribeMoldsByUserIdRequest.h"
#include "Task/WebSocket/DescribeMoldsByUserIdTask.h"
#include "Request/GetMoldRequest.h"
#include "Task/WebSocket/GetMoldTask.h"
#include "Request/GetMoldByUserIdRequest.h"
#include "Task/WebSocket/GetMoldByUserIdTask.h"
#include "Request/SetMoldCapacityByUserIdRequest.h"
#include "Task/WebSocket/SetMoldCapacityByUserIdTask.h"
#include "Request/AddMoldCapacityByUserIdRequest.h"
#include "Task/WebSocket/AddMoldCapacityByUserIdTask.h"
#include "Request/SubMoldCapacityByUserIdRequest.h"
#include "Task/WebSocket/SubMoldCapacityByUserIdTask.h"
#include "Request/DeleteMoldRequest.h"
#include "Task/WebSocket/DeleteMoldTask.h"
#include "Request/DeleteMoldByUserIdRequest.h"
#include "Task/WebSocket/DeleteMoldByUserIdTask.h"
#include "Request/AddCapacityByStampSheetRequest.h"
#include "Task/WebSocket/AddCapacityByStampSheetTask.h"
#include "Request/SubCapacityByStampTaskRequest.h"
#include "Task/WebSocket/SubCapacityByStampTaskTask.h"
#include "Request/SetCapacityByStampSheetRequest.h"
#include "Task/WebSocket/SetCapacityByStampSheetTask.h"
#include "Request/DescribeFormsRequest.h"
#include "Task/WebSocket/DescribeFormsTask.h"
#include "Request/DescribeFormsByUserIdRequest.h"
#include "Task/WebSocket/DescribeFormsByUserIdTask.h"
#include "Request/GetFormRequest.h"
#include "Task/WebSocket/GetFormTask.h"
#include "Request/GetFormByUserIdRequest.h"
#include "Task/WebSocket/GetFormByUserIdTask.h"
#include "Request/GetFormWithSignatureRequest.h"
#include "Task/WebSocket/GetFormWithSignatureTask.h"
#include "Request/GetFormWithSignatureByUserIdRequest.h"
#include "Task/WebSocket/GetFormWithSignatureByUserIdTask.h"
#include "Request/SetFormByUserIdRequest.h"
#include "Task/WebSocket/SetFormByUserIdTask.h"
#include "Request/SetFormWithSignatureRequest.h"
#include "Task/WebSocket/SetFormWithSignatureTask.h"
#include "Request/AcquireActionsToFormPropertiesRequest.h"
#include "Task/WebSocket/AcquireActionsToFormPropertiesTask.h"
#include "Request/DeleteFormRequest.h"
#include "Task/WebSocket/DeleteFormTask.h"
#include "Request/DeleteFormByUserIdRequest.h"
#include "Task/WebSocket/DeleteFormByUserIdTask.h"
#include "Request/AcquireActionToFormPropertiesByStampSheetRequest.h"
#include "Task/WebSocket/AcquireActionToFormPropertiesByStampSheetTask.h"
#include "Request/DescribePropertyFormsRequest.h"
#include "Task/WebSocket/DescribePropertyFormsTask.h"
#include "Request/DescribePropertyFormsByUserIdRequest.h"
#include "Task/WebSocket/DescribePropertyFormsByUserIdTask.h"
#include "Request/GetPropertyFormRequest.h"
#include "Task/WebSocket/GetPropertyFormTask.h"
#include "Request/GetPropertyFormByUserIdRequest.h"
#include "Task/WebSocket/GetPropertyFormByUserIdTask.h"
#include "Request/GetPropertyFormWithSignatureRequest.h"
#include "Task/WebSocket/GetPropertyFormWithSignatureTask.h"
#include "Request/GetPropertyFormWithSignatureByUserIdRequest.h"
#include "Task/WebSocket/GetPropertyFormWithSignatureByUserIdTask.h"
#include "Request/SetPropertyFormByUserIdRequest.h"
#include "Task/WebSocket/SetPropertyFormByUserIdTask.h"
#include "Request/SetPropertyFormWithSignatureRequest.h"
#include "Task/WebSocket/SetPropertyFormWithSignatureTask.h"
#include "Request/AcquireActionsToPropertyFormPropertiesRequest.h"
#include "Task/WebSocket/AcquireActionsToPropertyFormPropertiesTask.h"
#include "Request/DeletePropertyFormRequest.h"
#include "Task/WebSocket/DeletePropertyFormTask.h"
#include "Request/DeletePropertyFormByUserIdRequest.h"
#include "Task/WebSocket/DeletePropertyFormByUserIdTask.h"
#include "Request/AcquireActionToPropertyFormPropertiesByStampSheetRequest.h"
#include "Task/WebSocket/AcquireActionToPropertyFormPropertiesByStampSheetTask.h"

namespace Gs2::Formation
{
    class GS2FORMATION_API FGs2FormationWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2FormationWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFormModelTask>> GetFormModel(
            const Request::FGetFormModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFormModelMastersTask>> DescribeFormModelMasters(
            const Request::FDescribeFormModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateFormModelMasterTask>> CreateFormModelMaster(
            const Request::FCreateFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFormModelMasterTask>> GetFormModelMaster(
            const Request::FGetFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateFormModelMasterTask>> UpdateFormModelMaster(
            const Request::FUpdateFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFormModelMasterTask>> DeleteFormModelMaster(
            const Request::FDeleteFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMoldModelsTask>> DescribeMoldModels(
            const Request::FDescribeMoldModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMoldModelTask>> GetMoldModel(
            const Request::FGetMoldModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMoldModelMastersTask>> DescribeMoldModelMasters(
            const Request::FDescribeMoldModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMoldModelMasterTask>> CreateMoldModelMaster(
            const Request::FCreateMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMoldModelMasterTask>> GetMoldModelMaster(
            const Request::FGetMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMoldModelMasterTask>> UpdateMoldModelMaster(
            const Request::FUpdateMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMoldModelMasterTask>> DeleteMoldModelMaster(
            const Request::FDeleteMoldModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePropertyFormModelsTask>> DescribePropertyFormModels(
            const Request::FDescribePropertyFormModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPropertyFormModelTask>> GetPropertyFormModel(
            const Request::FGetPropertyFormModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePropertyFormModelMastersTask>> DescribePropertyFormModelMasters(
            const Request::FDescribePropertyFormModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreatePropertyFormModelMasterTask>> CreatePropertyFormModelMaster(
            const Request::FCreatePropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPropertyFormModelMasterTask>> GetPropertyFormModelMaster(
            const Request::FGetPropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdatePropertyFormModelMasterTask>> UpdatePropertyFormModelMaster(
            const Request::FUpdatePropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePropertyFormModelMasterTask>> DeletePropertyFormModelMaster(
            const Request::FDeletePropertyFormModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentFormMasterTask>> GetCurrentFormMaster(
            const Request::FGetCurrentFormMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentFormMasterTask>> UpdateCurrentFormMaster(
            const Request::FUpdateCurrentFormMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentFormMasterFromGitHubTask>> UpdateCurrentFormMasterFromGitHub(
            const Request::FUpdateCurrentFormMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMoldsTask>> DescribeMolds(
            const Request::FDescribeMoldsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMoldsByUserIdTask>> DescribeMoldsByUserId(
            const Request::FDescribeMoldsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMoldTask>> GetMold(
            const Request::FGetMoldRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetMoldByUserIdTask>> GetMoldByUserId(
            const Request::FGetMoldByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetMoldCapacityByUserIdTask>> SetMoldCapacityByUserId(
            const Request::FSetMoldCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddMoldCapacityByUserIdTask>> AddMoldCapacityByUserId(
            const Request::FAddMoldCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubMoldCapacityByUserIdTask>> SubMoldCapacityByUserId(
            const Request::FSubMoldCapacityByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMoldTask>> DeleteMold(
            const Request::FDeleteMoldRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMoldByUserIdTask>> DeleteMoldByUserId(
            const Request::FDeleteMoldByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAddCapacityByStampSheetTask>> AddCapacityByStampSheet(
            const Request::FAddCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSubCapacityByStampTaskTask>> SubCapacityByStampTask(
            const Request::FSubCapacityByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetCapacityByStampSheetTask>> SetCapacityByStampSheet(
            const Request::FSetCapacityByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFormsTask>> DescribeForms(
            const Request::FDescribeFormsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFormsByUserIdTask>> DescribeFormsByUserId(
            const Request::FDescribeFormsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFormTask>> GetForm(
            const Request::FGetFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFormByUserIdTask>> GetFormByUserId(
            const Request::FGetFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFormWithSignatureTask>> GetFormWithSignature(
            const Request::FGetFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFormWithSignatureByUserIdTask>> GetFormWithSignatureByUserId(
            const Request::FGetFormWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetFormByUserIdTask>> SetFormByUserId(
            const Request::FSetFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetFormWithSignatureTask>> SetFormWithSignature(
            const Request::FSetFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireActionsToFormPropertiesTask>> AcquireActionsToFormProperties(
            const Request::FAcquireActionsToFormPropertiesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFormTask>> DeleteForm(
            const Request::FDeleteFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFormByUserIdTask>> DeleteFormByUserId(
            const Request::FDeleteFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireActionToFormPropertiesByStampSheetTask>> AcquireActionToFormPropertiesByStampSheet(
            const Request::FAcquireActionToFormPropertiesByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePropertyFormsTask>> DescribePropertyForms(
            const Request::FDescribePropertyFormsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribePropertyFormsByUserIdTask>> DescribePropertyFormsByUserId(
            const Request::FDescribePropertyFormsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPropertyFormTask>> GetPropertyForm(
            const Request::FGetPropertyFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPropertyFormByUserIdTask>> GetPropertyFormByUserId(
            const Request::FGetPropertyFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPropertyFormWithSignatureTask>> GetPropertyFormWithSignature(
            const Request::FGetPropertyFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPropertyFormWithSignatureByUserIdTask>> GetPropertyFormWithSignatureByUserId(
            const Request::FGetPropertyFormWithSignatureByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetPropertyFormByUserIdTask>> SetPropertyFormByUserId(
            const Request::FSetPropertyFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetPropertyFormWithSignatureTask>> SetPropertyFormWithSignature(
            const Request::FSetPropertyFormWithSignatureRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireActionsToPropertyFormPropertiesTask>> AcquireActionsToPropertyFormProperties(
            const Request::FAcquireActionsToPropertyFormPropertiesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePropertyFormTask>> DeletePropertyForm(
            const Request::FDeletePropertyFormRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeletePropertyFormByUserIdTask>> DeletePropertyFormByUserId(
            const Request::FDeletePropertyFormByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcquireActionToPropertyFormPropertiesByStampSheetTask>> AcquireActionToPropertyFormPropertiesByStampSheet(
            const Request::FAcquireActionToPropertyFormPropertiesByStampSheetRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2FormationWebSocketClient, ESPMode::ThreadSafe> FGs2FormationWebSocketClientPtr;
}