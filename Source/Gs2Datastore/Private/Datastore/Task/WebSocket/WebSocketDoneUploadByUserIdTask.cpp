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

#include "Datastore/Task/WebSocket/DoneUploadByUserIdTask.h"

#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Net/WebSocket/Gs2WebSocketSession.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"
#include "Datastore/Error/InvalidStatusError.h"
#include "Datastore/Error/NotUploadedError.h"

namespace Gs2::Datastore::Task::WebSocket
{
    FDoneUploadByUserIdTask::FDoneUploadByUserIdTask(
        const Core::Net::WebSocket::FGs2WebSocketSessionPtr Session,
        const Request::FDoneUploadByUserIdRequestPtr Request
    ): Session(Session), Request(Request)
    {
    }

    FDoneUploadByUserIdTask::FDoneUploadByUserIdTask(
        const FDoneUploadByUserIdTask& From
    ): TGs2Future(From), Session(From.Session), Request(From.Request)
    {
    }

    Core::Model::FGs2ErrorPtr FDoneUploadByUserIdTask::Action(
        const TSharedPtr<Result::FDoneUploadByUserIdResultPtr> Result
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
            "datastore",
            "dataObject",
            "doneUploadByUserId"
        );
        Session->Send(RequestPayload);

        UE_LOG(Gs2Log, VeryVerbose, TEXT("[%s:%s:%s] %s"), TEXT("datastore"), TEXT("dataObject"), TEXT("doneUploadByUserId"), ToCStr(RequestPayload->Payload()));

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

        *Result = Result::FDoneUploadByUserIdResult::FromJson(WebSocketResult->Body());

        return nullptr;
    }

    void FDoneUploadByUserIdTask::OnError(Core::Model::FGs2ErrorPtr Error)
    {
        if (Error->Count() > 0 && Error->Detail(0)->Code() == "dataObject.status.invalid") {
            TGs2Future<Result::FDoneUploadByUserIdResult>::OnError(MakeShared<Datastore::Error::FInvalidStatusError>(Error));
        }
        else if (Error->Count() > 0 && Error->Detail(0)->Code() == "dataObject.file.notUploaded") {
            TGs2Future<Result::FDoneUploadByUserIdResult>::OnError(MakeShared<Datastore::Error::FNotUploadedError>(Error));
        }
        else {
            TGs2Future<Result::FDoneUploadByUserIdResult>::OnError(Error);
        }
    }
}