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

// Model
#include "Model/Namespace.h"
#include "Model/GuildModelMaster.h"
#include "Model/GuildModel.h"
#include "Model/Inbox.h"
#include "Model/SendBox.h"
#include "Model/Guild.h"
#include "Model/JoinedGuild.h"
#include "Model/CurrentGuildMaster.h"
#include "Model/RoleModel.h"
#include "Model/Member.h"
#include "Model/ReceiveMemberRequest.h"
#include "Model/SendMemberRequest.h"
#include "Model/TransactionSetting.h"
#include "Model/NotificationSetting.h"
#include "Model/ScriptSetting.h"
#include "Model/LogSetting.h"
#include "Model/GitHubCheckoutSetting.h"

// DescribeNamespaces
#include "Request/DescribeNamespacesRequest.h"
#include "Result/DescribeNamespacesResult.h"
#include "Task/Rest/DescribeNamespacesTask.h"
#include "Task/WebSocket/DescribeNamespacesTask.h"

// CreateNamespace
#include "Request/CreateNamespaceRequest.h"
#include "Result/CreateNamespaceResult.h"
#include "Task/Rest/CreateNamespaceTask.h"
#include "Task/WebSocket/CreateNamespaceTask.h"

// GetNamespaceStatus
#include "Request/GetNamespaceStatusRequest.h"
#include "Result/GetNamespaceStatusResult.h"
#include "Task/Rest/GetNamespaceStatusTask.h"
#include "Task/WebSocket/GetNamespaceStatusTask.h"

// GetNamespace
#include "Request/GetNamespaceRequest.h"
#include "Result/GetNamespaceResult.h"
#include "Task/Rest/GetNamespaceTask.h"
#include "Task/WebSocket/GetNamespaceTask.h"

// UpdateNamespace
#include "Request/UpdateNamespaceRequest.h"
#include "Result/UpdateNamespaceResult.h"
#include "Task/Rest/UpdateNamespaceTask.h"
#include "Task/WebSocket/UpdateNamespaceTask.h"

// DeleteNamespace
#include "Request/DeleteNamespaceRequest.h"
#include "Result/DeleteNamespaceResult.h"
#include "Task/Rest/DeleteNamespaceTask.h"
#include "Task/WebSocket/DeleteNamespaceTask.h"

// DumpUserDataByUserId
#include "Request/DumpUserDataByUserIdRequest.h"
#include "Result/DumpUserDataByUserIdResult.h"
#include "Task/Rest/DumpUserDataByUserIdTask.h"
#include "Task/WebSocket/DumpUserDataByUserIdTask.h"

// CheckDumpUserDataByUserId
#include "Request/CheckDumpUserDataByUserIdRequest.h"
#include "Result/CheckDumpUserDataByUserIdResult.h"
#include "Task/Rest/CheckDumpUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckDumpUserDataByUserIdTask.h"

// CleanUserDataByUserId
#include "Request/CleanUserDataByUserIdRequest.h"
#include "Result/CleanUserDataByUserIdResult.h"
#include "Task/Rest/CleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CleanUserDataByUserIdTask.h"

// CheckCleanUserDataByUserId
#include "Request/CheckCleanUserDataByUserIdRequest.h"
#include "Result/CheckCleanUserDataByUserIdResult.h"
#include "Task/Rest/CheckCleanUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckCleanUserDataByUserIdTask.h"

// PrepareImportUserDataByUserId
#include "Request/PrepareImportUserDataByUserIdRequest.h"
#include "Result/PrepareImportUserDataByUserIdResult.h"
#include "Task/Rest/PrepareImportUserDataByUserIdTask.h"
#include "Task/WebSocket/PrepareImportUserDataByUserIdTask.h"

// ImportUserDataByUserId
#include "Request/ImportUserDataByUserIdRequest.h"
#include "Result/ImportUserDataByUserIdResult.h"
#include "Task/Rest/ImportUserDataByUserIdTask.h"
#include "Task/WebSocket/ImportUserDataByUserIdTask.h"

// CheckImportUserDataByUserId
#include "Request/CheckImportUserDataByUserIdRequest.h"
#include "Result/CheckImportUserDataByUserIdResult.h"
#include "Task/Rest/CheckImportUserDataByUserIdTask.h"
#include "Task/WebSocket/CheckImportUserDataByUserIdTask.h"

// DescribeGuildModelMasters
#include "Request/DescribeGuildModelMastersRequest.h"
#include "Result/DescribeGuildModelMastersResult.h"
#include "Task/Rest/DescribeGuildModelMastersTask.h"
#include "Task/WebSocket/DescribeGuildModelMastersTask.h"

// CreateGuildModelMaster
#include "Request/CreateGuildModelMasterRequest.h"
#include "Result/CreateGuildModelMasterResult.h"
#include "Task/Rest/CreateGuildModelMasterTask.h"
#include "Task/WebSocket/CreateGuildModelMasterTask.h"

// GetGuildModelMaster
#include "Request/GetGuildModelMasterRequest.h"
#include "Result/GetGuildModelMasterResult.h"
#include "Task/Rest/GetGuildModelMasterTask.h"
#include "Task/WebSocket/GetGuildModelMasterTask.h"

// UpdateGuildModelMaster
#include "Request/UpdateGuildModelMasterRequest.h"
#include "Result/UpdateGuildModelMasterResult.h"
#include "Task/Rest/UpdateGuildModelMasterTask.h"
#include "Task/WebSocket/UpdateGuildModelMasterTask.h"

// DeleteGuildModelMaster
#include "Request/DeleteGuildModelMasterRequest.h"
#include "Result/DeleteGuildModelMasterResult.h"
#include "Task/Rest/DeleteGuildModelMasterTask.h"
#include "Task/WebSocket/DeleteGuildModelMasterTask.h"

// DescribeGuildModels
#include "Request/DescribeGuildModelsRequest.h"
#include "Result/DescribeGuildModelsResult.h"
#include "Task/Rest/DescribeGuildModelsTask.h"
#include "Task/WebSocket/DescribeGuildModelsTask.h"

// GetGuildModel
#include "Request/GetGuildModelRequest.h"
#include "Result/GetGuildModelResult.h"
#include "Task/Rest/GetGuildModelTask.h"
#include "Task/WebSocket/GetGuildModelTask.h"

// SearchGuilds
#include "Request/SearchGuildsRequest.h"
#include "Result/SearchGuildsResult.h"
#include "Task/Rest/SearchGuildsTask.h"
#include "Task/WebSocket/SearchGuildsTask.h"

// SearchGuildsByUserId
#include "Request/SearchGuildsByUserIdRequest.h"
#include "Result/SearchGuildsByUserIdResult.h"
#include "Task/Rest/SearchGuildsByUserIdTask.h"
#include "Task/WebSocket/SearchGuildsByUserIdTask.h"

// CreateGuild
#include "Request/CreateGuildRequest.h"
#include "Result/CreateGuildResult.h"
#include "Task/Rest/CreateGuildTask.h"
#include "Task/WebSocket/CreateGuildTask.h"

// CreateGuildByUserId
#include "Request/CreateGuildByUserIdRequest.h"
#include "Result/CreateGuildByUserIdResult.h"
#include "Task/Rest/CreateGuildByUserIdTask.h"
#include "Task/WebSocket/CreateGuildByUserIdTask.h"

// GetGuild
#include "Request/GetGuildRequest.h"
#include "Result/GetGuildResult.h"
#include "Task/Rest/GetGuildTask.h"
#include "Task/WebSocket/GetGuildTask.h"

// GetGuildByUserId
#include "Request/GetGuildByUserIdRequest.h"
#include "Result/GetGuildByUserIdResult.h"
#include "Task/Rest/GetGuildByUserIdTask.h"
#include "Task/WebSocket/GetGuildByUserIdTask.h"

// UpdateGuild
#include "Request/UpdateGuildRequest.h"
#include "Result/UpdateGuildResult.h"
#include "Task/Rest/UpdateGuildTask.h"
#include "Task/WebSocket/UpdateGuildTask.h"

// UpdateGuildByGuildName
#include "Request/UpdateGuildByGuildNameRequest.h"
#include "Result/UpdateGuildByGuildNameResult.h"
#include "Task/Rest/UpdateGuildByGuildNameTask.h"
#include "Task/WebSocket/UpdateGuildByGuildNameTask.h"

// DeleteMember
#include "Request/DeleteMemberRequest.h"
#include "Result/DeleteMemberResult.h"
#include "Task/Rest/DeleteMemberTask.h"
#include "Task/WebSocket/DeleteMemberTask.h"

// DeleteMemberByGuildName
#include "Request/DeleteMemberByGuildNameRequest.h"
#include "Result/DeleteMemberByGuildNameResult.h"
#include "Task/Rest/DeleteMemberByGuildNameTask.h"
#include "Task/WebSocket/DeleteMemberByGuildNameTask.h"

// UpdateMemberRole
#include "Request/UpdateMemberRoleRequest.h"
#include "Result/UpdateMemberRoleResult.h"
#include "Task/Rest/UpdateMemberRoleTask.h"
#include "Task/WebSocket/UpdateMemberRoleTask.h"

// UpdateMemberRoleByGuildName
#include "Request/UpdateMemberRoleByGuildNameRequest.h"
#include "Result/UpdateMemberRoleByGuildNameResult.h"
#include "Task/Rest/UpdateMemberRoleByGuildNameTask.h"
#include "Task/WebSocket/UpdateMemberRoleByGuildNameTask.h"

// DeleteGuild
#include "Request/DeleteGuildRequest.h"
#include "Result/DeleteGuildResult.h"
#include "Task/Rest/DeleteGuildTask.h"
#include "Task/WebSocket/DeleteGuildTask.h"

// DeleteGuildByGuildName
#include "Request/DeleteGuildByGuildNameRequest.h"
#include "Result/DeleteGuildByGuildNameResult.h"
#include "Task/Rest/DeleteGuildByGuildNameTask.h"
#include "Task/WebSocket/DeleteGuildByGuildNameTask.h"

// IncreaseMaximumCurrentMaximumMemberCountByGuildName
#include "Request/IncreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Result/IncreaseMaximumCurrentMaximumMemberCountByGuildNameResult.h"
#include "Task/Rest/IncreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Task/WebSocket/IncreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"

// DecreaseMaximumCurrentMaximumMemberCountByGuildName
#include "Request/DecreaseMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Result/DecreaseMaximumCurrentMaximumMemberCountByGuildNameResult.h"
#include "Task/Rest/DecreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Task/WebSocket/DecreaseMaximumCurrentMaximumMemberCountByGuildNameTask.h"

// SetMaximumCurrentMaximumMemberCountByGuildName
#include "Request/SetMaximumCurrentMaximumMemberCountByGuildNameRequest.h"
#include "Result/SetMaximumCurrentMaximumMemberCountByGuildNameResult.h"
#include "Task/Rest/SetMaximumCurrentMaximumMemberCountByGuildNameTask.h"
#include "Task/WebSocket/SetMaximumCurrentMaximumMemberCountByGuildNameTask.h"

// Assume
#include "Request/AssumeRequest.h"
#include "Result/AssumeResult.h"
#include "Task/Rest/AssumeTask.h"
#include "Task/WebSocket/AssumeTask.h"

// AssumeByUserId
#include "Request/AssumeByUserIdRequest.h"
#include "Result/AssumeByUserIdResult.h"
#include "Task/Rest/AssumeByUserIdTask.h"
#include "Task/WebSocket/AssumeByUserIdTask.h"

// IncreaseMaximumCurrentMaximumMemberCountByStampSheet
#include "Request/IncreaseMaximumCurrentMaximumMemberCountByStampSheetRequest.h"
#include "Result/IncreaseMaximumCurrentMaximumMemberCountByStampSheetResult.h"
#include "Task/Rest/IncreaseMaximumCurrentMaximumMemberCountByStampSheetTask.h"
#include "Task/WebSocket/IncreaseMaximumCurrentMaximumMemberCountByStampSheetTask.h"

// DecreaseMaximumCurrentMaximumMemberCountByStampTask
#include "Request/DecreaseMaximumCurrentMaximumMemberCountByStampTaskRequest.h"
#include "Result/DecreaseMaximumCurrentMaximumMemberCountByStampTaskResult.h"
#include "Task/Rest/DecreaseMaximumCurrentMaximumMemberCountByStampTaskTask.h"
#include "Task/WebSocket/DecreaseMaximumCurrentMaximumMemberCountByStampTaskTask.h"

// SetMaximumCurrentMaximumMemberCountByStampSheet
#include "Request/SetMaximumCurrentMaximumMemberCountByStampSheetRequest.h"
#include "Result/SetMaximumCurrentMaximumMemberCountByStampSheetResult.h"
#include "Task/Rest/SetMaximumCurrentMaximumMemberCountByStampSheetTask.h"
#include "Task/WebSocket/SetMaximumCurrentMaximumMemberCountByStampSheetTask.h"

// DescribeJoinedGuilds
#include "Request/DescribeJoinedGuildsRequest.h"
#include "Result/DescribeJoinedGuildsResult.h"
#include "Task/Rest/DescribeJoinedGuildsTask.h"
#include "Task/WebSocket/DescribeJoinedGuildsTask.h"

// DescribeJoinedGuildsByUserId
#include "Request/DescribeJoinedGuildsByUserIdRequest.h"
#include "Result/DescribeJoinedGuildsByUserIdResult.h"
#include "Task/Rest/DescribeJoinedGuildsByUserIdTask.h"
#include "Task/WebSocket/DescribeJoinedGuildsByUserIdTask.h"

// GetJoinedGuild
#include "Request/GetJoinedGuildRequest.h"
#include "Result/GetJoinedGuildResult.h"
#include "Task/Rest/GetJoinedGuildTask.h"
#include "Task/WebSocket/GetJoinedGuildTask.h"

// GetJoinedGuildByUserId
#include "Request/GetJoinedGuildByUserIdRequest.h"
#include "Result/GetJoinedGuildByUserIdResult.h"
#include "Task/Rest/GetJoinedGuildByUserIdTask.h"
#include "Task/WebSocket/GetJoinedGuildByUserIdTask.h"

// Withdrawal
#include "Request/WithdrawalRequest.h"
#include "Result/WithdrawalResult.h"
#include "Task/Rest/WithdrawalTask.h"
#include "Task/WebSocket/WithdrawalTask.h"

// WithdrawalByUserId
#include "Request/WithdrawalByUserIdRequest.h"
#include "Result/WithdrawalByUserIdResult.h"
#include "Task/Rest/WithdrawalByUserIdTask.h"
#include "Task/WebSocket/WithdrawalByUserIdTask.h"

// ExportMaster
#include "Request/ExportMasterRequest.h"
#include "Result/ExportMasterResult.h"
#include "Task/Rest/ExportMasterTask.h"
#include "Task/WebSocket/ExportMasterTask.h"

// GetCurrentGuildMaster
#include "Request/GetCurrentGuildMasterRequest.h"
#include "Result/GetCurrentGuildMasterResult.h"
#include "Task/Rest/GetCurrentGuildMasterTask.h"
#include "Task/WebSocket/GetCurrentGuildMasterTask.h"

// UpdateCurrentGuildMaster
#include "Request/UpdateCurrentGuildMasterRequest.h"
#include "Result/UpdateCurrentGuildMasterResult.h"
#include "Task/Rest/UpdateCurrentGuildMasterTask.h"
#include "Task/WebSocket/UpdateCurrentGuildMasterTask.h"

// UpdateCurrentGuildMasterFromGitHub
#include "Request/UpdateCurrentGuildMasterFromGitHubRequest.h"
#include "Result/UpdateCurrentGuildMasterFromGitHubResult.h"
#include "Task/Rest/UpdateCurrentGuildMasterFromGitHubTask.h"
#include "Task/WebSocket/UpdateCurrentGuildMasterFromGitHubTask.h"

// DescribeReceiveRequests
#include "Request/DescribeReceiveRequestsRequest.h"
#include "Result/DescribeReceiveRequestsResult.h"
#include "Task/Rest/DescribeReceiveRequestsTask.h"
#include "Task/WebSocket/DescribeReceiveRequestsTask.h"

// DescribeReceiveRequestsByGuildName
#include "Request/DescribeReceiveRequestsByGuildNameRequest.h"
#include "Result/DescribeReceiveRequestsByGuildNameResult.h"
#include "Task/Rest/DescribeReceiveRequestsByGuildNameTask.h"
#include "Task/WebSocket/DescribeReceiveRequestsByGuildNameTask.h"

// GetReceiveRequest
#include "Request/GetReceiveRequestRequest.h"
#include "Result/GetReceiveRequestResult.h"
#include "Task/Rest/GetReceiveRequestTask.h"
#include "Task/WebSocket/GetReceiveRequestTask.h"

// GetReceiveRequestByGuildName
#include "Request/GetReceiveRequestByGuildNameRequest.h"
#include "Result/GetReceiveRequestByGuildNameResult.h"
#include "Task/Rest/GetReceiveRequestByGuildNameTask.h"
#include "Task/WebSocket/GetReceiveRequestByGuildNameTask.h"

// AcceptRequest
#include "Request/AcceptRequestRequest.h"
#include "Result/AcceptRequestResult.h"
#include "Task/Rest/AcceptRequestTask.h"
#include "Task/WebSocket/AcceptRequestTask.h"

// AcceptRequestByGuildName
#include "Request/AcceptRequestByGuildNameRequest.h"
#include "Result/AcceptRequestByGuildNameResult.h"
#include "Task/Rest/AcceptRequestByGuildNameTask.h"
#include "Task/WebSocket/AcceptRequestByGuildNameTask.h"

// RejectRequest
#include "Request/RejectRequestRequest.h"
#include "Result/RejectRequestResult.h"
#include "Task/Rest/RejectRequestTask.h"
#include "Task/WebSocket/RejectRequestTask.h"

// RejectRequestByGuildName
#include "Request/RejectRequestByGuildNameRequest.h"
#include "Result/RejectRequestByGuildNameResult.h"
#include "Task/Rest/RejectRequestByGuildNameTask.h"
#include "Task/WebSocket/RejectRequestByGuildNameTask.h"

// DescribeSendRequests
#include "Request/DescribeSendRequestsRequest.h"
#include "Result/DescribeSendRequestsResult.h"
#include "Task/Rest/DescribeSendRequestsTask.h"
#include "Task/WebSocket/DescribeSendRequestsTask.h"

// DescribeSendRequestsByUserId
#include "Request/DescribeSendRequestsByUserIdRequest.h"
#include "Result/DescribeSendRequestsByUserIdResult.h"
#include "Task/Rest/DescribeSendRequestsByUserIdTask.h"
#include "Task/WebSocket/DescribeSendRequestsByUserIdTask.h"

// GetSendRequest
#include "Request/GetSendRequestRequest.h"
#include "Result/GetSendRequestResult.h"
#include "Task/Rest/GetSendRequestTask.h"
#include "Task/WebSocket/GetSendRequestTask.h"

// GetSendRequestByUserId
#include "Request/GetSendRequestByUserIdRequest.h"
#include "Result/GetSendRequestByUserIdResult.h"
#include "Task/Rest/GetSendRequestByUserIdTask.h"
#include "Task/WebSocket/GetSendRequestByUserIdTask.h"

// SendRequest
#include "Request/SendRequestRequest.h"
#include "Result/SendRequestResult.h"
#include "Task/Rest/SendRequestTask.h"
#include "Task/WebSocket/SendRequestTask.h"

// SendRequestByUserId
#include "Request/SendRequestByUserIdRequest.h"
#include "Result/SendRequestByUserIdResult.h"
#include "Task/Rest/SendRequestByUserIdTask.h"
#include "Task/WebSocket/SendRequestByUserIdTask.h"

// DeleteRequest
#include "Request/DeleteRequestRequest.h"
#include "Result/DeleteRequestResult.h"
#include "Task/Rest/DeleteRequestTask.h"
#include "Task/WebSocket/DeleteRequestTask.h"

// DeleteRequestByUserId
#include "Request/DeleteRequestByUserIdRequest.h"
#include "Result/DeleteRequestByUserIdResult.h"
#include "Task/Rest/DeleteRequestByUserIdTask.h"
#include "Task/WebSocket/DeleteRequestByUserIdTask.h"

// Client
#include "Gs2GuildRestClient.h"
#include "Gs2GuildWebSocketClient.h"