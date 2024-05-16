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


#include "Core/Net/WebSocket/Task/WebSocketResult.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

namespace Gs2::Core::Net::WebSocket::Task
{
    FWebSocketResult::FWebSocketResult(
        const FGs2SessionTaskId TaskId,
        const uint16 StatusCode,
        const TSharedPtr<FJsonObject> Body
    ):
        TaskIdValue(TaskId),
        StatusCodeValue(StatusCode),
        BodyValue(Body)
    {
    }

    FWebSocketResult::FWebSocketResult(
        const FGs2SessionTaskId TaskId,
        const uint16 StatusCode,
        const TSharedPtr<Gs2::Core::Model::FGs2Error> Error
    ):
        TaskIdValue(TaskId),
        StatusCodeValue(StatusCode),
        ErrorValue(Error)
    {
    }

    FWebSocketResult::~FWebSocketResult()
    {
    }

    FGs2SessionTaskId FWebSocketResult::TaskId()
    {
        return TaskIdValue;
    }

    bool FWebSocketResult::IsError() const
    {
        return StatusCodeValue / 100 != 2;
    }

    uint16 FWebSocketResult::StatusCode() const
    {
        return StatusCodeValue;
    }

    TSharedPtr<FJsonObject> FWebSocketResult::Body()
    {
        return BodyValue;
    }

    TSharedPtr<Gs2::Core::Model::FGs2Error> FWebSocketResult::Error()
    {
        return ErrorValue;
    }

    TSharedPtr<FWebSocketResult> FWebSocketResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }

        auto Type = Data->HasField(ANSI_TO_TCHAR("type")) ? Data->GetStringField(ANSI_TO_TCHAR("type")) : "";
        auto RequestId = Data->HasField(ANSI_TO_TCHAR("requestId")) ? Data->GetStringField(ANSI_TO_TCHAR("requestId")) : "";
        int16 Status = Data->HasField(ANSI_TO_TCHAR("status")) ? static_cast<int16>(Data->GetIntegerField(ANSI_TO_TCHAR("status"))) : 200;
        auto Body = Data->HasField(ANSI_TO_TCHAR("body")) ? Data->GetObjectField(ANSI_TO_TCHAR("body")) : nullptr;

        if (Status / 100 == 2)
        {
            return MakeShared<FWebSocketResult>(
                RequestId,
                Status,
                Body
            );
        }
        const auto Message = Body->HasField(ANSI_TO_TCHAR("message")) ? Body->GetStringField(ANSI_TO_TCHAR("message")) : "";
        if (Message != "")
        {
            TArray<TSharedPtr<FJsonValue>> JsonRootObject;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Message);
                FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
            {
                auto Error = Gs2::Core::Model::FGs2Error::FromJson(Status, JsonRootObject);
                return MakeShared<FWebSocketResult>(
                    RequestId,
                    Status,
                    Error
                );
            }
        }
        auto Detail = MakeShared<TArray<TSharedPtr<Gs2::Core::Model::FGs2ErrorDetail>>>();
        Detail->Add(MakeShared<Gs2::Core::Model::FGs2ErrorDetail>(
            "unknown",
            Message,
            ""
        ));
        return MakeShared<FWebSocketResult>(
            RequestId,
            Status,
            MakeShared<Gs2::Core::Model::FUnknownError>(
                Detail
            )
        );
    }
}