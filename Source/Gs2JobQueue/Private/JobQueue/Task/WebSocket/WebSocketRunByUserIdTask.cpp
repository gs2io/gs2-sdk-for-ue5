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

#include "JobQueue/Task/WebSocket/RunByUserIdTask.h"

#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"

namespace Gs2::JobQueue::Task::WebSocket
{
    FRunByUserIdTask::FRunByUserIdTask(
        const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
        const Request::FRunByUserIdRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FRunByUserIdTask::FRunByUserIdTask(
        const FRunByUserIdTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FRunByUserIdTask::Action(
        const TSharedPtr<Result::FRunByUserIdResultPtr> Result
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
            "jobQueue",
            "job",
            "runByUserId"
        );
        Session->Send(RequestPayload);

        UE_LOG(Gs2Log, Log, TEXT("[%s:%s:%s] %s"), TEXT("jobQueue"), TEXT("job"), TEXT("runByUserId"), ToCStr(RequestPayload->Payload()));

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

        *Result = Result::FRunByUserIdResult::FromJson(WebSocketResult->Body());

        return nullptr;
    }
}