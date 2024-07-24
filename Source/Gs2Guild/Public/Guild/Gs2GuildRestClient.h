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
#include "Request/DescribeGuildModelMastersRequest.h"
#include "Task/Rest/DescribeGuildModelMastersTask.h"
#include "Request/CreateGuildModelMasterRequest.h"
#include "Task/Rest/CreateGuildModelMasterTask.h"
#include "Request/GetGuildModelMasterRequest.h"
#include "Task/Rest/GetGuildModelMasterTask.h"
#include "Request/UpdateGuildModelMasterRequest.h"
#include "Task/Rest/UpdateGuildModelMasterTask.h"
#include "Request/DeleteGuildModelMasterRequest.h"
#include "Task/Rest/DeleteGuildModelMasterTask.h"
#include "Request/DescribeGuildModelsRequest.h"
#include "Task/Rest/DescribeGuildModelsTask.h"
#include "Request/GetGuildModelRequest.h"
#include "Task/Rest/GetGuildModelTask.h"
#include "Request/SearchGuildsRequest.h"
#include "Task/Rest/SearchGuildsTask.h"
#include "Request/SearchGuildsByUserIdRequest.h"
#include "Task/Rest/SearchGuildsByUserIdTask.h"
#include "Request/CreateGuildRequest.h"
#include "Task/Rest/CreateGuildTask.h"
#include "Request/CreateGuildByUserIdRequest.h"
#include "Task/Rest/CreateGuildByUserIdTask.h"
#include "Request/GetGuildRequest.h"
#include "Task/Rest/GetGuildTask.h"
#include "Request/GetGuildByUserIdRequest.h"
#include "Task/Rest/GetGuildByUserIdTask.h"
#include "Request/UpdateGuildRequest.h"
#include "Task/Rest/UpdateGuildTask.h"
#include "Request/UpdateGuildByGuildNameRequest.h"
#include "Task/Rest/UpdateGuildByGuildNameTask.h"
#include "Request/DeleteMemberRequest.h"
#include "Task/Rest/DeleteMemberTask.h"
#include "Request/DeleteMemberByGuildNameRequest.h"
#include "Task/Rest/DeleteMemberByGuildNameTask.h"
#include "Request/UpdateMemberRoleRequest.h"
#include "Task/Rest/UpdateMemberRoleTask.h"
#include "Request/UpdateMemberRoleByGuildNameRequest.h"
#include "Task/Rest/UpdateMemberRoleByGuildNameTask.h"
#include "Request/DeleteGuildRequest.h"
#include "Task/Rest/DeleteGuildTask.h"
#include "Request/DeleteGuildByGuildNameRequest.h"
#include "Task/Rest/DeleteGuildByGuildNameTask.h"
#include "Request/IncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/Rest/IncreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/DecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/Rest/DecreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/VerifyCurrentMaximumMemberCountRequest.h"
#include "Task/Rest/VerifyCurrentMaximumMemberCountTask.h"
#include "Request/VerifyCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/Rest/VerifyCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/VerifyIncludeMemberRequest.h"
#include "Task/Rest/VerifyIncludeMemberTask.h"
#include "Request/VerifyIncludeMemberByUserIdRequest.h"
#include "Task/Rest/VerifyIncludeMemberByUserIdTask.h"
#include "Request/SetMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Task/Rest/SetMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Request/AssumeRequest.h"
#include "Task/Rest/AssumeTask.h"
#include "Request/AssumeByUserIdRequest.h"
#include "Task/Rest/AssumeByUserIdTask.h"
#include "Request/IncreaseMaximumCurrentMaximumMemberCountByStampSheetRequest.h"
#include "Task/Rest/IncreaseMaximumCurrentMaximumMemberCountByStampSheetTask.h"
#include "Request/DecreaseMaximumCurrentMaximumMemberCountByStampTaskRequest.h"
#include "Task/Rest/DecreaseMaximumCurrentMaximumMemberCountByStampTaskTask.h"
#include "Request/SetMaximumCurrentMaximumMemberCountByStampSheetRequest.h"
#include "Task/Rest/SetMaximumCurrentMaximumMemberCountByStampSheetTask.h"
#include "Request/VerifyCurrentMaximumMemberCountByStampTaskRequest.h"
#include "Task/Rest/VerifyCurrentMaximumMemberCountByStampTaskTask.h"
#include "Request/VerifyIncludeMemberByStampTaskRequest.h"
#include "Task/Rest/VerifyIncludeMemberByStampTaskTask.h"
#include "Request/DescribeJoinedGuildsRequest.h"
#include "Task/Rest/DescribeJoinedGuildsTask.h"
#include "Request/DescribeJoinedGuildsByUserIdRequest.h"
#include "Task/Rest/DescribeJoinedGuildsByUserIdTask.h"
#include "Request/GetJoinedGuildRequest.h"
#include "Task/Rest/GetJoinedGuildTask.h"
#include "Request/GetJoinedGuildByUserIdRequest.h"
#include "Task/Rest/GetJoinedGuildByUserIdTask.h"
#include "Request/WithdrawalRequest.h"
#include "Task/Rest/WithdrawalTask.h"
#include "Request/WithdrawalByUserIdRequest.h"
#include "Task/Rest/WithdrawalByUserIdTask.h"
#include "Request/GetLastGuildMasterActivityRequest.h"
#include "Task/Rest/GetLastGuildMasterActivityTask.h"
#include "Request/GetLastGuildMasterActivityByGuildNameRequest.h"
#include "Task/Rest/GetLastGuildMasterActivityByGuildNameTask.h"
#include "Request/PromoteSeniorMemberRequest.h"
#include "Task/Rest/PromoteSeniorMemberTask.h"
#include "Request/PromoteSeniorMemberByGuildNameRequest.h"
#include "Task/Rest/PromoteSeniorMemberByGuildNameTask.h"
#include "Request/ExportMasterRequest.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Request/GetCurrentGuildMasterRequest.h"
#include "Task/Rest/GetCurrentGuildMasterTask.h"
#include "Request/UpdateCurrentGuildMasterRequest.h"
#include "Task/Rest/UpdateCurrentGuildMasterTask.h"
#include "Request/UpdateCurrentGuildMasterFromGitHubRequest.h"
#include "Task/Rest/UpdateCurrentGuildMasterFromGitHubTask.h"
#include "Request/DescribeReceiveRequestsRequest.h"
#include "Task/Rest/DescribeReceiveRequestsTask.h"
#include "Request/DescribeReceiveRequestsByGuildNameRequest.h"
#include "Task/Rest/DescribeReceiveRequestsByGuildNameTask.h"
#include "Request/GetReceiveRequestRequest.h"
#include "Task/Rest/GetReceiveRequestTask.h"
#include "Request/GetReceiveRequestByGuildNameRequest.h"
#include "Task/Rest/GetReceiveRequestByGuildNameTask.h"
#include "Request/AcceptRequestRequest.h"
#include "Task/Rest/AcceptRequestTask.h"
#include "Request/AcceptRequestByGuildNameRequest.h"
#include "Task/Rest/AcceptRequestByGuildNameTask.h"
#include "Request/RejectRequestRequest.h"
#include "Task/Rest/RejectRequestTask.h"
#include "Request/RejectRequestByGuildNameRequest.h"
#include "Task/Rest/RejectRequestByGuildNameTask.h"
#include "Request/DescribeSendRequestsRequest.h"
#include "Task/Rest/DescribeSendRequestsTask.h"
#include "Request/DescribeSendRequestsByUserIdRequest.h"
#include "Task/Rest/DescribeSendRequestsByUserIdTask.h"
#include "Request/GetSendRequestRequest.h"
#include "Task/Rest/GetSendRequestTask.h"
#include "Request/GetSendRequestByUserIdRequest.h"
#include "Task/Rest/GetSendRequestByUserIdTask.h"
#include "Request/SendRequestRequest.h"
#include "Task/Rest/SendRequestTask.h"
#include "Request/SendRequestByUserIdRequest.h"
#include "Task/Rest/SendRequestByUserIdTask.h"
#include "Request/DeleteRequestRequest.h"
#include "Task/Rest/DeleteRequestTask.h"
#include "Request/DeleteRequestByUserIdRequest.h"
#include "Task/Rest/DeleteRequestByUserIdTask.h"
#include "Request/DescribeIgnoreUsersRequest.h"
#include "Task/Rest/DescribeIgnoreUsersTask.h"
#include "Request/DescribeIgnoreUsersByGuildNameRequest.h"
#include "Task/Rest/DescribeIgnoreUsersByGuildNameTask.h"
#include "Request/GetIgnoreUserRequest.h"
#include "Task/Rest/GetIgnoreUserTask.h"
#include "Request/GetIgnoreUserByGuildNameRequest.h"
#include "Task/Rest/GetIgnoreUserByGuildNameTask.h"
#include "Request/AddIgnoreUserRequest.h"
#include "Task/Rest/AddIgnoreUserTask.h"
#include "Request/AddIgnoreUserByGuildNameRequest.h"
#include "Task/Rest/AddIgnoreUserByGuildNameTask.h"
#include "Request/DeleteIgnoreUserRequest.h"
#include "Task/Rest/DeleteIgnoreUserTask.h"
#include "Request/DeleteIgnoreUserByGuildNameRequest.h"
#include "Task/Rest/DeleteIgnoreUserByGuildNameTask.h"

namespace Gs2::Guild
{
    class GS2GUILD_API FGs2GuildRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2GuildRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGuildModelMastersTask>> DescribeGuildModelMasters(
            const Request::FDescribeGuildModelMastersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGuildModelMasterTask>> CreateGuildModelMaster(
            const Request::FCreateGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGuildModelMasterTask>> GetGuildModelMaster(
            const Request::FGetGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGuildModelMasterTask>> UpdateGuildModelMaster(
            const Request::FUpdateGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGuildModelMasterTask>> DeleteGuildModelMaster(
            const Request::FDeleteGuildModelMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeGuildModelsTask>> DescribeGuildModels(
            const Request::FDescribeGuildModelsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGuildModelTask>> GetGuildModel(
            const Request::FGetGuildModelRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSearchGuildsTask>> SearchGuilds(
            const Request::FSearchGuildsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSearchGuildsByUserIdTask>> SearchGuildsByUserId(
            const Request::FSearchGuildsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGuildTask>> CreateGuild(
            const Request::FCreateGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FCreateGuildByUserIdTask>> CreateGuildByUserId(
            const Request::FCreateGuildByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGuildTask>> GetGuild(
            const Request::FGetGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetGuildByUserIdTask>> GetGuildByUserId(
            const Request::FGetGuildByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGuildTask>> UpdateGuild(
            const Request::FUpdateGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateGuildByGuildNameTask>> UpdateGuildByGuildName(
            const Request::FUpdateGuildByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMemberTask>> DeleteMember(
            const Request::FDeleteMemberRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteMemberByGuildNameTask>> DeleteMemberByGuildName(
            const Request::FDeleteMemberByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateMemberRoleTask>> UpdateMemberRole(
            const Request::FUpdateMemberRoleRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateMemberRoleByGuildNameTask>> UpdateMemberRoleByGuildName(
            const Request::FUpdateMemberRoleByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGuildTask>> DeleteGuild(
            const Request::FDeleteGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteGuildByGuildNameTask>> DeleteGuildByGuildName(
            const Request::FDeleteGuildByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> IncreaseMaximumCurrentMaximumMemberCountByGuildName(
            const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> DecreaseMaximumCurrentMaximumMemberCountByGuildName(
            const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCurrentMaximumMemberCountTask>> VerifyCurrentMaximumMemberCount(
            const Request::FVerifyCurrentMaximumMemberCountRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCurrentMaximumMemberCountByGuildNameTask>> VerifyCurrentMaximumMemberCountByGuildName(
            const Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyIncludeMemberTask>> VerifyIncludeMember(
            const Request::FVerifyIncludeMemberRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyIncludeMemberByUserIdTask>> VerifyIncludeMemberByUserId(
            const Request::FVerifyIncludeMemberByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaximumCurrentMaximumMemberCountByGuildNameTask>> SetMaximumCurrentMaximumMemberCountByGuildName(
            const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAssumeTask>> Assume(
            const Request::FAssumeRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAssumeByUserIdTask>> AssumeByUserId(
            const Request::FAssumeByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetTask>> IncreaseMaximumCurrentMaximumMemberCountByStampSheet(
            const Request::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskTask>> DecreaseMaximumCurrentMaximumMemberCountByStampTask(
            const Request::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSetMaximumCurrentMaximumMemberCountByStampSheetTask>> SetMaximumCurrentMaximumMemberCountByStampSheet(
            const Request::FSetMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyCurrentMaximumMemberCountByStampTaskTask>> VerifyCurrentMaximumMemberCountByStampTask(
            const Request::FVerifyCurrentMaximumMemberCountByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FVerifyIncludeMemberByStampTaskTask>> VerifyIncludeMemberByStampTask(
            const Request::FVerifyIncludeMemberByStampTaskRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeJoinedGuildsTask>> DescribeJoinedGuilds(
            const Request::FDescribeJoinedGuildsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeJoinedGuildsByUserIdTask>> DescribeJoinedGuildsByUserId(
            const Request::FDescribeJoinedGuildsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJoinedGuildTask>> GetJoinedGuild(
            const Request::FGetJoinedGuildRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetJoinedGuildByUserIdTask>> GetJoinedGuildByUserId(
            const Request::FGetJoinedGuildByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWithdrawalTask>> Withdrawal(
            const Request::FWithdrawalRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWithdrawalByUserIdTask>> WithdrawalByUserId(
            const Request::FWithdrawalByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLastGuildMasterActivityTask>> GetLastGuildMasterActivity(
            const Request::FGetLastGuildMasterActivityRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetLastGuildMasterActivityByGuildNameTask>> GetLastGuildMasterActivityByGuildName(
            const Request::FGetLastGuildMasterActivityByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPromoteSeniorMemberTask>> PromoteSeniorMember(
            const Request::FPromoteSeniorMemberRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FPromoteSeniorMemberByGuildNameTask>> PromoteSeniorMemberByGuildName(
            const Request::FPromoteSeniorMemberByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> ExportMaster(
            const Request::FExportMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentGuildMasterTask>> GetCurrentGuildMaster(
            const Request::FGetCurrentGuildMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentGuildMasterTask>> UpdateCurrentGuildMaster(
            const Request::FUpdateCurrentGuildMasterRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentGuildMasterFromGitHubTask>> UpdateCurrentGuildMasterFromGitHub(
            const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveRequestsTask>> DescribeReceiveRequests(
            const Request::FDescribeReceiveRequestsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveRequestsByGuildNameTask>> DescribeReceiveRequestsByGuildName(
            const Request::FDescribeReceiveRequestsByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveRequestTask>> GetReceiveRequest(
            const Request::FGetReceiveRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveRequestByGuildNameTask>> GetReceiveRequestByGuildName(
            const Request::FGetReceiveRequestByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcceptRequestTask>> AcceptRequest(
            const Request::FAcceptRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcceptRequestByGuildNameTask>> AcceptRequestByGuildName(
            const Request::FAcceptRequestByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRejectRequestTask>> RejectRequest(
            const Request::FRejectRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRejectRequestByGuildNameTask>> RejectRequestByGuildName(
            const Request::FRejectRequestByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSendRequestsTask>> DescribeSendRequests(
            const Request::FDescribeSendRequestsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeSendRequestsByUserIdTask>> DescribeSendRequestsByUserId(
            const Request::FDescribeSendRequestsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSendRequestTask>> GetSendRequest(
            const Request::FGetSendRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetSendRequestByUserIdTask>> GetSendRequestByUserId(
            const Request::FGetSendRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendRequestTask>> SendRequest(
            const Request::FSendRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FSendRequestByUserIdTask>> SendRequestByUserId(
            const Request::FSendRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRequestTask>> DeleteRequest(
            const Request::FDeleteRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRequestByUserIdTask>> DeleteRequestByUserId(
            const Request::FDeleteRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeIgnoreUsersTask>> DescribeIgnoreUsers(
            const Request::FDescribeIgnoreUsersRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeIgnoreUsersByGuildNameTask>> DescribeIgnoreUsersByGuildName(
            const Request::FDescribeIgnoreUsersByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetIgnoreUserTask>> GetIgnoreUser(
            const Request::FGetIgnoreUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetIgnoreUserByGuildNameTask>> GetIgnoreUserByGuildName(
            const Request::FGetIgnoreUserByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddIgnoreUserTask>> AddIgnoreUser(
            const Request::FAddIgnoreUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAddIgnoreUserByGuildNameTask>> AddIgnoreUserByGuildName(
            const Request::FAddIgnoreUserByGuildNameRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteIgnoreUserTask>> DeleteIgnoreUser(
            const Request::FDeleteIgnoreUserRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteIgnoreUserByGuildNameTask>> DeleteIgnoreUserByGuildName(
            const Request::FDeleteIgnoreUserByGuildNameRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2GuildRestClient, ESPMode::ThreadSafe> FGs2GuildRestClientPtr;
}