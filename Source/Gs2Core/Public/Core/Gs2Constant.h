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
#include "GenericPlatform/GenericPlatformFile.h"
#include "Misc/Paths.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

GS2CORE_API DECLARE_LOG_CATEGORY_EXTERN(Gs2Log, Log, All);

namespace Gs2::Core
{
    class GS2CORE_API FGs2Constant
    {
    public:
        /**
         * 生成タスク（RestXxxTask.cpp）が URL の先頭に使う template。
         * ★生成タスクはセッションを見ずにこの static を直接読む。生成物を触らずに Steady（専用フリート）へ
         * 向けるには、ここに <steady>/{service} を入れるしかない（FGs2RestSession::SetSteadyEndpoint が
         * ApplySteadyEndpointHost 経由で行う）。{region} の置換は残っていても no-op になる。
         * ★プロセス全体で 1 つなので、セッションごとに別の Steady を使うことはできない（最後の設定が全部に効く）。
         */
        static FString EndpointHost;
        static FString WebSocketEndpointHost;

        /** 共有クラウドの既定値。アプリが上書きしたかの判定と、Steady を外したときの復帰に使う。 */
        static const FString DefaultEndpointHost;
        static const FString DefaultWebSocketEndpointHost;

        /** アプリが EndpointHost を自分で書き換えているか（Steady が書いた値は上書きとみなさない）。 */
        static bool IsEndpointHostOverridden();

        /**
         * EndpointHost に Steady の template を反映する。
         * 優先順: アプリによる静的な上書き ＞ SteadyEndpoint ＞ 共有クラウドの既定値。
         * SteadyEndpoint が空なら既定値に戻す。上書きがあるときは何もしない。
         */
        static void ApplySteadyEndpointHost(const FString& SteadyEndpoint);

    private:
        /** 直近に ApplySteadyEndpointHost が書いた値（空なら未適用）。 */
        static FString SteadyAppliedEndpointHost;
    };
}