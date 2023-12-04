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


#include "Core/Net/WebSocket/Task/WebSocketSessionRequest.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

namespace Gs2::Core::Net::WebSocket::Task
{
    FWebSocketSessionRequest::FWebSocketSessionRequest(
        const TSharedPtr<FJsonObject> Body
    ): TaskIdValue(FGuid::NewGuid().ToString()), BodyValue(Body)
    {
    }

    FWebSocketSessionRequest::~FWebSocketSessionRequest()
    {
    }

    FGs2SessionTaskId FWebSocketSessionRequest::TaskId() const
    {
        return TaskIdValue;
    }

    FString FWebSocketSessionRequest::Payload() const
    {
        FString Body("");
        const TSharedRef<TJsonWriter<TCHAR>> Writer = TJsonWriterFactory<TCHAR>::Create(&Body);
        FJsonSerializer::Serialize(BodyValue.ToSharedRef(), Writer);
        return Body;
    }

    void FWebSocketSessionRequest::AddHeader(
        const FGs2ClientId ClientId,
        const FGs2ProjectToken ProjectToken,
        const FGs2Service Service,
        const FGs2Component Component,
        const FGs2Function Function
    ) const
    {
        BodyValue->SetStringField("xGs2ClientId", ClientId);
        if (ProjectToken != "")
        {
            BodyValue->SetStringField("xGs2ProjectToken", ProjectToken);
        }
        BodyValue->SetObjectField("x_gs2", [Service, Component, Function, this]() -> TSharedPtr<FJsonObject>
        {
            const auto Header = TSharedPtr<FJsonObject>(new FJsonObject);
            Header->SetStringField("service", Service);
            Header->SetStringField("component", Component);
            Header->SetStringField("function", Function);
            Header->SetStringField("contentType", "application/json");
            Header->SetStringField("requestId", TaskIdValue);
            return Header;
        }());
    }
}