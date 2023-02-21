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
#include "Inbox/Request/DescribeGlobalMessagesRequest.h"
#include "Inbox/Result/DescribeGlobalMessagesResult.h"

namespace Gs2::Inbox::Task::WebSocket
{
    class GS2INBOX_API FDescribeGlobalMessagesTask final : public Gs2::Core::Util::TGs2Future<Result::FDescribeGlobalMessagesResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDescribeGlobalMessagesRequestPtr Request;
    public:
        explicit FDescribeGlobalMessagesTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDescribeGlobalMessagesRequestPtr Request
        );
        FDescribeGlobalMessagesTask(
            const FDescribeGlobalMessagesTask& From
        );
        virtual ~FDescribeGlobalMessagesTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDescribeGlobalMessagesResultPtr> Result) override;
    };
    typedef TSharedPtr<FDescribeGlobalMessagesTask, ESPMode::ThreadSafe> FDescribeGlobalMessagesTaskPtr;
}