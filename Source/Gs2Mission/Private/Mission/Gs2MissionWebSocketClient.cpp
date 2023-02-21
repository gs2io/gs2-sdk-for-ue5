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

#include "Mission/Gs2MissionWebSocketClient.h"

namespace Gs2::Mission
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCompletesTask>> FGs2MissionWebSocketClient::DescribeCompletes(
        const Request::FDescribeCompletesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCompletesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCompletesByUserIdTask>> FGs2MissionWebSocketClient::DescribeCompletesByUserId(
        const Request::FDescribeCompletesByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCompletesByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCompleteTask>> FGs2MissionWebSocketClient::Complete(
        const Request::FCompleteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCompleteTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCompleteByUserIdTask>> FGs2MissionWebSocketClient::CompleteByUserId(
        const Request::FCompleteByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCompleteByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveByUserIdTask>> FGs2MissionWebSocketClient::ReceiveByUserId(
        const Request::FReceiveByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReceiveByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCompleteTask>> FGs2MissionWebSocketClient::GetComplete(
        const Request::FGetCompleteRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCompleteTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCompleteByUserIdTask>> FGs2MissionWebSocketClient::GetCompleteByUserId(
        const Request::FGetCompleteByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCompleteByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCompleteByUserIdTask>> FGs2MissionWebSocketClient::DeleteCompleteByUserId(
        const Request::FDeleteCompleteByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteCompleteByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FReceiveByStampTaskTask>> FGs2MissionWebSocketClient::ReceiveByStampTask(
        const Request::FReceiveByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FReceiveByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCounterModelMastersTask>> FGs2MissionWebSocketClient::DescribeCounterModelMasters(
        const Request::FDescribeCounterModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCounterModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateCounterModelMasterTask>> FGs2MissionWebSocketClient::CreateCounterModelMaster(
        const Request::FCreateCounterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateCounterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterModelMasterTask>> FGs2MissionWebSocketClient::GetCounterModelMaster(
        const Request::FGetCounterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCounterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCounterModelMasterTask>> FGs2MissionWebSocketClient::UpdateCounterModelMaster(
        const Request::FUpdateCounterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCounterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCounterModelMasterTask>> FGs2MissionWebSocketClient::DeleteCounterModelMaster(
        const Request::FDeleteCounterModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteCounterModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionGroupModelMastersTask>> FGs2MissionWebSocketClient::DescribeMissionGroupModelMasters(
        const Request::FDescribeMissionGroupModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMissionGroupModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMissionGroupModelMasterTask>> FGs2MissionWebSocketClient::CreateMissionGroupModelMaster(
        const Request::FCreateMissionGroupModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateMissionGroupModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionGroupModelMasterTask>> FGs2MissionWebSocketClient::GetMissionGroupModelMaster(
        const Request::FGetMissionGroupModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetMissionGroupModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMissionGroupModelMasterTask>> FGs2MissionWebSocketClient::UpdateMissionGroupModelMaster(
        const Request::FUpdateMissionGroupModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateMissionGroupModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMissionGroupModelMasterTask>> FGs2MissionWebSocketClient::DeleteMissionGroupModelMaster(
        const Request::FDeleteMissionGroupModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteMissionGroupModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2MissionWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2MissionWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2MissionWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2MissionWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2MissionWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2MissionWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCountersTask>> FGs2MissionWebSocketClient::DescribeCounters(
        const Request::FDescribeCountersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCountersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCountersByUserIdTask>> FGs2MissionWebSocketClient::DescribeCountersByUserId(
        const Request::FDescribeCountersByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCountersByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseCounterByUserIdTask>> FGs2MissionWebSocketClient::IncreaseCounterByUserId(
        const Request::FIncreaseCounterByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncreaseCounterByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterTask>> FGs2MissionWebSocketClient::GetCounter(
        const Request::FGetCounterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCounterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterByUserIdTask>> FGs2MissionWebSocketClient::GetCounterByUserId(
        const Request::FGetCounterByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCounterByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteCounterByUserIdTask>> FGs2MissionWebSocketClient::DeleteCounterByUserId(
        const Request::FDeleteCounterByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteCounterByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseByStampSheetTask>> FGs2MissionWebSocketClient::IncreaseByStampSheet(
        const Request::FIncreaseByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncreaseByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2MissionWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentMissionMasterTask>> FGs2MissionWebSocketClient::GetCurrentMissionMaster(
        const Request::FGetCurrentMissionMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentMissionMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentMissionMasterTask>> FGs2MissionWebSocketClient::UpdateCurrentMissionMaster(
        const Request::FUpdateCurrentMissionMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentMissionMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentMissionMasterFromGitHubTask>> FGs2MissionWebSocketClient::UpdateCurrentMissionMasterFromGitHub(
        const Request::FUpdateCurrentMissionMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentMissionMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeCounterModelsTask>> FGs2MissionWebSocketClient::DescribeCounterModels(
        const Request::FDescribeCounterModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeCounterModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCounterModelTask>> FGs2MissionWebSocketClient::GetCounterModel(
        const Request::FGetCounterModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCounterModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionGroupModelsTask>> FGs2MissionWebSocketClient::DescribeMissionGroupModels(
        const Request::FDescribeMissionGroupModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMissionGroupModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionGroupModelTask>> FGs2MissionWebSocketClient::GetMissionGroupModel(
        const Request::FGetMissionGroupModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetMissionGroupModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionTaskModelsTask>> FGs2MissionWebSocketClient::DescribeMissionTaskModels(
        const Request::FDescribeMissionTaskModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMissionTaskModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionTaskModelTask>> FGs2MissionWebSocketClient::GetMissionTaskModel(
        const Request::FGetMissionTaskModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetMissionTaskModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeMissionTaskModelMastersTask>> FGs2MissionWebSocketClient::DescribeMissionTaskModelMasters(
        const Request::FDescribeMissionTaskModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeMissionTaskModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateMissionTaskModelMasterTask>> FGs2MissionWebSocketClient::CreateMissionTaskModelMaster(
        const Request::FCreateMissionTaskModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateMissionTaskModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetMissionTaskModelMasterTask>> FGs2MissionWebSocketClient::GetMissionTaskModelMaster(
        const Request::FGetMissionTaskModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetMissionTaskModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMissionTaskModelMasterTask>> FGs2MissionWebSocketClient::UpdateMissionTaskModelMaster(
        const Request::FUpdateMissionTaskModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateMissionTaskModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMissionTaskModelMasterTask>> FGs2MissionWebSocketClient::DeleteMissionTaskModelMaster(
        const Request::FDeleteMissionTaskModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteMissionTaskModelMasterTask>>(
            Session,
            Request
        );
    }
}