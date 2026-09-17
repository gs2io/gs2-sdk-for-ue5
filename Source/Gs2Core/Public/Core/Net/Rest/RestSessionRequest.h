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

namespace Gs2::Core::Net::Rest
{
    /** HTTP 応答が 1 つも得られなかった理由（FGs2RestSession::Send）。 */
    enum class ERestTransportFailure : uint8
    {
        /** 応答あり（ステータスコードは FRestSessionResponse::ResponseCode）。 */
        None,
        /** 接続段階の失敗（DNS / TCP 拒否。要求が 1 バイトも出ていない）。これだけが再送の対象。 */
        ConnectFailed,
        /** 要求タイムアウト（UE 5.4 以降だけ区別できる）。送信後かもしれないので再送しない。 */
        Timeout,
        /** それ以外（TLS 失敗・送信後の切断・キャンセル等）。届いたかもしれないので再送しない。 */
        Other,
    };

    /**
     * FGs2RestSession::Send に渡す 1 要求。生成タスクが IHttpRequest に積むものと同じ（動詞・URL・ヘッダ・本文）。
     * ★本文は FString で持ち、要求ごとに IHttpRequest を組み直す（Steady の再送で同じ要求をもう一度組むため）。
     */
    class GS2CORE_API FRestSessionRequest final
    {
    public:
        FString Verb;
        FString Url;
        TArray<TPair<FString, FString>> Headers;
        TOptional<FString> Body;

        FRestSessionRequest() = default;
        FRestSessionRequest(
            const FString& Verb,
            const FString& Url
        );

        FRestSessionRequest& AddHeader(const FString& Name, const FString& Value);
        FRestSessionRequest& SetBody(const FString& InBody);

        /** GET / DELETE だけを冪等とみなす（要求全体のタイムアウトを掛けてよい動詞）。 */
        bool IsIdempotent() const;
    };

    /** FGs2RestSession::Send の結果。 */
    class GS2CORE_API FRestSessionResponse final
    {
    public:
        FString Url;
        int32 ResponseCode = 999;
        FString ResponseBody;
        ERestTransportFailure TransportFailure = ERestTransportFailure::Other;
        /** 接続段階の失敗で同じ要求をもう 1 回送ったか。 */
        bool bRetried = false;

        bool HasResponse() const
        {
            return TransportFailure == ERestTransportFailure::None;
        }
    };
}
