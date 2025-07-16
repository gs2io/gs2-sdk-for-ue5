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

#include "Guild/Task/WebSocket/SendRequestTask.h"

#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"
#include "Guild/Error/MaximumMembersReachedError.h"
#include "Guild/Error/MaximumJoinedGuildsReachedError.h"
#include "Guild/Error/MaximumReceiveRequestsReachedError.h"
#include "Guild/Error/MaximumSendRequestsReachedError.h"
#include "Guild/Error/DotMeetJoinRequirementsError.h"

namespace Gs2::Guild::Task::WebSocket
{
    FSendRequestTask::FSendRequestTask(
        const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
        const Request::FSendRequestRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FSendRequestTask::FSendRequestTask(
        const FSendRequestTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FSendRequestTask::Action(
        const TSharedPtr<Result::FSendRequestResultPtr> Result
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
            "sendMemberRequest",
            "sendRequest"
        );
        Session->Send(RequestPayload);

        UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s:%s:%s] %s"), TEXT("guild"), TEXT("sendMemberRequest"), TEXT("sendRequest"), ToCStr(RequestPayload->Payload()));

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

        *Result = Result::FSendRequestResult::FromJson(WebSocketResult->Body());

        return nullptr;
    }

    void FSendRequestTask::OnError(Core::Model::FGs2ErrorPtr Error)
    {
        if (Error->Count() > 0 && Error->Detail(0)->Code() == "guild.members.tooMany") {
            TGs2Future<Result::FSendRequestResult>::OnError(MakeShared<Guild::Error::FMaximumMembersReachedError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "user.joinedGuild.tooMany") {
            TGs2Future<Result::FSendRequestResult>::OnError(MakeShared<Guild::Error::FMaximumJoinedGuildsReachedError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "guild.receiveRequests.tooMany") {
            TGs2Future<Result::FSendRequestResult>::OnError(MakeShared<Guild::Error::FMaximumReceiveRequestsReachedError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "guild.sendRequests.tooMany") {
            TGs2Future<Result::FSendRequestResult>::OnError(MakeShared<Guild::Error::FMaximumSendRequestsReachedError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "guild.sendRequests.notMeetJoinRequirements") {
            TGs2Future<Result::FSendRequestResult>::OnError(MakeShared<Guild::Error::FDotMeetJoinRequirementsError>(Error));
        }
        else {
            TGs2Future<Result::FSendRequestResult>::OnError(Error);
        }
    }
}