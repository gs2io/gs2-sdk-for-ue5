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
#include "Guild/Request/UpdateCurrentGuildMasterFromGitHubRequest.h"
#include "Guild/Result/UpdateCurrentGuildMasterFromGitHubResult.h"

namespace Gs2::Guild::Task::WebSocket
{
    class GS2GUILD_API FUpdateCurrentGuildMasterFromGitHubTask final : public Gs2::Core::Util::TGs2Future<Result::FUpdateCurrentGuildMasterFromGitHubResult>
    {
        Core::Net::WebSocket::FGs2WebSocketSessionPtr Session;
        Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request;
    public:
        explicit FUpdateCurrentGuildMasterFromGitHubTask(
            const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
            const Request::FUpdateCurrentGuildMasterFromGitHubRequestPtr Request
        );
        FUpdateCurrentGuildMasterFromGitHubTask(
            const FUpdateCurrentGuildMasterFromGitHubTask& From
        );
        virtual ~FUpdateCurrentGuildMasterFromGitHubTask() override = default;

        virtual Core::Model::FGs2ErrorPtr Action(const TSharedPtr<Result::FUpdateCurrentGuildMasterFromGitHubResultPtr> Result) override;
    };
    typedef TSharedPtr<FUpdateCurrentGuildMasterFromGitHubTask, ESPMode::ThreadSafe> FUpdateCurrentGuildMasterFromGitHubTaskPtr;
}