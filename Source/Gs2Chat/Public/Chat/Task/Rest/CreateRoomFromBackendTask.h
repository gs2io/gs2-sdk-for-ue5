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
#include "Chat/Request/CreateRoomFromBackendRequest.h"
#include "Chat/Result/CreateRoomFromBackendResult.h"

namespace Gs2::Chat::Task::Rest
{
    class GS2CHAT_API FCreateRoomFromBackendTask final : public Gs2::Core::Util::TGs2Future<Result::FCreateRoomFromBackendResult>
    {
        Core::Net::Rest::FGs2RestSessionPtr Session;
        Request::FCreateRoomFromBackendRequestPtr Request;
    public:
        explicit FCreateRoomFromBackendTask(
            const Core::Net::Rest::FGs2RestSessionPtr Session,
            const Request::FCreateRoomFromBackendRequestPtr Request
        );
        FCreateRoomFromBackendTask(
            const FCreateRoomFromBackendTask& From
        );
        virtual ~FCreateRoomFromBackendTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FCreateRoomFromBackendResultPtr> Result) override;
    };
    typedef TSharedPtr<FCreateRoomFromBackendTask, ESPMode::ThreadSafe> FCreateRoomFromBackendTaskPtr;
}