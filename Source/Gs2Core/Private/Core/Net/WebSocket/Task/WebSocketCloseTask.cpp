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


#include "Core/Net/WebSocket/Task/WebSocketCloseTask.h"
#include "Core/Model/Gs2Error.h"

#include "HttpManager.h"

namespace Gs2::Core::Net::WebSocket::Task
{
    FWebSocketCloseTask::FWebSocketCloseTask(const FGs2WebSocketSessionPtr Session): Session(Session)
    {
   
    }

    FWebSocketCloseTask::~FWebSocketCloseTask()
    {
    }

    Model::FGs2ErrorPtr FWebSocketCloseTask::Action(TSharedPtr<TSharedPtr<Result::FCloseTaskResult>> Result)
    {
        // ★明示的に閉じるときも、応答待ちの要求は FSessionNotOpenError で終わらせる（socket も閉じる）。
        //   以前は DisconnectEvent を鳴らすだけで、接続も待ち側もそのまま放置していた。
        if (Session->DropConnection(TEXT("close")))
        {
            Session->OnDisconnect().Broadcast();
        }
        *Result = MakeShared<Result::FCloseTaskResult>();
        return nullptr;
    }
}
