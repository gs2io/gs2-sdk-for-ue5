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
#include "Model/Profile.h"
#include "Model/Follow.h"
#include "Model/Friend.h"
#include "Model/SendBox.h"
#include "Model/Inbox.h"
#include "Model/BlackList.h"
#include "Model/FollowUser.h"
#include "Model/FriendUser.h"
#include "Model/FriendRequest.h"
#include "Model/SendFriendRequest.h"
#include "Model/ReceiveFriendRequest.h"
#include "Model/PublicProfile.h"
#include "Model/ScriptSetting.h"
#include "Model/NotificationSetting.h"
#include "Model/LogSetting.h"

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

// GetServiceVersion
#include "Request/GetServiceVersionRequest.h"
#include "Result/GetServiceVersionResult.h"
#include "Task/Rest/GetServiceVersionTask.h"
#include "Task/WebSocket/GetServiceVersionTask.h"

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

// GetProfile
#include "Request/GetProfileRequest.h"
#include "Result/GetProfileResult.h"
#include "Task/Rest/GetProfileTask.h"
#include "Task/WebSocket/GetProfileTask.h"

// GetProfileByUserId
#include "Request/GetProfileByUserIdRequest.h"
#include "Result/GetProfileByUserIdResult.h"
#include "Task/Rest/GetProfileByUserIdTask.h"
#include "Task/WebSocket/GetProfileByUserIdTask.h"

// UpdateProfile
#include "Request/UpdateProfileRequest.h"
#include "Result/UpdateProfileResult.h"
#include "Task/Rest/UpdateProfileTask.h"
#include "Task/WebSocket/UpdateProfileTask.h"

// UpdateProfileByUserId
#include "Request/UpdateProfileByUserIdRequest.h"
#include "Result/UpdateProfileByUserIdResult.h"
#include "Task/Rest/UpdateProfileByUserIdTask.h"
#include "Task/WebSocket/UpdateProfileByUserIdTask.h"

// DeleteProfileByUserId
#include "Request/DeleteProfileByUserIdRequest.h"
#include "Result/DeleteProfileByUserIdResult.h"
#include "Task/Rest/DeleteProfileByUserIdTask.h"
#include "Task/WebSocket/DeleteProfileByUserIdTask.h"

// UpdateProfileByStampSheet
#include "Request/UpdateProfileByStampSheetRequest.h"
#include "Result/UpdateProfileByStampSheetResult.h"
#include "Task/Rest/UpdateProfileByStampSheetTask.h"
#include "Task/WebSocket/UpdateProfileByStampSheetTask.h"

// DescribeFriends
#include "Request/DescribeFriendsRequest.h"
#include "Result/DescribeFriendsResult.h"
#include "Task/Rest/DescribeFriendsTask.h"
#include "Task/WebSocket/DescribeFriendsTask.h"

// DescribeFriendsByUserId
#include "Request/DescribeFriendsByUserIdRequest.h"
#include "Result/DescribeFriendsByUserIdResult.h"
#include "Task/Rest/DescribeFriendsByUserIdTask.h"
#include "Task/WebSocket/DescribeFriendsByUserIdTask.h"

// DescribeBlackList
#include "Request/DescribeBlackListRequest.h"
#include "Result/DescribeBlackListResult.h"
#include "Task/Rest/DescribeBlackListTask.h"
#include "Task/WebSocket/DescribeBlackListTask.h"

// DescribeBlackListByUserId
#include "Request/DescribeBlackListByUserIdRequest.h"
#include "Result/DescribeBlackListByUserIdResult.h"
#include "Task/Rest/DescribeBlackListByUserIdTask.h"
#include "Task/WebSocket/DescribeBlackListByUserIdTask.h"

// RegisterBlackList
#include "Request/RegisterBlackListRequest.h"
#include "Result/RegisterBlackListResult.h"
#include "Task/Rest/RegisterBlackListTask.h"
#include "Task/WebSocket/RegisterBlackListTask.h"

// RegisterBlackListByUserId
#include "Request/RegisterBlackListByUserIdRequest.h"
#include "Result/RegisterBlackListByUserIdResult.h"
#include "Task/Rest/RegisterBlackListByUserIdTask.h"
#include "Task/WebSocket/RegisterBlackListByUserIdTask.h"

// UnregisterBlackList
#include "Request/UnregisterBlackListRequest.h"
#include "Result/UnregisterBlackListResult.h"
#include "Task/Rest/UnregisterBlackListTask.h"
#include "Task/WebSocket/UnregisterBlackListTask.h"

// UnregisterBlackListByUserId
#include "Request/UnregisterBlackListByUserIdRequest.h"
#include "Result/UnregisterBlackListByUserIdResult.h"
#include "Task/Rest/UnregisterBlackListByUserIdTask.h"
#include "Task/WebSocket/UnregisterBlackListByUserIdTask.h"

// DescribeFollows
#include "Request/DescribeFollowsRequest.h"
#include "Result/DescribeFollowsResult.h"
#include "Task/Rest/DescribeFollowsTask.h"
#include "Task/WebSocket/DescribeFollowsTask.h"

// DescribeFollowsByUserId
#include "Request/DescribeFollowsByUserIdRequest.h"
#include "Result/DescribeFollowsByUserIdResult.h"
#include "Task/Rest/DescribeFollowsByUserIdTask.h"
#include "Task/WebSocket/DescribeFollowsByUserIdTask.h"

// GetFollow
#include "Request/GetFollowRequest.h"
#include "Result/GetFollowResult.h"
#include "Task/Rest/GetFollowTask.h"
#include "Task/WebSocket/GetFollowTask.h"

// GetFollowByUserId
#include "Request/GetFollowByUserIdRequest.h"
#include "Result/GetFollowByUserIdResult.h"
#include "Task/Rest/GetFollowByUserIdTask.h"
#include "Task/WebSocket/GetFollowByUserIdTask.h"

// Follow
#include "Request/FollowRequest.h"
#include "Result/FollowResult.h"
#include "Task/Rest/FollowTask.h"
#include "Task/WebSocket/FollowTask.h"

// FollowByUserId
#include "Request/FollowByUserIdRequest.h"
#include "Result/FollowByUserIdResult.h"
#include "Task/Rest/FollowByUserIdTask.h"
#include "Task/WebSocket/FollowByUserIdTask.h"

// Unfollow
#include "Request/UnfollowRequest.h"
#include "Result/UnfollowResult.h"
#include "Task/Rest/UnfollowTask.h"
#include "Task/WebSocket/UnfollowTask.h"

// UnfollowByUserId
#include "Request/UnfollowByUserIdRequest.h"
#include "Result/UnfollowByUserIdResult.h"
#include "Task/Rest/UnfollowByUserIdTask.h"
#include "Task/WebSocket/UnfollowByUserIdTask.h"

// GetFriend
#include "Request/GetFriendRequest.h"
#include "Result/GetFriendResult.h"
#include "Task/Rest/GetFriendTask.h"
#include "Task/WebSocket/GetFriendTask.h"

// GetFriendByUserId
#include "Request/GetFriendByUserIdRequest.h"
#include "Result/GetFriendByUserIdResult.h"
#include "Task/Rest/GetFriendByUserIdTask.h"
#include "Task/WebSocket/GetFriendByUserIdTask.h"

// AddFriend
#include "Request/AddFriendRequest.h"
#include "Result/AddFriendResult.h"
#include "Task/Rest/AddFriendTask.h"
#include "Task/WebSocket/AddFriendTask.h"

// AddFriendByUserId
#include "Request/AddFriendByUserIdRequest.h"
#include "Result/AddFriendByUserIdResult.h"
#include "Task/Rest/AddFriendByUserIdTask.h"
#include "Task/WebSocket/AddFriendByUserIdTask.h"

// DeleteFriend
#include "Request/DeleteFriendRequest.h"
#include "Result/DeleteFriendResult.h"
#include "Task/Rest/DeleteFriendTask.h"
#include "Task/WebSocket/DeleteFriendTask.h"

// DeleteFriendByUserId
#include "Request/DeleteFriendByUserIdRequest.h"
#include "Result/DeleteFriendByUserIdResult.h"
#include "Task/Rest/DeleteFriendByUserIdTask.h"
#include "Task/WebSocket/DeleteFriendByUserIdTask.h"

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

// DescribeReceiveRequests
#include "Request/DescribeReceiveRequestsRequest.h"
#include "Result/DescribeReceiveRequestsResult.h"
#include "Task/Rest/DescribeReceiveRequestsTask.h"
#include "Task/WebSocket/DescribeReceiveRequestsTask.h"

// DescribeReceiveRequestsByUserId
#include "Request/DescribeReceiveRequestsByUserIdRequest.h"
#include "Result/DescribeReceiveRequestsByUserIdResult.h"
#include "Task/Rest/DescribeReceiveRequestsByUserIdTask.h"
#include "Task/WebSocket/DescribeReceiveRequestsByUserIdTask.h"

// GetReceiveRequest
#include "Request/GetReceiveRequestRequest.h"
#include "Result/GetReceiveRequestResult.h"
#include "Task/Rest/GetReceiveRequestTask.h"
#include "Task/WebSocket/GetReceiveRequestTask.h"

// GetReceiveRequestByUserId
#include "Request/GetReceiveRequestByUserIdRequest.h"
#include "Result/GetReceiveRequestByUserIdResult.h"
#include "Task/Rest/GetReceiveRequestByUserIdTask.h"
#include "Task/WebSocket/GetReceiveRequestByUserIdTask.h"

// AcceptRequest
#include "Request/AcceptRequestRequest.h"
#include "Result/AcceptRequestResult.h"
#include "Task/Rest/AcceptRequestTask.h"
#include "Task/WebSocket/AcceptRequestTask.h"

// AcceptRequestByUserId
#include "Request/AcceptRequestByUserIdRequest.h"
#include "Result/AcceptRequestByUserIdResult.h"
#include "Task/Rest/AcceptRequestByUserIdTask.h"
#include "Task/WebSocket/AcceptRequestByUserIdTask.h"

// RejectRequest
#include "Request/RejectRequestRequest.h"
#include "Result/RejectRequestResult.h"
#include "Task/Rest/RejectRequestTask.h"
#include "Task/WebSocket/RejectRequestTask.h"

// RejectRequestByUserId
#include "Request/RejectRequestByUserIdRequest.h"
#include "Result/RejectRequestByUserIdResult.h"
#include "Task/Rest/RejectRequestByUserIdTask.h"
#include "Task/WebSocket/RejectRequestByUserIdTask.h"

// GetPublicProfile
#include "Request/GetPublicProfileRequest.h"
#include "Result/GetPublicProfileResult.h"
#include "Task/Rest/GetPublicProfileTask.h"
#include "Task/WebSocket/GetPublicProfileTask.h"

// Client
#include "Gs2FriendRestClient.h"
#include "Gs2FriendWebSocketClient.h"