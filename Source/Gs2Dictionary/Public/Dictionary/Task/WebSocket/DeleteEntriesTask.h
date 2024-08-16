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
#include "Dictionary/Request/DeleteEntriesRequest.h"
#include "Dictionary/Result/DeleteEntriesResult.h"

namespace Gs2::Dictionary::Task::WebSocket
{
    class GS2DICTIONARY_API FDeleteEntriesTask final : public Gs2::Core::Util::TGs2Future<Result::FDeleteEntriesResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FDeleteEntriesRequestPtr Request;
    public:
        explicit FDeleteEntriesTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FDeleteEntriesRequestPtr Request
        );
        FDeleteEntriesTask(
            const FDeleteEntriesTask& From
        );
        virtual ~FDeleteEntriesTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FDeleteEntriesResultPtr> Result) override;
    };
    typedef TSharedPtr<FDeleteEntriesTask, ESPMode::ThreadSafe> FDeleteEntriesTaskPtr;
}