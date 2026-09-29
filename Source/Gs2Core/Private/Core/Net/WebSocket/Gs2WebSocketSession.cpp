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
#include "Core/Model/Gs2Error.h"
#include "Core/Model/Region.h"
#include "Misc/ScopeLock.h"
#include "Core/Net/WebSocket/Task/WebSocketOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketReOpenTask.h"
#include "Core/Net/WebSocket/Task/WebSocketCloseTask.h"
#include "Core/Net/WebSocket/Task/WebSocketResult.h"

namespace Gs2::Core::Net::WebSocket
{
    FGs2WebSocketSession::FGs2WebSocketSession(
        const Model::FGs2CredentialPtr& Credential
    ): FGs2WebSocketSession(Credential, Model::ERegion::ApNorthEast1)
    {
    }

    FGs2WebSocketSession::FGs2WebSocketSession(
        const Model::FGs2CredentialPtr& Credential,
        const Model::ERegion Region
    ): FGs2WebSocketSession(
        Credential,
        Region,
        [](const FString& Endpoint) { return FWebSocketsModule::Get().CreateWebSocket(Endpoint); }
    )
    {
    }

    FGs2WebSocketSession::FGs2WebSocketSession(
        const Model::FGs2CredentialPtr& Credential,
        const Model::ERegion Region,
        TFunction<TSharedPtr<IWebSocket>(const FString&)> Factory
    ):
        WebSocketFactory(MoveTemp(Factory)),
        CredentialValue(Credential),
        RegionValue(Region),
        OwnerIdValue(""),
        Mutex(MakeShared<FCriticalSection>()),
        LoginTaskId(),
        SteadyEndpointValue(""),
        ClosedValue(true),
        GenerationValue(0),
        Disposed(false)
    {
        this->InflightRequests = TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketSessionRequest>>();
        this->Results = TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketResult>>();
    }

    FGs2WebSocketSession::FGs2WebSocketSession(
        const FGs2WebSocketSession& From
    ):
        SocketValue(From.SocketValue),
        WebSocketFactory(From.WebSocketFactory),
        InflightRequests(From.InflightRequests),
        Results(From.Results),
        CredentialValue(From.CredentialValue),
        RegionValue(From.RegionValue),
        OwnerIdValue(""),
        Mutex(From.Mutex),
        LoginTaskId(From.LoginTaskId),
        NotificationEvent(From.NotificationEvent),
        DisconnectEvent(From.DisconnectEvent),
        SteadyEndpointValue(From.SteadyEndpointValue),
        ClosedValue(From.ClosedValue),
        GenerationValue(From.GenerationValue),
        Disposed(From.Disposed)
    {
        
    }

    void FGs2WebSocketSession::Connect()
    {
        DropConnection(TEXT("reconnect"));

        const TSharedPtr<bool> Processing = MakeShared<bool>(true);

        int32 Generation;
        {
            FScopeLock Lock(Mutex.Get());
            GenerationValue++;
            Generation = GenerationValue;
            Results.Remove(LoginTaskId);
        }

        const auto Socket = WebSocketFactory(EndpointUrl());
        Socket->OnConnected().AddLambda([this, Processing, Generation]
        {
            if (Disposed || !IsCurrentGeneration(Generation))
            {
                return;
            }
            if (Credential()->IsProjectTokenCredential())
            {
                *Processing = false;
                return;
            }
            const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
            if (Credential()->ClientId() != "")
            {
                JsonRootObject->SetStringField(TEXT("client_id"), Credential()->ClientId());
            }
            if (Credential()->ClientSecret() != "")
            {
                JsonRootObject->SetStringField(TEXT("client_secret"), Credential()->ClientSecret());
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
        Socket->OnMessage().AddLambda([this, Processing, Generation](const FString& Message)
        {
            UE_LOG(Gs2Log, VeryVerbose, TEXT("%s"), ToCStr(Message));
            if (Disposed)
            {
                UE_LOG(Gs2Log, Error, TEXT("[Socket::OnMessage] FGs2WebSocketSession is already disposed."));
                return;
            }
            if (!IsCurrentGeneration(Generation))
            {
                return;
            }

            const auto Fail = [this, Processing](const FString& Reason)
            {
                UE_LOG(Gs2Log, Warning, TEXT("Failed to parse WebSocket response."));
                *Processing = false;
                if (DropConnection(Reason))
                {
                    DisconnectEvent.Broadcast();
                }
            };

            TSharedPtr<FJsonObject> JsonRootObject;
            if (const TSharedRef<TJsonReader<>> JsonReader = TJsonReaderFactory<>::Create(Message);
                !FJsonSerializer::Deserialize(JsonReader, JsonRootObject) || !JsonRootObject.IsValid())
            {
                Fail(TEXT("failed to parse websocket response"));
                return;
            }
            if ((JsonRootObject->HasField(ANSI_TO_TCHAR("type")) &&
                    !JsonRootObject->HasTypedField<EJson::String>(ANSI_TO_TCHAR("type"))) ||
                (JsonRootObject->HasField(ANSI_TO_TCHAR("requestId")) &&
                    !JsonRootObject->HasTypedField<EJson::String>(ANSI_TO_TCHAR("requestId"))) ||
                (JsonRootObject->HasField(ANSI_TO_TCHAR("status")) &&
                    !JsonRootObject->HasTypedField<EJson::Number>(ANSI_TO_TCHAR("status"))))
            {
                Fail(TEXT("failed to parse websocket response"));
                return;
            }

            auto Response = Task::FWebSocketResult::FromJson(JsonRootObject);
            if (!Response.IsValid())
            {
                Fail(TEXT("failed to parse websocket response"));
                return;
            }
            const bool bIsNotification = JsonRootObject->HasTypedField<EJson::String>(ANSI_TO_TCHAR("type")) &&
                JsonRootObject->GetStringField(ANSI_TO_TCHAR("type")) == ANSI_TO_TCHAR("notification");
            if (Response->TaskId() == "" && !bIsNotification)
            {
                Fail(TEXT("failed to parse websocket response"));
                return;
            }

            {
                if (Response->TaskId() == "")
                {
                    if (bIsNotification)
                    {
                        const auto Body = JsonRootObject->HasTypedField<EJson::Object>(ANSI_TO_TCHAR("body"))
                            ? JsonRootObject->GetObjectField(ANSI_TO_TCHAR("body"))
                            : nullptr;
                        const auto Notification = Domain::Model::FNotificationMessage::FromJson(Body);
                        const bool bHasDispatchFields = Body.IsValid() &&
                            Body->HasTypedField<EJson::String>(ANSI_TO_TCHAR("subject")) &&
                            Body->HasTypedField<EJson::String>(ANSI_TO_TCHAR("payload")) &&
                            Notification.IsValid() &&
                            Notification->GetSubject().IsSet() &&
                            Notification->GetPayload().IsSet();
                        if (bHasDispatchFields)
                        {
                            NotificationEvent.Broadcast(Notification);
                        }
                        else
                        {
                            UE_LOG(Gs2Log, Warning, TEXT("Notification did not contain required dispatch fields."));
                            if (DropConnection(TEXT("notification did not contain required dispatch fields")))
                            {
                                DisconnectEvent.Broadcast();
                            }
                        }
                    }
                }
                else
                {
                    if (LoginTaskId == Response->TaskId())
                    {
                        if (!Response->IsError())
                        {
                            FString Token;
                            if (Response->Body().IsValid() && Response->Body()->TryGetStringField(ANSI_TO_TCHAR("access_token"), Token))
                            {
                                Credential()->UpdateProjectToken(Token);
                            }
                            else
                            {
                                const auto Details = MakeShared<TArray<Model::FGs2ErrorDetailPtr>>();
                                Details->Add(MakeShared<Model::FGs2ErrorDetail>(
                                    TEXT("client"),
                                    TEXT("Login response did not contain an access token."),
                                    TEXT("")
                                ));
                                Response = MakeShared<Task::FWebSocketResult>(
                                    Response->TaskId(),
                                    0,
                                    MakeShared<Model::FUnknownError>(Details)
                                );
                            }
                        }
                        OnMessage(Response);
                        *Processing = false;
                        if (Response->IsError() && DropConnection(TEXT("websocket login failed")))
                        {
                            DisconnectEvent.Broadcast();
                        }
                    }
                    if (LoginTaskId != Response->TaskId())
                    {
                        OnMessage(Response);
                    }
                }
            }
        });
        Socket->OnConnectionError().AddLambda([this, Processing, Generation](const FString& Error)
        {
            UE_LOG(Gs2Log, Warning, TEXT("disconnect websocket session: %s"), ToCStr(Error));
            *Processing = false;
            if (Disposed || !IsCurrentGeneration(Generation))
            {
                return;
            }
            if (DropConnection(FString::Printf(TEXT("connection error: %s"), *Error)))
            {
                DisconnectEvent.Broadcast();
            }
        });
        Socket->OnClosed().AddLambda([this, Processing, Generation](int32 StatusCode, const FString& Reason, bool bWasClean)
        {
            *Processing = false;
            if (Disposed || !IsCurrentGeneration(Generation))
            {
                return;
            }
            if (DropConnection(FString::Printf(
                TEXT("closed: status=%d, clean=%s, reason=%s"),
                StatusCode,
                bWasClean ? TEXT("true") : TEXT("false"),
                *Reason
            )))
            {
                DisconnectEvent.Broadcast();
            }
        });
        
        {
            FScopeLock Lock(Mutex.Get());
            SocketValue = Socket;
            ClosedValue = false;
        }
        Socket->Connect();
        
        while (*Processing)
        {
            if (FPlatformTLS::GetCurrentThreadId() == GGameThreadId)
            {
                FTSBackgroundableTicker::GetCoreTicker().Tick(0.01f);
            }
            FPlatformProcess::Sleep(0.01f);
        }
    }

    bool FGs2WebSocketSession::IsCurrentGeneration(const int32 Generation) const
    {
        FScopeLock Lock(Mutex.Get());
        return GenerationValue == Generation;
    }

    TSharedPtr<Task::FWebSocketResult> FGs2WebSocketSession::MakeConnectionLostResult(
        const FGs2SessionTaskId& TaskId,
        const FString& Reason
    )
    {
        const auto Detail = MakeShared<TArray<Model::FGs2ErrorDetailPtr>>();
        Detail->Add(MakeShared<Model::FGs2ErrorDetail>(
            "session",
            Reason,
            ""
        ));
        const Model::FGs2ErrorPtr Error = MakeShared<Model::FSessionNotOpenError>(Detail);
        return MakeShared<Task::FWebSocketResult>(
            TaskId,
            0,
            Error
        );
    }

    bool FGs2WebSocketSession::DropConnection(const FString& Reason)
    {
        TArray<FGs2SessionTaskId> Pending;
        TSharedPtr<IWebSocket> Socket;
        {
            FScopeLock Lock(Mutex.Get());
            if (ClosedValue)
            {
                return false;
            }
            ClosedValue = true;
            GenerationValue++;
            InflightRequests.GetKeys(Pending);
            InflightRequests.Reset();
            for (const auto& TaskId : Pending)
            {
                if (!Results.Contains(TaskId))
                {
                    Results.Emplace(TaskId, MakeConnectionLostResult(TaskId, Reason));
                }
            }
            Socket = SocketValue;
        }
        if (Pending.Num() > 0)
        {
            UE_LOG(Gs2Log, Warning, TEXT("websocket closed with %d pending request(s): %s"), Pending.Num(), ToCStr(Reason));
        }
        if (Socket.IsValid() && Socket->IsConnected())
        {
            Socket->Close();
        }
        return true;
    }

    void FGs2WebSocketSession::Send(const TSharedPtr<Task::FWebSocketSessionRequest> Request)
    {
        auto Body = Request->Payload();
        UE_LOG(Gs2Log, VeryVerbose, TEXT("%s"), ToCStr(Body));

        TSharedPtr<IWebSocket> Socket;
        {
            FScopeLock Lock(Mutex.Get());
            Socket = SocketValue;
            if (ClosedValue || !Socket.IsValid())
            {
                ClosedValue = true;
                if (!Results.Contains(Request->TaskId()))
                {
                    Results.Emplace(
                        Request->TaskId(),
                        MakeConnectionLostResult(Request->TaskId(), TEXT("websocket session is not connected"))
                    );
                }
                UE_LOG(Gs2Log, Warning, TEXT("[Socket::Send] websocket session is not connected."));
                return;
            }
            InflightRequests.Add(Request->TaskId(), Request);
        }
        Socket->Send(Body);
    }

    bool FGs2WebSocketSession::IsConnected() const
    {
        FScopeLock Lock(Mutex.Get());
        return ClosedValue || (SocketValue.IsValid() && SocketValue->IsConnected());
    }

    bool FGs2WebSocketSession::IsAlive() const
    {
        FScopeLock Lock(Mutex.Get());
        return !ClosedValue && SocketValue.IsValid() && SocketValue->IsConnected();
    }

    bool FGs2WebSocketSession::IsComplete(FGs2SessionTaskId TaskId) const
    {
        FScopeLock Lock(Mutex.Get());
        return Results.Contains(TaskId);
    }

    TSharedPtr<Task::FWebSocketResult> FGs2WebSocketSession::GetResult(FGs2SessionTaskId TaskId)
    {
        FScopeLock Lock(Mutex.Get());
        if (const auto Found = Results.Find(TaskId))
        {
            const auto WebSocketResult = *Found;
            Results.Remove(TaskId);
            return WebSocketResult;
        }
        InflightRequests.Remove(TaskId);
        return MakeConnectionLostResult(TaskId, TEXT("no result for the request"));
    }

    void FGs2WebSocketSession::OnMessage(TSharedPtr<Task::FWebSocketResult> Result)
    {
        FScopeLock Lock(Mutex.Get());
        if (InflightRequests.Contains(Result->TaskId()))
        {
            Results.Emplace(Result->TaskId(), Result);
            InflightRequests.Remove(Result->TaskId());
        }
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

    void FGs2WebSocketSession::SetSteadyEndpoint(const FString& SteadyEndpoint)
    {
        SteadyEndpointValue = FGs2Steady::NormalizeEndpoint(SteadyEndpoint);
    }

    FString FGs2WebSocketSession::SteadyEndpoint() const
    {
        return SteadyEndpointValue;
    }

    bool FGs2WebSocketSession::HasSteadyEndpoint() const
    {
        return !SteadyEndpointValue.IsEmpty();
    }

    FString FGs2WebSocketSession::EndpointUrl() const
    {
        if (const auto Url = FGs2Steady::WebSocketUrl(SteadyEndpointValue); !Url.IsEmpty())
        {
            return Url;
        }
        const auto RegionString = RegionName();
        return FGs2Constant::WebSocketEndpointHost.Replace(TEXT("{region}"), *RegionString);
    }

    Model::ERegion FGs2WebSocketSession::Region() const
    {
        return RegionValue;
    }

    Model::FGs2CredentialPtr FGs2WebSocketSession::Credential() const
    {
        return CredentialValue;
    }

    FString FGs2WebSocketSession::OwnerId() const
    {
        return OwnerIdValue;
    }

    FString FGs2WebSocketSession::RegionName() const
    {
        switch (RegionValue)
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
