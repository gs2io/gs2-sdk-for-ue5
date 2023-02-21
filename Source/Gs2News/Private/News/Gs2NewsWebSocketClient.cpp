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

#include "News/Gs2NewsWebSocketClient.h"

namespace Gs2::News
{

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>> FGs2NewsWebSocketClient::DescribeNamespaces(
        const Request::FDescribeNamespacesRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNamespacesTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>> FGs2NewsWebSocketClient::CreateNamespace(
        const Request::FCreateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FCreateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>> FGs2NewsWebSocketClient::GetNamespaceStatus(
        const Request::FGetNamespaceStatusRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceStatusTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FGetNamespaceTask>> FGs2NewsWebSocketClient::GetNamespace(
        const Request::FGetNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FGetNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>> FGs2NewsWebSocketClient::UpdateNamespace(
        const Request::FUpdateNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>> FGs2NewsWebSocketClient::DeleteNamespace(
        const Request::FDeleteNamespaceRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDeleteNamespaceTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUpdateCurrentNewsMasterTask>> FGs2NewsWebSocketClient::PrepareUpdateCurrentNewsMaster(
        const Request::FPrepareUpdateCurrentNewsMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareUpdateCurrentNewsMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FUpdateCurrentNewsMasterTask>> FGs2NewsWebSocketClient::UpdateCurrentNewsMaster(
        const Request::FUpdateCurrentNewsMasterRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FUpdateCurrentNewsMasterTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FPrepareUpdateCurrentNewsMasterFromGitHubTask>> FGs2NewsWebSocketClient::PrepareUpdateCurrentNewsMasterFromGitHub(
        const Request::FPrepareUpdateCurrentNewsMasterFromGitHubRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FPrepareUpdateCurrentNewsMasterFromGitHubTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNewsTask>> FGs2NewsWebSocketClient::DescribeNews(
        const Request::FDescribeNewsRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNewsTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FDescribeNewsByUserIdTask>> FGs2NewsWebSocketClient::DescribeNewsByUserId(
        const Request::FDescribeNewsByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FDescribeNewsByUserIdTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FWantGrantTask>> FGs2NewsWebSocketClient::WantGrant(
        const Request::FWantGrantRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FWantGrantTask>>(
            Session,
            Request
        );
    }

    TSharedPtr<FAsyncTask<Task::WebSocket::FWantGrantByUserIdTask>> FGs2NewsWebSocketClient::WantGrantByUserId(
        const Request::FWantGrantByUserIdRequestPtr Request) const
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::WebSocket::FWantGrantByUserIdTask>>(
            Session,
            Request
        );
    }
}