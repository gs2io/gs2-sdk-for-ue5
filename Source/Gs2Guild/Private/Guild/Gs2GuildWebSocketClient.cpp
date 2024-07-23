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

#include "Guild/Gs2GuildWebSocketClient.h"

namespace Gs2::Guild
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2GuildWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2GuildWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2GuildWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2GuildWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2GuildWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2GuildWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>> FGs2GuildWebSocketClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>> FGs2GuildWebSocketClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>> FGs2GuildWebSocketClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>> FGs2GuildWebSocketClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>> FGs2GuildWebSocketClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>> FGs2GuildWebSocketClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>> FGs2GuildWebSocketClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGuildModelMastersTask>> FGs2GuildWebSocketClient::DescribeGuildModelMasters(
        const Request::FDescribeGuildModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGuildModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGuildModelMasterTask>> FGs2GuildWebSocketClient::CreateGuildModelMaster(
        const Request::FCreateGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildModelMasterTask>> FGs2GuildWebSocketClient::GetGuildModelMaster(
        const Request::FGetGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGuildModelMasterTask>> FGs2GuildWebSocketClient::UpdateGuildModelMaster(
        const Request::FUpdateGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGuildModelMasterTask>> FGs2GuildWebSocketClient::DeleteGuildModelMaster(
        const Request::FDeleteGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeGuildModelsTask>> FGs2GuildWebSocketClient::DescribeGuildModels(
        const Request::FDescribeGuildModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeGuildModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildModelTask>> FGs2GuildWebSocketClient::GetGuildModel(
        const Request::FGetGuildModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGuildModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSearchGuildsTask>> FGs2GuildWebSocketClient::SearchGuilds(
        const Request::FSearchGuildsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSearchGuildsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSearchGuildsByUserIdTask>> FGs2GuildWebSocketClient::SearchGuildsByUserId(
        const Request::FSearchGuildsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSearchGuildsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGuildTask>> FGs2GuildWebSocketClient::CreateGuild(
        const Request::FCreateGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateGuildByUserIdTask>> FGs2GuildWebSocketClient::CreateGuildByUserId(
        const Request::FCreateGuildByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateGuildByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildTask>> FGs2GuildWebSocketClient::GetGuild(
        const Request::FGetGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetGuildByUserIdTask>> FGs2GuildWebSocketClient::GetGuildByUserId(
        const Request::FGetGuildByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetGuildByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGuildTask>> FGs2GuildWebSocketClient::UpdateGuild(
        const Request::FUpdateGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateGuildByGuildNameTask>> FGs2GuildWebSocketClient::UpdateGuildByGuildName(
        const Request::FUpdateGuildByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateGuildByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMemberTask>> FGs2GuildWebSocketClient::DeleteMember(
        const Request::FDeleteMemberRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteMemberTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteMemberByGuildNameTask>> FGs2GuildWebSocketClient::DeleteMemberByGuildName(
        const Request::FDeleteMemberByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteMemberByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMemberRoleTask>> FGs2GuildWebSocketClient::UpdateMemberRole(
        const Request::FUpdateMemberRoleRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateMemberRoleTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateMemberRoleByGuildNameTask>> FGs2GuildWebSocketClient::UpdateMemberRoleByGuildName(
        const Request::FUpdateMemberRoleByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateMemberRoleByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGuildTask>> FGs2GuildWebSocketClient::DeleteGuild(
        const Request::FDeleteGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteGuildByGuildNameTask>> FGs2GuildWebSocketClient::DeleteGuildByGuildName(
        const Request::FDeleteGuildByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteGuildByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildWebSocketClient::IncreaseMaximumCurrentMaximumMemberCountByGuildName(
        const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildWebSocketClient::DecreaseMaximumCurrentMaximumMemberCountByGuildName(
        const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountTask>> FGs2GuildWebSocketClient::VerifyCurrentMaximumMemberCount(
        const Request::FVerifyCurrentMaximumMemberCountRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildWebSocketClient::VerifyCurrentMaximumMemberCountByGuildName(
        const Request::FVerifyCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberTask>> FGs2GuildWebSocketClient::VerifyIncludeMember(
        const Request::FVerifyIncludeMemberRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberByUserIdTask>> FGs2GuildWebSocketClient::VerifyIncludeMemberByUserId(
        const Request::FVerifyIncludeMemberByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaximumCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildWebSocketClient::SetMaximumCurrentMaximumMemberCountByGuildName(
        const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetMaximumCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAssumeTask>> FGs2GuildWebSocketClient::Assume(
        const Request::FAssumeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAssumeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAssumeByUserIdTask>> FGs2GuildWebSocketClient::AssumeByUserId(
        const Request::FAssumeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAssumeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetTask>> FGs2GuildWebSocketClient::IncreaseMaximumCurrentMaximumMemberCountByStampSheet(
        const Request::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskTask>> FGs2GuildWebSocketClient::DecreaseMaximumCurrentMaximumMemberCountByStampTask(
        const Request::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSetMaximumCurrentMaximumMemberCountByStampSheetTask>> FGs2GuildWebSocketClient::SetMaximumCurrentMaximumMemberCountByStampSheet(
        const Request::FSetMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSetMaximumCurrentMaximumMemberCountByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountByStampTaskTask>> FGs2GuildWebSocketClient::VerifyCurrentMaximumMemberCountByStampTask(
        const Request::FVerifyCurrentMaximumMemberCountByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyCurrentMaximumMemberCountByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberByStampTaskTask>> FGs2GuildWebSocketClient::VerifyIncludeMemberByStampTask(
        const Request::FVerifyIncludeMemberByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FVerifyIncludeMemberByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedGuildsTask>> FGs2GuildWebSocketClient::DescribeJoinedGuilds(
        const Request::FDescribeJoinedGuildsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeJoinedGuildsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeJoinedGuildsByUserIdTask>> FGs2GuildWebSocketClient::DescribeJoinedGuildsByUserId(
        const Request::FDescribeJoinedGuildsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeJoinedGuildsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedGuildTask>> FGs2GuildWebSocketClient::GetJoinedGuild(
        const Request::FGetJoinedGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetJoinedGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetJoinedGuildByUserIdTask>> FGs2GuildWebSocketClient::GetJoinedGuildByUserId(
        const Request::FGetJoinedGuildByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetJoinedGuildByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawalTask>> FGs2GuildWebSocketClient::Withdrawal(
        const Request::FWithdrawalRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FWithdrawalTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FWithdrawalByUserIdTask>> FGs2GuildWebSocketClient::WithdrawalByUserId(
        const Request::FWithdrawalByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FWithdrawalByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FExportMasterTask>> FGs2GuildWebSocketClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetCurrentGuildMasterTask>> FGs2GuildWebSocketClient::GetCurrentGuildMaster(
        const Request::FGetCurrentGuildMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetCurrentGuildMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentGuildMasterTask>> FGs2GuildWebSocketClient::UpdateCurrentGuildMaster(
        const Request::FUpdateCurrentGuildMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentGuildMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentGuildMasterFromGitHubTask>> FGs2GuildWebSocketClient::UpdateCurrentGuildMasterFromGitHub(
        const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentGuildMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsTask>> FGs2GuildWebSocketClient::DescribeReceiveRequests(
        const Request::FDescribeReceiveRequestsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsByGuildNameTask>> FGs2GuildWebSocketClient::DescribeReceiveRequestsByGuildName(
        const Request::FDescribeReceiveRequestsByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveRequestTask>> FGs2GuildWebSocketClient::GetReceiveRequest(
        const Request::FGetReceiveRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetReceiveRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveRequestByGuildNameTask>> FGs2GuildWebSocketClient::GetReceiveRequestByGuildName(
        const Request::FGetReceiveRequestByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetReceiveRequestByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptRequestTask>> FGs2GuildWebSocketClient::AcceptRequest(
        const Request::FAcceptRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcceptRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptRequestByGuildNameTask>> FGs2GuildWebSocketClient::AcceptRequestByGuildName(
        const Request::FAcceptRequestByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAcceptRequestByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRejectRequestTask>> FGs2GuildWebSocketClient::RejectRequest(
        const Request::FRejectRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRejectRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FRejectRequestByGuildNameTask>> FGs2GuildWebSocketClient::RejectRequestByGuildName(
        const Request::FRejectRequestByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FRejectRequestByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSendRequestsTask>> FGs2GuildWebSocketClient::DescribeSendRequests(
        const Request::FDescribeSendRequestsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSendRequestsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeSendRequestsByUserIdTask>> FGs2GuildWebSocketClient::DescribeSendRequestsByUserId(
        const Request::FDescribeSendRequestsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeSendRequestsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSendRequestTask>> FGs2GuildWebSocketClient::GetSendRequest(
        const Request::FGetSendRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSendRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetSendRequestByUserIdTask>> FGs2GuildWebSocketClient::GetSendRequestByUserId(
        const Request::FGetSendRequestByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetSendRequestByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSendRequestTask>> FGs2GuildWebSocketClient::SendRequest(
        const Request::FSendRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSendRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FSendRequestByUserIdTask>> FGs2GuildWebSocketClient::SendRequestByUserId(
        const Request::FSendRequestByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FSendRequestByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRequestTask>> FGs2GuildWebSocketClient::DeleteRequest(
        const Request::FDeleteRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteRequestByUserIdTask>> FGs2GuildWebSocketClient::DeleteRequestByUserId(
        const Request::FDeleteRequestByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteRequestByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIgnoreUsersTask>> FGs2GuildWebSocketClient::DescribeIgnoreUsers(
        const Request::FDescribeIgnoreUsersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeIgnoreUsersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeIgnoreUsersByGuildNameTask>> FGs2GuildWebSocketClient::DescribeIgnoreUsersByGuildName(
        const Request::FDescribeIgnoreUsersByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeIgnoreUsersByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetIgnoreUserTask>> FGs2GuildWebSocketClient::GetIgnoreUser(
        const Request::FGetIgnoreUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetIgnoreUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetIgnoreUserByGuildNameTask>> FGs2GuildWebSocketClient::GetIgnoreUserByGuildName(
        const Request::FGetIgnoreUserByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetIgnoreUserByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddIgnoreUserTask>> FGs2GuildWebSocketClient::AddIgnoreUser(
        const Request::FAddIgnoreUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddIgnoreUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FAddIgnoreUserByGuildNameTask>> FGs2GuildWebSocketClient::AddIgnoreUserByGuildName(
        const Request::FAddIgnoreUserByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FAddIgnoreUserByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteIgnoreUserTask>> FGs2GuildWebSocketClient::DeleteIgnoreUser(
        const Request::FDeleteIgnoreUserRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteIgnoreUserTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteIgnoreUserByGuildNameTask>> FGs2GuildWebSocketClient::DeleteIgnoreUserByGuildName(
        const Request::FDeleteIgnoreUserByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteIgnoreUserByGuildNameTask>>(
            Session,
            Request
        );
    }
}