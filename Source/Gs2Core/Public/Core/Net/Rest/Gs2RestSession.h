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
#include "Async/AsyncWork.h"
#include "../../Model/Region.h"
#include "../../Net/Gs2Session.h"
#include "Core/Net/Steady.h"
#include "Core/Net/Rest/RestSessionRequest.h"

namespace Gs2::Core::Net::Rest
{
    namespace Task
    {
        class GS2CORE_API FRestOpenTask;
        class GS2CORE_API FRestReOpenTask;
        class GS2CORE_API FRestCloseTask;
    }
    
    class GS2CORE_API FGs2RestSession final :
        public IGs2Session,
        public TSharedFromThis<FGs2RestSession>
    {
        Model::FGs2CredentialPtr CredentialValue;
        Model::ERegion RegionValue;
        FString OwnerIdValue;
        /** Steady（専用フリート）の基点（https://<host>、正規化済み）。空なら共有クラウド。 */
        FString SteadyEndpointValue;

    public:
        explicit FGs2RestSession(
            const Model::FGs2CredentialPtr Credential
        );
        FGs2RestSession(
            const FGs2RestSession& From
        );
    
        FGs2RestSession(
            const Model::FGs2CredentialPtr Credential,
            const Model::ERegion Region
        );

        TSharedPtr<FAsyncTask<Task::FRestOpenTask>> Open();
        TSharedPtr<FAsyncTask<Task::FRestReOpenTask>> ReOpen();
        TSharedPtr<FAsyncTask<Task::FRestCloseTask>> Close();

        /**
         * Steady（専用フリート）の基点（https://<host>）。セッションを開く前に設定する。空で共有クラウド。
         * 末尾の / と空白は落として保持する。
         * ★設定すると FGs2Constant::EndpointHost にも <steady>/{service} を書く（生成タスクはセッションを
         * 見ずにこの static を読むため）。したがって実質はプロセス全体の設定で、セッションごとに別の Steady は持てない。
         */
        void SetSteadyEndpoint(const FString& SteadyEndpoint);
        FString SteadyEndpoint() const;
        bool HasSteadyEndpoint() const;

        /**
         * 要求 URL の先頭（末尾に / は付かない）。
         * 優先順: アプリによる静的な上書き（FGs2Constant::EndpointHost）＞ SteadyEndpoint ＞ 共有クラウドの既定値。
         * SteadyEndpoint が未設定で上書きも無ければ、従来の
         * FGs2Constant::EndpointHost.Replace("{service}", Service).Replace("{region}", RegionName()) と byte 単位で同じ。
         */
        FString EndpointHost(const FString& Service) const;

        /**
         * 1 要求を送って応答を待つ（生成タスクの送信部と同じ Flush / Sleep 待ち）。
         * Steady の基点宛で接続段階の失敗（ConnectFailed。1 バイトも送っていない）だったときだけ、
         * 同じ要求をもう 1 回だけ送る（3 回目は無い）。送信後の失敗・5xx・Steady 未設定では再送しない。
         * ★冪等な動詞（GET / DELETE）が Steady 宛のときだけ FGs2Steady::ConnectTimeoutSeconds を要求全体の
         * タイムアウトに使う（UE には接続専用のタイムアウトが無いので、その近似）。POST / PUT には掛けない
         * （GS2 の長い API を殺す）ので、そちらは再送だけが効く。
         * ★生成タスク（RestXxxTask.cpp）は自分で IHttpRequest を組んで送るので、この再送は通らない。
         * 生成物を触らずに再送まで効かせるには sdk-gen の cpp テンプレートを Session->Send に寄せる必要がある。
         * 現状で再送が効くのは core が送る要求（プロジェクトトークンのログイン）だけ。
         */
        FRestSessionResponse Send(const FRestSessionRequest& Request) const;
        
        virtual FString OwnerId() const override;
        virtual void SetOwnerId(FString OwnerId);
        virtual Model::ERegion Region() const override;
        virtual FString RegionName() const override;
        virtual Model::FGs2CredentialPtr Credential() const override;
    };
	typedef TSharedPtr<FGs2RestSession, ESPMode::ThreadSafe> FGs2RestSessionPtr;
}
