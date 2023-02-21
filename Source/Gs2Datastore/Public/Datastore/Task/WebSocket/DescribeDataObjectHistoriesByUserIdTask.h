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

#include "Core/Gs2Core.h"
#include "Datastore/Request/DescribeDataObjectHistoriesByUserIdRequest.h"
#include "Datastore/Result/DescribeDataObjectHistoriesByUserIdResult.h"

namespace Gs2::Datastore::Task::WebSocket
{
    class GS2DATASTORE_API FDescribeDataObjectHistoriesByUserIdTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeDataObjectHistoriesByUserIdResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDescribeDataObjectHistoriesByUserIdRequestPtr Request;
    public:
        explicit FDescribeDataObjectHistoriesByUserIdTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDescribeDataObjectHistoriesByUserIdRequestPtr Request
        );
        FDescribeDataObjectHistoriesByUserIdTask(
            const FDescribeDataObjectHistoriesByUserIdTask& From
        );
        virtual ~FDescribeDataObjectHistoriesByUserIdTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeDataObjectHistoriesByUserIdResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeDataObjectHistoriesByUserIdTask, ESPMode::ThreadSafe> FDescribeDataObjectHistoriesByUserIdTaskPtr;
}