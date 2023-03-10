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


#include "Core/Net/WebSocket/Task/WebSocketOpenTask.h"

#include "WebSocketsModule.h"
#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Model/Gs2Error.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"

namespace Gs2::Core::Net::WebSocket::Task
{
    FWebSocketOpenTask::FWebSocketOpenTask(const FGs2WebSocketSessionPtr Session): Session(Session)
    {

    }

    FWebSocketOpenTask::~FWebSocketOpenTask()
    {
    }

    Model::FGs2ErrorPtr FWebSocketOpenTask::Action(TSharedPtr<TSharedPtr<Result::FOpenTaskResult>> Result)
    {
        Session->Connect();
        if (!Session->SocketValue->IsConnected() || !Session->Results.Contains(Session->LoginTaskId))
        {
            auto Detail = MakeShared<TArray<Model::FGs2ErrorDetailPtr>>();
            Detail->Add(MakeShared<Model::FGs2ErrorDetail>(
                "session",
                "failed",
                ""
            ));
            return MakeShared<Model::FSessionNotOpenError>(Detail);
        }
        
        const auto WebSocketResult = *Session->Results.Find(Session->LoginTaskId);
    
        Session->Mutex->Lock();
        Session->Results.Remove(Session->LoginTaskId);
        Session->Mutex->Unlock();

        if (WebSocketResult->IsError())
        {
            return WebSocketResult->Error();
        }
        
        *Result = MakeShared<Result::FOpenTaskResult>();
        return nullptr;
    }
}
