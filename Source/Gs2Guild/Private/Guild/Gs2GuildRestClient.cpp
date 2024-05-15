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

#include "Guild/Gs2GuildRestClient.h"

namespace Gs2::Guild
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2GuildRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2GuildRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2GuildRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2GuildRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2GuildRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2GuildRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>> FGs2GuildRestClient::DumpUserDataByUserId(
        const Request::FDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>> FGs2GuildRestClient::CheckDumpUserDataByUserId(
        const Request::FCheckDumpUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckDumpUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>> FGs2GuildRestClient::CleanUserDataByUserId(
        const Request::FCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>> FGs2GuildRestClient::CheckCleanUserDataByUserId(
        const Request::FCheckCleanUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckCleanUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>> FGs2GuildRestClient::PrepareImportUserDataByUserId(
        const Request::FPrepareImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FPrepareImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>> FGs2GuildRestClient::ImportUserDataByUserId(
        const Request::FImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>> FGs2GuildRestClient::CheckImportUserDataByUserId(
        const Request::FCheckImportUserDataByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCheckImportUserDataByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGuildModelMastersTask>> FGs2GuildRestClient::DescribeGuildModelMasters(
        const Request::FDescribeGuildModelMastersRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGuildModelMastersTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGuildModelMasterTask>> FGs2GuildRestClient::CreateGuildModelMaster(
        const Request::FCreateGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGuildModelMasterTask>> FGs2GuildRestClient::GetGuildModelMaster(
        const Request::FGetGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateGuildModelMasterTask>> FGs2GuildRestClient::UpdateGuildModelMaster(
        const Request::FUpdateGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGuildModelMasterTask>> FGs2GuildRestClient::DeleteGuildModelMaster(
        const Request::FDeleteGuildModelMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGuildModelMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeGuildModelsTask>> FGs2GuildRestClient::DescribeGuildModels(
        const Request::FDescribeGuildModelsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeGuildModelsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGuildModelTask>> FGs2GuildRestClient::GetGuildModel(
        const Request::FGetGuildModelRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGuildModelTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSearchGuildsTask>> FGs2GuildRestClient::SearchGuilds(
        const Request::FSearchGuildsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSearchGuildsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSearchGuildsByUserIdTask>> FGs2GuildRestClient::SearchGuildsByUserId(
        const Request::FSearchGuildsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSearchGuildsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGuildTask>> FGs2GuildRestClient::CreateGuild(
        const Request::FCreateGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateGuildByUserIdTask>> FGs2GuildRestClient::CreateGuildByUserId(
        const Request::FCreateGuildByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateGuildByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGuildTask>> FGs2GuildRestClient::GetGuild(
        const Request::FGetGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetGuildByUserIdTask>> FGs2GuildRestClient::GetGuildByUserId(
        const Request::FGetGuildByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetGuildByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateGuildTask>> FGs2GuildRestClient::UpdateGuild(
        const Request::FUpdateGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateGuildByGuildNameTask>> FGs2GuildRestClient::UpdateGuildByGuildName(
        const Request::FUpdateGuildByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateGuildByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteMemberTask>> FGs2GuildRestClient::DeleteMember(
        const Request::FDeleteMemberRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteMemberTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteMemberByGuildNameTask>> FGs2GuildRestClient::DeleteMemberByGuildName(
        const Request::FDeleteMemberByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteMemberByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateMemberRoleTask>> FGs2GuildRestClient::UpdateMemberRole(
        const Request::FUpdateMemberRoleRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateMemberRoleTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateMemberRoleByGuildNameTask>> FGs2GuildRestClient::UpdateMemberRoleByGuildName(
        const Request::FUpdateMemberRoleByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateMemberRoleByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGuildTask>> FGs2GuildRestClient::DeleteGuild(
        const Request::FDeleteGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteGuildByGuildNameTask>> FGs2GuildRestClient::DeleteGuildByGuildName(
        const Request::FDeleteGuildByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteGuildByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildRestClient::IncreaseMaximumCurrentMaximumMemberCountByGuildName(
        const Request::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIncreaseMaximumCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildRestClient::DecreaseMaximumCurrentMaximumMemberCountByGuildName(
        const Request::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDecreaseMaximumCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetMaximumCurrentMaximumMemberCountByGuildNameTask>> FGs2GuildRestClient::SetMaximumCurrentMaximumMemberCountByGuildName(
        const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetMaximumCurrentMaximumMemberCountByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAssumeTask>> FGs2GuildRestClient::Assume(
        const Request::FAssumeRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAssumeTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAssumeByUserIdTask>> FGs2GuildRestClient::AssumeByUserId(
        const Request::FAssumeByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAssumeByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetTask>> FGs2GuildRestClient::IncreaseMaximumCurrentMaximumMemberCountByStampSheet(
        const Request::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FIncreaseMaximumCurrentMaximumMemberCountByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskTask>> FGs2GuildRestClient::DecreaseMaximumCurrentMaximumMemberCountByStampTask(
        const Request::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDecreaseMaximumCurrentMaximumMemberCountByStampTaskTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSetMaximumCurrentMaximumMemberCountByStampSheetTask>> FGs2GuildRestClient::SetMaximumCurrentMaximumMemberCountByStampSheet(
        const Request::FSetMaximumCurrentMaximumMemberCountByStampSheetRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSetMaximumCurrentMaximumMemberCountByStampSheetTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeJoinedGuildsTask>> FGs2GuildRestClient::DescribeJoinedGuilds(
        const Request::FDescribeJoinedGuildsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeJoinedGuildsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeJoinedGuildsByUserIdTask>> FGs2GuildRestClient::DescribeJoinedGuildsByUserId(
        const Request::FDescribeJoinedGuildsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeJoinedGuildsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetJoinedGuildTask>> FGs2GuildRestClient::GetJoinedGuild(
        const Request::FGetJoinedGuildRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetJoinedGuildTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetJoinedGuildByUserIdTask>> FGs2GuildRestClient::GetJoinedGuildByUserId(
        const Request::FGetJoinedGuildByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetJoinedGuildByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FWithdrawalTask>> FGs2GuildRestClient::Withdrawal(
        const Request::FWithdrawalRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FWithdrawalTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FWithdrawalByUserIdTask>> FGs2GuildRestClient::WithdrawalByUserId(
        const Request::FWithdrawalByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FWithdrawalByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FExportMasterTask>> FGs2GuildRestClient::ExportMaster(
        const Request::FExportMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FExportMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetCurrentGuildMasterTask>> FGs2GuildRestClient::GetCurrentGuildMaster(
        const Request::FGetCurrentGuildMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetCurrentGuildMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentGuildMasterTask>> FGs2GuildRestClient::UpdateCurrentGuildMaster(
        const Request::FUpdateCurrentGuildMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentGuildMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateCurrentGuildMasterFromGitHubTask>> FGs2GuildRestClient::UpdateCurrentGuildMasterFromGitHub(
        const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateCurrentGuildMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveRequestsTask>> FGs2GuildRestClient::DescribeReceiveRequests(
        const Request::FDescribeReceiveRequestsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeReceiveRequestsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveRequestsByGuildNameTask>> FGs2GuildRestClient::DescribeReceiveRequestsByGuildName(
        const Request::FDescribeReceiveRequestsByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeReceiveRequestsByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveRequestTask>> FGs2GuildRestClient::GetReceiveRequest(
        const Request::FGetReceiveRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetReceiveRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveRequestByGuildNameTask>> FGs2GuildRestClient::GetReceiveRequestByGuildName(
        const Request::FGetReceiveRequestByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetReceiveRequestByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcceptRequestTask>> FGs2GuildRestClient::AcceptRequest(
        const Request::FAcceptRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcceptRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FAcceptRequestByGuildNameTask>> FGs2GuildRestClient::AcceptRequestByGuildName(
        const Request::FAcceptRequestByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FAcceptRequestByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRejectRequestTask>> FGs2GuildRestClient::RejectRequest(
        const Request::FRejectRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRejectRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FRejectRequestByGuildNameTask>> FGs2GuildRestClient::RejectRequestByGuildName(
        const Request::FRejectRequestByGuildNameRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FRejectRequestByGuildNameTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSendRequestsTask>> FGs2GuildRestClient::DescribeSendRequests(
        const Request::FDescribeSendRequestsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSendRequestsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeSendRequestsByUserIdTask>> FGs2GuildRestClient::DescribeSendRequestsByUserId(
        const Request::FDescribeSendRequestsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeSendRequestsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSendRequestTask>> FGs2GuildRestClient::GetSendRequest(
        const Request::FGetSendRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSendRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetSendRequestByUserIdTask>> FGs2GuildRestClient::GetSendRequestByUserId(
        const Request::FGetSendRequestByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetSendRequestByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSendRequestTask>> FGs2GuildRestClient::SendRequest(
        const Request::FSendRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSendRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FSendRequestByUserIdTask>> FGs2GuildRestClient::SendRequestByUserId(
        const Request::FSendRequestByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FSendRequestByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRequestTask>> FGs2GuildRestClient::DeleteRequest(
        const Request::FDeleteRequestRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRequestTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRequestByUserIdTask>> FGs2GuildRestClient::DeleteRequestByUserId(
        const Request::FDeleteRequestByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRequestByUserIdTask>>(
            Session,
            Request
        );
    }
}