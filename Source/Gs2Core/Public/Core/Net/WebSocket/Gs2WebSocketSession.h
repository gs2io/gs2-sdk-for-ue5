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

#pragma once

#include "CoreMinimal.h"
#include "WebSocketsModule.h"
#include "Containers/BackgroundableTicker.h"
#include "Core/Gs2Constant.h"
#include "Core/Domain/Model/NotificationMessage.h"
#include "Core/Model/Region.h"
#include "Core/Net/Gs2Session.h"
#include "Task/WebSocketResult.h"
#include "Task/WebSocketSessionRequest.h"
#include "IWebSocket.h"

DECLARE_EVENT_OneParam(FGs2WebSocketSession, FGs2NotificationEvent, Gs2::Core::Domain::Model::FNotificationMessagePtr);
DECLARE_EVENT(FGs2WebSocketSession, FGs2DisconnectEvent);

namespace Gs2::Core::Net::WebSocket
{
    namespace Task
    {
        class GS2CORE_API FWebSocketOpenTask;
        class GS2CORE_API FWebSocketReOpenTask;
        class GS2CORE_API FWebSocketCloseTask;
        class GS2CORE_API FWebSocketResult;
    }
    
    class GS2CORE_API FGs2WebSocketSession final :
        public IGs2Session,
        public TSharedFromThis<FGs2WebSocketSession>
    {
        friend Task::FWebSocketOpenTask;
        friend Task::FWebSocketReOpenTask;
        friend Task::FWebSocketCloseTask;
        
        TSharedPtr<IWebSocket> SocketValue;
        TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketSessionRequest>> InflightRequests;
        TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketResult>> Results;
        
        Model::FGs2CredentialPtr CredentialValue;
        Model::ERegion Region;
        FString OwnerIdValue;

        TSharedPtr<FCriticalSection> Mutex;
        FGs2SessionTaskId LoginTaskId;
        FGs2NotificationEvent NotificationEvent;
        FGs2DisconnectEvent DisconnectEvent;

    public:
        bool Disposed;

        explicit FGs2WebSocketSession(
            const Model::FGs2CredentialPtr& Credential
        );
        FGs2WebSocketSession(
            const FGs2WebSocketSession& From
        );
    
        FGs2WebSocketSession(
            const Model::FGs2CredentialPtr& Credential,
            const Model::ERegion Region
        );

        virtual ~FGs2WebSocketSession() override
        {
            Disposed = true;
        }

        void Connect();

        void Send(
            const TSharedPtr<Task::FWebSocketSessionRequest> Request
        );

        bool IsConnected() const;
        bool IsComplete(FGs2SessionTaskId TaskId) const;
        TSharedPtr<Task::FWebSocketResult> GetResult(FGs2SessionTaskId TaskId);
        
        void OnMessage(TSharedPtr<Task::FWebSocketResult> Result);
        FGs2NotificationEvent& OnNotification();
        FGs2DisconnectEvent& OnDisconnect();
    
        TSharedPtr<FAsyncTask<Task::FWebSocketOpenTask>> Open();
        TSharedPtr<FAsyncTask<Task::FWebSocketReOpenTask>> ReOpen();
        TSharedPtr<FAsyncTask<Task::FWebSocketCloseTask>> Close();
        
        virtual FString RegionName() const override;
        virtual Model::FGs2CredentialPtr Credential() const override;
        virtual FString OwnerId() const override;
    };
	typedef TSharedPtr<FGs2WebSocketSession, ESPMode::ThreadSafe> FGs2WebSocketSessionPtr;
}
