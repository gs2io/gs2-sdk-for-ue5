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
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeQuestGroupModelMastersRequest.h"
#include "Task/Rest/DescribeQuestGroupModelMastersTask.h"
#include "Request/CreateQuestGroupModelMasterRequest.h"
#include "Task/Rest/CreateQuestGroupModelMasterTask.h"
#include "Request/GetQuestGroupModelMasterRequest.h"
#include "Task/Rest/GetQuestGroupModelMasterTask.h"
#include "Request/UpdateQuestGroupModelMasterRequest.h"
#include "Task/Rest/UpdateQuestGroupModelMasterTask.h"
#include "Request/DeleteQuestGroupModelMasterRequest.h"
#include "Task/Rest/DeleteQuestGroupModelMasterTask.h"
#include "Request/DescribeQuestModelMastersRequest.h"
#include "Task/Rest/DescribeQuestModelMastersTask.h"
#include "Request/CreateQuestModelMasterRequest.h"
#include "Task/Rest/CreateQuestModelMasterTask.h"
#include "Request/GetQuestModelMasterRequest.h"
#include "Task/Rest/GetQuestModelMasterTask.h"
#include "Request/UpdateQuestModelMasterRequest.h"
#include "Task/Rest/UpdateQuestModelMasterTask.h"
#include "Request/DeleteQuestModelMasterRequest.h"
#include "Task/Rest/DeleteQuestModelMasterTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentQuestMasterRequest.h"
#include "Task/Rest/GetCurrentQuestMasterTask.h"
#include "Request/PreUpdateCurrentQuestMasterRequest.h"
#include "Task/Rest/PreUpdateCurrentQuestMasterTask.h"
#include "Request/UpdateCurrentQuestMasterRequest.h"
#include "Task/Rest/UpdateCurrentQuestMasterTask.h"
#include "Request/UpdateCurrentQuestMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentQuestMasterFromGitHubTask.h"
#include "Request/DescribeProgressesByUserIdRequest.h"
#include "Task/Rest/DescribeProgressesByUserIdTask.h"
#include "Request/CreateProgressByUserIdRequest.h"
#include "Task/Rest/CreateProgressByUserIdTask.h"
#include "Request/GetProgressRequest.h"
#include "Task/Rest/GetProgressTask.h"
#include "Request/GetProgressByUserIdRequest.h"
#include "Task/Rest/GetProgressByUserIdTask.h"
#include "Request/StartRequest.h"
#include "Task/Rest/StartTask.h"
#include "Request/StartByUserIdRequest.h"
#include "Task/Rest/StartByUserIdTask.h"
#include "Request/EndRequest.h"
#include "Task/Rest/EndTask.h"
#include "Request/EndByUserIdRequest.h"
#include "Task/Rest/EndByUserIdTask.h"
#include "Request/DeleteProgressRequest.h"
#include "Task/Rest/DeleteProgressTask.h"
#include "Request/DeleteProgressByUserIdRequest.h"
#include "Task/Rest/DeleteProgressByUserIdTask.h"
#include "Request/CreateProgressByStampSheetRequest.h"
#include "Task/Rest/CreateProgressByStampSheetTask.h"
#include "Request/DeleteProgressByStampTaskRequest.h"
#include "Task/Rest/DeleteProgressByStampTaskTask.h"
#include "Request/DescribeCompletedQuestListsRequest.h"
#include "Task/Rest/DescribeCompletedQuestListsTask.h"
#include "Request/DescribeCompletedQuestListsByUserIdRequest.h"
#include "Task/Rest/DescribeCompletedQuestListsByUserIdTask.h"
#include "Request/GetCompletedQuestListRequest.h"
#include "Task/Rest/GetCompletedQuestListTask.h"
#include "Request/GetCompletedQuestListByUserIdRequest.h"
#include "Task/Rest/GetCompletedQuestListByUserIdTask.h"
#include "Request/DeleteCompletedQuestListByUserIdRequest.h"
#include "Task/Rest/DeleteCompletedQuestListByUserIdTask.h"
#include "Request/DescribeQuestGroupModelsRequest.h"
#include "Task/Rest/DescribeQuestGroupModelsTask.h"
#include "Request/GetQuestGroupModelRequest.h"
#include "Task/Rest/GetQuestGroupModelTask.h"
#include "Request/DescribeQuestModelsRequest.h"
#include "Task/Rest/DescribeQuestModelsTask.h"
#include "Request/GetQuestModelRequest.h"
#include "Task/Rest/GetQuestModelTask.h"

namespace Gs2::Quest
{
    class GS2QUEST_API FGs2QuestRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2QuestRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeQuestGroupModelMastersTask>> DescribeQuestGroupModelMasters(
            const Request::FDescribeQuestGroupModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateQuestGroupModelMasterTask>> CreateQuestGroupModelMaster(
            const Request::FCreateQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetQuestGroupModelMasterTask>> GetQuestGroupModelMaster(
            const Request::FGetQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateQuestGroupModelMasterTask>> UpdateQuestGroupModelMaster(
            const Request::FUpdateQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteQuestGroupModelMasterTask>> DeleteQuestGroupModelMaster(
            const Request::FDeleteQuestGroupModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeQuestModelMastersTask>> DescribeQuestModelMasters(
            const Request::FDescribeQuestModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateQuestModelMasterTask>> CreateQuestModelMaster(
            const Request::FCreateQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetQuestModelMasterTask>> GetQuestModelMaster(
            const Request::FGetQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateQuestModelMasterTask>> UpdateQuestModelMaster(
            const Request::FUpdateQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteQuestModelMasterTask>> DeleteQuestModelMaster(
            const Request::FDeleteQuestModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentQuestMasterTask>> GetCurrentQuestMaster(
            const Request::FGetCurrentQuestMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPreUpdateCurrentQuestMasterTask>> PreUpdateCurrentQuestMaster(
            const Request::FPreUpdateCurrentQuestMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentQuestMasterTask>> UpdateCurrentQuestMaster(
            const Request::FUpdateCurrentQuestMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentQuestMasterFromGitHubTask>> UpdateCurrentQuestMasterFromGitHub(
            const Request::FUpdateCurrentQuestMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeProgressesByUserIdTask>> DescribeProgressesByUserId(
            const Request::FDescribeProgressesByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateProgressByUserIdTask>> CreateProgressByUserId(
            const Request::FCreateProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetProgressTask>> GetProgress(
            const Request::FGetProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetProgressByUserIdTask>> GetProgressByUserId(
            const Request::FGetProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FStartTask>> Start(
            const Request::FStartRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FStartByUserIdTask>> StartByUserId(
            const Request::FStartByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEndTask>> End(
            const Request::FEndRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FEndByUserIdTask>> EndByUserId(
            const Request::FEndByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProgressTask>> DeleteProgress(
            const Request::FDeleteProgressRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProgressByUserIdTask>> DeleteProgressByUserId(
            const Request::FDeleteProgressByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateProgressByStampSheetTask>> CreateProgressByStampSheet(
            const Request::FCreateProgressByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProgressByStampTaskTask>> DeleteProgressByStampTask(
            const Request::FDeleteProgressByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCompletedQuestListsTask>> DescribeCompletedQuestLists(
            const Request::FDescribeCompletedQuestListsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeCompletedQuestListsByUserIdTask>> DescribeCompletedQuestListsByUserId(
            const Request::FDescribeCompletedQuestListsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCompletedQuestListTask>> GetCompletedQuestList(
            const Request::FGetCompletedQuestListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCompletedQuestListByUserIdTask>> GetCompletedQuestListByUserId(
            const Request::FGetCompletedQuestListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteCompletedQuestListByUserIdTask>> DeleteCompletedQuestListByUserId(
            const Request::FDeleteCompletedQuestListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeQuestGroupModelsTask>> DescribeQuestGroupModels(
            const Request::FDescribeQuestGroupModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetQuestGroupModelTask>> GetQuestGroupModel(
            const Request::FGetQuestGroupModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeQuestModelsTask>> DescribeQuestModels(
            const Request::FDescribeQuestModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetQuestModelTask>> GetQuestModel(
            const Request::FGetQuestModelRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2QuestRestClient, ESPMode::ThreadSafe> FGs2QuestRestClientPtr;
}