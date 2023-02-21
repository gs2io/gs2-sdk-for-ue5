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

#include "Mission/Task/WebSocket/DeleteCounterModelMasterTask.h"

#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"

namespace Gs2::Mission::Task::WebSocket
{
    FDeleteCounterModelMasterTask::FDeleteCounterModelMasterTask(
        const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
        const Request::FDeleteCounterModelMasterRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FDeleteCounterModelMasterTask::FDeleteCounterModelMasterTask(
        const FDeleteCounterModelMasterTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FDeleteCounterModelMasterTask::Action(
        const TSharedPtr<Result::FDeleteCounterModelMasterResultPtr> Result
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
            "mission",
            "counterModelMaster",
            "deleteCounterModelMaster"
        );
        Session->Send(RequestPayload);

        UE_LOG(Gs2Log, Log, TEXT("[%s:%s:%s] %s"), TEXT("mission"), TEXT("counterModelMaster"), TEXT("deleteCounterModelMaster"), ToCStr(RequestPayload->Payload()));

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

        *Result = Result::FDeleteCounterModelMasterResult::FromJson(WebSocketResult->Body());

        return nullptr;
    }
}