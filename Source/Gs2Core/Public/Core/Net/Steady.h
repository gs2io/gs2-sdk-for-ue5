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

// Steady（専用フリート）の基点。
//
// フリートは 1 つの名前（SteadyEndpoint、例 https://bs-dev.ap-northeast-1.dev.gen2.gs2io.com）で受け、
// REST は <steady>/<service>/...、WebSocket は wss://<host>/ を使う。名前はフリートのノードへ直接
// 解決される（間に ALB は無い）ので、フリートが手放した公開 IP に当たると SYN が落ちる。
// そのため Steady のときだけ接続段階に上限（ConnectTimeoutSeconds）を置き、接続段階の失敗
// （1 バイトも送っていない）だけは同じ要求をもう 1 回だけ送る。送信後の失敗は届いたかもしれない
// ので再送しない（非冪等要求の二重実行を作らない）。
//
// golang/core/steady.go の写し（normalizeSteadyEndpoint / steadyRestTemplate / steadyWebSocketUrl / isSteadyUrl）。

#pragma once

#include "CoreMinimal.h"

namespace Gs2::Core::Net
{
    class GS2CORE_API FGs2Steady
    {
    public:
        /**
         * Steady の基点への接続段階の上限秒。フリートが手放した公開 IP は SYN を落とすので、OS 既定
         * （1〜2 分）に任せない。
         *
         * ★UE の HTTP には「接続段階だけ」の上限が無い。IHttpRequest::SetTimeout は要求全体の上限なので、
         * GS2 の長い API（POST / PUT）に掛けると正常な要求を殺す。したがって
         *  - 冪等な動詞（GET / DELETE）で Steady 宛のときだけ、要求全体の上限をこの値にする（近似）
         *  - POST / PUT には上限を掛けず、接続段階の失敗の 1 回再送だけを効かせる
         * FHttpModule の接続タイムアウト設定（[HTTP] HttpConnectionTimeout）はゲーム全体の HTTP に
         * 効いてしまうので SDK からは触らない。
         */
        static constexpr float ConnectTimeoutSeconds = 5.f;

        /** 末尾の / と空白を落とす。 */
        static FString NormalizeEndpoint(const FString& Value);

        /** SteadyEndpoint から REST の template（{service} 付き）を作る。空なら空文字列。 */
        static FString RestTemplate(const FString& SteadyEndpoint);

        /**
         * SteadyEndpoint から WebSocket の接続先を作る。空なら空文字列。
         * http:// の基点（ローカルの試験・開発）は ws:// に、https:// は wss:// に。
         */
        static FString WebSocketUrl(const FString& SteadyEndpoint);

        /** 要求 URL が Steady の基点宛か。 */
        static bool IsSteadyUrl(const FString& SteadyEndpoint, const FString& Url);
    };
}
