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
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"
#include "Request/DescribeGuildModelMastersRequest.h"
#include "Task/WebSocket/DescribeGuildModelMastersTask.h"
#include "Request/CreateGuildModelMasterRequest.h"
#include "Task/WebSocket/CreateGuildModelMasterTask.h"
#include "Request/GetGuildModelMasterRequest.h"
#include "Task/WebSocket/GetGuildModelMasterTask.h"
#include "Request/UpdateGuildModelMasterRequest.h"
#include "Task/WebSocket/UpdateGuildModelMasterTask.h"
#include "Request/DeleteGuildModelMasterRequest.h"
#include "Task/WebSocket/DeleteGuildModelMasterTask.h"
#include "Request/DescribeGuildModelsRequest.h"
#include "Task/WebSocket/DescribeGuildModelsTask.h"
#include "Request/GetGuildModelRequest.h"
#include "Task/WebSocket/GetGuildModelTask.h"
#include "Request/SearchGuildsRequest.h"
#include "Task/WebSocket/SearchGuildsTask.h"
#include "Request/SearchGuildsByUserIdRequest.h"
#include "Task/WebSocket/SearchGuildsByUserIdTask.h"
#include "Request/CreateGuildRequest.h"
#include "Task/WebSocket/CreateGuildTask.h"
#include "Request/CreateGuildByUserIdRequest.h"
#include "Task/WebSocket/CreateGuildByUserIdTask.h"
#include "Request/GetGuildRequest.h"
#include "Task/WebSocket/GetGuildTask.h"
#include "Request/GetGuildByUserIdRequest.h"
#include "Task/WebSocket/GetGuildByUserIdTask.h"
#include "Request/UpdateGuildRequest.h"
#include "Task/WebSocket/UpdateGuildTask.h"
#include "Request/UpdateGuildByGuildNameRequest.h"
#include "Task/WebSocket/UpdateGuildByGuildNameTask.h"
#include "Request/DeleteMemberRequest.h"
#include "Task/WebSocket/DeleteMemberTask.h"
#include "Request/DeleteMemberByGuildNameRequest.h"
#include "Task/WebSocket/DeleteMemberByGuildNameTask.h"
#include "Request/UpdateMemberRoleRequest.h"
#include "Task/WebSocket/UpdateMemberRoleTask.h"
#include "Request/UpdateMemberRoleByGuildNameRequest.h"
#include "Task/WebSocket/UpdateMemberRoleByGuildNameTask.h"
#include "Request/DeleteGuildRequest.h"
#include "Task/WebSocket/DeleteGuildTask.h"
#include "Request/DeleteGuildByGuildNameRequest.h"
#include "Task/WebSocket/DeleteGuildByGuildNameTask.h"
#include "Request/IncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/WebSocket/IncreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/DecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/WebSocket/DecreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/VerifyCurrentMaximumMemberCountRequest.h"
#include "Task/WebSocket/VerifyCurrentMaximumMemberCountTask.h"
#include "Request/VerifyCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/WebSocket/VerifyCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/VerifyIncludeMemberRequest.h"
#include "Task/WebSocket/VerifyIncludeMemberTask.h"
#include "Request/VerifyIncludeMemberByUserIdRequest.h"
#include "Task/WebSocket/VerifyIncludeMemberByUserIdTask.h"
#include "Request/SetMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/WebSocket/SetMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/AssumeRequest.h"
#include "Task/WebSocket/AssumeTask.h"
#include "Request/AssumeByUserIdRequest.h"
#include "Task/WebSocket/AssumeByUserIdTask.h"
#include "Request/IncreaseMaximumCurrentMaximumMemberCountByStampSheetRequest.h"
#include "Task/WebSocket/IncreaseMaximumCurrentMaximumMemberCountByStampSheetTask.h"
#include "Request/DecreaseMaximumCurrentMaximumMemberCountByStampTaskRequest.h"
#include "Task/WebSocket/DecreaseMaximumCurrentMaximumMemberCountByStampTaskTask.h"
#include "Request/SetMaximumCurrentMaximumMemberCountByStampSheetRequest.h"
#include "Task/WebSocket/SetMaximumCurrentMaximumMemberCountByStampSheetTask.h"
#include "Request/VerifyCurrentMaximumMemberCountByStampTaskRequest.h"
#include "Task/WebSocket/VerifyCurrentMaximumMemberCountByStampTaskTask.h"
#include "Request/VerifyIncludeMemberByStampTaskRequest.h"
#include "Task/WebSocket/VerifyIncludeMemberByStampTaskTask.h"
#include "Request/DescribeJoinedGuildsRequest.h"
#include "Task/WebSocket/DescribeJoinedGuildsTask.h"
#include "Request/DescribeJoinedGuildsByUserIdRequest.h"
#include "Task/WebSocket/DescribeJoinedGuildsByUserIdTask.h"
#include "Request/GetJoinedGuildRequest.h"
#include "Task/WebSocket/GetJoinedGuildTask.h"
#include "Request/GetJoinedGuildByUserIdRequest.h"
#include "Task/WebSocket/GetJoinedGuildByUserIdTask.h"
#include "Request/WithdrawalRequest.h"
#include "Task/WebSocket/WithdrawalTask.h"
#include "Request/WithdrawalByUserIdRequest.h"
#include "Task/WebSocket/WithdrawalByUserIdTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/WebSocket/ExportMasterTask.h"
#include "Request/GetCurrentGuildMasterRequest.h"
#include "Task/WebSocket/GetCurrentGuildMasterTask.h"
#include "Request/UpdateCurrentGuildMasterRequest.h"
#include "Task/WebSocket/UpdateCurrentGuildMasterTask.h"
#include "Request/UpdateCurrentGuildMasterFromGitHubRequest.h"
#include "Task/WebSocket/UpdateCurrentGuildMasterFromGitHubTask.h"
#include "Request/DescribeReceiveRequestsRequest.h"
#include "Task/WebSocket/DescribeReceiveRequestsTask.h"
#include "Request/DescribeReceiveRequestsByGuildNameRequest.h"
#include "Task/WebSocket/DescribeReceiveRequestsByGuildNameTask.h"
#include "Request/GetReceiveRequestRequest.h"
#include "Task/WebSocket/GetReceiveRequestTask.h"
#include "Request/GetReceiveRequestByGuildNameRequest.h"
#include "Task/WebSocket/GetReceiveRequestByGuildNameTask.h"
#include "Request/AcceptRequestRequest.h"
#include "Task/WebSocket/AcceptRequestTask.h"
#include "Request/AcceptRequestByGuildNameRequest.h"
#include "Task/WebSocket/AcceptRequestByGuildNameTask.h"
#include "Request/RejectRequestRequest.h"
#include "Task/WebSocket/RejectRequestTask.h"
#include "Request/RejectRequestByGuildNameRequest.h"
#include "Task/WebSocket/RejectRequestByGuildNameTask.h"
#include "Request/DescribeSendRequestsRequest.h"
#include "Task/WebSocket/DescribeSendRequestsTask.h"
#include "Request/DescribeSendRequestsByUserIdRequest.h"
#include "Task/WebSocket/DescribeSendRequestsByUserIdTask.h"
#include "Request/GetSendRequestRequest.h"
#include "Task/WebSocket/GetSendRequestTask.h"
#include "Request/GetSendRequestByUserIdRequest.h"
#include "Task/WebSocket/GetSendRequestByUserIdTask.h"
#include "Request/SendRequestRequest.h"
#include "Task/WebSocket/SendRequestTask.h"
#include "Request/SendRequestByUserIdRequest.h"
#include "Task/WebSocket/SendRequestByUserIdTask.h"
#include "Request/DeleteRequestRequest.h"
#include "Task/WebSocket/DeleteRequestTask.h"
#include "Request/DeleteRequestByUserIdRequest.h"
#include "Task/WebSocket/DeleteRequestByUserIdTask.h"

namespace Gs2::Guild
{
    class GS2GUILD_API FGs2GuildWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2GuildWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> DumpUserDataByUserId(
            const Request::FDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> CheckDumpUserDataByUserId(
            const Request::FCheckDumpUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> CleanUserDataByUserId(
            const Request::FCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> CheckCleanUserDataByUserId(
            const Request::FCheckCleanUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> PrepareImportUserDataByUserId(
            const Request::FPrepareImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> ImportUserDataByUserId(
            const Request::FImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> CheckImportUserDataByUserId(
            const Request::FCheckImportUserDataByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGuildModelMastersTask>> DescribeGuildModelMasters(
            const Request::FDescribeGuildModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGuildModelMasterTask>> CreateGuildModelMaster(
            const Request::FCreateGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildModelMasterTask>> GetGuildModelMaster(
            const Request::FGetGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGuildModelMasterTask>> UpdateGuildModelMaster(
            const Request::FUpdateGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGuildModelMasterTask>> DeleteGuildModelMaster(
            const Request::FDeleteGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGuildModelsTask>> DescribeGuildModels(
            const Request::FDescribeGuildModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildModelTask>> GetGuildModel(
            const Request::FGetGuildModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSearchGuildsTask>> SearchGuilds(
            const Request::FSearchGuildsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSearchGuildsByUserIdTask>> SearchGuildsByUserId(
            const Request::FSearchGuildsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGuildTask>> CreateGuild(
            const Request::FCreateGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGuildByUserIdTask>> CreateGuildByUserId(
            const Request::FCreateGuildByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildTask>> GetGuild(
            const Request::FGetGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildByUserIdTask>> GetGuildByUserId(
            const Request::FGetGuildByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGuildTask>> UpdateGuild(
            const Request::FUpdateGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGuildByGuildNameTask>> UpdateGuildByGuildName(
            const Request::FUpdateGuildByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMemberTask>> DeleteMember(
            const Request::FDeleteMemberRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMemberByGuildNameTask>> DeleteMemberByGuildName(
            const Request::FDeleteMemberByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMemberRoleTask>> UpdateMemberRole(
            const Request::FUpdateMemberRoleRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMemberRoleByGuildNameTask>> UpdateMemberRoleByGuildName(
            const Request::FUpdateMemberRoleByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGuildTask>> DeleteGuild(
            const Request::FDeleteGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGuildByGuildNameTask>> DeleteGuildByGuildName(
            const Request::FDeleteGuildByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> IncreaseMaximumCurrentMaximumMemberCountByGuildName(
            const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> DecreaseMaximumCurrentMaximumMemberCountByGuildName(
            const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountTask>> VerifyCurrentMaximumMemberCount(
            const Request::FVerifyCurrentMaximumMemberCountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountByGuildNameTask>> VerifyCurrentMaximumMemberCountByGuildName(
            const Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberTask>> VerifyIncludeMember(
            const Request::FVerifyIncludeMemberRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberByUserIdTask>> VerifyIncludeMemberByUserId(
            const Request::FVerifyIncludeMemberByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaximumCurrentMaximumMemberCountByGuildNameTask>> SetMaximumCurrentMaximumMemberCountByGuildName(
            const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAssumeTask>> Assume(
            const Request::FAssumeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAssumeByUserIdTask>> AssumeByUserId(
            const Request::FAssumeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetTask>> IncreaseMaximumCurrentMaximumMemberCountByStampSheet(
            const Request::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskTask>> DecreaseMaximumCurrentMaximumMemberCountByStampTask(
            const Request::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaximumCurrentMaximumMemberCountByStampSheetTask>> SetMaximumCurrentMaximumMemberCountByStampSheet(
            const Request::FSetMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountByStampTaskTask>> VerifyCurrentMaximumMemberCountByStampTask(
            const Request::FVerifyCurrentMaximumMemberCountByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberByStampTaskTask>> VerifyIncludeMemberByStampTask(
            const Request::FVerifyIncludeMemberByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedGuildsTask>> DescribeJoinedGuilds(
            const Request::FDescribeJoinedGuildsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedGuildsByUserIdTask>> DescribeJoinedGuildsByUserId(
            const Request::FDescribeJoinedGuildsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedGuildTask>> GetJoinedGuild(
            const Request::FGetJoinedGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedGuildByUserIdTask>> GetJoinedGuildByUserId(
            const Request::FGetJoinedGuildByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawalTask>> Withdrawal(
            const Request::FWithdrawalRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawalByUserIdTask>> WithdrawalByUserId(
            const Request::FWithdrawalByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentGuildMasterTask>> GetCurrentGuildMaster(
            const Request::FGetCurrentGuildMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentGuildMasterTask>> UpdateCurrentGuildMaster(
            const Request::FUpdateCurrentGuildMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentGuildMasterFromGitHubTask>> UpdateCurrentGuildMasterFromGitHub(
            const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsTask>> DescribeReceiveRequests(
            const Request::FDescribeReceiveRequestsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsByGuildNameTask>> DescribeReceiveRequestsByGuildName(
            const Request::FDescribeReceiveRequestsByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveRequestTask>> GetReceiveRequest(
            const Request::FGetReceiveRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveRequestByGuildNameTask>> GetReceiveRequestByGuildName(
            const Request::FGetReceiveRequestByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptRequestTask>> AcceptRequest(
            const Request::FAcceptRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptRequestByGuildNameTask>> AcceptRequestByGuildName(
            const Request::FAcceptRequestByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRejectRequestTask>> RejectRequest(
            const Request::FRejectRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRejectRequestByGuildNameTask>> RejectRequestByGuildName(
            const Request::FRejectRequestByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSendRequestsTask>> DescribeSendRequests(
            const Request::FDescribeSendRequestsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSendRequestsByUserIdTask>> DescribeSendRequestsByUserId(
            const Request::FDescribeSendRequestsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSendRequestTask>> GetSendRequest(
            const Request::FGetSendRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetSendRequestByUserIdTask>> GetSendRequestByUserId(
            const Request::FGetSendRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendRequestTask>> SendRequest(
            const Request::FSendRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FSendRequestByUserIdTask>> SendRequestByUserId(
            const Request::FSendRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRequestTask>> DeleteRequest(
            const Request::FDeleteRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRequestByUserIdTask>> DeleteRequestByUserId(
            const Request::FDeleteRequestByUserIdRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2GuildWebSocketClient, ESPMode::ThreadSafe> FGs2GuildWebSocketClientPtr;
}