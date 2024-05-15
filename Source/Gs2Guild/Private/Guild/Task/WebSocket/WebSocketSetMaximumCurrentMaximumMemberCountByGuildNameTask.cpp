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

#include "Guild/Task/WebSocket/SetMaximumCurrentMaximumMemberCountByGuildNameTask.h"

#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"

namespace Gs2::Guild::Task::WebSocket
{
    FSetMaximumCurrentMaximumMemberCountByGuildNameTask::FSetMaximumCurrentMaximumMemberCountByGuildNameTask(
        const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
        const Request::FSetMaximumCurrentMaximumMemberCountByGuildNameRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FSetMaximumCurrentMaximumMemberCountByGuildNameTask::FSetMaximumCurrentMaximumMemberCountByGuildNameTask(
        const FSetMaximumCurrentMaximumMemberCountByGuildNameTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FSetMaximumCurrentMaximumMemberCountByGuildNameTask::Action(
        const TSharedPtr<Result::FSetMaximumCurrentMaximumMemberCountByGuildNameResultPtr> Result
    )
    {
        if (this->Session->Credential()->ProjectToken().Len() == 0)
        {
            const auto Details = MakeShared<TArray<TSharedPtr<Core::Model::FGs2ErrorDetail>>>();
            return MakeShared<Core::Model::FSessionNotOpenError>(Details);
        }

        const auto RequestPayload = MakeShared<Core::Net::WebSocket::Task::FWebSocketSessionRequest>(Request->ToJson());
        RequestPayload->AddHeader(
            Session->Credential()->ClientId(),
            Session->Credential()->ProjectToken(),
            "guild",
            "guild",
            "setMaximumCurrentMaximumMemberCountByGuildName"
        );
        Session->Send(RequestPayload);

        UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s:%s:%s] %s"), TEXT("guild"), TEXT("guild"), TEXT("setMaximumCurrentMaximumMemberCountByGuildName"), ToCStr(RequestPayload->Payload()));

        while (!Session->IsConnected() || !Session->IsComplete(RequestPayload->TaskId()))
        {
            FTSBackgroundableTicker::GetCoreTicker().Tick(0.01f);
            FPlatformProcess::Sleep(0.01f);
        }

        const auto WebSocketResult = Session->GetResult(RequestPayload->TaskId());
        if (WebSocketResult->IsError())
        {
            return WebSocketResult->Error();
        }

        *Result = Result::FSetMaximumCurrentMaximumMemberCountByGuildNameResult::FromJson(WebSocketResult->Body());

        return nullptr;
    }
}