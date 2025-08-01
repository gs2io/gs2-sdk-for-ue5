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
#include "Request/GetServiceVersionRequest.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeRoomsRequest.h"
#include "Task/Rest/DescribeRoomsTask.h"
#include "Request/CreateRoomRequest.h"
#include "Task/Rest/CreateRoomTask.h"
#include "Request/CreateRoomFromBackendRequest.h"
#include "Task/Rest/CreateRoomFromBackendTask.h"
#include "Request/GetRoomRequest.h"
#include "Task/Rest/GetRoomTask.h"
#include "Request/UpdateRoomRequest.h"
#include "Task/Rest/UpdateRoomTask.h"
#include "Request/UpdateRoomFromBackendRequest.h"
#include "Task/Rest/UpdateRoomFromBackendTask.h"
#include "Request/DeleteRoomRequest.h"
#include "Task/Rest/DeleteRoomTask.h"
#include "Request/DeleteRoomFromBackendRequest.h"
#include "Task/Rest/DeleteRoomFromBackendTask.h"
#include "Request/DescribeMessagesRequest.h"
#include "Task/Rest/DescribeMessagesTask.h"
#include "Request/DescribeMessagesByUserIdRequest.h"
#include "Task/Rest/DescribeMessagesByUserIdTask.h"
#include "Request/DescribeLatestMessagesRequest.h"
#include "Task/Rest/DescribeLatestMessagesTask.h"
#include "Request/DescribeLatestMessagesByUserIdRequest.h"
#include "Task/Rest/DescribeLatestMessagesByUserIdTask.h"
#include "Request/PostRequest.h"
#include "Task/Rest/PostTask.h"
#include "Request/PostByUserIdRequest.h"
#include "Task/Rest/PostByUserIdTask.h"
#include "Request/GetMessageRequest.h"
#include "Task/Rest/GetMessageTask.h"
#include "Request/GetMessageByUserIdRequest.h"
#include "Task/Rest/GetMessageByUserIdTask.h"
#include "Request/DeleteMessageRequest.h"
#include "Task/Rest/DeleteMessageTask.h"
#include "Request/DescribeSubscribesRequest.h"
#include "Task/Rest/DescribeSubscribesTask.h"
#include "Request/DescribeSubscribesByUserIdRequest.h"
#include "Task/Rest/DescribeSubscribesByUserIdTask.h"
#include "Request/DescribeSubscribesByRoomNameRequest.h"
#include "Task/Rest/DescribeSubscribesByRoomNameTask.h"
#include "Request/SubscribeRequest.h"
#include "Task/Rest/SubscribeTask.h"
#include "Request/SubscribeByUserIdRequest.h"
#include "Task/Rest/SubscribeByUserIdTask.h"
#include "Request/GetSubscribeRequest.h"
#include "Task/Rest/GetSubscribeTask.h"
#include "Request/GetSubscribeByUserIdRequest.h"
#include "Task/Rest/GetSubscribeByUserIdTask.h"
#include "Request/UpdateNotificationTypeRequest.h"
#include "Task/Rest/UpdateNotificationTypeTask.h"
#include "Request/UpdateNotificationTypeByUserIdRequest.h"
#include "Task/Rest/UpdateNotificationTypeByUserIdTask.h"
#include "Request/UnsubscribeRequest.h"
#include "Task/Rest/UnsubscribeTask.h"
#include "Request/UnsubscribeByUserIdRequest.h"
#include "Task/Rest/UnsubscribeByUserIdTask.h"
#include "Request/DescribeCategoryModelsRequest.h"
#include "Task/Rest/DescribeCategoryModelsTask.h"
#include "Request/GetCategoryModelRequest.h"
#include "Task/Rest/GetCategoryModelTask.h"
#include "Request/DescribeCategoryModelMastersRequest.h"
#include "Task/Rest/DescribeCategoryModelMastersTask.h"
#include "Request/CreateCategoryModelMasterRequest.h"
#include "Task/Rest/CreateCategoryModelMasterTask.h"
#include "Request/GetCategoryModelMasterRequest.h"
#include "Task/Rest/GetCategoryModelMasterTask.h"
#include "Request/UpdateCategoryModelMasterRequest.h"
#include "Task/Rest/UpdateCategoryModelMasterTask.h"
#include "Request/DeleteCategoryModelMasterRequest.h"
#include "Task/Rest/DeleteCategoryModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentModelMasterRequest.h"
#include "Task/Rest/GetCurrentModelMasterTask.h"
#include "Request/PreUpdateCurrentModelMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterRequest.h"
#include "Task/Rest/UpdateCurrentModelMasterTask.h"
#include "Request/UpdateCurrentModelMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentModelMasterFromGitHubTask.h"

namespace Gs2::Chat
{
    class GS2CHAT_API FGs2ChatRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2ChatRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRoomsTask>> DescribeRooms(
            const Request::FDescribeRoomsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRoomTask>> CreateRoom(
            const Request::FCreateRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateRoomFromBackendTask>> CreateRoomFromBackend(
            const Request::FCreateRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRoomTask>> GetRoom(
            const Request::FGetRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRoomTask>> UpdateRoom(
            const Request::FUpdateRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateRoomFromBackendTask>> UpdateRoomFromBackend(
            const Request::FUpdateRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRoomTask>> DeleteRoom(
            const Request::FDeleteRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRoomFromBackendTask>> DeleteRoomFromBackend(
            const Request::FDeleteRoomFromBackendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMessagesTask>> DescribeMessages(
            const Request::FDescribeMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeMessagesByUserIdTask>> DescribeMessagesByUserId(
            const Request::FDescribeMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLatestMessagesTask>> DescribeLatestMessages(
            const Request::FDescribeLatestMessagesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeLatestMessagesByUserIdTask>> DescribeLatestMessagesByUserId(
            const Request::FDescribeLatestMessagesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPostTask>> Post(
            const Request::FPostRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPostByUserIdTask>> PostByUserId(
            const Request::FPostByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMessageTask>> GetMessage(
            const Request::FGetMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetMessageByUserIdTask>> GetMessageByUserId(
            const Request::FGetMessageByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMessageTask>> DeleteMessage(
            const Request::FDeleteMessageRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesTask>> DescribeSubscribes(
            const Request::FDescribeSubscribesRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByUserIdTask>> DescribeSubscribesByUserId(
            const Request::FDescribeSubscribesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSubscribesByRoomNameTask>> DescribeSubscribesByRoomName(
            const Request::FDescribeSubscribesByRoomNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubscribeTask>> Subscribe(
            const Request::FSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSubscribeByUserIdTask>> SubscribeByUserId(
            const Request::FSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeTask>> GetSubscribe(
            const Request::FGetSubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSubscribeByUserIdTask>> GetSubscribeByUserId(
            const Request::FGetSubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNotificationTypeTask>> UpdateNotificationType(
            const Request::FUpdateNotificationTypeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateNotificationTypeByUserIdTask>> UpdateNotificationTypeByUserId(
            const Request::FUpdateNotificationTypeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnsubscribeTask>> Unsubscribe(
            const Request::FUnsubscribeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnsubscribeByUserIdTask>> UnsubscribeByUserId(
            const Request::FUnsubscribeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCategoryModelsTask>> DescribeCategoryModels(
            const Request::FDescribeCategoryModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCategoryModelTask>> GetCategoryModel(
            const Request::FGetCategoryModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCategoryModelMastersTask>> DescribeCategoryModelMasters(
            const Request::FDescribeCategoryModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateCategoryModelMasterTask>> CreateCategoryModelMaster(
            const Request::FCreateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCategoryModelMasterTask>> GetCategoryModelMaster(
            const Request::FGetCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCategoryModelMasterTask>> UpdateCategoryModelMaster(
            const Request::FUpdateCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCategoryModelMasterTask>> DeleteCategoryModelMaster(
            const Request::FDeleteCategoryModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentModelMasterTask>> GetCurrentModelMaster(
            const Request::FGetCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentModelMasterTask>> PreUpdateCurrentModelMaster(
            const Request::FPreUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentModelMasterTask>> UpdateCurrentModelMaster(
            const Request::FUpdateCurrentModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentModelMasterFromGitHubTask>> UpdateCurrentModelMasterFromGitHub(
            const Request::FUpdateCurrentModelMasterFromGitHubRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2ChatRestClient, ESPMode::ThreadSafe> FGs2ChatRestClientPtr;
}