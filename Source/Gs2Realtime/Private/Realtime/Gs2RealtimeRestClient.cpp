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

#include "Realtime/Gs2RealtimeRestClient.h"

namespace Gs2::Realtime
{

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeNamespacesTask>> FGs2RealtimeRestClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FCreateNamespaceTask>> FGs2RealtimeRestClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>> FGs2RealtimeRestClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetNamespaceTask>> FGs2RealtimeRestClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FUpdateNamespaceTask>> FGs2RealtimeRestClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteNamespaceTask>> FGs2RealtimeRestClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FNowTask>> FGs2RealtimeRestClient::Now(
        const Request::FNowRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FNowTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDescribeRoomsTask>> FGs2RealtimeRestClient::DescribeRooms(
        const Request::FDescribeRoomsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDescribeRoomsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FWantRoomTask>> FGs2RealtimeRestClient::WantRoom(
        const Request::FWantRoomRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FWantRoomTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FGetRoomTask>> FGs2RealtimeRestClient::GetRoom(
        const Request::FGetRoomRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FGetRoomTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::Rest::FDeleteRoomTask>> FGs2RealtimeRestClient::DeleteRoom(
        const Request::FDeleteRoomRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::Rest::FDeleteRoomTask>>(
            Session,
            Request
        );
    }
}