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


#include "Core/Net/Steady.h"

namespace Gs2::Core::Net
{
    FString FGs2Steady::NormalizeEndpoint(const FString& Value)
    {
        FString Result = Value.TrimStartAndEnd();
        while (Result.EndsWith(TEXT("/"), ESearchCase::CaseSensitive))
        {
            Result = Result.LeftChop(1);
        }
        return Result;
    }

    FString FGs2Steady::RestTemplate(const FString& SteadyEndpoint)
    {
        const auto Base = NormalizeEndpoint(SteadyEndpoint);
        if (Base.IsEmpty())
        {
            return FString();
        }
        return Base + TEXT("/{service}");
    }

    FString FGs2Steady::WebSocketUrl(const FString& SteadyEndpoint)
    {
        const auto Base = NormalizeEndpoint(SteadyEndpoint);
        if (Base.IsEmpty())
        {
            return FString();
        }

        FString Scheme;
        FString Authority;
        if (Base.StartsWith(TEXT("https://")))
        {
            Scheme = TEXT("wss");
            Authority = Base.RightChop(8);
        }
        else if (Base.StartsWith(TEXT("http://")))
        {
            Scheme = TEXT("ws");
            Authority = Base.RightChop(7);
        }
        else
        {
            // 解釈できない基点（scheme 無し）は空を返し、呼び手は従来の接続先に落ちる。
            return FString();
        }

        // パスが付いていても authority だけを使う（Go の url.Parse().Host と同じ）。
        int32 SlashIndex = INDEX_NONE;
        if (Authority.FindChar(TEXT('/'), SlashIndex))
        {
            Authority = Authority.Left(SlashIndex);
        }
        if (Authority.IsEmpty())
        {
            return FString();
        }
        return Scheme + TEXT("://") + Authority + TEXT("/");
    }

    bool FGs2Steady::IsSteadyUrl(const FString& SteadyEndpoint, const FString& Url)
    {
        const auto Base = NormalizeEndpoint(SteadyEndpoint);
        if (Base.IsEmpty())
        {
            return false;
        }
        return Url == Base || Url.StartsWith(Base + TEXT("/"), ESearchCase::CaseSensitive);
    }
}
