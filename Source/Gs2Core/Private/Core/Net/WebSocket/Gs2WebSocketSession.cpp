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


#include "Core/Net/WebSocket/Gs2WebSocketSession.h"

#include "Core/Gs2Constant.h"
#include "Core/Model/Region.h"
#include "Core/Net/WebSocket/Task/WebSocketOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketReOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketCloseTask.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"

namespace Gs2::Core::Net::WebSocket
{
    FGs2WebSocketSession::FGs2WebSocketSession(
        const Model::FGs2CredentialPtr Credential
    ):
        CredentialValue(Credential),
        Region(Model::ERegion::ApNorthEast1),
        Mutex(MakeShared<FCriticalSection>()),
        Disposed(false)
    {
        this->InflightRequests = TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketSessionRequest>>();
        this->Results = TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketResult>>();
    }

    FGs2WebSocketSession::FGs2WebSocketSession(
        const FGs2WebSocketSession& From
    ):
        SocketValue(From.SocketValue),
        InflightRequests(From.InflightRequests),
        Results(From.Results),
        CredentialValue(From.CredentialValue),
        Region(From.Region),
        Mutex(From.Mutex),
        LoginTaskId(From.LoginTaskId),
        NotificationEvent(From.NotificationEvent),
        DisconnectEvent(From.DisconnectEvent),
        Disposed(From.Disposed)
    {
        
    }

    FGs2WebSocketSession::FGs2WebSocketSession(
        const Model::FGs2CredentialPtr Credential,
        const Model::ERegion Region
    ):
        CredentialValue(Credential),
        Region(Region),
        Mutex(MakeShared<FCriticalSection>()),
        Disposed(false)
    {
        this->InflightRequests = TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketSessionRequest>>();
        this->Results = TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketResult>>();
    }

    void FGs2WebSocketSession::Connect()
    {
        auto Processing = true;
    
        const auto Socket = FWebSocketsModule::Get()
            .CreateWebSocket(FGs2Constant::WebSocketEndpointHost
                         .Replace(TEXT("{region}"), *RegionName()));
        Socket->OnConnected().AddLambda([&]
        {
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (Credential()->ClientId() != "")
            {
                JsonRootObject->SetStringField("client_id", Credential()->ClientId());
            }
            if (Credential()->ClientSecret() != "")
            {
                JsonRootObject->SetStringField("client_secret", Credential()->ClientSecret());
            }
            const auto Request = MakeShared<Task::FWebSocketSessionRequest>(JsonRootObject);
            LoginTaskId = Request->TaskId();
            Request->AddHeader(
                Credential()->ClientId(),
                Credential()->ProjectToken(),
                "identifier",
                "projectToken",
                "login"
            );
            Send(Request);
        });
        Socket->OnMessage().AddLambda([&](const FString& Message)
        {
            UE_LOG(Gs2Log, Log, TEXT("%s"), ToCStr(Message));
            if (Disposed)
            {
                UE_LOG(Gs2Log, Error, TEXT("[Socket::OnMessage] FGs2WebSocketSession is already disposed."));
                return;
            }
            
            TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Message);
                FJsonSerializer::Deserialize(JsonReader, JsonRootObject))
            {
                if (const auto Response = Task::FWebSocketResult::FromJson(JsonRootObject); Response->TaskId() == "")
                {
                    if (!Response->IsError())
                    {
                        const auto Notification = Domain::Model::FNotificationMessage::FromJson(Response->Body());
                        NotificationEvent.Broadcast(Notification);
                    }
                }
                else
                {
                    if (LoginTaskId == Response->TaskId())
                    {
                        if (!Response->IsError())
                        {
                            if (Response->Body()->HasField("access_token"))
                            {
                                const auto Token = Response->Body()->GetStringField("access_token");
                                Credential()->UpdateProjectToken(Token);
                            }
                        }
                        Processing = false;
                    }
                    OnMessage(Response);
                }
            }
        });
        Socket->OnConnectionError().AddLambda([&](const FString error)
        {
            UE_LOG(Gs2Log, Warning, TEXT("disconnect websocket session: %s"), ToCStr(error));
            Close();

            Processing = false;
        });
        Socket->OnClosed().AddLambda([&, Socket](int32 StatusCode, const FString& Reason, bool bWasClean)
        {
            Mutex->Lock();
            InflightRequests.Reset();
            Mutex->Unlock();
            Socket->Close();
            DisconnectEvent.Broadcast();
        });
        
        SocketValue = Socket;
        SocketValue->Connect();
        
        while (Processing)
        {
            if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
            {
                FTSBackgroundableTicker::GetCoreTicker().Tick(0.01f);
            }
            FPlatformProcess::Sleep(0.01f);
        }
    }

    void FGs2WebSocketSession::Send(const TSharedPtr<Task::FWebSocketSessionRequest> Request)
    {
        auto Body = Request->Payload();
        UE_LOG(Gs2Log, Log, TEXT("%s"), ToCStr(Body));

        Mutex->Lock();
        InflightRequests.Add(Request->TaskId(), Request);
        Mutex->Unlock();
        SocketValue->Send(Body);
    }

    bool FGs2WebSocketSession::IsConnected() const
    {
        return SocketValue->IsConnected();
    }

    bool FGs2WebSocketSession::IsComplete(FGs2SessionTaskId TaskId) const
    {
        return Results.Contains(TaskId);
    }

    TSharedPtr<Task::FWebSocketResult> FGs2WebSocketSession::GetResult(FGs2SessionTaskId TaskId)
    {
        const auto WebSocketResult = *Results.Find(TaskId);

        Mutex->Lock();
        Results.Remove(TaskId);
        Mutex->Unlock();

        return WebSocketResult;
    }

    void FGs2WebSocketSession::OnMessage(TSharedPtr<Task::FWebSocketResult> Result)
    {
        Mutex->Lock();
        if (InflightRequests.Contains(Result->TaskId()))
        {
            Results.Emplace(Result->TaskId(), Result);
            InflightRequests.Remove(Result->TaskId());
        }
        Mutex->Unlock();
    }

    FGs2NotificationEvent& FGs2WebSocketSession::OnNotification()
    {
        return NotificationEvent;
    }

    FGs2DisconnectEvent& FGs2WebSocketSession::OnDisconnect()
    {
        return DisconnectEvent;
    }

    TSharedPtr<FAsyncTask<Task::FWebSocketOpenTask>> FGs2WebSocketSession::Open()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FWebSocketOpenTask>>(SharedThis(this));
    }

    TSharedPtr<FAsyncTask<Task::FWebSocketReOpenTask>> FGs2WebSocketSession::ReOpen()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FWebSocketReOpenTask>>(SharedThis(this));
    }

    TSharedPtr<FAsyncTask<Task::FWebSocketCloseTask>> FGs2WebSocketSession::Close()
    {
        return Gs2::Core::Util::New<FAsyncTask<Task::FWebSocketCloseTask>>(SharedThis(this));
    }

    Model::FGs2CredentialPtr FGs2WebSocketSession::Credential() const
    {
        return CredentialValue;
    }

    FString FGs2WebSocketSession::RegionName() const
    {
        switch (Region)
        {
        case Model::ApNorthEast1:
            return "ap-northeast-1";
        case Model::UsEast1:
            return "us-east-1";
        case Model::EuWest1:
            return "eu-west-1";
        case Model::ApSouthEast1:
            return "ap-southeast-1";
        }
        return "unknown";
    }
}
