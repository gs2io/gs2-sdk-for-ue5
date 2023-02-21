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
#include "Request/NowRequest.h"
#include "Task/Rest/NowTask.h"
#include "Request/DescribeRoomsRequest.h"
#include "Task/Rest/DescribeRoomsTask.h"
#include "Request/WantRoomRequest.h"
#include "Task/Rest/WantRoomTask.h"
#include "Request/GetRoomRequest.h"
#include "Task/Rest/GetRoomTask.h"
#include "Request/DeleteRoomRequest.h"
#include "Task/Rest/DeleteRoomTask.h"

namespace Gs2::Realtime
{
    class GS2REALTIME_API FGs2RealtimeRestClient : Core::Net::FAbstractGs2Client
    {
    public:
        explicit FGs2RealtimeRestClient(
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

        TSharedPtr<FAsyncTask<Task::Rest::FNowTask>> Now(
            const Request::FNowRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDescribeRoomsTask>> DescribeRooms(
            const Request::FDescribeRoomsRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FWantRoomTask>> WantRoom(
            const Request::FWantRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FGetRoomTask>> GetRoom(
            const Request::FGetRoomRequestPtr Request
        ) const;

        TSharedPtr<FAsyncTask<Task::Rest::FDeleteRoomTask>> DeleteRoom(
            const Request::FDeleteRoomRequestPtr Request
        ) const;
    };
    typedef TSharedPtr<FGs2RealtimeRestClient, ESPMode::ThreadSafe> FGs2RealtimeRestClientPtr;
}