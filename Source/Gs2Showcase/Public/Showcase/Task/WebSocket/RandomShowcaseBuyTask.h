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
#include "Showcase/Request/RandomShowcaseBuyRequest.h"
#include "Showcase/Result/RandomShowcaseBuyResult.h"

namespace Gs2::Showcase::Task::WebSocket
{
    class GS2SHOWCASE_API FRandomShowcaseBuyTask final : public Gs2::Core::Util::TGs2Future<Result::FRandomShowcaseBuyResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FRandomShowcaseBuyRequestPtr Request;
    public:
        explicit FRandomShowcaseBuyTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FRandomShowcaseBuyRequestPtr Request
        );
        FRandomShowcaseBuyTask(
            const FRandomShowcaseBuyTask& From
        );
        virtual ~FRandomShowcaseBuyTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FRandomShowcaseBuyResultPtr> Result) override;
    };
    typedef TSharedPtr<FRandomShowcaseBuyTask, ESPMode::ThreadSafe> FRandomShowcaseBuyTaskPtr;
}