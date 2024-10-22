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

#include "Chat/Task/WebSocket/DescribeLatestMessagesByUserIdTask.h"

#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"
#include "Chat/Error/NoAccessPrivilegesError.h"
#include "Chat/Error/PasswordRequiredError.h"
#include "Chat/Error/PasswordIncorrectError.h"

namespace Gs2::Chat::Task::WebSocket
{
    FDescribeLatestMessagesByUserIdTask::FDescribeLatestMessagesByUserIdTask(
        const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
        const Request::FDescribeLatestMessagesByUserIdRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FDescribeLatestMessagesByUserIdTask::FDescribeLatestMessagesByUserIdTask(
        const FDescribeLatestMessagesByUserIdTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FDescribeLatestMessagesByUserIdTask::Action(
        const TSharedPtr<Result::FDescribeLatestMessagesByUserIdResultPtr> Result
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
            "chat",
            "message",
            "describeLatestMessagesByUserId"
        );
        Session->Send(RequestPayload);

        UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s:%s:%s] %s"), TEXT("chat"), TEXT("message"), TEXT("describeLatestMessagesByUserId"), ToCStr(RequestPayload->Payload()));

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

        *Result = Result::FDescribeLatestMessagesByUserIdResult::FromJson(WebSocketResult->Body());

        return nullptr;
    }

    void FDescribeLatestMessagesByUserIdTask::OnError(Core::Model::FGs2ErrorPtr Error)
    {
        if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.allowUserIds.notInclude") {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(MakeShared<Chat::Error::FNoAccessPrivilegesError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.password.require") {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(MakeShared<Chat::Error::FPasswordRequiredError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "room.password.invalid") {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(MakeShared<Chat::Error::FPasswordIncorrectError>(Error));
        }
        else {
            TGs2Future<Result::FDescribeLatestMessagesByUserIdResult>::OnError(Error);
        }
    }
}