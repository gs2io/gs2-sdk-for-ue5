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

#include "Auth/Result/FederationResult.h"

namespace Gs2::Auth::Result
{
    FFederationResult::FFederationResult():
        TokenValue(TOptional<FString>()),
        UserIdValue(TOptional<FString>()),
        ExpireValue(TOptional<int64>())
    {
    }

    FFederationResult::FFederationResult(
        const FFederationResult& From
    ):
        TokenValue(From.TokenValue),
        UserIdValue(From.UserIdValue),
        ExpireValue(From.ExpireValue)
    {
    }

    TSharedPtr<FFederationResult> FFederationResult::WithToken(
        const TOptional<FString> Token
    )
    {
        this->TokenValue = Token;
        return SharedThis(this);
    }

    TSharedPtr<FFederationResult> FFederationResult::WithUserId(
        const TOptional<FString> UserId
    )
    {
        this->UserIdValue = UserId;
        return SharedThis(this);
    }

    TSharedPtr<FFederationResult> FFederationResult::WithExpire(
        const TOptional<int64> Expire
    )
    {
        this->ExpireValue = Expire;
        return SharedThis(this);
    }

    TOptional<FString> FFederationResult::GetToken() const
    {
        return TokenValue;
    }

    TOptional<FString> FFederationResult::GetUserId() const
    {
        return UserIdValue;
    }

    TOptional<int64> FFederationResult::GetExpire() const
    {
        return ExpireValue;
    }

    FString FFederationResult::GetExpireString() const
    {
        if (!ExpireValue.IsSet())
        {
            return FString("null");
        }
        return FString::Printf(TEXT("%lld"), ExpireValue.GetValue());
    }

    TSharedPtr<FFederationResult> FFederationResult::FromJson(const TSharedPtr<FJsonObject> Data)
    {
        if (Data == nullptr) {
            return nullptr;
        }
        return MakeShared<FFederationResult>()
            ->WithToken(Data->HasField("token") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("token", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithUserId(Data->HasField("userId") ? [Data]() -> TOptional<FString>
                {
                    FString v("");
                    if (Data->TryGetStringField("userId", v))
                    {
                        return TOptional(FString(TCHAR_TO_UTF8(*v)));
                    }
                    return TOptional<FString>();
                }() : TOptional<FString>())
            ->WithExpire(Data->HasField("expire") ? [Data]() -> TOptional<int64>
                {
                    int64 v;
                    if (Data->TryGetNumberField("expire", v))
                    {
                        return TOptional(v);
                    }
                    return TOptional<int64>();
                }() : TOptional<int64>());
    }

    TSharedPtr<FJsonObject> FFederationResult::ToJson() const
    {
        const TSharedPtr<FJsonObject> JsonRootObject = MakeShared<FJsonObject>();
        if (TokenValue.IsSet())
        {
            JsonRootObject->SetStringField("token", TokenValue.GetValue());
        }
        if (UserIdValue.IsSet())
        {
            JsonRootObject->SetStringField("userId", UserIdValue.GetValue());
        }
        if (ExpireValue.IsSet())
        {
            JsonRootObject->SetStringField("expire", FString::Printf(TEXT("%lld"), ExpireValue.GetValue()));
        }
        return JsonRootObject;
    }
}