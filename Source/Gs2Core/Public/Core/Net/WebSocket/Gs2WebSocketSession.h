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
#include "Core/Net/Steady.h"
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
        TFunction<TSharedPtr<IWebSocket>(const FString&)> WebSocketFactory;
        TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketSessionRequest>> InflightRequests;
        TMap<FGs2SessionTaskId, TSharedPtr<Task::FWebSocketResult>> Results;
        
        Model::FGs2CredentialPtr CredentialValue;
        Model::ERegion RegionValue;
        FString OwnerIdValue;

        TSharedPtr<FCriticalSection> Mutex;
        FGs2SessionTaskId LoginTaskId;
        FGs2NotificationEvent NotificationEvent;
        FGs2DisconnectEvent DisconnectEvent;
        /** Steady（専用フリート）の基点（https://<host>、正規化済み）。空なら共有クラウド。 */
        FString SteadyEndpointValue;
        /**
         * ★使える接続が無い間は true（まだ繋いでいない、閉じた、壊れた）。
         * true の間の送信は待たせずその場で FSessionNotOpenError にする。
         */
        bool ClosedValue;
        /**
         * ★今の接続の世代。Connect() と切断で増やし、古い socket から遅れて届く
         * OnMessage / OnClosed / OnConnectionError を弾くために使う。
         */
        int32 GenerationValue;

        /** ★Generation が今の接続のものか（古い socket のイベントを弾く）。 */
        bool IsCurrentGeneration(int32 Generation) const;
        /** ★応答待ちの要求へ返す「接続が無い」結果（FSessionNotOpenError）。 */
        static TSharedPtr<Task::FWebSocketResult> MakeConnectionLostResult(
            const FGs2SessionTaskId& TaskId,
            const FString& Reason
        );
        /**
         * ★接続が無くなったことを記録し、応答待ちの要求すべてを
         * FSessionNotOpenError で終わらせる（socket も閉じる）。
         * 戻り値は「接続があった→無くなった」に変わったか。
         * DisconnectEvent を鳴らすのは呼び手の役目。
         */
        bool DropConnection(const FString& Reason);

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

        FGs2WebSocketSession(
            const Model::FGs2CredentialPtr& Credential,
            const Model::ERegion Region,
            TFunction<TSharedPtr<IWebSocket>(const FString&)> WebSocketFactory
        );

        virtual ~FGs2WebSocketSession() override
        {
            Disposed = true;
        }

        void Connect();

        void Send(
            const TSharedPtr<Task::FWebSocketSessionRequest> Request
        );

        /**
         * ★「これ以上待っても状況が変わらないか」も兼ねる口。
         * 生成された各タスクの待ち合わせが
         * while (!IsConnected() || !IsComplete(TaskId)) なので、接続が無い間 false を
         * 返し続けると待ち側が永久に抜けられない。そこで接続が無いと分かって
         * いるときは true を返し、待ち側には DropConnection / Send が積んだ
         * FSessionNotOpenError を読ませる。生きているかどうかは IsAlive() で見る。
         */
        bool IsConnected() const;
        /** ★本当に繋がっているか（繋ぎ直しの判断に使う）。 */
        bool IsAlive() const;
        bool IsComplete(FGs2SessionTaskId TaskId) const;
        TSharedPtr<Task::FWebSocketResult> GetResult(FGs2SessionTaskId TaskId);
        
        void OnMessage(TSharedPtr<Task::FWebSocketResult> Result);
        FGs2NotificationEvent& OnNotification();
        FGs2DisconnectEvent& OnDisconnect();
    
        TSharedPtr<FAsyncTask<Task::FWebSocketOpenTask>> Open();
        TSharedPtr<FAsyncTask<Task::FWebSocketReOpenTask>> ReOpen();
        TSharedPtr<FAsyncTask<Task::FWebSocketCloseTask>> Close();

        /**
         * Steady（専用フリート）の基点（https://<host>）。Connect の前に設定する。空で共有クラウド。
         * 末尾の / と空白は落として保持する。
         */
        void SetSteadyEndpoint(const FString& SteadyEndpoint);
        FString SteadyEndpoint() const;
        bool HasSteadyEndpoint() const;

        /**
         * 次の Connect() が使う接続先。SteadyEndpoint ＞ 従来の FGs2Constant::WebSocketEndpointHost の置換。
         * Steady のときは wss://<host>/（基点が http:// なら ws://）。未設定なら従来と byte 単位で同じ。
         */
        FString EndpointUrl() const;
        
        virtual Model::ERegion Region() const override;
        virtual FString RegionName() const override;
        virtual Model::FGs2CredentialPtr Credential() const override;
        virtual FString OwnerId() const override;
    };
	typedef TSharedPtr<FGs2WebSocketSession, ESPMode::ThreadSafe> FGs2WebSocketSessionPtr;
}
