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
#include "Request/GetProfileRequest.h"
#include "Task/Rest/GetProfileTask.h"
#include "Request/GetProfileByUserIdRequest.h"
#include "Task/Rest/GetProfileByUserIdTask.h"
#include "Request/UpdateProfileRequest.h"
#include "Task/Rest/UpdateProfileTask.h"
#include "Request/UpdateProfileByUserIdRequest.h"
#include "Task/Rest/UpdateProfileByUserIdTask.h"
#include "Request/DeleteProfileByUserIdRequest.h"
#include "Task/Rest/DeleteProfileByUserIdTask.h"
#include "Request/DescribeFriendsRequest.h"
#include "Task/Rest/DescribeFriendsTask.h"
#include "Request/DescribeFriendsByUserIdRequest.h"
#include "Task/Rest/DescribeFriendsByUserIdTask.h"
#include "Request/DescribeBlackListRequest.h"
#include "Task/Rest/DescribeBlackListTask.h"
#include "Request/DescribeBlackListByUserIdRequest.h"
#include "Task/Rest/DescribeBlackListByUserIdTask.h"
#include "Request/RegisterBlackListRequest.h"
#include "Task/Rest/RegisterBlackListTask.h"
#include "Request/RegisterBlackListByUserIdRequest.h"
#include "Task/Rest/RegisterBlackListByUserIdTask.h"
#include "Request/UnregisterBlackListRequest.h"
#include "Task/Rest/UnregisterBlackListTask.h"
#include "Request/UnregisterBlackListByUserIdRequest.h"
#include "Task/Rest/UnregisterBlackListByUserIdTask.h"
#include "Request/DescribeFollowsRequest.h"
#include "Task/Rest/DescribeFollowsTask.h"
#include "Request/DescribeFollowsByUserIdRequest.h"
#include "Task/Rest/DescribeFollowsByUserIdTask.h"
#include "Request/GetFollowRequest.h"
#include "Task/Rest/GetFollowTask.h"
#include "Request/GetFollowByUserIdRequest.h"
#include "Task/Rest/GetFollowByUserIdTask.h"
#include "Request/FollowRequest.h"
#include "Task/Rest/FollowTask.h"
#include "Request/FollowByUserIdRequest.h"
#include "Task/Rest/FollowByUserIdTask.h"
#include "Request/UnfollowRequest.h"
#include "Task/Rest/UnfollowTask.h"
#include "Request/UnfollowByUserIdRequest.h"
#include "Task/Rest/UnfollowByUserIdTask.h"
#include "Request/GetFriendRequest.h"
#include "Task/Rest/GetFriendTask.h"
#include "Request/GetFriendByUserIdRequest.h"
#include "Task/Rest/GetFriendByUserIdTask.h"
#include "Request/DeleteFriendRequest.h"
#include "Task/Rest/DeleteFriendTask.h"
#include "Request/DeleteFriendByUserIdRequest.h"
#include "Task/Rest/DeleteFriendByUserIdTask.h"
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
#include "Request/DescribeReceiveRequestsRequest.h"
#include "Task/Rest/DescribeReceiveRequestsTask.h"
#include "Request/DescribeReceiveRequestsByUserIdRequest.h"
#include "Task/Rest/DescribeReceiveRequestsByUserIdTask.h"
#include "Request/GetReceiveRequestRequest.h"
#include "Task/Rest/GetReceiveRequestTask.h"
#include "Request/GetReceiveRequestByUserIdRequest.h"
#include "Task/Rest/GetReceiveRequestByUserIdTask.h"
#include "Request/AcceptRequestRequest.h"
#include "Task/Rest/AcceptRequestTask.h"
#include "Request/AcceptRequestByUserIdRequest.h"
#include "Task/Rest/AcceptRequestByUserIdTask.h"
#include "Request/RejectRequestRequest.h"
#include "Task/Rest/RejectRequestTask.h"
#include "Request/RejectRequestByUserIdRequest.h"
#include "Task/Rest/RejectRequestByUserIdTask.h"
#include "Request/GetPublicProfileRequest.h"
#include "Task/Rest/GetPublicProfileTask.h"

namespace Gs2::Friend
{
    class GS2FRIEND_API FGs2FriendRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2FriendRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FGetProfileTask>> GetProfile(
            const Request::FGetProfileRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetProfileByUserIdTask>> GetProfileByUserId(
            const Request::FGetProfileByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateProfileTask>> UpdateProfile(
            const Request::FUpdateProfileRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUpdateProfileByUserIdTask>> UpdateProfileByUserId(
            const Request::FUpdateProfileByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteProfileByUserIdTask>> DeleteProfileByUserId(
            const Request::FDeleteProfileByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFriendsTask>> DescribeFriends(
            const Request::FDescribeFriendsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFriendsByUserIdTask>> DescribeFriendsByUserId(
            const Request::FDescribeFriendsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBlackListTask>> DescribeBlackList(
            const Request::FDescribeBlackListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeBlackListByUserIdTask>> DescribeBlackListByUserId(
            const Request::FDescribeBlackListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRegisterBlackListTask>> RegisterBlackList(
            const Request::FRegisterBlackListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRegisterBlackListByUserIdTask>> RegisterBlackListByUserId(
            const Request::FRegisterBlackListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnregisterBlackListTask>> UnregisterBlackList(
            const Request::FUnregisterBlackListRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnregisterBlackListByUserIdTask>> UnregisterBlackListByUserId(
            const Request::FUnregisterBlackListByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFollowsTask>> DescribeFollows(
            const Request::FDescribeFollowsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeFollowsByUserIdTask>> DescribeFollowsByUserId(
            const Request::FDescribeFollowsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFollowTask>> GetFollow(
            const Request::FGetFollowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFollowByUserIdTask>> GetFollowByUserId(
            const Request::FGetFollowByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FFollowTask>> Follow(
            const Request::FFollowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FFollowByUserIdTask>> FollowByUserId(
            const Request::FFollowByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnfollowTask>> Unfollow(
            const Request::FUnfollowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FUnfollowByUserIdTask>> UnfollowByUserId(
            const Request::FUnfollowByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFriendTask>> GetFriend(
            const Request::FGetFriendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetFriendByUserIdTask>> GetFriendByUserId(
            const Request::FGetFriendByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFriendTask>> DeleteFriend(
            const Request::FDeleteFriendRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteFriendByUserIdTask>> DeleteFriendByUserId(
            const Request::FDeleteFriendByUserIdRequestPtr Request
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

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveRequestsTask>> DescribeReceiveRequests(
            const Request::FDescribeReceiveRequestsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeReceiveRequestsByUserIdTask>> DescribeReceiveRequestsByUserId(
            const Request::FDescribeReceiveRequestsByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveRequestTask>> GetReceiveRequest(
            const Request::FGetReceiveRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetReceiveRequestByUserIdTask>> GetReceiveRequestByUserId(
            const Request::FGetReceiveRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcceptRequestTask>> AcceptRequest(
            const Request::FAcceptRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FAcceptRequestByUserIdTask>> AcceptRequestByUserId(
            const Request::FAcceptRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRejectRequestTask>> RejectRequest(
            const Request::FRejectRequestRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FRejectRequestByUserIdTask>> RejectRequestByUserId(
            const Request::FRejectRequestByUserIdRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetPublicProfileTask>> GetPublicProfile(
            const Request::FGetPublicProfileRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2FriendRestClient, ESPMode::ThreadSafe> FGs2FriendRestClientPtr;
}