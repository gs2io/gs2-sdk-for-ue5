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
#include "Request/GetServiceVersionRequest.h"
#include "Task/WebSocket/GetServiceVersionTask.h"
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
#include "Request/GetProfileRequest.h"
#include "Task/WebSocket/GetProfileTask.h"
#include "Request/GetProfileByUserIdRequest.h"
#include "Task/WebSocket/GetProfileByUserIdTask.h"
#include "Request/UpdateProfileRequest.h"
#include "Task/WebSocket/UpdateProfileTask.h"
#include "Request/UpdateProfileByUserIdRequest.h"
#include "Task/WebSocket/UpdateProfileByUserIdTask.h"
#include "Request/DeleteProfileByUserIdRequest.h"
#include "Task/WebSocket/DeleteProfileByUserIdTask.h"
#include "Request/UpdateProfileByStampSheetRequest.h"
#include "Task/WebSocket/UpdateProfileByStampSheetTask.h"
#include "Request/DescribeFriendsRequest.h"
#include "Task/WebSocket/DescribeFriendsTask.h"
#include "Request/DescribeFriendsByUserIdRequest.h"
#include "Task/WebSocket/DescribeFriendsByUserIdTask.h"
#include "Request/DescribeBlackListRequest.h"
#include "Task/WebSocket/DescribeBlackListTask.h"
#include "Request/DescribeBlackListByUserIdRequest.h"
#include "Task/WebSocket/DescribeBlackListByUserIdTask.h"
#include "Request/RegisterBlackListRequest.h"
#include "Task/WebSocket/RegisterBlackListTask.h"
#include "Request/RegisterBlackListByUserIdRequest.h"
#include "Task/WebSocket/RegisterBlackListByUserIdTask.h"
#include "Request/UnregisterBlackListRequest.h"
#include "Task/WebSocket/UnregisterBlackListTask.h"
#include "Request/UnregisterBlackListByUserIdRequest.h"
#include "Task/WebSocket/UnregisterBlackListByUserIdTask.h"
#include "Request/DescribeFollowsRequest.h"
#include "Task/WebSocket/DescribeFollowsTask.h"
#include "Request/DescribeFollowsByUserIdRequest.h"
#include "Task/WebSocket/DescribeFollowsByUserIdTask.h"
#include "Request/GetFollowRequest.h"
#include "Task/WebSocket/GetFollowTask.h"
#include "Request/GetFollowByUserIdRequest.h"
#include "Task/WebSocket/GetFollowByUserIdTask.h"
#include "Request/FollowRequest.h"
#include "Task/WebSocket/FollowTask.h"
#include "Request/FollowByUserIdRequest.h"
#include "Task/WebSocket/FollowByUserIdTask.h"
#include "Request/UnfollowRequest.h"
#include "Task/WebSocket/UnfollowTask.h"
#include "Request/UnfollowByUserIdRequest.h"
#include "Task/WebSocket/UnfollowByUserIdTask.h"
#include "Request/GetFriendRequest.h"
#include "Task/WebSocket/GetFriendTask.h"
#include "Request/GetFriendByUserIdRequest.h"
#include "Task/WebSocket/GetFriendByUserIdTask.h"
#include "Request/DeleteFriendRequest.h"
#include "Task/WebSocket/DeleteFriendTask.h"
#include "Request/DeleteFriendByUserIdRequest.h"
#include "Task/WebSocket/DeleteFriendByUserIdTask.h"
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
#include "Request/DescribeReceiveRequestsRequest.h"
#include "Task/WebSocket/DescribeReceiveRequestsTask.h"
#include "Request/DescribeReceiveRequestsByUserIdRequest.h"
#include "Task/WebSocket/DescribeReceiveRequestsByUserIdTask.h"
#include "Request/GetReceiveRequestRequest.h"
#include "Task/WebSocket/GetReceiveRequestTask.h"
#include "Request/GetReceiveRequestByUserIdRequest.h"
#include "Task/WebSocket/GetReceiveRequestByUserIdTask.h"
#include "Request/AcceptRequestRequest.h"
#include "Task/WebSocket/AcceptRequestTask.h"
#include "Request/AcceptRequestByUserIdRequest.h"
#include "Task/WebSocket/AcceptRequestByUserIdTask.h"
#include "Request/RejectRequestRequest.h"
#include "Task/WebSocket/RejectRequestTask.h"
#include "Request/RejectRequestByUserIdRequest.h"
#include "Task/WebSocket/RejectRequestByUserIdTask.h"
#include "Request/GetPublicProfileRequest.h"
#include "Task/WebSocket/GetPublicProfileTask.h"

namespace Gs2::Friend
{
    class GS2FRIEND_API FGs2FriendWebSocketClient : Core::Net::FAbstractWebSocketGs2Client
    {
    public:
        explicit FGs2FriendWebSocketClient(
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetServiceVersionTask>> GetServiceVersion(
            const Request::FGetServiceVersionRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProfileTask>> GetProfile(
            const Request::FGetProfileRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetProfileByUserIdTask>> GetProfileByUserId(
            const Request::FGetProfileByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateProfileTask>> UpdateProfile(
            const Request::FUpdateProfileRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateProfileByUserIdTask>> UpdateProfileByUserId(
            const Request::FUpdateProfileByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteProfileByUserIdTask>> DeleteProfileByUserId(
            const Request::FDeleteProfileByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateProfileByStampSheetTask>> UpdateProfileByStampSheet(
            const Request::FUpdateProfileByStampSheetRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFriendsTask>> DescribeFriends(
            const Request::FDescribeFriendsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFriendsByUserIdTask>> DescribeFriendsByUserId(
            const Request::FDescribeFriendsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBlackListTask>> DescribeBlackList(
            const Request::FDescribeBlackListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeBlackListByUserIdTask>> DescribeBlackListByUserId(
            const Request::FDescribeBlackListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRegisterBlackListTask>> RegisterBlackList(
            const Request::FRegisterBlackListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRegisterBlackListByUserIdTask>> RegisterBlackListByUserId(
            const Request::FRegisterBlackListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnregisterBlackListTask>> UnregisterBlackList(
            const Request::FUnregisterBlackListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnregisterBlackListByUserIdTask>> UnregisterBlackListByUserId(
            const Request::FUnregisterBlackListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFollowsTask>> DescribeFollows(
            const Request::FDescribeFollowsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeFollowsByUserIdTask>> DescribeFollowsByUserId(
            const Request::FDescribeFollowsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFollowTask>> GetFollow(
            const Request::FGetFollowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFollowByUserIdTask>> GetFollowByUserId(
            const Request::FGetFollowByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFollowTask>> Follow(
            const Request::FFollowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FFollowByUserIdTask>> FollowByUserId(
            const Request::FFollowByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnfollowTask>> Unfollow(
            const Request::FUnfollowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FUnfollowByUserIdTask>> UnfollowByUserId(
            const Request::FUnfollowByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFriendTask>> GetFriend(
            const Request::FGetFriendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetFriendByUserIdTask>> GetFriendByUserId(
            const Request::FGetFriendByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFriendTask>> DeleteFriend(
            const Request::FDeleteFriendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteFriendByUserIdTask>> DeleteFriendByUserId(
            const Request::FDeleteFriendByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsTask>> DescribeReceiveRequests(
            const Request::FDescribeReceiveRequestsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeReceiveRequestsByUserIdTask>> DescribeReceiveRequestsByUserId(
            const Request::FDescribeReceiveRequestsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveRequestTask>> GetReceiveRequest(
            const Request::FGetReceiveRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetReceiveRequestByUserIdTask>> GetReceiveRequestByUserId(
            const Request::FGetReceiveRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptRequestTask>> AcceptRequest(
            const Request::FAcceptRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FAcceptRequestByUserIdTask>> AcceptRequestByUserId(
            const Request::FAcceptRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRejectRequestTask>> RejectRequest(
            const Request::FRejectRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FRejectRequestByUserIdTask>> RejectRequestByUserId(
            const Request::FRejectRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::WebSocket::FGetPublicProfileTask>> GetPublicProfile(
            const Request::FGetPublicProfileRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2FriendWebSocketClient, ESPMode::ThreadSafe> FGs2FriendWebSocketClientPtr;
}